# Search in int dungeon_new_jump(lua_State* L)

		int x = (int)lua_tonumber(L, 2);
		x *= 100;

		int y = (int)lua_tonumber(L, 3);
		y *= 100;

# Add after

#ifdef __BACK_DUNGEON__
		pDungeon->SetFlag("LAST_X", x);
		pDungeon->SetFlag("LAST_Y", y);
#endif

