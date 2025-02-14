# Search

	PyModule_AddIntConstant(poModule, "CAMERA_STOP", CPythonApplication::CAMERA_STOP);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	PyModule_AddIntConstant(poModule, "ENABLE_GUILD_REQUEST", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_GUILD_REQUEST", 0);
#endif
