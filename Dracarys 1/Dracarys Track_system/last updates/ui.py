# Search

        self.RegisterWindow(layer)

# Add after

        if app.ENABLE_TRACK_WINDOW:
            self.exPos = (0,0)
            self.itsRendered = False
            self.itsNeedDoubleRender = False
            self.sortIndex = 0

# Search

    def SetPosition(self, x, y):
        wndMgr.SetWindowPosition(self.hWnd, x, y)

# Change

    if app.ENABLE_TRACK_WINDOW:
        def SetPosition(self, x, y, flag = False):
            if flag == True:
                self.exPos = (x,y)
            wndMgr.SetWindowPosition(self.hWnd, x, y)
    else:
        def SetPosition(self, x, y):
            wndMgr.SetWindowPosition(self.hWnd, x, y)




ui.py
# Search

class Button(Window):

# Add in

    if app.ENABLE_TRACK_WINDOW:
        def SetRenderingRect(self, left, top, right, bottom):
            wndMgr.SetRenderingRect(self.hWnd, left, top, right, bottom)