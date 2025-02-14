# add

#ifdef RENEWAL_PICKUP_AFFECT
ACMD(do_pickup_affect)
{
	
	CAffect* affect = ch->FindAffect(AFFECT_PICKUP_ENABLE);
	if (!affect)
	{
		affect = ch->FindAffect(AFFECT_PICKUP_DEACTIVE);
		if (!affect)
			return;
	}
	const long duration = affect->lDuration - time(0);
	const bool isActive = affect->dwType == AFFECT_PICKUP_ENABLE;
	ch->RemoveAffect(affect);
	if (duration <= 0)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Affect is removed.");
		return;
	}
	ch->AddAffect(isActive ? AFFECT_PICKUP_DEACTIVE : AFFECT_PICKUP_ENABLE, POINT_NONE, 0, AFF_NONE, duration, 0, 0, false);
}
#endif
