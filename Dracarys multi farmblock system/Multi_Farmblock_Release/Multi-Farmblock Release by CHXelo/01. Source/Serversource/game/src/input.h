//Unter der Funktion: MyShop(LPCHARACTER ch, const char * c_pData, size_t uiBytes); hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		auto		RecvAntiFarmUpdateStatus(LPCHARACTER ch, const char* c_pData, size_t uiBytes) -> int;
#endif

//Unter der Funktion: IamAwake(LPDESC d, const char * c_pData); hinzuf�gen

#ifdef ENABLE_ANTI_MULTIPLE_FARM
		auto		RecvAntiFarmUpdateStatus(LPDESC d, const char* c_pData) -> void;
#endif
