# Search

	CHARACTER_SET		m_set_pkChrPendingDestroy;

# Add after

#ifdef ENABLE_REWARD_SYSTEM
public:
	void	LoadRewardData();
	void	SetRewardData(BYTE rewardIndex, const char* playerName, bool isP2P);
	bool	IsRewardEmpty(BYTE rewardIndex);
	void	SendRewardInfo(LPCHARACTER ch);
protected:
	std::map<BYTE, TRewardInfo> m_rewardData;
#endif