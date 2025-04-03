# Search

public:

# Add before

#if defined(__MISSION_BOOKS__)
public:
	void	LoadMissionBook();
	void	GiveNewMission(LPITEM missionBook, LPCHARACTER ch);
	const TMissionBookData* GetMissionData(WORD id);
protected:
	std::map<WORD, TMissionBookData> m_mapMissionData;
#endif

