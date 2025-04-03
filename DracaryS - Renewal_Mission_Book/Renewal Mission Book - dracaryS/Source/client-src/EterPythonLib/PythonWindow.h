# Search

		const char* GetUpVisualFileName();

# Add before

#if defined(RENEWAL_MISSION_BOOKS)
		static DWORD Type();
		void SetRenderingRect(float fLeft, float fTop, float fRight, float fBottom);
#endif

# Search

		void SetCurrentVisual(CGraphicImageInstance* pVisual);

# Change

#if defined(RENEWAL_MISSION_BOOKS)
		void SetCurrentVisual(CGraphicExpandedImageInstance* pVisual);
		BOOL OnIsType(DWORD dwType);
#else
		void SetCurrentVisual(CGraphicImageInstance* pVisual);
#endif

# Search

		CGraphicImageInstance* m_pcurVisual;
		CGraphicImageInstance m_upVisual;
		CGraphicImageInstance m_overVisual;
		CGraphicImageInstance m_downVisual;
		CGraphicImageInstance m_disableVisual;

# Change

#if defined(RENEWAL_MISSION_BOOKS)
		CGraphicExpandedImageInstance* m_pcurVisual;
		CGraphicExpandedImageInstance m_upVisual;
		CGraphicExpandedImageInstance m_overVisual;
		CGraphicExpandedImageInstance m_downVisual;
		CGraphicExpandedImageInstance m_disableVisual;
#else
		CGraphicImageInstance* m_pcurVisual;
		CGraphicImageInstance m_upVisual;
		CGraphicImageInstance m_overVisual;
		CGraphicImageInstance m_downVisual;
		CGraphicImageInstance m_disableVisual;
#endif

# Search

	class CRadioButton : public CButton

# Change

	class CRadioButton : public CButton
	{
	public:
#if defined(RENEWAL_MISSION_BOOKS)
		static DWORD Type();
#endif
		CRadioButton(PyObject* ppyObject);
		virtual ~CRadioButton();

	protected:
		BOOL OnMouseLeftButtonDown();
		BOOL OnMouseLeftButtonUp();
		void OnMouseOverIn();
		void OnMouseOverOut();
#if defined(RENEWAL_MISSION_BOOKS)
		BOOL OnIsType(DWORD dwType);
#endif
	};

# Search

	class CToggleButton : public CButton

# Change

	class CToggleButton : public CButton
	{
	public:
#if defined(RENEWAL_MISSION_BOOKS)
		static DWORD Type();
#endif
		CToggleButton(PyObject* ppyObject);
		virtual ~CToggleButton();

	protected:
		BOOL OnMouseLeftButtonDown();
		BOOL OnMouseLeftButtonUp();
		void OnMouseOverIn();
		void OnMouseOverOut();
#if defined(RENEWAL_MISSION_BOOKS)
		BOOL OnIsType(DWORD dwType);
#endif
	};

