#ifndef   FS_H
#define   FS_H

#include "stream.h"

#define O_RDONLY             00
#define O_WRONLY             01
#define O_RDWR               02

struct file {
	i32 fd;
	u64 buf_len;
	u8 *buf;
};

void fs_write(struct stream *, const u8 *, u64);
void fs_read(struct stream *, u8 *, u64);
struct stream *fs_open(i8 *, i32);
void fs_close(struct stream **);

#endif // FS_H
