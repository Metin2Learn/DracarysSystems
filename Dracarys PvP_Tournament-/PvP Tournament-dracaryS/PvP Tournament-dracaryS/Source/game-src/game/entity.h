# Search

	LPSECTREE		m_pSectree;

# add after

#ifdef ENABLE_PVP_TOURNAMENT
	bool			m_bPvPTournament;
#endif

# Search

	bool			IsObserverMode() const { return m_bIsObserver; }

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
	void			SetPvPTournament(bool bFlag);
#endif