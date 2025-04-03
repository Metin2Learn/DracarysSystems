# Search

void initskill()

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
PyObject* skillGetIconImageNewEx(PyObject* poSelf, PyObject* poArgs)
{
	char* skillFile;
	if (!PyTuple_GetString(poArgs, 0, &skillFile))
		return Py_BadArgument();
	CGraphicImage* pImage = (CGraphicImage*)CResourceManager::Instance().GetResourcePointer(skillFile);
	if(!pImage)
		return Py_BuildValue("i", 0);
	return Py_BuildValue("i", pImage);
}
#endif

# Search

	{ "DeleteIconInstance",						skillDeleteIconInstance,					METH_VARARGS },

# Add before

#ifdef ENABLE_NEW_PET_SYSTEM
		{ "GetIconImageNewEx",					skillGetIconImageNewEx,					METH_VARARGS },
#endif

