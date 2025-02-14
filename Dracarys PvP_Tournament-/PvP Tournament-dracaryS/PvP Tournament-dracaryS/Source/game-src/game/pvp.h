# Search

	void	Process();

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	void	RemoveCharactersPvP(LPCHARACTER pkChr, LPCHARACTER pkVictim);
#endif

# Search

	DWORD   m_dwLastFightTime;

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	bool	itsPvPTournament;
#endif
