# Search

	void CAniImageBox::AppendImage(const char* c_szFileName)

# Add before

	void CAniImageBox::SetRotation(float fRotation)
	{
		for (BYTE a = 0; a < m_ImageVector.size(); a++)
		{
			CGraphicExpandedImageInstance* pImage = m_ImageVector[a];
			if (pImage)
				pImage->SetRotation(fRotation);
		}
	}
	