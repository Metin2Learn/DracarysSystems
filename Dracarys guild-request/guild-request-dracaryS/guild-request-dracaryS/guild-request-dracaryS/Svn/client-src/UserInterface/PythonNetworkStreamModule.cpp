# Search

void initnet()

# Add before

#ifdef ENABLE_GUILD_REQUEST
PyObject* netSendGuildRequestPage(PyObject* poSelf, PyObject* poArgs)
{
	BYTE szTab;
	if (!PyTuple_GetByte(poArgs, 0, &szTab))
		return Py_BuildException();
	int szPage;
	if (!PyTuple_GetInteger(poArgs, 1, &szPage))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendGuildRequestPage(szTab, szPage);
	return Py_BuildNone();
}
PyObject* netSendGuildRequestName(PyObject* poSelf, PyObject* poArgs)
{
	BYTE szTab;
	if (!PyTuple_GetByte(poArgs, 0, &szTab))
		return Py_BuildException();
	char* szName;
	if (!PyTuple_GetString(poArgs, 1, &szName))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendGuildRequestName(szTab, szName);
	return Py_BuildNone();
}
PyObject* netSendGuildRequest(PyObject* poSelf, PyObject* poArgs)
{
	int szGuildID;
	if (!PyTuple_GetInteger(poArgs, 0, &szGuildID))
		return Py_BuildException();
	BYTE szRequestIndex;
	if (!PyTuple_GetByte(poArgs, 1, &szRequestIndex))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendGuildRequest(szGuildID, szRequestIndex);
	return Py_BuildNone();
}
#endif

# Search

{ NULL,										NULL,										NULL		 },

# Add before

#ifdef ENABLE_GUILD_REQUEST
		{ "SendGuildRequestPage", netSendGuildRequestPage, METH_VARARGS },
		{ "SendGuildRequestName", netSendGuildRequestName, METH_VARARGS },
		{ "SendGuildRequest", netSendGuildRequest, METH_VARARGS },
#endif
