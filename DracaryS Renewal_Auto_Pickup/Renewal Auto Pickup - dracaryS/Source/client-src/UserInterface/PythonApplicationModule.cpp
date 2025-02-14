# add end file like other define

#ifdef RENEWAL_PICKUP_AFFECT
	PyModule_AddIntConstant(poModule, "RENEWAL_PICKUP_AFFECT", 1);
#else
	PyModule_AddIntConstant(poModule, "RENEWAL_PICKUP_AFFECT", 0);
#endif
