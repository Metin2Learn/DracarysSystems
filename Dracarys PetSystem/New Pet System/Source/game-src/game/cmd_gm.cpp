# Search struct 

struct FuncPurge

# Search in

	pkChr->IsNPC()

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
		&& !pkChr->IsPet()
#endif