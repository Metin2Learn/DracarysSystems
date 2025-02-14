# Search

private:
	int					m_iMobItemRate;

# Add before

#ifdef ENABLE_EVENT_MANAGER
public:
	void			ClearEventData();
	void			SetEventData(BYTE dayIndex, const std::vector<TEventManagerData>& m_data);
	void			SetEventStatus(const TEventManagerData& m_data, bool eventStatus);
	void			SendDataPlayer(LPCHARACTER ch);
	void			CheckBonusEvent(LPCHARACTER ch);
	bool			CheckEventIsActive(BYTE eventIndex);
	void			CheckEventForDrop(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM>& vec_item);
protected:
	std::map<BYTE, std::vector<TEventManagerData>>	m_eventData;
#endif