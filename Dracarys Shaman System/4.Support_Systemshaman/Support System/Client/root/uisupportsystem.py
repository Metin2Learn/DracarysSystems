import app, chr, chrmgr, player, net, pack, net, snd, item, chat, ime
import grp, os, mouseModule, ui, uiScriptLocale, localeInfo, constInfo, wndMgr, uiToolTip, exception
from _weakref import proxy

class SupportMainGui(ui.ScriptWindow):
	class TextToolTip(ui.Window):
		def __init__(self, y):
			ui.Window.__init__(self, "TOP_MOST")
			textLine = ui.TextLine()
			textLine.SetParent(self)
			textLine.SetHorizontalAlignLeft()
			textLine.SetOutline()
			textLine.Show()
			self.y = y
			self.textLine = textLine
		def __del__(self):
			ui.Window.__del__(self)
		def SetText(self, text):
			self.textLine.SetText(text)
		def OnRender(self):
			(mouseX, mouseY) = wndMgr.GetMousePosition()
			self.textLine.SetPosition(mouseX, mouseY - 60 + self.y)

	def __init__(self, vnum = 0):
		ui.ScriptWindow.__init__(self)
		self.vnum = vnum
		self.__LoadWindow()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "uiscript/supportinformationwindow.py")
		except:
			exception.Abort("supportinformationwindow.LoadWindow.LoadObject")
		try:
			self.board = self.GetChild("board")
			self.boardclose = self.GetChild("CloseButton")
			self.slotimage = self.GetChild("SlotSupportImage")
			self.speciality = self.GetChild("SpecialityValue")
			self.supportlvl = self.GetChild("LevelValue")
			self.supportint = self.GetChild("SupportIntValue")
			self.suppexp = self.GetChild("UpBringing_Support_EXP_Gauge_Board")

			self.tooltipexp = []
			for i in range(0,4):
				self.tooltipexp.append(self.TextToolTip(15*i))
				self.tooltipexp[i].Hide()
			self.petexppages = []
			for j in xrange(4):
				self.petexppages.append(self.GetChild("UpBringing_Support_EXPGauge_%d"%j))
				self.petexppages[j].SetSize(0, 0)
			self.SetDefaultInfo()
			self.boardclose.SetEvent(ui.__mem_func__(self.Close))

		except:
			exception.Abort("PetInformationWindow.LoadWindow.BindObject")

	def SetDefaultInfo(self):
		self.speciality.SetText("")
		self.supportlvl.SetText("")
		self.supportint.SetText("")
		self.slotimage.ClearSlot(0)
		self.SetExperience(0,0)

	def SetImageSlot(self, vnum):
		self.slotimage.SetItemSlot(0, int(vnum), 0)
		self.slotimage.SetAlwaysRenderCoverButton(0, True)

	def SetLevel(self, level):
		self.supportlvl.SetText(level)

	def SetSpeciality(self, speciality):
		self.speciality.SetText(speciality)

	def SetInt(self, ints):
		self.supportint.SetText(ints +"%")

	def SetExperience(self, expm, exptot):
		expm = int(expm)
		exptot = int(exptot)
		if exptot > 0:	
			totalexp = exptot
			totexpm = int(float(totalexp) / 100 * 100 )
			totexpi = totalexp - totexpm
			expmp =  float(expm) / totexpm * 100
		else:
			totalexp = 0
			totexpm = 0
			totexpi = 0
			expmp =  0

		curPoint = int(min(expm, totexpm))
		curPoint = int(max(expm, 0))
		maxPoint = int(max(totexpm, 0))
		maxPointi = int(max(totexpi, 0))

		quarterPoint = maxPoint/4
		quarterPointi = maxPointi 
		FullCount = 0

		if 0 != quarterPoint:
			FullCount = min(4, curPoint / quarterPoint)

		for i in xrange(4):
			self.petexppages[i].Hide()

		for i in xrange(FullCount):
			self.petexppages[i].SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			self.petexppages[i].Show()

		if 0 != quarterPoint:
			if FullCount < 4:
				Percentage = float(curPoint % quarterPoint) / quarterPoint - 1.0
				self.petexppages[FullCount].SetRenderingRect(0.0, Percentage, 0.0, 0.0)
				self.petexppages[FullCount].Show()
		self.tooltipexp[0].SetText(localeInfo.PET_KALAN_TECRUBE+"%d of %d" % (expm, totexpm))
		self.tooltipexp[1].SetText(localeInfo.PET_GUNCEL_TECRUBE+"%.2f%%" % expmp)

	def Show(self):
		ui.ScriptWindow.Show(self)

	def Close(self):
		self.Hide()

	def OnPressEscapeKey(self):
		self.Close()
		return True

	def OnUpdate(self):
		if True == self.suppexp.IsIn():
			for i in range(0,4):
				self.tooltipexp[i].Show()
		else:
			for i in range(0,4):
				self.tooltipexp[i].Hide()

