# Search

	m_dwTargetEndTime = 0;

# Add after

#ifdef ENABLE_PVP_CAMERA_MODE
	SetCameraMode(false);
#endif

# Search

	m_dwMainCharacterIndex = iIndex;

# Add after

#ifdef ENABLE_PVP_CAMERA_MODE
	if (GetCameraMode())
		return;
#endif

