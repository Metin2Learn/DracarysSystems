# Add

#ifdef ENABLE_REWARD_SYSTEM
#include "char_manager.h"
#include "char.h"
#endif


# Search

pItem->AddAttribute(APPLY_NORMAL_HIT_DAMAGE_BONUS, iNormalHitBonus);

# Add after

#ifdef ENABLE_REWARD_SYSTEM
	if(iNormalHitBonus>=60)
	{
		LPCHARACTER ch = pItem->GetOwner();
		if(ch)
			CHARACTER_MANAGER::Instance().SetRewardData(REWARD_AVERAGE,ch->GetName(), true);
	}
#endif

