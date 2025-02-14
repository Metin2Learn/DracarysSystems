//Include hinzufügen:

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//In folgendes Packet hinzufügen:
//bool CPythonNetworkStream::SendLoginPacketNew(const char * c_szName, const char * c_szPassword)
//unter:
//LoginPacket.name[ID_MAX_NUM]='\0';

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	auto mac_adress = CAntiMultipleFarm::Instance().GetClientMacAdress();
	strncpy(LoginPacket.cMAIf, mac_adress, sizeof(LoginPacket.cMAIf) - 1);
	LoginPacket.cMAIf[MA_LENGTH] = '\0';
#endif
