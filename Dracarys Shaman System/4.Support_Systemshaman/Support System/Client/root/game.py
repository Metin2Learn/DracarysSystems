# Search

		self.PickingCharacterIndex = -1

# Add after:

		if app.ENABLE_SUPPORT_SYSTEM:
			self.supportpg=None
			self.supportpg2=None
			self.supportmini=None
			self.supportmini2=None

# Search

		self.mapNameShower.Hide()
		self.mapNameShower = None

# Add after


		if app.ENABLE_SUPPORT_SYSTEM:
			if self.supportpg:
				self.supportpg.Close()
				self.supportpg=None
			if self.supportpg2:
				self.supportpg2.Close()
				self.supportpg2=None
			if self.supportmini:
				self.supportmini.Close()
				self.supportmini=None
			if self.supportmini2:
				self.supportmini2.Close()
				self.supportmini2=None

# Search

		self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.ENABLE_SUPPORT_SYSTEM:
			serverCommandList.update({"SupportLv" : self.SetSupportLevel })
			serverCommandList.update({"SupportName" : self.SetSupportName })
			serverCommandList.update({"SupportLeave" : self.SupportLeave })
			serverCommandList.update({"SupporInt" : self.SupportInt })
			serverCommandList.update({"SupportExp" : self.SetSupportExp })
			serverCommandList.update({"SupportIcon" : self.SetSupportIcon })
			serverCommandList.update({"SupportSpeciality" : self.SetSupportSpeciality })


# Add 


	if app.ENABLE_SUPPORT_SYSTEM:
		def MakeSupportBG(self, type):
			if type == 1:
				if self.supportpg==None:
					import uisupportsystem
					self.supportpg = uisupportsystem.SupportMainGui()
					self.supportpg.Close()
			elif type == 2:
				if self.supportpg2==None:
					import uisupportsystem
					self.supportpg2 = uisupportsystem.SupportMainGui()
					self.supportpg2.Close()
		def MakeSupportMini(self, type):
			if type == 1:
				if self.supportmini==None:
					import uisupportsystem
					self.supportmini = uisupportsystem.SupportSystemMini(1)
					self.supportmini.SetGame(self)
					self.supportmini.Close()
			elif type == 2:
				if self.supportmini2==None:
					import uisupportsystem
					self.supportmini2 = uisupportsystem.SupportSystemMini(2)
					self.supportmini2.SetGame(self)
					self.supportmini2.Close()

		def OpenSupportGui(self, arg):
			if(int(arg)==1):
				if self.supportpg:
					if self.supportpg.IsShow():
						self.supportpg.Close()
					else:
						self.supportpg.Show()
						self.supportpg.SetTop()
			elif(int(arg)==2):
				if self.supportpg2:
					if self.supportpg2.IsShow():
						self.supportpg2.Close()
					else:
						self.supportpg2.Show()
						self.supportpg2.SetTop()

		def SetSupportLevel(self, arg, level):
			if(int(arg)==1):
				if self.supportpg==None:
					self.MakeSupportBG(1)
				if self.supportpg:
					self.supportpg.SetLevel(level)
			elif(int(arg)==2):
				if self.supportpg2==None:
					self.MakeSupportBG(2)
				if self.supportpg2:
					self.supportpg2.SetLevel(level)

		def SetSupportName(self, arg, name):
			x = int(arg)
			if x==1:
				if self.supportmini==None:
					self.MakeSupportMini(1)
				if self.supportmini.IsShow():
					self.supportmini.Close()
				else:
					self.supportmini.SetPosition(5,systemSetting.GetHeight()-285)
					self.supportmini.Show()
					self.supportmini.SetName(localeInfo.EJDERHA)
			elif x==2:
				if self.supportmini2==None:
					self.MakeSupportMini(2)
				if self.supportmini2.IsShow():
					self.supportmini2.Close()
				else:
					self.supportmini2.SetPosition(5,systemSetting.GetHeight()-330)
					self.supportmini2.Show()
					self.supportmini2.SetName(localeInfo.IYILESTIRME)
			else:
				pass
			#if self.supportpg:
				#self.supportpg.SetName(name, name2)

		def SupportLeave(self, arg):
			if(int(arg)==1):
				if self.supportpg:
					self.supportpg.SetDefaultInfo()
					self.supportpg.Close()
				if self.supportmini:
					self.supportmini.SetDefaultInfo()
					self.supportmini.Close()
			elif(int(arg)==2):
				if self.supportpg2:
					self.supportpg2.SetDefaultInfo()
					self.supportpg2.Close()
				if self.supportmini2:
					self.supportmini2.SetDefaultInfo()
					self.supportmini2.Close()

		def SupportInt(self , arg, ints):
			if(int(arg)==1):
				if self.supportpg:
					self.supportpg.SetInt(ints)
			elif(int(arg)==2):
				if self.supportpg2:
					self.supportpg2.SetInt(ints)

		def SetSupportExp(self, arg, exp, exptot):
			if(int(arg)==1):
				if self.supportpg:
					self.supportpg.SetExperience(exp, exptot)
				if self.supportmini:
					self.supportmini.SetExperience(exp, exptot)
			elif(int(arg)==2):
				if self.supportpg2:
					self.supportpg2.SetExperience(exp, exptot)
				if self.supportmini2:
					self.supportmini2.SetExperience(exp, exptot)

		def SetSupportIcon(self, arg, vnum):
			if(int(arg)==1):
				if self.supportpg:
					self.supportpg.SetImageSlot(vnum)
					self.supportpg.SetSpeciality(localeInfo.EJDERHA)
				if self.supportmini:
					self.supportmini.SetImageSlot(vnum)
			elif(int(arg)==2):
				if self.supportpg2:
					self.supportpg2.SetImageSlot(vnum)
					self.supportpg2.SetSpeciality(localeInfo.IYILESTIRME)
				if self.supportmini2:
					self.supportmini2.SetImageSlot(vnum)

		def SetSupportSpeciality(self, arg, speciality):
			if(int(arg)==1):
				if self.supportpg:
					self.supportpg.SetSpeciality(localeInfo.EJDERHA)
			elif(int(arg)==2):
				if self.supportpg2:
					self.supportpg2.SetSpeciality(localeInfo.IYILESTIRME)