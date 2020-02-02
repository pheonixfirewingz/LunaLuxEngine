#ifndef _TYPES_
#define _TYPES_

#ifndef WIN32
typedef __UINT64_TYPE__ uint64_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT8_TYPE__ uint8_t;

typedef __INT64_TYPE__ int64_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT16_TYPE__ int16_t;
typedef __INT8_TYPE__ int8_t;
#else
#include <stdint.h>
#endif // WIN32

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
#endif