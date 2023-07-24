/**
 * @file keyboard.c
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief utility functions for keyboard
 * @version 0.0.1
 * @date 2023-07-24
 */

/* -------------------------------- includes -------------------------------- */
#include <devices/keyboard.h>
#include <devices/screen.h>
/* -------------------------------------------------------------------------- */

/**
 * @brief Get one character of input from user.
 *
 * Blocks until character is typed. The input character is not printed on the
 * screen. This function uses BIOS interrupt 0x16, AH=0.
 *
 * @return typed character
 */
char keyboard_getch() {
  asm("mov ah, 0");
  asm("int 0x16");
}

/**
 * @brief Read a line of input into buffer.
 *
 * Uses keyboard_getch, typed characters are echoed on the screen. Blocks until
 * a line of input is typed or the maximum number of input characters have been
 * typed. Buffer contains the trailing newline.
 *
 * @param buf - character buffer to read user input into
 * @param len - max length of input read
 * @return number of characters read on success, -1 on failure
 */
int keyboard_readline(char* buf, int len) {
  int n_chars = 0;      /* number of characters read */
  char inp_char = '\0'; /* current input character */

  /* loop until user hits enter or max no. of chars are typed */
  while (inp_char != '\r' && n_chars < len) {
    /* block until user types character */
    inp_char = keyboard_getch();

    /* check if user typed backspace */
    if (inp_char == '\b') {
      /* if buffer is not empty, remove a character from it and erase
         character on screen */
      if (n_chars > 0) {
        n_chars--;
        screen_putc(inp_char);
      }
      /* move on to next char */
      continue;
    }
    screen_putc(inp_char);     /* echo input character */
    buf[n_chars++] = inp_char; /* write to input buffer */
  }

  /* newline represented by '\n' and not '\r' */
  if (inp_char == '\r') {
    buf[n_chars - 1] = '\n';
  }

  /* write null terminator at the end of input in buffer */
  buf[n_chars] = '\0';

  return n_chars;
}
