#include "fs.h"
#include "stream.h"
#include "alc.h"

struct file {
	i32 fd;
	u8 *buf;
	u64 buf_len;
};

#define O_RDONLY             00
#define O_WRONLY             01
#define O_RDWR               02

void fs_write(struct stream *file, const u8 *str, u64 len) {
	syscall(WRITE, ((struct file *)file->cookie)->fd, (u64)str, len);
}

void fs_read(struct stream *file, u8 *str, u64 len) {
	syscall(READ, ((struct file *)file->cookie)->fd, (u64)str, len);
}

struct stream *fs_open(i8 *filename, i32 flags) {
	struct stream *file = 0;
	if ((file = mem_alc(sizeof *file + sizeof(struct file)))) {
		file->cookie = file + sizeof file;
		if ((((struct file *)file->cookie)->fd =
				syscall(OPEN, (u64)filename, flags, 0666))) {
			file->write = fs_write;
		} else file = 0;
	}
	return file;
}

void fs_close(struct stream **file) {
	mem_dlc((*file)->cookie);
	mem_dlc(file);
	*file = 0;
}
