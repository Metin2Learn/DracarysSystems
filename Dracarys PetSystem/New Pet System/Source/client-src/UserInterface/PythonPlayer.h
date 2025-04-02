# Search
	void	SetItemCount(TItemPos Cell, WORD wCount);

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	void	SetItemNewName(TItemPos itemPos, const char* name);
	const char*	GetItemNewName(TItemPos itemPos);
#endif

