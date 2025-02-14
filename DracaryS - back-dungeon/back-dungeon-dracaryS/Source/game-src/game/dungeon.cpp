# Search

	pDungeon->deadEvent = NULL;

	CDungeonManager::instance().Destroy(info->dungeon_id);

# Add before

#ifdef __BACK_DUNGEON__
	if (pDungeon->GetFlag("can_back_dungeon") == 1)
		return PASSES_PER_SEC(2);
#endif

# Search

void CDungeon::JumpAll(long lFromMapIndex, int x, int y)

# Search in

	x *= 100;
	y *= 100;

# Add after

#ifdef __BACK_DUNGEON__
	SetFlag("LAST_X", x);
	SetFlag("LAST_Y", y);
#endif


# Search

void CDungeon::WarpAll(long lFromMapIndex, int x, int y)

# Search in

	x *= 100;
	y *= 100;

# Add after

#ifdef __BACK_DUNGEON__
	SetFlag("LAST_X", x);
	SetFlag("LAST_Y", y);
#endif


# Search

void CDungeon::JumpParty(LPPARTY pParty, long lFromMapIndex, int x, int y)

# Search in

	x *= 100;
	y *= 100;

# Add after

#ifdef __BACK_DUNGEON__
	SetFlag("LAST_X", x);
	SetFlag("LAST_Y", y);
#endif

# Search

void CDungeonManager::Destroy(CDungeon::IdType dungeon_id)


#Search in

	m_map_pkDungeon.erase(dungeon_id);

# Add before

#ifdef __BACK_DUNGEON__
	CHARACTER_MANAGER::Instance().CheckBackDungeon(NULL, BACK_DUNGEON_REMOVE);
#endif


