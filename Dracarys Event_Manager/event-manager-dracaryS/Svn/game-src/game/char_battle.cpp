# Search

	if (pkAttacker->GetPoint(POINT_MALL_GOLDBONUS))
		iGoldPercent += (iGoldPercent * pkAttacker->GetPoint(POINT_MALL_GOLDBONUS) / 100);

# Add before

#ifdef ENABLE_EVENT_MANAGER
	if (pkAttacker->IsPC())
	{
		const auto event = CHARACTER_MANAGER::Instance().CheckEventIsActive(YANG_DROP_EVENT, pkAttacker->GetEmpire());
		if(event != 0)
			iGoldPercent = iGoldPercent * (100 + event->value[0]) / 100;
	}
#endif

# Search

	int iBaseExp = iExp;

# Add before

#ifdef ENABLE_EVENT_MANAGER
	const auto event = CHARACTER_MANAGER::Instance().CheckEventIsActive(EXP_EVENT, to->GetEmpire());
	if(event != 0)
		iExp = iExp * (100 + event->value[0]) / 100;
#endif

