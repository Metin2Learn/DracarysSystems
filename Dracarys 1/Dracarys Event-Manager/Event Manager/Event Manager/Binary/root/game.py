
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
		def AppendEvent(self, dayIndex, eventIndex, startTime, endTime, empireFlag, channelFlag, value0, value1, value2, value3, startRealTime, endRealTime, isAlreadyStart):
			self.interface.AppendEvent(int(dayIndex), int(eventIndex), str(startTime), str(endTime), int(empireFlag), int(channelFlag), int(value0), int(value1), int(value2), int(value3), int(startRealTime), int(endRealTime), int(isAlreadyStart))