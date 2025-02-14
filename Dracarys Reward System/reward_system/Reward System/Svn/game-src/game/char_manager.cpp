# Search

	m_iUserDamageRatePremium = 100;

# Add after

#ifdef ENABLE_REWARD_SYSTEM
	m_rewardData.clear();
#endif

# Search

	auto it = m_map_pkChrByVID.begin();
	while (it != m_map_pkChrByVID.end()) {
		LPCHARACTER ch = it->second;
		M2_DESTROY_CHARACTER(ch);
		it = m_map_pkChrByVID.begin();
	}

# Add after

#ifdef ENABLE_REWARD_SYSTEM
	m_rewardData.clear();
#endif


# Add

#ifdef ENABLE_REWARD_SYSTEM
const char* GetRewardIndexToString(BYTE rewardIndex)
{
	std::map<BYTE, std::string> rewardNames = {
		{REWARD_115,"REWARD_115"},
		{REWARD_PET_115,"REWARD_PET_115"},
		{REWARD_120,"REWARD_120"},
		{REWARD_LEGENDARY_SKILL,"REWARD_LEGENDARY_SKILL"},
		{REWARD_LEGENDARY_SKILL_SET,"REWARD_LEGENDARY_SKILL_SET"},
		{REWARD_THANDRUIL,"REWARD_THANDRUIL"},
		{REWARD_HYDRA,"REWARD_HYDRA"},
		{REWARD_CRYSTAL_DRAGON,"REWARD_CRYSTAL_DRAGON"},
		{REWARD_OFFLINESHOP_SLOT,"REWARD_OFFLINESHOP_SLOT"},
		{REWARD_INVENTORY_SLOT,"REWARD_INVENTORY_SLOT"},
		{REWARD_AVERAGE,"REWARD_AVERAGE"},
		{REWARD_ELEMENT,"REWARD_ELEMENT"},
		{REWARD_BATTLEPASS,"REWARD_BATTLEPASS"},
		{REWARD_CUSTOM_SASH,"REWARD_CUSTOM_SASH"},
		{REWARD_AURA,"REWARD_AURA"},
		{REWARD_ENERGY,"REWARD_ENERGY"},
		{REWARD_112_BIO,"REWARD_112_BIO"},
		{REWARD_120_BIO,"REWARD_120_BIO"},
		{REWARD_LEADER_SHIP,"REWARD_LEADER_SHIP"},
		{REWARD_BUFFI_LEGENDARY_SKILL,"REWARD_BUFFI_LEGENDARY_SKILL"},
	};
	auto it = rewardNames.find(rewardIndex);
	if (it != rewardNames.end())
		return it->second.c_str();
	return 0;
}
BYTE GetRewardIndex(const char* szRewardName)
{
	std::map<std::string, BYTE> rewardNames = {
		{"REWARD_115",REWARD_115},
		{"REWARD_PET_115",REWARD_PET_115},
		{"REWARD_120",REWARD_120},
		{"REWARD_LEGENDARY_SKILL",REWARD_LEGENDARY_SKILL},
		{"REWARD_LEGENDARY_SKILL_SET",REWARD_LEGENDARY_SKILL_SET},
		{"REWARD_THANDRUIL",REWARD_THANDRUIL},
		{"REWARD_HYDRA",REWARD_HYDRA},
		{"REWARD_CRYSTAL_DRAGON",REWARD_CRYSTAL_DRAGON},
		{"REWARD_OFFLINESHOP_SLOT",REWARD_OFFLINESHOP_SLOT},
		{"REWARD_INVENTORY_SLOT",REWARD_INVENTORY_SLOT},
		{"REWARD_AVERAGE",REWARD_AVERAGE},
		{"REWARD_ELEMENT",REWARD_ELEMENT},
		{"REWARD_BATTLEPASS",REWARD_BATTLEPASS},
		{"REWARD_CUSTOM_SASH",REWARD_CUSTOM_SASH},
		{"REWARD_AURA",REWARD_AURA},
		{"REWARD_ENERGY",REWARD_ENERGY},
		{"REWARD_112_BIO",REWARD_112_BIO},
		{"REWARD_120_BIO",REWARD_120_BIO},
		{"REWARD_LEADER_SHIP",REWARD_LEADER_SHIP},
		{"REWARD_BUFFI_LEGENDARY_SKILL",REWARD_BUFFI_LEGENDARY_SKILL},
	};
	auto it = rewardNames.find(szRewardName);
	if (it != rewardNames.end())
		return it->second;
	return 0;
}
void CHARACTER_MANAGER::LoadRewardData()
{
	m_rewardData.clear();

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery), "SELECT rewardIndex, lc_text, playerName, itemVnum0, itemCount0, itemVnum1, itemCount1, itemVnum2, itemCount2 FROM player.reward_table");
	std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));

	if (pMsg->Get()->uiNumRows != 0)
	{
		MYSQL_ROW row = NULL;
		for (int n = 0; (row = mysql_fetch_row(pMsg->Get()->pSQLResult)) != NULL; ++n)
		{
			int col = 0;
			TRewardInfo p;
			p.m_rewardItems.clear();

			char rewardName[50];
			DWORD rewardIndex;
			strlcpy(rewardName, row[col++], sizeof(rewardName));
			rewardIndex = GetRewardIndex(rewardName);

			strlcpy(p.lc_text, row[col++], sizeof(p.lc_text));
			strlcpy(p.playerName, row[col++], sizeof(p.playerName));
			for (BYTE j = 0; j < 3; ++j)
			{
				DWORD itemVnum, itemCount;
				str_to_number(itemVnum, row[col++]);
				str_to_number(itemCount, row[col++]);
				p.m_rewardItems.emplace_back(itemVnum, itemCount);
			}
			m_rewardData.emplace(rewardIndex, p);
		}
	}
}
bool CHARACTER_MANAGER::IsRewardEmpty(BYTE rewardIndex)
{
	auto it = m_rewardData.find(rewardIndex);
	if (it != m_rewardData.end())
	{
		if (strcmp(it->second.playerName, "") == 0)
			return true;
	}
	return false;
}
void CHARACTER_MANAGER::SendRewardInfo(LPCHARACTER ch)
{
	ch->SetProtectTime("RewardInfo", 1);
	std::string cmd="";//12
	if (m_rewardData.size())
	{
		for (auto it = m_rewardData.begin(); it != m_rewardData.end(); ++it)
		{
			if (strlen(it->second.playerName) > 1)
			{
				char text[60];
				snprintf(text, sizeof(text), "%d|%s#", it->first, it->second.playerName);
				cmd += text;
			}
			if (strlen(cmd.c_str()) + 12 > CHAT_MAX_LEN - 30)
			{
				ch->ChatPacket(CHAT_TYPE_COMMAND, "RewardInfo %s", cmd.c_str());
				cmd = "";
			}
		}
		if (strlen(cmd.c_str()) > 1)
			ch->ChatPacket(CHAT_TYPE_COMMAND, "RewardInfo %s", cmd.c_str());
	}
}

