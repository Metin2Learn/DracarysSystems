#include "stdafx.h"
#include "pvp_duel.h"
#include "char.h"
#include "desc.h"
#include "char_manager.h"
#include "buffer_manager.h"
#include "sectree_manager.h"
#include "utils.h"
#include "config.h"
#include "pvp.h"
#include "vector.h"
#include "quest.h"
#include "questmanager.h"
#include "item.h"
#include "party.h"

void CPvPDuel::Login(LPCHARACTER ch)
{
	if (ch->GetMapIndex() != PVP_DUEL_MAP_INDEX)
		return;

	if (GetFlag("event_is_active") != 1 && !ch->IsGM())
	{
		ch->GoHome();
		return;
	}

	auto party = ch->GetParty();
	if (party)
	{
		if(ch->GetPlayerID() == party->GetLeaderPID())
			CPartyManager::instance().DeleteParty(party);
		else
			party->Quit(ch->GetPlayerID());
	}

	const auto it = std::find(m_vec_PlayerList.begin(), m_vec_PlayerList.end(), ch);
	if (it == m_vec_PlayerList.end())
		m_vec_PlayerList.emplace_back(ch);

	UpdatePvPData(PVP_DATA_UPDATE, 0, ch);
}
void CPvPDuel::Logout(LPCHARACTER ch)
{
	if (ch->GetMapIndex() != PVP_DUEL_MAP_INDEX)
		return;

	DonePvPDuel(ch, PVP_DUEL_LEFT_TYPE_LOGOUT);

	const auto it = std::find(m_vec_PlayerList.begin(), m_vec_PlayerList.end(), ch);
	if (it != m_vec_PlayerList.end())
		m_vec_PlayerList.erase(it);
}

CPvPDuel::CPvPDuel(){Destroy();}
CPvPDuel::~CPvPDuel(){Destroy();}

void CPvPDuel::Destroy()
{
	m_llMaxBet = 0;
	m_map_pvpFlags.clear();
	m_vec_PlayerList.clear();
	m_vec_pvpRegisterList.clear();
	m_map_pvpList.clear();
	if (processEvent)
		event_cancel(&processEvent);
	processEvent = NULL;
}

void CPvPDuel::DefaultSettings()
{
	Destroy();
	SetFlag("register_max_time", PVP_DUEL_DEFAULT_REGISTER_TIME);
	SetFlag("register_count_max", PVP_DUEL_DEFAULT_REGISTER_COUNT_MAX);
	SetFlag("pvp_min_level", PVP_DUEL_DEFAULT_MIN_LEVEL);
	SetFlag("pvp_max_level", PVP_DUEL_DEFAULT_MAX_LEVEL);
	SetFlag("pvp_bet", PVP_DUEL_DEFAULT_PVP_BET);
	SetFlag("pvp_for_job", 0);
}

void CPvPDuel::ClosePvP()
{
	DefaultSettings();
	SendOut();
}

void CPvPDuel::StartPvP(const BYTE arenaIndex)
{
	const auto it = m_map_pvpList.find(arenaIndex);
	if (it == m_map_pvpList.end())
		return;
	LPCHARACTER pkKiller = CHARACTER_MANAGER::Instance().FindByPID(it->second.first.pid);
	if (pkKiller)
	{
		LPCHARACTER pkVictim = CHARACTER_MANAGER::Instance().FindByPID(it->second.second.pid);
		if (pkVictim)
		{
			if (pkKiller->GetEmpire() == pkVictim->GetEmpire())
			{
				CPVPManager::Instance().Insert(pkKiller, pkVictim);
				CPVPManager::Instance().Insert(pkVictim, pkKiller);
			}
			RemoveDuelAffect(pkKiller);
			RemoveDuelAffect(pkVictim);
		}
	}
}

void CPvPDuel::SendOut(bool isStart)
{
	if (isStart)
	{
		SetFlag("event_send_out", time(0) + PVP_DUEL_DONE_SEND_OUT_TIME);
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO, 2062, "", PVP_DUEL_DONE_SEND_OUT_TIME);
#endif
		//Notice(LC_TEXT("1003"), PVP_DUEL_DONE_SEND_OUT_TIME);
	}
	else
	{
		for (const auto& ch : m_vec_PlayerList)
		{
			if (ch->IsGM())
				continue;
			ch->GoHome();
		}
		processEvent = NULL;
	}
}


EVENTINFO(empty_event_info){char pvpEvent;};
EVENTFUNC(pvp_duel_event)
{
	const empty_event_info* info = dynamic_cast<empty_event_info*>(event->info);
	if (info == NULL)
		return 0;
	CPvPDuel& pvpDuel = CPvPDuel::Instance();
	const int now = get_global_time();

	const int sendOutTime = pvpDuel.GetFlag("event_send_out");
	if (sendOutTime != 0 && now > sendOutTime)
	{
		pvpDuel.SetFlag("event_send_out", 0);
		pvpDuel.SendOut(false);
		return 0;
	}

	const int registerTime = pvpDuel.GetFlag("register_time");
	if (registerTime != 0 && now > registerTime)
	{
		pvpDuel.SetFlag("register_time", 0);
		pvpDuel.SendInfoNotice(true);
		pvpDuel.ComparePvP();
	}

	for (BYTE j = 1; j <= PVP_DUEL_POS_COUNT; ++j)
	{
		const int posTime = pvpDuel.GetFlag("pvp_%d_pos", j);
		if (posTime != 0 && now > posTime)
		{
			pvpDuel.SetFlag("pvp_%d_pos", 0, j);
			const auto firstPlayer = pvpDuel.GetPvPData(j, 1);
			const auto secondPlayer = pvpDuel.GetPvPData(j, 2);
			if(firstPlayer->win == 0 && secondPlayer->win == 0)
				pvpDuel.SetFlag("pvp_%d_start", now+ PVP_DUEL_FIRST_WAIT_TIME, j);
			else
				pvpDuel.SetFlag("pvp_%d_start", now+ PVP_DUEL_WAIT_TIME, j);
			pvpDuel.UpdatePvPData(PVP_DATA_START_TIME, j);
			pvpDuel.SetPvPPos(j);
		}

		const int startTime = pvpDuel.GetFlag("pvp_%d_start", j);
		if (startTime != 0 && now > startTime)
		{
			pvpDuel.SetFlag("pvp_%d_start", 0, j);
			pvpDuel.SetFlag("pvp_%d_fighthing", 1, j);
			pvpDuel.StartPvP(j);
		}
	}
	return PASSES_PER_SEC(1);
}

