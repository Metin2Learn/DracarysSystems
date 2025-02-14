# Search

		self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.__BACK_DUNGEON__:
			serverCommandList.update({"ReJoinDungeonDialog" : self.ReJoinDungeonDialog})

# Search

	def Close(self):

# add after

		if app.__BACK_DUNGEON__:
			self.__CancelReJoinDungeon()

# Search

		player.SetGameWindow(self)

# Add after

		if app.__BACK_DUNGEON__:
			self.questionReJoinDialogDict = {}

# add

	if app.__BACK_DUNGEON__:
		def ReJoinDungeonDialog(self, mapIdx):
			__mapNames = {
				66 : "Devil Tower",
			}
			mapName = __mapNames[int(mapIdx) / 10000] if __mapNames.has_key(int(mapIdx) / 10000) else "Noname"
			listIdx = len(self.questionReJoinDialogDict)
			questionReJoinDialog = uiCommon.QuestionDialog()
			questionReJoinDialog.SetText("Do you want re-join %s????"%mapName)
			questionReJoinDialog.SetAcceptEvent(lambda idx = int(mapIdx), lIdx = listIdx  : self.__AcceptReJoinDungeon(idx, lIdx))
			questionReJoinDialog.SetCancelEvent(lambda lIdx = listIdx : self.__CancelReJoinDungeon(lIdx))
			questionReJoinDialog.Open()
			self.questionReJoinDialogDict[listIdx] = questionReJoinDialog

		def __AcceptReJoinDungeon(self, mapIdx, listIdx):
			net.SendChatPacket("/back_dungeon {}".format(mapIdx))
			self.__CancelReJoinDungeon(listIdx)

		def __CancelReJoinDungeon(self, idx = -1):
			if idx == -1:
				for key, data in self.questionReJoinDialogDict.items():
					data.SetAcceptEvent(None)
					data.SetCancelEvent(None)
					data.Close()
				self.questionReJoinDialogDict={}
			else:
				if self.questionReJoinDialogDict.has_key(idx):
					self.questionReJoinDialogDict[idx].SetAcceptEvent(None)
					self.questionReJoinDialogDict[idx].SetCancelEvent(None)
					self.questionReJoinDialogDict[idx].Close()
					del self.questionReJoinDialogDict[idx]
