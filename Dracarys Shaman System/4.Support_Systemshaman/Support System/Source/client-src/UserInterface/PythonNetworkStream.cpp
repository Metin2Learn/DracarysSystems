# Search

			Set(HEADER_GC_DRAGON_SOUL_REFINE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

# Add after


#ifdef ENABLE_SUPPORT_SYSTEM
			Set(HEADER_GC_SUPPORT_SKILL, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCSupportUseSkill), STATIC_SIZE_PACKET));
#endif