# Search

	{ NULL,							NULL,								NULL },

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
		{ "GetItemNewName", playerGetItemNewName, METH_VARARGS },
#endif

# Search

void initPlayer()

# add before

#ifdef ENABLE_NEW_NAME_ITEM
PyObject* playerGetItemNewName(PyObject* poSelf, PyObject* poArgs)
{
	switch (PyTuple_Size(poArgs))
	{
		case 1:
		{
			int iSlotIndex;
			if (!PyTuple_GetInteger(poArgs, 0, &iSlotIndex))
				return Py_BuildException();
			return Py_BuildValue("s", CPythonPlayer::Instance().GetItemNewName(TItemPos(INVENTORY, iSlotIndex)));
		}
		case 2:
		{
			TItemPos Cell;
			if (!PyTuple_GetByte(poArgs, 0, &Cell.window_type))
				return Py_BuildException();
			if (!PyTuple_GetInteger(poArgs, 1, &Cell.cell))
				return Py_BuildException();
			return Py_BuildValue("s", CPythonPlayer::Instance().GetItemNewName(Cell));
		}
	}
	return Py_BuildValue("s", "^");
}
#endif

# Search

PyObject* playerGetItemLink(PyObject* poSelf, PyObject* poArgs)

# Change

PyObject* playerGetItemLink(PyObject* poSelf, PyObject* poArgs)
{
	TItemPos Cell;

	switch (PyTuple_Size(poArgs))
	{
	case 1:
		if (!PyTuple_GetInteger(poArgs, 0, &Cell.cell))
			return Py_BuildException();
		break;
	case 2:
		if (!PyTuple_GetByte(poArgs, 0, &Cell.window_type))
			return Py_BuildException();
		if (!PyTuple_GetInteger(poArgs, 1, &Cell.cell))
			return Py_BuildException();
		break;
	default:
		return Py_BuildException();
	}
	const TItemData* pPlayerItem = CPythonPlayer::Instance().GetItemData(Cell);
	CItemData* pItemData = NULL;
	char buf[1024];

	if (pPlayerItem && CItemManager::Instance().GetItemDataPointer(pPlayerItem->vnum, &pItemData))
	{
		char itemlink[256*2];
		int len;
		bool isAttr = false;
		len = snprintf(itemlink, sizeof(itemlink), "item:%x:%x"
#ifdef ENABLE_NEW_NAME_ITEM
			":%s"
#endif
			":%x:%x:%x:%x:%x:%x:%x:%x",
			pPlayerItem->vnum, pPlayerItem->flags,
#ifdef ENABLE_NEW_NAME_ITEM
			pPlayerItem->name,
#endif
			pPlayerItem->alSockets[0], pPlayerItem->alSockets[1], pPlayerItem->alSockets[2], pPlayerItem->alSockets[3], pPlayerItem->alSockets[4], pPlayerItem->alSockets[5], pPlayerItem->alSockets[6], pPlayerItem->alSockets[7]);

		for (int i = 0; i < ITEM_ATTRIBUTE_SLOT_MAX_NUM; ++i)
			if (pPlayerItem->aAttr[i].bType != 0)
			{
				len += snprintf(itemlink + len, sizeof(itemlink) - len, ":%x:%d",
					pPlayerItem->aAttr[i].bType, pPlayerItem->aAttr[i].sValue);
				isAttr = true;
			}

		
		if (GetDefaultCodePage() == CP_ARABIC) {
			if (isAttr)
				snprintf(buf, sizeof(buf), " |h|r[%s]|cffffc700|H%s|h",pItemData->GetName(), itemlink);
			else
				snprintf(buf, sizeof(buf), " |h|r[%s]|cfff1e6c0|H%s|h", pItemData->GetName(), itemlink);
		}
		else
		{

			if (isAttr)
			{
#ifdef ENABLE_NEW_NAME_ITEM
				if(!strstr(pPlayerItem->name,"^"))
					snprintf(buf, sizeof(buf), "|cffffc700|H%s|h[%s]|h|r", itemlink, pPlayerItem->name);
				else
#endif
					snprintf(buf, sizeof(buf), "|cffffc700|H%s|h[%s]|h|r", itemlink, pItemData->GetName());
			}
			else
			{
#ifdef ENABLE_NEW_NAME_ITEM
				if (!strstr(pPlayerItem->name, "^"))
					snprintf(buf, sizeof(buf), "|cfff1e6c0|H%s|h[%s]|h|r", itemlink, pPlayerItem->name);
				else
#endif
					snprintf(buf, sizeof(buf), "|cfff1e6c0|H%s|h[%s]|h|r", itemlink, pItemData->GetName());
			}
				
		}
	}
	else
		buf[0] = '\0';

	return Py_BuildValue("s", buf);
}
