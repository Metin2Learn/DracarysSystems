#Imports hinzufügen

if app.ENABLE_ANTI_MULTIPLE_FARM:
	import uiAntiMultipleFarm
	import anti_multiple_farm
	
#In der class Interface(object):
#def __init__(self):
#unter: self.wndGuildBuilding = None

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			self.wndAntiMultipleFarm = None

#In der Funktion: def __MakeTaskBar(self):
#Toggle-Buttons setzen:

		self.wndTaskBar.SetToggleButtonEvent(uiTaskBar.TaskBar.BUTTON_ANTI_MULTIPLE_FARM, ui.__mem_func__(self.ToggleAntiMultipleFarmWindow))
		self.wndTaskBar.SetToggleButtonEvent(uiTaskBar.TaskBar.BUTTON_ANTI_MULTIPLE_FARM_OLD, ui.__mem_func__(self.ToggleAntiMultipleFarmWindow))

#Über der Funktion: def __MakeCubeWindow(self):
#Hinzufügen:

	if app.ENABLE_ANTI_MULTIPLE_FARM:
		def __MakeAntiMultipleFarmWnd(self):
			self.wndAntiMultipleFarm = uiAntiMultipleFarm.AntiMultipleFarmWnd()
			self.wndAntiMultipleFarm.Hide()

#In der Funktion: def MakeInterface(self):
#Hinzufügen:

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			self.__MakeAntiMultipleFarmWnd()

#In der Funktion: def Close(self):
#Hinzufügen:

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			if self.wndAntiMultipleFarm:
				self.wndAntiMultipleFarm.Hide()
				self.wndAntiMultipleFarm.Destroy()

#In der selben Funktion: def Close(self):
#Weiter unten hinzufügen:

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			del self.wndAntiMultipleFarm

#In der Funktion: def HideAllWindows(self):
#Hinzufügen:

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			if self.wndAntiMultipleFarm:
				self.wndAntiMultipleFarm.Hide()

#In der Funktion: def __HideWindows(self):
#Hinzufügen:

		if app.ENABLE_ANTI_MULTIPLE_FARM and self.wndAntiMultipleFarm:
			hideWindows += self.wndAntiMultipleFarm,

#Über: if __name__ == "__main__":
#Hinzufügen:

	if app.ENABLE_ANTI_MULTIPLE_FARM:
		def ToggleAntiMultipleFarmWindow(self):
			if not self.wndAntiMultipleFarm:
				return
			
			if anti_multiple_farm.GetAntiFarmPlayerCount() <= anti_multiple_farm.MULTIPLE_FARM_MAX_ACCOUNT:
				try:
					self.wndPopupDialog.SetText(localeInfo.ANTI_MULTIPLE_FARM_MESSAGE.format(anti_multiple_farm.MULTIPLE_FARM_MAX_ACCOUNT+1))
					self.wndPopupDialog.Open()
				except:
					self.wndPopupDialog = uiCommon.PopupDialog()
					self.wndPopupDialog.SetText(localeInfo.ANTI_MULTIPLE_FARM_MESSAGE.format(anti_multiple_farm.MULTIPLE_FARM_MAX_ACCOUNT+1))
					self.wndPopupDialog.Open()
				return
			
			isShow = self.wndAntiMultipleFarm.IsShow()
			self.wndAntiMultipleFarm.Close() if isShow else self.wndAntiMultipleFarm.Open()
		
		def SendAntiFarmReload(self):
			if self.wndTaskBar:
				self.wndTaskBar.ReloadAntiMultipleFarmState()
			
			if self.wndAntiMultipleFarm.IsShow():
				self.wndAntiMultipleFarm.OnRefreshData()

				if self.wndAntiMultipleFarm.page_manage_mode != self.wndAntiMultipleFarm.VIEW_MODE:
					chat.AppendChat(chat.CHAT_TYPE_INFO, localeInfo.ANTI_MULTIPLE_FARM_REFRESHED)
		
		def RegistItemGive(self, itemVnum, itemCount):
			if not self.wndGiveItem:
				return
			
			self.wndGiveItem.Open(itemVnum, itemCount)
