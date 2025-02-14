# Add like other define in end file

#ifdef __BACK_DUNGEON__
	PyModule_AddIntConstant(poModule, "__BACK_DUNGEON__", 1);
#else
	PyModule_AddIntConstant(poModule, "__BACK_DUNGEON__", 0);
#endif
