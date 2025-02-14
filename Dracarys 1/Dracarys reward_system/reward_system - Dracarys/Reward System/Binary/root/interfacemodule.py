# Add

if app.ENABLE_REWARD_SYSTEM:
	import uiReward


# Search

		self.tipBoard = None

# Add after

		if app.ENABLE_REWARD_SYSTEM:
			self.wndReward = None

# Search

	def Close(self):


# Add after

		if app.ENABLE_REWARD_SYSTEM:
			if self.wndReward:
				self.wndReward.Hide()
				self.wndReward.Destroy()
				self.wndReward = None

# add

	if app.ENABLE_REWARD_SYSTEM:
		def MakeRewardWindow(self):
			if self.wndReward == None:
				self.wndReward = uiReward.RewardWindow()
		def SetRewardPlayers(self, data):
			self.MakeRewardWindow()
			self.wndReward.SetRewardPlayers(data)
		def OpenRewardWindow(self):
			self.MakeRewardWindow()
			if self.wndReward.IsShow():
				self.wndReward.Close()
			else:
				self.wndReward.Open()

