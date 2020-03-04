#ifndef _TYPES_
#define _TYPES_
/*
 * used to keep reliance on one os
 */
#ifdef _MSC_VER
#include <winapifamily.h>
#ifdef  WINAPI_FAMILY_SYSTEM
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define UWP
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
#define UNIX
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

#define CHECK_N(result,cause)                       \
if(result != 0)                                     \
{                                                   \
    printf("%s%s\n","LunaLuxEngine internal number type 1 validation check failed:",cause);  \
    exit(EXIT_FAILURE);                             \
};

#define CHECK_N2(result,cause)                       \
if(result == 0)                                     \
{                                                   \
    printf("%s%s\n","LunaLuxEngine internal number type 2 validation check failed:",cause);  \
    exit(EXIT_FAILURE);                             \
};

#define CHECK_B(result,cause)                       \
if(result != true)                                  \
{                                                   \
    printf("%s%s\n","LunaLuxEngine internal LLEbool validation check failed:",cause);  \
    exit(EXIT_FAILURE);                             \
};

#define CHECK_P(result,cause)                       \
if(result == nullptr)                               \
{                                                   \
    printf("%s%s\n","LunaLuxEngine internal pointer validation check failed:",cause);  \
    exit(EXIT_FAILURE);                             \
};

#define FOURCE_STOP(msg) \
{\
LOG(msg)\
exit(EXIT_ERROR);\
}
#endif