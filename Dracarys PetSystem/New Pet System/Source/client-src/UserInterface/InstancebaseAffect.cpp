# Search

	else if (IsNPC())
	{
		return NAMECOLOR_NPC;
	}

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	else if (IsPet() || IsNewPet())
	{
		return NAMECOLOR_NPC;
	}
#endif


# Search 

void CInstanceBase::__AttachEmpireEffect(DWORD eEmpire)


# Search in

	if (IsWarp())
		return;

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	else if (IsPet() || IsNewPet())
		return;
#endif

