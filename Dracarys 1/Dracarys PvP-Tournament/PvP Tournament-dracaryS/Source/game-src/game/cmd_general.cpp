# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
ACMD(do_pvp_duel)
{
	if (!ch->IsGM())
		return;
	std::vector<std::string> vecArgs;
	split_argument(argument, vecArgs);
	if (vecArgs.size() < 2) { return; }
	CPvPDuel& pvpDuel = CPvPDuel::Instance();
	if (vecArgs[1] == "remove")
	{
		if (vecArgs.size() < 3) { return; }
		LPCHARACTER removePlayer = CHARACTER_MANAGER::Instance().FindPC(vecArgs[2].c_str());
		if (!removePlayer)
			return;
		pvpDuel.DonePvPDuel(removePlayer, PVP_DUEL_LEFT_TYPE_GM);
	}
	else if (vecArgs[1] == "close")
	{
		CPvPDuel::Instance().DonePvP(PVP_DUEL_CLOSE_FROM_GM);
	}
	else if (vecArgs[1] == "start")
	{
		if (!map_allow_find(PVP_DUEL_MAP_INDEX))
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1002"));
			return;
		}

		if (vecArgs.size() < 8) { return; }

		BYTE pvpType;
		str_to_number(pvpType, vecArgs[2].c_str());
		BYTE minLevel;
		str_to_number(minLevel, vecArgs[3].c_str());
		BYTE maxLevel;
		str_to_number(maxLevel, vecArgs[4].c_str());
		short registerCount;
		str_to_number(registerCount, vecArgs[5].c_str());
		short registerTime;
		str_to_number(registerTime, vecArgs[6].c_str());
		long long betPrice;
		str_to_number(betPrice, vecArgs[7].c_str());

		// Check
		if (pvpType > 4)
			return;
		else if (minLevel > 120 || maxLevel > 120 || minLevel > maxLevel || minLevel == maxLevel)
			return;
		else if (registerCount < 0 || registerCount > 300)
			return;
		else if (registerTime < 0 || registerTime > 300)
			return;
		else if (betPrice < 0)
			return;
		pvpDuel.SetFlag("pvp_for_job", pvpType);
		pvpDuel.SetFlag("register_max_time", registerTime * 60);
		pvpDuel.SetFlag("register_count_max", registerCount);
		pvpDuel.SetFlag("pvp_min_level", minLevel);
		pvpDuel.SetFlag("pvp_max_level", maxLevel);
		pvpDuel.SetFlag("pvp_bet", betPrice);
		pvpDuel.StartProcess(ch);
	}
}
#endif

