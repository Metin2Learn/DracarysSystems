# Add

#ifdef ENABLE_NEW_PET_SYSTEM
BOOL CInstanceBase::IsNewPet()
{
	return m_GraphicThingInstance.IsNewPet();
}
void CInstanceBase::RefreshModelScale()
{
	if (IsNewPet())
	{
		float fScale = static_cast<float>((float(m_dwLevel + 70) * 0.8f) / 100.0f);
		m_GraphicThingInstance.SetScaleWorld(fScale, fScale, fScale);
	}
}
#endif

# Search

	m_GraphicThingInstance.SetBattleHitEffect(ms_adwCRCAffectEffect[EFFECT_HIT]);

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	RefreshModelScale();
#endif
