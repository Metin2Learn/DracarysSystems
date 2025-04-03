# Search

	BYTE					accept;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
		std::string				item_name[EXCHANGE_ITEM_MAX_NUM];
#endif

# Search

	long long		GetElkFromSelf();

#Add after

#ifdef ENABLE_NEW_NAME_ITEM
	void			SetItemNewName(int iPos, const char* name, bool bSelf);
	const char*		GetItemNewName(int iPos, bool bSelf);
#endif