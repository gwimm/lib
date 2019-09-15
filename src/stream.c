#include "stream.h"
#include "str.h"

inline void
stream_str_write(struct stream *stream, const i8 *str) {
	stream->write(stream, (u8 *)str, str_len(str));
}
