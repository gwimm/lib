#include <sys.h>

u64 exec(const i8 *path, i8 *const av[], i8 *const env[]) {
	return syscall(EXECVE, (u64)path, (u64)av, (u64)env);
}

u64 fork() {
	return syscall(FORK);
}
