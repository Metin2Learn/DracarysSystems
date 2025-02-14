# Search

		if chr.NEW_AFFECT_DRAGON_SOUL_DECK1 == type or chr.NEW_AFFECT_DRAGON_SOUL_DECK2 == type:
			self.interface.DragonSoulActivate(type - chr.NEW_AFFECT_DRAGON_SOUL_DECK1)

# Add after

		if app.__RENEWAL_BRAVE_CAPE__:
			if type == chr.NEW_AFFECT_BRAVE_CAPE:
				if self.interface:
					if self.interface.wndInventory:
						if self.interface.wndInventory.wndBraveCape:
							self.interface.wndInventory.wndBraveCape.LoadData()

# Search

		self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.__RENEWAL_BRAVE_CAPE__:
			serverCommandList.update({"SetBraveCapeStatus" : self.SetBraveCapeStatus})

# Add

	if app.__RENEWAL_BRAVE_CAPE__:
		def SetBraveCapeStatus(self, status):
			if self.interface:
				if self.interface.wndInventory:
					if self.interface.wndInventory.wndBraveCape:
						self.interface.wndInventory.wndBraveCape.SetStatus(status)

