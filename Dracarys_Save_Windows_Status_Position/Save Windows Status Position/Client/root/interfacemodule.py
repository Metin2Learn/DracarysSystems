# search

		event.SetInterfaceWindow(self)

# add

		if app.ENABLE_SAVE_LAST_WINDOW_POSITION:
			import os
			if not os.path.exists("wndconf/"):
				os.makedirs("wndconf/")
			if not os.path.exists("wndconf/" + player.GetName()):
				os.makedirs("wndconf/" + player.GetName())