# Add

#ifdef ENABLE_SUPPORT_SYSTEM
	#include "SupportSystem.h"
#endif

# Search


ACMD(do_item_purge)
{
	..
}


# Add in top

#ifdef ENABLE_SUPPORT_SYSTEM
	if (ch->GetSupportSystem() && ch->GetSupportSystem()->IsActiveSupport())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "when support active you can't to this!");
		return;
	}
#endif


# Search All

	&& !ch->IsPet()

# Add after

#ifdef ENABLE_SUPPORT_SYSTEM
					&& !ch->IsSupport()
#endif