# Search

	if (DragonSoul_IsDeckActivated())

# add before

#ifdef ENABLE_EVENT_MANAGER
		CHARACTER_MANAGER::Instance().CheckBonusEvent(this);
#endif

