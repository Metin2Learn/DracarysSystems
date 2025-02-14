//In folgendem Struct: typedef struct _CCI hinzufügen
//unter: BYTE	bChannel;

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	char	cMAIf[MA_LENGTH + 1];
#endif

//Funktion mit Define austauschen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		void			Logout(const char* c_pszName, bool is_warping = false);
#else
		void			Logout(const char * c_pszName);
#endif

//Private Funktion mit Define austauschen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		void			Logout(CCI* pkCCI, bool is_warping = false);
#else
		void			Logout(CCI * pkCCI);
#endif
