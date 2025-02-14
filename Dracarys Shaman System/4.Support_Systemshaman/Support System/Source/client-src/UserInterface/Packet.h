# Search

	HEADER_GC_AUTH_SUCCESS                      = 150,

# Add before:

#ifdef ENABLE_SUPPORT_SYSTEM
	HEADER_GC_SUPPORT_SKILL						= 149,
#endif

# Add

#ifdef ENABLE_SUPPORT_SYSTEM
typedef struct support_use_skill
{
	BYTE	bHeader;
	DWORD	dwVnum;
	DWORD	dwVid;
	DWORD	dwLevel;
}TPacketGCSupportUseSkill;
#endif
