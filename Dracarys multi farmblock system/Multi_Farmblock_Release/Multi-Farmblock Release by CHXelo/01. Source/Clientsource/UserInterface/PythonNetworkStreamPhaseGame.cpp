//Hinzufügen unter:
//case HEADER_GC_DIG_MOTION:
//	ret = RecvDigMotionPacket();
//	break;

#ifdef ENABLE_ANTI_MULTIPLE_FARM
			case HEADER_GC_ANTI_FARM:
				ret = RecvAntiFarmInformation();
				break;
#endif

//Am Ende der Datei hinzufügen:

#ifdef ENABLE_ANTI_MULTIPLE_FARM
#include "HAntiMultipleFarm.h"

bool CPythonNetworkStream::RecvAntiFarmInformation()
{
	TSendAntiFarmInfo bufPacket;
	if (!Recv(sizeof(bufPacket), &bufPacket))
		return false;

	int packet_size = int(bufPacket.size) - sizeof(bufPacket);

	if (bufPacket.subheader == AF_SH_SENDING_DATA)
	{
		bool canClean;
		if (!Recv(sizeof(canClean), &canClean))
			return false;

		if (canClean) CAntiMultipleFarm::instance().ClearAntiFarmData();
		packet_size -= sizeof(canClean);

		size_t table_size = sizeof(TAntiFarmPlayerInfo);
		while (packet_size >= table_size)
		{
			TAntiFarmPlayerInfo table;
			if (!Recv(table_size, &table))
				return false;

			CAntiMultipleFarm::instance().AddNewPlayerData(table);
			packet_size -= table_size;
		}

		/*send refresh advise for main character*/
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_RecvAntiFarmReload", Py_BuildValue("()"));
	}

	return true;
}

bool CPythonNetworkStream::SendAntiFarmStatus(std::vector<DWORD> dwPIDs)
{
	TSendAntiFarmInfo pack;
	pack.header = HEADER_CG_ANTI_FARM;
	pack.subheader = AF_SH_SEND_STATUS_UPDATE;
	pack.size = sizeof(TSendAntiFarmInfo) + (sizeof(DWORD) * MULTIPLE_FARM_MAX_ACCOUNT);

	if (!Send(sizeof(pack), &pack))
		return false;

	for (uint8_t i = 0; i < MULTIPLE_FARM_MAX_ACCOUNT; ++i)
		if (!Send(sizeof(dwPIDs[i]), &dwPIDs[i]))
			return false;

	return SendSequence();
}
#endif
