#include "stdafx.h"
#include "constants.h"
#include "config.h"
#include "desc.h"
#include "buffer_manager.h"
#include "start_position.h"
#include "questmanager.h"
#include "char.h"
#include "char_manager.h"
#include "sectree_manager.h"
#include "new_mob_timer.h"
#include "utils.h"
#include <algorithm>
#include "mob_manager.h"
#include "dungeon.h"
#include <time.h>


CNewMobTimer::CNewMobTimer() : m_pkMobRegenTimerEvent(NULL) {}
CNewMobTimer::~CNewMobTimer() { Destroy(); }
EVENTINFO(empty_event_info){empty_event_info(){}};
EVENTFUNC(main_timer)
{
	empty_event_info* info = dynamic_cast<empty_event_info*>(event->info);
	if (info == NULL)
		return 0;
	return PASSES_PER_SEC(CNewMobTimer::Instance().Update());
}

void CNewMobTimer::Destroy()
{
	if (m_pkMobRegenTimerEvent)
	{
		event_cancel(&m_pkMobRegenTimerEvent);
		m_pkMobRegenTimerEvent = NULL;
	}

	for (DWORD j=0;j< m_vecRegenData.size();++j)
	{
		const TNewRegen& newRegen = m_vecRegenData[j];
		if (newRegen.bossPtr)
			M2_DESTROY_CHARACTER(newRegen.bossPtr);
	}
	m_vecRegenData.clear();
}

int CalculateForFindPerRegenTime(time_t calculatedTime, const TNewRegen* newRegen)
{
	const struct tm vKey = *localtime(&calculatedTime);

	int myear = vKey.tm_year;
	int mmon = vKey.tm_mon;
	int mday = vKey.tm_mday;
	int yday = vKey.tm_yday;
	int day = vKey.tm_wday;
	int hour = vKey.tm_hour;
	int minute = vKey.tm_min;
	int second = vKey.tm_sec;

	const BYTE regenHour = newRegen->hour;
	const BYTE regenMinute = newRegen->minute;
	const BYTE regenSecond = newRegen->second;

	bool isSucces = false;
	const int now = time(0) + 2;

	while (true)
	{
		++second;
		if (second == 60)
		{
			minute += 1;
			second = 0;
			if (minute == 60)
			{
				minute = 0;
				hour += 1;
				if (hour == 24)
				{
					hour = 0;
					day += 1;
					if (day == 7)
						day = 0;
					mday += 1;
					yday += 1;
					if (mday == 32)
					{
						mday = 1;
						mmon += 1;
						if (mmon == 12)
						{
							mmon = 0;
							myear += 1;
							yday = 0;
						}
					}
				}
			}
		}

		if (newRegen->days_range)
		{
			if ((day % newRegen->days_range) != 0)
				continue;
		}

		if (second == 0)
		{
			if (newRegen->hours_range)
			{
				const int realStartHour = regenHour ? 24+(24-regenHour) : 0 ;
				if (((hour+realStartHour) % newRegen->hours_range) == 0 && regenMinute == minute)
				{
					isSucces = true;
					break;
				}
			}
			if (newRegen->minute_range)
			{
				if ((minute % newRegen->minute_range) == 0)
				{
					isSucces = true;
					break;
				}
			}
		}
		if (regenHour == hour && regenMinute == minute && regenSecond == second)
		{
			if (newRegen->day)
			{
				if (newRegen->day - 1 == day)
				{
					isSucces = true;
					break;
				}
			}
			else
			{
				isSucces = true;
				break;
			}
		}
		if (time(0) > now)
			break;
	}
	if (isSucces)
	{
		struct tm tm;
		tm.tm_year = myear;
		tm.tm_mon = mmon;
		tm.tm_mday = mday;
		tm.tm_isdst = 0;
		tm.tm_wday = day;
		tm.tm_hour = hour;
		tm.tm_min = minute;
		tm.tm_sec = second;
		tm.tm_yday = yday;
		const time_t t = mktime(&tm);
		return t;
	}
	return WORD_MAX;
}

