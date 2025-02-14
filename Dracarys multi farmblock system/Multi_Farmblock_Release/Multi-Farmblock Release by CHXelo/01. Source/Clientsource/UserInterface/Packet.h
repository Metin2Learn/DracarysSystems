//Über

enum
{
	HEADER_CG_LOGIN								= 1
	
//Hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
enum EMacAdress
{
	MA_LENGTH = 255,
	MULTIPLE_FARM_MAX_ACCOUNT = 2,
};
#endif

//Client-Gameserver Packet hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	HEADER_CG_ANTI_FARM							= 229,
#endif

//Gameserver-Client Packet hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	HEADER_GC_ANTI_FARM							= 199,
#endif

//Hinzufügen zum Packet (only Define)

typedef struct command_login2
{
	BYTE	header;
	char	name[ID_MAX_NUM + 1];
	DWORD	login_key;
    DWORD	adwClientKey[4];
#ifdef ENABLE_ANTI_MULTIPLE_FARM
	char	cMAIf[MA_LENGTH + 1];
#endif
} TPacketCGLogin2;

//Am Ende der Datei hinzufügen über -> #pragma pack(pop)

#ifdef ENABLE_ANTI_MULTIPLE_FARM
enum EAntiFarmSubHeader
{
	AF_SH_SENDING_DATA,
	AF_SH_SEND_STATUS_UPDATE,
	AF_SH_SENDING_CONFIRM_DATA,
};

typedef struct SAntiFarmPlayerInfo
{
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	DWORD	dwPID;
	bool	bDropStatus;
} TAntiFarmPlayerInfo;

typedef struct SSendAntiFarmInfo
{
	BYTE	header;
	int		size;
	BYTE	subheader;
} TSendAntiFarmInfo;
#endif
