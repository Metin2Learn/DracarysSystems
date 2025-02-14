# Search

	Set(HEADER_GG_XMAS_WARP_SANTA_REPLY, sizeof(TPacketGGXmasWarpSantaReply), "XmasWarpSantaReply", false);

# Add after

#ifdef ENABLE_REWARD_SYSTEM
	Set(HEADER_GG_REWARD_INFO, sizeof(TPacketGGRewardInfo), "RewardInfo", false);
#endif
