# search

	{ "\n",						NULL,						0,				POS_DEAD,		GM_PLAYER	}

# add before

#ifdef ENABLE_PVP_TOURNAMENT
	{ "pvp_duel",	do_pvp_duel,		0,		POS_DEAD,	GM_IMPLEMENTOR },
#endif
#ifdef ENABLE_PVP_CAMERA_MODE
	{ "camera_mode",	do_camera_mode,		0,		POS_DEAD,	GM_PLAYER },
#endif

# Add

#ifdef ENABLE_PVP_CAMERA_MODE
ACMD(do_camera_mode);
#endif

#ifdef ENABLE_PVP_TOURNAMENT
ACMD(do_pvp_duel);
#endif
