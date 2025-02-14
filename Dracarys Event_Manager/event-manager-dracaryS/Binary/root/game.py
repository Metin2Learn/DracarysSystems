
# Search

		self.interface = interfaceModule.Interface()

# Add after

		if app.ENABLE_EVENT_MANAGER:
			constInfo.SetInterfaceInstance(self.interface)

# Search

		self.KillFocus()

# Add after

		if app.ENABLE_EVENT_MANAGER:
			constInfo.SetInterfaceInstance(None)

# Search

	onPressKeyDict[app.DIK_F4]	= lambda : self.__PressQuickSlot(7)

# Add after
	if app.ENABLE_EVENT_MANAGER:
		onPressKeyDict[app.DIK_F11]	= lambda : self.interface.OpenEventCalendar()

# add

	if app.ENABLE_EVENT_MANAGER:
		def ClearEventManager(self):
			self.interface.ClearEventManager()
		def RefreshEventManager(self):
			self.interface.RefreshEventManager()
		def RefreshEventStatus(self, eventID, eventStatus, eventendTime, eventEndTimeText):
			self.interface.RefreshEventStatus(int(eventID), int(eventStatus), int(eventendTime), str(eventEndTimeText))
		def AppendEvent(self, dayIndex, eventID, eventIndex, startTime, endTime, empireFlag, channelFlag, value0, value1, value2, value3, startRealTime, endRealTime, isAlreadyStart):
			self.interface.AppendEvent(int(dayIndex),int(eventID), int(eventIndex), str(startTime), str(endTime), int(empireFlag), int(channelFlag), int(value0), int(value1), int(value2), int(value3), int(startRealTime), int(endRealTime), int(isAlreadyStart))

