#ifndef _TYPES_
#define _TYPES_
/*
 * used to keep reliance on one os
 */

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64) || defined(_WINDOWS) || defined(__CYGWIN__) && !defined(_WIN32)
#define LLE_WINDOWS
#endif
#if defined(__linux__)
#define LLE_LINUX
#endif
#if defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define LLE_IPHONE_EMULATOR
    #elif TARGET_OS_IPHONE == 1
        #define LLE_IPHONE
    #elif TARGET_OS_MAC == 1
        #define LLE_MAC
    #endif
#endif
#if defined(__sun) && defined(__SVR4)
#error "this is not designed to run on Solaris Enviroments"
#endif
#if defined(BSD)
#error "this is not designed to run on BSD Enviroments"
#endif
#if defined(__QNX__)
#error "this is not designed to run on BSD Enviroments"
#endif

#ifdef _MSC_VER
#include <winapifamily.h>
#ifdef  WINAPI_FAMILY_SYSTEM
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#endif
#else
#include <stdio.h>
#include <stdlib.h>
typedef __UINT64_TYPE__ uint64_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT8_TYPE__ uint8_t;

typedef __INT64_TYPE__ int64_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT16_TYPE__ int16_t;
typedef __INT8_TYPE__ int8_t;
#endif

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef i8 LLEbool;
#define LLEtrue 1;
#define LLEfalse 0;

#define EXIT_ERROR -1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define LOG(logtext)                                \
printf("%s%s\n","Engine and Game Log:",logtext);

#define CHECK_P(result,cause)                       \
if(result == nullptr)                               \
{                                                   \
    printf("%s%s\n\n","LunaLuxEngine internal pointer validation check failed:",cause);  \
    exit(EXIT_FAILURE);                             \
};
#endif