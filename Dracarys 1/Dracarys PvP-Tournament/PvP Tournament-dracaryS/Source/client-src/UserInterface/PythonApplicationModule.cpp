# Add like other define in end file

#ifdef ENABLE_PVP_TOURNAMENT
	PyModule_AddIntConstant(poModule, "ENABLE_PVP_TOURNAMENT", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_PVP_TOURNAMENT", 0);
#endif

#ifdef ENABLE_PVP_CAMERA_MODE
	PyModule_AddIntConstant(poModule, "ENABLE_PVP_CAMERA_MODE", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_PVP_CAMERA_MODE", 0);
#endif


