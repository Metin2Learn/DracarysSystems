# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
#endif


# Search

	if (false == CanUseSkill(dwVnum))
		return false;

#Add after

#ifdef ENABLE_PVP_TOURNAMENT
	if (GetMapIndex() == PVP_DUEL_MAP_INDEX)
	{
		constexpr unsigned int pTableSkill[] = { 94, 95, 96, 109, 110, 111 };
		for (const auto blockSkill : pTableSkill)
		{
			if (blockSkill == dwVnum)
			{
				pkVictim = this;
				break;
			}
		}
	}
#endif

