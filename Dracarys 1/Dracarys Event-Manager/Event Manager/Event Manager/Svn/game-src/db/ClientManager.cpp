# Search

	peer->EncodeWORD(0xffff);

# add after

#ifdef ENABLE_EVENT_MANAGER
	SendEventData(peer);
#endif


# Search

	marriage::CManager::instance().Update();

# add after

#ifdef ENABLE_EVENT_MANAGER
			//if (!(thecore_heart->pulse % thecore_heart->passes_per_sec * 5))
				InitializeEventManager();
			UpdateEventManager();
#endif


# Add


#ifdef ENABLE_EVENT_MANAGER
#include "buffer_manager.h"
void stringToTime(struct tm& t, const std::string& strDateTime)
{
	int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
	if (sscanf(strDateTime.c_str(), "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6)
	{
		t.tm_year = year - 1900;
		t.tm_mon = month - 1;
		t.tm_mday = day;
		t.tm_isdst = 0;
		t.tm_hour = hour;
		t.tm_min = min;
		t.tm_sec = sec;
	}
}
void CClientManager::UpdateEventManager()
{
	time_t cur_Time = time(NULL);
	struct tm vKey = *localtime(&cur_Time);
	auto it = m_EventManager.find(vKey.tm_mday);
	if (it != m_EventManager.end())
	{
		if (it->second.size())
		{
			for (DWORD j = 0; j < it->second.size(); ++j)
			{
				const TEventManagerData& pData = it->second[j];
				int leftTimeStart = pData.startRealTime - time(0);
				if (leftTimeStart == 0)
				{
					TEMP_BUFFER buf;
					BYTE subIndex = EVENT_MANAGER_EVENT_STATUS;
					bool eventStatus = true;
					buf.write(&subIndex, sizeof(BYTE));
					buf.write(&eventStatus, sizeof(bool));
					buf.write(&pData, sizeof(TEventManagerData));
					ForwardPacket(HEADER_DG_EVENT_MANAGER, buf.read_peek(), buf.size(), (pData.channelFlag != 0)?pData.channelFlag:0);
				}
				int leftTimeEnd = pData.endRealTime - time(0);
				if (leftTimeEnd == 0)
				{
					TEMP_BUFFER buf;
					BYTE subIndex = EVENT_MANAGER_EVENT_STATUS;
					bool eventStatus = false;
					buf.write(&subIndex, sizeof(BYTE));
					buf.write(&eventStatus, sizeof(bool));
					buf.write(&pData, sizeof(TEventManagerData));
					ForwardPacket(HEADER_DG_EVENT_MANAGER, buf.read_peek(), buf.size(), (pData.channelFlag != 0) ? pData.channelFlag : 0);
				}
			}
		}
	}
}

BYTE GetEventIndex(const char* szEventName)
{
	std::map<std::string, BYTE> eventNames = {
		{"BONUS_EVENT",BONUS_EVENT},
		{"DOUBLE_BOSS_LOOT_EVENT",DOUBLE_BOSS_LOOT_EVENT},
		{"DOUBLE_METIN_LOOT_EVENT",DOUBLE_METIN_LOOT_EVENT},
		{"DOUBLE_MISSION_BOOK_EVENT",DOUBLE_MISSION_BOOK_EVENT},
		{"DUNGEON_COOLDOWN_EVENT",DUNGEON_COOLDOWN_EVENT},
		{"DUNGEON_TICKET_LOOT_EVENT",DUNGEON_TICKET_LOOT_EVENT},
		{"EMPIRE_WAR_EVENT",EMPIRE_WAR_EVENT},
		{"MOONLIGHT_EVENT",MOONLIGHT_EVENT},
		{"TOURNAMENT_EVENT",TOURNAMENT_EVENT},
		{"WHELL_OF_FORTUNE_EVENT",WHELL_OF_FORTUNE_EVENT},
		{"HALLOWEEN_EVENT",HALLOWEEN_EVENT},
		{"NPC_SEARCH_EVENT",NPC_SEARCH_EVENT},
	};
	auto it = eventNames.find(szEventName);
	if (it != eventNames.end())
		return it->second;

	return EVENT_NONE;
}

bool SortWithTime(const TEventManagerData& a, const TEventManagerData& b)
{
	return (a.startTime.tm_hour < b.startTime.tm_hour);
}
bool CClientManager::InitializeEventManager()
{
	m_EventManager.clear();
	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery), "SELECT eventIndex, startTime, endTime, empireFlag, channelFlag, value0, value1, value2, value3 FROM player.event_table");
	SQLMsg* pMsg = CDBManager::instance().DirectQuery(szQuery, SQL_PLAYER);
	if (pMsg->Get()->uiNumRows != 0)
	{
		time_t cur_Time = time(NULL);
		struct tm vKey = *localtime(&cur_Time);

		MYSQL_ROW row = NULL;
		for (int n = 0; (row = mysql_fetch_row(pMsg->Get()->pSQLResult)) != NULL; ++n)
		{
			int col = 0;

			char eventName[50];
			TEventManagerData p;
			strlcpy(eventName, row[col++], sizeof(eventName));
			p.eventIndex = GetEventIndex(eventName);
			strlcpy(p.startText, row[col++], sizeof(p.startText));
			strlcpy(p.endText, row[col++], sizeof(p.endText));
			//p.startTime = stringToTime(p.startText);
			//p.endTime = stringToTime(p.endText);
			stringToTime(p.startTime, p.startText);
			stringToTime(p.endTime, p.endText);
			p.startRealTime = mktime(&p.startTime);
			p.endRealTime = mktime(&p.endTime);
			bool insertWithStart = true;
			if (p.startTime.tm_mon < vKey.tm_mon)
				insertWithStart = false;
			str_to_number(p.empireFlag, row[col++]);
			str_to_number(p.channelFlag, row[col++]);
			for(DWORD j=0;j<4;++j)
				str_to_number(p.value[j], row[col++]);
			if (p.endTime.tm_mon < vKey.tm_mon)
				continue;
			else
				if (p.endTime.tm_mday == 1 && p.endTime.tm_hour == 0 && p.endTime.tm_min == 0 && p.endTime.tm_sec == 0)
					continue;
			if (insertWithStart)
			{
				auto it = m_EventManager.find(p.startTime.tm_mday);
				if (it != m_EventManager.end())
					it->second.emplace_back(p);
				else
				{
					std::vector<TEventManagerData> m_vec;
					m_vec.emplace_back(p);
					m_EventManager.emplace(p.startTime.tm_mday, m_vec);
				}
			}
			else
			{
				auto it = m_EventManager.find(p.endTime.tm_mday);
				if (it != m_EventManager.end())
					it->second.emplace_back(p);
				else
				{
					std::vector<TEventManagerData> m_vec;
					m_vec.emplace_back(p);
					m_EventManager.emplace(p.endTime.tm_mday, m_vec);
				}
			}
		}

		if (m_EventManager.size())
		{
			for (auto it = m_EventManager.begin(); it != m_EventManager.end(); ++it)
				std::stable_sort(it->second.begin(), it->second.end(), SortWithTime);
		}

	}
	delete pMsg;
	SendEventData();
	return true;
}

void CClientManager::SendEventData(CPeer* pkPeer)
{
	TEMP_BUFFER buf;

	BYTE subIndex = EVENT_MANAGER_LOAD;
	buf.write(&subIndex, sizeof(BYTE));

	BYTE dayCount = m_EventManager.size();
	buf.write(&dayCount, sizeof(BYTE));

	if (m_EventManager.size())
	{
		for (auto it = m_EventManager.begin(); it != m_EventManager.end(); ++it)
		{
			BYTE dayIndex = it->first;
			BYTE dayEventCount = it->second.size();
			buf.write(&dayIndex, sizeof(BYTE));
			buf.write(&dayEventCount, sizeof(BYTE));
			if(dayEventCount)
				buf.write(it->second.data(), sizeof(TEventManagerData)* dayEventCount);
		}
	}
	if (pkPeer != NULL)
	{
		pkPeer->EncodeHeader(HEADER_DG_EVENT_MANAGER, 0, buf.size());
		pkPeer->Encode(buf.read_peek(), buf.size());
	}
	else
	{
		ForwardPacket(HEADER_DG_EVENT_MANAGER, buf.read_peek(), buf.size());
	}
}
#endif

