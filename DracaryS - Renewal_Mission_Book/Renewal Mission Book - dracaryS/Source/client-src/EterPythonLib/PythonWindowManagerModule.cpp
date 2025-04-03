# Search

	if (pWindow->IsType(UI::CExpandedImageBox::Type()))
		((UI::CExpandedImageBox*)pWindow)->SetRenderingRect(fLeft, fTop, fRight, fBottom);

# Add after

#if defined(RENEWAL_MISSION_BOOKS)
	else if (pWindow->IsType(UI::CButton::Type()))
		((UI::CButton*)pWindow)->SetRenderingRect(fLeft, fTop, fRight, fBottom);
	else if (pWindow->IsType(UI::CRadioButton::Type()))
		((UI::CRadioButton*)pWindow)->SetRenderingRect(fLeft, fTop, fRight, fBottom);
	else if (pWindow->IsType(UI::CToggleButton::Type()))
		((UI::CToggleButton*)pWindow)->SetRenderingRect(fLeft, fTop, fRight, fBottom);
#endif
