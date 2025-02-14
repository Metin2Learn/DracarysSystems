# Search

	case HEADER_DG_RELOAD_ADMIN:
		ReloadAdmin(c_pData);
		break;

# Add after

#ifdef ENABLE_EVENT_MANAGER
	case HEADER_DG_EVENT_MANAGER:
		EventManager(c_pData);
		break;
#endif

# Add

#ifdef ENABLE_EVENT_MANAGER
void CInputDB::EventManager(const char* c_pData)
{
	CHARACTER_MANAGER& chrMngr = CHARACTER_MANAGER::Instance();
	const BYTE subIndex = *(BYTE*)c_pData;
	c_pData += sizeof(BYTE);
	if (subIndex == EVENT_MANAGER_LOAD)
	{
		chrMngr.ClearEventData();
		const BYTE dayCount = *(BYTE*)c_pData;
		c_pData += sizeof(BYTE);
		for (DWORD x = 0; x < dayCount; ++x)
		{
			const BYTE dayIndex = *(BYTE*)c_pData;
			c_pData += sizeof(BYTE);
			const BYTE dayEventCount = *(BYTE*)c_pData;
			c_pData += sizeof(BYTE);
			std::vector<TEventManagerData> m_vec;
			m_vec.clear();
			for (DWORD j = 0; j < dayEventCount; ++j)
			{
				const TEventManagerData& eventData = *(TEventManagerData*)c_pData;
				c_pData += sizeof(TEventManagerData);
				tm start = eventData.startTime;
				//sys_err("START TIME: %d-%d-%d %d:%d:%d", start.tm_year, start.tm_mon, start.tm_mday, start.tm_hour, start.tm_min, start.tm_sec);
				//sys_err("DIFFERENCE: %d", eventData.startRealTime-time(0));
				m_vec.emplace_back(eventData);
			}
			chrMngr.SetEventData(dayIndex, m_vec);
		}
	}
	else if (EVENT_MANAGER_EVENT_STATUS == subIndex)
	{
		const bool eventStatus = *(bool*)c_pData;
		c_pData += sizeof(bool);
		const TEventManagerData& eventData = *(TEventManagerData*)c_pData;
		c_pData += sizeof(TEventManagerData);
		chrMngr.SetEventStatus(eventData, eventStatus);
	}
}
#endif
