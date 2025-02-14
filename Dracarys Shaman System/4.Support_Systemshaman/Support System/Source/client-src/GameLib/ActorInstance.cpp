# Search

bool CActorInstance::IsEnemy()
{
	if (TYPE_ENEMY == m_eActorType)
		return true;

	return false;
}

# Add above:

#ifdef ENABLE_SUPPORT_SYSTEM
bool CActorInstance::IsSupport()
{
	if (m_eRace == 34998 || m_eRace == 34999)
		return true;
	return false;
}
#endif

