# Search

	PyModule_AddIntConstant(poModule, "ENERGY", POINT_ENERGY);

# Add after

#ifdef ENABLE_EVENT_MANAGER
	PyModule_AddIntConstant(poModule, "EVENT_NONE", EVENT_NONE);
	PyModule_AddIntConstant(poModule, "BONUS_EVENT", BONUS_EVENT);
	PyModule_AddIntConstant(poModule, "DOUBLE_BOSS_LOOT_EVENT", DOUBLE_BOSS_LOOT_EVENT);
	PyModule_AddIntConstant(poModule, "DOUBLE_METIN_LOOT_EVENT", DOUBLE_METIN_LOOT_EVENT);
	PyModule_AddIntConstant(poModule, "DOUBLE_MISSION_BOOK_EVENT", DOUBLE_MISSION_BOOK_EVENT);
	PyModule_AddIntConstant(poModule, "DUNGEON_COOLDOWN_EVENT", DUNGEON_COOLDOWN_EVENT);
	PyModule_AddIntConstant(poModule, "DUNGEON_TICKET_LOOT_EVENT", DUNGEON_TICKET_LOOT_EVENT);
	PyModule_AddIntConstant(poModule, "EMPIRE_WAR_EVENT", EMPIRE_WAR_EVENT);
	PyModule_AddIntConstant(poModule, "MOONLIGHT_EVENT", MOONLIGHT_EVENT);
	PyModule_AddIntConstant(poModule, "TOURNAMENT_EVENT", TOURNAMENT_EVENT);
	PyModule_AddIntConstant(poModule, "WHELL_OF_FORTUNE_EVENT", WHELL_OF_FORTUNE_EVENT);
	PyModule_AddIntConstant(poModule, "HALLOWEEN_EVENT", HALLOWEEN_EVENT);
	PyModule_AddIntConstant(poModule, "NPC_SEARCH_EVENT", NPC_SEARCH_EVENT);
#endif