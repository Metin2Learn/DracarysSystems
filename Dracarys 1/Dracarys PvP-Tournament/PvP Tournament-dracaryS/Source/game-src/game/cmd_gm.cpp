# Add

#ifdef ENABLE_PVP_CAMERA_MODE
ACMD(do_camera_mode)
{
	std::vector<std::string> vecArgs;
	split_argument(argument, vecArgs);
	if (vecArgs.size() < 2) { return; }
	else if (vecArgs[1] == "camera_on")
	{
		if (vecArgs.size() < 3) { return; }
		LPCHARACTER cameraPlayer = CHARACTER_MANAGER::Instance().FindPC(vecArgs[2].c_str());
		if (!cameraPlayer)
			return;
		CHARACTER_MANAGER::Instance().SetCameraPlayer(cameraPlayer, ch);
	}
	else if (vecArgs[1] == "camera_off")
	{
		CHARACTER_MANAGER::Instance().RemoveCamera(ch);
	}
}
#endif
