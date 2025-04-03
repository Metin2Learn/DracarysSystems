# Search

public:

# Add before

#if defined(__MISSION_BOOKS__)
public:
	void		SetMissionBook(BYTE missionType, BYTE value, DWORD arg, WORD level);
	void		RewardMissionBook(WORD missionID);
	void		DeleteBookMission(WORD missionID);
	void		LoadMissionData();
	void		SendMissionData();
	void		SaveMissionData();
	void		GiveNewMission(WORD missionID);
	bool		IsMissionHas(WORD missionID);
	BYTE		MissionCount();
	void		ModifySetMissionCMD(WORD missionID, std::string& cmdText);
	void		SetProtectTime(const std::string& flagname, int value);
	int			GetProtectTime(const std::string& flagname) const;
protected:
	std::map<WORD, TMissionBook> m_mapMissionData;
	std::map<std::string, int>  m_protection_Time;
#endif
