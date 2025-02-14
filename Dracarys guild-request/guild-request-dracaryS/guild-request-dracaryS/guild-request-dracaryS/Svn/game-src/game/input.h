#Search

	int			Chat(LPCHARACTER ch, const char* data, size_t uiBytes);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	int			GuildRequest(LPCHARACTER ch, const char* data, size_t uiBytes);
#endif