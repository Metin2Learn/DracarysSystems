# Add

#ifdef ENABLE_NEW_PET_SYSTEM
#include "PetSystem.h"
#endif



# Search

	from->CreateFly(FLY_EXP, to);

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	CPetSystem* pet = to->GetPetSystem();
	if (pet)
		pet->PointChange(POINT_PET_EXP, iExp*300);
#endif
