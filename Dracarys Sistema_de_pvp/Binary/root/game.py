# Search

		self.interface = interfaceModule.Interface()

# Add after

		if app.ENABLE_PVP_TOURNAMENT:
			constInfo.SetInterfaceInstance(self.interface)

# Search

		self.KillFocus()

# Add after

		if app.ENABLE_PVP_TOURNAMENT:
			constInfo.SetInterfaceInstance(None)

# Search

		self.interface.OpenRestartDialog()

# Add before

		if app.ENABLE_PVP_TOURNAMENT:
			if background.GetCurrentMapName() == "metin2_map_pvp_duel":
				return

# Search

		self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.ENABLE_PVP_TOURNAMENT:
			serverCommandList.update({"OpenPvPDuelPanel" : self.interface.OpenPvPDuelPanel})

# Add

	if app.ENABLE_PVP_TOURNAMENT:
		def SetPvPTournamentClear(self, arenaIndex):
			self.interface.SetPvPTournamentClear(int(arenaIndex))
		def SetPvPTournamentStartTime(self, arenaIndex, serverStartTime):
			self.interface.SetPvPTournamentStartTime(int(arenaIndex), int(serverStartTime))
		def SetPvPTournamentRace(self, arenaIndex, playerIndex, playerRace):
			self.interface.SetPvPTournamentRace(int(arenaIndex), int(playerIndex), int(playerRace))
		def SetPvPTournamentScore(self, arenaIndex, playerIndex, playerScore):
			self.interface.SetPvPTournamentScore(int(arenaIndex), int(playerIndex), int(playerScore))
		def SetPvPTournamentName(self, arenaIndex, playerIndex, playerName):
			self.interface.SetPvPTournamentName(int(arenaIndex), int(playerIndex), str(playerName))
		def SetPvPTournamentHP(self, arenaIndex, playerIndex, playerHPPercent, playerMinHP, playerMaxHP, isPoisoned):
			self.interface.SetPvPTournamentHP(int(arenaIndex), int(playerIndex), int(playerHPPercent), int(playerMinHP), int(playerMaxHP), int(isPoisoned))

