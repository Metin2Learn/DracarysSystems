# Add like other command

#ifdef RENEWAL_PICKUP_AFFECT
ACMD(do_pickup_affect);
#endif

#ifdef RENEWAL_PICKUP_AFFECT
	{ "pickup_affect",	do_pickup_affect,		0,		POS_DEAD,	GM_PLAYER },
#endif
