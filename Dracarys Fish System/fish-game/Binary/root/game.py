# Search

	self.playerGauge = None

# Add after

	self.FishGame=None

# Search

	self.serverCommander=stringCommander.Analyzer()

# Add before

	serverCommandList.update({"OpenFish" : self.OpenFish })

# Add

	def OpenFish(self, p):
		n = int(p)
		if n == 1:
			import uifishgame
			self.FishGame = uifishgame.FishGame()
			self.FishGame.SetCenterPosition()
			self.FishGame.Show()
		else:
			if self.FishGame:
				self.FishGame.Close()
			self.FishGame=0
