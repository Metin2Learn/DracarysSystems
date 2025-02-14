# Search

		Set(HEADER_GC_PING, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPing), STATIC_SIZE_PACKET));

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
		Set(HEADER_GC_PVP_DUEL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPvPInfo), DYNAMIC_SIZE_PACKET));
#endif