static bool get_word(FILE* fp, char* buf)
{
	int i = 0;
	int c;
	int semicolon_mode = 0;
	while ((c = fgetc(fp)) != EOF)
	{
		if (i == 0)
		{
			if (c == '"')
			{
				semicolon_mode = 1;
				continue;
			}
			if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
				continue;
		}
		if (semicolon_mode)
		{
			if (c == '"')
			{
				buf[i] = '\0';
				return true;
			}
			buf[i++] = c;
		}
		else
		{
			if ((c == ' ' || c == '\t' || c == '\n' || c == '\r'))
			{
				buf[i] = '\0';
				return true;
			}
			buf[i++] = c;
		}
		if (i == 2 && buf[0] == '/' && buf[1] == '/')
		{
			buf[i] = '\0';
			return true;
		}
	}
	buf[i] = '\0';
	return (i != 0);
}

static void next_line(FILE* fp)
{
	int c;
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n')
			return;
}

bool CNewMobTimer::ReadLine(FILE* fp, TNewRegen& regen)
{
	char szTmp[256];

	int mode = R_ID;
	int tmpTime;
	DWORD i;
	while (get_word(fp, szTmp))
	{
		if (!strncmp(szTmp, "//", 2))
		{
			next_line(fp);
			continue;
		}

		switch (mode)
		{
			case R_ID:
				str_to_number(regen.id, szTmp);
				++mode;
				break;
			case R_MAPINDEX:
				str_to_number(regen.mapIndex, szTmp);
				++mode;
				break;
			case R_MAPNAME:
				++mode;
				break;
			case R_X:
				str_to_number(regen.x, szTmp);
				++mode;
				break;
			case R_Y:
				str_to_number(regen.y, szTmp);
				++mode;
				break;
			case R_DIRECTION:
				str_to_number(regen.direction, szTmp);
				++mode;
				break;
			case R_CHANNEL:
				str_to_number(regen.channel, szTmp);
				++mode;
				break;
			
			case R_DAY:
				str_to_number(regen.day, szTmp);
				++mode;
				break;
			case R_HOUR:
				str_to_number(regen.hour, szTmp);
				++mode;
				break;
			case R_MINUTE:
				str_to_number(regen.minute, szTmp);
				++mode;
				break;
			case R_SECOND:
				str_to_number(regen.second, szTmp);
				++mode;
				break;

			case R_BROADCAST:
				int broadcast;
				str_to_number(broadcast, szTmp);
				regen.broadcast = broadcast?1:0;
				++mode;
				break;

			case R_SAFE_RANGE:
				str_to_number(regen.safeRange, szTmp);
				++mode;
				break;
			case R_DAYS_RANGE:
				str_to_number(regen.days_range, szTmp);
				++mode;
				break;
			case R_HOURS_RANGE:
				str_to_number(regen.hours_range, szTmp);
				++mode;
				break;
			case R_MINUTE_RANGE:
				str_to_number(regen.minute_range, szTmp);
				++mode;
				break;
			case R_VNUM:
				str_to_number(regen.mob_vnum, szTmp);
				++mode;
				return true;
		}
	}
	return false;
}

bool CNewMobTimer::LoadFile(const char* filename)
{
	Destroy();
	FILE* fp = fopen(filename, "rt");
	if (NULL == fp)
	{
		sys_err("SYSTEM: load_new_regen: %s: file not found", filename);
		return false;
	}
	while (true)
	{
		TNewRegen tmp;
		memset(&tmp, 0, sizeof(tmp));
		tmp.bossPtr = NULL;
		if (!ReadLine(fp, tmp))
			break;
		const CMob* p = CMobManager::instance().Get(tmp.mob_vnum);
		if (!p)
		{
			sys_err("CNewMobTimer::Update %s unkown mob vnum!", tmp.mob_vnum);
			continue;
		}
		const long x = tmp.x, y = tmp.y;

		const SECTREE_MAP* sectreeMap = SECTREE_MANAGER::instance().GetMap(tmp.mapIndex);
		if (sectreeMap)
		{
			
			tmp.x = sectreeMap->m_setting.iBaseX + x * 100;
			tmp.y = sectreeMap->m_setting.iBaseY + y * 100;
		}
		CalculateLeftTimeReal(&tmp);
		m_vecRegenData.emplace_back(tmp);
		if (!HasMob(tmp.mob_vnum))
			m_vecHasVnums.emplace_back(tmp.mob_vnum);
		sys_log(0, "Insert mob %d mapIndex %d x %ld y %ld", tmp.mob_vnum, tmp.mapIndex, tmp.x, tmp.y);
	}
	if (m_vecRegenData.size())
		Initialize();
	return true;
}

