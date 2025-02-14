# Search

		{ NULL,							NULL,								NULL },

# add before

#ifdef ENABLE_PVP_CAMERA_MODE
		{ "GetCameraMode", playerGetCameraMode, METH_VARARGS },
		{ "SetCameraMode", playerSetCameraMode, METH_VARARGS },
#endif

# add

#ifdef ENABLE_PVP_CAMERA_MODE
PyObject* playerGetCameraMode(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonPlayer::Instance().GetCameraMode());
}
PyObject* playerSetCameraMode(PyObject* poSelf, PyObject* poArgs)
{
	bool iFlag;
	if (!PyTuple_GetBoolean(poArgs, 0, &iFlag))
		return Py_BadArgument();
	CPythonPlayer::Instance().SetCameraMode(iFlag);
	return Py_BuildNone();
}
#endif
