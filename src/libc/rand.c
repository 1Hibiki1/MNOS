/**
 * @file rand.c
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief rng implementation
 * @version 0.0.1
 * @date 2023-07-24
 */


/* -------------------------------- includes -------------------------------- */
#include <libc/rand.h>
/* -------------------------------------------------------------------------- */


/* --------------------------------- globals -------------------------------- */
static unsigned int next = 1;
/* -------------------------------------------------------------------------- */

/**
 * @brief get a random number
 * 
 * @return random number 
 */
int rand(void) {
    next = (next * 20077 + 13245) & 0xffff;
    return ((unsigned int)(next/22768) % 32761) & 0xffff;
}

/**
 * @brief set the rng seed
 * 
 * @param seed
 */
void srand(unsigned int seed) {
    next = seed;
}
