# Search

		snprintf(queryStr, sizeof(queryStr), "DELETE FROM player.messenger_list WHERE account='%s' OR companion='%s'", szName, szName);
		CDBManager::instance().AsyncQuery(queryStr);

# Add after

#ifdef ENABLE_GUILD_REQUEST
		snprintf(queryStr, sizeof(queryStr), "DELETE FROM player.request_list WHERE pid = %d", pi->player_id);
		CDBManager::instance().AsyncQuery(queryStr);
#endif