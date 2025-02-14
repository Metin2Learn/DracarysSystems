# Search

	PyModule_AddIntConstant(poModule, "CAMERA_STOP", CPythonApplication::CAMERA_STOP);

# Add after

#ifdef ENABLE_REWARD_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_REWARD_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_REWARD_SYSTEM", 0);
#endif
