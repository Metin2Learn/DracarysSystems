# Search

	if (!__CanMove())
		return;

#Add after

#ifdef ENABLE_PVP_CAMERA_MODE
	if (GetCameraMode())
	{
		m_isSmtMov = false;
		return;
	}
#endif

# Search

	switch (eDirKey)

# add before

#ifdef ENABLE_PVP_CAMERA_MODE
	if (GetCameraMode())
	{
		m_isSmtMov = false;
		return;
	}
#endif

# search

	if (NEW_CancelFishing())
		return;

# Add after

#ifdef ENABLE_PVP_CAMERA_MODE
	if (GetCameraMode())
	{
		m_isSmtMov = false;
		return;
	}
#endif
