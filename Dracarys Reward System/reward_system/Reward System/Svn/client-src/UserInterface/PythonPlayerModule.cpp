# Search

	PyModule_AddIntConstant(poModule, "DS_SUB_HEADER_DO_REFINE", DS_SUB_HEADER_DO_REFINE);

#Add after

#ifdef ENABLE_REWARD_SYSTEM
	PyModule_AddIntConstant(poModule, "REWARD_115", REWARD_115);
	PyModule_AddIntConstant(poModule, "REWARD_PET_115", REWARD_PET_115);
	PyModule_AddIntConstant(poModule, "REWARD_120", REWARD_120);
	PyModule_AddIntConstant(poModule, "REWARD_LEGENDARY_SKILL", REWARD_LEGENDARY_SKILL);
	PyModule_AddIntConstant(poModule, "REWARD_LEGENDARY_SKILL_SET", REWARD_LEGENDARY_SKILL_SET);
	PyModule_AddIntConstant(poModule, "REWARD_THANDRUIL", REWARD_THANDRUIL);
	PyModule_AddIntConstant(poModule, "REWARD_HYDRA", REWARD_HYDRA);
	PyModule_AddIntConstant(poModule, "REWARD_CRYSTAL_DRAGON", REWARD_CRYSTAL_DRAGON);
	PyModule_AddIntConstant(poModule, "REWARD_OFFLINESHOP_SLOT", REWARD_OFFLINESHOP_SLOT);
	PyModule_AddIntConstant(poModule, "REWARD_INVENTORY_SLOT", REWARD_INVENTORY_SLOT);
	PyModule_AddIntConstant(poModule, "REWARD_AVERAGE", REWARD_AVERAGE);
	PyModule_AddIntConstant(poModule, "REWARD_ELEMENT", REWARD_ELEMENT);
	PyModule_AddIntConstant(poModule, "REWARD_BATTLEPASS", REWARD_BATTLEPASS);
	PyModule_AddIntConstant(poModule, "REWARD_CUSTOM_SASH", REWARD_CUSTOM_SASH);
	PyModule_AddIntConstant(poModule, "REWARD_AURA", REWARD_AURA);
	PyModule_AddIntConstant(poModule, "REWARD_ENERGY", REWARD_ENERGY);
	PyModule_AddIntConstant(poModule, "REWARD_112_BIO", REWARD_112_BIO);
	PyModule_AddIntConstant(poModule, "REWARD_120_BIO", REWARD_120_BIO);
	PyModule_AddIntConstant(poModule, "REWARD_LEADER_SHIP", REWARD_LEADER_SHIP);
	PyModule_AddIntConstant(poModule, "REWARD_BUFFI_LEGENDARY_SKILL", REWARD_BUFFI_LEGENDARY_SKILL);
	PyModule_AddIntConstant(poModule, "REWARD_MAX", REWARD_MAX);
#endif
