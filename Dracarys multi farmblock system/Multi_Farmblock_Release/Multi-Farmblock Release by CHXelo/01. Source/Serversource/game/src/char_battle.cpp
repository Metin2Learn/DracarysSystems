//In der Funktion: void CHARACTER::Reward(bool bItemDrop) hinzufügen
//unter dem Call:
//	if (!bItemDrop)
//		return;

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	if (pkAttacker->IsPC() && pkAttacker->HasBlockedDrops())
		return;
#endif
