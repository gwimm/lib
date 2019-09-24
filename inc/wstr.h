#ifndef   WSTR_H
#define   WSTR_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

i32 *wstr_cpy(i32 *, const i32 *);

i32 wstr_cmp(const i32 *, const i32 *);
i32 wstr_cmpn(const i32 *, const i32 *, u64);

u64 wstr_len(const i32 *);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // WSTR_H
