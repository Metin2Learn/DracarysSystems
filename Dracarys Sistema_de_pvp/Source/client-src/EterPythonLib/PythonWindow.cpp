# Search

		m_bycurIndex = rand() % m_ImageVector.size();

# Add after

#ifdef ENABLE_PVP_TOURNAMENT
		SetSize(pImageInstance->GetWidth(), pImageInstance->GetHeight());
#endif

# Search

	void CAniImageBox::OnChangePosition()

# Add before

#ifdef ENABLE_PVP_TOURNAMENT
	void CAniImageBox::ClearImages()
	{
		for_each(m_ImageVector.begin(), m_ImageVector.end(), CGraphicExpandedImageInstance::DeleteExpandedImageInstance);
		m_ImageVector.clear();
	}
#endif