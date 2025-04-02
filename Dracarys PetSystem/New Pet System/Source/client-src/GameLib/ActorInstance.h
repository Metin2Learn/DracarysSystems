# Search

	bool IsPet();

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	bool IsNewPet();
#endif

# Search

			TYPE_GOTO,

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
			TYPE_PET,
#endif

