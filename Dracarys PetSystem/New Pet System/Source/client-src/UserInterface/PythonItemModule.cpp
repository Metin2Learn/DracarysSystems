# Search

	PyModule_AddIntConstant(poModule, "ITEM_TYPE_PENDANT", CItemData::ITEM_TYPE_PENDANT);

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_PET", CItemData::ITEM_TYPE_PET);
	PyModule_AddIntConstant(poModule, "PET_LEVELABLE", CItemData::PET_LEVELABLE);
	PyModule_AddIntConstant(poModule, "PET_EGG", CItemData::PET_EGG);
	PyModule_AddIntConstant(poModule, "PET_TRANSPORTBOX", CItemData::PET_TRANSPORTBOX);
	PyModule_AddIntConstant(poModule, "PET_PROTEIN", CItemData::PET_PROTEIN);
	PyModule_AddIntConstant(poModule, "PET_CHANGE_NAME_ITEM", CItemData::PET_CHANGE_NAME_ITEM);
	PyModule_AddIntConstant(poModule, "PET_DEW", CItemData::PET_DEW);
	PyModule_AddIntConstant(poModule, "PET_SKILL", CItemData::PET_SKILL);
	PyModule_AddIntConstant(poModule, "PET_PRIMIUM_FEEDSTUFF", CItemData::PET_PRIMIUM_FEEDSTUFF);
	PyModule_AddIntConstant(poModule, "PET_ATTR_CHANGE", CItemData::PET_ATTR_CHANGE);
	PyModule_AddIntConstant(poModule, "PET_ATTR_DETERMINE", CItemData::PET_ATTR_DETERMINE);
	PyModule_AddIntConstant(poModule, "PET_EXPFOOD_PER", CItemData::PET_EXPFOOD_PER);
	PyModule_AddIntConstant(poModule, "PET_SKILL_DEL_BOOK", CItemData::PET_SKILL_DEL_BOOK);
	PyModule_AddIntConstant(poModule, "PET_SKILL_ALL_DEL_BOOK", CItemData::PET_SKILL_ALL_DEL_BOOK);
	PyModule_AddIntConstant(poModule, "PET_EXPFOOD", CItemData::PET_EXPFOOD);
	PyModule_AddIntConstant(poModule, "PET_FEEDSTUFF", CItemData::PET_FEEDSTUFF);
#endif

# Search

PyModule_AddIntConstant(poModule, "BELT_INVENTORY_SLOT_END", c_Belt_Inventory_Slot_End);

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	PyModule_AddIntConstant(poModule, "EQUIPMENT_PET", c_Slot_Pet);
#endif

