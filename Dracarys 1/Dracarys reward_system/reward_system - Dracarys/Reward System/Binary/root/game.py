# Search

		onPressKeyDict[app.DIK_F4]	= lambda : self.__PressQuickSlot(7)

# Add after

		if app.ENABLE_REWARD_SYSTEM:
			onPressKeyDict[app.DIK_F8]	= lambda : self.interface.OpenRewardWindow()

# Search

		self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.ENABLE_REWARD_SYSTEM:
			serverCommandList.update({"RewardInfo" : self.SetRewardPlayers})

# Add

	if app.ENABLE_REWARD_SYSTEM:
		def SetRewardPlayers(self, data):
			self.interface.SetRewardPlayers(str(data))

