#Search

	AFFECT_DATA_DICT =	{
	...
	}

# Add after

	if app.RENEWAL_PICKUP_AFFECT:
		AFFECT_DATA_DICT[chr.NEW_AFFECT_PICKUP_ENABLE] =  (localeInfo.NEW_AFFECT_PICKUP_ENABLE, "icon/affectshower/pickup_active.tga")
		AFFECT_DATA_DICT[chr.NEW_AFFECT_PICKUP_DEACTIVE] =  (localeInfo.NEW_AFFECT_PICKUP_DEACTIVE, "icon/affectshower/pickup_deactive.tga")

# Search

	INFINITE_AFFECT_DURATION = 0x1FFFFFFF

#Add after

	if app.RENEWAL_PICKUP_AFFECT:
		pickupQuestionDialog = None

#Seach

		if affect != chr.NEW_AFFECT_AUTO_SP_RECOVERY and affect != chr.NEW_AFFECT_AUTO_HP_RECOVERY:
			description = description(float(value))

# Add after

		if app.RENEWAL_PICKUP_AFFECT:
			if affect == chr.NEW_AFFECT_PICKUP_ENABLE or affect == chr.NEW_AFFECT_PICKUP_DEACTIVE:
				image.SetEvent(ui.__mem_func__(self.__OnClickPickup),"mouse_click", affect)

# Search

	def BINARY_NEW_RemoveAffect(self, type, pointIdx):

# add before

	if app.RENEWAL_PICKUP_AFFECT:
		def OnChangePickup(self, answer):
			if not self.pickupQuestionDialog:
				return
			if answer:
				net.SendChatPacket("/pickup_affect")
			self.pickupQuestionDialog.Close()
			self.pickupQuestionDialog = None
		def __OnClickPickup(self, emptyArg, affect):
			if self.pickupQuestionDialog:
				self.pickupQuestionDialog.Close()
			pickupQuestionDialog = uiCommon.QuestionDialog()
			pickupQuestionDialog.SetText(localeInfo.PICKUP_DEACTIVE_DIALOG if chr.NEW_AFFECT_PICKUP_ENABLE else localeInfo.PICKUP_ACTIVE_DIALOG)
			pickupQuestionDialog.SetAcceptEvent(lambda arg = True: self.OnChangePickup(arg))
			pickupQuestionDialog.SetCancelEvent(lambda arg = False: self.OnChangePickup(arg))
			pickupQuestionDialog.Open()
			self.pickupQuestionDialog = pickupQuestionDialog

