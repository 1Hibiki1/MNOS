/**
 * @file string.h
 * @author 1Hibiki1 (tori96.1729@gmail.com)
 * @brief string library interface
 * @version 0.0.1
 * @date 2023-07-24
 */

#ifndef _STRING_H
#define _STRING_H

char *strchr(const char *str, int c);
int strcmp(const char *X, const char *Y);
size_t *strlen(const char *str);
int strncmp(const char *X, const char *Y, size_t n);
char *strpbrk(const char *X, const char *Y);
char *strrchr(const char *str, int c);

#endif  /* _STRING_H */
