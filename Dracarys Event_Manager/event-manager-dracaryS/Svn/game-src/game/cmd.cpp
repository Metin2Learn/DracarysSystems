# Add

#ifdef ENABLE_EVENT_MANAGER
ACMD(do_event_manager);
#endif

# Search

{ "\n",						NULL,						0,				POS_DEAD,		GM_PLAYER	}

# add before

#ifdef ENABLE_EVENT_MANAGER
	{ "event_manager",	do_event_manager,		0,		POS_DEAD,	GM_PLAYER },
#endif

