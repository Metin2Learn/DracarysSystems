# Search

	void Flash();

# Change

#ifdef ENABLE_NEW_PET_SYSTEM
	void Flash(bool bFlash);
#else
	void Flash();
#endif