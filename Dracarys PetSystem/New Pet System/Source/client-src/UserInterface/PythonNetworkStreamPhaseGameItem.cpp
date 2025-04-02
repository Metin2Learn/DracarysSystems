# Search in CPythonNetworkStream::RecvSafeBoxSetPacket()

	kItemData.count = kItemSet.count;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	sprintf(kItemData.name, "%s", kItemSet.name);
#endif



# Search in CPythonNetworkStream::RecvMallItemSetPacket()

	kItemData.count = kItemSet.count;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	sprintf(kItemData.name, "%s", kItemSet.name);
#endif


# Search in CPythonNetworkStream::RecvItemSetPacket()

	kItemData.count = packet_item_set.count;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	sprintf(kItemData.name, "%s", packet_item_set.name);
#endif

# Search in CPythonNetworkStream::RecvItemSetPacket2()

	kItemData.count = packet_item_set.count;

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	sprintf(kItemData.name, "%s", packet_item_set.name);
#endif


# Search

	rkPlayer.SetItemCount(packet_item_update.Cell, packet_item_update.count);

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	rkPlayer.SetItemNewName(packet_item_update.Cell, packet_item_update.name);
#endif




