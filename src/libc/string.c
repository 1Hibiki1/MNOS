/**
 * @file string.c
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief string library implementation
 * @version 0.0.1
 * @date 2023-07-24
 */


/* -------------------------------- includes -------------------------------- */
#include <libc/string.h>
/* -------------------------------------------------------------------------- */


/**
 * @brief compare two strings
 * 
 * @param X - string 1
 * @param Y - string 2
 * @return 0 if equal, difference otherwise 
 */
int strcmp(const char *X, const char *Y) {
    while (*X){
        /* if characters differ, or end of the second string is reached */
        if (*X != *Y) {
            break;
        }
 
        /* move to the next pair of characters */
        X++;
        Y++;
    }
 
    /* return the ASCII difference */
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}
