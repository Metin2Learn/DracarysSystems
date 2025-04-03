# Add

#ifdef ENABLE_NEW_PET_SYSTEM
ACMD(do_pet_egg);
ACMD(do_pet_evolve);
ACMD(do_pet_add_slot);
#endif

# Search

	{ "\n",						NULL,						0,				POS_DEAD,		GM_PLAYER	}

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
	{ "pet_egg",	do_pet_egg,		0,		POS_DEAD,	GM_PLAYER },
	{ "pet_evolve",	do_pet_evolve,		0,		POS_DEAD,	GM_PLAYER },
	{ "pet_add_slot",	do_pet_add_slot,		0,		POS_DEAD,	GM_PLAYER },
#endif

