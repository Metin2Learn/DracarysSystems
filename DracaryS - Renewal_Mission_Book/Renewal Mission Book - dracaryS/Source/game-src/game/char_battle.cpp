# Search

	bool isAgreedPVP = false;

# Add before

#if defined(__MISSION_BOOKS__)
	if (pkKiller)
	{
		if (IsStone())
			pkKiller->SetMissionBook(MISSION_BOOK_TYPE_METINSTONE, 1, GetRaceNum(), GetLevel());
		else if (!IsPC())
			pkKiller->SetMissionBook(GetMobRank() >= MOB_RANK_KING ? MISSION_BOOK_TYPE_BOSS : MISSION_BOOK_TYPE_MONSTER, 1, GetRaceNum(), GetLevel());
	}
#endif
