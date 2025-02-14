# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
#endif


# Search

		if (get_dword_time() - pvp->GetLastFightTime() > 600000)
		{
			pvp->Packet(true);
			Delete(pvp);
		}

# Change

		if (get_dword_time() - pvp->GetLastFightTime() > 600000)
		{
#ifdef ENABLE_PVP_TOURNAMENT
			if(pvp->itsPvPTournament)
				return;
#endif

			pvp->Packet(true);
			Delete(pvp);
		}


# Search

	char msg[CHAT_MAX_LEN + 1];

# Add before

#ifdef ENABLE_PVP_TOURNAMENT
	if (pkChr->GetMapIndex() == PVP_DUEL_MAP_INDEX)
	{
		pkPVP->itsPvPTournament = true;
		return;
	}
	else
		pkPVP->itsPvPTournament = false;
#endif

# Search

		if (pkPVP->Agree(pkChr->GetPlayerID()))
		{
			...
		}

# Change Like that


		if (pkPVP->Agree(pkChr->GetPlayerID()))
		{
#ifdef ENABLE_PVP_TOURNAMENT
			if (pkChr->GetMapIndex() == PVP_DUEL_MAP_INDEX)
				return;
#endif

			....
		}

# Add

#ifdef ENABLE_PVP_TOURNAMENT
void CPVPManager::RemoveCharactersPvP(LPCHARACTER pkChr, LPCHARACTER pkVictim)
{
	auto it = m_map_pkPVPSetByID.find(pkChr->GetPlayerID());

	if (it == m_map_pkPVPSetByID.end())
		return;

	auto it2 = it->second.begin();
	while (it2 != it->second.end())
	{
		CPVP* pkPVP = *it2++;
		DWORD dwCompanionPID;
		if (pkPVP->m_players[0].dwPID == pkChr->GetPlayerID())
			dwCompanionPID = pkPVP->m_players[1].dwPID;
		else
			dwCompanionPID = pkPVP->m_players[0].dwPID;
		if (dwCompanionPID == pkVictim->GetPlayerID())
		{
			pkPVP->Packet(true);
			Delete(pkPVP);
		}
	}
}
#endif