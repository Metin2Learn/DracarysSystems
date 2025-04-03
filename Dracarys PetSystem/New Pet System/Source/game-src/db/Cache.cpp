
# Search

	"id, owner_id, window, pos, count, vnum"

# Add like this

	"id, owner_id, window, pos, count, vnum"
#ifdef ENABLE_NEW_NAME_ITEM
	",name"
#endif

# Search

	"%u, %u, %d, %d, %u, %u"

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	", '%s'"
#endif


# Search

	, p->id, p->owner, p->window, p->pos, p->count, p->vnum

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	,p->name
#endif

# Search

	 "owner_id=%u, window=%d, pos=%d, count=%u, vnum=%u"

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	",name='%s'"
#endif

# Search

	, p->owner, p->window, p->pos, p->count, p->vnum

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
	, p->name
#endif



