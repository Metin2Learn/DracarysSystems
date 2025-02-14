# Add

#ifdef ENABLE_REWARD_SYSTEM
ACMD(do_update_reward_data);
#endif

# Search

	{ "\n",						NULL,						0,				POS_DEAD,		GM_PLAYER	}

# add before

#ifdef ENABLE_REWARD_SYSTEM
	{ "update_reward_data",	do_update_reward_data,		0,		POS_DEAD,	GM_PLAYER },
#endif