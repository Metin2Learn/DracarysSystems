#Unter den Imports hinzufügen

if app.ENABLE_ANTI_MULTIPLE_FARM:
	import anti_multiple_farm
	MULTIPLE_FARM_STATE_IMAGES = ["d:/ymir work/ui/pattern/visible_mark_01.tga", "d:/ymir work/ui/pattern/visible_mark_03.tga"]

#In: class TaskBar(ui.ScriptWindow): den Button hinzufügen (achtet auf eure Zahlen!)

	if app.ENABLE_ANTI_MULTIPLE_FARM:
		BUTTON_ANTI_MULTIPLE_FARM = 12

#In: def __init__(self): hinzufügen

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			self.anti_farm_info = None

#In: def LoadWindow(self): hinzufügen
#Unter: toggleButtonDict[TaskBar.BUTTON_SYSTEM] = self.GetChild("SystemButton")

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			pos_x, pos_y = (tuple(x-y for x,y in zip(toggleButtonDict[TaskBar.BUTTON_CHARACTER].GetLocalPosition(), [toggleButtonDict[TaskBar.BUTTON_CHARACTER].GetWidth() + 2, 0])))
			tmpButton = ui.MakeButton(self, pos_x, pos_y, "", "d:/ymir work/ui/anti_multiple_farm/", "anti_multiple_farm_bt_norm.png", "anti_multiple_farm_bt_hover.png", "anti_multiple_farm_bt_down.png")
			toggleButtonDict[TaskBar.BUTTON_ANTI_MULTIPLE_FARM] = tmpButton
			self.anti_farm_info = ui.MakeImageBox(toggleButtonDict[TaskBar.BUTTON_ANTI_MULTIPLE_FARM],\
					"d:/ymir work/ui/pattern/visible_mark_01.tga", -17, 7)

#In: def Destroy(self):
#Unter: self.tooltipEXP = 0

		if app.ENABLE_ANTI_MULTIPLE_FARM:
			self.anti_farm_info = 0

#Am Ende der Datei hinzufügen:

	if app.ENABLE_ANTI_MULTIPLE_FARM:
		def ReloadAntiMultipleFarmState(self):
			if not self.anti_farm_info:
				return
			
			playerState = anti_multiple_farm.GetAntiFarmMainPlayerStatus()
			self.anti_farm_info.LoadImage(MULTIPLE_FARM_STATE_IMAGES[playerState])
