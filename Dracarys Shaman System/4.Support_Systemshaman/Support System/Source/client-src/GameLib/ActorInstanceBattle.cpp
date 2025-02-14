# Search

bool CActorInstance::CanAct()
{
	...
}

# Add in

#ifdef ENABLE_SUPPORT_SYSTEM
	if (IsSupport())
		return false;
#endif
