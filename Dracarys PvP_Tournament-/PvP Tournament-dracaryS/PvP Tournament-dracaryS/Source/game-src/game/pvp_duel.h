#pragma once

enum
{
	// Map Settings
	PVP_DUEL_MAP_INDEX = 98,
	PVP_DUEL_POS_COUNT = 8,
	PVP_DUEL_BASE_ROTATION = 0,
	PVP_DUEL_FIRST_PLAYER_ROTATION = 0,
	PVP_DUEL_SECOND_PLAYER_ROTATION = 180,

	// Rount Settings
	PVP_DUEL_ROUNT_MAX = 2,
	PVP_DUEL_QUARTER_FINAL_ROUNT_MAX = 3,
	PVP_DUEL_SEMI_FINAL_ROUNT_MAX = 4,
	PVP_DUEL_FINAL_ROUNT_MAX = 5,

	// Time Settings(Second)
	PVP_DUEL_POS_SEND_TIME = 10,
	PVP_DUEL_POS_SEND_TIME_AFTER_DEAD = 2,

	PVP_DUEL_FIRST_WAIT_TIME = 30,
	PVP_DUEL_WAIT_TIME = 10,

	PVP_DUEL_DONE_SEND_OUT_TIME = 60,
	
	// Move Block Range Settings
	PVP_DUEL_MOVE_MAX_DISTANCE = 2000,
	PVP_DUEL_AFTER_PULL_POISON = true,

	PVP_DUEL_BLOCK_MULTI_ACCOUNT=false,//only 1 register 1 computer

	//Default PvP Settings
	PVP_DUEL_DEFAULT_REGISTER_TIME = 60*15,//15 minute
	PVP_DUEL_DEFAULT_REGISTER_COUNT_MAX = 100,
	PVP_DUEL_DEFAULT_MIN_LEVEL = 70,
	PVP_DUEL_DEFAULT_MAX_LEVEL = 120,
	PVP_DUEL_DEFAULT_PVP_BET = 0,

	// Dont touch!
	PVP_DUEL_LEFT_NONE = 0,
	PVP_DUEL_LEFT_TYPE_LOGOUT = 1,
	PVP_DUEL_LEFT_TYPE_GM = 2,

	PVP_DUEL_DONE_WITH_WINNER = 0,
	PVP_DUEL_CLOSE_FROM_GM = 1,
	PVP_DUEL_NOT_HAVE_ENOUGHT_REGISTER = 2,

};

constexpr const char* jobNames[JOB_MAX_NUM] = { "Warrior", "Assassin", "Sura", "Shaman" };
constexpr unsigned short pvpBasePosition[2] = { 137, 191 };
constexpr unsigned short pvpArenaPosition[PVP_DUEL_POS_COUNT][2][2] = {
	
	{{116,252},{99,252}},
	{{170,252},{154,252}},
	{{98,307},{114,307}},
	{{154,306},{170,306}},
	{{99,362},{115,362}},
	{{153,361},{169,361}},
	{{115,420},{100,420}},

	{{153,420},{169,420}},
};

struct pvp_data {
	DWORD pid;
	BYTE win;
};

class CPvPDuel : public singleton<CPvPDuel>
{
public:
	CPvPDuel();
	virtual ~CPvPDuel();
	void Destroy();

	void Login(LPCHARACTER ch);
	void Logout(LPCHARACTER ch);

	int Register(LPCHARACTER ch);

	void StartProcess(LPCHARACTER ch);

	void UpdatePvPData(BYTE subHeader, BYTE arenaIndex = 0, LPCHARACTER ch = NULL);

	void Dead(LPCHARACTER pkKiller, LPCHARACTER pkVictim, BYTE winCount = 1);

	void DonePvPDuel(LPCHARACTER pkVictim, BYTE leftType = 0);
	void DonePvP(BYTE doneIndex = PVP_DUEL_DONE_WITH_WINNER);

	void ComparePvP();
	void ClosePvP();

	void SendOut(bool isStart = true);
	void SendInfoNotice(bool isStartText = false);

	const pvp_data* GetPvPData(const BYTE arenaIndex, const BYTE playerIndex);

	bool IsBlockItem(const LPITEM item, bool isEquip = false);
	void PrintBlockItemList(LPCHARACTER ch);

	void SetFlag(const char* flagname, const int value, ...);
	int	GetFlag(const char* flagname, ...);

	void SetPvPBase(LPCHARACTER ch);
	void SetPvPPos(const BYTE arenaIndex);
	void SetPvPBase(const BYTE arenaIndex);
	void StartPvP(const BYTE arenaIndex);

	int IsFighting(const DWORD playerID, const bool isNeedCheckCache = false);
	int IsFighting(LPCHARACTER ch, const bool isNeedCheckCache = false);
	bool PvPPullFunction(LPCHARACTER ch);

private:
	void DefaultSettings();
	void ComparePvPList();
	void RemoveDuelAffect(LPCHARACTER ch);
	void CheckReadyForDuel(LPCHARACTER ch);
	void AddDuelAffect(LPCHARACTER ch);
	void Notice(const char* szNotice, ...);
	void Show(LPCHARACTER ch, const long x, const long y);
	BYTE GetMaxRount();
	const LPCHARACTER GetPvPEnemy(const BYTE arenaIndex, const DWORD exceptCh);
	
	bool IsFighthingStart(const BYTE arenaIndex);


protected:
	LPEVENT processEvent;
	long long	m_llMaxBet;

	std::map<std::string, int>	m_map_pvpFlags;

	std::vector<LPCHARACTER> m_vec_PlayerList;

	std::vector<DWORD> m_vec_pvpRegisterList;
	std::map<BYTE, std::pair<pvp_data, pvp_data>> m_map_pvpList;
	std::map<BYTE, std::pair<pvp_data, pvp_data>> m_map_pvpCacheList;
};


