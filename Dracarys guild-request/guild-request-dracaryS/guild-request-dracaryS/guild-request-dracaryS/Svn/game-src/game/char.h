# Add

#ifdef ENABLE_GUILD_REQUEST
public:
	void				SetProtectTime(const std::string& flagname, int value);
	int					GetProtectTime(const std::string& flagname) const;
protected:
	std::map<std::string, int>  m_protection_Time;
#endif

