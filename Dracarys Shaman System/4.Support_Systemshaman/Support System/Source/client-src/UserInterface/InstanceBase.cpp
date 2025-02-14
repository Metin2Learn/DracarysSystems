# Search

bool CInstanceBase::IsAttackableInstance(CInstanceBase& rkInstVictim)
{
	...
}

# Add in top


#ifdef ENABLE_SUPPORT_SYSTEM
	if (IsSupport())
		return false;
#endif


# Search

bool CInstanceBase::IsPartyMember()
{
	return m_isPartyMember;
}

# Add after

#ifdef ENABLE_SUPPORT_SYSTEM
BOOL CInstanceBase::IsSupport()
{
	return m_GraphicThingInstance.IsSupport();
}
#endif


# Search

	SetMoveSpeed(c_rkCreateData.m_dwMovSpd);

# Add after


#ifdef ENABLE_SUPPORT_SYSTEM
	if(IsSupport())
		m_GraphicThingInstance.SetScale(0.5, 0.5, 0.5, true);
#endif
