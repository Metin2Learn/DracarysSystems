# Search

#pragma pack()

#Add before

#if defined(__MISSION_BOOKS__)
typedef struct SMissionBookData
{
	WORD	id;
	DWORD	missionItemIndex;
	BYTE type;
	DWORD subtype;
	BYTE levelRange;
	long long max;
	int maxTime;
	long long gold[2];
	DWORD exp[2];
	DWORD rewardItems[6];
	WORD rewardCount[6];
} TMissionBookData;
typedef struct SMissionBook
{
	long long value;
	int	leftTime;
	bool reward;
	int endTime;
}TMissionBook;
enum
{
	MISSION_BOOK_MAX = 10,

	MISSION_BOOK_TYPE_MONSTER = 0,
	MISSION_BOOK_TYPE_METINSTONE = 1,
	MISSION_BOOK_TYPE_BOSS = 2,

};
#endif

