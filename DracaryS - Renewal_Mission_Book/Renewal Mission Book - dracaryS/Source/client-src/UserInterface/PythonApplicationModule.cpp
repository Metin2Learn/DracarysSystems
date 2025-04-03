# add in end file like other define

#if defined(RENEWAL_MISSION_BOOKS)
	PyModule_AddIntConstant(poModule, "RENEWAL_MISSION_BOOKS", 1);
#else
	PyModule_AddIntConstant(poModule, "RENEWAL_MISSION_BOOKS", 0);
#endif
