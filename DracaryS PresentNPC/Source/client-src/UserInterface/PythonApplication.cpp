# Search

	if (!rkNetStream.LoadInsultList(szInsultList))
	{
		Tracenf("CPythonApplication - CPythonNetworkStream::LoadInsultList(%s)", szInsultList);
	}

# Add after

#ifdef ENABLE_NPC_WEAR_ITEM
	if (!rkNPCMgr.LoadNPCWear("locale/common/npc_wear.txt"))
		Tracenf("CPythonApplication - CPythonNonPlayer::LoadNPCWear()");
#endif
