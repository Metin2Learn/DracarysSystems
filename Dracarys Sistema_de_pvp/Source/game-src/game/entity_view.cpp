# Search

void CEntity::ViewInsert(LPENTITY entity, bool recursive)

# Search in

	if (!entity->m_bIsObserver)
		entity->EncodeInsertPacket(this);

# Change

#ifdef ENABLE_PVP_TOURNAMENT
	bool insertTARGET = !entity->m_bIsObserver;
	if (m_bPvPTournament == true && entity->m_bPvPTournament == false)
	{
		insertTARGET = false;
		//recursive = false;
	}

	if (insertTARGET)
		entity->EncodeInsertPacket(this);
#else
	if (!entity->m_bIsObserver)
		entity->EncodeInsertPacket(this);
#endif
