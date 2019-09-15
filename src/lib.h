#ifndef   LIB_H
#define   LIB_H

#define inline inline __attribute__((always_inline))

#define true  1
#define false 0

typedef unsigned long  u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef long           i64;
typedef int            i32;
typedef short          i16;
typedef char           i8;

typedef enum cmp { cmp_lesser = -1, cmp_equal, cmp_greater } cmp_t;
typedef _Bool bool;

#include "lib.c"
#endif // LIB_H
