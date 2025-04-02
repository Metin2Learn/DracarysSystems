# Search

PyObject* chatGetLinkFromHyperlink(PyObject* poSelf, PyObject* poArgs)

# Change

PyObject* chatGetLinkFromHyperlink(PyObject* poSelf, PyObject* poArgs)
{
	char* szHyperlink;

	if (!PyTuple_GetString(poArgs, 0, &szHyperlink))
		return Py_BuildException();

	std::string stHyperlink(szHyperlink);
	std::vector<std::string> results;

	split_string(stHyperlink, ":", results, false);

	if (0 == results[0].compare("item"))
	{
		if (results.size() < 6)
			return Py_BuildValue("s", "");
		CItemData* pItemData = NULL;
		if (CItemManager::Instance().GetItemDataPointer(htoi(results[1].c_str()), &pItemData))
		{
			char buf[1024] = { 0 };
			char itemlink[256*2];
			int len;
			bool isAttr = false;

			len = snprintf(itemlink, sizeof(itemlink), "item:%x:%x"
#ifdef ENABLE_NEW_NAME_ITEM
				":%s"
#endif
				":%x:%x:%x:%x:%x:%x:%x:%x",
				htoi(results[1].c_str()),
				htoi(results[2].c_str()),
				htoi(results[3].c_str()),
				htoi(results[4].c_str()),
				htoi(results[5].c_str()),
				htoi(results[6].c_str()),
				htoi(results[7].c_str()),
				htoi(results[8].c_str()),
				htoi(results[9].c_str()),
				htoi(results[10].c_str())
#ifdef ENABLE_NEW_NAME_ITEM
				,results[11].c_str()
#endif
			
			);
			if (results.size() >= 12)
			{
				for (int i = 12; i < results.size(); i += 2)
				{
					len += snprintf(itemlink + len, sizeof(itemlink) - len, ":%x:%lld",
						htoi(results[i].c_str()),
						atoi(results[i + 1].c_str()));
					isAttr = true;
				}
			}

			if (isAttr)
			{
#ifdef ENABLE_NEW_NAME_ITEM
				if(results[11] != "^")
					snprintf(buf, sizeof(buf), "|cffffc700|H%s|h[%s]|h|r", itemlink, results[11].c_str());
				else
#endif
					snprintf(buf, sizeof(buf), "|cffffc700|H%s|h[%s]|h|r", itemlink, pItemData->GetName());
			}
			else
			{
#ifdef ENABLE_NEW_NAME_ITEM
				if(results[11] != "^")
					snprintf(buf, sizeof(buf), "|cfff1e6c0|H%s|h[%s]|h|r", itemlink, results[11].c_str());
				else
#endif
					snprintf(buf, sizeof(buf), "|cfff1e6c0|H%s|h[%s]|h|r", itemlink, pItemData->GetName());
			}

			return Py_BuildValue("s", buf);
		}
	}
	return Py_BuildValue("s", "");
}