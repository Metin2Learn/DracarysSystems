//Include hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//In der Funktion: void CInputLogin::LoginByKey(LPDESC d, const char * data)
//unter: d->SetSecurityKey(pinfo->adwClientKey); hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	d->SetLoginMacAdress(pinfo->cMAIf);
#endif

//In der Funktion: void CInputLogin::Entergame(LPDESC d, const char * data)
//unter: marriage::CManager::instance().Login(ch);

#ifdef ENABLE_ANTI_MULTIPLE_FARM //@fix core cross-fire
	std::string sMAIf = d->GetLoginMacAdress();
	int8_t i8GetOldState = static_cast<int8_t>(CAntiMultipleFarm::instance().GetPlayerDropState(sMAIf, ch->GetPlayerID()));
	CAntiMultipleFarm::instance().Login(sMAIf, ch->GetPlayerID(), i8GetOldState);
#endif
