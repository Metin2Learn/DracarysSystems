# Search

	case ITEM_QUEST:

# Add after

#if defined(__MISSION_BOOKS__)
		if (item->GetVnum() >= 50307 && item->GetVnum() <= 50309)
		{
			CHARACTER_MANAGER::Instance().GiveNewMission(item, this);
			return true;
		}
#endif