void CPvPDuel::SendInfoNotice(bool isStartText)
{
	char noticeText[256];
	if (!isStartText)
	{
		int registerTime = (GetFlag("register_time") - get_global_time()) / 60;
#ifdef TEXTS_IMPROVEMENT
		snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,1004, "", registerTime, GetFlag("register_count_max"));
#endif
		//snprintf(noticeText, sizeof(noticeText), LC_TEXT("1004"), registerTime, GetFlag("register_count_max"));
		BroadcastNotice(false, noticeText);

		if (GetFlag("pvp_for_job") != 0 && GetFlag("pvp_for_job") >= 1 && GetFlag("pvp_for_job") <= 4)
#ifdef TEXTS_IMPROVEMENT
			snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2064, "", jobNames[GetFlag("pvp_for_job") - 1]);
#endif
			//snprintf(noticeText, sizeof(noticeText), LC_TEXT("1005"), jobNames[GetFlag("pvp_for_job") - 1]);
		else
#ifdef TEXTS_IMPROVEMENT
			snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2065, "");
#endif
			//snprintf(noticeText, sizeof(noticeText), LC_TEXT("1006"));
		BroadcastNotice(false, noticeText);
		
#ifdef TEXTS_IMPROVEMENT
		if (GetFlag("pvp_bet") != 0)
			snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2066, "", GetFlag("pvp_bet"));
		else
			snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2067, "");
#endif

//		if (GetFlag("pvp_bet") != 0)
//			snprintf(noticeText, sizeof(noticeText), LC_TEXT("1007"), GetFlag("pvp_bet"));
//		else
//			snprintf(noticeText, sizeof(noticeText), LC_TEXT("1008"));
		
		BroadcastNotice(false, noticeText);
#ifdef TEXTS_IMPROVEMENT
		snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2068, "");
#endif
		//snprintf(noticeText, sizeof(noticeText), LC_TEXT("1009"));
		BroadcastNotice(false, noticeText);
	}
	else
	{
#ifdef TEXTS_IMPROVEMENT
		snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2069, "", m_vec_pvpRegisterList.size(), GetFlag("register_count_max"));
#endif
		//snprintf(noticeText, sizeof(noticeText), LC_TEXT("1010"), m_vec_pvpRegisterList.size(), GetFlag("register_count_max"));
		BroadcastNotice(false, noticeText);
		const auto totalBet = GetFlag("pvp_bet") > 0 ? m_llMaxBet : 0;
		if (totalBet > 0)
		{
#ifdef TEXTS_IMPROVEMENT
			snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2070, "", totalBet);
#endif
			//snprintf(noticeText, sizeof(noticeText), LC_TEXT("1011"), totalBet);
			BroadcastNotice(false, noticeText);
		}
#ifdef TEXTS_IMPROVEMENT
		snprintf(noticeText, sizeof(noticeText), CHAT_TYPE_INFO,2071, "");
#endif
		//snprintf(noticeText, sizeof(noticeText), LC_TEXT("1012"));
		BroadcastNotice(false, noticeText);
	}
}

void CPvPDuel::StartProcess(LPCHARACTER ch)
{
	if (!ch->IsGM())
		return;

	if (GetFlag("event_is_active") == 1)
	{
#ifdef TEXTS_IMPROVEMENT
		ch->ChatPacketnew(CHAT_TYPE_INFO,2073, "");
#endif
		//ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1013"));
		return;
	}

	SetFlag("pvp_state", 0);

	for (BYTE j = 1; j <= PVP_DUEL_POS_COUNT; ++j)
	{
		SetFlag("pvp_%d_start", 0, j);
		SetFlag("pvp_%d_pos", 0, j);
		SetFlag("pvp_%d_fighthing", 0, j);
	}

	if (GetFlag("register_max_time") == 0)
	{
#ifdef TEXTS_IMPROVEMENT
		ch->ChatPacketnew(CHAT_TYPE_INFO,2073, "");
#endif
		//ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1014"));
		return;
	}
	else if (GetFlag("register_count_max") == 0)
	{
#ifdef TEXTS_IMPROVEMENT
		ch->ChatPacketnew(CHAT_TYPE_INFO,2074, "");
#endif
		//ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1015"));
		return;
	}
	else if (GetFlag("pvp_min_level") == 0)
	{
#ifdef TEXTS_IMPROVEMENT
		ch->ChatPacketnew(CHAT_TYPE_INFO,2075, "");
#endif
		//ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1016"));
		return;
	}
	else if (GetFlag("pvp_max_level") == 0)
	{
#ifdef TEXTS_IMPROVEMENT
		ch->ChatPacketnew(CHAT_TYPE_INFO,2076, "");
#endif
		//ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1017"));
		return;
	}

	quest::CQuestManager::instance().RequestSetEventFlag("pvp_duel_active", 1);

	SetFlag("register_time", time(0)+GetFlag("register_max_time"));

	SetFlag("event_is_active", 1);
	UpdatePvPData(PVP_DATA_DELETE);
	SendInfoNotice();
	if (processEvent)
		event_cancel(&processEvent);

	processEvent = event_create(pvp_duel_event, AllocEventInfo<empty_event_info>(), PASSES_PER_SEC(0));
}

