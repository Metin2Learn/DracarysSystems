# search

	bool				m_bUsePendingDestroy;

# Add before

#ifdef ENABLE_PVP_CAMERA_MODE
	std::map<LPCHARACTER, std::vector<LPCHARACTER>> m_cameraMode;
#endif

# Search

	void			FlushPendingDestroy();

# Add after

#ifdef ENABLE_PVP_CAMERA_MODE
	bool			IsCameraModeMap(const DWORD mapIndex);
	void			SetCameraPlayer(LPCHARACTER camera, LPCHARACTER watcher);
	void			RemoveCamera(LPCHARACTER watcher);
	void			GetMyWatcher(LPCHARACTER camera, std::vector<LPCHARACTER>& m_data);
#endif