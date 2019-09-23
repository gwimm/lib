#ifndef   STREAM_H
#define   STREAM_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

struct stream {
        u64 (*write)(struct stream *, const u8 *, u64);
        u64 (*read)(struct stream *, u8 *, u64);
        u64 (*seek)(struct stream *, u64);
        void (*close)(struct stream *);
        void *cookie;
};

u64 stream_str_write(struct stream *stream, const i8 *str);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // STREAM_H