void CPvPDuel::ComparePvP()
{
	for (BYTE j = 1; j <= PVP_DUEL_POS_COUNT; ++j)
	{
		SetFlag("pvp_%d_start", 0, j);
		SetFlag("pvp_%d_pos", 0, j);
		SetFlag("pvp_%d_fighthing", 0, j);
	}

	if (m_vec_pvpRegisterList.size() <= 1)
	{
		UpdatePvPData(PVP_DATA_UPDATE);
		DonePvP(PVP_DUEL_NOT_HAVE_ENOUGHT_REGISTER);
		return;
	}

	ComparePvPList();

	const int totalPvPCount = m_vec_pvpRegisterList.size();
	if (totalPvPCount <= 1)
		DonePvP();
	else if (totalPvPCount == 2)//final
	{
		SetFlag("pvp_state", 3);
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2077, "", PVP_DUEL_WAIT_TIME);
#endif
		//Notice(LC_TEXT("1018"), PVP_DUEL_WAIT_TIME);
	}
	else if (totalPvPCount >= 3 && totalPvPCount <= 4)//semi-final
	{
		SetFlag("pvp_state", 2);
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2078, "", PVP_DUEL_WAIT_TIME);
#endif
		//Notice(LC_TEXT("1019"), PVP_DUEL_WAIT_TIME);
	}
	else if (totalPvPCount >= 5 && totalPvPCount <=8)//quarter-final
	{
		SetFlag("pvp_state", 1);
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2079, "", PVP_DUEL_WAIT_TIME);
#endif
		//Notice(LC_TEXT("1020"), PVP_DUEL_WAIT_TIME);
	}
	else
	{
		SetFlag("pvp_state", 0);
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2080, "", PVP_DUEL_WAIT_TIME);
#endif
		//Notice(LC_TEXT("1021"), PVP_DUEL_WAIT_TIME);
	}

	for (BYTE j = 1; j <= PVP_DUEL_POS_COUNT; ++j)
	{
		const auto it = m_map_pvpList.find(j);
		if (it != m_map_pvpList.end())
			SetFlag("pvp_%d_pos", get_global_time() + PVP_DUEL_POS_SEND_TIME, j);
	}

	UpdatePvPData(PVP_DATA_UPDATE);
}

void CPvPDuel::Dead(LPCHARACTER pkKiller, LPCHARACTER pkVictim, BYTE winCount)
{
	const int pvpArenaIndex = IsFighting(pkKiller);
	if (pvpArenaIndex <= 0 || pvpArenaIndex > PVP_DUEL_POS_COUNT)
		return;
	const auto it = m_map_pvpList.find(pvpArenaIndex);
	if (it == m_map_pvpList.end())
		return;
	else if (it->second.first.pid != pkVictim->GetPlayerID() && it->second.second.pid != pkVictim->GetPlayerID())
		return;

	pvp_data* killerPlayer = it->second.first.pid == pkKiller->GetPlayerID() ? &it->second.first : &it->second.second;
	const pvp_data* victimPlayer = it->second.first.pid == pkVictim->GetPlayerID() ? &it->second.first : &it->second.second;

	if (!killerPlayer || !victimPlayer)
		return;

	killerPlayer->win += winCount;

	if (GetMaxRount() == killerPlayer->win)
	{
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2081, "", pkKiller->GetName(), killerPlayer->win, victimPlayer->win, pkVictim->GetName(), pkKiller->GetName());
#endif
		//Notice(LC_TEXT("1022"), pkKiller->GetName(), killerPlayer->win, victimPlayer->win, pkVictim->GetName(), pkKiller->GetName());
		DonePvPDuel(pkVictim);
	}
	else
	{
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2082, "", pkKiller->GetName(), killerPlayer->win, victimPlayer->win, pkVictim->GetName(), PVP_DUEL_WAIT_TIME);
#endif
		//Notice(LC_TEXT("1023"), pkKiller->GetName(), killerPlayer->win, victimPlayer->win, pkVictim->GetName(), PVP_DUEL_WAIT_TIME);
		SetFlag("pvp_%d_pos", get_global_time() + PVP_DUEL_POS_SEND_TIME_AFTER_DEAD, pvpArenaIndex);
		UpdatePvPData(PVP_DATA_UPDATE_SCORE, pvpArenaIndex);
	}
}

void CPvPDuel::DonePvP(BYTE doneIndex)
{
	if (doneIndex == PVP_DUEL_DONE_WITH_WINNER)
	{
		if (m_vec_pvpRegisterList.size() == 1)
		{
			const auto it = m_vec_pvpRegisterList.begin();
			if (it != m_vec_pvpRegisterList.end())
			{
				LPCHARACTER pkWinner = CHARACTER_MANAGER::Instance().FindByPID(*it);
				if (pkWinner != NULL)
				{
					const auto betPrice = GetFlag("pvp_bet") > 0 ? m_llMaxBet : 0;
					if (betPrice > 0)
					{
#ifdef TEXTS_IMPROVEMENT
						Notice(CHAT_TYPE_INFO,2083, "", pkWinner->GetName(), betPrice);
#endif
						//Notice(LC_TEXT("1024"), pkWinner->GetName(), betPrice);
						pkWinner->PointChange(POINT_GOLD, betPrice);
						m_llMaxBet = 0;
					}
					else
#ifdef TEXTS_IMPROVEMENT
						Notice(CHAT_TYPE_INFO,2084, "", pkWinner->GetName());
#endif
						//Notice(LC_TEXT("1025"), pkWinner->GetName());
				}
			}
		}
	}
	else if (doneIndex == PVP_DUEL_CLOSE_FROM_GM)
	{
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2085, "");
#endif
		//Notice(LC_TEXT("1026"));
		for (BYTE i = 1; i <= PVP_DUEL_POS_COUNT; ++i)
			SetPvPBase(i);
	}
	else if (doneIndex == PVP_DUEL_NOT_HAVE_ENOUGHT_REGISTER)
	{
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2086, "");
#endif
		//Notice(LC_TEXT("1027"));
	}

	quest::CQuestManager::instance().RequestSetEventFlag("pvp_duel_active", 0);
	
	if (processEvent)
		event_cancel(&processEvent);

	processEvent = event_create(pvp_duel_event, AllocEventInfo<empty_event_info>(), PASSES_PER_SEC(0));

	SetFlag("event_is_active", 0);
	SetFlag("event_send_out", time(0) + PVP_DUEL_DONE_SEND_OUT_TIME);
