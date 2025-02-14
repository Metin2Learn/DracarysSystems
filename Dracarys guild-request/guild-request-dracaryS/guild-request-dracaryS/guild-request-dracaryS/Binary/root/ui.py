# Search

		self.bCodePage = FALSE

# Add after

		if app.ENABLE_GUILD_REQUEST:
			self.infoMsg = ""
			self.backText=None
			self.isNeedEmpty=True

# Search

		self.candidateWindowClassDict = 0

# Add after

		if app.ENABLE_GUILD_REQUEST:
			self.infoMsg = ""
			self.backText=None
			self.isNeedEmpty=False


# Search

	def SetCodePage(self, codePage):
		candidateWindowClass=EditLine.candidateWindowClassDict.get(codePage, EmptyCandidateWindow)
		self.__SetCandidateClass(candidateWindowClass)

# add after

	if app.ENABLE_GUILD_REQUEST:
		def SetInfoMessage(self, msg):
			self.infoMsg = msg
			if self.backText == None:
				self.backText = TextLine()
				self.backText.SetParent(self)
				self.backText.SetPosition(0,0)
				self.backText.SetFontColor(128,128,128)

			self.backText.SetText(msg)

			if self.isNeedEmpty:
				if len(self.GetText()) > 0:
					self.backText.Hide()
				else:
					self.backText.Show()
			else:
				self.backText.Show()


# Search

	def OnIMEUpdate(self):

# Change

	def OnIMEUpdate(self):
		snd.PlaySound("sound/ui/type.wav")
		TextLine.SetText(self, ime.GetText(self.bCodePage))
		
		if app.ENABLE_GUILD_REQUEST:
			if self.backText:
				if self.isNeedEmpty:
					if len(self.GetText()) > 0:
						self.backText.Hide()
					else:
						self.backText.Show()
				else:
					self.backText.Show()



if app.ENABLE_GUILD_REQUEST:
	class MouseReflector(Window):
		def __init__(self, parent):
			Window.__init__(self)
			self.SetParent(parent)
			self.AddFlag("not_pick")
			self.width = self.height = 0
			self.isDown = False
		def __del__(self):
			Window.__del__(self)
		def Down(self):
			self.isDown = True
		def Up(self):
			self.isDown = False
		def OnRender(self):
			if self.isDown:
				grp.SetColor(WHITE_COLOR)
			else:
				grp.SetColor(HALF_WHITE_COLOR)
			x, y = self.GetGlobalPosition()
			grp.RenderBar(x + 2, y + 2, self.GetWidth() - 4, self.GetHeight() - 4)
	class CheckBoxNew(ImageBox):
		def __init__(self, parent, x, y, event, filename = "d:/ymir work/ui/chat/chattingoption_check_box_off.sub"):
			ImageBox.__init__(self)
			self.SetParent(parent)
			self.SetPosition(x, y)
			self.LoadImage(filename)
			self.mouseReflector = MouseReflector(self)
			self.mouseReflector.SetSize(self.GetWidth(), self.GetHeight())
			image = MakeImageBox(self, "d:/ymir work/ui/public/check_image.sub", 0, 0)
			image.AddFlag("not_pick")
			image.SetWindowHorizontalAlignCenter()
			image.SetWindowVerticalAlignCenter()
			image.Hide()
			self.check = False
			self.enable = True
			self.image = image
			self.event = event
			self.Show()
			self.mouseReflector.UpdateRect()
		def __del__(self):
			ImageBox.__del__(self)
		def GetCheck(self):
			return self.check
		def SetCheck(self, flag):
			if flag:
				self.check = True
				self.image.Show()
			else:
				self.check = False
				self.image.Hide()
		def Disable(self):
			self.enable = False
		def OnMouseOverIn(self):
			if not self.enable:
				return
			self.mouseReflector.Show()
		def OnMouseOverOut(self):
			if not self.enable:
				return
			self.mouseReflector.Hide()
		def OnMouseLeftButtonDown(self):
			if not self.enable:
				return
			self.mouseReflector.Down()
		def OnMouseLeftButtonUp(self):
			if not self.enable:
				return
			self.mouseReflector.Up()
			self.event()