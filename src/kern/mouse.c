/**
 * @file mouse.c
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief mouse driver implementation
 * @version 0.0.1
 * @date 2023-07-24
 */

/* -------------------------------- includes -------------------------------- */
#include <devices/mouse.h>
#include <devices/screen.h>
/* -------------------------------------------------------------------------- */

/* --------------------------------- defines -------------------------------- */
#define MOUSE_CURSOR_W 14
#define MOUSE_CURSOR_H 20
/* -------------------------------------------------------------------------- */

/* --------------------------------- globals -------------------------------- */
int mouseX = 0;
int mouseY = 0;
/* -------------------------------------------------------------------------- */

/**
 * @brief "THE" mouse cursor
 *
 */
char mouseCursor[MOUSE_CURSOR_H][MOUSE_CURSOR_W] = {
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 9, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 0xf, 9, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 9, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 9, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 9, 0, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 9, 0, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 9, 0, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 9, 0},
    {9, 0xf, 0xf, 0xf, 0xf, 9, 9, 9, 9, 9, 9, 9, 9, 9},
    {9, 0xf, 0xf, 0xf, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0xf, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0xf, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
/* -------------------------------------------------------------------------- */

/**
 * @brief mouse interrupt handler
 *
 * @param ignore1
 * @param ignore2
 * @param my_arg - mouse y movement, a signed 8 bit value
 * @param mx_arg - mouse x movement, a signed 8 bit value
 * @param stat_arg - mouse status: info about buttons pressed, etc
 */
void mouse_handler(int ignore1, int ignore2, char my_arg, char mx_arg,
                   char stat_arg) {
  /* "clear" the area where the cursor currently is*/
  /* this won't really work, cuz it will completely erase what was on
     the screen previously. Need to store the "previous" pixel values
     under mouse cursor so that it can be restored on cursor move. */
  for (int i = 0; i < MOUSE_CURSOR_H; i++) {
    for (int j = 0; j < MOUSE_CURSOR_W; j++) {
      screen_putpix(mouseX + j, mouseY + i, 0);
    }
  }

  /* calculate new x, y positions */
  short newMouseX = mouseX + mx_arg;
  short newMouseY = mouseY - my_arg;

  /* update positions of they dont run off the screen*/
  if (newMouseX > 0 && newMouseX < SCREEN_WIDTH_P) {
    mouseX = newMouseX;
  }
  if (newMouseY > 0 && newMouseY < SCREEN_HEIGHT_P) {
    mouseY = newMouseY;
  }

  /* draw cursor at new position */
  for (int i = 0; i < MOUSE_CURSOR_H; i++) {
    for (int j = 0; j < MOUSE_CURSOR_W; j++) {
      if (mouseCursor[i][j])
        screen_putpix(mouseX + j, mouseY + i, mouseCursor[i][j]);
    }
  }

  /* return from a "far call" */
  asm("leave");
  asm("retf");
}

/**
 * @brief Initialize the mouse
 *
 * Checks if mouse os available, and installs mouse handler
 *
 * @return 0 on success, -1 on error
 */
int mouse_initialize(void) {
  asm("int 0x11");
  asm("test ax, 4");
  asm("jz _fail");

  asm("mov ax, 0xC205");
  asm("mov bh, 3");
  asm("int 0x15");
  asm("jc _fail");

  asm("mov bx, _mouse_handler");
  asm("mov ax, 0xC207");
  asm("int 0x15");
  asm("jc _fail");

  return 0;

  asm("_fail:");
  return -1;
}

/**
 * @brief enable the mouse
 *
 */
void mouse_enable() {
  /* disable before modifying */
  mouse_disable();

  /* install mouse handler */
  asm("mov bx, _mouse_handler");
  asm("mov ax, 0xC207");
  asm("int 0x15");

  /* enable */
  asm("mov ax, 0xC200");
  asm("mov bh, 1");
  asm("int 0x15");
}

/**
 * @brief disable the mouse
 *
 */
void mouse_disable() {
  asm("mov ax, 0xC200");
  asm("xor bx, bx");
  asm("int 0x15");
}
