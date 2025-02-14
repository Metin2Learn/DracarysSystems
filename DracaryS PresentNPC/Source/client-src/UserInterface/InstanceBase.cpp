# Search

	if (!SetRace(c_rkCreateData.m_dwRace))
		return false;

# Change

#ifdef ENABLE_NPC_WEAR_ITEM
	const auto npcRaceIndex = CPythonNonPlayer::Instance().GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_RACE);
	if (npcRaceIndex != -1)
	{
		if (!SetRace(npcRaceIndex))
			return false;
	}
	else
	{
		if (!SetRace(c_rkCreateData.m_dwRace))
			return false;
	}
#else
	if (!SetRace(c_rkCreateData.m_dwRace))
		return false;
#endif

# Search

	if (0 != c_rkCreateData.m_dwMountVnum)
		MountHorse(c_rkCreateData.m_dwMountVnum);

	SetArmor(c_rkCreateData.m_dwArmor);

# Change

#ifdef ENABLE_NPC_WEAR_ITEM
	if (npcRaceIndex != -1)
	{
		CPythonNonPlayer& nonPlayer = CPythonNonPlayer::Instance();

		const auto mount = nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_MOUNT);
		if (mount != 0)
			MountHorse(mount);
		SetArmor(nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_ARMOR));
		SetWeapon(nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_WEAPON));
		SetHair(nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_HAIR));
		SetAcce(nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_ACCE));
		for (int i = 0; i < CHR_SHINING_NUM; i++)
			SetShining(i, nonPlayer.GetNPCWear(c_rkCreateData.m_dwRace, NPC_WEAR_SHINING_WEAPON + i));
	}
	else
	{
		if (0 != c_rkCreateData.m_dwMountVnum)
			MountHorse(c_rkCreateData.m_dwMountVnum);
		SetArmor(c_rkCreateData.m_dwArmor);
	}
#else
	if (0 != c_rkCreateData.m_dwMountVnum)
		MountHorse(c_rkCreateData.m_dwMountVnum);

	SetArmor(c_rkCreateData.m_dwArmor);
#endif

# Search

void CInstanceBase::SetHair(DWORD eHair)

# Search in

	if (IsPC() == false)

# Change

#ifdef ENABLE_NPC_WEAR_ITEM
	if (IsPC() == false && GetRace() > 7)
#else
	if (IsPC() == false)
#endif



# Search

bool CInstanceBase::SetAcce(DWORD eAcce)

# Search in

	if (!IsPC() || IsPoly() || IsWearingDress() || __IsShapeAnimalWear())

# Change

#ifdef ENABLE_NPC_WEAR_ITEM
	if ((IsPC()&&GetRace()>7) || IsPoly() || IsWearingDress() || __IsShapeAnimalWear())
#else
	if (!IsPC() || IsPoly() || IsWearingDress() || __IsShapeAnimalWear())
#endif

