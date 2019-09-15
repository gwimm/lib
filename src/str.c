#include "str.h"
#include "mem.h"
#include "prc_map.h"
#include "stdarg.h"

void str_cpy(i8 *dst, const i8 *src) {
        while ((*dst++ = *src++));
}

u64 str_len(const i8 *buf) {
        const i8 *ptr = buf;
        while (*ptr++);
        return ptr - buf;
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

void chr_print(i8 c)    { syscall(WRITE, 1, (u64)&c, 1); }
void str_print(i8 *str) { syscall(WRITE, 1, (u64)str, str_len(str)); }

#include "stream.h"
#include "fs.h"

void stream_fmt_print(struct stream *stream, const i8 *fmt, va_list ap) {
        for (; *fmt; fmt++) {
		if (*fmt == '%') {
			fmt++;
			u64 len;
			i8 *buf = mem_alc_local(1024);
			switch (*fmt) {
			case 's': {
				buf = va_arg(ap, i8 *);
				len = str_len(buf) - 1;
			} break;
			case 'b': {
				u64 num = va_arg(ap, u64);
				len = sizeof num * 8 + 2;
				mem_cpy(buf, "0b", 2);
				buf += len;
				for (u64 i = 0; i < sizeof num * 8; i++, num >>= 1) {
					*--buf = num & 1 ? '1' : '0';
				}
				buf -= 2;
			} break;
			case 'x': {
				u64 num = va_arg(ap, u64);
				len = sizeof num * 2 + 2;
				mem_cpy(buf, "0x", 2);
				buf += len;
				for (u64 i = 0; i < sizeof num * 2; i++, num >>= 4) {
					*--buf = "0123456789ABCDEF"[num & 0xF];
				}
				buf -= 2;
			} break;
                	case 'i': {
				len = str_len(num_str(buf, va_arg(ap, u64))) - 1;
                	} break;
			}
			stream->write(stream, (u8 *)buf, len);
                } else {
			stream->write(stream, (u8 *)fmt, 1);
		}
        }
}

void str_write(struct stream *buf, const u8 *str, u64 len) {
	mem_cpy(buf->cookie, str, len);
	buf->cookie += len;
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

void fmt_print(const i8 *fmt, ...) {
	struct file file = {
                .fd = 1,
        };

        struct stream stream = {
                .write = fs_write,
                .cookie = &file,
        };

	va_list ap;
	va_start(ap, fmt);
	stream_fmt_print(&stream, fmt, ap);
	va_end(ap);
}
