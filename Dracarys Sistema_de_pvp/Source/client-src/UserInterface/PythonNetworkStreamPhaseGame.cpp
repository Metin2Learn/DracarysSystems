# Search

	bool bSelf = (pInstTarget == CPythonCharacterManager::Instance().GetMainInstancePtr());

# change

#ifdef ENABLE_PVP_CAMERA_MODE
	bool bSelf = (pInstTarget == (CPythonPlayer::Instance().GetCameraMode()?CPythonPlayer::Instance().NEW_GetMainActorPtr(): CPythonCharacterManager::Instance().GetMainInstancePtr()));
#else
	bool bSelf = (pInstTarget == CPythonCharacterManager::Instance().GetMainInstancePtr());
#endif

# Search

		case HEADER_GC_REFINE_CLOSE:
			ret = RecvRefineClose();
			break;

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
		case HEADER_GC_PVP_DUEL:
			ret = RecvPvPDuel();
			break;
#endif

# Add

#ifdef ENABLE_PVP_TOURNAMENT
bool CPythonNetworkStream::RecvPvPDuel()
{
	TPacketGCPvPInfo pvpInfo;
	if (!Recv(sizeof(pvpInfo), &pvpInfo))
		return false;

	BYTE subHeader;
	if (!Recv(sizeof(BYTE), &subHeader))
		return false;

	switch (subHeader)
	{
		case PVP_DATA_UPDATE_HP:
		{
			BYTE arenaIndex;
			if (!Recv(sizeof(BYTE), &arenaIndex))
				return false;
			arenaIndex -= 1;
			for (BYTE j = 0; j < 2; ++j)
			{
				BYTE hpPercent;
				if (!Recv(sizeof(BYTE), &hpPercent))
					return false;
				int playerMinHP;
				if (!Recv(sizeof(int), &playerMinHP))
					return false;
				int playerMaxHP;
				if (!Recv(sizeof(int), &playerMaxHP))
					return false;
				bool playerIsPoisoned;
				if (!Recv(sizeof(bool), &playerIsPoisoned))
					return false;
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentHP", Py_BuildValue("(iiiiii)", arenaIndex, j, hpPercent, playerMinHP, playerMaxHP, playerIsPoisoned));
			}
		}
		break;

		case PVP_DATA_START_TIME:
		{
			BYTE arenaIndex;
			if (!Recv(sizeof(BYTE), &arenaIndex))
				return false;
			int startTime;
			if (!Recv(sizeof(int), &startTime))
				return false;
			arenaIndex -= 1;
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentStartTime", Py_BuildValue("(ii)", arenaIndex, startTime));
		}
		break;

		case PVP_DATA_UPDATE_SCORE:
		{
			BYTE arenaIndex;
			if (!Recv(sizeof(BYTE), &arenaIndex))
				return false;
			BYTE player0Score;
			if (!Recv(sizeof(BYTE), &player0Score))
				return false;
			BYTE player1Score;
			if (!Recv(sizeof(BYTE), &player1Score))
				return false;
			arenaIndex -= 1;

			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentScore", Py_BuildValue("(iii)", arenaIndex, 0, player0Score));
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentScore", Py_BuildValue("(iii)", arenaIndex, 1, player1Score));
		}
		break;

		case PVP_DATA_DELETE:
		{
			BYTE arenaIndex;
			if (!Recv(sizeof(BYTE), &arenaIndex))
				return false;
			if (arenaIndex == 0)
			{
				for (BYTE j = 0; j < 8; ++j)
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentClear", Py_BuildValue("(i)", j));
			}
			else
			{
				arenaIndex -= 1;
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentClear", Py_BuildValue("(i)", arenaIndex));
			}
			
		}
		break;
		case PVP_DATA_CLEAR_TARGET:
		{
			CPythonPlayer::Instance().ClearTargetProcess();
			CPythonApplication::Instance().SetDefaultCamera();
		}
		break;
		case PVP_DATA_UPDATE:
		{
			BYTE dataSize;
			if (!Recv(sizeof(BYTE), &dataSize))
				return false;

			if (dataSize == 0 || dataSize > 1)
				for(BYTE j=0;j<8;++j)
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentClear", Py_BuildValue("(i)",j));

			for (BYTE j = 0; j < dataSize; ++j)
			{

				BYTE arenaIndex;
				if (!Recv(sizeof(BYTE), &arenaIndex))
					return false;

				arenaIndex -= 1;

				int startTime;
				if (!Recv(sizeof(int), &startTime))
					return false;

				TPvPDuelData player0;
				if (!Recv(sizeof(TPvPDuelData), &player0))
					return false;

				TPvPDuelData player1;
				if (!Recv(sizeof(TPvPDuelData), &player1))
					return false;

				if (player0.id == 0 || player1.id == 0)
				{
					PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentClear", Py_BuildValue("(i)", arenaIndex));
					continue;
				}

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentStartTime", Py_BuildValue("(ii)", arenaIndex, startTime));

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentRace", Py_BuildValue("(iii)", arenaIndex, 0, player0.race));
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentRace", Py_BuildValue("(iii)", arenaIndex, 1, player1.race));

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentScore", Py_BuildValue("(iii)", arenaIndex, 0, player0.score));
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentScore", Py_BuildValue("(iii)", arenaIndex, 1, player1.score));

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentName", Py_BuildValue("(iis)", arenaIndex, 0, player0.name));
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentName", Py_BuildValue("(iis)", arenaIndex, 1, player1.name));

				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentHP", Py_BuildValue("(iiiiii)", arenaIndex, 0, player0.percent, player0.minHP, player0.maxHP,player0.isPoisoned));
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "SetPvPTournamentHP", Py_BuildValue("(iiiiii)", arenaIndex, 1, player1.percent, player1.minHP, player1.maxHP, player1.isPoisoned));

			}
		}
		break;

	}
	return true;
}
#endif
