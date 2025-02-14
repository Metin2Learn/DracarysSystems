# Add

#ifdef ENABLE_SUPPORT_SYSTEM
	#include "SupportSystem.h"
#endif

# Search

	iExp = AdjustExpByLevel(to, iExp);

# Add after

#ifdef ENABLE_SUPPORT_SYSTEM
	if (to->GetSupportSystem())
	{
		if (to->GetSupportSystem()->IsActiveSupport() && to->GetSupportSystem()->GetLevel() < 120)
		{
			to->GetSupportSystem()->SetExp(34998,from,iExp);
			to->GetSupportSystem()->SetExp(34999,from,iExp);
		}
	}
#endif

