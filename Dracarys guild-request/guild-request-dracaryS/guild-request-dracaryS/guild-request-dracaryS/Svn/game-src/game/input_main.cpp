# Search

	case HEADER_CG_HACK:
		Hack(ch, c_pData);
		break;

# Add after

#ifdef ENABLE_GUILD_REQUEST
	case HEADER_CG_GUILD_REQUEST:
		if ((iExtraLen = GuildRequest(ch, c_pData, m_iBufferLeft)) < 0)
			return -1;
		break;
#endif

# Add

#ifdef ENABLE_GUILD_REQUEST
int CInputMain::GuildRequest(LPCHARACTER ch, const char* data, size_t uiBytes)
{
	TPacketCGGuildRequest* p = (TPacketCGGuildRequest*)data;
	if (p->sub_index == SUB_REQUEST_PAGEINDEX)
	{
		int extraLen = sizeof(BYTE) + sizeof(int);
		if (uiBytes < (sizeof(TPacketCGGuildRequest) + extraLen))
			return -1;
		data += sizeof(TPacketCGGuildRequest);
		const BYTE tabIndex = *(BYTE*)data;
		data += sizeof(BYTE);
		const int pageIndex = *(int*)data;
		CGuildManager::Instance().SendData(ch, tabIndex, pageIndex, NULL);
		return extraLen;
	}
	else if (p->sub_index == SUB_REQUEST_NAME)
	{
		struct req_name{char name[GUILD_NAME_MAX_LEN + 1];};
		int extraLen = (sizeof(BYTE)+sizeof(req_name));
		if (uiBytes < (sizeof(TPacketCGGuildRequest) + extraLen))
			return -1;
		data += sizeof(TPacketCGGuildRequest);
		const BYTE tabIndex = *(BYTE*)data;
		data += sizeof(BYTE);
		const req_name& request_name = *(req_name*)data;
		CGuildManager::Instance().SendData(ch, tabIndex, 0, request_name.name);
		return extraLen;
	}
	else if (p->sub_index == SUB_REQUEST_REQUEST)
	{
		int extraLen = (sizeof(DWORD)+sizeof(BYTE));
		if (uiBytes < (sizeof(TPacketCGGuildRequest) + extraLen))
			return -1;
		data += sizeof(TPacketCGGuildRequest);
		const DWORD guildID = *(DWORD*)data;
		data += sizeof(DWORD);
		const BYTE requestIndex = *(BYTE*)data;
		CGuildManager::Instance().SendRequest(ch, guildID, requestIndex);
		return extraLen;
	}
	else
	{
		sys_err("guild_request unknown sub_index %d", p->sub_index);
	}
	return -1;
}
#endif

