#include "lib.h"
#include "fs.h"
#include "str.h"
#include "mem.h"

u64 ini(i32 arc, i8 *arv[]) {
	// i8 buf[256];
	// struct stream *file = fs_open("src/ini.c", O_RDONLY);
	// fs_read(file, (u8 *)buf, 16);
	// fmt_print("%s\n", buf);
	u32 nums[] = { 3, 1, 3, 2, 4, 5};
	for (u64 i = 0; i < 6; i++) fmt_print("%i", nums[i]);
	for_each (n : nums) fmt_print("%i", n);
	fmt_print("\n");
	for (u64 i = 0; i < 6; i++) fmt_print("%i", nums[i]);
	fmt_print("\n");
	return 0;
}
