# Add

#ifdef ENABLE_PVP_TOURNAMENT
#include "pvp_duel.h"
#endif

# Search

			{	NULL,	NULL	}

# Add before

#ifdef ENABLE_PVP_TOURNAMENT
			{ "pvp_duel_setflag", _pvp_duel_setflag },
			{ "pvp_duel_getflag", _pvp_duel_getflag },
			{ "pvp_duel_register", _pvp_duel_register },
			{ "pvp_duel_start", _pvp_duel_start },
			{ "pvp_duel_close", _pvp_duel_close },
			{ "pvp_duel_warpbase", _pvp_duel_warpbase },
			{ "pvp_duel_printblockitem", _pvp_duel_printblockitem },
#endif


# Search

	void RegisterGlobalFunctionTable(lua_State* L)

# add before

#ifdef ENABLE_PVP_TOURNAMENT
	int _pvp_duel_setflag(lua_State* L)
	{
		if (!lua_isstring(L, 1) || !lua_isnumber(L, 2))
			return 0;
		CPvPDuel::Instance().SetFlag(lua_tostring(L, 1), (int)lua_tonumber(L, 2));
		return 0;
	}
	int _pvp_duel_getflag(lua_State* L)
	{
		if (!lua_isstring(L, 1))
			lua_pushstring(L, "");
		else
			lua_pushnumber(L, CPvPDuel::Instance().GetFlag(lua_tostring(L, 1)));
		return 1;
	}
	int _pvp_duel_register(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		int returnValue = -1;
		if (ch)
			returnValue = CPvPDuel::Instance().Register(ch);
		lua_pushnumber(L, returnValue);
		return 1;
	}
	int _pvp_duel_start(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (ch)
			CPvPDuel::Instance().StartProcess(ch);
		return 0;
	}
	int _pvp_duel_close(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (ch)
			CPvPDuel::Instance().DonePvP(PVP_DUEL_CLOSE_FROM_GM);
		return 0;
	}
	int _pvp_duel_warpbase(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (ch)
			CPvPDuel::Instance().SetPvPBase(ch);
		return 0;
	}
	int _pvp_duel_printblockitem(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		if (ch)
			CPvPDuel::Instance().PrintBlockItemList(ch);
		return 0;
	}
#endif
