# all in "class InventoryWindow(ui.ScriptWindow):"

# search in "def Show(self):"

		ui.ScriptWindow.Show(self)

# add 

		if app.ENABLE_SAVE_LAST_WINDOW_POSITION:
			self.SetLastPosition()

# search "def Destroy(self):" and add on first position

		if app.ENABLE_SAVE_LAST_WINDOW_POSITION:
			if self.IsShow():
				self.SaveLastPosition()
				
# search in"def Close(self):"

		wndMgr.Hide(self.hWnd)

# add before

		if app.ENABLE_SAVE_LAST_WINDOW_POSITION:
			if self.IsShow():
				self.SaveLastPosition()


# add on the end from "class InventoryWindow(ui.ScriptWindow):"

	if app.ENABLE_SAVE_LAST_WINDOW_POSITION:
		import player, wndMgr
		pos_filename = "inventory"
		def SetLastPosition(self):
			file = open("wndconf/" + player.GetName() + "/"+ self.pos_filename + ".pos", 'r')
			line = file.read().split(",")
			pos_x, pos_y = int(line[0]), int(line[1])
			file.close()
			if pos_x > wndMgr.GetScreenWidth() or pos_y > wndMgr.GetScreenHeight():
				return
			if pos_x < 0:
				pos_x = 0
			if pos_y < 0:
				pos_y = 0
			self.SetPosition(pos_x, pos_y);
		
		def SaveLastPosition(self):
			pos_x, pos_y = self.GetGlobalPosition()
			file = open("wndconf/" + player.GetName() + "/"+ self.pos_filename + ".pos","w")
			file.write(str(pos_x)+","+str(pos_y))
			file.close()
			


##############################
# fix for first opening position from "wndEquipmentTypeTab" (like fliege v3 or other i think)

# search in "def Show(self):"

		if self.wndEquipmentTypeTab:
			self.wndEquipmentTypeTab.Show()

# add

			self.wndEquipmentTypeTab.AdjustPosition()