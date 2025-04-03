
#ifdef ENABLE_NEW_PET_SYSTEM
#include "PetSystem.h"
#endif


# Search

			pack.vnum = pItem->GetVnum();

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
			strlcpy(pack.name,pItem->GetNewName(),sizeof(pack.name));
#endif

# seARCH

	case ITEM_SPECIAL_DS:
		if (!item->IsEquipped())
			EquipItem(item);
		else
			UnequipItem(item);
		break;

# Add After

#ifdef ENABLE_NEW_PET_SYSTEM
	case ITEM_PET:
	{
		switch (item->GetSubType())
		{
		case PET_LEVELABLE:
		{
			time_t now = get_global_time();
			if (GetProtectTime("newpet.ride") > now)
			{
				ChatPacket(CHAT_TYPE_INFO, LC_TEXT("684"), GetProtectTime("newpet.ride") - now);
				return false;
			}
			SetProtectTime("newpet.ride", now + 1);

			if (time(0) > item->GetSocket(POINT_PET_DURATION))
			{
				TItemTable* p = ITEM_MANAGER::instance().GetTable(55001);
				if(p)
					ChatPacket(CHAT_TYPE_INFO, LC_TEXT("719"), p->szName);
				if (item->IsEquipped())
					UnequipItem(item);
				return false;
			}

			if (!item->IsEquipped())
				EquipItem(item);
			else
				UnequipItem(item);
		}
		break;

		case PET_PROTEIN:
		{
			LPITEM item2 = GetItem(DestCell);
			if (item2 != NULL)
			{
				if (!(item2->GetType() == ITEM_PET && item2->GetSubType() == PET_LEVELABLE))
					return false;
				long oldTime = item2->GetSocket(POINT_PET_DURATION) - time(0);
				if (oldTime < 0)
					oldTime = 0;
				if (oldTime >= ((60 * 60 * 24 * 14) * 6) - 100)
				{
					ChatPacket(CHAT_TYPE_INFO, LC_TEXT("732"));
					return false;
				}
				else
				{
					long newTime = MIN((oldTime + 60 * 60 * 24 * 7), (60 * 60 * 24 * 14) * 6);
					item2->SetSocket(POINT_PET_DURATION, time(0) + newTime);
					item->SetCount(item->GetCount() - 1);
					ChatPacket(CHAT_TYPE_INFO, LC_TEXT("720"), 7);
				}


			}
			else
			{
				CPetSystem* pet = GetPetSystem();
				if (pet)
				{
					LPPET petActor = pet->GetNewPet();
					if (petActor) {
						if (petActor->PointChange(POINT_PET_DURATION, 60 * 60 * 24 * 7))
						{
							ChatPacket(CHAT_TYPE_INFO, LC_TEXT("720"), 7);
							item->SetCount(item->GetCount() - 1);
						}
						else
						{
							ChatPacket(CHAT_TYPE_INFO, LC_TEXT("732"));
							return false;
						}
					}
					else
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("721"));
				}
			}
		}
		break;

		case PET_DEW:
		{
			LPITEM item2 = GetItem(DestCell);
			if (item2 != NULL)
			{
				if (!(item2->GetType() == ITEM_PET && item2->GetSubType() == PET_LEVELABLE))
					return false;

				BYTE bonusType = item->GetValue(0);
				BYTE bonusStep = item->GetValue(1);

				DWORD petLevel = item2->GetSocket(POINT_PET_LEVEL);
				long bonusLevel = item2->GetSocket(POINT_PET_BONUS_1 + bonusType);

				if (bonusStep == 1)
				{
					if (bonusLevel >= 0 && bonusLevel <= 4)
					{
						item2->SetSocket(POINT_PET_BONUS_1 + bonusType, bonusLevel + 1);
						//item2->UpdatePacket();
						item->SetCount(item->GetCount() - 1);
						return true;
					}
					else
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("722"));
						return false;
					}
				}
				else if (bonusStep == 2)
				{
					if (petLevel < 40)
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("718"), 40);
						return false;
					}

					if (bonusLevel >= 5 && bonusLevel <= 9)
					{
						item2->SetSocket(POINT_PET_BONUS_1 + bonusType, bonusLevel + 1);
						//item2->UpdatePacket();
						item->SetCount(item->GetCount() - 1);
						return true;
					}
					else
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("722"));
						return false;
					}

				}
				else if (bonusStep == 3)
				{
					if (petLevel < 75)
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("718"), 75);
						return false;
					}

					if (bonusLevel >= 10 && bonusLevel <= 14)
					{
						item2->SetSocket(POINT_PET_BONUS_1 + bonusType, bonusLevel + 1);
						//item2->UpdatePacket();
						item->SetCount(item->GetCount() - 1);
						return true;
					}
					else
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("722"));
						return false;
					}
				}
				else if (bonusStep == 4)
				{
					if (petLevel < 100)
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("718"), 100);
						return false;
					}

					if (bonusLevel >= 15 && bonusLevel <= 19)
					{
						item2->SetSocket(POINT_PET_BONUS_1 + bonusType, bonusLevel + 1);
						//item2->UpdatePacket();
						item->SetCount(item->GetCount() - 1);
						return true;
					}
					else
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("722"));
						return false;
					}
				}
			}
			else
			{
				CPetSystem* pet = GetPetSystem();
				if (pet)
				{
					LPPET petActor = pet->GetNewPet();
					if (petActor) {
						if (petActor->IncreaseBonus(item->GetValue(0), item->GetValue(1)))
							item->SetCount(item->GetCount() - 1);
					}
					else
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("721"));
				}
			}
		}
		break;

		case PET_SKILL:
		{
			LPITEM item2 = GetItem(DestCell);
			if (item2 != NULL)
			{
				if (!(item2->GetType() == ITEM_PET && item2->GetSubType() == PET_LEVELABLE))
					return false;

				BYTE skillIndex = item->GetValue(0);

				BYTE bySlotIndex = 99;
				for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
				{
					if (item2->GetAttributeType(j) == skillIndex) {
						bySlotIndex = j;
						break;
					}
				}
				if (bySlotIndex == 99)
				{
					BYTE emptyIndex = 99;
					for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
					{
						if (item2->GetAttributeType(j) == 0) {
							emptyIndex = j;
							break;
						}
					}
					if (emptyIndex == 99)
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("723"));
						return false;
					}

					item2->SetForceAttribute(emptyIndex, skillIndex, 0);
					TItemTable* p = ITEM_MANAGER::instance().GetTable(55009+skillIndex);
					if(p)
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("724"), p->szName);
					item->SetCount(item->GetCount() - 1);
					return true;
				}
				else
				{
					BYTE type = item2->GetAttributeType(bySlotIndex);
					long value = item2->GetAttributeValue(bySlotIndex);
					if (value > 19)
					{
						TItemTable* p = ITEM_MANAGER::instance().GetTable(55009+skillIndex);
						if(p)
							ChatPacket(CHAT_TYPE_INFO, LC_TEXT("725"), p->szName);
						return false;
					}
					item2->SetForceAttribute(bySlotIndex, type, value + 1);
					TItemTable* p = ITEM_MANAGER::instance().GetTable(55009+skillIndex);
					if(p)
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("726"), p->szName);
					item->SetCount(item->GetCount() - 1);
				}
			}
			else
			{
				CPetSystem* pet = GetPetSystem();
				if (pet)
				{
					LPPET petActor = pet->GetNewPet();
					if (petActor) {
						if (petActor->IncreaseSkill(item->GetValue(0)))
							item->SetCount(item->GetCount() - 1);
					}
					else
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("721"));
				}
			}
		}
		break;

		case PET_SKILL_DEL_BOOK:
		{
			WORD index = DestCell.cell;
			if (index >= 0 && index <= 15)
			{
				CPetSystem* pet = GetPetSystem();
				if (pet)
				{
					LPPET petActor = pet->GetNewPet();
					if (petActor) {
						LPITEM petItem = petActor->GetSummonItem();
						if (!petItem)
							return false;
						BYTE type = petItem->GetAttributeType(index);
						if (type >= 1 && type <= 25)
						{
							petActor->PointChange(POINT_PET_SKILL_INDEX_1 + index, 0);
							petActor->PointChange(POINT_PET_SKILL_LEVEL_1 + index, 0);
							TItemTable* p = ITEM_MANAGER::instance().GetTable(55009+type);
							if(p)
								ChatPacket(CHAT_TYPE_INFO, LC_TEXT("727"), p->szName);
							item->SetCount(item->GetCount() - 1);
						}
					}
					else
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("721"));
				}
			}
		}
		break;
		case PET_EXPFOOD_PER:
		{
			CPetSystem* pet = GetPetSystem();
			if (pet)
			{
				LPPET petActor = pet->GetNewPet();
				if (petActor) {
					DWORD petExp = petActor->GetNextExp();
					float realExp = (float(petActor->GetNextExp()) / 100.0) * 2.0;
					if (petActor->PointChange(POINT_PET_EXP, int(realExp)))
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("734"));
						item->SetCount(item->GetCount() - 1);
					}
					else
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("735"));
				}
				else
					ChatPacket(CHAT_TYPE_INFO, LC_TEXT("721"));
			}
		}
		break;
		case PET_SKILL_ALL_DEL_BOOK:
		{
			LPITEM item2 = GetItem(DestCell);
			if (item2 != NULL)
			{
				if (!(item2->GetType() == ITEM_PET && item2->GetSubType() == PET_LEVELABLE))
					return false;
				bool isHaveSkill = false;
				for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
				{
					BYTE type = item2->GetAttributeType(j);
					if (type != 0 && type != 99)
					{
						isHaveSkill = true;
						break;
					}
				}
				if (!isHaveSkill)
				{
					ChatPacket(CHAT_TYPE_INFO, LC_TEXT("728"));
					return false;
				}
				else
				{
					for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
					{
						BYTE type = item2->GetAttributeType(j);
						if (type != 0 && type != 99)
							item2->SetForceAttribute(j, 0, 0);
					}
					ChatPacket(CHAT_TYPE_INFO, LC_TEXT("729"));
					item->SetCount(item->GetCount() - 1);
				}
			}
			else
			{
				CPetSystem* pet = GetPetSystem();
				if (pet)
				{
					LPPET petActor = pet->GetNewPet();
					if (petActor)
					{
						LPITEM petItem = petActor->GetSummonItem();
						if (!petItem)
							return false;
						bool isHaveSkill = false;
						for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
						{
							BYTE type = petItem->GetAttributeType(j);
							if (type != 0 && type != 99)
							{
								isHaveSkill = true;
								break;
							}
						}
						if (!isHaveSkill)
						{
							ChatPacket(CHAT_TYPE_INFO, LC_TEXT("728"));
							return false;
						}
						else
						{
							for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
							{
								BYTE type = petItem->GetAttributeType(j);
								if (type != 0 && type != 99)
									petItem->SetForceAttribute(j, 0, 0);
							}
							ChatPacket(CHAT_TYPE_COMMAND, "UpdatePet %d", POINT_PET_SKILL_INDEX_1);
							ChatPacket(CHAT_TYPE_INFO, LC_TEXT("729"));
							item->SetCount(item->GetCount() - 1);
						}
					}
					else
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("721"));
				}
			}
		}
		break;
		}
	}
	break;
#endif

