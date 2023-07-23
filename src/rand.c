#include <rand.h>

static unsigned int next = 1;

int rand(void) {
    next = (next * 20077 + 13245) & 0xffff;
    return ((unsigned int)(next/22768) % 32761) & 0xffff;
}

void srand(unsigned int seed) {
    next = seed;
}