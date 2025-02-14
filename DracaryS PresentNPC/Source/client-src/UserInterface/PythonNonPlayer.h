# Add

#ifdef ENABLE_NPC_WEAR_ITEM
enum
{
	NPC_WEAR_RACE,
	NPC_WEAR_WEAPON,
	NPC_WEAR_ARMOR,
	NPC_WEAR_HAIR,
	NPC_WEAR_ACCE,
	NPC_WEAR_MOUNT,
	NPC_WEAR_SHINING_WEAPON,
	NPC_WEAR_SHINING_ARMOR,
	NPC_WEAR_SHINING_SPECIAL,
	NPC_WEAR_SHINING_WING,
	NPC_WEAR_MAX,
};
#endif

# Search in class 

# Search 

public:

# Add before

#ifdef ENABLE_NPC_WEAR_ITEM
public:
	bool		LoadNPCWear(const char* szNPCWearFile);
	int			GetNPCWear(const int raceIndex, const BYTE wearIndex);
protected:
	std::map<std::string, std::map<DWORD, std::vector<int>>> m_mapnpcWear;
#endif
