#include "alc.h"

struct vec {
	void *buf;
	u64 siz, len;
};

struct vec *vec_alc(u64 siz, u64 len) {
	struct vec *vec = mem_alc(sizeof(struct vec));
	vec->buf = mem_alc((vec->len = len) * (vec->siz = siz));
	return vec;
}

void vec_dlc(struct vec **vec) {
	mem_dlc(&(*vec)->buf)
	mem_dlc(vec)
}

void *vec_get(struct vec *vec, u64 idx) {
	return idx < len ? vec->buf + idx * vec->siz : 0;
}
