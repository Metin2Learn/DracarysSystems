# Search

	Set(HEADER_CG_DRAGON_SOUL_REFINE, sizeof(TPacketCGDragonSoulRefine), "DragonSoulRefine", false);

# add after

#ifdef ENABLE_GUILD_REQUEST
	Set(HEADER_CG_GUILD_REQUEST, sizeof(TPacketCGGuildRequest), "GuildRequest", true);
#endif