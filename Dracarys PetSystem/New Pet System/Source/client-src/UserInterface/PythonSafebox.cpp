# Search

{ NULL,							NULL,									NULL },

# Add before

#ifdef ENABLE_NEW_NAME_ITEM
		{ "GetItemNewName",				safeboxGetItemNewName,					METH_VARARGS },
#endif

# Search

void initsafebox()

# Add before


#ifdef ENABLE_NEW_NAME_ITEM
PyObject* safeboxGetItemNewName(PyObject* poSelf, PyObject* poArgs)
{
	int ipos;
	if (!PyTuple_GetInteger(poArgs, 0, &ipos))
		return Py_BadArgument();

	TItemData* pInstance;
	if (CPythonSafeBox::Instance().GetItemDataPtr(ipos, &pInstance))
		return Py_BuildValue("s", pInstance->name);

	return Py_BuildValue("s", "^");
}
#endif

