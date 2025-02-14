# Add


#ifdef ENABLE_SUPPORT_SYSTEM
bool CPythonNetworkStream::RecvSupportUseSkill()
{
	TPacketGCSupportUseSkill packet;
	if (!Recv(sizeof(TPacketGCSupportUseSkill), &packet))
	{
		Tracen("CPythonNetworkStream::RecvCharacterMovePacket - PACKET READ ERROR");
		return false;
	}

	CInstanceBase* pkInstClone = CPythonCharacterManager::Instance().GetInstancePtr(packet.dwVid);
	if(pkInstClone)
	{
		DWORD dwSkillIndex = packet.dwVnum;
		CPythonSkill::TSkillData * pSkillData;
		if (!CPythonSkill::Instance().GetSkillData(dwSkillIndex, &pSkillData))
			return false;
		DWORD value;
		if (packet.dwLevel <= 17)
			value = 0;
		else if (packet.dwLevel <= 30 && packet.dwLevel >17)
			value = 1;
		else if (packet.dwLevel > 30 && packet.dwLevel <= 39)
			value = 2;
		else if (packet.dwLevel >= 40)
			value = 3;
		DWORD dwMotionIndex = pSkillData->GetSkillMotionIndex(value);
		if (!pkInstClone->NEW_UseSkill(dwSkillIndex, dwMotionIndex, 1, false))
			Tracenf("CPythonPlayer::UseGuildSkill(%d) - pkInstMain->NEW_UseSkill - ERROR", dwSkillIndex);
	}
	return true;
}
#endif

