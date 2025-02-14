# Search

	HEADER_GC_AUTH_SUCCESS = 150,

# Add before

#ifdef ENABLE_PVP_TOURNAMENT
	HEADER_GC_PVP_DUEL = 141,
#endif

# Add

#ifdef ENABLE_PVP_TOURNAMENT
typedef struct SPacketGCPvPInfo
{
	BYTE	header;
	DWORD	size;
} TPacketGCPvPInfo;
typedef struct SPvPDuelData {
	DWORD id;
	BYTE race;
	char name[CHARACTER_NAME_MAX_LEN + 1];
	BYTE percent;
	unsigned int minHP;
	unsigned int maxHP;
	BYTE	score;
	bool	isPoisoned;
}TPvPDuelData;
enum
{
	PVP_DATA_UPDATE,
	PVP_DATA_UPDATE_HP,
	PVP_DATA_UPDATE_SCORE,
	PVP_DATA_DELETE,
	PVP_DATA_START_TIME,
	PVP_DATA_CLEAR_TARGET,
};
#endif

