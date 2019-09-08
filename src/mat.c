float log_flt_fst(float a) {
	union { float f; int x; } u = { a };
	return (u.x - 1064866805) * 8.262958405176314e-8f;
}
