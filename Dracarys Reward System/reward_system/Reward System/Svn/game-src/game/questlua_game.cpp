# Search

	void RegisterGameFunctionTable()

# Add before

#ifdef ENABLE_REWARD_SYSTEM
	int game_set_reward(lua_State* L)
	{
		CQuestManager& qMgr = CQuestManager::instance();
		LPCHARACTER pkChar = qMgr.GetCurrentCharacterPtr();
		if (pkChar)
		{
			if (!lua_isnumber(L, 1))
				return 0;
			CHARACTER_MANAGER::instance().SetRewardData(lua_tonumber(L, 1), pkChar->GetName(), true);
		}
		return 0;
	}
#endif

# Search

	{ NULL,					NULL				}

# add after

#ifdef ENABLE_REWARD_SYSTEM
			{ "set_reward",		game_set_reward			},
#endif