void CNewMobTimer::Initialize()
{
	if (g_bAuthServer)
	{
		sys_log(0, "CNewMobTimer: I am the master!");
		return;
	}

	empty_event_info* info = AllocEventInfo<empty_event_info>();
	m_pkMobRegenTimerEvent = event_create(main_timer, info, PASSES_PER_SEC(0));
}

long CNewMobTimer::Update()
{
	const time_t cur_Time = time(NULL);
	const struct tm vKey = *localtime(&cur_Time);
	const int hour = vKey.tm_hour;
	const int minute = vKey.tm_min;
	const int second = vKey.tm_sec;
	for (auto j = 0; j < m_vecRegenData.size(); ++j)
	{
		TNewRegen& newRegen = m_vecRegenData[j];
		SECTREE_MAP* sectreeMap = SECTREE_MANAGER::instance().GetMap(newRegen.mapIndex);
		if (!sectreeMap)
			continue;
		if (newRegen.channel)
		{
			if (newRegen.channel != g_bChannel)
				continue;
		}
		const int leftTime = CalculateLeftTime(&newRegen);
		if (leftTime < 0)
			continue;
		const bool printMessage = leftTime == 30 ? true:false;
		const bool trySpawn = leftTime == 0 ? true:false;
		if (trySpawn)
			SpawnBoss(sectreeMap, newRegen);
		else if(printMessage)
		{
			const CMob* p = CMobManager::instance().Get(newRegen.mob_vnum);
			if (!p)
			{
				sys_err("CNewMobTimer::Update %s unkown mob vnum!", newRegen.mob_vnum);
				continue;
			}

			char buf[512];
			if (newRegen.bossPtr)
			{
				if (IsWorldBoss(newRegen.mob_vnum))
					//snprintf(buf, sizeof(buf), "2500 M%d %d", newRegen.mob_vnum, g_bChannel);
					snprintf(buf, sizeof(buf), ("2500"), newRegen.bossPtr->GetName(), g_bChannel);
				else
					//snprintf(buf, sizeof(buf), "2505 M%d %d", newRegen.mob_vnum, g_bChannel);
					snprintf(buf, sizeof(buf), ("2505"), newRegen.bossPtr->GetName(), g_bChannel);
			}
			else
			{
				if (IsWorldBoss(newRegen.mob_vnum))
					//snprintf(buf, sizeof(buf), "2501 M%d %d", newRegen.mob_vnum, g_bChannel);
					snprintf(buf, sizeof(buf), ("2501"), p->m_table.szLocaleName, g_bChannel);
				else
					//snprintf(buf, sizeof(buf), "2506 M%d %d", newRegen.mob_vnum, g_bChannel);
					snprintf(buf, sizeof(buf), ("2506"), p->m_table.szLocaleName, g_bChannel);
			}
			
			if (newRegen.broadcast)
				BroadcastNotice(buf);
			else
				SendNoticeMap(buf, newRegen.mapIndex, false);
			
			newRegen.blockAttack = true;
		}
		
	}
	return 1;
}

