# Search

				if (item->CheckItemUseLevel(ch->GetLevel()) == true)

# add before

#ifdef ENABLE_PVP_TOURNAMENT
				if(isPvPDuelMap)
				{
					if(CPvPDuel::Instance().IsBlockItem(item, true))
					{
						v.push_back(item);
						continue;
					}
				}
#endif

# Search

	std::vector<LPITEM> v;

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	bool isPvPDuelMap = ch->GetMapIndex() == PVP_DUEL_MAP_INDEX;
#endif

# Search

	signal_timer_enable(30);

#ifdef ENABLE_PVP_TOURNAMENT
	if(g_bChannel == 99)
		quest::CQuestManager::instance().RequestSetEventFlag("pvp_duel_active", 0);
#endif