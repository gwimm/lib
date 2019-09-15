#include "prc.h"

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
