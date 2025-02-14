# Add



#ifdef ENABLE_SUPPORT_SYSTEM
	#include "SupportSystem.h"
#endif


# Search x2

	&& !ch->IsPet()

# Add after x2
 
#ifdef ENABLE_SUPPORT_SYSTEM
					&& !ch->IsSupport()
#endif