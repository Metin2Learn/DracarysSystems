# Search

	sys_log(0, "DISCONNECT: %s (%s)", GetName(), c_pszReason ? c_pszReason : "unset");

#Add after

#if defined(__MISSION_BOOKS__)
	SaveMissionData();
#endif

# Add

#if defined(__MISSION_BOOKS__)
void CHARACTER::SetProtectTime(const std::string& flagname, int value)
{
	itertype(m_protection_Time) it = m_protection_Time.find(flagname);
	if (it != m_protection_Time.end())
		it->second = value;
	else
		m_protection_Time.insert(make_pair(flagname, value));
}
int CHARACTER::GetProtectTime(const std::string& flagname) const
{
	itertype(m_protection_Time) it = m_protection_Time.find(flagname);
	if (it != m_protection_Time.end())
		return it->second;
	return 0;
}
void CHARACTER::SetMissionBook(BYTE missionType, BYTE value, DWORD arg, WORD level)
{
#if __cplusplus < 199711L
	for (itertype(m_mapMissionData) it = m_mapMissionData.begin(); it != m_mapMissionData.end(); ++it)
#else
	for (auto it = m_mapMissionData.begin(); it != m_mapMissionData.end(); ++it)
#endif
	{
#if __cplusplus < 199711L
		const TMissionBookData* missionData = CHARACTER_MANAGER::Instance().GetMissionData(it->first);
#else
		auto missionData = CHARACTER_MANAGER::Instance().GetMissionData(it->first);
#endif
		if (missionData)
		{
			if (missionData->type != missionType)
				continue;
			if (missionData->subtype != 0)
			{
				if (missionData->subtype != arg)
					continue;
			}
			else
			{
				if (!LEVEL_DELTA(level, GetLevel(), missionData->levelRange))
					continue;
			}
			if (it->second.value >= missionData->max || time(0) > it->second.leftTime)
				continue;
			it->second.value += value;
			
			if (it->second.value >= missionData->max)
			{
				it->second.endTime = time(0);
				it->second.value = missionData->max;

				char endTime[34];
				const time_t cur_Time = it->second.endTime;
				const struct tm vKey = *localtime(&cur_Time);
				snprintf(endTime, sizeof(endTime), "%02d:%02d:%02d-%02d/%02d/%02d", vKey.tm_hour, vKey.tm_min, vKey.tm_sec, vKey.tm_mday, vKey.tm_mon, vKey.tm_year + 1900);

				ChatPacket(CHAT_TYPE_COMMAND, "UpdateMissionEndTime %u %s", it->first, endTime);
				
				ChatPacket(CHAT_TYPE_INFO, "Your mission done!");
			}
			if (GetProtectTime("mission_load") == 1)
				ChatPacket(CHAT_TYPE_COMMAND, "UpdateMissionValue %u %lld", it->first, it->second.value);
		}
	}
}
void CHARACTER::RewardMissionBook(WORD missionID)
{
#if __cplusplus < 199711L
	const itertype(m_mapMissionData) it = m_mapMissionData.find(missionID);
#else
	const auto it = m_mapMissionData.find(missionID);
#endif
	if (it != m_mapMissionData.end())
	{
#if __cplusplus < 199711L
		const TMissionBookData* missionData = CHARACTER_MANAGER::Instance().GetMissionData(missionID);
#else
		auto missionData = CHARACTER_MANAGER::Instance().GetMissionData(missionID);
#endif
		if (missionData)
		{
			if(it->second.reward)
			{
				ChatPacket(CHAT_TYPE_INFO, "You already get reward!");
				return;
			}

			if (it->second.value >= missionData->max)
			{
				it->second.reward = true;
				SaveMissionData();
				for (BYTE j = 0; j < 6; ++j)
				{
					if (missionData->rewardItems[j] != 0)
						AutoGiveItem(missionData->rewardItems[j], missionData->rewardCount[j]);
				}
				PointChange(POINT_GOLD, number(missionData->gold[0], missionData->gold[1]));
				PointChange(POINT_EXP, number(missionData->exp[0], missionData->exp[1]));
				ChatPacket(CHAT_TYPE_INFO, "Succesfully get reward!");
				ChatPacket(CHAT_TYPE_COMMAND, "RewardMissionData %u %d", missionID, true);
			}
			else
				ChatPacket(CHAT_TYPE_INFO, "You need first finish mission!");
		}
	}
}
void CHARACTER::DeleteBookMission(WORD missionID)
{
#if __cplusplus < 199711L
	itertype(m_mapMissionData) it = m_mapMissionData.find(missionID);
#else
	auto it = m_mapMissionData.find(missionID);
#endif
	if (it != m_mapMissionData.end())
	{
		m_mapMissionData.erase(it);
		SaveMissionData();
		ChatPacket(CHAT_TYPE_COMMAND, "RemoveMissionData %u", missionID);
		ChatPacket(CHAT_TYPE_INFO, "Mission succesfully removed!");
	}
}
BYTE CHARACTER::MissionCount()
{
	return m_mapMissionData.size();
}
bool CHARACTER::IsMissionHas(WORD missionID)
{
#if __cplusplus < 199711L
	const itertype(m_mapMissionData) it = m_mapMissionData.find(missionID);
#else
	const auto it = m_mapMissionData.find(missionID);
#endif
	if (it != m_mapMissionData.end())
		return true;
	return false;
}
void CHARACTER::GiveNewMission(WORD missionID)
{
#if __cplusplus < 199711L
	const TMissionBookData* missionData = CHARACTER_MANAGER::Instance().GetMissionData(missionID);
#else
	auto missionData = CHARACTER_MANAGER::Instance().GetMissionData(missionID);
#endif
	if (!missionData)
		return;
	TMissionBook misson;
	memset(&misson,0,sizeof(misson));
	misson.leftTime = time(0)+ missionData->maxTime;
#if __cplusplus < 199711L
	m_mapMissionData.insert(std::make_pair(missionID, misson));
#else
	m_mapMissionData.emplace(missionID, misson);
#endif
	SaveMissionData();

	std::string cmdText("");
	ModifySetMissionCMD(missionID, cmdText);
	if (cmdText.length())
		ChatPacket(CHAT_TYPE_COMMAND, "UpdateMissionInfo %s", cmdText.c_str());
}
void CHARACTER::SaveMissionData()
{
	char filename[124];
	snprintf(filename, sizeof(filename), "share/missionbook/%u", GetPlayerID());
	FILE* fp = fopen(filename, "w+");
	if (fp)
	{
		fprintf(fp, "missionid-value-lefttime-reward\n");
#if __cplusplus < 199711L
		for (itertype(m_mapMissionData) it = m_mapMissionData.begin(); it != m_mapMissionData.end(); ++it)
		{
			const BYTE& missionID = it->first;
			const TMissionBook& missionData = it->second;
			fprintf(fp, "%u %lld %d %u %d\n", missionID, missionData.value, missionData.leftTime, missionData.reward, missionData.endTime);
		}
#else
		for (const auto& [missionID, missionData] : m_mapMissionData)
			fprintf(fp, "%u %lld %d %u %d\n", missionID, missionData.value, missionData.leftTime, missionData.reward, missionData.endTime);
#endif
		fclose(fp);
	}
}

