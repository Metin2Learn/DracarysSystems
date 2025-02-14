# Search

	void initwndMgr()

# Add before

PyObject* wndImageSetRotationAni(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	float fRotation;
	if (!PyTuple_GetFloat(poArgs, 1, &fRotation))
		return Py_BuildException();

	((UI::CAniImageBox*)pWindow)->SetRotation(fRotation);

	return Py_BuildNone();
}

#Search


{ NULL,		NULL,				NULL },

# Add before

{ "SetRotationAni",		wndImageSetRotationAni,				METH_VARARGS },