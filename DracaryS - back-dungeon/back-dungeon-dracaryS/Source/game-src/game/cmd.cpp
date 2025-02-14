# Add like other command

#ifdef __BACK_DUNGEON__
ACMD(do_back_dungeon);
#endif

#ifdef __BACK_DUNGEON__
	{ "back_dungeon",	do_back_dungeon,		0,		POS_DEAD,	GM_PLAYER },
#endif