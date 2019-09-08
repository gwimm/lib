void mem_cpy(void *dst, const void *src, wrd_t len) {
        const unsigned char *s = src;
        unsigned char *d = dst;
        while (len--) *d++ = *s++;
}

void mem_swp(void *mem1, void *mem2, wrd_t len) {
        unsigned char *m1 = mem1, *m2 = mem2;
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
	unsigned char tmp[len];
	for (wrd_t i = len; i--;)  tmp[i] = m2 [i];
	for (wrd_t i = len; i--;)  m2 [i] = m1 [i];
	for (wrd_t i = len; i--;)  m1 [i] = tmp[i];
#endif
}

cmp_t mem_cmp(const void *vl, const void *vr, wrd_t n) {
        const unsigned char *l=vl, *r=vr;
        while (n-- && *l++ == *r++);
        return n ? (*l-*r < 0 ? cmp_lss : cmp_grt) : cmp_eql;
}

typedef cmp_t (*cmp_fun_t)(const void *, const void *);

void srt(void *src, wrd_t nel, wrd_t len, cmp_fun_t cmp) {

}
