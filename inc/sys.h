#ifndef   SYS_H
#define   SYS_H
#ifdef    __cplusplus
extern "C" {
#endif // __cplusplus

#include "prc/prc.h"
#include "syscall.h"

#define __SYS_IND(n) PRC_CAT(__syscall, n)
#define __SYS_CAST(x) ((u64)(x))
#define syscall(...) __SYS_IND(PRC_NUM_ARG(__VA_ARGS__))(SYS_ ## __VA_ARGS__)

inline u64 __syscall0(u64 rax) {
        asm volatile (
	"syscall"
	: "+a" (rax)
	:
	: "rcx", "r11", "memory"
	);
	return rax;
}

inline u64 __syscall1(u64 rax, u64 rdi) {
        asm volatile (
	"syscall"
	: "+a"(rax)
	: "D" (rdi)
	: "rcx", "r11", "memory"
	);
	return rax;
}

inline u64 __syscall2(u64 rax, u64 rdi, u64 rsi) {
        asm volatile (
	"syscall"
	: "+a"(rax)
	: "D" (rdi), "S" (rsi)
	: "rcx", "r11", "memory"
	);
	return rax;
}

inline u64 __syscall3(u64 rax, u64 rdi, u64 rsi, u64 rdx) {
        asm volatile (
	"syscall"
	: "+a"(rax)
	: "D" (rdi), "S" (rsi), "d" (rdx)
	: "rcx", "r11", "memory"
	);
	return rax;
}

#ifdef    __cplusplus
}
#endif // __cplusplus
#endif // SYS_H
