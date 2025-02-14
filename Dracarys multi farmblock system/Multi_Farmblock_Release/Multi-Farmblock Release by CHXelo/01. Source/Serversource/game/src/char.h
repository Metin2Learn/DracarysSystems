//Am Ende der Datei vor hinzufügen: 
//};
//ESex GET_SEX(LPCHARACTER ch);

#ifdef ENABLE_ANTI_MULTIPLE_FARM
	public:
		auto		HasBlockedDrops() -> bool;
		auto		UpdateCharacterWarpCheck(bool state) -> void { bAFisWarping = state; }
		auto		IsSetWarp() -> bool { return bAFisWarping; }

	protected:
		bool		bAFisWarping;
#endif
