//Include hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//In der Funktion: void CInputDB::PlayerLoad(LPDESC d, const char * data) hinzufügen
//unter: d->BindCharacter(ch);

#ifdef ENABLE_ANTI_MULTIPLE_FARM //@fix core cross-fire
	CAntiMultipleFarm::instance().Login(d->GetLoginMacAdress(), ch->GetPlayerID());
#endif

//In der selben Funktion unter: p.bChannel = g_bChannel; hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		strlcpy(p.cMAIf, d->GetLoginMacAdress(), sizeof(p.cMAIf));
		p.i8BlockState = static_cast<int8_t>(CAntiMultipleFarm::instance().GetPlayerDropState(d->GetLoginMacAdress(), ch->GetPlayerID()));
#endif
