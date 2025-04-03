# Search


PyObject* wndButtonFlash(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	((UI::CButton*)pWindow)->Flash();
	return Py_BuildNone();
}

# Change

#ifdef ENABLE_NEW_PET_SYSTEM
PyObject* wndButtonFlash(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	bool bFlash;
	if (!PyTuple_GetBoolean(poArgs, 1, &bFlash))
		return Py_BuildException();

	((UI::CButton*)pWindow)->Flash(bFlash);
	return Py_BuildNone();
}
#else
PyObject* wndButtonFlash(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	((UI::CButton*)pWindow)->Flash();
	return Py_BuildNone();
}
#endif