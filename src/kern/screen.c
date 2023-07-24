/**
 * @file screen.c
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief some utility functions for screen
 * @version 0.0.1
 * @date 2023-07-24
 */


/* -------------------------------- includes -------------------------------- */
#include <devices/screen.h>
/* -------------------------------------------------------------------------- */


/* --------------------------------- globals -------------------------------- */
int scr_col = 0x0F;
/* -------------------------------------------------------------------------- */


/**
 * @brief put a character at the current cursor position
 * 
 * 
 * Advance the cursor and scroll if necessary.
 * 
 * @param c - character to print
 * @param col - BG/FG color of the character
 */
void _putc(char c, int col) {
	asm("mov ah, 0x0e");
	asm("mov al, [bp+4]");  /* get first arg */
	asm("mov bh, 0");
	asm("mov bl, [bp+6]");  /* get second arg */
	asm("int 0x10");
}

/**
 * @brief interface function for printing a character on screen
 * 
 * @param c - character to print
 */
void screen_putc(char c) {
    switch(c) {
        /* LF and CR both do the mov the cursor to col 0 of next line */
        case '\n':
        case '\r': {
            _putc('\r', scr_col);
            _putc('\n', scr_col);
            return;
        }

        /* '\b' erases the character to the left of cursor and moves cursor
           back. has no effect is cursor is at col 0. */
        case '\b': {
            _putc('\b', scr_col);
            _putc(' ', scr_col);
            _putc('\b', scr_col);
            return;
        }
    }

    _putc(c, scr_col);
}

/**
 * @brief Print a null-terminated string of characters on screen
 * 
 * @param s - string to print
 */
void screen_puts(char* s) {
	while(*s) {
		screen_putc(*s);
		s++;
	}
}

/**
 * @brief print a signed integer on screen
 * 
 * @param num - integer to print
 */
void screen_putint(int num) {
    /* the "trivial case" */
    if (num == 0) {
        screen_putc('0');
        return;
    }

    /* print negative sign? */
    if (num < 0) {
        screen_putc('-');
        num = -num;
    }

    char buffer[5]; /* Maximum number of digits in a 16-bit integer */
    int index = 0;

    while (num > 0) {
        int digit = num % 10;
        buffer[index++] = '0' + digit;
        num /= 10;
    }

    /* print the integer */
    while (--index >= 0) {
        screen_putc(buffer[index]);
    }
}

/**
 * @brief print a hex value on screen
 * 
 * @param num - number to print as hex
 */
void screen_puthex(unsigned int num) {
    if (num == 0) {
        screen_putc('0');
        return;
    }

    char buffer[4]; /* Maximum number of hex digits in a 16-bit integer */
    int index = 0;

    while (num > 0) {
        int digit = num % 16;
        if (digit < 10)
            buffer[index++] = '0' + digit;
        else
            buffer[index++] = 'A' + (digit - 10);
        num /= 16;
    }

    /* print the hex number */
    while (--index >= 0) {
        screen_putc(buffer[index]);
    }
}

/**
 * @brief put a pixel of specified color at specified location on screen
 * 
 * @param x - x location of pixel
 * @param y - y location of pixel
 * @param col - color of pixel
 * @return 0 on success, -1 on error
 */
int screen_putpix(int x, int y, unsigned char col) {
    if(x < 0 || x > SCREEN_WIDTH_P) {
        return -1;
    }

    if(y < 0 || y > SCREEN_HEIGHT_P) {
        return -1;
    }

    asm("mov ah, 0xC");
    asm("mov al, [bp+8]");
    asm("mov bh, 0");
    asm("mov cx, [bp+4]");
    asm("mov dx, [bp+6]");
    asm("int 0x10");

    return 0;
}

/**
 * @brief clear the screen with BG|FG color
 * 
 * @param col - bg, fg color
 */
void screen_cls(unsigned char col) {
    scr_col = col;

    /* move cursor to 0,0 */
    asm("mov ah, 0x02");
    asm("mov bh, 0");
    asm("mov dh, 0");
    asm("mov al, 0");
    asm("int 0x10");

    /* print ' ' on entire screen */
    /* TODO: this is inefficient, use some bios service to do this */
    for(int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++) {
        screen_putc(' ');
    }

    /* move cursor back to 0,0 */
    asm("mov ah, 0x02");
    asm("mov bh, 0");
    asm("mov dh, 0");
    asm("mov al, 0");
    asm("int 0x10");
}
