# Search

		Set(HEADER_GC_CHANGE_SPEED, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCChangeSpeed), STATIC_SIZE_PACKET));

# Add after

#ifdef ENABLE_EVENT_MANAGER
		Set(HEADER_GC_EVENT_MANAGER, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCEventManager), DYNAMIC_SIZE_PACKET));
#endif