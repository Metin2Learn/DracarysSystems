//Include hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//Am Ende der Funktion: void CHARACTER::Initialize() hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	bAFisWarping = false;
#endif

//Am Ende der Funktion: void CHARACTER::Destroy() hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	bAFisWarping = false;
#endif

//In der Funktion: void CHARACTER::Disconnect(const char * c_pszReason)
//unter: marriage::CManager::instance().Logout(this); hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	LPDESC d = nullptr;
	bool is_warping = IsSetWarp();
	if ((d = GetDesc())) { CAntiMultipleFarm::instance().Logout(d->GetLoginMacAdress(), GetPlayerID(), is_warping); }
#endif

//In der selben Funktion im P2P Packet unter: strlcpy(p.szName, GetName(), sizeof(p.szName)); hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	p.bAFisWarping = is_warping;
#endif

//In der Funktion: bool CHARACTER::WarpSet(long x, long y, long lPrivateMapIndex)
//�ber dem Call: GetDesc()->Packet(&p, sizeof(TPacketGCWarp)); hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	UpdateCharacterWarpCheck(true);
#endif

//Wenn Ihr die Funktion habt: void CHARACTER::WarpEnd()
//unter dem Aufruf: m_posWarp.x = m_posWarp.y = m_posWarp.z = 0; hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	LPDESC d = GetDesc();
	std::string sMAIf = (d ? d->GetLoginMacAdress() : "");
	UpdateCharacterWarpCheck(false);
#endif

//In der selben Funktion im P2P Packet unter: p.bChannel = g_bChannel; hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		strlcpy(p.cMAIf, sMAIf.c_str(), sizeof(p.cMAIf));
		p.i8BlockState = static_cast<int8_t>(CAntiMultipleFarm::instance().GetPlayerDropState(d->GetLoginMacAdress(), GetPlayerID()));
#endif

//Wenn Ihr einen Channel-Changer habt, f�gt folgendes hinzu - meine Funktion hei�t: bool CHARACTER::SwitchChannel(long newAddr, WORD newPort)
//unter dem Aufruf: p.wPort = wPort; hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	UpdateCharacterWarpCheck(true);
#endif

//Am Ende der Datei hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
auto CHARACTER::HasBlockedDrops() -> bool
{
	LPDESC d = nullptr;
	if (!(d = GetDesc()))
		return false;

	std::string sMAIf = d->GetLoginMacAdress();
	return CAntiMultipleFarm::instance().GetPlayerDropState(sMAIf, GetPlayerID());
}
#endif
