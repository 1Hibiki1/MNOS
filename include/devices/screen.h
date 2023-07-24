/**
 * @file screen.h
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief screen interface
 * @version 0.0.1
 * @date 2023-07-24
 */

#ifndef _SCREEN_H
#define _SCREEN_H

/* character width and height of screen */
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

/* pixel width and height of screen */
#define SCREEN_WIDTH_P 640
#define SCREEN_HEIGHT_P 350

void screen_cls(unsigned char col);
void screen_putc(char c);
void screen_puts(char* str);
void screen_putint(int num);
void screen_puthex(unsigned int num);
int screen_putpix(int x, int y, unsigned char col);

#endif  /* _SCREEN_H */
