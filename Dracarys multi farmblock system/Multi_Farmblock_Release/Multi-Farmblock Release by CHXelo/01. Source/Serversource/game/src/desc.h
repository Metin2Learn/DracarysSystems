//Unter der Funktion: SetChannelStatusRequested(bool bChannelStatusRequested) { m_bChannelStatusRequested = bChannelStatusRequested; } hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		auto			SetLoginMacAdress(const char* recv_sMAIf) -> void { sMAIf = recv_sMAIf; }
		auto			GetLoginMacAdress() -> const char* { return sMAIf.c_str(); }
#endif

//Unter: m_adwEncryptionKey[4]; hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		std::string sMAIf;
#endif
