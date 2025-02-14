# Search

	m_iUserDamageRatePremium = 100;

# Add after

#ifdef ENABLE_EVENT_MANAGER
	m_eventData.clear();
#endif

# Search

	auto it = m_map_pkChrByVID.begin();

# Add before

#ifdef ENABLE_EVENT_MANAGER
	m_eventData.clear();
#endif


# Add

#ifdef ENABLE_EVENT_MANAGER
#include "item_manager.h"
#include "item.h"
#include "desc_client.h"
#include "desc_manager.h"
void CHARACTER_MANAGER::ClearEventData()
{
	m_eventData.clear();
}
/*
BONUS_EVENT = 1,////DONE
DOUBLE_BOSS_LOOT_EVENT = 2,//DONE
DOUBLE_METIN_LOOT_EVENT = 3,//DONE
DOUBLE_MISSION_BOOK_EVENT = 4,//DONE
DUNGEON_COOLDOWN_EVENT = 5,//DONE
DUNGEON_TICKET_LOOT_EVENT = 6,//DONE
EMPIRE_WAR_EVENT = 7,
MOONLIGHT_EVENT = 8,//DONE
TOURNAMENT_EVENT = 9,
WHELL_OF_FORTUNE_EVENT = 10,
HALLOWEEN_EVENT = 11,
NPC_SEARCH_EVENT = 12,
*/

void CHARACTER_MANAGER::CheckBonusEvent(LPCHARACTER ch)
{
	time_t cur_Time = time(NULL);
	struct tm vKey = *localtime(&cur_Time);
	auto it = m_eventData.find(vKey.tm_mday);
	if (it != m_eventData.end())
	{
		if (it->second.size())
		{
			for (BYTE j = 0; j < it->second.size(); ++j)
			{
				const TEventManagerData& eventData = it->second[j];
				if (cur_Time > eventData.startRealTime && cur_Time < eventData.endRealTime)
				{
					if (eventData.eventIndex == BONUS_EVENT)
					{
						if (eventData.channelFlag != 0)
						{
							if (eventData.channelFlag != ch->GetEmpire())
								continue;
						}
						ch->ApplyPoint(eventData.value[0], eventData.value[1]);
					}
				}
			}
		}
	}
}

