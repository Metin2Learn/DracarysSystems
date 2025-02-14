//Hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	PyModule_AddIntConstant(poModule, "ENABLE_ANTI_MULTIPLE_FARM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_ANTI_MULTIPLE_FARM", 0);
#endif
