# Search

	if (id == 0)
	{
		...
	}

# Add in top

#ifdef ENABLE_SUPPORT_SYSTEM
		if(vnum >= 61020 && vnum <= 61021){
			item->SetSocket(4, get_global_time()+60*60*1*24*7);
		}
#endif