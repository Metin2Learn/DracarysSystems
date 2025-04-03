# Add in module

#ifdef ENABLE_NEW_NAME_ITEM
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_NAME_ITEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_NAME_ITEM", 0);
#endif
#ifdef ENABLE_NEW_PET_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_PET_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_NEW_PET_SYSTEM", 0);
#endif

