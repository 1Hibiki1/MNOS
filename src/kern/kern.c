/**
 * @file kern.c
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief kernel entrypoint
 * @version 0.0.1
 * @date 2023-07-24
 */

/* -------------------------------- includes -------------------------------- */
#include <devices/mouse.h>
#include <devices/screen.h>
#include <user/shell.h>
/* -------------------------------------------------------------------------- */

/* setup stack before anything else */
asm("mov sp, _KSTACK_PTR");

/**
 * @brief Kernel main function.
 *
 * called _start so that linker does not freak out.
 *
 */
void _start() {
  /* clear screen with white FG and black BG */
  screen_cls(0x0F);

  /* initialize everything */
  mouse_initialize();
  mouse_enable();

  /* welcome the user to our... our what? */
  screen_puts(
      ".---------------------------------------------------.\n"
      "| Welcome to the Mustard Non-Operating System (TM) !|\n"
      "'---------------------------------------------------'\n\n");

  /* start shell */
  /* for now the shell is a part of the kernel, we need to make it a user
     program and load it in */
  shell_main();

  /* ... ?? */
  while (1) /* keep the bus warm */
    asm("hlt");
}

/* 4k stack for now */
asm("times 4096 db 0");
asm("_KSTACK_PTR:");
