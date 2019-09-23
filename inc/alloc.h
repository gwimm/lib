#ifndef   ALLOC_H
#define   ALLOC_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

#define PAGE_SIZE 4096

#define mem_alc_local __builtin_alloca

void *mem_alc(u64);
void mem_dlc(void *);

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // ALLOC_H