#ifdef TEXTS_IMPROVEMENT
	Notice(CHAT_TYPE_INFO,2062, "", PVP_DUEL_DONE_SEND_OUT_TIME);
#endif
	//Notice(LC_TEXT("1003"), PVP_DUEL_DONE_SEND_OUT_TIME);
	m_vec_pvpRegisterList.clear();
}

void CPvPDuel::DonePvPDuel(LPCHARACTER pkVictim, BYTE leftType)
{
	if (!pkVictim)
		return;

	RemoveDuelAffect(pkVictim);

	const DWORD victimPID = pkVictim->GetPlayerID();
	LPCHARACTER chWinner = NULL;

	const auto it = std::find(m_vec_pvpRegisterList.begin(), m_vec_pvpRegisterList.end(), victimPID);
	if (it != m_vec_pvpRegisterList.end())
		m_vec_pvpRegisterList.erase(it);

	if (leftType == PVP_DUEL_LEFT_TYPE_GM)
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2087, "", pkVictim->GetName());
#endif
		//Notice(LC_TEXT("1028"), pkVictim->GetName());

	const int pvpArenaIndex = IsFighting(pkVictim);
	const auto itPvP = m_map_pvpList.find(pvpArenaIndex);
	if (itPvP == m_map_pvpList.end())
	{
		// Check Cache PvP List!
		const int pvpArenaCacheIndex = IsFighting(pkVictim, true);
		const auto itPvPCache = m_map_pvpCacheList.find(pvpArenaCacheIndex);
		if (itPvPCache != m_map_pvpCacheList.end())
		{
			const auto pvpCachePair = itPvPCache->second;
			chWinner = CHARACTER_MANAGER::Instance().FindByPID(pvpCachePair.first.pid == victimPID ? pvpCachePair.second.pid : pvpCachePair.first.pid);
			m_map_pvpCacheList.erase(itPvPCache->first);
			if (chWinner == NULL)
				return;
#ifdef TEXTS_IMPROVEMENT
			Notice(CHAT_TYPE_INFO,2088, "", pkVictim->GetName(), chWinner->GetName());
#endif
			//Notice(LC_TEXT("1029"), pkVictim->GetName(), chWinner->GetName());
		}
		return;
	}

	SetFlag("pvp_%d_fighthing", 0, pvpArenaIndex);

	const auto pvpPair = itPvP->second;
	chWinner =  CHARACTER_MANAGER::Instance().FindByPID(pvpPair.first.pid == victimPID ? pvpPair.second.pid : pvpPair.first.pid);
	if (chWinner == NULL)
		return;

	RemoveDuelAffect(chWinner);

	if (leftType != 0)
	{
		if(pkVictim->GetEmpire() == chWinner->GetEmpire())
			CPVPManager::Instance().RemoveCharactersPvP(pkVictim, chWinner);
	}
		
	if (leftType == PVP_DUEL_LEFT_TYPE_LOGOUT)
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2088, "", pkVictim->GetName(), chWinner->GetName());
#endif
		//Notice(LC_TEXT("1029"), pkVictim->GetName(), chWinner->GetName());

	SetPvPBase(pvpArenaIndex);
	UpdatePvPData(PVP_DATA_DELETE, pvpArenaIndex);
	m_map_pvpList.erase(pvpArenaIndex);

	if (m_vec_pvpRegisterList.size() <= 1)
		DonePvP();
	else
	{
		if (m_map_pvpList.size() == 0)
		{
			if (m_vec_pvpRegisterList.size() == 2 || m_vec_pvpRegisterList.size() == 4 || m_vec_pvpRegisterList.size() == 8)
				ComparePvP();
			else if (m_map_pvpCacheList.size())
			{
				const auto itFirst = m_map_pvpCacheList.begin();
				if (itFirst != m_map_pvpCacheList.end())
				{
					m_map_pvpList.emplace(pvpArenaIndex, itFirst->second);
					m_map_pvpCacheList.erase(itFirst->first);
					SetFlag("pvp_%d_pos", get_global_time() + PVP_DUEL_POS_SEND_TIME, pvpArenaIndex);
					UpdatePvPData(PVP_DATA_UPDATE, pvpArenaIndex);
				}
			}
			else
				ComparePvP();
		}
	}
}

void CPvPDuel::ComparePvPList()
{
	m_map_pvpList.clear();
	m_map_pvpCacheList.clear();

	if (m_vec_pvpRegisterList.size() > 1)
	{
		while (true)
		{
			const short randomFirst = number(0, m_vec_pvpRegisterList.size() - 1);
			const DWORD firstPlayer = m_vec_pvpRegisterList[randomFirst];
			if (IsFighting(firstPlayer) != -1)
				continue;
			const short randomSecond = number(0, m_vec_pvpRegisterList.size() - 1);
			const DWORD secondPlayer = m_vec_pvpRegisterList[randomSecond];
			if (IsFighting(secondPlayer) != -1)
				continue;
			else if (firstPlayer == secondPlayer)
				continue;
			pvp_data first;
			first.pid = firstPlayer;
			first.win = 0;
			pvp_data second;
			second.pid = secondPlayer;
			second.win = 0;
			if (m_map_pvpList.size() >= PVP_DUEL_POS_COUNT)
				m_map_pvpCacheList.emplace(m_map_pvpCacheList.size(), std::make_pair(first, second));
			else
				m_map_pvpList.emplace(m_map_pvpList.size() + 1, std::make_pair(first, second));
			if (m_vec_pvpRegisterList.size()/2 == m_map_pvpList.size()+ m_map_pvpCacheList.size())
				break;
		}
	}

	for (const auto playerID : m_vec_pvpRegisterList)
	{
		if (IsFighting(playerID) != -1)
			continue;
		while (true)
		{
			const short randomFirst = number(0, m_vec_pvpRegisterList.size() - 1);
			const DWORD firstPlayer = m_vec_pvpRegisterList[randomFirst];
			if (firstPlayer == playerID)
				continue;
			pvp_data first;
			first.pid = firstPlayer;
			first.win = 0;
			pvp_data second;
			second.pid = playerID;
			second.win = 0;
			m_map_pvpCacheList.emplace(m_map_pvpCacheList.size(), std::make_pair(first, second));
			break;
		}
	}
}

