/**
 * @file stdint.h
 * @author ghostlypi (parth.iyer@gmail.com)
 * @brief integer library interface
 * @version 0.0.1
 * @date 2023-07-23
 */
#ifndef __STDINT_H
#define __STDINT_H

#ifndef __INTPTR_T_DEF
#define __INTPTR_T_DEF
typedef int intptr_t;
#endif
typedef unsigned uintptr_t;

#ifdef __SMALLER_C_16__
#define INTPTR_MIN (-32768)
#define INTPTR_MAX 32767
#define UINTPTR_MAX 65535U

#define PTRDIFF_MIN (-32768)
#define PTRDIFF_MAX 32767

#define SIZE_MAX 65535U

typedef int intmax_t;
#define INTMAX_MIN (-32768)
#define INTMAX_MAX 32767
typedef unsigned uintmax_t;
#define UINTMAX_MAX 65535U
#endif  // __SMALLER_C_16__

typedef signed char int8_t, int_least8_t, int_fast8_t;
typedef unsigned char uint8_t, uint_least8_t, uint_fast8_t;

typedef short int16_t, int_least16_t, int_fast16_t;
typedef unsigned short uint16_t, uint_least16_t, uint_fast16_t;

#define INT8_MIN (-128)
#define INT_LEAST8_MIN (-128)
#define INT_FAST8_MIN (-128)
#define INT8_MAX 127
#define INT_LEAST8_MAX 127
#define INT_FAST8_MAX 127
#define UINT8_MAX 255
#define UINT_LEAST8_MAX 255
#define UINT_FAST8_MAX 255

#define INT16_MIN (-32767 - 1)
#define INT_LEAST16_MIN (-32767 - 1)
#define INT_FAST16_MIN (-32767 - 1)
#define INT16_MAX 32767
#define INT_LEAST16_MAX 32767
#define INT_FAST16_MAX 32767
#define UINT16_MAX 0xFFFF
#define UINT_LEAST16_MAX 0xFFFF
#define UINT_FAST16_MAX 0xFFFF

#define INT8_C(val) (val)
#define UINT8_C(val) (val)

#define INT16_C(val) (val)
#define UINT16_C(val) (val##U)

#define INTMAX_C(val) (val)
#define UINTMAX_C(val) (val##U)

#ifndef WCHAR_MAX

#ifdef __SIGNED_WCHAR__
typedef int wchar_t;
#define WCHAR_MIN (-32768)
#define WCHAR_MAX 32767
#endif  // __SIGNED_WCHAR__
#ifdef __UNSIGNED_WCHAR__
typedef unsigned int wchar_t;
#define WCHAR_MIN 0
#define WCHAR_MAX 0xFFFF
#endif  // __UNSIGNED_WCHAR__

#endif  // WCHAR_MAX

#endif
