# Search

		self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.ENABLE_GUILD_REQUEST:
			serverCommandList.update({"OpenGuildRequest" : self.interface.OpenGuildRequest})

# Add

	if app.ENABLE_GUILD_REQUEST:
		def GuildRequestLoadName(self, tabIndex):
			self.interface.GuildRequestLoadName(int(tabIndex))
		def GuildRequestLoadPage(self, tabIndex, pageIndex, maxPage):
			self.interface.GuildRequestLoadPage(int(tabIndex), int(pageIndex), int(maxPage))
		def GuildRequestSetItem(self, index, g_id, name, level, ladder_point, membercount, maxmember, isRequest):
			self.interface.GuildRequestSetItem(int(index), int(g_id), str(name), int(level), int(ladder_point), int(membercount), int(maxmember), int(isRequest))
		def GuildRequestSetRequest(self, index, pid, name, level, race, skillIndex):
			self.interface.GuildRequestSetRequest(int(index), int(pid), str(name), int(level), int(race), int(skillIndex))

# Search

		self.interface = interfaceModule.Interface()

# Add after

		if app.ENABLE_GUILD_REQUEST:
			constInfo.SetInterfaceInstance(self.interface)

# Search

		self.KillFocus()

# Add after

		if app.ENABLE_GUILD_REQUEST:
			constInfo.SetInterfaceInstance(None)
