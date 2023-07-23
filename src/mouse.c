#include <mouse.h>
#include <screen.h>

int mouseX = 0;
int mouseY = 0;

#define CUR_W 14
#define CUR_H 20

char mouseCursor[20][14] = {
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

void mouse_handler(
    int ignore1, int ignore2,
    char my_arg, char mx_arg, char stat_arg
) {
    for (int i = 0; i < CUR_H; i++) {
        for (int j = 0; j < CUR_W; j++) {
            putpix(mouseX + j, mouseY + i, 0);
        }
    }

    short newMouseX = mouseX + mx_arg;
    short newMouseY = mouseY - my_arg;

    if(newMouseX > 0 && newMouseX < SCREEN_WIDTH_P) {
        mouseX = newMouseX;
    }

    if(newMouseY > 0 && newMouseY < SCREEN_HEIGHT_P) {
        mouseY = newMouseY;
    }

    for (int i = 0; i < CUR_H; i++) {
        for (int j = 0; j < CUR_W; j++) {
            if(mouseCursor[i][j])
                putpix(mouseX + j, mouseY + i, mouseCursor[i][j]);
        }
    }
    // putpix(mouseX, mouseY, 0x0A);

    asm("leave");
    asm("retf");
}

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

void mouse_enable() {
    mouse_disable();

    asm("mov bx, _mouse_handler");
    asm("mov ax, 0xC207");
    asm("int 0x15");

    asm("MOV AX, 0xC200");
    asm("MOV BH, 1");
    asm("INT 0x15");
}

void mouse_disable() {
    asm("MOV AX, 0xC200");
    asm("xor bx, bx");
    asm("INT 0x15");
}
