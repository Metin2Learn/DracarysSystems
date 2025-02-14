# Search

		default:
			ret = RecvDefaultPacket(header);

# Add before

#ifdef ENABLE_EVENT_MANAGER
		case HEADER_GC_EVENT_MANAGER:
			ret = RecvEventManager();
			break;
#endif

# add

#ifdef ENABLE_EVENT_MANAGER
bool CPythonNetworkStream::RecvEventManager()
{
	TPacketGCEventManager p;
	if (!Recv(sizeof(TPacketGCEventManager), &p))
		return false;

	BYTE subIndex;
	if (!Recv(sizeof(BYTE), &subIndex))
		return false;

	if (subIndex == EVENT_MANAGER_LOAD)
	{
		BYTE dayCount;
		if (!Recv(sizeof(BYTE), &dayCount))
			return false;
		int serverTime;
		if (!Recv(sizeof(int), &serverTime))
			return false;

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "ClearEventManager", Py_BuildValue("()"));
		for (BYTE j = 0; j < dayCount; ++j)
		{
			BYTE dayIndex;
			if (!Recv(sizeof(BYTE), &dayIndex))
				return false;
			BYTE dayEventCount;
			if (!Recv(sizeof(BYTE), &dayEventCount))
				return false;
			if (dayEventCount > 0)
			{
				std::vector<TEventManagerData> m_vec;
				m_vec.resize(dayEventCount);
				if (!Recv(dayEventCount * sizeof(TEventManagerData), &m_vec[0]))
					return false;
				for (const auto& eventPtr : m_vec)
				{
					const time_t startTime = eventPtr.startTime;					
					const time_t endTime = eventPtr.endTime;
					const struct tm vEventStartKey = *localtime(&startTime);
					const struct tm vEventEndKey = *localtime(&endTime);
					char startTimeText[24];
					snprintf(startTimeText, sizeof(startTimeText), "%d-%02d-%02d %02d:%02d:%02d", vEventStartKey.tm_year + 1900, vEventStartKey.tm_mon + 1, vEventStartKey.tm_mday, vEventStartKey.tm_hour, vEventStartKey.tm_min, vEventStartKey.tm_sec);
					char endTimeText[24];
					snprintf(endTimeText, sizeof(endTimeText), "%d-%02d-%02d %02d:%02d:%02d", vEventEndKey.tm_year + 1900, vEventEndKey.tm_mon + 1, vEventEndKey.tm_mday, vEventEndKey.tm_hour, vEventEndKey.tm_min, vEventEndKey.tm_sec);
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "AppendEvent", Py_BuildValue("(iiissiiiiiiiii)", dayIndex, eventPtr.eventID, eventPtr.eventIndex, startTimeText, endTimeText, eventPtr.empireFlag, eventPtr.channelFlag, eventPtr.value[0], eventPtr.value[1], eventPtr.value[2], eventPtr.value[3], eventPtr.startTime - serverTime, eventPtr.endTime == 0 ? 0 : eventPtr.endTime - serverTime, eventPtr.eventStatus));
				}
			}
		}
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshEventManager", Py_BuildValue("()"));
	}
	else if (subIndex == EVENT_MANAGER_EVENT_STATUS)
	{
		WORD eventID;
		if (!Recv(sizeof(WORD), &eventID))
			return false;
		bool eventStatus;
		if (!Recv(sizeof(bool), &eventStatus))
			return false;
		int endTime;
		if (!Recv(sizeof(int), &endTime))
			return false;
		int serverTime;
		if (!Recv(sizeof(int), &serverTime))
			return false;

		const time_t endTimeReal = endTime;
		const struct tm vEventEndKey = *localtime(&endTimeReal);
		char endTimeText[24];
		snprintf(endTimeText, sizeof(endTimeText), "%d-%02d-%02d %02d:%02d:%02d", vEventEndKey.tm_year + 1900, vEventEndKey.tm_mon + 1, vEventEndKey.tm_mday, vEventEndKey.tm_hour, vEventEndKey.tm_min, vEventEndKey.tm_sec);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshEventStatus", Py_BuildValue("(iiis)", eventID, eventStatus, endTime == 0? 0 : endTime - serverTime, endTimeText));
	}
	return true;
}
#endif

