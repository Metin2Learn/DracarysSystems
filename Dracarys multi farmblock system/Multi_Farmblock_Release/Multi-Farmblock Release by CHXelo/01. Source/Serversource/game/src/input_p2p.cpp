//Include hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//In der Funktion: void CInputP2P::Logout(LPDESC d, const char * c_pData)
//"P2P_MANAGER::instance().Logout(p->szName);" austauschen mit dem Define
//Volle Funktion von mir:

void CInputP2P::Logout(LPDESC d, const char * c_pData)
{
	TPacketGGLogout * p = (TPacketGGLogout *) c_pData;

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	P2P_MANAGER::instance().Logout(p->szName, p->bAFisWarping);
#else
	P2P_MANAGER::instance().Logout(p->szName);
#endif
}

//In der Funktion: int CInputP2P::Analyze(LPDESC d, BYTE bHeader, const char * c_pData)
// ganz unten über hinzufügen:
//	}

//	return (iExtraLen);
//}

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		case HEADER_GG_ANTI_FARM:
			RecvAntiFarmUpdateStatus(d, c_pData);
			break;
#endif

//Am Ende der Datei hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
auto CInputP2P::RecvAntiFarmUpdateStatus(LPDESC d, const char* c_pData) -> void
{
	if (!d) return;

	CAntiMultipleFarm::TP2PChangeDropStatus* p = (CAntiMultipleFarm::TP2PChangeDropStatus*)c_pData;

	std::vector <DWORD> dwPIDs;
	for (uint8_t i = 0; i < MULTIPLE_FARM_MAX_ACCOUNT; ++i)
		dwPIDs.emplace_back(p->dwPIDs[i]);

	CAntiMultipleFarm::instance().P2PSendBlockDropStatusChange(p->cMAIf, dwPIDs);
}
#endif
