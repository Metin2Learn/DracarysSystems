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

	BYTE dayCount;
	if (!Recv(sizeof(BYTE), &dayCount))
		return false;

	for (BYTE j = 0; j < dayCount; ++j)
	{
		BYTE dayIndex;
		if (!Recv(sizeof(BYTE), &dayIndex))
			return false;
		BYTE dayEventCount;
		if (!Recv(sizeof(BYTE), &dayEventCount))
			return false;
		if (dayEventCount)
		{
			std::vector<TEventManagerData> m_vec;
			m_vec.resize(dayEventCount);
			if (!Recv(sizeof(TEventManagerData) * dayEventCount, &m_vec[0]))
				return false;
			for (BYTE j = 0; j < m_vec.size(); ++j)
			{
				const TEventManagerData& eventPtr = m_vec[j];
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "AppendEvent", Py_BuildValue("(iissiiiiiiiii)", dayIndex, eventPtr.eventIndex, eventPtr.startText, eventPtr.endText, eventPtr.empireFlag, eventPtr.channelFlag,eventPtr.value[0], eventPtr.value[1], eventPtr.value[2], eventPtr.value[3], eventPtr.startRealTime, eventPtr.endRealTime, eventPtr.isAlreadyStart?1:0));
			}
		}
	}
	return true;
}
#endif

