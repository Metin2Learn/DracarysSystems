//Hinzufügen unter:
//bool SendChangeNamePacket(BYTE index, const char *name);

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		bool SendAntiFarmStatus(std::vector<DWORD> dwPIDs);
#endif

//Hinzufügen unter:
//bool RecvChannelPacket();

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		bool RecvAntiFarmInformation();
#endif
