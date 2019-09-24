#ifndef   IO_H
#define   IO_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

#include <fs.h>

u64 chr_print(i8 c);
u64 str_print(i8 *str);

i8 chr_read(void);
i8 *str_read(i8 *);

u64 fmt_print(const i8 *fmt, ...);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // IO_H
