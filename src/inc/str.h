#ifndef   STR_H
#define   STR_H

#include "stdarg.h"
#include "stream.h"

void str_cpy(i8 *, const i8 *);
u64 str_len(const i8 *);

i8 *num_str(i8 *, int);
i64 str_num(const i8 *);

i8 *str_fmt(i8 *, const i8 *, ...);

void chr_print(i8 c);
void str_print(i8 *str);
void fmt_print(const i8 *fmt, ...);
void stream_fmt_print(struct stream *, const i8 *, va_list);

#endif // STR_H
