# Add

#ifdef ENABLE_PVP_TOURNAMENT
PyObject* wndImageClearImages(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	if (pWindow->IsType(UI::CAniImageBox::Type()))
		((UI::CAniImageBox*)pWindow)->ClearImages();
	return Py_BuildNone();
}
#endif

# Search

		{ "SetRotation",				wndImageSetRotation,				METH_VARARGS },

# add after

#ifdef ENABLE_PVP_TOURNAMENT
		{ "ClearImages",				wndImageClearImages,				METH_VARARGS },
#endif

