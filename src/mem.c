void mem_cpy(void *dst, const void *src, u64 len) {
        const u8 *s = src;
        u8 *d = dst;
        while (len--) *d++ = *s++;
}

void mem_swp(void *mem1, void *mem2, u64 len) {
        u8 *m1 = mem1, *m2 = mem2;
#ifdef XOR_SWAP
        while (len--) {
		if (*m1 == *m2) continue;
		*m1 ^= *m2;
		*m2 ^= *m1;
		*m1 ^= *m2;
		m1++;
		m2++;
	}
#else
	if (len == 0) return;
	u8 tmp[len];
	for (u64 i = len; i--;)  tmp[i] = m2 [i];
	for (u64 i = len; i--;)  m2 [i] = m1 [i];
	for (u64 i = len; i--;)  m1 [i] = tmp[i];
#endif
}

enum cmp mem_cmp(const void *vl, const void *vr, u64 n) {
        const u8 *l=vl, *r=vr;
        while (n-- && *l++ == *r++);
        return n ? (*l-*r < 0 ? cmp_lesser : cmp_greater) : cmp_equal;
}

typedef cmp_t (*cmp_fun_t)(const void *, const void *);

#if 0
void srt(void *arr, u64 len, u64 siz, cmp_fun_t cmp) {
	char *cur[siz];

	for (u64 i = 1; i < len; i++) {
		u64 j;

		mem_cpy(cur, arr + i * siz, siz);
		for (j = i - 1; j && cmp((i - j) * siz, i * siz) == cmp_greater; j--) {
		}
		mem_cpy(cur - j * siz, cur - (j - 1) * siz, j * siz);
		mem_cpy(cur, arr + i * siz, siz);
	}
}
#endif
