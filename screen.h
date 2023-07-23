#ifndef _SCREEN_H
#define _SCREEN_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define SCREEN_WIDTH_P 640
#define SCREEN_HEIGHT_P 350

void putc(char c);
void puts(char* str);
void putint(int num);
void puthex(unsigned int num);
void putpix(int x, int y, char col);

#endif  /* _SCREEN_H */
