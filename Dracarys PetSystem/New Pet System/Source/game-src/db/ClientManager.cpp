# Search


	"SELECT id, window+0, pos, count, vnum, "

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
			"name, "
#endif


# Search

	"REPLACE INTO player.item (id, owner_id, window, pos, count, vnum, "

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	"name, "
#endif


# Search

	"VALUES(%u, %u, %d, %d, %u, %u, "

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
			"'%s', "
#endif

# Search

	p->vnum,

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	p->name,
#endif

