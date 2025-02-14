# Add

if app.__RENEWAL_NOTICE__:
	class TipBoardNew(ui.ThinBoard):
		def __del__(self):
			ui.ThinBoard.__del__(self)
		def Destroy(self):
			self.__tipList=[]
			self.__min_width=0
			self.__max_duration=0.0
			self.__process_duration=0.0
			self.__text_duration=0.0
			self.__sleepTime=0.0
			self.__currentTip=""
			self.__textBar=None
			self.processType = False
			self.__open_max_duration =  0.0
			self.__open_text_duration =  0.0
			self.__close_max_duration =  0.0
			self.__close_text_duration =  0.0
			self.__click_close_max_duration =  0.0
			self.__click_close_text_duration = 0.0
		def __init__(self):
			ui.ThinBoard.__init__(self)
			self.SetWindowHorizontalAlignCenter()
			self.Destroy()

			# config
			self.__min_width=40
			self.__min_height=30
			self.__yPos=70

			self.processType = True

			self.__open_max_duration = 5.0
			self.__open_text_duration = 0.30

			self.__close_max_duration = 1.0
			self.__close_text_duration = 0.1

			self.__click_close_max_duration = 0.7
			self.__click_close_text_duration = 0.05

			textBar = ui.TextLine()
			textBar.SetParent(self)
			textBar.AddFlag("not_pick")
			textBar.SetOutline()
			textBar.SetHorizontalAlignCenter()
			textBar.SetVerticalAlignCenter()
			textBar.SetWindowHorizontalAlignCenter()
			textBar.SetWindowVerticalAlignCenter()
			self.__textBar = textBar

			self.AddFlag("attach")
			self.AddFlag("movable")
			self.AddFlag("float")
			self.SetMouseOverInEvent(ui.__mem_func__(self.OnMouseOverIn))
			self.SetMouseOverOutEvent(ui.__mem_func__(self.OnMouseOverOut))
			self.SetMouseLeftButtonUpEvent(ui.__mem_func__(self.OnMouseClick))
		def OnMouseClick(self):
			self.processType = False
			self.__process_duration = app.GetTime()+self.__click_close_max_duration
			self.__text_duration = (self.__click_close_text_duration/(len(self.__currentTip)))
		def SetYPos(self, globalY):
			self.__yPos = globalY
		def OnMouseOverIn(self):
			self.SetAlpha(0.5)
		def OnMouseOverOut(self):
			self.SetAlpha(1.0)
		def SetDefaultData(self):
			self.__sleepTime = 0.0
			self.__text_duration = 0.0
			self.__process_text = 0.0
			self.__process_duration = 0.0
			self.__currentTip = ""
		def SetNewTipHideData(self):
			self.__process_text = 0.0
			self.__process_duration = app.GetTime()+self.__close_max_duration
			self.__text_duration = (self.__close_text_duration/(len(self.__currentTip)))
			self.processType = False
		def SetNewTipOpenData(self, tipMessage):
			self.__textBar.SetText("")
			self.__process_text = 0.0
			self.__process_duration = app.GetTime()+self.__open_max_duration
			self.__currentTip = tipMessage
			self.__text_duration = (self.__open_text_duration/(len(self.__currentTip)))
			self.processType = True
			self.SetPosition(0, self.__yPos)
			if not self.__textBar.IsShow():
				self.__textBar.Show()
				self.__textBar.SetTop()
				self.SetSize(self.__min_width+self.__textBar.GetTextSize()[0],self.__min_height)
				self.SetPosition(0, self.__yPos)
		def SetTip(self, newTip):
			if self.__process_duration != 0.0:
				self.__tipList.append(newTip)
				return
			self.__sleepTime = app.GetTime()+0.5
			self.__alpha_duration = 0.0
			self.__alphaValue = 0.0
			self.__alpha = 0.5/30.0
			self.SetNewTipOpenData(newTip)
			self.Show()
		def OnUpdate(self):
			if self.__sleepTime >= app.GetTime():
				if app.GetTime() >= self.__alpha_duration:
					self.__alphaValue += self.__alpha
					self.__alpha_duration = app.GetTime()+0.01
					if self.processType:
						self.SetAlpha(0.5+self.__alphaValue)
					else:
						self.SetAlpha(1.0-self.__alphaValue)
				return
			if self.__process_duration != 0:
				lastDuration = self.__process_duration-app.GetTime()
				if self.processType:
					if app.GetTime() > self.__process_text:
						self.__process_text = app.GetTime()+self.__text_duration
						nextChar = len(self.__textBar.GetText())
						if nextChar < len(self.__currentTip):
							self.__textBar.SetText(self.__textBar.GetText()+self.__currentTip[nextChar])
						if lastDuration <= 0.0:
							self.SetNewTipHideData()
				else:
					if app.GetTime() > self.__process_text:
						self.__process_text = app.GetTime()+self.__text_duration
						nextChar = len(self.__textBar.GetText())
						if nextChar > 0:
							self.__textBar.SetText(self.__textBar.GetText()[:nextChar-1])

							if len(self.__textBar.GetText()) == 0:
								if len(self.__tipList) > 0:
									lastDuration = 0
								else:
									self.__sleepTime = app.GetTime()+0.5
									self.__alpha_duration = 0.0
									self.__alphaValue = 0.0
									self.__alpha = 0.5/30.0
						else:
							lastDuration = 0.0
					if lastDuration <= 0.0:
						if len(self.__tipList)>0:
							self.SetNewTipOpenData(self.__tipList[0])
							del self.__tipList[0]
							return
						self.SetDefaultData()
						self.Hide()
				self.SetSize(self.__min_width+self.__textBar.GetTextSize()[0],self.__min_height)
				self.SetPosition(0, self.__yPos)

# in case of float div zero error

