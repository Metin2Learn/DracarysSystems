# Add

#ifdef ENABLE_EVENT_MANAGER
#include "buffer_manager.h"
#endif



# Search

private:
	int					m_iMobItemRate;

# Add before

#ifdef ENABLE_EVENT_MANAGER
public:
	void			ClearEventData();
	bool			CloseEventManuel(BYTE eventIndex);
	void			SetEventData(BYTE dayIndex, const std::vector<TEventManagerData>& m_data);
	void			SetEventStatus(const WORD eventID, const bool eventStatus, const int endTime);
	void			SendDataPlayer(LPCHARACTER ch);
	void			CheckBonusEvent(LPCHARACTER ch);
	void			UpdateAllPlayerEventData();
	void			CompareEventSendData(TEMP_BUFFER* buf);
	const TEventManagerData* CheckEventIsActive(BYTE eventIndex, BYTE empireIndex = 0);
	void			CheckEventForDrop(LPCHARACTER pkChr, LPCHARACTER pkKiller, std::vector<LPITEM>& vec_item);
protected:
	std::map<BYTE, std::vector<TEventManagerData>>	m_eventData;
#endif