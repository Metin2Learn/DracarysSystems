# Search

	SAutoPotionInfo			m_kAutoPotionInfo[AUTO_POTION_TYPE_NUM];

# Add after

#ifdef ENABLE_PVP_CAMERA_MODE
	bool					m_camera_Mode;
	std::string				m_mainCharacterName;
#endif

# Search

	void	SetRace(DWORD dwRace);

# Add before

#ifdef ENABLE_PVP_CAMERA_MODE
	bool	GetCameraMode() {return m_camera_Mode;}
	void	SetCameraMode(bool flag) {m_camera_Mode= flag;}
	std::string GetMainCharacterName() { return m_mainCharacterName; }
	void	SetMainCharacterName(std::string newMainCharacter) { m_mainCharacterName=newMainCharacter; }
#endif

# Search

	void	NotifyChangePKMode();

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	void	ClearTargetProcess();
#endif
