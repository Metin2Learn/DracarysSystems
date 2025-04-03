# Search

	thecore_memcpy(&pack_exchg.aAttr, ((LPITEM)pvData)->GetAttributes(), sizeof(pack_exchg.aAttr));

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
		strlcpy(pack_exchg.name,((LPITEM) pvData)->GetNewName(),sizeof(pack_exchg.name));
#endif

# Search

		memset(&pack_exchg.aAttr, 0, sizeof(pack_exchg.aAttr));

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
		strlcpy(pack_exchg.name,"^",sizeof(pack_exchg.name));
#endif

