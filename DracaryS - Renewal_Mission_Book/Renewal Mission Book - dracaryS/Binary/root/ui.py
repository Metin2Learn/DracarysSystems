# Search

			elif Type == "editline":

# Add before

			elif Type == "listbox_new":
				parent.Children[Index] = ListBoxNew()
				parent.Children[Index].SetParent(parent)
				self.LoadElementListBox(parent.Children[Index], ElementValue, parent)

# Search

		self.RegisterWindow(layer)

# Add after

		if app.RENEWAL_MISSION_BOOKS:
			self.exPos = (0,0)
			self.itsRendered = False
			self.itsNeedDoubleRender = False
			self.sortIndex = 0

# Search

	def SetPosition(self, x, y):
		wndMgr.SetWindowPosition(self.hWnd, x, y)

# Change

	if app.RENEWAL_MISSION_BOOKS:
		def SetPosition(self, x, y, flag = False):
			if flag == True:
				self.exPos = (x,y)
			wndMgr.SetWindowPosition(self.hWnd, x, y)
	else:
		def SetPosition(self, x, y):
			wndMgr.SetWindowPosition(self.hWnd, x, y)


# Add

class ListBoxNew(Window):
	def __del__(self):
		Window.__del__(self)
	def Destroy(self):
		for item in self.itemList:
			item.Destroy()
		self.itemList=[]
		self.scrollBar=None
		self.basePos=0
		self.scrollLen=0
		self.scrollLenExtra=0
		self.isHorizontal= 0
	def __init__(self, isHorizontal = False):
		Window.__init__(self)
		self.itemList=[]
		self.Destroy()
		self.isHorizontal= isHorizontal
	def RemoveAllItems(self):
		for item in self.itemList:
			item.Destroy()
		self.itemList=[]
		if self.scrollBar:
			self.scrollBar.SetPos(0)
		self.RefreshAll()
	def SetExtraScrollLen(self, extraLen):
		self.scrollLenExtra=extraLen
	def GetItems(self):
		return self.itemList
	def AppendItem(self, newItem):
		self.itemList.append(newItem)
	def SetScrollBar(self, scrollBar):
		scrollBar.SetScrollEvent(__mem_func__(self.__OnScroll))
		self.scrollBar=scrollBar
	def OnMouseWheel(self, nLen):
		if self.scrollBar:
			if self.scrollBar.IsShow():
				if nLen > 0:
					self.scrollBar.OnUp()
				else:
					self.scrollBar.OnDown()
				return True
		return False
	def __OnScroll(self):
		self.SetBasePos(int(self.scrollBar.GetPos()*self.scrollLen))
	def RefreshAll(self):
		windowHeight = self.GetHeight()
		scrollBar = self.scrollBar
		screenSize = 0
		for child in self.itemList:
			if child.exPos[1] > screenSize:
				screenSize = child.exPos[1]
		if screenSize > windowHeight:
			scrollLen = screenSize-windowHeight
			if scrollLen != 0:
				scrollLen += self.scrollLenExtra
			self.scrollLen = scrollLen
			scrollBar.SetMiddleBarSize(float(windowHeight-5)/float(screenSize))
		else:
			scrollBar.SetMiddleBarSize(1.0)
	def Render(self,basePos):
		for item in self.itemList:
			(ex,ey) = item.exPos
			if self.isHorizontal:
				item.SetPosition(ex-(basePos), ey)
			else:
				item.SetPosition(ex, ey-(basePos))
			item.OnRender()
	def SetBasePos(self, basePos):
		if self.basePos == basePos:
			return
		self.Render(basePos)
		self.basePos=basePos

# Search

class Button(Window):

# Add in

	if app.RENEWAL_MISSION_BOOKS:
		def SetRenderingRect(self, left, top, right, bottom):
			wndMgr.SetRenderingRect(self.hWnd, left, top, right, bottom)
