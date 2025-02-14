# Add

#ifdef ENABLE_EVENT_MANAGER
ACMD(do_event_manager)
{
	CHARACTER_MANAGER::Instance().SendDataPlayer(ch);
}
#endif

