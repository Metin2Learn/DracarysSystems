# Add

#ifdef ENABLE_GUILD_REQUEST
bool CPythonNetworkStream::SendGuildRequestName(BYTE tabIndex, const char* guildName)
{
	TPacketCGGuildRequest p;
	p.bHeader = HEADER_CG_GUILD_REQUEST;
	p.sub_index = SUB_REQUEST_NAME;
	if (!Send(sizeof(TPacketCGGuildRequest), &p))
	{
		Tracef("SendGuildRequestName Packet error\n");
		return false;
	}
	if (!Send(sizeof(BYTE), &tabIndex))
	{
		Tracef("SendGuildRequestName Packet Error\n");
		return false;
	}
	struct req_name { char name[GUILD_NAME_MAX_LEN + 1]; };
	req_name x;
	strcpy(x.name, guildName);
	if (!Send(sizeof(req_name), &x))
	{
		Tracef("SendGuildRequestName Packet Error\n");
		return false;
	}
	return SendSequence();
}
bool CPythonNetworkStream::SendGuildRequestPage(BYTE tabIndex, int pageIndex)
{
	TPacketCGGuildRequest p;
	p.bHeader = HEADER_CG_GUILD_REQUEST;
	p.sub_index = SUB_REQUEST_PAGEINDEX;
	if (!Send(sizeof(TPacketCGGuildRequest), &p))
	{
		Tracef("SendGuildRequestPage Packet error\n");
		return false;
	}
	if (!Send(sizeof(BYTE), &tabIndex))
	{
		Tracef("SendGuildRequestPage Packet Error\n");
		return false;
	}
	if (!Send(sizeof(int), &pageIndex))
	{
		Tracef("SendGuildRequestPage Packet Error\n");
		return false;
	}

	return SendSequence();
}
bool CPythonNetworkStream::SendGuildRequest(DWORD guildIndex, BYTE requestIndex)
{
	TPacketCGGuildRequest p;
	p.bHeader = HEADER_CG_GUILD_REQUEST;
	p.sub_index = SUB_REQUEST_REQUEST;
	if (!Send(sizeof(TPacketCGGuildRequest), &p))
	{
		Tracef("SendGuildRequest Packet error\n");
		return false;
	}
	if (!Send(sizeof(DWORD), &guildIndex))
	{
		Tracef("SendGuildRequest Packet Error\n");
		return false;
	}
	if (!Send(sizeof(BYTE), &requestIndex))
	{
		Tracef("SendGuildRequest Packet Error\n");
		return false;
	}
	return SendSequence();
}
#endif
