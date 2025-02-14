# Search

	HEADER_GC_SHOP = 38,

# add after

#ifdef ENABLE_EVENT_MANAGER
	HEADER_GC_EVENT_MANAGER = 39,
#endif

# add

#ifdef ENABLE_EVENT_MANAGER
typedef struct SPacketGCEventManager
{
	BYTE	header;
	DWORD	size;
} TPacketGCEventManager;
#endif