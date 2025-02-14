# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
#endif

# Search

	if (m_set_pkChrTargetedBy.empty())
		return;

# Add before

#ifdef ENABLE_PVP_TOURNAMENT
	const int pvpArenaIndex = CPvPDuel::Instance().IsFighting(this);
	if (pvpArenaIndex != -1)
		CPvPDuel::Instance().UpdatePvPData(PVP_DATA_UPDATE_HP, pvpArenaIndex);
#endif

# Search

	marriage::CManager::instance().Logout(this);

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	CPvPDuel::Instance().Logout(this);
#endif
