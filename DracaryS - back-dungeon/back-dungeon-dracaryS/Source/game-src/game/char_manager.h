# search

public:

# add before

#ifdef __BACK_DUNGEON__
public:
	bool	CheckBackDungeon(LPCHARACTER ch, BYTE checkType, DWORD mapIdx = 0);
protected:
	std::map<DWORD, std::map<std::pair<DWORD, WORD>, std::vector<DWORD>>> m_mapbackDungeon;
#endif
