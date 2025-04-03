
# Search

	def Flash(self):
		wndMgr.Flash(self.hWnd)

# Change

	if app.ENABLE_NEW_PET_SYSTEM:
		def Flash(self, state):
			wndMgr.Flash(self.hWnd, state)
	else:
		def Flash(self):
			wndMgr.Flash(self.hWnd)



# Search

	def SetSkillSlotNew(self, renderingSlotNumber, skillIndex, skillGrade, skillLevel):

# Add before

	if app.ENABLE_NEW_PET_SYSTEM:
		def SetPetSkillSlot(self, renderingSlotNumber, skillIndex, skillLevel):
			if 0 == skillIndex:
				wndMgr.ClearSlot(self.hWnd, renderingSlotNumber)
				return

			if skillIndex == 99:
				skillIcon = skill.GetIconImageNewEx("d:/ymir work/ui/pet/skill_button/skill_enable_button.sub")
			else:
				skillIcon = skill.GetIconImageNewEx("d:/ymir work/ui/skill/pet/%d.sub"%skillIndex)
			if 0 == skillIcon:
				wndMgr.ClearSlot(self.hWnd, renderingSlotNumber)
				return
			wndMgr.SetSlot(self.hWnd, renderingSlotNumber, skillIndex, 1, 1, skillIcon)
			if skillIndex != 0:
				wndMgr.SetSlotCount(self.hWnd, renderingSlotNumber, skillLevel)