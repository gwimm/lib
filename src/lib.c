u64 ini();

asm (
	".global _start;"
"_start:"
	"xorq %rbp, %rbp;"
	"popq %rdi;"
	"movq %rsp, %rsi;"
	"andq $0xfffffffffffffff0, %rsp;"
	"call ini;"
	"movq %rax, %rdi;"
	"movq $60, %rax;"
	"syscall;"
);
