#include <fs.h>
#include <stream.h>
#include <alloc.h>
#include <sys.h>

u64 fs_write(struct stream *file, const u8 *buf, u64 len) {
	return syscall(WRITE, ((struct file *)file->cookie)->fd, (u64)buf, len);
}

u64 fs_read(struct stream *file, u8 *buf, u64 len) {
	return syscall(READ, ((struct file *)file->cookie)->fd, (u64)buf, len);
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
