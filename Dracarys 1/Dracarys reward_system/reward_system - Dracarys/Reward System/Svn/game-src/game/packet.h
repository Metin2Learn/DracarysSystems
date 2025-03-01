# Search

	HEADER_GG_SETUP = 9,

# Add after

#ifdef ENABLE_REWARD_SYSTEM
	HEADER_GG_REWARD_INFO = 41,
#endif


# add

#ifdef ENABLE_REWARD_SYSTEM
#include <vector>
typedef struct reward_infos
{
	char lc_text[100];
	char playerName[CHARACTER_NAME_MAX_LEN+1];
	std::vector<std::pair<DWORD, DWORD>> m_rewardItems;
}TRewardInfo;
enum
{
	REWARD_115 = 1,
	REWARD_PET_115=2,
	REWARD_120=3,
	REWARD_LEGENDARY_SKILL=4,
	REWARD_LEGENDARY_SKILL_SET=5,
	REWARD_THANDRUIL=6,
	REWARD_HYDRA=7,
	REWARD_CRYSTAL_DRAGON=8,
	REWARD_OFFLINESHOP_SLOT=9,
	REWARD_INVENTORY_SLOT=10,
	REWARD_AVERAGE=11,
	REWARD_ELEMENT=12,
	REWARD_BATTLEPASS=13,
	REWARD_CUSTOM_SASH=14,
	REWARD_AURA=15,
	REWARD_ENERGY=16,
	REWARD_112_BIO=17,
	REWARD_120_BIO=18,
	REWARD_LEADER_SHIP=19,
	REWARD_BUFFI_LEGENDARY_SKILL=20,
	REWARD_MAX,
};
typedef struct SPacketGGRewardInfo
{
	BYTE	bHeader;
	BYTE	rewardIndex;
	char	playerName[CHARACTER_NAME_MAX_LEN+1];
} TPacketGGRewardInfo;
#endif
