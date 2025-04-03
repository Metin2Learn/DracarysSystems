# Search

	str_to_number(item.vnum, row[cur++]);

# Add after

#ifdef ENABLE_NEW_NAME_ITEM
		strlcpy(item.name, row[cur++],sizeof(item.name));
#endif

# Search x2

	"vnum,"

# Add after x2

#ifdef ENABLE_NEW_NAME_ITEM
				"name,"
#endif