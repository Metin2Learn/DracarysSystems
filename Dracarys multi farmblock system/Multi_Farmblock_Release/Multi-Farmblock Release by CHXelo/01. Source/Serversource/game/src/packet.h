//Client-Gameserver Packet hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	HEADER_CG_ANTI_FARM							= 229,
#endif

//Gameserver-Client Packet hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	HEADER_GC_ANTI_FARM							= 199,
#endif

//Gameserver-Gameserver Packet hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	HEADER_GG_ANTI_FARM						= 36,
#endif

//Im Packet: typedef struct SPacketGGLogin folgendes hinzufügen
//unter: BYTE	bChannel;

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	char	cMAIf[MA_LENGTH + 1];
	int8_t	i8BlockState;
#endif

//Im Packet: typedef struct SPacketGGLogout folgendes hinzufügen
//unter: char	szName[CHARACTER_NAME_MAX_LEN + 1];

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	bool	bAFisWarping;
#endif

//Im Packet: typedef struct command_login2
//unter: DWORD	adwClientKey[4];

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	char	cMAIf[MA_LENGTH + 1];
#endif

//Am Ende der Datei hinzufügen über -> #pragma pack()

#ifdef ENABLE_ANTI_MULTIPLE_FARM
enum EAntiFarmSubHeader
{
	AF_SH_SENDING_DATA,
	AF_SH_SEND_STATUS_UPDATE,
	AF_SH_SENDING_CONFIRM_DATA,
};

typedef struct SAntiFarmPlayerInfo
{
	SAntiFarmPlayerInfo(DWORD dwPID, bool bDropStatus) :
		dwPID(dwPID), bDropStatus(bDropStatus)
	{
		memset(szName, 0, sizeof(szName));
	}

	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	DWORD	dwPID;
	bool	bDropStatus;
} TAntiFarmPlayerInfo;

typedef struct SSendAntiFarmInfo
{
	SSendAntiFarmInfo(BYTE header, int size, BYTE subheader) :
		header(header), size(size), subheader(subheader)
	{}

	BYTE	header;
	int		size;
	BYTE	subheader;
} TSendAntiFarmInfo;
#endif
