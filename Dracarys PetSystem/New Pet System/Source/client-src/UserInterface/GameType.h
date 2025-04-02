# Search

} TItemData;

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
	char		name[CItemData::ITEM_NAME_MAX_LEN+1];
#endif

# Search

	const DWORD	c_Costume_Slot_Weapon = c_Equipment_Start + CItemData::WEAR_COSTUME_WEAPON;

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	const DWORD	c_Slot_Pet = c_Equipment_Start + CItemData::WEAR_PET;
#endif


# Search

	c_Costume_Slot_Count

# Increate +1

Example:

	c_Costume_Slot_Count = 5 to 6;
