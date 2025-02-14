# Search

	CreateQuestDropItem(pkChr, pkKiller, vec_item, iDeltaPercent, iRandRange);

# add after

#ifdef ENABLE_EVENT_MANAGER
	CHARACTER_MANAGER::Instance().CheckEventForDrop(pkChr, pkKiller, vec_item);
#endif
