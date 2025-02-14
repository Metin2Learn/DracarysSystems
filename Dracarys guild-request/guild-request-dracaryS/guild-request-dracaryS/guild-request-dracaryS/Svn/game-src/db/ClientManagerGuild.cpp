# Search

	snprintf(szQuery, sizeof(szQuery), "DELETE FROM player.guild_comment WHERE guild_id=%u", p->dwGuild);
	CDBManager::instance().AsyncQuery(szQuery);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	snprintf(szQuery, sizeof(szQuery), "DELETE FROM player.request_list WHERE guild_id=%u", p->dwGuild);
	CDBManager::instance().AsyncQuery(szQuery);
#endif