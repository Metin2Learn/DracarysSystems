# add

#ifdef ENABLE_EVENT_MANAGER
#include "char_manager.h"
#endif

# Search

	void RegisterGameFunctionTable()

# add before

#ifdef ENABLE_EVENT_MANAGER
	int game_check_event(lua_State* L)
	{
		if (!lua_isnumber(L, 1))
		{
			lua_pushboolean(L, false);
			return 1;
		}
		lua_pushboolean(L, CHARACTER_MANAGER::Instance().CheckEventIsActive(lua_tonumber(L,1)));
		return 1;
	}
#endif


# Search

	{ NULL,					NULL				}

# Add before

#ifdef ENABLE_EVENT_MANAGER
			{ "check_event",		game_check_event			},
#endif