if app.__RENEWAL_NOTICE__:
	class TipBoardNew(ui.ThinBoard):
		def __del__(self):
			ui.ThinBoard.__del__(self)
		def Destroy(self):
			self.__tipList=[]
			self.__min_width=0
			self.__max_duration=0.0
			self.__process_duration=0.0
			self.__text_duration=0.0
			self.__sleepTime=0.0
			self.__currentTip=""
			self.__textBar=None
			self.processType = False
			self.__open_max_duration =  0.0
			self.__open_text_duration =  0.0
			self.__close_max_duration =  0.0
			self.__close_text_duration =  0.0
			self.__click_close_max_duration =  0.0
			self.__click_close_text_duration = 0.0
		def __init__(self):
			ui.ThinBoard.__init__(self)
			self.SetWindowHorizontalAlignCenter()
			self.Destroy()

			# config
			self.__min_width=40
			self.__min_height=30
			self.__yPos=70

			self.processType = True

			self.__open_max_duration = 5.0
			self.__open_text_duration = 0.30

			self.__close_max_duration = 1.0
			self.__close_text_duration = 0.1

			self.__click_close_max_duration = 0.7
			self.__click_close_text_duration = 0.05

			textBar = ui.TextLine()
			textBar.SetParent(self)
			textBar.AddFlag("not_pick")
			textBar.SetOutline()
			textBar.SetHorizontalAlignCenter()
			textBar.SetVerticalAlignCenter()
			textBar.SetWindowHorizontalAlignCenter()
			textBar.SetWindowVerticalAlignCenter()
			self.__textBar = textBar

			self.AddFlag("attach")
			self.AddFlag("movable")
			self.AddFlag("float")
			self.SetMouseOverInEvent(ui.__mem_func__(self.OnMouseOverIn))
			self.SetMouseOverOutEvent(ui.__mem_func__(self.OnMouseOverOut))
			self.SetMouseLeftButtonUpEvent(ui.__mem_func__(self.OnMouseClick))
		def OnMouseClick(self):
			self.processType = False
			self.__process_duration = app.GetTime()+self.__click_close_max_duration
			self.__text_duration = (self.__click_close_text_duration/(len(self.__currentTip)))
		def SetYPos(self, globalY):
			self.__yPos = globalY
		def OnMouseOverIn(self):
			self.SetAlpha(0.5)
		def OnMouseOverOut(self):
			self.SetAlpha(1.0)
		def SetDefaultData(self):
			self.__sleepTime = 0.0
			self.__text_duration = 0.0
			self.__process_text = 0.0
			self.__process_duration = 0.0
			self.__currentTip = ""
		def SetNewTipHideData(self):
			self.__process_text = 0.0
			self.__process_duration = app.GetTime()+self.__close_max_duration
			self.__text_duration = (self.__close_text_duration/(len(self.__currentTip)))
			self.processType = False
		def SetNewTipOpenData(self, tipMessage):
			if not len(tipMessage):
				return
			self.__textBar.SetText("")
			self.__process_text = 0.0
			self.__process_duration = app.GetTime()+self.__open_max_duration
			self.__currentTip = tipMessage
			self.__text_duration = (self.__open_text_duration/(len(self.__currentTip)))
			self.processType = True
			self.SetPosition(0, self.__yPos)
			if not self.__textBar.IsShow():
				self.__textBar.Show()
				self.__textBar.SetTop()
				self.SetSize(self.__min_width+self.__textBar.GetTextSize()[0],self.__min_height)
				self.SetPosition(0, self.__yPos)
		def SetTip(self, newTip):
			if self.__process_duration != 0.0:
				self.__tipList.append(newTip)
				return
			self.__sleepTime = app.GetTime()+0.5
			self.__alpha_duration = 0.0
			self.__alphaValue = 0.0
			self.__alpha = 0.5/30.0
			self.SetNewTipOpenData(newTip)
			self.Show()
		def OnUpdate(self):
			if self.__sleepTime >= app.GetTime():
				if app.GetTime() >= self.__alpha_duration:
					self.__alphaValue += self.__alpha
					self.__alpha_duration = app.GetTime()+0.01
					if self.processType:
						self.SetAlpha(0.5+self.__alphaValue)
					else:
						self.SetAlpha(1.0-self.__alphaValue)
				return
			if self.__process_duration != 0:
				lastDuration = self.__process_duration-app.GetTime()
				if self.processType:
					if app.GetTime() > self.__process_text:
						self.__process_text = app.GetTime()+self.__text_duration
						nextChar = len(self.__textBar.GetText())
						if nextChar < len(self.__currentTip):
							self.__textBar.SetText(self.__textBar.GetText()+self.__currentTip[nextChar])
						if lastDuration <= 0.0:
							self.SetNewTipHideData()
				else:
					if app.GetTime() > self.__process_text:
						self.__process_text = app.GetTime()+self.__text_duration
						nextChar = len(self.__textBar.GetText())
						if nextChar > 0:
							self.__textBar.SetText(self.__textBar.GetText()[:nextChar-1])

							if len(self.__textBar.GetText()) == 0:
								if len(self.__tipList) > 0:
									lastDuration = 0
								else:
									self.__sleepTime = app.GetTime()+0.5
									self.__alpha_duration = 0.0
									self.__alphaValue = 0.0
									self.__alpha = 0.5/30.0
						else:
							lastDuration = 0.0
					if lastDuration <= 0.0:
						if len(self.__tipList)>0:
							self.SetNewTipOpenData(self.__tipList[0])
							del self.__tipList[0]
							return
						self.SetDefaultData()
						self.Hide()
				self.SetSize(self.__min_width+self.__textBar.GetTextSize()[0],self.__min_height)
				self.SetPosition(0, self.__yPos)
