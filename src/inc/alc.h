#ifndef   ALC_H
#define   ALC_H

#define PAGE_SIZE 4096

#define mem_alc_local __builtin_alloca

void *mem_alc(u64);
void mem_dlc(void *);

#endif // ALC_H
