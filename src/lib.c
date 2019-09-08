enum cmp { cmp_lss = -1, cmp_eql, cmp_grt };
typedef enum cmp cmp_t;
typedef unsigned long long int wrd_t;
typedef _Bool bool;

#define PAGE_SIZE 4096

#define true  1
#define false 0

#define NULL ((void *)0)

#include "sys.h"
#include "prc_map.h"
#include "str.h"
#include "mem.h"
#include "alc.h"
#include "bst.h"

wrd_t ini();

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
