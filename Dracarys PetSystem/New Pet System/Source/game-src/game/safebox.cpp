# Search

	pack.anti_flags = pkItem->GetAntiFlag();

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	strlcpy(pack.name, pkItem->GetNewName(),sizeof(pack.name));
#endif