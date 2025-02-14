# Add in start file

#ifdef RENEWAL_PICKUP_AFFECT
bool IsRealTimeAffect(DWORD affectType)
{
	switch(affectType)
	{
		case AFFECT_PICKUP_ENABLE:
		case AFFECT_PICKUP_DEACTIVE:
			return true;
	}
	return false;
}
#endif

# Search

	ptoc.elem.lDuration = pkAff->lDuration;

# Change

#ifdef RENEWAL_PICKUP_AFFECT
	ptoc.elem.lDuration = IsRealTimeAffect(pkAff->dwType) ? pkAff->lDuration - time(0) : pkAff->lDuration;
#else
	ptoc.elem.lDuration = pkAff->lDuration;
#endif

# Search

			if (IsPC())
				SendAffectRemovePacket(GetDesc(), GetPlayerID(), pkAff->dwType, pkAff->bApplyOn);

# Add after

#ifdef RENEWAL_PICKUP_AFFECT
			if(IsRealTimeAffect(pkAff->dwType))
			{
				++it;
				continue;
			}
#endif


# Search

		if (--pkAff->lDuration <= 0)

# Change

#ifdef RENEWAL_PICKUP_AFFECT
		const int leftTime = IsRealTimeAffect(pkAff->dwType) ? pkAff->lDuration-time(0) : --pkAff->lDuration;
		if (leftTime <= 0)
#else
		if (--pkAff->lDuration <= 0)
#endif

# Search

	pkAff->lDuration = lDuration;

# Change

#ifdef RENEWAL_PICKUP_AFFECT
	pkAff->lDuration = IsRealTimeAffect(dwType) ? time(0)+ lDuration : lDuration;
#else
	pkAff->lDuration = lDuration;
#endif

