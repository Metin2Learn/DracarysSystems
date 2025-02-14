# Add

#ifdef ENABLE_SUPPORT_SYSTEM
	#include "SupportSystem.h"
#endif

# Search

m_petSystem = M2_NEW CPetSystem(this);

# Add after

#ifdef ENABLE_SUPPORT_SYSTEM
	if (m_supportSystem)
	{
		m_supportSystem->Destroy();
		delete m_supportSystem;
	}
	m_supportSystem = M2_NEW CSupportSystem(this);
#endif

# Search

	if (m_petSystem)
	{
		m_petSystem->Destroy();
		delete m_petSystem;

		m_petSystem = 0;
	}

# Add after


#ifdef ENABLE_NEW_PET_SYSTEM
	if (m_newpetSystem)
	{
		m_newpetSystem->Destroy();
		delete m_newpetSystem;

		m_newpetSystem = 0;
	}
#endif


# Search

	m_dwSkipComboAttackByTime = 0;

# Add after

#ifdef ENABLE_SUPPORT_SYSTEM
	m_supportSystem = 0;
	m_bIsSupport = false;
	m_Owner = NULL;
#endif


# Add


#ifdef ENABLE_SUPPORT_SYSTEM
void CHARACTER::SendSupportSkillPacket(DWORD skill_vnum)
{
	TPacketGCSupportUseSkill pack;
	pack.bHeader = HEADER_GC_SUPPORT_SKILL;
	pack.dwVnum = skill_vnum;
	pack.dwVid = GetVID();
	pack.dwLevel = 41;
	
	PacketView(&pack, sizeof(TPacketGCSupportUseSkill), this);
}
#endif

