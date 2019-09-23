extern u64 ini();
i8 **envv = 0;

u64 lib_ini(u32 ac, i8 **av) {
	for (envv = av; *envv++;);
	return ini(ac, av, envv);
}
