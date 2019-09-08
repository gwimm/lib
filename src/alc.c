#include "alc.h"
#include "lst.h"

struct flt mem_hep = {0};
void *mem_hep_upp = NULL;

void *mem_alc(wrd_t len) {
	struct flt_obj *flt_obj = NULL;
	if (!mem_hep.fst) {
		mem_hep_upp = brk(NULL);
		if (brk(mem_hep_upp + 2046) == mem_hep_upp + 2046) {
			mem_hep = flt_ini(mem_hep_upp, 2046);
			mem_hep_upp += 2046;
		} else {
			return NULL;
		}
	}
	if (!(flt_obj = flt_get(&mem_hep, len))) {
		if (brk(mem_hep_upp + 2046) == mem_hep_upp + 2046) {
			mem_hep_upp += 2046;
			flt_ext(&mem_hep, 2046);
		}
		if (!(flt_obj = flt_get(&mem_hep, len))) {
			return NULL;
		}
	}
	return flt_obj_bin(flt_obj);
}

void *mem_rlc(void *ptr, wrd_t len) {
	return NULL;
}

void mem_dlc(void *ptr) {
	if (ptr && *(void **)ptr) {
		flt_del(&mem_hep, flt_bin_obj(*(void **)ptr));
		*(void **)ptr = NULL;
	}
}
