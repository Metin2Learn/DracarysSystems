# Search

const char* CPythonPlayer::GetItemNameBySlot(TItemPos Cell)

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
void CPythonPlayer::SetItemNewName(TItemPos itemPos, const char* name)
{
	if (!itemPos.IsValidCell())
		return;
	sprintf((const_cast <TItemData*>(GetItemData(itemPos)))->name, "%s", name);
	PyCallClassMemberFunc(m_ppyGameWindow, "RefreshInventory", Py_BuildValue("()"));
}
const char* CPythonPlayer::GetItemNewName(TItemPos itemPos)
{
	if (itemPos.IsValidCell())
	{
		const TItemData* pkItem = GetItemData(itemPos);
		if (pkItem)
			return pkItem->name;
	}
	return "^";
}
#endif

