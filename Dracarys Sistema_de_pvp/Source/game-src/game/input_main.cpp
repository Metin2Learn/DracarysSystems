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
# to do find where
# 总结：
# PvPPullFunction 函数的目的是在 PvP 对战中，如果当前角色和敌方角色的距离超过设定的最大拉近距离，则将两者互相拉近，并可能触发中毒效果。这个功能通常用于确保对战中的角色之间的距离符合游戏规则，并且避免某些玩家通过跑动拉开距离来规避战斗。
# 关键点：
# IsFighting 检查角色是否参与对战。
# GetPvPEnemy 获取敌方角色。
# 通过 DISTANCE_APPROX 计算距离，并在超出阈值时进行拉近。
# 可能附带中毒效果（AttackedByPoison）。

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

