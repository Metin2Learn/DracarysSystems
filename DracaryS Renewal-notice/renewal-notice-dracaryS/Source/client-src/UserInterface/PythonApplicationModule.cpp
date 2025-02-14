# Add like other define in endfile

#ifdef __RENEWAL_NOTICE__
	PyModule_AddIntConstant(poModule, "__RENEWAL_NOTICE__", 1);
#else
	PyModule_AddIntConstant(poModule, "__RENEWAL_NOTICE__", 0);
#endif