class SupportSystemMini(ui.ScriptWindow):
	class TextToolTip(ui.Window):
		def __init__(self, y):
			ui.Window.__init__(self, "TOP_MOST")
			textLine = ui.TextLine()
			textLine.SetParent(self)
			textLine.SetHorizontalAlignLeft()
			textLine.SetOutline()
			textLine.Show()
			self.y = y
			self.textLine = textLine

		def __del__(self):
			ui.Window.__del__(self)

		def SetText(self, text):
			self.textLine.SetText(text)

		def OnRender(self):
			(mouseX, mouseY) = wndMgr.GetMousePosition()
			self.textLine.SetPosition(mouseX, mouseY - 60 + self.y)

	def __init__(self, vnum = 0):
		ui.ScriptWindow.__init__(self)
		self.vnum = vnum
		self.game=0
		self.__LoadWindow()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def Show(self):
		ui.ScriptWindow.Show(self)

	def Close(self):
		self.Hide()

	def __LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "uiscript/supportminiinformationwindow.py")
		except:
			exception.Abort("supportminiinformationwindow.LoadWindow.LoadObject")

		try:
			self.mainbg = self.GetChild("main_bg")
			self.main_slot_img = self.GetChild("pet_icon_slot")
			self.job_name = self.GetChild("job_name")
			self.suppexp = self.GetChild("UpBringing_Support_EXP_Gauge_Board")

			self.tooltipexp = []
			for i in xrange(4):
				self.tooltipexp.append(self.TextToolTip(15*i))
				self.tooltipexp[i].Hide()
			
			self.petexppages = []
			for j in xrange(4):
				self.petexppages.append(self.GetChild("UpBringing_Support_EXPGauge_%d"%j))
				self.petexppages[j].SetSize(0, 0)

			self.main_slot_img.SetUseSlotEvent(ui.__mem_func__(self.OpenPet))
			self.main_slot_img.SetSelectItemSlotEvent(ui.__mem_func__(self.OpenPet))

			self.SetDefaultInfo()

		except:
			exception.Abort("supportminiinformationwindow.LoadWindow.BindObject")

	def SetGame(self, game):
		self.game = proxy(game)
	def SetDefaultInfo(self):
		self.main_slot_img.ClearSlot(0)
		self.SetExperience(0,0)

	def OpenPet(self):
		self.game.OpenSupportGui(self.vnum)

	def SetImageSlot(self, vnum):
		self.main_slot_img.SetItemSlot(0, int(vnum), 0)
		self.main_slot_img.SetAlwaysRenderCoverButton(0, True)

	def SetName(self,name):
		self.job_name.SetText(name)

	def SetExperience(self, expm, exptot):
		expm = int(expm)
		exptot = int(exptot)
		if exptot > 0:	
			totalexp = exptot
			totexpm = int(float(totalexp) / 100 * 100 )
			totexpi = totalexp - totexpm
			expmp =  float(expm) / totexpm * 100
		else:
			totalexp = 0
			totexpm = 0
			totexpi = 0
			expmp =  0

		curPoint = int(min(expm, totexpm))
		curPoint = int(max(expm, 0))
		maxPoint = int(max(totexpm, 0))
		maxPointi = int(max(totexpi, 0))

		quarterPoint = maxPoint/4
		quarterPointi = maxPointi 
		FullCount = 0

		if 0 != quarterPoint:
			FullCount = min(4, curPoint / quarterPoint)

		for i in xrange(4):
			self.petexppages[i].Hide()

		for i in xrange(FullCount):
			self.petexppages[i].SetRenderingRect(0.0, 0.0, 0.0, 0.0)
			self.petexppages[i].Show()

		if 0 != quarterPoint:
			if FullCount < 4:
				Percentage = float(curPoint % quarterPoint) / quarterPoint - 1.0
				self.petexppages[FullCount].SetRenderingRect(0.0, Percentage, 0.0, 0.0)
				self.petexppages[FullCount].Show()
		self.tooltipexp[0].SetText(localeInfo.PET_KALAN_TECRUBE+"%d of %d" % (expm, totexpm))
		self.tooltipexp[1].SetText(localeInfo.PET_GUNCEL_TECRUBE+"%.2f%%" % expmp)

	def OnUpdate(self):
		if True == self.suppexp.IsIn():
			for i in xrange(4):
				self.tooltipexp[i].Show()
		else:
			for i in xrange(4):
				self.tooltipexp[i].Hide()
