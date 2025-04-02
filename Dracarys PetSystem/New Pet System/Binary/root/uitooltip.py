
#Search this function.

	def AddItemData(self, itemVnum, metinSlot, attrSlot = 0, flags = 0, unbindTime = 0, IsSearchShop = 0, window_type = player.INVENTORY, slotIndex = -1, IsSwitchbot = 0, transmutation = -1):

# Add in parameter newname "^"

	def AddItemData(self, itemVnum, metinSlot, attrSlot = 0, flags = 0, unbindTime = 0, IsSearchShop = 0, window_type = player.INVENTORY, slotIndex = -1, IsSwitchbot = 0, transmutation = -1, newname = "^"):



# Search

	NEED_SKILL_POINT_COLOR = 0xff9A9CDB

# Add after

	if app.ENABLE_NEW_NAME_ITEM:
		TYRANIS_TOOLTIP_COLOR = 0xff5FFFF3
		CHANGELOOK_ITEMNAME_COLOR = 0xffBCE55C
		RENDER_TARGET = 0xff90ee90


# What is ...PARAMETER... ?

# Example:

	# This your define.

	def AddItemData(self, itemVnum, metinSlot, attrSlot = 0, flags = 0, unbindTime = 0, IsSearchShop = 0, window_type = player.INVENTORY, slotIndex = -1, IsSwitchbot = 0, transmutation = -1):

	# How can u use this?
	
	self.AddItemData(itemVnum, metinSlot, attrSlot, 0, 0, 0, player.INVENTORY, -1, 0, -1)

	# Why we use like this.
	#Because newname parameter in the end.
	self.AddItemData(itemVnum, metinSlot, attrSlot, 0, 0, 0, player.INVENTORY, -1, 0, -1, newname) # like this.

# Search

	def SetSafeBoxItem(self, slotIndex):

# Search in

	self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetItemFlags(slotIndex))

# Change

	if app.ENABLE_PERMA_ITEM:
		newname = safebox.GetItemNewName(slotIndex)
		if not newname:
			newname = "^"
		self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetItemFlags(slotIndex),...PARAMETER..., newname)
	else:
		self.AddItemData(itemVnum, metinSlot, attrSlot, safebox.GetItemFlags(slotIndex))

# Search

	def SetExchangeTargetItem(self, slotIndex):

# Search in

	self.AddItemData(itemVnum, metinSlot, attrSlot)

# Change

	if app.ENABLE_NEW_NAME_ITEM:
		newname = exchange.GetItemNewName(slotIndex,False)
		if not newname:
			newname = "^"
		self.AddItemData(itemVnum, metinSlot, attrSlot, ..PARAMETER..., newname)
	else:
		self.AddItemData(itemVnum, metinSlot, attrSlot)


# Search

	def SetExchangeOwnerItem(self, slotIndex):

# Search in

	self.AddItemData(itemVnum, metinSlot, attrSlot)

# Change

		if app.ENABLE_NEW_NAME_ITEM:
			newname = exchange.GetItemNewName(slotIndex,True)
			if not newname:
				newname = "^"
			self.AddItemData(itemVnum, metinSlot, attrSlot, ...PARAMETER..., newname)
		else:
			self.AddItemData(itemVnum, metinSlot, attrSlot)


		self.__SetItemTitle(itemVnum, metinSlot, attrSlot)

# Change

		if app.ENABLE_NEW_NAME_ITEM:
			self.__SetItemTitle(itemVnum, metinSlot, attrSlot, window_type, slotIndex, newname)
		else:
			self.__SetItemTitle(itemVnum, metinSlot, attrSlot)


