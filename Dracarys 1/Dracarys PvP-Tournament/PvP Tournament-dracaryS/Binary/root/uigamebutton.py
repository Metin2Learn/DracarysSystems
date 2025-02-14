# Search

if app.ENABLE_PVP_TOURNAMENT:
	import constInfo

# Search

			self.gameButtonDict={
				"STATUS" : self.GetChild("StatusPlusButton"),
				"SKILL" : self.GetChild("SkillPlusButton"),
				"QUEST" : self.GetChild("QuestButton"),
				"BUILD" : self.GetChild("BuildGuildBuilding"),
				"EXIT_OBSERVER" : self.GetChild("ExitObserver"),
			}

# Add after

			if app.ENABLE_PVP_TOURNAMENT:
				self.gameButtonDict["EXIT_CAMERA_MODE"] = self.GetChild("ExitCameraMode")
				self.gameButtonDict["EXIT_CAMERA_MODE"].SetEvent(ui.__mem_func__(self.__OnClickExitCameraMode))

# Add

	if app.ENABLE_PVP_TOURNAMENT:
		def __OnClickExitCameraMode(self):
			if app.GUILD_WAR_COUNTER:
				interface = constInfo.GetInterfaceInstance()
				if interface != None:
					if interface.wndGuildWar:
						interface.wndGuildWar.ExitCameraMode()

			if app.ENABLE_PVP_TOURNAMENT:
				interface = constInfo.GetInterfaceInstance()
				if interface != None:
					if interface.wndPvPDuel:
						interface.wndPvPDuel.ExitCameraMode()
		def UpdateCameraMode(self):
			isEnable = player.GetCameraMode()
			if isEnable:
				self.gameButtonDict["EXIT_CAMERA_MODE"].Show()
			else:
				self.gameButtonDict["EXIT_CAMERA_MODE"].Hide()
