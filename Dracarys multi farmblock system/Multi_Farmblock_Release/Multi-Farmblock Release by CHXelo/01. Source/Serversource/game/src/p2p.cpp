//Include hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//In der Funktion: void P2P_MANAGER::Boot(LPDESC d)
//unter: p.bChannel = g_bChannel;

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		strlcpy(p.cMAIf, d->GetLoginMacAdress(), sizeof(p.cMAIf));
		p.i8BlockState = CAntiMultipleFarm::AF_GENERATE_NEW_STATE;
#endif

//In der Funktion: void P2P_MANAGER::Login(LPDESC d, const TPacketGGLogin * p)
//unter: pkCCI->bChannel = p->bChannel;

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	strlcpy(pkCCI->cMAIf, p->cMAIf, sizeof(pkCCI->cMAIf));
#endif

//In der selben Funktion über: if (UpdateP2P) {

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	CAntiMultipleFarm::instance().P2PLogin(pkCCI->cMAIf, pkCCI->dwPID, p->i8BlockState);
#endif

//Funktion mit Define austauschen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
void P2P_MANAGER::Logout(CCI* pkCCI, bool is_warping)
#else
void P2P_MANAGER::Logout(CCI * pkCCI)
#endif

//In der selben Funktion über: m_map_pkCCI.erase(name);

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	CAntiMultipleFarm::instance().P2PLogout(pkCCI->cMAIf, pkCCI->dwPID, is_warping);
#endif

//Funktion mit Define austauschen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
void P2P_MANAGER::Logout(const char* c_pszName, bool is_warping)
#else
void P2P_MANAGER::Logout(const char * c_pszName)
#endif

//In der selben Funktion austauschen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	Logout(pkCCI, is_warping);
#else
	Logout(pkCCI);
#endif
