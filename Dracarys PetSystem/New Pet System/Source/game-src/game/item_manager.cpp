# Search

	t.vnum = item->GetOriginalVnum();

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	strlcpy(t.name,item->GetNewName(),sizeof(t.name));
#endif

