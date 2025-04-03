# Add

if app.RENEWAL_MISSION_BOOKS:
	import uiMission

# Search

		self.windowOpenPosition = 0

# Add after

		if app.RENEWAL_MISSION_BOOKS:
			self.wndBookMission = None

# Search

	def Close(self):

# Add after

		if app.RENEWAL_MISSION_BOOKS:
			if self.wndBookMission:
				self.wndBookMission.Close()
				self.wndBookMission.Destroy()
				self.wndBookMission = None

# Add

	if app.RENEWAL_MISSION_BOOKS:
		def MakeBookMission(self):
			if self.wndBookMission == None:
				self.wndBookMission = uiMission.MissionWindow()
		def OpenBookMission(self):
			self.MakeBookMission()
			if self.wndBookMission.IsShow():
				self.wndBookMission.Close()
			else:
				self.wndBookMission.Open()
		def ClearBookMission(self):
			self.MakeBookMission()
			self.wndBookMission.Clear()
		def UpdateMissionInfo(self, cmd):
			self.wndBookMission.UpdateMissionInfo(cmd)
		def UpdateMissionValue(self, missionID, value):
			self.wndBookMission.UpdateMissionValue(int(missionID), int(value))
		def RewardMissionData(self, missionID, rewardStatus):
			self.wndBookMission.RewardMissionData(int(missionID), int(rewardStatus))
		def RemoveMissionData(self, missionID):
			self.wndBookMission.RemoveMissionData(int(missionID))
		def UpdateMissionEndTime(self, missionID, endTime):
			self.wndBookMission.UpdateMissionEndTime(int(missionID), str(endTime))
