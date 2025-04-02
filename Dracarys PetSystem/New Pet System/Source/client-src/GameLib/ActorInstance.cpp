# Search

bool CActorInstance::IsPet()

# Change

# If don't have add.

#ifdef ENABLE_NEW_PET_SYSTEM
bool CActorInstance::IsPet()
{
	if (TYPE_PET == m_eActorType)
		return true;
	return false;
}
bool CActorInstance::IsNewPet()
{
	if (TYPE_PET != m_eActorType)
		return false;

	switch (GetRace())
	{
		case 34041:
		case 34042:
		case 34045:
		case 34046:
		case 34049:
		case 34050:
		case 34053:
		case 34054:
		case 34036:
		case 34037:
		case 34064:
		case 34065:
		case 34073:
		case 34074:
		case 34075:
		case 34076:
		case 34080:
		case 34081:
		case 34082:
		case 34083:
		case 34047:
		case 34048:
			return true;
	}
	return false;
}
#endif