# Search

	def __SetItemTitle(self, itemVnum, metinSlot, attrSlot):
			if self.__IsPolymorphItem(itemVnum):
				self.__SetPolymorphItemTitle(metinSlot[0])
			else:
				if self.__IsAttr(attrSlot):
					self.__SetSpecialItemTitle()
					return
				self.__SetNormalItemTitle()
		def __SetNormalItemTitle(self):
			if app.ENABLE_TARGET_INFO:
				if self.isStone:
					itemName = item.GetItemName()
					realName = itemName[:itemName.find("+")]
					self.SetTitle(realName + " +0 - +4")
				else:
					self.SetTitle(item.GetItemName())
			else:
				self.SetTitle(item.GetItemName())
		def __SetSpecialItemTitle(self):
			self.AppendTextLine(item.GetItemName(), self.SPECIAL_TITLE_COLOR)

# Change

	if app.ENABLE_NEW_NAME_ITEM:
		def __SetItemTitle(self, itemVnum, metinSlot, attrSlot, window_type, slotIndex, newname):
			if self.__IsPolymorphItem(itemVnum):
				self.__SetPolymorphItemTitle(metinSlot[0])
			else:
				if newname == "^" and slotIndex >= 0:
					if window_type == player.INVENTORY:
						newname = player.GetItemNewName(window_type, slotIndex)
					elif window_type == player.SAFEBOX:
						newname = safebox.GetItemNewName(slotIndex)
					elif window_type == player.MALL:
						newname = safebox.GetItemNewName(slotIndex)
				if self.__IsAttr(attrSlot):
					self.__SetSpecialItemTitle(newname)
					return
				self.__SetNormalItemTitle(newname)
		def __SetNormalItemTitle(self, newname):
			if app.ENABLE_TARGET_INFO:
				if self.isStone:
					itemName = item.GetItemName()
					realName = itemName[:itemName.find("+")]
					self.SetTitle(realName + " +0 - +4")
				else:
					if newname != "^":
						self.SetTitle(newname)
					else:
						self.SetTitle(item.GetItemName())
			else:
				self.SetTitle(item.GetItemName())
		def __SetSpecialItemTitle(self, newname):
			if newname != "^":
				self.AppendTextLine(newname, self.SPECIAL_TITLE_COLOR)
			else:
				self.AppendTextLine(item.GetItemName(), self.SPECIAL_TITLE_COLOR)
	else:
		def __SetItemTitle(self, itemVnum, metinSlot, attrSlot):
			if self.__IsPolymorphItem(itemVnum):
				self.__SetPolymorphItemTitle(metinSlot[0])
			else:
				if self.__IsAttr(attrSlot):
					self.__SetSpecialItemTitle()
					return
				self.__SetNormalItemTitle()
		def __SetNormalItemTitle(self):
			if app.ENABLE_TARGET_INFO:
				if self.isStone:
					itemName = item.GetItemName()
					realName = itemName[:itemName.find("+")]
					self.SetTitle(realName + " +0 - +4")
				else:
					self.SetTitle(item.GetItemName())
			else:
				self.SetTitle(item.GetItemName())
		def __SetSpecialItemTitle(self):
			self.AppendTextLine(item.GetItemName(), self.SPECIAL_TITLE_COLOR)

# Search

	self.AppendDescription(itemSummary, 26, self.CONDITION_COLOR)

