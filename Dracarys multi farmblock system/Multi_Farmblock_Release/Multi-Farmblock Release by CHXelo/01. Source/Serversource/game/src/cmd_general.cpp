//Include hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//Unter den Includes hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
ACMD(do_debug_anti_multiple_farm)
{
	LPDESC d = nullptr;
	if (!ch || (ch && !(d = ch->GetDesc())))
		return;

	CAntiMultipleFarm::instance().PrintPlayerDropState(d->GetLoginMacAdress(), ch);
}
#endif