void CPvPDuel::SetPvPBase(LPCHARACTER ch)
{
	Show(ch, (long)pvpBasePosition[0], (long)pvpBasePosition[1]);
}

void CPvPDuel::SetPvPBase(const BYTE arenaIndex)
{
	const auto it = m_map_pvpList.find(arenaIndex);
	if (it == m_map_pvpList.end())
		return;
	const auto pvpPair = it->second;
	LPCHARACTER pkKiller = CHARACTER_MANAGER::Instance().FindByPID(pvpPair.first.pid);
	if (pkKiller)
	{
		LPCHARACTER pkVictim = CHARACTER_MANAGER::Instance().FindByPID(pvpPair.second.pid);
		if (pkVictim)
		{
			CheckReadyForDuel(pkKiller);
			CheckReadyForDuel(pkVictim);

			pkVictim->SetPvPTournament(false);
			pkKiller->SetPvPTournament(false);

			pkVictim->UpdateSectree();
			pkKiller->UpdateSectree();

			pkKiller->SetRotation(PVP_DUEL_BASE_ROTATION);
			pkVictim->SetRotation(PVP_DUEL_BASE_ROTATION);
			Show(pkKiller, (long)pvpBasePosition[0], (long)pvpBasePosition[1]);
			Show(pkVictim, (long)pvpBasePosition[0], (long)pvpBasePosition[1]);
		}
	}
}

void CPvPDuel::SetPvPPos(const BYTE arenaIndex)
{
	const auto it = m_map_pvpList.find(arenaIndex);
	if (it == m_map_pvpList.end())
		return;
	
	const auto pvpPair = it->second;
	LPCHARACTER pkKiller = CHARACTER_MANAGER::Instance().FindByPID(pvpPair.first.pid);
	if (pkKiller)
	{
		LPCHARACTER pkVictim = CHARACTER_MANAGER::Instance().FindByPID(pvpPair.second.pid);
		if (pkVictim)
		{
			pkVictim->SetPvPTournament(true);
			pkKiller->SetPvPTournament(true);

			pkVictim->UpdateSectree();
			pkKiller->UpdateSectree();

			CheckReadyForDuel(pkKiller);
			CheckReadyForDuel(pkVictim);

			pkKiller->SetRotation(PVP_DUEL_FIRST_PLAYER_ROTATION);
			pkVictim->SetRotation(PVP_DUEL_SECOND_PLAYER_ROTATION);
			Show(pkKiller, (long)pvpArenaPosition[arenaIndex - 1][0][0], (long)pvpArenaPosition[arenaIndex - 1][0][1]);
			Show(pkVictim, (long)pvpArenaPosition[arenaIndex - 1][1][0], (long)pvpArenaPosition[arenaIndex - 1][1][1]);

			AddDuelAffect(pkKiller);
			AddDuelAffect(pkVictim);
		}
	}
}

int CPvPDuel::Register(LPCHARACTER ch)
{
	if (!ch->IsPC())
		return 0;//unkown desc!
	else if (1 != GetFlag("event_is_active"))
		return 1;//event not active!
	else if (get_global_time() > GetFlag("register_time"))
		return 2;//register done!
	else if (m_vec_pvpRegisterList.size() >= GetFlag("register_count_max"))
		return 3;//max register
	else if (GetFlag("pvp_for_job") != 0 && !(GetFlag("pvp_for_job") - 1 == ch->GetJob()))
		return 4;//not same job!
	else if (ch->GetLevel() < GetFlag("pvp_min_level"))
		return 5;//lower level
	else if (ch->GetLevel() > GetFlag("pvp_max_level"))
		return 6;//bigger level
	else if (ch->GetMapIndex() != PVP_DUEL_MAP_INDEX)
		return 7;//not on pvp map!
	else if (ch->GetGold() < GetFlag("pvp_bet"))
		return 8;//not enought bet money

	const auto it = std::find(m_vec_pvpRegisterList.begin(), m_vec_pvpRegisterList.end(), ch->GetPlayerID());
	if (it != m_vec_pvpRegisterList.end())
		return 9;//already register!

	if (PVP_DUEL_BLOCK_MULTI_ACCOUNT == 1)
	{
		const std::string playerIP = ch->GetDesc()->GetHostName();
		for (const auto& registerPlayerPID : m_vec_pvpRegisterList)
		{
			const auto registerPlayer = CHARACTER_MANAGER::Instance().FindByPID(registerPlayerPID);
			if (registerPlayer)
			{
				const auto desc = registerPlayer->GetDesc();
				if (desc)
				{
					const std::string otherPlayer = desc->GetHostName();
					if (otherPlayer == playerIP)
						return 10;//already register with same ip!
				}
			}
		}
	}

	if (m_vec_pvpRegisterList.size() == GetFlag("register_count_max"))
#ifdef TEXTS_IMPROVEMENT
		Notice(CHAT_TYPE_INFO,2089, "");
#endif
		//Notice(LC_TEXT("1030"));

	const int betPrice = GetFlag("pvp_bet");
	if (betPrice > 0)
	{
		ch->PointChange(POINT_GOLD, -betPrice);
		if (!m_vec_pvpRegisterList.size())
			m_llMaxBet = betPrice;
		else
			m_llMaxBet += betPrice;
	}

	m_vec_pvpRegisterList.emplace_back(ch->GetPlayerID());
	return 99;
}

