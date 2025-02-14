# add

#ifdef __BACK_DUNGEON__
ACMD(do_back_dungeon)
{
	std::vector<std::string> vecArgs;
	split_argument(argument, vecArgs);
	if (vecArgs.size() < 2) { return; }
	DWORD mapIdx;
	if (!str_to_number(mapIdx, vecArgs[1].c_str()))
		return;
	CHARACTER_MANAGER::Instance().CheckBackDungeon(ch, BACK_DUNGEON_WARP, mapIdx);
}
#endif

