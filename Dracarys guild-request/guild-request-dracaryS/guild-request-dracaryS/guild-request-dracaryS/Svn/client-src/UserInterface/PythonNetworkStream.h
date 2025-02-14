# Search

	bool SendExchangeItemDelPacket(BYTE pos);

# Add before

#ifdef ENABLE_GUILD_REQUEST
	bool SendGuildRequest(DWORD guildIndex, BYTE requestIndex);
	bool SendGuildRequestPage(BYTE tabIndex, int pageIndex);
	bool SendGuildRequestName(BYTE tabIndex, const char* guildName);
	bool RecvGuildRequest();
#endif