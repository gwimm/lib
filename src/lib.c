#include "lib.h"
#include "sys.h"
#include "prc_map.h"
#include "mem.h"
#include "str.h"
#include "stream.h"
#include "alc.h"
#include "bst.h"

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
