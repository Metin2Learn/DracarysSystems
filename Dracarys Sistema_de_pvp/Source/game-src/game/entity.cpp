# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "char_manager.h"
#endif

# Search

	m_bObserverModeChange = false;

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	m_bPvPTournament = false;
#endif

# Add

#ifdef ENABLE_PVP_TOURNAMENT
void CEntity::SetPvPTournament(bool bFlag)
{
	if (m_bPvPTournament == bFlag)
		return;
	m_bPvPTournament = bFlag;
	UpdateSectree();
}
#endif

