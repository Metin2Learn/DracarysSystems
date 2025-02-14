#Am Ende der Datei hinzufügen

	if app.ENABLE_ANTI_MULTIPLE_FARM:
		def BINARY_RecvAntiFarmReload(self):
			if not self.interface:
				return
			self.interface.SendAntiFarmReload()
