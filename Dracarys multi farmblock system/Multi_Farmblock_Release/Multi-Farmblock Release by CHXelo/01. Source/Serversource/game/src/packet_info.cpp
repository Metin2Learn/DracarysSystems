//Include hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//In der Funktion: CPacketInfoCG::CPacketInfoCG() unten hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	Set(HEADER_CG_ANTI_FARM, sizeof(TSendAntiFarmInfo), "RecvAntiFarmUpdateStatus", true);
#endif

//In der Funktion: CPacketInfoGG::CPacketInfoGG() unten hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	Set(HEADER_GG_ANTI_FARM, sizeof(CAntiMultipleFarm::TP2PChangeDropStatus), "RecvAntiFarmUpdateStatus", true);
#endif
