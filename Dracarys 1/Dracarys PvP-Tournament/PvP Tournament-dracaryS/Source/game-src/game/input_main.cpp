# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
#endif

#Search

	if (ch->IsDead())
	{
		sys_log(0, "MOVE: %s trying to move as dead", ch->GetName());
		ch->Show(ch->GetMapIndex(), ch->GetX(), ch->GetY(), ch->GetZ());
		ch->Stop();
		return;
	}

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	if (ch->GetMapIndex() == PVP_DUEL_MAP_INDEX)
	{
		if (CPvPDuel::Instance().PvPPullFunction(ch))
			return;
	}
#endif


#Search

	LPCHARACTER pInvitee = CHARACTER_MANAGER::instance().Find(p->vid);

# Add before

#ifdef ENABLE_PVP_TOURNAMENT
	if (ch->GetMapIndex() == PVP_DUEL_MAP_INDEX)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("1031"));
		return;
	}
#endif

