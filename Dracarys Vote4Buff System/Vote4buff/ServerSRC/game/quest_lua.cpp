       //OptimistAdam\\
////---www.metin2hub.com---\\\


//search
	void RegisterPCFunctionTable()

//add above
#ifdef ENABLE_VOTE_FOR_BONUS
	ALUA(pc_can_get_bonus_vote) {
		int32_t ret = 0;

		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (ch) {
			if (!ch->FindAffect(AFFECT_VOTEFORBONUS)) {
				LPDESC d = ch->GetDesc();
				if (d) {
					std::unique_ptr<SQLMsg> msg(DBManager::instance().DirectQuery("SELECT UNIX_TIMESTAMP(vote_time)-UNIX_TIMESTAMP(NOW()) FROM account.account WHERE id=%u", d->GetAccountTable().id));
					if (msg->Get()->uiNumRows > 0) {
						MYSQL_ROW row = mysql_fetch_row(msg->Get()->pSQLResult);
						int32_t expire = atoi(row[0]);
						if (expire > 0)
						{
							ret = 3;
						}
						else
						{
							ret = 2;
						}
					}
					else
					{
						ret = 2;
					}
				}
			}
			else
			{
				ret = 1;
			}
		}

		lua_pushnumber(L, ret);
		return 1;
	}

	ALUA(pc_set_bonus_for_vote) {
		int32_t ret = 0;
		if (lua_isnumber(L, 1)) {
			int32_t type = (int32_t)lua_tonumber(L, 1);
			if (type >= 1 && type <= 3) {
				LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
				if (ch) {
					if (!ch->FindAffect(AFFECT_VOTEFORBONUS))
					{
						switch (type)
						{
							case 1:
								{
									ch->AddAffect(AFFECT_VOTEFORBONUS, POINT_ATTBONUS_MONSTER, 10, AFF_NONE, get_global_time() + 86400, 0, false);
									ret = 2;
								}
								break;
							case 2:
								{
									ch->AddAffect(AFFECT_VOTEFORBONUS, POINT_EXP_DOUBLE_BONUS, 20, AFF_NONE, get_global_time() + 86400, 0, false);
									ret = 3;
								}
								break;
							case 3:
								{
									ch->AddAffect(AFFECT_VOTEFORBONUS, POINT_DOUBLE_DROP_ITEM, 20, AFF_NONE, get_global_time() + 86400, 0, false);
									ret = 4;
								}
								break;
							default:
								{
									ret = 5;
								}
								break;
						}
					}
					else
					{
						ret = 1;
					}
				}
			}
		}

		lua_pushnumber(L, ret);
		return 1;
	}
#endif

//search
			{NULL, NULL}
		};

//add above
#ifdef ENABLE_VOTE_FOR_BONUS
			{"can_get_bonus_vote", pc_can_get_bonus_vote},
			{"set_bonus_for_vote", pc_set_bonus_for_vote},
#endif

