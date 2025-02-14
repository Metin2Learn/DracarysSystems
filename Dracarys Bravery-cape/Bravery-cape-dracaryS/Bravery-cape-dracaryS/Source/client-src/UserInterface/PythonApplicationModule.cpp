# add like other define in end file

#ifdef __RENEWAL_BRAVE_CAPE__
	PyModule_AddIntConstant(poModule, "__RENEWAL_BRAVE_CAPE__", 1);
#else
	PyModule_AddIntConstant(poModule, "__RENEWAL_BRAVE_CAPE__", 0);
#endif

