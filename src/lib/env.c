#include <str.h>

extern i8 **envv;

i8 *env_get(i8 *var) {
	u64 len = str_len(var) - 1;
	for (i8 **e = envv; *e; e++)
		if (!str_cmpn(var, *e, len) && (*e)[len] == '=')
			return *e + len + 1;
	return 0;
}
