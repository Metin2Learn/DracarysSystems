#class window
#def initialize add in case missing

		self.mouseLeftButtonUpEvent = None
		self.mouseLeftButtonUpArgs = None

		self.mouseOverInEvent = None
		self.mouseOverInArgs = None

		self.mouseOverOutEvent = None
		self.mouseOverOutArgs = None

#down add

	def SetMouseLeftButtonUpEvent(self, event, *args):
		self.mouseLeftButtonUpEvent = event
		self.mouseLeftButtonUpArgs = args

	def SetMouseOverInEvent(self, event, *args):
		self.mouseOverInEvent = event
		self.mouseOverInArgs = args

	def SetMouseOverOutEvent(self, event, *args):
		self.mouseOverOutEvent = event
		self.mouseOverOutArgs = args


# in class Thinboard add 

	def SetAlpha(self, alpha):
		color  = grp.GenerateColor(0.0, 0.0, 0.0, alpha)
		self.Base.SetColor(color)
		for wnd in self.Lines:
			wnd.SetAlpha(alpha)
		for wnd in self.Corners:
			wnd.SetAlpha(alpha)