# Search

	marriage::CManager::instance().Login(ch);

# Add after

#ifdef ENABLE_EVENT_MANAGER
	CHARACTER_MANAGER::Instance().SendDataPlayer(ch);
#endif