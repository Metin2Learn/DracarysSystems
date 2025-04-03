# Search

	void CButton::Flash()
	{
		m_isFlash = TRUE;
	}

# Change


#ifdef ENABLE_NEW_PET_SYSTEM
	void CButton::Flash(bool bFlash)
	{
		m_isFlash = bFlash;
	}
#else
	void CButton::Flash()
	{
		m_isFlash = TRUE;
	}
#endif