# Search

public:

# add before

#ifdef RENEWAL_PICKUP_AFFECT
public:
	bool		CanPickupDirectly();
	void		AutoGiveItemNew(LPITEM item, bool printMsg = true);
#endif
