# Search

	case ITEM_QUEST:

# Add after

#ifdef __RENEWAL_BRAVE_CAPE__
		if (item->GetVnum() >= 20570 && item->GetVnum() <= 20575)
		{
			if (FindAffect(AFFECT_BRAVE_CAPE))
			{
				ChatPacket(CHAT_TYPE_INFO, "You already has this affect!");
				return false;
			}
			const int timeAdd = item->GetValue(0) > 30 ? INFINITE_AFFECT_DURATION : 60 * 60 * 24 * item->GetValue(0);
			if (!timeAdd)
			{
				ChatPacket(CHAT_TYPE_INFO, "[SYSTEM] Contact game master. This item not has time data!");
				return false;
			}

			AddAffect(AFFECT_BRAVE_CAPE, POINT_NONE, 0, AFF_NONE, timeAdd, 0, 0, false);
			item->SetCount(item->GetCount() - 1);
			return true;
		}
#endif