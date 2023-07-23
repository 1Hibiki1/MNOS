#include <keyboard.h>
#include <screen.h>

char getch() {
    asm("MOV AH, 0");
    asm("INT 0X16");
}

void readline(int len, char* buf) {
    int ctr = 0;
    char inp = '\0';
    while(inp != '\r' && ctr < len) {
        inp = getch();

        if(inp == '\b') {
            if(ctr > 0) {
                ctr--;
                putc(inp);
            }
            continue;
        }

        putc(inp);
        buf[ctr++] = inp;
    }
    buf[ctr] = '\0';
}
