//Hinzufügen unter:
//Set(HEADER_GC_CHANNEL...

#ifdef ENABLE_ANTI_MULTIPLE_FARM
			Set(HEADER_GC_ANTI_FARM,						CNetworkPacketHeaderMap::TPacketType(sizeof(TSendAntiFarmInfo),						DYNAMIC_SIZE_PACKET));
#endif
