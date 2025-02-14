# Search in Inventory class

	# Search 
	

	def OnMoveWindow(self, x, y):

	# Add in 
	
		if app.__RENEWAL_BRAVE_CAPE__:
			if self.wndBraveCape:
				self.wndBraveCape.AdjustPosition(x, y)

	
	# Search
	
	def ClickCostumeButton(self):

	# Add before
	
	if app.__RENEWAL_BRAVE_CAPE__:
		def ClickBraveCape(self):
			if self.wndBraveCape:
				if self.wndBraveCape.IsShow():
					self.wndBraveCape.Close()
				else:
					self.wndBraveCape.Open()
	
	# Search which one has_key
	
	def Hide(self): or def Close(self):

	# add after

		if app.__RENEWAL_BRAVE_CAPE__:
			if self.wndBraveCape:
				self.wndBraveCape.Close()
	
	# Search
	
		self.ClearDictionary()
	
	# Add after
	
		if app.__RENEWAL_BRAVE_CAPE__:
			if self.wndBraveCape:
				self.wndBraveCape.Destroy()
				self.wndBraveCape = None
	
	# search
	
		self.SetInventoryPage(0)
	
	# Add before
	
		if app.__RENEWAL_BRAVE_CAPE__:
			disbandBtn = ui.Button()
			disbandBtn.SetParent(self)
			disbandBtn.SetPosition(0, 220)
			disbandBtn.SetUpVisual("d:/ymir work/ui/game/belt_inventory/btn_expand_normal.tga")
			disbandBtn.SetOverVisual("d:/ymir work/ui/game/belt_inventory/btn_expand_over.tga")
			disbandBtn.SetDownVisual("d:/ymir work/ui/game/belt_inventory/btn_expand_down.tga")
			disbandBtn.SAFE_SetEvent(self.ClickBraveCape)
			disbandBtn.Show()
			self.disbandBtn = disbandBtn

			self.wndBraveCape = BraveCapeWindow()
			self.OnMoveWindow(*self.GetGlobalPosition())
	
	# Search in init  func
	
		self.wndCostume = None
	
	# Add after
	
		if app.__RENEWAL_BRAVE_CAPE__:
			self.wndBraveCape = None

# add

