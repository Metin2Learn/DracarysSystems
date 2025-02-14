# Search

		default:
			ret = RecvDefaultPacket(header);

# Add before

#ifdef ENABLE_GUILD_REQUEST
		case HEADER_GC_GUILD_REQUEST:
			ret = RecvGuildRequest();
			break;
#endif

# Add

#ifdef ENABLE_GUILD_REQUEST
bool CPythonNetworkStream::RecvGuildRequest()
{
	TPacketGCGuildRequest p;
	if (!Recv(sizeof(TPacketGCGuildRequest), &p))
		return false;
	switch (p.sub_index)
	{
		case SUB_REQUEST_NAME:
		{
			BYTE tabIndex;
			if (!Recv(sizeof(BYTE), &tabIndex))
				return false;
			int dataSize;
			if (!Recv(sizeof(int), &dataSize))
				return false;
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildRequestLoadName", Py_BuildValue("(i)", tabIndex));
			if (dataSize)
			{
				std::vector<TGuildRequest> m_cache;
				m_cache.resize(dataSize);
				if (!Recv(sizeof(TGuildRequest)*dataSize, &m_cache[0]))
					return false;
				for (DWORD j = 0; j < m_cache.size();++j)
				{
					const TGuildRequest& request = m_cache[j];
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildRequestSetItem", Py_BuildValue("(iisiiiii)", request.index, request.g_id, request.name, request.level, request.ladder_point, request.member[0], request.member[1], request.isRequest ? 1 : 0));
				}
			}
		}
		break;
		case SUB_REQUEST_PAGEINDEX:
		{
			BYTE tabIndex;
			if (!Recv(sizeof(BYTE), &tabIndex))
				return false;
			DWORD pageIndex;
			if (!Recv(sizeof(DWORD), &pageIndex))
				return false;
			int maxPage;
			if (!Recv(sizeof(int), &maxPage))
				return false;
			int dataSize;
			if (!Recv(sizeof(int), &dataSize))
				return false;
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildRequestLoadPage", Py_BuildValue("(iii)", tabIndex, pageIndex, maxPage));
			if (dataSize)
			{
				std::vector<TGuildRequest> m_cache;
				m_cache.resize(dataSize);
				if (!Recv(sizeof(TGuildRequest) * dataSize, &m_cache[0]))
					return false;
				for (DWORD j = 0; j < m_cache.size(); ++j)
				{
					const TGuildRequest& request = m_cache[j];
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildRequestSetItem", Py_BuildValue("(iisiiiii)", request.index, request.g_id, request.name, request.level, request.ladder_point, request.member[0], request.member[1], request.isRequest ? 1 : 0));
				}
			}
		}
		break;
		case SUB_REQUEST_REQUEST:
		{
			BYTE tabIndex;
			if (!Recv(sizeof(BYTE), &tabIndex))
				return false;
			DWORD pageIndex;
			if (!Recv(sizeof(DWORD), &pageIndex))
				return false;
			int maxPage;
			if (!Recv(sizeof(int), &maxPage))
				return false;
			int dataSize;
			if (!Recv(sizeof(int), &dataSize))
				return false;
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildRequestLoadPage", Py_BuildValue("(iii)", tabIndex, pageIndex, maxPage));
			if (dataSize)
			{
				std::vector<TGuild_request> m_cache;
				m_cache.resize(dataSize);
				if (!Recv(sizeof(TGuild_request) * dataSize, &m_cache[0]))
					return false;
				for (DWORD j = 0; j < m_cache.size(); ++j)
				{
					const TGuild_request& request = m_cache[j];
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "GuildRequestSetRequest", Py_BuildValue("(iisiii)", request.index, request.pid, request.name, request.level, request.race, request.skillIndex));
				}
			}
		}
		break;
	}
	return true;
}
#endif
