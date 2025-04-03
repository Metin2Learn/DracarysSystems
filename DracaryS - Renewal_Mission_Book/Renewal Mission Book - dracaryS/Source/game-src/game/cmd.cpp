# Add like other command

#if defined(__MISSION_BOOKS__)
ACMD(do_missionbooks);
#endif

#if defined(__MISSION_BOOKS__)
	{ "mission_books",	do_missionbooks,		0,		POS_DEAD,	GM_PLAYER },
#endif

