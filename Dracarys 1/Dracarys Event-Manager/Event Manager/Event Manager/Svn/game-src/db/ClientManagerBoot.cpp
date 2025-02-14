# Search

	if (!InitializeObjectTable())
	{
		sys_err("InitializeObjectTable FAILED");
		return false;
	}

# Add after

#ifdef ENABLE_EVENT_MANAGER
	if (!InitializeEventManager())
	{
		sys_err("InitializeEventManager FAILED");
		return false;
	}
#endif
