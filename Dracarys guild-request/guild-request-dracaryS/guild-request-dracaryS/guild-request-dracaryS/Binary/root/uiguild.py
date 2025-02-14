# Search
			page.declareWarButton.SetEvent(ui.__mem_func__(self.__OnClickDeclareWarButton))
# Add after
			if app.ENABLE_GUILD_REQUEST:
				page.GetChild("requestButton").SetEvent(ui.__mem_func__(self.__OnClickRequestButton))

#Search

	def __OnClickDeclareWarButton(self):

# Add before

	if app.ENABLE_GUILD_REQUEST:
		def __OnClickRequestButton(self):
			interface = constInfo.GetInterfaceInstance()
			if interface != None:
				interface.OpenGuildRequest()