void CPvPDuel::UpdatePvPData(BYTE subHeader, BYTE arenaIndex, LPCHARACTER ch)
{
	if (ch && !ch->GetDesc())
		return;

	TPacketGCPvPInfo p;
	p.header = HEADER_GC_PVP_DUEL;
	TEMP_BUFFER buf;
	bool checkInPvPList = true;
	BYTE dataSize = m_map_pvpList.size();
	if (subHeader == PVP_DATA_UPDATE)
	{
		if (arenaIndex != 0)
			dataSize = 1;
		p.size = sizeof(TPacketGCPvPInfo) + sizeof(BYTE) + sizeof(BYTE) + (dataSize * (sizeof(BYTE) + sizeof(int)+sizeof(TPvPDuelData) + sizeof(TPvPDuelData)));
		buf.write(&p, sizeof(TPacketGCPvPInfo));
		buf.write(&subHeader, sizeof(BYTE));
		buf.write(&dataSize, sizeof(BYTE));
	}
	else if (subHeader == PVP_DATA_CLEAR_TARGET)
	{
		p.size = sizeof(TPacketGCPvPInfo) + sizeof(BYTE);
		buf.write(&p, sizeof(TPacketGCPvPInfo));
		buf.write(&subHeader, sizeof(BYTE));
		checkInPvPList = false;
	}
	else if (subHeader == PVP_DATA_DELETE)
	{
		p.size = sizeof(TPacketGCPvPInfo) + sizeof(BYTE) + sizeof(BYTE);
		buf.write(&p, sizeof(TPacketGCPvPInfo));
		buf.write(&subHeader, sizeof(BYTE));
		buf.write(&arenaIndex, sizeof(BYTE));
		checkInPvPList = false;
	}

	if (checkInPvPList)
	{
		for (const auto& [arenaKey, arenaPair] : m_map_pvpList)
		{
			if (subHeader == PVP_DATA_UPDATE_HP)
			{
				if (arenaKey == arenaIndex)
				{
					p.size = sizeof(TPacketGCPvPInfo) + sizeof(BYTE) + sizeof(BYTE) + ((sizeof(BYTE) + sizeof(int) + sizeof(int) + sizeof(bool)) * 2);

					buf.write(&p, sizeof(TPacketGCPvPInfo));
					buf.write(&subHeader, sizeof(BYTE));
					buf.write(&arenaKey, sizeof(BYTE));

					int playerHP = 0, playerMaxHP = 0;
					BYTE hpPercent = 0;
					bool isPoisoned = false;

					LPCHARACTER ch = CHARACTER_MANAGER::Instance().FindByPID(arenaPair.first.pid);
					if (ch)
					{
						playerHP = MINMAX(0, ch->GetHP(), ch->GetMaxHP());
						playerMaxHP = MINMAX(0, ch->GetMaxHP(), INT_MAX);
						hpPercent = MINMAX(0, (static_cast<long long>(playerHP * 100LL)) / playerMaxHP, 100);
						isPoisoned = ch->FindAffect(AFFECT_POISON) ? true : false;
					}

					buf.write(&hpPercent, sizeof(BYTE));
					buf.write(&playerHP, sizeof(int));
					buf.write(&playerMaxHP, sizeof(int));
					buf.write(&isPoisoned, sizeof(bool));

					playerHP = 0, playerMaxHP = 0;
					hpPercent = 0;
					isPoisoned = false;

					ch = CHARACTER_MANAGER::Instance().FindByPID(arenaPair.second.pid);
					if (ch)
					{
						playerHP = MINMAX(0, ch->GetHP(), ch->GetMaxHP());
						playerMaxHP = MINMAX(0, ch->GetMaxHP(), INT_MAX);
						hpPercent = MINMAX(0, (static_cast<long long>(playerHP * 100LL)) / playerMaxHP, 100);
						isPoisoned = ch->FindAffect(AFFECT_POISON) ? true : false;
					}

					buf.write(&hpPercent, sizeof(BYTE));
					buf.write(&playerHP, sizeof(int));
					buf.write(&playerMaxHP, sizeof(int));
					buf.write(&isPoisoned, sizeof(bool));
					break;
				}
			}
			else if (subHeader == PVP_DATA_START_TIME)
			{
				if (arenaKey == arenaIndex)
				{
					p.size = sizeof(TPacketGCPvPInfo) + sizeof(BYTE) + sizeof(BYTE) + sizeof(int);
					int startTime = GetFlag("pvp_%d_start", arenaKey);
					buf.write(&p, sizeof(TPacketGCPvPInfo));
					buf.write(&subHeader, sizeof(BYTE));
					buf.write(&arenaKey, sizeof(BYTE));
					buf.write(&startTime, sizeof(int));
					break;
				}
			}
			else if (subHeader == PVP_DATA_UPDATE)
			{
				if (arenaIndex != 0 && arenaIndex != arenaKey)
					continue;
				int startTime = GetFlag("pvp_%d_start", arenaKey);
				buf.write(&arenaKey, sizeof(BYTE));
				buf.write(&startTime, sizeof(int));
				TPvPDuelData playerData;
				memset(&playerData, 0, sizeof(playerData));
				LPCHARACTER ch = CHARACTER_MANAGER::Instance().FindByPID(arenaPair.first.pid);
				if (ch)
				{
					playerData.id = arenaPair.first.pid;
					playerData.race = ch->GetRaceNum();
					strlcpy(playerData.name, ch->GetName(), sizeof(playerData.name));
					playerData.minHP = MINMAX(0, ch->GetHP(), ch->GetMaxHP());
					playerData.maxHP = MINMAX(0, ch->GetMaxHP(), INT_MAX);
					playerData.percent = MINMAX(0, (static_cast<long long>(playerData.minHP * 100LL)) / playerData.maxHP, 100);
					playerData.score = arenaPair.first.win;
					playerData.isPoisoned = ch->FindAffect(AFFECT_POISON) ? true : false;
				}

				buf.write(&playerData, sizeof(TPvPDuelData));

				memset(&playerData, 0, sizeof(playerData));
				ch = CHARACTER_MANAGER::Instance().FindByPID(arenaPair.second.pid);
				if (ch)
				{
					playerData.id = arenaPair.second.pid;
					playerData.race = ch->GetRaceNum();
					strlcpy(playerData.name, ch->GetName(), sizeof(playerData.name));
					playerData.minHP = MINMAX(0, ch->GetHP(), ch->GetMaxHP());
					playerData.maxHP = MINMAX(0, ch->GetMaxHP(), INT_MAX);
					playerData.percent = MINMAX(0, (static_cast<long long>(playerData.minHP * 100LL)) / playerData.maxHP, 100);
					playerData.score = arenaPair.second.win;
					playerData.isPoisoned = ch->FindAffect(AFFECT_POISON) ? true : false;
				}

				buf.write(&playerData, sizeof(TPvPDuelData));

				if (arenaIndex != 0 && arenaIndex == arenaKey)
					break;
			}
			else if (subHeader == PVP_DATA_UPDATE_SCORE)
			{
				if (arenaKey == arenaIndex)
				{
					p.size = sizeof(TPacketGCPvPInfo) + sizeof(BYTE) + sizeof(BYTE) + sizeof(BYTE) + sizeof(BYTE);

					buf.write(&p, sizeof(TPacketGCPvPInfo));
					buf.write(&subHeader, sizeof(BYTE));
					buf.write(&arenaKey, sizeof(BYTE));
					buf.write(&arenaPair.first.win, sizeof(BYTE));
					buf.write(&arenaPair.second.win, sizeof(BYTE));
					break;
				}
			}
		}
	}

	if (buf.size() > 0)
	{
		if (buf.size() != p.size)
		{
			sys_err("Something wrong is packet dynamic size! subHeader %d bufSize %d packetSize %d", subHeader, buf.size(), p.size);
			return;
		}

		if (ch != NULL)
			ch->GetDesc()->Packet(buf.read_peek(), buf.size());
		else
		{
			for (auto& player : m_vec_PlayerList)
			{
				auto desc = player->GetDesc();
				if (desc)
					desc->Packet(buf.read_peek(), buf.size());
			}
		}
	}
}