void CNewMobTimer::SpawnBoss(const SECTREE_MAP* sectreeMap, TNewRegen& m_Regen)
{
	m_Regen.blockAttack = false;

	if (m_Regen.bossPtr)
	{
		sys_log(0, "CNewMobTimer::SpawnBoss - Channel: %d MapIndex: %ld BossVnum: %d - still alive!", m_Regen.channel, m_Regen.mapIndex, m_Regen.mob_vnum);
		return;
	}

	LPCHARACTER spawnMob = CHARACTER_MANAGER::instance().SpawnMob(m_Regen.mob_vnum, m_Regen.mapIndex, m_Regen.x, m_Regen.y, 0, true, m_Regen.direction);
	if (spawnMob)
	{
		spawnMob->SetProtectTime("IAMBOSS", 1);
		
		char szNotice[256];
		if (IsWorldBoss(m_Regen.mob_vnum))
			//snprintf(szNotice, sizeof(szNotice), "2502 M%d %d", m_Regen.mob_vnum, g_bChannel);
			snprintf(szNotice, sizeof(szNotice), ("2502"), spawnMob->GetName(), g_bChannel);
		else
			//snprintf(szNotice, sizeof(szNotice), "2507 M%d %d", m_Regen.mob_vnum, g_bChannel);
			snprintf(szNotice, sizeof(szNotice), ("2507"), spawnMob->GetName(), g_bChannel);

		if (m_Regen.broadcast)
			BroadcastNotice(szNotice);
		else
			SendNoticeMap(szNotice, m_Regen.mapIndex, false);

		m_Regen.bossPtr = spawnMob;
		UpdateNewRegen(m_Regen.id, true);
		sys_log(0, "CNewMobTimer::SpawnBoss - Spawn successfully(mobvnum %d mapIndex %d)", m_Regen.mob_vnum, m_Regen.mapIndex);
	}
	else
	{
		sys_log(0, "CNewMobTimer::SpawnBoss - Spawn fail!!!!!!!!!!(mobvnum %d mapIndex %d)", m_Regen.mob_vnum, m_Regen.mapIndex);
		m_Regen.bossPtr = NULL;
		UpdateNewRegen(m_Regen.id, false);
	}
}

bool CNewMobTimer::HasMob(DWORD mobVnum)
{
	const auto it = std::find(m_vecHasVnums.begin(), m_vecHasVnums.end(), mobVnum);
	if (it == m_vecHasVnums.end())
		return false;
	return true;
}
void CNewMobTimer::Dead(LPCHARACTER pkBoss, LPCHARACTER pkKiller)
{
	if (!pkBoss)
		return;
	if (pkBoss->GetProtectTime("IAMBOSS"))
	{
		for (auto j = 0; j < m_vecRegenData.size(); ++j)
		{
			TNewRegen& newRegen = m_vecRegenData[j];
			if (newRegen.bossPtr == pkBoss)
			{
				newRegen.bossPtr = NULL;
				UpdateNewRegen(newRegen.id, false);

				char szNotice[256];
				if (IsWorldBoss(newRegen.mob_vnum))
				{
					const int leftTime = CalculateLeftTime(&newRegen);
					std::string timeText("");
					const int second = int(leftTime % 60);
					const int minute = int((leftTime / 60) % 60);
					const int hour = int((leftTime / 60) / 60);
					const int day = int(int((hour / 60) / 60) / 24);
					if (day > 0)
					{
						timeText += std::to_string(day);
						timeText += "d-";
					}
					if (hour > 0)
					{
						timeText += std::to_string(hour);
						timeText += "h-";
					}
					if (minute > 0)
					{
						timeText += std::to_string(minute);
						timeText += "m-";
					}
					if (second > 0)
					{
						timeText += std::to_string(second);
						timeText += "s";
					}
					if (timeText.length() == 0)
						timeText = "None";
					//snprintf(szNotice, sizeof(szNotice), "2503 M%d", pkBoss->GetRaceNum(), timeText.c_str());
					snprintf(szNotice, sizeof(szNotice), ("2503"), pkBoss->GetName(), g_bChannel, CalculateLeftTime(&newRegen));
				}
				else
					//snprintf(szNotice, sizeof(szNotice), "2504 %s M%d %d", pkKiller ? pkKiller->GetName() : "Unknown", newRegen.mob_vnum, g_bChannel);
					snprintf(szNotice, sizeof(szNotice), ("2504"), pkKiller ? pkKiller->GetName() : "Unknown", pkBoss->GetName(), g_bChannel);
				if (newRegen.broadcast)
					BroadcastNotice(szNotice);
				else
					SendNoticeMap(szNotice, newRegen.mapIndex, false);
				break;
			}
		}
	}
}

