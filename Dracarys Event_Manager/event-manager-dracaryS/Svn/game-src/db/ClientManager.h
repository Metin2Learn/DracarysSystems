
# Search

	bool		InitializeObjectTable();

# add after

#ifdef ENABLE_EVENT_MANAGER
public:
	bool		InitializeEventManager(bool updateFromGameMaster = false);
	void		RecvEventManagerPacket(const char* data);
	void		UpdateEventManager();
	void		SendEventData(CPeer* pkPeer = NULL, bool updateFromGameMaster = false);
protected:
	std::map<BYTE, std::vector<TEventManagerData>> m_EventManager;
#endif