if app.__RENEWAL_BRAVE_CAPE__:
	import os
	class BraveCapeWindow(ui.Board):
		__children={}
		class SliderBarNew(ui.Window):
			def __init__(self):
				ui.Window.__init__(self)
				self.curPos = 1.0
				self.pageSize = 1.0
				self.eventChange = None
				self.__Load()

			def __Load(self):
				IMG_DIR = "d:/ymir work/ui/game/bravery_cape/"

				img = ui.ImageBox()
				img.SetParent(self)
				img.LoadImage(IMG_DIR+"slider_bg.tga")
				img.Show()
				self.backGroundImage = img

				self.SetSize(self.backGroundImage.GetWidth(), self.backGroundImage.GetHeight())

				cursor = ui.DragButton()
				cursor.AddFlag("movable")
				cursor.AddFlag("restrict_y")
				cursor.SetParent(self)
				cursor.SetMoveEvent(ui.__mem_func__(self.__OnMove))
				cursor.SetUpVisual(IMG_DIR+"drag.tga")
				cursor.SetOverVisual(IMG_DIR+"drag.tga")
				cursor.SetDownVisual(IMG_DIR+"drag.tga")
				cursor.Show()
				self.cursor = cursor

				##
				self.cursor.SetRestrictMovementArea(0, 0, self.backGroundImage.GetWidth(), 0)
				self.pageSize = self.backGroundImage.GetWidth() - self.cursor.GetWidth()

			def __OnMove(self):
				(xLocal, yLocal) = self.cursor.GetLocalPosition()
				self.curPos = float(xLocal) / float(self.pageSize)
				if self.eventChange:
					self.eventChange()
			def SetSliderPos(self, pos):
				self.curPos = pos
				self.cursor.SetPosition(int(self.pageSize * pos), 0)
			def GetSliderPos(self):
				return self.curPos
			def SetEvent(self, event):
				self.eventChange = event
			def Enable(self):
				self.cursor.Show()
			def Disable(self):
				self.cursor.Hide()

		def Destroy(self):
			self.SaveData()
			self.__children={}
		def CreateWindow(self, classPtr, parent, pos):
			window = classPtr
			window.SetParent(parent)
			window.SetPosition(*pos)
			window.Show()
			return window
		def __OverOutItem(self):
			interface = constInfo.GetInterfaceInstance()
			if interface:
				if interface.tooltipItem:
					interface.tooltipItem.HideToolTip()
		def __OverInItem(self, itemIdx):
			interface = constInfo.GetInterfaceInstance()
			if interface:
				if interface.tooltipItem:
					interface.tooltipItem.SetItemToolTip(itemIdx)
		def __init__(self):
			ui.Board.__init__(self)
			self.SetSize(140, 130 + 44)
			self.AddFlag("attach")
			self.AddFlag("float")

			self.__children["firstOpened"] = app.GetGlobalTimeStamp() + 5

			IMG_DIR = "d:/ymir work/ui/game/bravery_cape/"

			BRAVE_CAPE_ITEM_IDX = 20570

			item.SelectItem(BRAVE_CAPE_ITEM_IDX)

			bgImg = self.CreateWindow(ui.ImageBox(), self, (5, 6))
			bgImg.LoadImage(IMG_DIR+"bg.tga")
			self.__children["bgImg"] = bgImg

			timeTextVisual = self.CreateWindow(ui.TextLine(), bgImg, (13, 60))
			timeTextVisual.SetText("Second")
			self.__children["timeTextVisual"] = timeTextVisual

			timeSlider = self.CreateWindow(self.SliderBarNew(), bgImg, (13, 73 + 5))
			timeSlider.SetEvent(ui.__mem_func__(self.OnChangeTimeSlider))
			self.__children["timeSlider"] = timeSlider

			timeBg = self.CreateWindow(ui.ImageBox(), bgImg, (77, 64))
			timeBg.LoadImage(IMG_DIR+"input_output.tga")
			self.__children["timeBg"] = timeBg

			timeText = self.CreateWindow(ui.TextLine(), timeBg, (0, 0))
			timeText.SetAllAlign()
			timeText.SetText("0")
			self.__children["timeText"] = timeText

			rangeTextVisual = self.CreateWindow(ui.TextLine(), bgImg, (13, 73 + 22 + 17 + 5 - 18))
			rangeTextVisual.SetText("Range")
			self.__children["rangeTextVisual"] = rangeTextVisual

			rangeSlider = self.CreateWindow(self.SliderBarNew(), bgImg, (13, 73 + 22 + 17 + 5))
			rangeSlider.SetEvent(ui.__mem_func__(self.OnChangeRangeSlider))
			self.__children["rangeSlider"] = rangeSlider

			rangeBg = self.CreateWindow(ui.ImageBox(), bgImg, (77, 95 + 8))
			rangeBg.LoadImage(IMG_DIR+"input_output.tga")
			self.__children["rangeBg"] = rangeBg

			rangeText = self.CreateWindow(ui.TextLine(), rangeBg, (0, 0))
			rangeText.SetAllAlign()
			rangeText.SetText("0")
			self.__children["rangeText"] = rangeText

			itemIcon = self.CreateWindow(ui.ImageBox(), bgImg, (50, 13))
			itemIcon.LoadImage(item.GetIconImageFileName())
			itemIcon.SAFE_SetStringEvent("MOUSE_OVER_OUT",self.__OverOutItem)
			itemIcon.SAFE_SetStringEvent("MOUSE_OVER_IN",self.__OverInItem, BRAVE_CAPE_ITEM_IDX)
			self.__children["itemIcon"] = itemIcon

			startBtn = self.CreateWindow(ui.Button(), bgImg, (6, 95 + 39))
			startBtn.SetUpVisual(IMG_DIR+"start_btn_0.tga")
			startBtn.SetOverVisual(IMG_DIR+"start_btn_1.tga")
			startBtn.SetDownVisual(IMG_DIR+"start_btn_2.tga")
			startBtn.SetDisableVisual(IMG_DIR+"start_btn_2.tga")
			startBtn.SAFE_SetEvent(self.__ClickStatusBtn, "ACTIVE")
			startBtn.SetText("Start")
			self.__children["startBtn"] = startBtn

			stopBtn = self.CreateWindow(ui.Button(), bgImg, (66, 95 + 39))
			stopBtn.SetUpVisual(IMG_DIR+"start_btn_0.tga")
			stopBtn.SetOverVisual(IMG_DIR+"start_btn_1.tga")
			stopBtn.SetDownVisual(IMG_DIR+"start_btn_2.tga")
			stopBtn.SetDisableVisual(IMG_DIR+"start_btn_2.tga")
			stopBtn.SAFE_SetEvent(self.__ClickStatusBtn, "DEACTIVE")
			stopBtn.SetText("Stop")
			self.__children["stopBtn"] = stopBtn

			expandBtn = self.CreateWindow(ui.Button(), self, (0, 10))
			expandBtn.SetUpVisual("d:/ymir work/ui/game/belt_inventory/btn_minimize_normal.tga")
			expandBtn.SetOverVisual("d:/ymir work/ui/game/belt_inventory/btn_minimize_over.tga")
			expandBtn.SetDownVisual("d:/ymir work/ui/game/belt_inventory/btn_minimize_down.tga")
			expandBtn.SAFE_SetEvent(self.Close)
			self.__children["expandBtn"] = expandBtn

			self.__children["second"] = 0
			self.__children["range"] = 0
			self.__children["status"] = False
			self.Refresh()

		def Refresh(self):
			(second, range, posTime, posSlider) = (self.__children["second"], self.__children["range"], 0.0, 0.0)
			if second > 5800:
				second = 5800
			if range > 14000:
				range = 14000

			self.__children["timeText"].SetText(str((second/100)+2))
			self.__children["rangeText"].SetText(str(range+1000))

			self.__children["timeSlider"].SetSliderPos((1.0/5800.0)*second)
			self.__children["rangeSlider"].SetSliderPos((1.0/14000.0)*range)

			self.__children["second"] = second
			self.__children["range"] = range

		def Open(self):
			interface = constInfo.GetInterfaceInstance()
			if interface:
				if interface.wndInventory:
					interface.wndInventory.disbandBtn.Hide()
			self.Show()

		def Close(self):
			interface = constInfo.GetInterfaceInstance()
			if interface:
				if interface.wndInventory:
					interface.wndInventory.disbandBtn.Show()
			self.Hide()

		def __ClickStatusBtn(self, type):
			if type == "ACTIVE":
				net.SendChatPacket("/brave_cape active {} {}".format((self.__children["second"]/100)+2, self.__children["range"] + 1000))
			elif type == "DEACTIVE":
				net.SendChatPacket("/brave_cape deactive")

		def AdjustPosition(self, x, y):
			self.SetPosition(x + 10 - self.GetWidth(), y + 220)
		def OnChangeRangeSlider(self):
			val = int(((1.0/14000.0)*(self.__children["rangeSlider"].GetSliderPos()*14000))*14000)
			self.__children["range"] = val
			self.Refresh()
		def OnChangeTimeSlider(self):
			val = int(((1.0/5800.0)*(self.__children["timeSlider"].GetSliderPos()*5800))*5800)
			self.__children["second"] = val
			self.Refresh()
		def SetStatus(self, status):
			self.__children["status"] = True if int(status) == 1 else False
			if self.__children["status"]:
				self.__children["startBtn"].Disable()
				self.__children["stopBtn"].Enable()
			else:
				self.__children["stopBtn"].Disable()
				self.__children["startBtn"].Enable()
			self.Refresh()
		def SaveData(self):
			try:
				file = open("lib/{}_brave_cape".format(player.GetName()), "w+")
				file.write("{}#{}#{}\n".format(1 if (self.__children["status"] if self.__children.has_key("status") else False) == True else 0, self.__children["second"], self.__children["range"]))
				file.close()
			except:
				pass
		def LoadData(self):
			try:
				splitList = open("lib/{}_brave_cape".format(player.GetName()), "r").readlines()[0].split("#")
				self.__children["status"] = True if int(splitList[0]) == 1 else False
				self.__children["second"] = int(splitList[1])
				self.__children["range"] = int(splitList[2])
				self.Refresh()
				if self.__children["status"]:
					self.__ClickStatusBtn("ACTIVE")
				os.remove("lib/{}_brave_cape".format(player.GetName()))
			except:
				pass
