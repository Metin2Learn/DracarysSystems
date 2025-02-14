# Add

#ifdef __BACK_DUNGEON__
bool CHARACTER_MANAGER::CheckBackDungeon(LPCHARACTER ch, BYTE checkType, DWORD mapIdx)
{
	if (!ch && checkType != BACK_DUNGEON_REMOVE)
		return false;

	// std::map<DWORD, std::map<std::pair<DWORD, WORD>, std::vector<DWORD>>> m_mapbackDungeon;

	if (checkType == BACK_DUNGEON_SAVE)
	{
		const DWORD dungeonIdx = ch->GetMapIndex();
		if (dungeonIdx < 10000)
			return false;
		LPDUNGEON dungeon = CDungeonManager::Instance().FindByMapIndex(dungeonIdx);
		if (!dungeon)
			return false;
		if (dungeon->GetFlag("can_back_dungeon") != 1)
			return false;
		const DWORD mapIdx = dungeonIdx / 10000;
		auto it = m_mapbackDungeon.find(mapIdx);
		if (it == m_mapbackDungeon.end())
		{
			std::map<std::pair<DWORD, WORD>, std::vector<DWORD>> m_mapList;
			m_mapbackDungeon.emplace(mapIdx, m_mapList);
			it = m_mapbackDungeon.find(mapIdx);
		}
		auto itDungeon = it->second.find(std::make_pair(dungeonIdx, mother_port));
		if (itDungeon == it->second.end())
		{
			std::vector<DWORD> m_pidList;
			it->second.emplace(std::make_pair(dungeonIdx, mother_port), m_pidList);
			itDungeon = it->second.find(std::make_pair(dungeonIdx, mother_port));
		}
		if(std::find(itDungeon->second.begin(), itDungeon->second.end(),ch->GetPlayerID()) == itDungeon->second.end())
			itDungeon->second.emplace_back(ch->GetPlayerID());
	}
	else if (checkType == BACK_DUNGEON_REMOVE)
	{
		if (mapIdx < 10000)
			return false;

		auto it = m_mapbackDungeon.find(mapIdx / 10000);
		if (it != m_mapbackDungeon.end())
		{
			for (auto& [dungeonData, playerList] : it->second)
			{
				if (mapIdx == dungeonData.first)
				{
					it->second.erase(dungeonData);
					return true;
				}
			}
		}
	}
	else if (checkType == BACK_DUNGEON_CHECK || checkType == BACK_DUNGEON_WARP)
	{
		const DWORD curretMapIdx = ch->GetMapIndex();
		if (curretMapIdx > 10000)
			return false;

		const std::map<DWORD, std::vector<DWORD>> m_baseToDungeonIdx = {
			{
				65, // baseMapidx
				{
					66,//devil-tower
				},
			}
		};

		const auto itBase = m_baseToDungeonIdx.find(curretMapIdx);
		if (itBase != m_baseToDungeonIdx.end())
		{
			for (const auto& dungeonIdx : itBase->second)
			{
				auto it = m_mapbackDungeon.find(dungeonIdx);
				if (it != m_mapbackDungeon.end())
				{
					for (auto& [dungeonData, playerList] : it->second)
					{
						LPDUNGEON dungeon = CDungeonManager::Instance().FindByMapIndex(dungeonData.first);
						if (std::find(playerList.begin(), playerList.end(), ch->GetPlayerID()) == playerList.end())
							continue;
						else if (!dungeon)
							continue;
						else if (dungeon->GetFlag("can_back_dungeon") != 1)
							continue;
						if (checkType == BACK_DUNGEON_WARP)
						{
							if (mapIdx == dungeonData.first)
							{
								ch->WarpSet(dungeon->GetFlag("LAST_X"), dungeon->GetFlag("LAST_Y"), dungeonData.first);
								return true;
							}
						}
						else
							ch->ChatPacket(CHAT_TYPE_COMMAND, "ReJoinDungeonDialog %d", dungeonData.first);
					}
				}
			}
		}
	}
	return false;
}
#endif
