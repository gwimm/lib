#include <str.h>

#include <fs.h>
#include <mem.h>
#include <alloc.h>
#include <sys.h>
#include <stdarg.h>

void chr_print(i8 c)    { syscall(WRITE, 1, (u64)&c, 1); }
void str_print(i8 *str) { syscall(WRITE, 1, (u64)str, str_len(str)); }

i8 chr_read(void) {
	i8 c;
	syscall(READ, 1, (u64)&c, 1);
	return c;
}

i8 *str_read(i8 *str) {
	i8 c;
	u64 i = 0;
	while ((c = chr_read()) != '\0' && c != '\n') str[i++] = c;
	str[i] = '\0';
	if(c != '\n') str = 0;
	return str;

}

u64 stream_write(struct stream *stream, const i8 *str, u64 len) {
	return stream ? stream->write(stream, (void *)str, len) : -1;
}

static i8 *fmt_b(u64 num, i8 *buf) {
	for (; num; num >>= 1) *--buf = num & 1 ? '1' : '0';
	return buf;
}

static i8 *fmt_x(u64 num, i8 *buf) {
	for (; num; num >>= 4) *--buf = "0123456789abcdef"[num & 0x0F];
	return buf;
}

static i8 *fmt_o(u64 num, i8 *buf) {
	for (; num; num >>= 3) *--buf = '0' + (num & 07);
	return buf;
}

static i8 *fmt_d(u64 num, i8 *buf) {
	for (; num; num /= 10) *--buf = '0' + num % 10;
	return buf;
}

u64 stream_fmt_print(struct stream *stream, const i8 *fmt, va_list ap) {
	const i8 *ptr, *off, *pre;
	i8 *end, buf[1024];
	u64 len, ret = 0;

        while (*fmt) {
		len = 0;
		for (ptr = fmt; fmt[0] && fmt[0] != '%'; fmt++);
		for (off = fmt; fmt[0] == '%' && fmt[1] == '%'; fmt += 2, off++);
		if (!(len += stream_write(stream, ptr, off - ptr))) {
 			end = buf + sizeof(buf);
			pre = ptr = 0;
			fmt++;

			union {
				u64 num;
				f64 flt;
				void *ptr;
			} arg;
			arg.num = va_arg(ap, u64);

                	switch (*fmt++) {
                	case 's':
				ptr = arg.ptr ? arg.ptr : "(null)";
				end = (void *)ptr + str_len(ptr);
                		break;
                	case 'b':
				ptr = fmt_b(arg.num, end);
				pre = "0b";
                		break;
                	case 'x':
				ptr = fmt_x(arg.num, end);
				pre = "0x";
                		break;
                	case 'o':
				ptr = fmt_o(arg.num, end);
				pre = "0";
                		break;
                	case 'i':
				ptr = fmt_d(arg.num, end);
                		break;
                	}

                	len += stream_str_write(stream, pre);
                	len += stream_write(stream, ptr, end - ptr);
		}
		ret += len;
        }
	return ret;
}

u64 str_write(struct stream *buf, const u8 *str, u64 len) {
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

u64 fmt_print(const i8 *fmt, ...) {
	u64 ret;

        struct file file = {
                .fd = 1,
        };

        struct stream stream = {
                .write = fs_write,
                .cookie = &file,
        };

        va_list ap;
        va_start(ap, fmt);
        ret = stream_fmt_print(&stream, fmt, ap);
        va_end(ap);

	return ret;
}
