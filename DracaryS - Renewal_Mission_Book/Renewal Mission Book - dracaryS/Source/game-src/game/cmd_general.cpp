# Add

#if defined(__MISSION_BOOKS__)
ACMD(do_missionbooks)
{
	std::vector<std::string> vecArgs;
	split_argument(argument, vecArgs);
	if (vecArgs.size() < 2) { return; }
	else if (vecArgs[1] == "load")
	{
		ch->SendMissionData();
	}
	else if (vecArgs[1] == "delete")
	{
		if (vecArgs.size() < 3) { return; }
		WORD missionID;
		str_to_number(missionID, vecArgs[2].c_str());
		ch->DeleteBookMission(missionID);
	}
	else if (vecArgs[1] == "reward")
	{
		if (vecArgs.size() < 3) { return; }
		WORD missionID;
		str_to_number(missionID, vecArgs[2].c_str());
		ch->RewardMissionBook(missionID);
	}
}
#endif
