# Add

#ifdef ENABLE_REWARD_SYSTEM
public:
	void				SetProtectTime(const std::string& flagname, int value);
	int					GetProtectTime(const std::string& flagname) const;
protected:
	std::map<std::string, int>  m_protection_Time;
#endif

