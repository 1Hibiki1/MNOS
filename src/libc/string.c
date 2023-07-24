/**
 * @file string.c
 * @authors 1Hibiki1 (tori96.1729@gmail.com), ghostlypi (parth.iyer@gmail.com)
 * @brief string library implementation
 * @version 0.0.1
 * @date 2023-07-24
 */


/* -------------------------------- includes -------------------------------- */
#include <libc/string.h>
/* -------------------------------------------------------------------------- */

/**
 * @brief find a char in a string
 * 
 * @param str - string
 * @param c - int
 * @return pointer to the string beginning with the first instance of the char
 */
char *strchr(const char *str, int c) {
    while (*str) {
        //Check if the current character is c
        if (*str == c) {
            return str;
        }

        //move the character forward
        str++;
    }
    return NULL;
}

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

/**
 * @brief get the length of a string
 * 
 * @param str - string
 * @return the size of the string
 */
size_t *strlen(const char *str) {
    size_t count = 0;
    while (*str){
        //forward count and string
        count++;
        str++;
    }
    return count;
}

/**
 * @brief compare the first n chars between two strings
 * 
 * @param X - string 1
 * @param Y - string 2
 * @param n - size_t
 * @return 0 if equal within the first n chars, difference otherwise 
 */
int strncmp(const char *X, const char *Y, size_t n) {
    while (*X && n){
        /* if characters differ, or end of the second string is reached */
        if (*X != *Y) {
            break;
        }
 
        /* move to the next pair of characters decrement n*/
        X++;
        Y++;
        n--;
    }
 
    /* return the ASCII difference */
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

/**
 * @brief find any match between two strings
 * 
 * @param X - string 1
 * @param Y - string 2
 * @return a pointer to the first char in X that is also in Y
 */
char *strpbrk(const char *X, const char *Y) {
    while(*X) {
        //Set temporary so we can check the whole string every time
        const char *t = Y;
        while (*t) {
            //return on any match
            if (*X == *t) {
                return X;
            }

            //move through Y
            t++;
        }

        //move through X
        X++;
    }
    return NULL;
}

/**
 * @brief returns the rightmost instance of a char in the string
 * 
 * @param X - string 1
 * @param Y - string 2
 * @return a pointer to the first char in X that is also in Y
 */
char *strrchr(const char *str, int c) {
    const char *last = NULL;

    while (*str) {
        //update last on any match
        if (*str == c) {
            last = str;
        }

        //move through str
        str++;
    }

    return last;
}
