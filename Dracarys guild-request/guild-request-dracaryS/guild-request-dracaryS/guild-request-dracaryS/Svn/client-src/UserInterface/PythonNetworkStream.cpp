#Search

	Set(HEADER_GC_DAMAGE_INFO, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDamageInfo), STATIC_SIZE_PACKET));

# Add after

#ifdef ENABLE_GUILD_REQUEST
		Set(HEADER_GC_GUILD_REQUEST, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCGuildRequest), DYNAMIC_SIZE_PACKET));
#endif
