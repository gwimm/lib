#ifndef   FS_H
#define   FS_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

#include "stream.h"

#define O_RDONLY             0
#define O_WRONLY             1
#define O_RDWR               2

struct file {
	i32 fd;
	u64 buf_len;
	u8 *buf;
};

struct stream *fs_open(i8 *, i32);
u64 fs_write(struct stream *, const u8 *, u64);
u64 fs_read(struct stream *, u8 *, u64);
void fs_close(struct stream **);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // FS_H
