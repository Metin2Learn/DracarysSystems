
# Search

	self.interface = interfaceModule.Interface()

# Add after

	if app.ENABLE_NEW_PET_SYSTEM:
		constInfo.SetInterfaceInstance(self.interface)

# Search

	self.KillFocus()

# Add after

	if app.ENABLE_NEW_PET_SYSTEM:
		constInfo.SetInterfaceInstance(None)

# Search

		onPressKeyDict[app.DIK_P]			= self.__PressPKey

# change

		if app.ENABLE_NEW_PET_SYSTEM:
			onPressKeyDict[app.DIK_P]	= lambda : self.PetOpenWindow()

# Search

	self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.ENABLE_NEW_PET_SYSTEM:
			serverCommandList.update({"PetSetSlotIndex" : self.PetSetSlotIndex})
			serverCommandList.update({"PetClearData" : self.PetClearData})
			serverCommandList.update({"UpdatePet" : self.PetUpdate})

# Add

	if app.ENABLE_NEW_PET_SYSTEM:
		def PetSetSlotIndex(self, index):
			self.interface.SetPetSlotIndex(index)
		def PetClearData(self):
			self.interface.ClearPetData()
		def PetOpenWindow(self):
			self.interface.OpenPetWindow()
		def PetUpdate(self, index):
			self.interface.PetUpdate(int(index))
