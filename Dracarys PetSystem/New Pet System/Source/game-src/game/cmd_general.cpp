
# Add

#ifdef ENABLE_NEW_PET_SYSTEM
#include "PetSystem.h"
ACMD(do_change_name)
{
	std::vector<std::string> vecArgs;
	split_argument(argument, vecArgs);
	if (vecArgs.size() < 3) { return; }
	int scrollPos = -1;
	int petPos = -1;
	str_to_number(scrollPos, vecArgs[1].c_str());
	str_to_number(petPos, vecArgs[2].c_str());
	if (scrollPos == -1 || petPos == -1 || vecArgs[3].empty() || vecArgs[3].size() < 3 || ch->GetGold() < 100000)
		return;
	LPITEM scroll = ch->GetInventoryItem(scrollPos);
	if (scroll)
	{
		//if ()
		{
			LPITEM pet = ch->GetInventoryItem(petPos);
			if (pet)
			{
				if (pet->IsEquipped())
					return;
				if (pet->GetType() == ITEM_PET && pet->GetSubType() == PET_LEVELABLE && scroll->GetVnum() == 55008)
				{
					ch->SetPoint(POINT_GOLD, -100000);
					scroll->SetCount(scroll->GetCount() - 1);
					//str_replace(vecArgs[3], ";", " ");
					if (!check_name(vecArgs[3].c_str()))
						return;
					pet->SetNewName(vecArgs[3].c_str());
					pet->UpdatePacket();
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("688"));
				}
			}
		}
	}
}
ACMD(do_pet_egg)
{
	if (ch->GetGold() < 100000)
		return;

	std::vector<std::string> vecArgs;
	split_argument(argument, vecArgs);
	if (vecArgs.size() < 2) { return; }
	int petPos = -1;
	str_to_number(petPos, vecArgs[1].c_str());

	LPITEM item = ch->GetInventoryItem(petPos);
	if (!item)
		return;
	else if (!(item->GetType() == ITEM_PET && item->GetSubType() == PET_EGG))
		return;
	else if (!check_name(vecArgs[2].c_str()))
		return;

	LPITEM petItem = ch->AutoGiveItem(item->GetValue(0));
	if (!petItem)
		return;

	item->SetCount(item->GetCount()-1);
	petItem->SetNewName(vecArgs[2].c_str());
	petItem->SetSocket(0,time(0)+60*60*24*7);
	petItem->SetSocket(1, 1);
	for (BYTE j = 0; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
		petItem->SetForceAttribute(j, 99, 0);
	petItem->Save();
	petItem->UpdatePacket();
}
ACMD(do_pet_evolve)
{
	LPITEM item = ch->GetWear(WEAR_PET);
	if(!item)
		return;
	long level = item->GetSocket(1);
	if (level != 40 && level != 75 && level != 100)
		return;
	CPetSystem* pet = ch->GetPetSystem();
	if (!pet)
		return;
	LPPET petActor = pet->GetNewPet();
	if (!petActor)
		return;
	petActor->IncreaseEvolve();
}
ACMD(do_pet_add_slot)
{
	std::vector<std::string> vecArgs;
	split_argument(argument, vecArgs);
	if (vecArgs.size() < 2) { return; }
	int skillSlot = -1;
	str_to_number(skillSlot, vecArgs[1].c_str());
	if (skillSlot >= 0 && skillSlot <= 14)
	{
		CPetSystem* pet = ch->GetPetSystem();
		if (!pet)
			return;
		LPPET petActor = pet->GetNewPet();
		if (!petActor)
			return;
		LPITEM item = petActor->GetSummonItem();
		if (!item)
			return;
		if (item->GetSocket(1) < 115)
			return;

		int nextIndex = -1;
		for (int j = 3; j < ITEM_ATTRIBUTE_MAX_NUM; ++j)
		{
			if (item->GetAttributeType(j) == 99) {
				nextIndex = j;
				break;
			}
		}

		if (nextIndex < 0)
			return;

		DWORD slotItems[][2] = {
			{55036,1},
			{55004,5},
			{55005,5},
			{55006,5},
		};
		for (BYTE j=0;j<_countof(slotItems);++j)
		{
			if (ch->CountSpecifyItem(slotItems[j][0]) < slotItems[j][1])
			{
				TItemTable* p = ITEM_MANAGER::instance().GetTable(slotItems[j][0]);
				if(p)
					ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("730"), p->szName, slotItems[j][1]);
				return;
			}
		}
		for (BYTE j = 0; j < _countof(slotItems); ++j)
			ch->RemoveSpecifyItem(slotItems[j][0],slotItems[j][1]);
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("733"));
		petActor->PointChange(POINT_PET_SKILL_INDEX_1 + nextIndex, 0);
	}
}
#endif

