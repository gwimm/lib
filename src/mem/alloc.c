#include <alloc.h>
#include <flt.h>
#include <sys.h>

struct flt mem_hep = {0};
void *mem_hep_upp = 0;

inline void mem_alc_ini() {
	mem_hep_upp = (void *)syscall(BRK, 0);
	if ((void *)syscall(BRK, (u64)mem_hep_upp + 2046) == mem_hep_upp + 2046) {
		mem_hep = flt_ini(mem_hep_upp, 2046);
		mem_hep_upp += 2046;
	}
}

void *mem_alc(u64 len) {
	struct flt_obj *flt_obj = 0;
	if (!mem_hep.fst) {
		mem_alc_ini();
	}
	if (!(flt_obj = flt_get(&mem_hep, len))) {
		if ((void *)syscall(BRK, (u64)mem_hep_upp + 2046) == mem_hep_upp + 2046) {
			mem_hep_upp += 2046;
			flt_ext(&mem_hep, 2046);
		}
		if (!(flt_obj = flt_get(&mem_hep, len))) {
			return 0;
		}
	}
	return flt_obj_bin(flt_obj);
}

void *mem_rlc(void *ptr, u64 len) {
	return 0;
}

void mem_dlc(void *ptr) {
	if (ptr && *(void **)ptr) {
		flt_del(&mem_hep, flt_bin_obj(*(void **)ptr));
		*(void **)ptr = 0;
	}
}
