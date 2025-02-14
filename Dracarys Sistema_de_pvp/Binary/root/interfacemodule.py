# add

if app.ENABLE_PVP_TOURNAMENT:
	import uiPvPDuel

# Search

		self.wndItemSelect=None

# Add after

		if app.ENABLE_PVP_TOURNAMENT:
			self.wndPvPDuel=None
			self.wndPvPDuelPanel=None

# Search

	def Close(self):

# Add after

		if app.ENABLE_PVP_TOURNAMENT:
			if self.wndPvPDuel:
				self.wndPvPDuel.Hide()
				self.wndPvPDuel.Destroy()
				self.wndPvPDuel=None
			if self.wndPvPDuelPanel:
				self.wndPvPDuelPanel.Hide()
				self.wndPvPDuelPanel.Destroy()
				self.wndPvPDuelPanel=None

# Add

	if app.ENABLE_PVP_TOURNAMENT:
		def MakePvPDuel(self):
			if self.wndPvPDuel == None:
				self.wndPvPDuel= uiPvPDuel.DuelInfoWindow()
		def SetPvPTournamentClear(self, arenaIndex):
			self.MakePvPDuel()
			self.wndPvPDuel.ClearArena(arenaIndex)
		def SetPvPTournamentStartTime(self, arenaIndex, serverStartTime):
			self.MakePvPDuel()
			self.wndPvPDuel.SetStartTime(arenaIndex, serverStartTime)
		def SetPvPTournamentRace(self, arenaIndex, playerIndex, playerRace):
			self.MakePvPDuel()
			self.wndPvPDuel.SetRace(arenaIndex, playerIndex, playerRace)
		def SetPvPTournamentScore(self, arenaIndex, playerIndex, playerScore):
			self.MakePvPDuel()
			self.wndPvPDuel.SetScore(arenaIndex, playerIndex, playerScore)
		def SetPvPTournamentName(self, arenaIndex, playerIndex, playerName):
			self.MakePvPDuel()
			self.wndPvPDuel.SetName(arenaIndex, playerIndex, playerName)
		def SetPvPTournamentHP(self, arenaIndex, playerIndex, playerHPPercent, playerMinHP, playerMaxHP, isPoisoned):
			self.MakePvPDuel()
			self.wndPvPDuel.SetHP(arenaIndex, playerIndex, playerHPPercent, playerMinHP, playerMaxHP, isPoisoned)
		def MakePvPDuelPanel(self):
			if self.wndPvPDuelPanel == None:
				self.wndPvPDuelPanel = uiPvPDuel.PvPDuelAdminPanel()
		def OpenPvPDuelPanel(self):
			self.MakePvPDuelPanel()
			self.wndPvPDuelPanel.Show()
