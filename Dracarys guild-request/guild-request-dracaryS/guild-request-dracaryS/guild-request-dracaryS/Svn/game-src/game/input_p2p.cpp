# Search

	default:
		sys_err("UNKNOWN GUILD SUB PACKET");
		break;

# Add before

#ifdef ENABLE_GUILD_REQUEST
	case GUILD_SUBHEADER_UPDATE_REQUEST:
	{
		CGuild* pGuild = CGuildManager::instance().FindGuild(p->dwGuild);
		if (pGuild)
			pGuild->ReloadRequest();
	}
	break;
#endif