//Include hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"
#endif

//In der Funktion: int CInputMain::Analyze(LPDESC d, BYTE bHeader, const char * c_pData)
// ganz unten über hinzufügen:
//			break;
//	}
//	return (iExtraLen);
//}

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		case HEADER_CG_ANTI_FARM:
			if ((iExtraLen = RecvAntiFarmUpdateStatus(ch, c_pData, m_iBufferLeft)) < 0)
				return -1;
			break;
#endif

//Am Ende der Datei hinzufügen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
auto CInputMain::RecvAntiFarmUpdateStatus(LPCHARACTER ch, const char* data, size_t uiBytes) -> int
{
	const TSendAntiFarmInfo* p = reinterpret_cast<const TSendAntiFarmInfo*>(data);

	if (uiBytes < sizeof(TSendAntiFarmInfo))
		return -1;

	LPDESC d = nullptr;
	if (!ch || !(d = ch->GetDesc()))
		return -1;

	const char* c_pData = data + sizeof(TSendAntiFarmInfo);
	uiBytes -= sizeof(TSendAntiFarmInfo);

	switch (p->subheader)
	{
	case AF_SH_SEND_STATUS_UPDATE:
	{
		size_t extraLen = (sizeof(DWORD) * MULTIPLE_FARM_MAX_ACCOUNT);
		if (uiBytes < extraLen)
			return -1;

		std::vector<DWORD> v_dwPIDS;
		for (uint8_t i = 0; i < MULTIPLE_FARM_MAX_ACCOUNT; ++i)
			v_dwPIDS.emplace_back(*reinterpret_cast<const DWORD*>(c_pData + (sizeof(DWORD) * i)));

		std::string sMAIf = d->GetLoginMacAdress();
		CAntiMultipleFarm::instance().SendBlockDropStatusChange(sMAIf, v_dwPIDS);

		{ //send p2p update
			CAntiMultipleFarm::TP2PChangeDropStatus dataPacket(HEADER_GG_ANTI_FARM);
			strlcpy(dataPacket.cMAIf, sMAIf.c_str(), sizeof(dataPacket.cMAIf));
			for (uint8_t i = 0; i < v_dwPIDS.size(); ++i)
				dataPacket.dwPIDs[i] = v_dwPIDS[i];
			P2P_MANAGER::instance().Send(&dataPacket, sizeof(CAntiMultipleFarm::TP2PChangeDropStatus));
		}

		return extraLen;
	}
	}

	return 0;
}
#endif
