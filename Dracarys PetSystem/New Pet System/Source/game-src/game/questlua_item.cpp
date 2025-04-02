# Search

	{ NULL,			NULL			}

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
			{ "get_newname",	item_get_newname},
			{ "set_newname",	item_set_newname},
#endif

# Search

	void RegisterITEMFunctionTable()

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
	int item_get_newname(lua_State* L)
	{
		CQuestManager& q = CQuestManager::instance();
		LPITEM item = q.GetCurrentItem();
		if (item)
			lua_pushstring(L, item->GetNewName());
		else
			lua_pushstring(L, "^");
		return 1;
	}
	int item_set_newname(lua_State* L)
	{
		if (!lua_isstring(L, 1))
			return 1;
		CQuestManager& q = CQuestManager::instance();
		LPITEM item = q.GetCurrentItem();
		if (item)
			item->SetNewName(lua_tostring(L, 1));
		return 0;
	}
#endif

