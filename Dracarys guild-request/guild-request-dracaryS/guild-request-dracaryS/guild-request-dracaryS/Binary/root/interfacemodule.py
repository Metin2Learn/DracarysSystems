# Add

if app.ENABLE_GUILD_REQUEST:
	import uiGuildRequest


# Search

		systemSetting.SetInterfaceHandler(self)

# Add after

		if app.ENABLE_GUILD_REQUEST:
			self.wndGuildRequest = None

# Search

	def Close(self):


# Add after

		if app.ENABLE_GUILD_REQUEST:
			if self.wndGuildRequest:
				self.wndGuildRequest.Hide()
				self.wndGuildRequest.Destroy()
				self.wndGuildRequest = None

# Add

	if app.ENABLE_GUILD_REQUEST:
		def MakeGuildRequest(self):
			if self.wndGuildRequest == None:
				self.wndGuildRequest = uiGuildRequest.GuildRequestWindow()
		def OpenGuildRequest(self):
			self.MakeGuildRequest()
			if self.wndGuildRequest.IsShow():
				self.wndGuildRequest.Close()
			else:
				self.wndGuildRequest.Open()
		def GuildRequestLoadName(self, tabIndex):
			self.MakeGuildRequest()
			self.wndGuildRequest.GuildRequestLoadName(int(tabIndex))
		def GuildRequestLoadPage(self, tabIndex, pageIndex, maxPage):
			self.MakeGuildRequest()
			self.wndGuildRequest.GuildRequestLoadPage(int(tabIndex), int(pageIndex), int(maxPage))
		def GuildRequestSetItem(self, index, g_id, name, level, ladder_point, membercount, maxmember, isRequest):
			self.MakeGuildRequest()
			self.wndGuildRequest.GuildRequestSetItem(index, g_id, name, level, ladder_point, membercount, maxmember, isRequest)
		def GuildRequestSetRequest(self, index, pid, name, level, race, skillIndex):
			self.MakeGuildRequest()
			self.wndGuildRequest.GuildRequestSetRequest(index, pid, name, level, race, skillIndex)
