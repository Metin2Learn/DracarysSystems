# Search

	HEADER_GC_HANDSHAKE_OK = 0xfc,

# Add before

#ifdef ENABLE_GUILD_REQUEST
	HEADER_CG_GUILD_REQUEST = 234,
	HEADER_GC_GUILD_REQUEST = 234,
#endif

# Add


#ifdef ENABLE_GUILD_REQUEST
typedef struct SGuildRequest
{
	WORD	index;
	DWORD	g_id;
	char	name[GUILD_NAME_MAX_LEN + 1];
	BYTE	level;
	DWORD	ladder_point;
	WORD	member[2];
	bool	isRequest;
} TGuildRequest;
typedef struct SPacketGCGuildRequest
{
	BYTE	header;
	DWORD	size;
	BYTE	sub_index;
} TPacketGCGuildRequest;
typedef struct SPacketCGGuildRequest
{
	BYTE	bHeader;
	BYTE	sub_index;
} TPacketCGGuildRequest;
enum
{
	SUB_REQUEST_PAGEINDEX,
	SUB_REQUEST_NAME,
	SUB_REQUEST_REQUEST,
};
typedef struct guild_request_
{
	WORD	index;
	DWORD	pid;
	char	name[CHARACTER_NAME_MAX_LEN + 1];
	int		level;
	int		race;
	int		skillIndex;
} TGuild_request;
#endif