// Static Functions:
void CPvPDuel::Show(LPCHARACTER ch, const long x, const long y)
{
	const LPSECTREE_MAP pkSectreeMap = SECTREE_MANAGER::instance().GetMap(PVP_DUEL_MAP_INDEX);
	if (pkSectreeMap)
	{
		if (ch->GetMapIndex() == PVP_DUEL_MAP_INDEX)
		{
			ch->Show(ch->GetMapIndex(), pkSectreeMap->m_setting.iBaseX + x * 100, pkSectreeMap->m_setting.iBaseY + y * 100, 0);
			ch->Stop();
			ch->UpdateSectree();
			UpdatePvPData(PVP_DATA_CLEAR_TARGET, 0, ch);
		}
		else
			ch->WarpSet(pkSectreeMap->m_setting.iBaseX + x * 100, pkSectreeMap->m_setting.iBaseY + y * 100);
	}
	else
	{
		auto mapSettings = SECTREE_MANAGER::Instance().GetMapRegion(PVP_DUEL_MAP_INDEX);
		if (mapSettings != NULL)
		{
			ch->WarpSet(mapSettings->sx + x * 100, mapSettings->sy + y * 100);
		}
	}
}
void CPvPDuel::Notice(const char* szNotice, ...)
{
	char notice[CHAT_MAX_LEN + 1];
	va_list args;
	va_start(args, szNotice);
	const int len = vsnprintf(notice, sizeof(notice), szNotice, args);
	va_end(args);
	SendNoticeMap(notice, PVP_DUEL_MAP_INDEX, true);
}
BYTE CPvPDuel::GetMaxRount()
{
	switch (GetFlag("pvp_state"))
	{
	case 3:
		return PVP_DUEL_FINAL_ROUNT_MAX;
	case 2:
		return PVP_DUEL_SEMI_FINAL_ROUNT_MAX;
	case 1:
		return PVP_DUEL_QUARTER_FINAL_ROUNT_MAX;
	default:
		return PVP_DUEL_ROUNT_MAX;
	}
	return PVP_DUEL_ROUNT_MAX;
}
const pvp_data* CPvPDuel::GetPvPData(const BYTE arenaIndex, const BYTE playerIndex)
{
	const auto it = m_map_pvpList.find(arenaIndex);
	return it != m_map_pvpList.end() ? (playerIndex == 1 ? &it->second.first : &it->second.second) : NULL;
}
int CPvPDuel::IsFighting(const DWORD playerID, const bool isNeedCheckCache)
{
	if (isNeedCheckCache)
	{
		for (const auto& [arenaIndex, arenaPair] : m_map_pvpCacheList)
			if (arenaPair.first.pid == playerID || arenaPair.second.pid == playerID)
				return arenaIndex;
	}
	else
	{
		for (const auto& [arenaIndex, arenaPair] : m_map_pvpList)
			if (arenaPair.first.pid == playerID || arenaPair.second.pid == playerID)
				return arenaIndex;
	}
	return -1;
}
int CPvPDuel::IsFighting(LPCHARACTER ch, const bool isNeedCheckCache)
{
	if (ch->GetMapIndex() != PVP_DUEL_MAP_INDEX)
		return -1;

	const DWORD playerID = ch->GetPlayerID();

	if (isNeedCheckCache)
	{
		for (const auto& [arenaIndex, arenaPair] : m_map_pvpCacheList)
			if (arenaPair.first.pid == playerID || arenaPair.second.pid == playerID)
				return arenaIndex;
	}
	else
	{
		for (const auto& [arenaIndex, arenaPair] : m_map_pvpList)
			if (arenaPair.first.pid == playerID || arenaPair.second.pid == playerID)
				return arenaIndex;
	}
	return -1;
}
void CPvPDuel::SetFlag(const char* flagname, const int value, ...)
{
	char realFlag[90];
	va_list args;
	va_start(args, value);
	vsnprintf(realFlag, sizeof(realFlag), flagname, args);
	va_end(args);
	
	auto it = m_map_pvpFlags.find(realFlag);
	if (it != m_map_pvpFlags.end())
	{
		if (value != 0)
			it->second = value;
		else
			m_map_pvpFlags.erase(it->first);
	}
	else
	{
		if (value != 0)
			m_map_pvpFlags.emplace(realFlag, value);
	}
}
int CPvPDuel::GetFlag(const char* flagname, ...)
{
	char realFlag[90];
	va_list args;
	va_start(args, flagname);
	vsnprintf(realFlag, sizeof(realFlag), flagname, args);
	va_end(args);

	const auto it = m_map_pvpFlags.find(realFlag);
	if (it != m_map_pvpFlags.end())
		return it->second;
	return 0;
}
void CPvPDuel::AddDuelAffect(LPCHARACTER ch)
{
	ch->AddAffect(AFFECT_PVP_DUEL, POINT_MOV_SPEED, -999, AFF_NONE, INFINITE_AFFECT_DURATION, 0, false, false);
}
void CPvPDuel::CheckReadyForDuel(LPCHARACTER ch)
{
	if (ch->IsDead())
	{
		ch->GetDesc()->SetPhase(PHASE_GAME);
		ch->SetPosition(POS_STANDING);
		ch->StartRecoveryEvent();
		ch->RestartAtSamePos();
	}
	else
		ch->RemoveBadAffect();

	const int hp = ch->GetHP(), maxHp = ch->GetMaxHP();
	if(maxHp != hp)
		ch->PointChange(POINT_HP, maxHp - hp);
	const int sp = ch->GetSP(), maxSp = ch->GetMaxSP();
	if (maxSp != sp)
		ch->PointChange(POINT_SP, maxSp - sp);
}
void CPvPDuel::RemoveDuelAffect(LPCHARACTER ch)
{
	const auto affect = ch->FindAffect(AFFECT_PVP_DUEL);
	if (affect)
		ch->RemoveAffect(affect);
}