struct RewardForEach
{
	void operator() (LPDESC d)
	{
		LPCHARACTER ch = d->GetCharacter();
		if (ch == NULL)
			return;
		else if (ch->GetProtectTime("RewardInfo") != 1)
			return;
		CHARACTER_MANAGER::Instance().SendRewardInfo(ch);
	}
};
void CHARACTER_MANAGER::SetRewardData(BYTE rewardIndex, const char* playerName, bool isP2P)
{
	if (!IsRewardEmpty(rewardIndex))
		return;

	auto it = m_rewardData.find(rewardIndex);
	if (it == m_rewardData.end())
		return;
	TRewardInfo& rewardInfo = it->second;
	strlcpy(rewardInfo.playerName, playerName, sizeof(rewardInfo.playerName));

	if (isP2P)
	{
		LPCHARACTER ch = FindPC(playerName);
		if (ch)
		{
			for (DWORD j = 0; j < rewardInfo.m_rewardItems.size(); ++j)
				ch->AutoGiveItem(rewardInfo.m_rewardItems[j].first, rewardInfo.m_rewardItems[j].second);
		}

		char msg[CHAT_MAX_LEN+1];
		snprintf(msg, sizeof(msg), LC_TEXT(it->second.lc_text), playerName);
		//snprintf(msg, sizeof(msg), rewardInfo.lc_text, playerName);
		BroadcastNotice(false, msg);

		TPacketGGRewardInfo p;
		p.bHeader = HEADER_GG_REWARD_INFO;
		p.rewardIndex = rewardIndex;
		strlcpy(p.playerName, playerName, sizeof(p.playerName));
		P2P_MANAGER::Instance().Send(&p, sizeof(p));

		char szQuery[1024];
		snprintf(szQuery, sizeof(szQuery), "UPDATE player.reward_table SET playerName = '%s' WHERE lc_text = '%s'", playerName, rewardInfo.lc_text);
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));
	}
	const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::instance().GetClientSet();
	std::for_each(c_ref_set.begin(), c_ref_set.end(), RewardForEach());
}
#endif
