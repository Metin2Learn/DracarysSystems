//Hinzuf�gen unter:
//bool SendChangeNamePacket(BYTE index, const char *name);

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		bool SendAntiFarmStatus(std::vector<DWORD> dwPIDs);
#endif

//Hinzuf�gen unter:
//bool RecvChannelPacket();

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		bool RecvAntiFarmInformation();
#endif
