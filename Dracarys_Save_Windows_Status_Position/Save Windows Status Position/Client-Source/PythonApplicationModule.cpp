

#ifdef ENABLE_SAVE_LAST_WINDOW_POSITION
	PyModule_AddIntConstant(poModule, "ENABLE_SAVE_LAST_WINDOW_POSITION", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_SAVE_LAST_WINDOW_POSITION", 0);
#endif