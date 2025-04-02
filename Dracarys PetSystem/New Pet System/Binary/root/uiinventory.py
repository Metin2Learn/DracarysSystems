# Search

		elif item.IsMetin(srcItemVNum):
			if player.ATTACH_METIN_OK == player.CanAttachMetin(srcItemVNum, dstSlotPos):
				return TRUE

# add in function begin

		
		item.SelectItem(player.GetItemIndex(dstSlotPos))
		destItemType = item.GetItemType()
		destItemSubType = item.GetItemSubType()

# Search

		elif item.IsMetin(srcItemVNum):
			if player.ATTACH_METIN_OK == player.CanAttachMetin(srcItemVNum, dstSlotPos):
				return TRUE

# Add after


		elif destItemType == item.ITEM_TYPE_PET and destItemSubType == item.PET_LEVELABLE:
			if srcItemVNum == 55008:
				return TRUE
			elif srcItemVNum == 55001:
				return TRUE
			elif srcItemVNum == 55033:
				return TRUE
			elif srcItemVNum >= 55101 and srcItemVNum <= 55121:
				return TRUE
			elif srcItemVNum >= 55010 and srcItemVNum <= 55031:
				return TRUE

# Search


		elif item.IsMetin(srcItemVID):
			self.AttachMetinToItem(srcItemSlotPos, dstItemSlotPos)

# add in function begin

		item.SelectItem(player.GetItemIndex(dstItemSlotPos))
		destItemType = item.GetItemType()
		destItemSubType = item.GetItemSubType()
		

# Search


		elif item.IsMetin(srcItemVID):
			self.AttachMetinToItem(srcItemSlotPos, dstItemSlotPos)

# Add after

		elif destItemType == item.ITEM_TYPE_PET and destItemSubType == item.PET_LEVELABLE:
			if srcItemVID == 55008:
				self.interface.OpenChangeNameWindow(srcItemSlotPos,dstItemSlotPos,destItemVnum, 1)
			elif srcItemVID == 72325:
				self.DetachMetinFromItem(srcItemSlotPos, dstItemSlotPos)
			elif (srcItemVID == 55001 or srcItemVID == 55033 or (srcItemVID >= 55010 and srcItemVID <= 55031)):
				self.questionDialog = uiCommon.QuestionDialog()
				if 55001 == srcItemVID:
					self.questionDialog.SetText(localeInfo.PET_PROTEIN_QUESTION_TEXT)
				elif 55033 == srcItemVID:
					self.questionDialog.SetText(localeInfo.PET_REMOVE_QUESTION_TEXT)
				else:
					self.questionDialog.SetText(localeInfo.INVENTORY_REALLY_USE_ITEM % item.GetItemName())
				self.questionDialog.SetAcceptEvent(ui.__mem_func__(self.__UseItemToItemQuestionDialog_OnAccept))
				self.questionDialog.SetCancelEvent(ui.__mem_func__(self.__UseItemQuestionDialog_OnCancel))
				self.questionDialog.Open()
				self.questionDialog.srcItemSlotPos = srcItemSlotPos
				self.questionDialog.dstItemSlotPos = dstItemSlotPos
				constInfo.SET_ITEM_QUESTION_DIALOG_STATUS(1)

# Search

		elif item.IsKey(srcItemVNum):
			return TRUE

# Add after

		elif srcItemVNum >= 55701 and srcItemVNum <= 55715:
			return TRUE
		elif srcItemVNum == 55008:
			return TRUE
		elif srcItemVNum == 55001:
			return TRUE
		elif srcItemVNum == 55033:
			return TRUE
		elif srcItemVNum >= 55101 and srcItemVNum <= 55121:
			return TRUE
		elif srcItemVNum >= 55010 and srcItemVNum <= 55031:
			return TRUE

# Add

	def __UseItemToItemQuestionDialog_OnAccept(self):
		self.__SendUseItemToItemPacket(self.questionDialog.srcItemSlotPos,self.questionDialog.dstItemSlotPos)
		self.OnCloseQuestionDialog()

#Search

		self.__SendUseItemPacket(slotIndex)

# Change

		if app.ENABLE_NEW_PET_SYSTEM and itemType == item.ITEM_TYPE_PET and itemSubType == item.PET_EGG:
			self.interface.OpenChangeNameWindow(slotIndex,slotIndex,ItemVNum, 2)
		else:
			self.__SendUseItemPacket(slotIndex)

