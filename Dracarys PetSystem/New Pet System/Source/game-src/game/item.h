# Search

	DWORD		GetCount();

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	const char*	GetNewName() const	{return nameex;}
	void		SetNewName(const char* name);
#endif

# Search

	DWORD		m_dwSIGVnum;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	char		nameex[ITEM_NAME_MAX_LEN+1];
#endif

# Search

	void		SetMaskVnum(DWORD vnum) { m_dwMaskVnum = vnum; }

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
	bool		IsCostumePetItem();
	bool		IsNewPetItem();
#endif