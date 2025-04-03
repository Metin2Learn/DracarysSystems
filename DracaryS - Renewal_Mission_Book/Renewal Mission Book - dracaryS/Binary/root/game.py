# Search

		self.serverCommander=stringCommander.Analyzer()

# add before

		if app.RENEWAL_MISSION_BOOKS:
			serverCommandList.update({"ClearBookMission" : self.interface.ClearBookMission})
			serverCommandList.update({"UpdateMissionInfo" : self.interface.UpdateMissionInfo})
			serverCommandList.update({"UpdateMissionValue" : self.interface.UpdateMissionValue})
			serverCommandList.update({"RewardMissionData" : self.interface.RewardMissionData})
			serverCommandList.update({"RemoveMissionData" : self.interface.RemoveMissionData})
			serverCommandList.update({"UpdateMissionEndTime" : self.interface.UpdateMissionEndTime})

# Search

		self.interface = interfaceModule.Interface()

# Add after

		constInfo.SetInterfaceInstance(self.interface)

# Search

		self.KillFocus()

# Add after

		constInfo.SetInterfaceInstance(None)
