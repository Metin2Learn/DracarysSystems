# Search

void initTrade()

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
PyObject* exchangeGetItemNewName(PyObject* poTarget, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BuildException();
	bool bSelf;
	if (!PyTuple_GetBoolean(poArgs, 1, &bSelf))
		return Py_BadArgument();
	return Py_BuildValue("s", CPythonExchange::Instance().GetItemNewName(iPos, bSelf));
}
#endif
#ifdef ENABLE_PERMA_ITEM
PyObject* exchangeGetItemPerma(PyObject* poTarget, PyObject* poArgs)
{
	int iPos;
	if (!PyTuple_GetInteger(poArgs, 0, &iPos))
		return Py_BuildException();

	bool bSelf;
	if (!PyTuple_GetBoolean(poArgs, 1, &bSelf))
		return Py_BadArgument();

	return Py_BuildValue("i", CPythonExchange::Instance().GetItemPerma(iPos, bSelf));
}
#endif

# Search

	{NULL, NULL},

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
		{"GetItemNewName", exchangeGetItemNewName, METH_VARARGS},
#endif

