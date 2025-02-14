# Add

#include "fishing.h"
ACMD(do_fishgame)
{
	LPITEM rod = ch->GetWear(WEAR_WEAPON);
	if (!rod)
		return;
	if (ch->m_pkFishingEvent)
	{
		char arg1[256];
		one_argument(argument, arg1, sizeof(arg1));
		int arg1_1 = atoi(arg1);
		if (arg1_1 == 58236)
		{
			++ch->fishGame;
		}
		else if (arg1_1 == 78531)
		{
			if (rod->GetType() == ITEM_ROD)
			{
				ch->fishing_take();
			}
		}
		else if (arg1_1 == 90295)
		{
			ch->m_pkFishingEvent = NULL;
			rod->SetSocket(2, 0);
			fishing::FishingFail(ch); // :)
		}
	}

}

