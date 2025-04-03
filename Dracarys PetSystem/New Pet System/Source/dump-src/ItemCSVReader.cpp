# Add 

#define ENABLE_NEW_PET_SYSTEM


# Search

	"ITEM_BELT",

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
		"ITEM_PET",
#endif

# Search

static string arSub31[] =
	{
		"EXTRACT_DRAGON_SOUL",
		"EXTRACT_DRAGON_HEART"
	};

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	static string arSub35[] =
	{
		"PET_LEVELABLE",
		"PET_EGG",
		"PET_TRANSPORTBOX",
		"PET_PROTEIN",
		"PET_CHANGE_NAME_ITEM",
		"PET_DEW",
		"PET_SKILL",
		"PET_PRIMIUM_FEEDSTUFF",
		"PET_ATTR_CHANGE",
		"PET_ATTR_DETERMINE",
		"PET_EXPFOOD_PER",
		"PET_SKILL_DEL_BOOK",
		"PET_SKILL_ALL_DEL_BOOK",
		"PET_EXPFOOD",
		"PET_FEEDSTUFF",
	};
#endif

# Search

	arSub31,
		0,
		0,
		0,

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
		,arSub35
#endif

# Search

	sizeof(arSub31) / sizeof(arSub31[0]),
		0,
		0,
		0,

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
		,sizeof(arSub35) / sizeof(arSub35[0])
#endif

# Search

	"GOTO"

# Add after

#ifdef ENABLE_NEW_PET_SYSTEM
	,"PET"
#endif
