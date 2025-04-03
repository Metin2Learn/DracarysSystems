# Search

			for (int j = 0; j < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++j)
				CPythonExchange::Instance().SetItemAttributeToSelf(iSlotIndex, j, exchange_packet.aAttr[j].bType, exchange_packet.aAttr[j].sValue);

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
			CPythonExchange::Instance().SetItemNewName(iSlotIndex, exchange_packet.name, true);
#endif

# Search


			for (int j = 0; j < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++j)
				CPythonExchange::Instance().SetItemAttributeToTarget(iSlotIndex, j, exchange_packet.aAttr[j].bType, exchange_packet.aAttr[j].sValue);

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
			CPythonExchange::Instance().SetItemNewName(iSlotIndex, exchange_packet.name, false);
#endif

# Search

	if (PointChange.dwVID == pInstance->GetVirtualID())
	{
		...
	}

# Add afterr

		else
		{
			pInstance = rkChrMgr.GetInstancePtr(PointChange.dwVID);
			if (pInstance)
				if (POINT_LEVEL == PointChange.Type)
				{

					pInstance->UpdateTextTailLevel(PointChange.value);

#ifdef ENABLE_NEW_PET_SYSTEM
					pInstance->RefreshModelScale();
#endif
				}
		}