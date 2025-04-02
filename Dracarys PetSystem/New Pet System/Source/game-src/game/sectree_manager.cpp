# Search struct

struct FPurgeMonsters

# Search in

lpChar->IsMonster() == true 

# Add after

			#ifdef ENABLE_NEW_PET_SYSTEM
			&& !lpChar->IsPet()
			#endif
			
			
			
# Search struct

struct FPurgeNPCs

# Search in

lpChar->IsNPC() == true 

# Add after

			#ifdef ENABLE_NEW_PET_SYSTEM
			&& !lpChar->IsPet()
			#endif
			
			