# Search

	CPetSystem* GetPetSystem() { return m_petSystem; }

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	bool IsPet() const { return m_bCharType == CHAR_TYPE_PET; }
	void SetNewPet() { m_bIsNewPet = true; }
	bool IsNewPet() const { return m_bIsNewPet; }
	LPCHARACTER GetOwner() {return m_PetOwner;}
	void SetOwner(LPCHARACTER ch) { m_PetOwner = ch; }
	void StatePet();
	bool PetBlockMap();
#endif

# Search

	CPetSystem* m_petSystem;

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	bool m_bIsNewPet;
	LPCHARACTER	m_PetOwner;
	std::map<std::string, int>  m_protection_Time;
#endif

