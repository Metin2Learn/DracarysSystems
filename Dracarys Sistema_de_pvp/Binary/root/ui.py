# Search

	def OnEndFrame(self):
		pass

# Add before

	if app.ENABLE_PVP_TOURNAMENT:
		def ClearImages(self):
			wndMgr.ClearImages(self.hWnd)
		def SetPercentageReverse(self, curValue, maxValue):
			wndMgr.SetRenderingRect(self.hWnd,-1.0 + float(curValue) / float(maxValue), 0.0, 0.0, 0.0)
