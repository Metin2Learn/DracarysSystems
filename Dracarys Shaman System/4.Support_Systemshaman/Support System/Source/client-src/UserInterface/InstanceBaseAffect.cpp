# Search

	CPythonTextTail::Instance().AttachLevel(GetVirtualID(), szText, s_kLevelColor);

# Add before

#ifdef ENABLE_SUPPORT_SYSTEM
	if (IsSupport())
		sprintf(szText, "|cffffff00Lv %d|r", level);
#endif

