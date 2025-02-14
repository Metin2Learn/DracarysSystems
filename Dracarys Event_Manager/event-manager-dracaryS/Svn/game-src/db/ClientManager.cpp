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
			UpdateEventManager();
#endif


# Search

		default:
			sys_err("Unknown header (header: %d handle: %d length: %d)", header, dwHandle, dwLength);
			break;

# add before

#ifdef ENABLE_EVENT_MANAGER
		case HEADER_GD_EVENT_MANAGER:
			RecvEventManagerPacket(data);
			break;
#endif


# Add


#ifdef ENABLE_EVENT_MANAGER
#include "buffer_manager.h"
bool IsDontHaveEndTimeEvent(BYTE eventIndex)
{
	switch (eventIndex)
	{
		case EMPIRE_WAR_EVENT:
		case TOURNAMENT_EVENT:
			return true;
			break;
	}
	return false;
}
void CClientManager::RecvEventManagerPacket(const char* data)
{
	const BYTE subIndex = *(BYTE*)data;
	data += sizeof(BYTE);
	if (subIndex == EVENT_MANAGER_UPDATE)
		InitializeEventManager(true);
	else if (subIndex == EVENT_MANAGER_REMOVE_EVENT)
	{
		const WORD index = *(WORD*)data;
		data += sizeof(WORD);

		if (m_EventManager.size())
		{
			for (auto it = m_EventManager.begin(); it != m_EventManager.end(); ++it)
			{
				for (DWORD j = 0; j < it->second.size(); ++j)
				{
					TEventManagerData& eventPtr = it->second[j];
					if (eventPtr.eventID == index)
					{
						eventPtr.endTime = time(0);
						UpdateEventManager();
						char szQuery[QUERY_MAX_LEN];
						snprintf(szQuery, sizeof(szQuery), "UPDATE player.event_table SET endTime = NOW() WHERE id = %u", index);
						std::unique_ptr<SQLMsg> pMsg(CDBManager::instance().DirectQuery(szQuery, SQL_PLAYER));
						return;
					}
				}
			}
		}
	}
}
void CClientManager::UpdateEventManager()
{
	const time_t now = time(0);
	const struct tm vKey = *localtime(&now);
	const auto it = m_EventManager.find(vKey.tm_mday);
	if (it != m_EventManager.end())
	{
		if (it->second.size())
		{
			for(DWORD j=0;j<it->second.size();++j)
			{
				TEventManagerData& pData = it->second[j];
				int leftTime = pData.startTime - now;
				bool sendStatusPacket = false;
				
				if (leftTime == 0 && pData.eventStatus == false)
				{
					pData.eventStatus = true;
					sendStatusPacket = true;
				}

				leftTime = pData.endTime - now;
				if (leftTime == 0 && pData.endTime != 0 && pData.eventStatus == true)
				{
					pData.eventStatus = false;
					sendStatusPacket = true;
				}

				if (sendStatusPacket)
				{
					const BYTE subIndex = EVENT_MANAGER_EVENT_STATUS;
					TEMP_BUFFER buf;
					buf.write(&subIndex, sizeof(BYTE));
					buf.write(&pData.eventID, sizeof(WORD));
					buf.write(&pData.eventStatus, sizeof(bool));
					buf.write(&pData.endTime, sizeof(int));
					ForwardPacket(HEADER_DG_EVENT_MANAGER, buf.read_peek(), buf.size());
				}
			}
		}
	}
}

