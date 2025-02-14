# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
#endif


# Search in CanEquipNow(const LPITEM item, const TItemPos& srcCell, const TItemPos& destCell)

	const TItemTable* itemTable = item->GetProto();
	BYTE itemType = item->GetType();
	BYTE itemSubType = item->GetSubType();

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	if (GetMapIndex() == PVP_DUEL_MAP_INDEX)
	{
		if (CPvPDuel::Instance().IsBlockItem(item, true))
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1001"));
			return false;
		}
	}
#endif

# Search

	int iLimitTimerBasedOnWearFlagIndex = -1;

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	if (GetMapIndex() == PVP_DUEL_MAP_INDEX)
	{
		if (CPvPDuel::Instance().IsBlockItem(item))
		{
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1001"));
			return false;
		}
	}
#endif