bool CNewMobTimer::CheckDamage(LPCHARACTER pkAttacker, LPCHARACTER pkVictim)
{
	if (!(pkAttacker && pkVictim))
		return true;
	if (!pkVictim->IsPC() || !pkAttacker->IsPC())
		return true;

	for (auto j = 0; j < m_vecRegenData.size(); ++j)
	{
		const TNewRegen& newRegen = m_vecRegenData[j];
		const LPCHARACTER mob = newRegen.bossPtr;
		if (mob)
		{
			const float fDist = DISTANCE_APPROX(pkAttacker->GetX() - mob->GetX(), pkAttacker->GetY() - mob->GetY());
			if (fDist <= float(newRegen.safeRange))
				return false;
		}
		else if (newRegen.blockAttack)
		{
			const float fDist = DISTANCE_APPROX(pkAttacker->GetX() - newRegen.x, pkAttacker->GetY() - newRegen.y);
			if (fDist <= float(newRegen.safeRange))
				return false;
		}
	}
	return true;
}

#include "p2p.h"
#include "desc_manager.h"
bool CNewMobTimer::IsWorldBoss(DWORD mobIndex)
{
	switch(mobIndex)
	{
		case 6091:
		case 6191:
			return true;
	}
	return false;
}
void CNewMobTimer::UpdateNewRegen(WORD id, bool isAlive, bool isP2P)
{
	TNewRegen* newRegen = NULL;

	for (auto j = 0; j < m_vecRegenData.size(); ++j)
	{
		newRegen = &m_vecRegenData[j];
		if (newRegen->id == id)
			break;
	}
	if (!newRegen)
		return;

	CalculateLeftTimeReal(newRegen);

	if (!isP2P)
	{
		TGGPacketNewRegen p;
		p.header = HEADER_GG_NEW_REGEN;
		p.subHeader = NEW_REGEN_REFRESH;
		p.id = id;
		p.isAlive = isAlive;
		P2P_MANAGER::Instance().Send(&p, sizeof(p));
	}
	else
	{
		newRegen->p2pAlive = isAlive;
	}

	const int calculatedTime = CalculateLeftTime(newRegen);
	const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::instance().GetClientSet();
	for (auto it = c_ref_set.begin(); it != c_ref_set.end(); ++it)
	{
		LPCHARACTER ch = (*it)->GetCharacter();
		if (ch)
		{
			if (ch->GetProtectTime("track_dungeon") == 1)
				ch->ChatPacket(CHAT_TYPE_COMMAND, "TrackBossInfo %d %d %d", id, calculatedTime, newRegen->channel);
		}
	}
}
void CNewMobTimer::UpdatePlayers()
{	
	const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::instance().GetClientSet();
	for (auto j = 0; j < m_vecRegenData.size(); ++j)
	{
		TNewRegen* newRegen = &m_vecRegenData[j];
		const int calculatedTime = CalculateLeftTime(newRegen);
		for (auto it = c_ref_set.begin(); it != c_ref_set.end(); ++it)
		{
			LPCHARACTER ch = (*it)->GetCharacter();
			if (!ch)
				continue;
			if (ch->GetProtectTime("track_dungeon") == 1)
				ch->ChatPacket(CHAT_TYPE_COMMAND, "TrackBossInfo %d %d %d", newRegen->id, calculatedTime, newRegen->channel);
		}
	}
}

