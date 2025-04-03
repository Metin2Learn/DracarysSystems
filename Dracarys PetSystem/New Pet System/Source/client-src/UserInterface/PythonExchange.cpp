# Search

	memset(&m_victim, 0, sizeof(m_victim));

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	for (DWORD i = 0; i < EXCHANGE_ITEM_MAX_NUM; i++)
	{
		m_self.item_name[i] = "^";
		m_victim.item_name[i] = "^";
	}
#endif

# Add

#ifdef ENABLE_NEW_NAME_ITEM
void CPythonExchange::SetItemNewName(int iPos, const char* name, bool bSelf)
{
	if (iPos >= EXCHANGE_ITEM_MAX_NUM)
		return;
	if (bSelf)
		m_self.item_name[iPos] = name;
	else
		m_victim.item_name[iPos] = name;
}

const char* CPythonExchange::GetItemNewName(int iPos, bool bSelf)
{
	if (iPos >= EXCHANGE_ITEM_MAX_NUM)
		return "^";
	return bSelf == true ? m_self.item_name[iPos].c_str() : m_victim.item_name[iPos].c_str();
}
#endif
