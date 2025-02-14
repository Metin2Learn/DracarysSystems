#Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
#endif

# Search

	marriage::CManager::instance().Login(ch);

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	CPvPDuel::Instance().Login(ch);
#endif

