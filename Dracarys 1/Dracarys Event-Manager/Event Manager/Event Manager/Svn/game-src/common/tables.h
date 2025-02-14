# search

	HEADER_DG_MAP_LOCATIONS						= 0xfe,

# Add after

#ifdef ENABLE_EVENT_MANAGER
	HEADER_DG_EVENT_MANAGER						= 212,
#endif

# Add

#ifdef ENABLE_EVENT_MANAGER
typedef struct event_struct_
{
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
}TEventManagerData;
enum
{
	EVENT_MANAGER_LOAD,
	EVENT_MANAGER_EVENT_STATUS,


	EVENT_NONE = 0,
	BONUS_EVENT = 1,
	DOUBLE_BOSS_LOOT_EVENT = 2,
	DOUBLE_METIN_LOOT_EVENT = 3,
	DOUBLE_MISSION_BOOK_EVENT = 4,
	DUNGEON_COOLDOWN_EVENT = 5,
	DUNGEON_TICKET_LOOT_EVENT = 6,
	EMPIRE_WAR_EVENT = 7,
	MOONLIGHT_EVENT = 8,
	TOURNAMENT_EVENT = 9,
	WHELL_OF_FORTUNE_EVENT = 10,
	HALLOWEEN_EVENT = 11,
	NPC_SEARCH_EVENT = 12,

};
#endif