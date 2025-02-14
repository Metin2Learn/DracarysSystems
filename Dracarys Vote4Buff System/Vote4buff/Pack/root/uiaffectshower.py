       //OptimistAdam\\
////---www.metin2hub.com---\\\


##search
	def SetDuration(self, duration):
		self.endTime = 0
		if duration > 0:

##add under
			if app.ENABLE_VOTE_FOR_BONUS and self.affect == chr.AFFECT_VOTEFORBONUS:
				self.endTime = duration

##search
	def SetClock(self, isClocked):
		self.isClocked = isClocked

		def UpdateDescription(self):

##add under
		if not self.isClocked and not (app.ENABLE_VOTE_FOR_BONUS and self.affect == chr.AFFECT_VOTEFORBONUS):
			self.__UpdateDescription2()
			return

		if not self.description and not (app.ENABLE_VOTE_FOR_BONUS and self.affect == chr.AFFECT_VOTEFORBONUS):
			return

##search
	def __init__(self):
		ui.Window.__init__(self)

##add above
	if app.ENABLE_VOTE_FOR_BONUS:
		AFFECT_DATA_DICT[chr.AFFECT_VOTEFORBONUS] = (localeinfo.TOOLTIP_AFFECT_VOTEFORBONUS, "d:/ymir work/ui/pattern/potions/votexbonus.tga")

##search
			value = 1 + float(value) / 100.0

##add under
				if app.ENABLE_VOTE_FOR_BONUS and affect == chr.AFFECT_VOTEFORBONUS:
					duration = duration

