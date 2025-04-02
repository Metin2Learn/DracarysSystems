
# Search

	LPCHARACTER rider = GetRider();

# change

#ifdef ENABLE_NEW_PET_SYSTEM
				LPCHARACTER rider = GetRider()?GetRider():GetOwner();
#else
				LPCHARACTER rider = GetRider();
#endif


# ADd

#ifdef ENABLE_NEW_PET_SYSTEM
void CHARACTER::StatePet()
{
	float	START_FOLLOW_DISTANCE = 200.0f;
	float	START_RUN_DISTANCE = 300.0f;
	float	RESPAWN_DISTANCE = 3000.0f;
	int		APPROACH = 200;

	bool bDoMoveAlone = true;
	bool bRun = true;

	m_dwStateDuration = 0;
	LPCHARACTER victim = GetOwner();

	if (!victim)
	{
		//M2_DESTROY_CHARACTER(this);
		return;
	}

	m_pkMobInst->m_posLastAttacked = GetXYZ();

	float fDist = DISTANCE_APPROX(GetX() - victim->GetX(), GetY() - victim->GetY());

	if (fDist >= RESPAWN_DISTANCE)
	{
		float fOwnerRot = victim->GetRotation() * 3.141592f / 180.f;
		float fx = -APPROACH * cos(fOwnerRot);
		float fy = -APPROACH * sin(fOwnerRot);
		Show(victim->GetMapIndex(), victim->GetX() + fx, victim->GetY() + fy);
	}
	else if (fDist >= START_FOLLOW_DISTANCE)
	{
		if (fDist > START_RUN_DISTANCE)
			SetNowWalking(!bRun);

		Follow(victim, APPROACH);
	}
	else if (bDoMoveAlone && (get_dword_time() > m_dwLastAttackTime))
	{
		m_dwLastAttackTime = get_dword_time() + number(5000, 12000);
		SetRotation(number(0, 359));
		float fx, fy;
		float fDist = number(200, 400);
		GetDeltaByDegree(GetRotation(), fDist, &fx, &fy);

		if (!(SECTREE_MANAGER::instance().IsMovablePosition(GetMapIndex(), GetX() + (int)fx, GetY() + (int)fy)
			&& SECTREE_MANAGER::instance().IsMovablePosition(GetMapIndex(), GetX() + (int)fx / 2, GetY() + (int)fy / 2)))
			return;

		SetNowWalking(true);

		if (Goto(GetX() + (int)fx, GetY() + (int)fy))
			SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	}
}
#endif
