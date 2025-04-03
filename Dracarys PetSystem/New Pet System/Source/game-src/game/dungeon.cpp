# Search struct

struct FKillSectree

# Search in

!ch->IsPC() 

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
				&& !ch->IsPet()
#endif

# Search struct

struct FPurgeSectree

# search in

!ch->IsPC() 

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
				&& !ch->IsPet()
#endif

