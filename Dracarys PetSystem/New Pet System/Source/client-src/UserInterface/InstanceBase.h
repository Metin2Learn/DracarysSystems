# Search

	BOOL					IsPet();

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	BOOL					IsNewPet();
	void					RefreshModelScale();
#endif