const LPCHARACTER CPvPDuel::GetPvPEnemy(const BYTE arenaIndex, const DWORD exceptCh)
{
	const auto it = m_map_pvpList.find(arenaIndex);
	if (it == m_map_pvpList.end())
		return NULL;
	const auto pvpPair = it->second;
	return CHARACTER_MANAGER::Instance().FindByPID(pvpPair.first.pid == exceptCh ? pvpPair.second.pid : pvpPair.first.pid);
}

bool CPvPDuel::IsFighthingStart(const BYTE arenaIndex)
{
	return GetFlag("pvp_%d_fighthing", arenaIndex)?true:false;
}

struct FuncPullPlayer
{
	void operator()(LPCHARACTER m_ch, LPCHARACTER ch)
	{
		float fDist = DISTANCE_APPROX(m_ch->GetX() - ch->GetX(), m_ch->GetY() - ch->GetY());
		float fNewDist = fDist - (PVP_DUEL_MOVE_MAX_DISTANCE / 2);
		if (fNewDist < 100)
			fNewDist = 100;
		float degree = GetDegreeFromPositionXY(ch->GetX(), ch->GetY(), m_ch->GetX(), m_ch->GetY());
		float fx, fy;
		GetDeltaByDegree(degree, fDist - fNewDist, &fx, &fy);
		long tx = (long)(ch->GetX() + fx);
		long ty = (long)(ch->GetY() + fy);
		ch->Sync(tx, ty);
		ch->Goto(tx, ty);
		ch->CalculateMoveDuration();
		ch->SyncPacket();
	}
};
bool CPvPDuel::PvPPullFunction(LPCHARACTER ch)
{
	const int pvpArenaIndex = IsFighting(ch);
	if (pvpArenaIndex != -1 && IsFighthingStart(pvpArenaIndex) == true)
	{
		auto enemyCharacter = GetPvPEnemy(pvpArenaIndex, ch->GetPlayerID());
		if (enemyCharacter != NULL)
		{
			const long c_x = ch->GetX(), c_y = ch->GetY(), e_x = enemyCharacter->GetX(), e_y = enemyCharacter->GetY();
			const float fDist = DISTANCE_APPROX(c_x - e_x, c_y - e_y);

			if (fDist > PVP_DUEL_MOVE_MAX_DISTANCE)
			{
				FuncPullPlayer f;
				f(ch, enemyCharacter);
				f(enemyCharacter, ch);
				if (PVP_DUEL_AFTER_PULL_POISON == 1)
				{
					enemyCharacter->AttackedByPoison(ch);
					ch->AttackedByPoison(enemyCharacter);
				}
				return true;
			}
		}
	}
	return false;
}

bool CPvPDuel::IsBlockItem(const LPITEM item, bool isEquip)
{
	// These block directly blocking. If you set something these lines you need recompile source again..
	const BYTE itemType = item->GetType();
	const BYTE itemSubType = item->GetSubType();
	const DWORD itemVnum = item->GetVnum();
	
	// Equipment part!
	if (itemType == ITEM_COSTUME && itemSubType == COSTUME_MOUNT)
		return true;
	if (itemType == ITEM_COSTUME && itemSubType == COSTUME_PET && GetFlag("block_pet"))
		return true;

	if (isEquip)
		return false;

	// don't add after equipment item!

	constexpr DWORD blockItemVnums[] = {
		50629,
	};
	for (const auto blockItem : blockItemVnums)
	{
		if (blockItem == itemVnum)
			return true;
	}
	// These block directly blocking. If you set something these lines you need recompile source again..

	// Quest Part
	if (GetFlag("block_%d", itemVnum))
		return true;
	// Quest Part

	return false;
}

void CPvPDuel::PrintBlockItemList(LPCHARACTER ch)
{
	int printCount = 0;
	ch->ChatPacket(CHAT_TYPE_INFO, "---------------");
	for (const auto [flagName, flagValue] : m_map_pvpFlags)
	{
		if (flagName.find("block_") != std::string::npos)
		{
			printCount++;
			ch->ChatPacket(CHAT_TYPE_INFO, "%s", flagName.c_str());
		}
	}
	if (printCount == 0)
#ifdef TEXTS_IMPROVEMENT
		ch->ChatPacketNew(CHAT_TYPE_INFO, 2061, "");
#endif
		//ch->ChatPacket(CHAT_TYPE_INFO, "Não tem nenhum item de bloqueio!");
	ch->ChatPacket(CHAT_TYPE_INFO, "---------------");
}
