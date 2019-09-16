void mem_move(void *dst, const void *src, u64 len) {
        const u8 *s = src;
        u8 *d = dst;
        while (len--) *d++ = *s++;
}

void mem_swap(void *mem1, void *mem2, u64 len) {
        u8 *m1 = mem1, *m2 = mem2, tmp[len];
	for (u64 i = len; i--;)  {
		tmp[i] = m2 [i];
		m2 [i] = m1 [i];
		m1 [i] = tmp[i];
	}
}

enum cmp mem_cmp(const void *vl, const void *vr, u64 n) {
        const u8 *l=vl, *r=vr;
        while (n-- && *l++ == *r++);
        return n ? (*l-*r < 0 ? cmp_lesser : cmp_greater) : cmp_equal;
}

typedef enum cmp (*cmp_fun_t)(const void *, const void *);

void srt(void *arr, u64 len, u64 siz, cmp_fun_t cmp_fun) {
	char *cur[siz - 1];
	u64 j;
	for (u64 i = 1; i < len; i++) {
		mem_move(cur, arr + i * siz, siz);
		for (j = i - 1; j; j--) {
			enum cmp cmp = cmp_fun(arr + (i - j) * siz, arr + i * siz);
			if (cmp != cmp_greater || j == 0) {
				mem_move(arr + (i - j + 1) * siz, arr + (i - j) * siz, (i - j - 1) * siz);
				mem_move(arr + (i - j) * siz, cur, siz);
				break;
			}
		}
	}
}
