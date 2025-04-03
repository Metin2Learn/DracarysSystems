# Search

	BOOL CToggleButton::OnMouseLeftButtonDown()

# add before

#if defined(RENEWAL_MISSION_BOOKS)
	DWORD CToggleButton::Type()
	{
		static DWORD s_dwType = GetCRC32("CToggleButton", strlen("CToggleButton"));
		return (s_dwType);
	}
	BOOL CToggleButton::OnIsType(DWORD dwType)
	{
		if (CToggleButton::Type() == dwType)
			return TRUE;
		return FALSE;
	}
#endif

# Search

	BOOL CRadioButton::OnMouseLeftButtonDown()

# add before

#if defined(RENEWAL_MISSION_BOOKS)
	DWORD CRadioButton::Type()
	{
		static DWORD s_dwType = GetCRC32("CRadioButton", strlen("CRadioButton"));
		return (s_dwType);
	}
	BOOL CRadioButton::OnIsType(DWORD dwType)
	{
		if (CRadioButton::Type() == dwType)
			return TRUE;
		return FALSE;
	}
#endif

# Search

	void CButton::SetCurrentVisual(CGraphicImageInstance* pVisual)

# Change

#if defined(RENEWAL_MISSION_BOOKS)
	DWORD CButton::Type()
	{
		static DWORD s_dwType = GetCRC32("CButton", strlen("CButton"));
		return (s_dwType);
	}
	BOOL CButton::OnIsType(DWORD dwType)
	{
		if (CButton::Type() == dwType)
			return TRUE;
		return FALSE;
	}
	void CButton::SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom)
	{
		m_upVisual.SetRenderingRect(fLeft, fTop, fRight, fBottom);
		m_overVisual.SetRenderingRect(fLeft, fTop, fRight, fBottom);
		m_downVisual.SetRenderingRect(fLeft, fTop, fRight, fBottom);
		m_disableVisual.SetRenderingRect(fLeft, fTop, fRight, fBottom);
	}
	void CButton::SetCurrentVisual(CGraphicExpandedImageInstance* pVisual)
#else
	void CButton::SetCurrentVisual(CGraphicImageInstance* pVisual)
#endif

