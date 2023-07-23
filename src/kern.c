#include <screen.h>
#include <keyboard.h>
#include <mouse.h>
#include <string.h>
#include <rand.h>

asm("mov sp, _KSTACK_PTR");

#define INP_BUF_SZ 512
#define SRAND_SEED 17290

#define SCREEN_COLOR 0x0f

char inp_buf[INP_BUF_SZ];

char* funny_strings[] = {
    "nope\n", "try again\n", "UwU\n",
    "mitochondria is the powerhouse of the cell\n", "bing chilling\n", "sus\n"
};

void print_help() {
    puts(".-------------------------------.\n");
    puts("| CONGRATZ, YOU HIT THE JACKPOT |\n");
    puts("'-------------------------------'\n");
    puts("\nhere's the help menu:\n\n");
    puts("help - print this menu (sometimes)\n");
    puts("cls - clear screen\n");
}

asm("global __start");
asm("__start:");
void main(){
    srand(SRAND_SEED);
    int funny_strings_ctr = 1;

    cls(SCREEN_COLOR);
    puts(
        ".---------------------------------------------------.\n"
        "| Welcome to the Mustard Non-Operating System (TM) !|\n"
        "'---------------------------------------------------'\n\n"
    );
    puts(
        "Type \"help\" to get a list of available commands.\n"
        "It might work, it might not work. gl c:\n\n"
    );

    mouse_initialize();
    mouse_enable();

    while(1) {
        puts("C:\\> ");
        readline(INP_BUF_SZ, inp_buf);
        
        if(strcmp(inp_buf, "help\r") == 0) {
            funny_strings_ctr = 
                (funny_strings_ctr + rand())%
                (sizeof(funny_strings)/sizeof(char*));

            if(funny_strings_ctr%3 == 0)
                print_help();
            else {
                puts(funny_strings[funny_strings_ctr]);
            }
        }

        else if(strcmp(inp_buf, "cls\r") == 0) {
            cls(SCREEN_COLOR);
            continue;
        }

        else {
            puts(inp_buf);
        }

        putc('\n');
    }
    while(1);
}


asm("times 1024 db 0");
asm("_KSTACK_PTR:");
