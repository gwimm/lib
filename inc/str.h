#ifndef   STR_H
#define   STR_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdarg.h>
#include <stream.h>

i8 *str_cpy(i8 *, const i8 *);

i8 str_cmp(const i8 *, const i8 *);
i8 str_cmpn(const i8 *, const i8 *, u64);

u64 str_len(const i8 *);

i8 *num_str(i8 *, int);
i64 str_num(const i8 *);

i8 *str_fmt(i8 *, const i8 *, ...);
u64 stream_fmt_print(struct stream *, const i8 *, va_list);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // STR_H
