# Search

		if (!IS_SET(item->GetFlag(), ITEM_FLAG_QUEST_USE | ITEM_FLAG_QUEST_USE_MULTIPLE))

# Add before

#ifdef RENEWAL_PICKUP_AFFECT
		if (item->GetVnum() == 70002)
		{
			CAffect* affect = FindAffect(AFFECT_PICKUP_ENABLE);
			if (!affect)
			{
				affect = FindAffect(AFFECT_PICKUP_DEACTIVE);
				if (affect)
				{
					ChatPacket(CHAT_TYPE_INFO, "You has already pickup affect.");
					return false;
				}
			}
			else
			{
				ChatPacket(CHAT_TYPE_INFO, "You has already pickup affect.");
				return false;
			}
			AddAffect(AFFECT_PICKUP_ENABLE, POINT_NONE, 0, AFF_NONE, 60 * 60 * 7, 0, 0, false);
			ChatPacket(CHAT_TYPE_INFO, "Succesfully added affect");
			return true;
		}
#endif



# Add

#ifdef RENEWAL_PICKUP_AFFECT
void CHARACTER::AutoGiveItemNew(LPITEM item, bool printMsg)
{
	if (!item)
		return;

	const DWORD itemVnum = item->GetVnum();
	const WORD realCount = item->GetCount();

	WORD wCount = item->GetCount();

	if (item->IsStackable() && item->GetType() != ITEM_BLEND)
	{
		for (WORD i = 0; i < INVENTORY_AND_EQUIP_SLOT_MAX; ++i)
		{
			LPITEM invItem = GetInventoryItem(i);
			if (!invItem)
				continue;

			if (invItem->GetVnum() == itemVnum)
			{
				BYTE j;
				for (j = 0; j < ITEM_SOCKET_MAX_NUM; ++j)
					if (invItem->GetSocket(j) != item->GetSocket(j))
						break;
				if (j != ITEM_SOCKET_MAX_NUM)
					continue;
				const WORD bCount2 = MIN(ITEM_MAX_COUNT - invItem->GetCount(), wCount);
				if (bCount2 > 0)
				{
					wCount -= bCount2;
					invItem->SetCount(invItem->GetCount() + bCount2);
					if (wCount == 0)
					{
						if (printMsg)
						{
							if (realCount > 1)
								//ChatPacket(CHAT_TYPE_INFO, "111 %s %d", item->GetName(), realCount);
								ChatPacket(CHAT_TYPE_INFO, "You earn x%d%s.", realCount, item->GetName());
							else
								//ChatPacket(CHAT_TYPE_INFO, "112 %s", item->GetName());
								ChatPacket(CHAT_TYPE_INFO, "You earn %s.", item->GetName());
						}
						M2_DESTROY_ITEM(item);
						return;
					}
				}
			}
		}
		item->SetCount(wCount);
	}

	const int cell = item->IsDragonSoul() ? GetEmptyDragonSoulInventory(item) : GetEmptyInventory(item->GetSize());
	if (cell != -1)
	{
		item->AddToCharacter(this, TItemPos(item->IsDragonSoul() ? DRAGON_SOUL_INVENTORY : INVENTORY, cell));
		if (printMsg)
		{
			if (realCount > 1)
				//ChatPacket(CHAT_TYPE_INFO, "111 %s %d", item->GetName(), realCount);
				ChatPacket(CHAT_TYPE_INFO, "You earn x%d%s.", realCount, item->GetName());
			else
				//ChatPacket(CHAT_TYPE_INFO, "112 %s", item->GetName());
				ChatPacket(CHAT_TYPE_INFO, "You earn %s.", item->GetName());
		}
	}
	else
	{
		if (printMsg && realCount != wCount)
		{
			if (realCount-wCount > 1)
				//ChatPacket(CHAT_TYPE_INFO, "111 %s %d", item->GetName(), realCount);
				ChatPacket(CHAT_TYPE_INFO, "You earn x%d%s.", realCount, item->GetName());
		}

		item->AddToGround(GetMapIndex(), GetXYZ());
		item->StartDestroyEvent();
		item->SetOwnership(this, 300);
	}
}
bool CHARACTER::CanPickupDirectly()
{
	return FindAffect(AFFECT_PICKUP_ENABLE) != NULL;
}
#endif
