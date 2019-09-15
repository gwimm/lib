#include "lib.h"
#include "fs.h"

u64 ini(i32 arc, i8 *arv[]) {
	i8 buf[256];
	struct stream *file = fs_open("src/ini.c", O_RDONLY);
	fs_read(file, (u8 *)buf, 16);
	fmt_print("%s\n", buf);
	return 0;
}
