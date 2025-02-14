
# Search

	bool		InitializeObjectTable();

# add after

#ifdef ENABLE_EVENT_MANAGER
	bool		InitializeEventManager();
	void		UpdateEventManager();
	void		SendEventData(CPeer* pkPeer = NULL);
	std::map<BYTE, std::vector<TEventManagerData>> m_EventManager;
#endif
