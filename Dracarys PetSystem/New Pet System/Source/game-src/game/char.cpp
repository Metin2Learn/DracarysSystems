# Search x2 times.

			item->SetAttributes(pItems->aAttr);

# Add after x2 times.

#ifdef ENABLE_NEW_NAME_ITEM
			item->SetNewName(pItems->name);
#endif


# Search

	GetMobBattleType() != BATTLE_TYPE_MAGIC 

# Add after

		#ifdef ENABLE_NEW_PET_SYSTEM
		&& IsPet()
		#endif



# search

	m_fAttMul = 1.0f;

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
	m_PetOwner = NULL;
	m_bIsNewPet = false;
#endif

# Search

	pack.dwLevel

# Change like this.

	pack.dwLevel = (IsMonster() || IsStone()
#ifdef ENABLE_NEW_PET_SYSTEM
		|| IsNewPet()
#endif
		) ? GetLevel() : 0;


# Search

	if (IsPC() == true || m_bCharType == CHAR_TYPE_NPC)

# Change

#ifdef ENABLE_NEW_PET_SYSTEM
	if (IsPC() == true || m_bCharType == CHAR_TYPE_NPC || m_bCharType == CHAR_TYPE_PET)
#else
	if (IsPC() == true || m_bCharType == CHAR_TYPE_NPC)
#endif


# Search

	else if (warmap::IsWarFlagBase(GetRaceNum()))
	{
		m_stateIdle.Set(this, &CHARACTER::BeginStateEmpty, &CHARACTER::StateFlagBase, &CHARACTER::EndStateEmpty);
		m_stateMove.Set(this, &CHARACTER::BeginStateEmpty, &CHARACTER::StateFlagBase, &CHARACTER::EndStateEmpty);
		m_stateBattle.Set(this, &CHARACTER::BeginStateEmpty, &CHARACTER::StateFlagBase, &CHARACTER::EndStateEmpty);
	}

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	else if (m_bCharType == CHAR_TYPE_PET)
	{
		m_stateIdle.Set(this, &CHARACTER::BeginStateEmpty, &CHARACTER::StatePet, &CHARACTER::EndStateEmpty);
		m_stateMove.Set(this, &CHARACTER::BeginStateEmpty, &CHARACTER::StateMove, &CHARACTER::EndStateEmpty);
		m_stateBattle.Set(this, &CHARACTER::BeginStateEmpty, &CHARACTER::StatePet, &CHARACTER::EndStateEmpty);
	}
#endif


# Add

#ifdef ENABLE_NEW_PET_SYSTEM
bool CHARACTER::PetBlockMap()
{
	if (IsObserverMode())
		return true;
	switch (GetMapIndex())
	{
		case 999:
			return true;
	}
	return false;
}
void CHARACTER::SetProtectTime(const std::string& flagname, int value)
{
	itertype(m_protection_Time) it = m_protection_Time.find(flagname);
	if (it != m_protection_Time.end())
		it->second = value;
	else
		m_protection_Time.insert(make_pair(flagname, value));
}
int CHARACTER::GetProtectTime(const std::string& flagname) const
{
	itertype(m_protection_Time) it = m_protection_Time.find(flagname);
	if (it != m_protection_Time.end())
		return it->second;
	return 0;
}
#endif