bool SortWithTime(const TEventManagerData& a, const TEventManagerData& b)
{
	return (a.startTime < b.startTime);
}
bool CClientManager::InitializeEventManager(bool updateFromGameMaster)
{
	m_EventManager.clear();

	char szQuery[QUERY_MAX_LEN];
	snprintf(szQuery, sizeof(szQuery), "SELECT id, eventIndex+0, UNIX_TIMESTAMP(startTime), UNIX_TIMESTAMP(endTime), empireFlag, channelFlag, value0, value1, value2, value3 FROM player.event_table");
	std::unique_ptr<SQLMsg> pMsg(CDBManager::instance().DirectQuery(szQuery, SQL_PLAYER));
	if (pMsg->Get()->uiNumRows != 0)
	{
		const time_t cur_Time = time(NULL);
		const struct tm vKey = *localtime(&cur_Time);

		MYSQL_ROW row = NULL;
		for (int n = 0; (row = mysql_fetch_row(pMsg->Get()->pSQLResult)) != NULL; ++n)
		{
			int col = 0;
			TEventManagerData p;
			str_to_number(p.eventID, row[col++]);
			str_to_number(p.eventIndex, row[col++]);
			str_to_number(p.startTime, row[col++]);
			str_to_number(p.endTime, row[col++]);
			str_to_number(p.empireFlag, row[col++]);
			str_to_number(p.channelFlag, row[col++]);
			for (DWORD j = 0; j < 4; ++j)
				str_to_number(p.value[j], row[col++]);

			const time_t eventEndTime = p.endTime;
			const struct tm vEventEndKey = *localtime(&eventEndTime);
			if (vEventEndKey.tm_mon < vKey.tm_mon && p.endTime != 0)
				continue;

			p.eventTypeOnlyStart = IsDontHaveEndTimeEvent(p.eventIndex);
			p.eventStatus = p.eventTypeOnlyStart ? false : (cur_Time >= p.startTime && cur_Time <= p.endTime);

			const time_t eventStartTime = p.startTime;
			const struct tm vEventStartKey = *localtime(&eventStartTime);

			bool insertWithStart = true;
			if (vEventStartKey.tm_mon < vKey.tm_mon)
				insertWithStart = false;

			if (insertWithStart)
			{
				const auto it = m_EventManager.find(vEventStartKey.tm_mday);
				if (it != m_EventManager.end())
					it->second.emplace_back(p);
				else
				{
					std::vector<TEventManagerData> m_vec;
					m_vec.emplace_back(p);
					m_EventManager.emplace(vEventStartKey.tm_mday, m_vec);
				}
			}
			else
			{
				const auto it = m_EventManager.find(vEventEndKey.tm_mday);
				if (it != m_EventManager.end())
					it->second.emplace_back(p);
				else
				{
					std::vector<TEventManagerData> m_vec;
					m_vec.emplace_back(p);
					m_EventManager.emplace(vEventEndKey.tm_mday, m_vec);
				}
			}
		}
		if (m_EventManager.size())
		{
			for (auto it = m_EventManager.begin(); it != m_EventManager.end(); ++it)
				std::stable_sort(it->second.begin(), it->second.end(), SortWithTime);
		}
	}
	SendEventData(NULL, updateFromGameMaster);
	return true;
}

void CClientManager::SendEventData(CPeer* pkPeer, bool updateFromGameMaster)
{
	const BYTE subIndex = EVENT_MANAGER_LOAD;
	const BYTE dayCount = m_EventManager.size();
	TEMP_BUFFER buf;
	buf.write(&subIndex, sizeof(BYTE));
	buf.write(&dayCount, sizeof(BYTE));
	buf.write(&updateFromGameMaster, sizeof(bool));

	for (const auto& [dayIndex, dayData] : m_EventManager)
	{
		BYTE dayEventCount = dayData.size();
		buf.write(&dayIndex, sizeof(BYTE));
		buf.write(&dayEventCount, sizeof(BYTE));
		if (dayEventCount > 0)
			buf.write(dayData.data(), dayEventCount * sizeof(TEventManagerData));
	}

	if (pkPeer != NULL)
	{
		pkPeer->EncodeHeader(HEADER_DG_EVENT_MANAGER, 0, buf.size());
		pkPeer->Encode(buf.read_peek(), buf.size());
	}
	else
		ForwardPacket(HEADER_DG_EVENT_MANAGER, buf.read_peek(), buf.size());
}
#endif


