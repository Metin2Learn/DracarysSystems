# Search

	virtual void	SetItemAttribute(TItemPos itemPos, DWORD dwAttrIndex, BYTE byType, short sValue) = 0;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	virtual void	SetItemNewName(TItemPos itemPos, const char* name) = 0;
	virtual const char*	GetItemNewName(TItemPos itemPos) = 0;
#endif

