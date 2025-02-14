# Add

#ifdef ENABLE_PVP_TOURNAMENT
void CPythonPlayer::ClearTargetProcess()
{
	__ClearReservedAction();
	__ClearAutoAttackTargetActorID();
	auto mainPlayer = NEW_GetMainActorPtr();
	if(mainPlayer)
		mainPlayer->NEW_Stop();
}
#endif

