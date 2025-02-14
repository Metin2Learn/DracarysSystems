#Search

	void FishingSuccess(LPCHARACTER ch)
	{
		TPacketGCFishing p;
		p.header = HEADER_GC_FISHING;
		p.subheader = FISHING_SUBHEADER_GC_SUCCESS;
		p.info = ch->GetVID();
		ch->PacketAround(&p, sizeof(p));
	}
	
	void FishingFail(LPCHARACTER ch)
	{
		TPacketGCFishing p;
		p.header = HEADER_GC_FISHING;
		p.subheader = FISHING_SUBHEADER_GC_FAIL;
		p.info = ch->GetVID();
		ch->PacketAround(&p, sizeof(p));
	}

# change

	void FishingSuccess(LPCHARACTER ch)
	{
		TPacketGCFishing p;
		p.header = HEADER_GC_FISHING;
		p.subheader = FISHING_SUBHEADER_GC_SUCCESS;
		p.info = ch->GetVID();
		ch->PacketAround(&p, sizeof(p));
		ch->fishGame = 0;
		ch->ChatPacket(CHAT_TYPE_COMMAND, "OpenFish 0");
	}
	
	void FishingFail(LPCHARACTER ch)
	{
		TPacketGCFishing p;
		p.header = HEADER_GC_FISHING;
		p.subheader = FISHING_SUBHEADER_GC_FAIL;
		p.info = ch->GetVID();
		ch->PacketAround(&p, sizeof(p));
		ch->fishGame = 0;
		ch->ChatPacket(CHAT_TYPE_COMMAND, "OpenFish 0");
	}

# Search
	return (PASSES_PER_SEC(6));

# Change

	return (PASSES_PER_SEC(10));

# Search

LPEVENT CreateFishingEvent(LPCHARACTER ch)

# Change

	LPEVENT CreateFishingEvent(LPCHARACTER ch)
	{
		fishing_event_info* info = AllocEventInfo<fishing_event_info>();
		info->pid = ch->GetPlayerID();
		info->step = 0;
		info->hang_time = 0;
	
		TPacketGCFishing p;
		p.header = HEADER_GC_FISHING;
		p.subheader = FISHING_SUBHEADER_GC_START;
		p.info = ch->GetVID();
		p.dir = (BYTE)(ch->GetRotation() / 5);
		ch->PacketAround(&p, sizeof(TPacketGCFishing));
		ch->fishGame=0;
		ch->ChatPacket(CHAT_TYPE_COMMAND, "OpenFish 1");
		return event_create(fishing_event, info, PASSES_PER_SEC(0));
	}

# Search

int Compute(DWORD fish_id, DWORD ms, DWORD* item, int level)

# Change

	int Compute(DWORD fish_id, DWORD ms, DWORD* item, int level)
	{
		if (fish_id == 0)
			return -2;

		if (fish_id >= MAX_FISH)
		{
			sys_err("Wrong FISH ID : %d", fish_id);
			return -2;
		}

		//if (ms > 6000)
		//	return -1;
		//
		//int time_step = MINMAX(0, ((ms + 99) / 200), MAX_FISHING_TIME_COUNT - 1);
		//
		//if (number(1, 100) <= aFishingTime[fish_info[fish_id].time_type][time_step])
		{
			if (number(1, fish_info[fish_id].difficulty) <= level)
			{
				*item = fish_info[fish_id].vnum;
				return 0;
			}
			return -3;
		}

		return -1;
	}




#Search

	void Take(fishing_event_info* info, LPCHARACTER ch)

# Search in

		if (info->step == 1)
	
# Add before

		if (ch->fishGame < 3)
			info->step = 2;


