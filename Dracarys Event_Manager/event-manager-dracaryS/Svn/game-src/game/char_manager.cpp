
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
void CHARACTER_MANAGER::CheckBonusEvent(LPCHARACTER ch)
{
	const TEventManagerData* eventPtr = CheckEventIsActive(BONUS_EVENT, ch->GetEmpire());
	if (eventPtr)
		ch->ApplyPoint(eventPtr->value[0], eventPtr->value[1]);
}
const TEventManagerData* CHARACTER_MANAGER::CheckEventIsActive(BYTE eventIndex, BYTE empireIndex)
{
	const time_t cur_Time = time(NULL);
	const struct tm vKey = *localtime(&cur_Time);

	for (const auto& [dayIndex, dayVector] : m_eventData)
	{
		for (const auto& eventData : dayVector)
		{
			if (eventData.eventIndex == eventIndex)
			{
				if (eventData.channelFlag != 0)
					if (eventData.channelFlag != g_bChannel)
						continue;
				if (eventData.empireFlag != 0 && empireIndex != 0)
					if (eventData.empireFlag != empireIndex)
						continue;

				if(eventData.eventStatus == true)
					return &eventData;
				//if (cur_Time >= eventData.startTime && cur_Time <= eventData.endTime)
				//	return &eventData;
			}
		}
	}
	return NULL;
}
void CHARACTER_MANAGER::CheckEventForDrop(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM>& vec_item)
{
	const BYTE killerEmpire = pkKiller->GetEmpire();
	const TEventManagerData* eventPtr = NULL;
	LPITEM rewardItem = NULL;

	if (pkChr->IsStone())
	{
		eventPtr = CheckEventIsActive(DOUBLE_METIN_LOOT_EVENT, killerEmpire);
		if (eventPtr)
		{
			const int prob = number(1, 100);
			const int success_prob = eventPtr->value[3];
			if (prob < success_prob)
			{
				std::vector<LPITEM> m_cache;
				for (const auto& vItem : vec_item)
				{
					rewardItem = ITEM_MANAGER::Instance().CreateItem(vItem->GetVnum(), vItem->GetCount(), 0, true);
					if (rewardItem) m_cache.emplace_back(rewardItem);
				}
				for (const auto& rItem : m_cache)
					vec_item.emplace_back(rItem);
			}
		}
	}
	else if (pkChr->GetMobRank() >= MOB_RANK_BOSS)
	{
		eventPtr = CheckEventIsActive(DOUBLE_BOSS_LOOT_EVENT, killerEmpire);
		if (eventPtr)
		{
			const int prob = number(1, 100);
			const int success_prob = eventPtr->value[3];
			if (prob < success_prob)
			{
				std::vector<LPITEM> m_cache;
				for (const auto& vItem : vec_item)
				{
					rewardItem = ITEM_MANAGER::Instance().CreateItem(vItem->GetVnum(), vItem->GetCount(), 0, true);
					if (rewardItem) m_cache.emplace_back(rewardItem);
				}
				for (const auto& rItem : m_cache)
					vec_item.emplace_back(rItem);
			}
		}
	}

	eventPtr = CheckEventIsActive(DOUBLE_MISSION_BOOK_EVENT, killerEmpire);
	if (eventPtr)
	{
		const int prob = number(1, 100);
		const int success_prob = eventPtr->value[3];
		if (prob < success_prob)
		{
			// If you have different book index put here!
			constexpr DWORD m_lbookItems[] = { 50300, 50301, 50302 };
			std::vector<LPITEM> m_cache;
			for (const auto& vItem : vec_item)
			{
				const DWORD itemVnum = vItem->GetVnum();
				for (const auto& missionBook : m_lbookItems)
				{
					if (missionBook == itemVnum)
					{
						rewardItem = ITEM_MANAGER::Instance().CreateItem(itemVnum, vItem->GetCount(), 0, true);
						if (rewardItem) m_cache.emplace_back(rewardItem);

						break;
					}
				}
				for (const auto& rItem : m_cache)
					vec_item.emplace_back(rItem);
			}
		}
	}

	eventPtr = CheckEventIsActive(DUNGEON_TICKET_LOOT_EVENT, killerEmpire);
	if (eventPtr)
	{
		const int prob = number(1, 100);
		const int success_prob = eventPtr->value[3];
		if (prob < success_prob)
		{
			// If you have different book index put here!
			constexpr DWORD m_lticketItems[] = { 71201 };
			std::vector<LPITEM> m_cache;
			for (const auto& vItem : vec_item)
			{
				const DWORD itemVnum = vItem->GetVnum();
				for (const auto& ticketItem : m_lticketItems)
				{
					if (ticketItem == itemVnum)
					{
						rewardItem = ITEM_MANAGER::Instance().CreateItem(itemVnum, vItem->GetCount(), 0, true);
						if (rewardItem) m_cache.emplace_back(rewardItem);

						break;
					}
				}
				for (const auto& rItem : m_cache)
					vec_item.emplace_back(rItem);
			}
		}
	}
	eventPtr = CheckEventIsActive(MOONLIGHT_EVENT, killerEmpire);
	if (eventPtr)
	{
		const int prob = number(1, 100);
		const int success_prob = eventPtr->value[3];
		if (prob < success_prob)
		{
			// If your moonlight item vnum is different change 50011!
			LPITEM item = ITEM_MANAGER::Instance().CreateItem(50011, 1, 0, true);
			if (item) vec_item.emplace_back(item);
		}
	}
}
void CHARACTER_MANAGER::CompareEventSendData(TEMP_BUFFER* buf)
{
	const BYTE dayCount = m_eventData.size();
	const BYTE subIndex = EVENT_MANAGER_LOAD;
	const int cur_Time = time(NULL);
	TPacketGCEventManager p;
	p.header = HEADER_GC_EVENT_MANAGER;
	p.size = sizeof(TPacketGCEventManager) + sizeof(BYTE)+sizeof(BYTE)+sizeof(int);
	for (const auto& [dayIndex, dayData] : m_eventData)
	{
		const BYTE dayEventCount = dayData.size();
		p.size += sizeof(BYTE) + sizeof(BYTE) + (dayEventCount * sizeof(TEventManagerData));
	}
	buf->write(&p, sizeof(TPacketGCEventManager));
	buf->write(&subIndex, sizeof(BYTE));
	buf->write(&dayCount, sizeof(BYTE));
	buf->write(&cur_Time, sizeof(int));
	for (const auto& [dayIndex, dayData] : m_eventData)
	{
		const BYTE dayEventCount = dayData.size();
		buf->write(&dayIndex, sizeof(BYTE));
		buf->write(&dayEventCount, sizeof(BYTE));
		if (dayEventCount > 0)
			buf->write(dayData.data(), dayEventCount * sizeof(TEventManagerData));
	}
}
void CHARACTER_MANAGER::UpdateAllPlayerEventData()
{
	TEMP_BUFFER buf;
	CompareEventSendData(&buf);
	const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::instance().GetClientSet();
	for (const auto& desc : c_ref_set)
	{
		if (!desc->GetCharacter())
			continue;
		desc->Packet(buf.read_peek(), buf.size());
	}
}
void CHARACTER_MANAGER::SendDataPlayer(LPCHARACTER ch)
{
	auto desc = ch->GetDesc();
	if (!desc)
		return;
	TEMP_BUFFER buf;
	CompareEventSendData(&buf);
	desc->Packet(buf.read_peek(), buf.size());
}
bool CHARACTER_MANAGER::CloseEventManuel(BYTE eventIndex)
{
	auto eventPtr = CheckEventIsActive(eventIndex);
	if (eventPtr != NULL)
	{
		const BYTE subHeader = EVENT_MANAGER_REMOVE_EVENT;
		db_clientdesc->DBPacketHeader(HEADER_GD_EVENT_MANAGER, 0, sizeof(BYTE)+sizeof(WORD));
		db_clientdesc->Packet(&subHeader, sizeof(BYTE));
		db_clientdesc->Packet(&eventPtr->eventID, sizeof(WORD));
		return true;
	}
	return false;
}
void CHARACTER_MANAGER::SetEventStatus(const WORD eventID, const bool eventStatus, const int endTime)
{
	//eventStatus - 0-deactive  // 1-active

	TEventManagerData* eventData = NULL;
	for (auto it = m_eventData.begin(); it != m_eventData.end(); ++it)
	{
		if (it->second.size())
		{
			for (DWORD j = 0; j < it->second.size(); ++j)
			{
				TEventManagerData& pData = it->second[j];
				if (pData.eventID == eventID)
				{
					eventData = &pData;
					break;
				}
			}
		}
	}
	if (eventData == NULL)
		return;
	eventData->eventStatus = eventStatus;
	eventData->endTime = endTime;

	// Auto open&close notice
	const std::map<BYTE, std::pair<std::string, std::string>> m_eventText = {
		{BONUS_EVENT,{"761","762"}},
		{DOUBLE_BOSS_LOOT_EVENT,{"763","764"}},
		{DOUBLE_METIN_LOOT_EVENT,{"765","766"}},
		{DOUBLE_MISSION_BOOK_EVENT,{"767","768"}},
		{DUNGEON_COOLDOWN_EVENT,{"769","770"}},
		{DUNGEON_TICKET_LOOT_EVENT,{"771","772"}},
		{MOONLIGHT_EVENT,{"773","774"}},
	};

	const auto it = m_eventText.find(eventData->eventIndex);
	if (it != m_eventText.end())
	{
		if (eventStatus)
			SendNotice(false, it->second.first.c_str());
		else
			SendNotice(false, it->second.second.c_str());
	}

	const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::instance().GetClientSet();

	// Bonus event update status
	if (eventData->eventIndex == BONUS_EVENT)
	{
		for (const auto& desc : c_ref_set)
		{
			LPCHARACTER ch = desc->GetCharacter();
			if (!ch)
				continue;
			if (eventData->empireFlag != 0)
				if (eventData->empireFlag != ch->GetEmpire())
					continue;
			if (eventData->channelFlag != 0)
				if (eventData->channelFlag != g_bChannel)
					return;
			if (!eventStatus)
			{
				const long value = eventData->value[1];
				ch->ApplyPoint(eventData->value[0], -value);
			}
			ch->ComputePoints();
		}
	}

	const int now = time(0);
	const BYTE subIndex = EVENT_MANAGER_EVENT_STATUS;
	
	TPacketGCEventManager p;
	p.header = HEADER_GC_EVENT_MANAGER;
	p.size = sizeof(TPacketGCEventManager)+sizeof(BYTE)+sizeof(WORD)+sizeof(bool)+sizeof(int)+sizeof(int);
	
	TEMP_BUFFER buf;
	buf.write(&p, sizeof(TPacketGCEventManager));
	buf.write(&subIndex, sizeof(BYTE));
	buf.write(&eventData->eventID, sizeof(WORD));
	buf.write(&eventData->eventStatus, sizeof(bool));
	buf.write(&eventData->endTime, sizeof(int));
	buf.write(&now, sizeof(int));

	for (const auto& desc : c_ref_set)
	{
		if (!desc->GetCharacter())
			continue;
		desc->Packet(buf.read_peek(), buf.size());
	}

}
void CHARACTER_MANAGER::SetEventData(BYTE dayIndex, const std::vector<TEventManagerData>& m_data)
{
	const auto it = m_eventData.find(dayIndex);
	if (it == m_eventData.end())
		m_eventData.emplace(dayIndex, m_data);
	else
	{
		it->second.clear();
		for (const auto& newEvents : m_data)
			it->second.emplace_back(newEvents);
	}
}
#endif
