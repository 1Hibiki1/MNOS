#include <screen.h>

int scr_col = 0x0F;

void _putc(char c, int col) {
	asm("mov ah, 0x0e");
	asm("mov al, [bp+4]");
	asm("mov bh, 0");
	asm("mov bl, [bp+6]");
	asm("int 0x10");
}

void putc(char c) {
    switch(c) {
        case '\n':
        case '\r': {
            _putc('\r', scr_col);
            _putc('\n', scr_col);
            return;
        }

        case '\b': {
            _putc('\b', scr_col);
            _putc(' ', scr_col);
            _putc('\b', scr_col);
            return;
        }
    }

    _putc(c, scr_col);
}

void puts(char* s) {
	while(*s) {
		putc(*s);
		s++;
	}
}

void putint(int num) {
    if (num == 0) {
        putc('0');
        return;
    }

    if (num < 0) {
        putc('-');
        num = -num;
    }

    char buffer[10]; // Maximum number of digits in a 32-bit integer
    int index = 0;

    while (num > 0) {
        int digit = num % 10;
        buffer[index++] = '0' + digit;
        num /= 10;
    }

    while (--index >= 0) {
        putc(buffer[index]);
    }
}

void puthex(unsigned int num) {
    if (num == 0) {
        putc('0');
        return;
    }

    char buffer[8]; // Maximum number of hex digits in a 32-bit unsigned integer
    int index = 0;

    while (num > 0) {
        int digit = num % 16;
        if (digit < 10)
            buffer[index++] = '0' + digit;
        else
            buffer[index++] = 'A' + (digit - 10);
        num /= 16;
    }

    while (--index >= 0) {
        putc(buffer[index]);
    }
}

void putpix(int x, int y, char col) {
    asm("mov ah, 0xC");
    asm("mov al, [bp+8]");
    asm("mov bh, 0");
    asm("mov cx, [bp+4]");
    asm("mov dx, [bp+6]");
    asm("int 0x10");
}

void cls(int col) {
    scr_col = col;

    asm("MOV AH, 0x02");
    asm("MOV BH, 0");
    asm("MOV DH, 0");
    asm("MOV DL, 0");
    asm("INT 0x10");

    for(int i = 0; i < SCREEN_HEIGHT*SCREEN_WIDTH; i++) {
        putc(' ');
    }

    asm("MOV AH, 0x02");
    asm("MOV BH, 0");
    asm("MOV DH, 0");
    asm("MOV DL, 0");
    asm("INT 0x10");
}
