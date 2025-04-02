# Add


if app.ENABLE_NEW_PET_SYSTEM:
	import uiPetSystem
	import uiChangeName


# Search

		self.wndItemSelect=None

# Add after


		if app.ENABLE_NEW_PET_SYSTEM:
			self.wndPet=None
			self.change_window=None


# Search

	def Close(self):

# Add after


		if app.ENABLE_NEW_PET_SYSTEM:
			if self.wndPet:
				self.wndPet.Destroy()
				self.wndPet.Hide()
				del self.wndPet
				self.wndPet = None
			
			if self.change_window:
				self.change_window.Hide()
				self.change_window.Destroy()
				del self.change_window
				self.change_window = None

# Add


	if app.ENABLE_NEW_PET_SYSTEM:
		def MakeChangeNameWindow(self):
			self.change_window = uiChangeName.NameInputWindow()

		def OpenChangeNameWindow(self, srcitemPos, destitemPos, itemVnum, type = False):
			if self.change_window == None:
				self.MakeChangeNameWindow()
			self.change_window.LoadItemData(srcitemPos,destitemPos, itemVnum, type)
			self.change_window.Show()
			self.change_window.SetTop()
		def MakePetWindow(self):
			self.wndPet = uiPetSystem.PetSystemMain()
			self.wndPet.Hide()

		def ClearPetData(self):
			if self.wndPet == None:
				return
			self.wndPet.ClearData()

		def SetPetSlotIndex(self, index):
			if self.wndPet == None:
				self.MakePetWindow()
			self.wndPet.SetSlotIndex(index)

			if self.wndPet.IsShow():
				self.wndPet.Open()

		def PetUpdate(self, index):
			if self.wndPet == None:
				return
			if index == 0:
				self.wndPet.UpdateTime()
			elif index == 1:
				self.wndPet.UpdateLevel()
				self.wndPet.CheckEvolveFlash()
				self.wndPet.CheckFeedWindow()
			elif index == 2:
				self.wndPet.UpdateExp()
			elif index == 3:
				self.wndPet.UpdateAge()
				self.wndPet.CheckEvolveFlash()
				self.wndPet.CheckFeedWindow()
				self.wndPet.UpdateSkill()
			elif index >= 5 and index <= 7:
				self.wndPet.UpdateBonus()
			elif ((index >= 100 and index <= 114) or (index >= 150 and index <= 164)):
				self.wndPet.UpdateSkill()

		def OpenPetWindow(self):
			if self.wndPet == None:
				self.MakePetWindow()
			if self.wndPet.IsShow():
				self.wndPet.Hide()
			else:
				self.wndPet.Open()