void CHARACTER::ModifySetMissionCMD(WORD missionID, std::string& cmdText)
{
#if __cplusplus < 199711L
	const itertype(m_mapMissionData) it = m_mapMissionData.find(missionID);
#else
	const auto it = m_mapMissionData.find(missionID);
#endif
	if (it != m_mapMissionData.end())
	{
#if __cplusplus < 199711L
		const TMissionBookData* missionData = CHARACTER_MANAGER::Instance().GetMissionData(it->first);
#else
		auto missionData = CHARACTER_MANAGER::Instance().GetMissionData(it->first);
#endif
		if (missionData)
		{
			char endTime[34];
			if (it->second.endTime != 0)
			{
				const time_t cur_Time = it->second.endTime;
				const struct tm vKey = *localtime(&cur_Time);
				snprintf(endTime, sizeof(endTime), "%02d:%02d:%02d-%02d/%02d/%02d", vKey.tm_hour, vKey.tm_min, vKey.tm_sec, vKey.tm_mday, vKey.tm_mon, vKey.tm_year + 1900);
			}
			else
				snprintf(endTime, sizeof(endTime), "-");
			cmdText += std::to_string(it->first);
			cmdText += "#";
			cmdText += std::to_string(missionData->missionItemIndex);
			cmdText += "#";
			cmdText += std::to_string(missionData->type);
			cmdText += "#";
			cmdText += std::to_string(missionData->subtype);
			cmdText += "#";
			cmdText += std::to_string(missionData->levelRange);
			cmdText += "#";
			cmdText += std::to_string(it->second.value);
			cmdText += "#";
			cmdText += std::to_string(missionData->max);
			cmdText += "#";
			cmdText += std::to_string(it->second.leftTime-time(0));
			cmdText += "#";
			cmdText += std::to_string(missionData->maxTime);
			cmdText += "#";
			cmdText += endTime;
			cmdText += "#";
			cmdText += std::to_string(missionData->gold[0]);
			cmdText += "#";
			cmdText += std::to_string(missionData->gold[1]);
			cmdText += "#";
			cmdText += std::to_string(missionData->exp[0]);
			cmdText += "#";
			cmdText += std::to_string(missionData->exp[1]);
			cmdText += "#";
			cmdText += std::to_string(it->second.reward);
			cmdText += "#";
			BYTE rewardCount = 0;
			for (BYTE j = 0; j < 6; ++j)
			{
				if ((missionData->rewardItems[j] == 0 && j != 0) || j == 5)
				{
					rewardCount = j + 1;
					break;
				}
			}
			cmdText += std::to_string(rewardCount);
			cmdText += "#";
			for (BYTE j = 0; j < rewardCount; ++j)
			{
				cmdText += std::to_string(missionData->rewardItems[j]);
				cmdText += "#";
				cmdText += std::to_string(missionData->rewardCount[j]);
				cmdText += "#";
			}
		}
		else
		{
			sys_err("Player has %d id mission but not has remove in data!", it->first);
		}
	}
}
void CHARACTER::SendMissionData()
{
	if (GetProtectTime("mission_load") == 1)
		return;
	ChatPacket(CHAT_TYPE_COMMAND, "ClearBookMission");
	std::string cmdText("");
#if __cplusplus < 199711L
	for (itertype(m_mapMissionData) it = m_mapMissionData.begin(); it != m_mapMissionData.end(); ++it)
#else
	for (auto it = m_mapMissionData.begin(); it != m_mapMissionData.end(); ++it)
#endif
	{
		ModifySetMissionCMD(it->first, cmdText);
		if (cmdText.length())
		{
			ChatPacket(CHAT_TYPE_COMMAND, "UpdateMissionInfo %s", cmdText.c_str());
			cmdText.clear();
		}
	}
	SetProtectTime("mission_load", 1);
}
void CHARACTER::LoadMissionData()
{
	m_mapMissionData.clear();
	char filename[124];
	snprintf(filename, sizeof(filename), "share/missionbook/%u", GetPlayerID());
	FILE* fp;
	if ((fp = fopen(filename, "r")) != NULL)
	{
		char	one_line[256];
		while (fgets(one_line, 256, fp))
		{
			std::vector<std::string> m_vec;
			split_argument(one_line, m_vec);
			if (m_vec.size() != 5)
				continue;
			TMissionBook missionItem;
			WORD missionID;
			str_to_number(missionID, m_vec[0].c_str());
			str_to_number(missionItem.value, m_vec[1].c_str());
			str_to_number(missionItem.leftTime, m_vec[2].c_str());
			str_to_number(missionItem.reward, m_vec[3].c_str());
			str_to_number(missionItem.endTime, m_vec[4].c_str());
#if __cplusplus < 199711L
			m_mapMissionData.insert(std::make_pair(missionID, missionItem));
#else
			m_mapMissionData.emplace(missionID, missionItem);
#endif
		}
		fclose(fp);
	}
	
}
#endif

