#include "str.h"
#include "prc_map.h"
#include "stdarg.h"

void str_cpy(char *dst, const char *src) {
        while ((*dst++ = *src++));
}

wrd_t str_len(const char *buf) {
        const char *ptr = buf;
        while (*ptr++);
        return ptr - buf;
}

char *num_str(char *buf, int num) {
	wrd_t len = 0;
	if (num) {
		for (wrd_t i = num; i; i /= 10) len++;
		buf[len] = '\0';
		for (; len--; num /= 10) buf[len] = '0' + num % 10;
	} else str_cpy(buf, "0");
	return buf;
}

wrd_t str_num(char *str) {
	wrd_t num = 0;
	bool neg = false;
        while (*str == ' ') str++;
        switch (*str) {
        case '-': neg = true;
        case '+': str++;
        }
        while (*str) num = 10 * num - (*str++ - '0');
	return neg ? num : -num;
}

void chr_prt(char c)    { fdc_wrt(1, &c, 1); }
void str_prt(char *str) { fdc_wrt(1, str, str_len(str)); }

void fmt_prt(const char *fmt, ...) {
	char buf[1024];
	va_list ap;
	va_start(ap, fmt);
        for (; *fmt; fmt++) {
		if (*fmt == '%') switch (*(++fmt)) {
		case 's': {
			str_prt(va_arg(ap, char *));
		} continue;
		case 'b': {
			unsigned char *ptr = va_arg(ap, unsigned char *);
			wrd_t len = va_arg(ap, wrd_t);
			for (wrd_t j = 0; j < len; j++) {
				unsigned char val = ptr[j];
				for (wrd_t i = 0; i < 8; i++, val >>= 1) {
					chr_prt(val & 1 ? '1' : '0');
				}
			}
                } continue;
		case 'x': {
			wrd_t num = va_arg(ap, wrd_t);
			for (wrd_t i = 0; i < sizeof(wrd_t); i++) {
				for (wrd_t j = 0; j < 2; j++) {
					chr_prt("0123456789abcdef"[num & 15 << j]);
				}
			}
		} continue;
                case 'i': {
			str_prt(num_str(buf, va_arg(ap, wrd_t)));
                } continue;
                }
		chr_prt(*fmt);
        }
	va_end(ap);
}
