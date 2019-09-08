#define SYS_READ    0
#define SYS_WRITE   1
#define SYS_OPEN    2
#define SYS_CLOSE   3
#define SYS_BRK    12
#define SYS_EXIT   60

wrd_t syscall(wrd_t rax, wrd_t rdi, wrd_t rsi, wrd_t rdx) {
        asm volatile ("syscall" : "+a"(rax) : "D"(rdi), "S"(rsi), "d"(rdx));
        return rax;
}
void exit(wrd_t val) {
        (void)syscall(SYS_EXIT, val, 0, 0);
}
void fdc_wrt(unsigned fdc, const char *buf, wrd_t len) {
        (void)syscall(SYS_WRITE, fdc, (wrd_t)buf, len);
}
void *brk(void *brk) {
        return (void *)syscall(SYS_BRK, (wrd_t)brk, 0, 0);
}
