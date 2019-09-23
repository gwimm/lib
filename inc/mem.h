#ifndef   MEM_H
#define   MEM_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum cmp (*cmp_fun_t)(const void *, const void *);

void *mem_move(void *, const void *, u64);
void mem_swap(void *, void *, u64);
void *mem_set(void *, u8, u64);
enum cmp mem_cmp(const void *, const void *, u64);
void srt(void *, u64, u64, cmp_fun_t);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // MEM_H
