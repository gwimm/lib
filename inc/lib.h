#ifndef   LIB_H
#define   LIB_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

#define inline inline __attribute__((always_inline))

#define true  1
#define false 0

typedef unsigned long  u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef signed long    s64;
typedef signed int     s32;
typedef signed short   s16;
typedef signed char    s8;

typedef long           i64;
typedef int            i32;
typedef short          i16;
typedef char           i8;

typedef float          f32;
typedef double         f64;
typedef long double    f80;

typedef enum cmp { cmp_lesser = -1, cmp_equal, cmp_greater } cmp_t;
typedef _Bool bool;

typedef enum cmp (*cmp_fun_t)(const void *, const void *);

i8 *env_get(i8 *);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // LIB_H
