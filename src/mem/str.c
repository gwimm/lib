#include <mem.h>
#include <str.h>
#include <wstr.h>

i8 *str_cpy(i8 *dst, const i8 *src) {
        while ((*dst++ = *src++));
	return dst;
}

i8 str_cmp(const i8 *l, const i8 *r) {
        for (; *l == *r && *l; l++, r++);
        return *l - *r;
}

i8 str_cmpn(const i8 *l, const i8 *r, u64 n) {
	if (n--) {
        	for (; *l == *r && *l && n; l++, r++, n--);
        	return *l - *r;
	}
	return 0;
}

u64 str_len(const i8 *str) {
        const i8 *end;
        for (end = str; *end; end++);
        return end - str;
}

i8 *str_cat(i8 *dst, const i8 *src) {
	return str_cpy(dst + str_len(dst), src);
}

i8 *num_str(i8 *buf, int num) {
	u64 len = 0;
	if (num) {
		for (u64 i = num; i; i /= 10) len++;
		buf[len] = '\0';
		for (; len--; num /= 10) buf[len] = '0' + num % 10;
	} else str_cpy(buf, "0");
	return buf;
}

i64 str_num(const i8 *str) {
	u64 num = 0;
	bool neg = false;
        while (*str == ' ') str++;
        switch (*str) {
        case '-': neg = true;
        case '+': str++;
        }
        while (*str) num = 10 * num - (*str++ - '0');
	return neg ? num : -num;
}

static u64 str_write(struct stream *buf, const u8 *str, u64 len) {
        mem_move(buf->cookie, str, str[len - 1] ? len : --len);
        buf->cookie += len;
	return len;
}

i8 *str_fmt(i8 *buf, const i8 *fmt, ...) {
        struct stream stream = {
                .write = str_write,
                .cookie = buf,
        };

        va_list ap;
        va_start(ap, fmt);
        stream_fmt_print(&stream, fmt, ap);
        va_end(ap);

        return buf;
}

u64 wstr_len(const i32 *str) {
	const i32 *end;
	for (end = str; *end; end++);
	return end - str;
}
