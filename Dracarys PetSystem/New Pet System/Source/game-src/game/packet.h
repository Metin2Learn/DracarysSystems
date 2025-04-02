# Search

struct packet_exchange
{
	...
};

# Add in end

#ifdef ENABLE_NEW_NAME_ITEM
	char		name[ITEM_NAME_MAX_LEN+1];
#endif

# Search


} TPacketGCItemUpdate;

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
	char		name[ITEM_NAME_MAX_LEN+1];
#endif

# Search

} TPacketGCItemSet;

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
	char		name[ITEM_NAME_MAX_LEN+1];
#endif

# Search

struct TPacketGCItemDelDeprecated
{
	...
};

# Add in the end

#ifdef ENABLE_NEW_NAME_ITEM
	char		name[ITEM_NAME_MAX_LEN+1];
#endif

# Search

HEADER_CG_MESSENGER = 67,

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	HEADER_GC_PET_POINT_CHANGE=68,
#endif

