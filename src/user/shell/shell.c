/**
 * @file shell.c
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief "shell" implementation
 * @version 0.0.1
 * @date 2023-07-24
 */


/* -------------------------------- includes -------------------------------- */
#include <user/shell.h>
#include <devices/screen.h>
#include <devices/keyboard.h>
/* -------------------------------------------------------------------------- */


/* --------------------------------- defines -------------------------------- */
#define INP_BUF_MAX_LEN 512
/* -------------------------------------------------------------------------- */


/* --------------------------------- globals -------------------------------- */
char inp_buf[INP_BUF_MAX_LEN];
/* -------------------------------------------------------------------------- */


/**
 * @brief shell main function
 * 
 * @return 0 
 */
int shell_main() {
    /* echo shell */
    while(1) {
        screen_puts("C:\> ");
        keyboard_readline(inp_buf, INP_BUF_MAX_LEN);
        screen_puts(inp_buf);
        screen_putc('\n');
    }
    return 0;
}