# Add after

		if app.ENABLE_NEW_PET_SYSTEM:
			if item.ITEM_TYPE_PET == itemType:
				if itemSubType == item.PET_LEVELABLE:
					level = metinSlot[1]
					if level > 0:
						curPoint = metinSlot[2]
						if level >= 120:
							maxPoint = 2500000000
						else:
							maxPoint = constInfo.exp_table[level]
						curPoint = min(curPoint, maxPoint)
						curPoint = max(curPoint, 0)
						maxPoint = max(maxPoint, 0)

						self.AppendTextLine("Lv. %d"%level,self.SPECIAL_POSITIVE_COLOR)
						age_text = [localeInfo.PET_GUI_YOUNG, localeInfo.PET_GUI_WILD, localeInfo.PET_GUI_BRAVE, localeInfo.PET_GUI_HERO]
						self.AppendTextLine("%s : %s"%(localeInfo.PET_GUI_AGE,age_text[metinSlot[3]]),self.SPECIAL_POSITIVE_COLOR)
						self.AppendTextLine("%s : %.2f%%" % (localeInfo.TASKBAR_EXP, float(curPoint) / max(1, float(maxPoint)) * 100),self.SPECIAL_POSITIVE_COLOR)

						self.AppendSpace(5)

						pet_bonus_types=[item.APPLY_MAX_HP,item.APPLY_ATTBONUS_MONSTER,item.APPLY_CRITICAL_PCT]
						pet_bonus_value=[4000,20,10]
						for j in xrange(3):
							ptr = metinSlot[5+j]
							if ptr == 20:
								bonus_value = pet_bonus_value[j]
							else:
								bonus_value = float(float(pet_bonus_value[j])/20.0) * ptr

							text = self.__GetAffectString(pet_bonus_types[j],int(bonus_value))
							if text != None:
								text = text.replace(":","")
								index = text.find("+")
								if index == -1:
									index = text.find("%")
									if index == -1:
										index =0
								if not index  <= 0:
									new_text = text[:index]
									new_text += " (Lv %d  -  %s)"%(ptr,text[index:])
									self.AppendTextLine(new_text,self.TYRANIS_TOOLTIP_COLOR)
								else:
									new_text = text
									new_text += " (Lv %d  -  +%d)"%(ptr,int(bonus_value))
									self.AppendTextLine(new_text,self.TYRANIS_TOOLTIP_COLOR)

						self.AppendSpace(5)
						for j in xrange(len(attrSlot)):
							if attrSlot[j][0] == 0 or attrSlot[j][0] == 99:
								continue
							self.AppendTextLine(constInfo.pet_skill_data[attrSlot[j][0]][0]+"(Lv"+str(attrSlot[j][1])+")",self.SPECIAL_TITLE_COLOR)

						self.AppendSpace(5)
						self.AppendTextLine(localeInfo.LEFT_TIME+ ": "+localeInfo.SecondToDHM(metinSlot[0]-app.GetGlobalTimeStamp()),self.SPECIAL_POSITIVE_COLOR)

						# if have transmutation !!!!!!!!!!!!!!!!!
						self.AppendSpace(5)
						self.AppendTransmutationEx(window_type, slotIndex, transmutation) #if have transmutation...


# Search

class HyperlinkItemToolTip(ItemToolTip):

# Change

# Check your hyperlink algorithm with yours...


class HyperlinkItemToolTip(ItemToolTip):
	def __init__(self):
		ItemToolTip.__init__(self, isPickable=TRUE)
	def SetHyperlinkItem(self, tokens):
		defaultTokenCount = 4 #head, vnum, flag, newname

		minTokenCount = defaultTokenCount + player.METIN_SOCKET_MAX_NUM
		maxTokenCount = minTokenCount + 2 * player.ATTRIBUTE_SLOT_MAX_NUM

		if tokens and len(tokens) >= minTokenCount and len(tokens) <= maxTokenCount:
			head, vnum, flag, newname  = tokens[:defaultTokenCount]
			newname = str(newname)
			itemVnum = int(vnum, 16)
			metinSlot = [int(metin, 16) for metin in tokens[defaultTokenCount:defaultTokenCount+player.METIN_SOCKET_MAX_NUM]]
			rests = tokens[defaultTokenCount+player.METIN_SOCKET_MAX_NUM:]
			if rests:
				attrSlot = []
				rests.reverse()
				while rests:
					key = int(rests.pop(), 16)
					if rests:
						val = int(rests.pop())
						attrSlot.append((key, val))
				attrSlot += [(0, 0)] * (player.ATTRIBUTE_SLOT_MAX_NUM - len(attrSlot))
			else:
				attrSlot = [(0, 0)] * player.ATTRIBUTE_SLOT_MAX_NUM
			self.ClearToolTip()
			self.AddItemData(itemVnum, metinSlot, attrSlot)
			ItemToolTip.OnUpdate(self)

	def OnUpdate(self):
		pass

	def OnMouseLeftButtonDown(self):
		self.Hide()



