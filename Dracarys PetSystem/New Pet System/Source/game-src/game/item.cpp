# Search x2 times.

	memset(&m_aAttr, 0, sizeof(m_aAttr));

# Add x2 times.

#ifdef ENABLE_NEW_NAME_ITEM
	strlcpy(nameex,"^",sizeof(nameex));
#endif

# Search

	pack.count = m_dwCount;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	strlcpy(pack.name,nameex,sizeof(pack.name));
#endif


# Search
	
	ITEM_MANAGER::instance().RemoveItem(item, "REAL_TIME_EXPIRE");

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
		if (item->IsCostumeMountItem() && item->IsEquipped())
		{
			LPCHARACTER owner = item->GetOwner();
			if (owner)
			{
				owner->StopRiding();
				owner->HorseSummon(false);
			}
		}
#endif

# Add

#ifdef ENABLE_NEW_NAME_ITEM
void CItem::SetNewName(const char* name)
{
	strlcpy(nameex,name,sizeof(nameex));
}
#endif


/////
# Search in __IsWearableWithoutWearFlags

	case ITEM_BELT:


# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	case ITEM_PET:
#endif


# if don't have this. __IsWearableWithoutWearFlags

# Search 

	GetType() != ITEM_BELT

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	&& !IsNewPetItem()
#endif

///



# Search in IsEquipable

	case ITEM_BELT:


# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	case ITEM_PET:
#endif

# Search

	else if (GetType() == ITEM_BELT)
		return WEAR_BELT;

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	else if (IsNewPetItem())
		return WEAR_PET;
#endif

# Search

	int accessoryGrade;

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
	if (GetType() == ITEM_PET && GetSubType() == PET_LEVELABLE)
	{
		int bonusTypes[][2] = { {APPLY_MAX_HP,4000},{APPLY_ATTBONUS_MONSTER,20},{APPLY_CRITICAL_PCT,10} };
		for (BYTE i = 0; i < 3; ++i)
		{
			long bonusLevel = GetSocket(POINT_PET_BONUS_1+i);
			if (bonusLevel == 0)
				continue;
			int value = bonusLevel == 20 ? bonusTypes[i][1]:bonusLevel*(float(bonusTypes[i][1])/20.0);
			m_pOwner->ApplyPoint(bonusTypes[i][0], bAdd ? value : -value);
		}

		for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
		{
			BYTE skillType = GetAttributeType(j);
			if (skillType == 0 || skillType == 99)
				continue;
			auto it = petSkillBonus.find(skillType);
			if (it != petSkillBonus.end())
			{
				BYTE skillLevel = GetAttributeValue(j);
				for (BYTE i = 0; i < it->second.size(); ++i)
				{
					auto bonus = it->second[i];
					int value = skillLevel == 20 ? bonus.second : skillLevel * (float(bonus.second) / 20.0);
					m_pOwner->ApplyPoint(bonus.first, bAdd ? value : -value);
				}
			}
		}
		return;
	}
#endif

# Search

ch->BuffOnAttr_AddBuffsFromItem(this);

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
	if (GetOwner())
	{
		if (IsCostumePetItem())
		{
			CPetSystem* petSystem = GetOwner()->GetPetSystem();
			if (petSystem)
				petSystem->HandlePetCostumeItem();
		}
		if (IsNewPetItem())
		{
			CPetSystem* petSystem = GetOwner()->GetPetSystem();
			if (petSystem)
				petSystem->HandleNewPetItem();
		}
	}
#endif

# Search

	if (IsDragonSoul())
	{
		DSManager::instance().DeactivateDragonSoul(this);
	}
	else
	{
		ModifyPoints(false);
	}

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
	if (GetOwner())
	{
		if (IsCostumePetItem() || IsNewPetItem())
		{
			CPetSystem* petSystem = GetOwner()->GetPetSystem();
			if (petSystem)
				petSystem->DeletePet(GetID());
		}
	}
#endif

# Add


#ifdef ENABLE_NEW_PET_SYSTEM
bool CItem::IsCostumePetItem()
{
	return GetType() == ITEM_COSTUME && GetSubType() == COSTUME_PET;
}
bool CItem::IsNewPetItem()
{
	return GetType() == ITEM_PET && GetSubType() == PET_LEVELABLE;
}
#endif