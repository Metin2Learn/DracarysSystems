//Hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
ACMD(do_debug_anti_multiple_farm);
#endif

//In dem Struct: struct command_info cmd_info[] = am Ende hinzufügen (vor \n)

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	{ "anti_farm_info",				do_debug_anti_multiple_farm,		0,					POS_DEAD,		GM_PLAYER		},
#endif
