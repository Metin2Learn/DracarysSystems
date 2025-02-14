# Search

	void		ChangeMaster(DWORD dwGID);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	void		SortGuildCache();
	void		SendData(LPCHARACTER ch, BYTE tabIndex, DWORD pageIndex, const char* guildName);
	void		SendRequest(LPCHARACTER ch, DWORD guildID, BYTE requestIndex);
#endif

# Search

	friend class CGuild;

# Add before

#ifdef ENABLE_GUILD_REQUEST
	std::map<std::string, CGuild*> m_mapNameGuild;

	std::vector<CGuild*> m_mapNameAll;
	std::vector<CGuild*> m_mapNameShinsoo;
	std::vector<CGuild*> m_mapNameChunjo;
	std::vector<CGuild*> m_mapNameJinno;
#endif

