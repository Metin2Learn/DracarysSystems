# Search

	CreateQuestDropItem(pkChr, pkKiller, vec_item, iDeltaPercent, iRandRange);

# add after

#ifdef ENABLE_EVENT_MANAGER
	CHARACTER_MANAGER::Instance().CheckEventForDrop(pkChr, pkKiller, vec_item);
#endif


# Search

	iRandRange = iRandRange * 100 / 
		(100 + 
		 CPrivManager::instance().GetPriv(pkKiller, PRIV_ITEM_DROP) + 
		 pkKiller->IsEquipUniqueItem(UNIQUE_ITEM_DOUBLE_ITEM)?100:0);

# Change


#ifdef ENABLE_EVENT_MANAGER
	int extraDrop = extraDrop+=CPrivManager::instance().GetPriv(pkKiller, PRIV_ITEM_DROP)+(pkKiller->IsEquipUniqueItem(UNIQUE_ITEM_DOUBLE_ITEM) ? 100 : 0);
	const auto event = CHARACTER_MANAGER::Instance().CheckEventIsActive(ITEM_DROP_EVENT, pkKiller->GetEmpire());
	if(event != 0)
		extraDrop += event->value[0];
	iRandRange = iRandRange * 100 / (100+extraDrop);
#else
	iRandRange = iRandRange * 100 / 
		(100 + 
		 CPrivManager::instance().GetPriv(pkKiller, PRIV_ITEM_DROP) + 
		 pkKiller->IsEquipUniqueItem(UNIQUE_ITEM_DOUBLE_ITEM)?100:0);
#endif