bool CHARACTER_MANAGER::CheckEventIsActive(BYTE eventIndex)
{
	time_t cur_Time = time(NULL);
	struct tm vKey = *localtime(&cur_Time);
	auto it = m_eventData.find(vKey.tm_mday);
	if (it != m_eventData.end())
	{
		if (it->second.size())
		{
			for (BYTE j = 0; j < it->second.size(); ++j)
			{
				const TEventManagerData& eventData = it->second[j];
				if (eventData.eventIndex == eventIndex)
					if (cur_Time > eventData.startRealTime && cur_Time < eventData.endRealTime)
						return true;
			}
		}
	}
	return false;
}
void CHARACTER_MANAGER::CheckEventForDrop(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM>& vec_item)
{
	time_t cur_Time = time(NULL);
	struct tm vKey = *localtime(&cur_Time);
	auto it = m_eventData.find(vKey.tm_mday);
	if (it != m_eventData.end())
	{
		if (it->second.size())
		{
			for (BYTE j = 0; j < it->second.size(); ++j)
			{
				const TEventManagerData& eventData = it->second[j];
				if (cur_Time > eventData.startRealTime && cur_Time < eventData.endRealTime)
				{
					int prob = number(1, 100);
					int success_prob = eventData.value[3];
					if (prob > success_prob)
						return;
					if (eventData.eventIndex == DOUBLE_BOSS_LOOT_EVENT)
					{
						if (pkChr->GetMobRank() >= MOB_RANK_BOSS)
						{
							std::vector<LPITEM> m_cache;
							LPITEM item = NULL;
							for (DWORD j = 0; j < vec_item.size(); ++j)
							{
								item = ITEM_MANAGER::Instance().CreateItem(vec_item[j]->GetVnum(), 1, 0, true);
								if (item) m_cache.emplace_back(item);
							}
							for (DWORD j = 0; j < m_cache.size(); ++j)
								vec_item.emplace_back(m_cache[j]);
							m_cache.clear();
						}
					}
					else if (eventData.eventIndex == DOUBLE_METIN_LOOT_EVENT)
					{
						if (pkChr->IsStone())
						{
							std::vector<LPITEM> m_cache;
							LPITEM item = NULL;
							for (DWORD j = 0; j < vec_item.size(); ++j)
							{
								item = ITEM_MANAGER::Instance().CreateItem(vec_item[j]->GetVnum(), 1, 0, true);
								if (item) m_cache.emplace_back(item);
							}
							for (DWORD j = 0; j < m_cache.size(); ++j)
								vec_item.emplace_back(m_cache[j]);
							m_cache.clear();
						}
					}
					else if (eventData.eventIndex == DOUBLE_MISSION_BOOK_EVENT)
					{
						std::vector<LPITEM> m_cache;
						LPITEM item = NULL;
						std::vector<DWORD> m_missionbook = {
							50300,
							469,
						};
						for (DWORD j = 0; j < vec_item.size(); ++j)
						{
							LPITEM checkItem = vec_item[j];
							auto it = std::find(m_missionbook.begin(), m_missionbook.end(), checkItem->GetVnum());
							if (it != m_missionbook.end())
							{

								item = ITEM_MANAGER::Instance().CreateItem(checkItem->GetVnum(), 1, 0, true);
								if (item) m_cache.emplace_back(item);
							}
						}
						for (DWORD j = 0; j < m_cache.size(); ++j)
							vec_item.emplace_back(m_cache[j]);
						m_cache.clear();
					}
					else if (eventData.eventIndex == DUNGEON_TICKET_LOOT_EVENT)
					{
						std::vector<LPITEM> m_cache;
						LPITEM item = NULL;
						std::vector<DWORD> m_missionbook = {
							50300,
							469,
						};
						for (DWORD j = 0; j < vec_item.size(); ++j)
						{
							LPITEM checkItem = vec_item[j];
							auto it = std::find(m_missionbook.begin(), m_missionbook.end(), checkItem->GetVnum());
							if (it != m_missionbook.end())
							{
								item = ITEM_MANAGER::Instance().CreateItem(checkItem->GetVnum(), 1, 0, true);
								if (item) m_cache.emplace_back(item);
							}
						}
						for (DWORD j = 0; j < m_cache.size(); ++j)
							vec_item.emplace_back(m_cache[j]);
						m_cache.clear();
					}
					else if (eventData.eventIndex == MOONLIGHT_EVENT)
					{
						DWORD itemVnum = 50011;
						LPITEM item = ITEM_MANAGER::Instance().CreateItem(itemVnum, 1, 0, true);
						if (item) vec_item.emplace_back(item);
					}
				}
			}
		}
	}
}
void CHARACTER_MANAGER::SendDataPlayer(LPCHARACTER ch)
{
	TPacketGCEventManager p;
	p.header = HEADER_GC_EVENT_MANAGER;	

	p.size = sizeof(p);
	TEMP_BUFFER buf;
	BYTE dayCount = m_eventData.size();
	buf.write(&dayCount, sizeof(BYTE));
	p.size += sizeof(BYTE);

	if (m_eventData.size())
	{
		for (auto it = m_eventData.begin(); it != m_eventData.end(); ++it) {
			p.size += sizeof(BYTE) + sizeof(BYTE) + (sizeof(TEventManagerDataClient) * it->second.size());

			BYTE dayIndex = it->first;
			buf.write(&dayIndex, sizeof(BYTE));
			BYTE dayEventCount = it->second.size();
			buf.write(&dayEventCount, sizeof(BYTE));

			std::vector<TEventManagerDataClient> m_vec;
			for (BYTE j = 0; j < it->second.size(); ++j)
			{
				const TEventManagerData& eventData= it->second[j];
				TEventManagerDataClient p;
				p.eventIndex = eventData.eventIndex;
				p.startRealTime = eventData.startRealTime-get_global_time();
				p.endRealTime = eventData.endRealTime-get_global_time();
				p.isAlreadyStart = CheckEventIsActive(eventData.eventIndex);
				strlcpy(p.endText, eventData.endText, sizeof(p.endText));
				strlcpy(p.startText, eventData.startText, sizeof(p.startText));
				p.empireFlag = eventData.empireFlag;
				p.channelFlag = eventData.channelFlag;
				thecore_memcpy(&p.value, &eventData.value, sizeof(p.value));
				m_vec.emplace_back(p);
			}
			buf.write(m_vec.data(), sizeof(TEventManagerDataClient) * dayEventCount);
		}
	}
	ch->GetDesc()->BufferedPacket(&p, sizeof(p));
	ch->GetDesc()->Packet(buf.read_peek(), buf.size());
}
void CHARACTER_MANAGER::SetEventStatus(const TEventManagerData& m_data, bool eventStatus)
{
	// eventStatus 1 - ACTIVE
	// eventStatus 0 - DEACTIVE
	std::map<BYTE, std::pair<std::string, std::string>> m_eventText = {
		{BONUS_EVENT,{"761","762"}},
		{DOUBLE_BOSS_LOOT_EVENT,{"763","764"}},
		{DOUBLE_METIN_LOOT_EVENT,{"765","766"}},
		{DOUBLE_MISSION_BOOK_EVENT,{"767","768"}},
		{DUNGEON_COOLDOWN_EVENT,{"769","770"}},
		{DUNGEON_TICKET_LOOT_EVENT,{"771","772"}},
		{MOONLIGHT_EVENT,{"773","774"}},
	};

	auto it = m_eventText.find(m_data.eventIndex);
	if (it != m_eventText.end())
	{
		if (m_data.channelFlag == 0)
		{
			if (eventStatus)
				SendNotice(it->second.first.c_str());
			else
				SendNotice(it->second.second.c_str());
		}
		else
		{
			if (eventStatus)
				BroadcastNotice(it->second.first.c_str());
			else
				BroadcastNotice(it->second.second.c_str());
		}
	}

	// CLEAR BONUS
	if (m_data.eventIndex == BONUS_EVENT)
	{
		const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::instance().GetClientSet();
		if (eventStatus)
		{
			for (auto it = c_ref_set.begin(); it != c_ref_set.end(); ++it)
			{
				LPCHARACTER ch = (*it)->GetCharacter();
				if (!ch)
					continue;

				if (m_data.empireFlag != 0)
					if (m_data.empireFlag != ch->GetEmpire())
						continue;

				ch->ComputePoints();
			}
		}
		else
		{
			for (auto it = c_ref_set.begin(); it != c_ref_set.end(); ++it)
			{
				LPCHARACTER ch = (*it)->GetCharacter();
				if (!ch)
					continue;
				if (m_data.empireFlag != 0)
					if (m_data.empireFlag != ch->GetEmpire())
						continue;
				long value = m_data.value[1];
				ch->ApplyPoint(m_data.value[0], -value);
				ch->ComputePoints();
			}
		}
	}
}
void CHARACTER_MANAGER::SetEventData(BYTE dayIndex, const std::vector<TEventManagerData>& m_data)
{
	auto it = m_eventData.find(dayIndex);
	if (it != m_eventData.end())
	{
		it->second.clear();
		for (DWORD j = 0; j < m_data.size(); ++j)
			it->second.emplace_back(m_data[j]);
	}
	else
	{
		m_eventData.emplace(dayIndex, m_data);
	}
}
#endif
