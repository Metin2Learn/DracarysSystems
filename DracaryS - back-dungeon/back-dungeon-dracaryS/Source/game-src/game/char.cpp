# Search in void CHARACTER::Disconnect(const char* c_pszReason)

	if (GetShop())
	{
		GetShop()->RemoveGuest(this);
	}

# Add before

#ifdef __BACK_DUNGEON__
	CHARACTER_MANAGER::Instance().CheckBackDungeon(this, BACK_DUNGEON_SAVE);
#endif

