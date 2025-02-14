# Search

		{ "GetGuildID",					chrGetGuildID,						METH_VARARGS },

# add before

#ifdef ENABLE_PVP_CAMERA_MODE
		{ "GetVIDByName",				chrGetVIDByName,					METH_VARARGS },
		{ "SetMainInstance",				chrSetMainInstance,					METH_VARARGS },
#endif

# Add

#ifdef ENABLE_PVP_CAMERA_MODE
#include "PythonPlayer.h"
PyObject* chrGetVIDByName(PyObject* poSelf, PyObject* poArgs)
{
	char* iName;
	if (!PyTuple_GetString(poArgs, 0, &iName))
		return Py_BuildException();

	CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetInstancePtrByName(iName);

	if (!pInstance)
		return Py_BuildValue("i", -1);
	return Py_BuildValue("i", pInstance->GetVirtualID());
}
PyObject* chrSetMainInstance(PyObject* poSelf, PyObject* poArgs)
{
	char* iName;
	if (!PyTuple_GetString(poArgs, 0, &iName))
		return Py_BuildException();
	char* iRealName;
	if (!PyTuple_GetString(poArgs, 1, &iRealName))
		return Py_BuildException();
	bool iFlag;
	if (!PyTuple_GetBoolean(poArgs, 2, &iFlag))
		return Py_BuildException();

	CPythonPlayer::Instance().NEW_Stop();
	//if (!CPythonPlayer::Instance().IsObserverMode())
	//	return Py_BuildValue("i", 0);

	CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetInstancePtrByName(iName);
	if (!pInstance)
	{
		CPythonPlayer::Instance().SetCameraMode(false);
		pInstance = CPythonCharacterManager::Instance().GetInstancePtrByName(iRealName);
		if (pInstance)
			CPythonPlayer::Instance().SetMainCharacterIndex(pInstance->GetVirtualID());

		CPythonPlayer::Instance().SetMainCharacterName("");
		return Py_BuildValue("i", 0);
	}
	CPythonPlayer::Instance().SetCameraMode(iFlag);
	CPythonPlayer::Instance().SetMainCharacterIndex(pInstance->GetVirtualID());
	CPythonPlayer::Instance().SetMainCharacterName(iName);
	return Py_BuildValue("i", 1);
}
#endif
