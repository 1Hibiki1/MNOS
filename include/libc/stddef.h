/**
 * @file stddef.h
 * @author ghostlypi (parth.iyer@gmail.com)
 * @brief definition library interface
 * @version 0.0.1
 * @date 2023-07-23
 */
#ifndef __STDDEF_H
#define __STDDEF_H

#ifndef NULL
#define NULL 0
#endif

#ifndef __SIZE_T_DEF
#define __SIZE_T_DEF
typedef unsigned int size_t;
#endif

typedef int ptrdiff_t;

#ifndef __WCHAR_T__
#define __WCHAR_T__
#ifdef SIGNED_WCHAR
typedef short wchar_t;
#endif // SIGNED_WCHAR
#ifdef UNSIGNED_WCHAR
typedef unsigned short wchar_t;
#endif // UNSIGNED_WCHAR
#endif // __WCHAR_T_DEF

#define offsetof(type, member) ((unsigned)&((type*)0)->member)

#endif
