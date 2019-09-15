#ifndef   STREAM_H
#define   STREAM_H

struct stream {
        void (*write)(struct stream *, const u8 *, u64);
        void (*read )(struct stream *, u8 *, u64);
        void (*seek )(struct stream *, u64, u64);
        void (*close)(struct stream *);
        void *cookie;
};

#include "stream.c"
#endif // STREAM_H
