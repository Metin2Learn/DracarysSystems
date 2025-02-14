# Search

	case HEADER_GG_BLOCK_CHAT:
		BlockChat(c_pData);
		break;

# Add after

#ifdef ENABLE_REWARD_SYSTEM
	case HEADER_GG_REWARD_INFO:
	{
		TPacketGGRewardInfo* data = (TPacketGGRewardInfo*)c_pData;
		CHARACTER_MANAGER::Instance().SetRewardData(data->rewardIndex, data->playerName, false);
	}
	break;
#endif

