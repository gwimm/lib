#include "stream.h"
#include "str.h"

u64 stream_str_write(struct stream *stream, const i8 *str) {
	return str ? stream->write(stream, (u8 *)str, str_len(str)) : 0;
}
