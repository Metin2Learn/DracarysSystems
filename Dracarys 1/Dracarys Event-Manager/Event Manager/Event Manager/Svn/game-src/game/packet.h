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
typedef struct event_struct_client_
{
	BYTE	eventIndex;
	char	startText[40];
	int		startRealTime;
	char	endText[40];
	int		endRealTime;
	bool	isAlreadyStart;
	BYTE	empireFlag;
	BYTE	channelFlag;
	DWORD	value[4];

	/*
	BYTE	eventIndex;
	char	startText[40];
	tm		startTime;
	time_t	startRealTime;
	char	endText[40];
	tm		endTime;
	time_t	endRealTime;
	BYTE	empireFlag;
	BYTE	channelFlag;
	DWORD	value[4];
	*/
}TEventManagerDataClient;
#endif