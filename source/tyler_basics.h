/* date = August 16th 2021 7:21 pm */

#ifndef TYLER_BASICS_H
#define TYLER_BASICS_H

#include <stdint.h>
#include <float.h>
#include <math.h>

//~ Primitive types
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef s8  b8;
typedef s16 b16;
typedef s32 b32;
typedef s64 b64;

typedef size_t umw;

typedef float  f32;
typedef double f64;

#define global          static
#define global_constant static const
#define local_persist   static
#define local_constant  static const

#define Minimum(A, B) ((A) > (B) ? (B) : (A))
#define Maximum(A, B) ((A) > (B) ? (A) : (B))
#define ArrayCount(Arr) (sizeof(Arr)/sizeof(*Arr))

#define BEGIN_STRING(X) #X

#define INVALID_CODE_PATH   Assert(0)
#define NOT_IMPLEMENTED_YET Assert(0)

#define U8_MAX  0xff
#define U16_MAX 0xffff
#define U32_MAX 0xffffffff
#define U64_MAX 0xffffffffffffffff

#define S8_MAX  0x7f
#define S16_MAX 0x7fff
#define S32_MAX 0x7fffffff
#define S64_MAX 0x7fffffffffffffff

#define S8_MIN  0x80
#define S16_MIN 0x8000
#define S32_MIN 0x80000000
#define S64_MIN 0x8000000000000000

#define F32_POSITIVE_INFINITY INFINITY 
#define F32_NEGATIVE_INFINITY -INFINITY

#define F64_NAN               0x7FF7FFFFFFFFFFFF 
#define F64_POSITIVE_INFINITY 0x7FF0000000000000 
#define F64_NEGATIVE_INFINITY 0xFFF0000000000000 

#endif //TYLER_BASICS_H
