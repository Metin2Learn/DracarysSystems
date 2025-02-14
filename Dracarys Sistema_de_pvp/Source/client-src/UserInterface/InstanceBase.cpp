# Search

		__AttachEmpireEffect(c_rkCreateData.m_dwEmpireID);

# Add after

#ifdef ENABLE_PVP_CAMERA_MODE
		if (CPythonPlayer::Instance().GetCameraMode() && CPythonPlayer::Instance().GetMainCharacterName() == c_rkCreateData.m_stName)
			CPythonPlayer::Instance().SetMainCharacterIndex(GetVirtualID());
#endif