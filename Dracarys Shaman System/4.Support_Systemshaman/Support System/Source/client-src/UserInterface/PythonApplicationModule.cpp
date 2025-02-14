# Add in module


#ifdef ENABLE_SUPPORT_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_SUPPORT_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_SUPPORT_SYSTEM", 0);
#endif
