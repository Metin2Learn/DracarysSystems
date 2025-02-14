//In der Funktion: LPCHARACTER CParty::GetNextOwnership(LPCHARACTER ch, long x, long y)
//while-statement einfach austauschen (falls keine weiteren Defines)

	while (size-- > 0)
	{
		LPCHARACTER pkMember = m_itNextOwner->second.pCharacter;

		if (pkMember && DISTANCE_APPROX(pkMember->GetX() - x, pkMember->GetY() - y) < 3000)
		{
			IncreaseOwnership();

#ifdef ENABLE_ANTI_MULTIPLE_FARM
			if (pkMember->IsPC() && !pkMember->HasBlockedDrops())
				return pkMember;
#else
			return pkMember;
#endif
		}

		IncreaseOwnership();
	}
