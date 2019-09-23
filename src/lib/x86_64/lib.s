.text
.global _start
.type _start, @function
_start:
	xor %rbp, %rbp
	pop %rdi
	mov %rsp, %rsi
	and $0xfffffffffffffff0, %rsp
	call lib_ini
	mov %rax, %rdi
	mov $60, %rax
	syscall