void CNewMobTimer::CalculateLeftTimeReal(TNewRegen* newRegen)
{
	const time_t cur_Time = time(NULL);
	const struct tm vKey = *localtime(&cur_Time);

	int myear = vKey.tm_year;
	int mmon = vKey.tm_mon;
	int mday = vKey.tm_mday;
	int yday = vKey.tm_yday;
	int day = vKey.tm_wday;
	int hour = vKey.tm_hour;
	int minute = vKey.tm_min;
	int second = vKey.tm_sec;

	const BYTE regenHour = newRegen->hour;
	const BYTE regenMinute = newRegen->minute;
	const BYTE regenSecond = newRegen->second;

	DWORD startTime = get_dword_time();

	bool isSucces = false;
	const int now = time(0) + 2;
	while (true)
	{
		++second;
		if (second == 60)
		{
			minute += 1;
			second = 0;
			if (minute == 60)
			{
				minute = 0;
				hour += 1;
				if (hour == 24)
				{
					hour = 0;
					day += 1;
					if (day == 7)
						day = 0;
					mday += 1;
					yday += 1;
					if (mday == 32)
					{
						mday = 1;
						mmon += 1;
						if (mmon == 12)
						{
							mmon = 0;
							myear += 1;
							yday = 0;
						}
					}
				}
			}
		}

		sys_err("step 1");
		if (newRegen->days_range)
		{
			sys_err("step 2");
			if ((day % newRegen->days_range) != 0)
				continue;
			sys_err("step 3");
		}
		sys_err("step 4 %d %d %d - %d %d", hour, minute, second, newRegen->hours_range, newRegen->minute_range, newRegen->hours_range);
		if (second == 0)
		{
			sys_err("step 5");
			if (newRegen->hours_range)
			{
				sys_err("step 6");
				const int realStartHour = regenHour ? 24+(24-regenHour) : 0 ;
				if (((hour+realStartHour) % newRegen->hours_range) == 0 && regenMinute == minute)
				{
					isSucces = true;
					break;
				}
				sys_err("step 7");
			}
			sys_err("step 8");
			if (newRegen->minute_range)
			{
				sys_err("step 9");
				if ((minute % newRegen->minute_range) == 0)
				{
					isSucces = true;
					break;
				}
				sys_err("step 10");
			}
		}
		sys_err("step 11");
		if (regenHour == hour && regenMinute == minute && regenSecond == second)
		{
			sys_err("step 12");
			if (newRegen->day)
			{
				sys_err("step 13");
				if (newRegen->day - 1 == day)
				{
					isSucces = true;
					break;
				}
				sys_err("step 14");
			}
			else
			{
				sys_err("step 15");
				isSucces = true;
				break;
			}
		}

		sys_err("step 16");
		if (time(0) > now)
			break;
		sys_err("step 17");
	}
	if (isSucces)
	{
		struct tm tm;
		tm.tm_year = myear;
		tm.tm_mon = mmon;
		tm.tm_mday = mday;
		tm.tm_isdst = 0;
		tm.tm_wday = day;
		tm.tm_hour = hour;
		tm.tm_min = minute;
		tm.tm_sec = second;
		tm.tm_yday = yday;
		const time_t t = mktime(&tm);
		newRegen->leftTime = t - 3570;
	}
	else
		newRegen->leftTime = WORD_MAX;
}
int CNewMobTimer::CalculateLeftTime(TNewRegen* newRegen)
{
	if (newRegen->p2pAlive == true || newRegen->bossPtr != NULL)
		newRegen->leftTime = WORD_MAX;
	return newRegen->leftTime != WORD_MAX ? newRegen->leftTime-time(0) : WORD_MAX;
}

void CNewMobTimer::GetTrackData(LPCHARACTER ch, WORD id)
{
	if (!ch)
		return;

	for (auto j = 0; j < m_vecRegenData.size(); ++j)
	{
		TNewRegen* newRegen = &m_vecRegenData[j];
		if (id == newRegen->id)
		{
			ch->ChatPacket(CHAT_TYPE_COMMAND, "TrackBossInfo %d %d %d", id, CalculateLeftTime(newRegen), newRegen->channel);
			return;
		}
	}
}

