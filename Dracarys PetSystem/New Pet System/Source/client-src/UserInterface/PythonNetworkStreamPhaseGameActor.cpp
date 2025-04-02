# Search

	if (kNetActorData.m_bType != CActorInstance::TYPE_PC)

# Change

	if (kNetActorData.m_bType != CActorInstance::TYPE_PC
#ifdef ENABLE_NEW_PET_SYSTEM
	&& kNetActorData.m_bType != CActorInstance::TYPE_PET
#endif
	)

