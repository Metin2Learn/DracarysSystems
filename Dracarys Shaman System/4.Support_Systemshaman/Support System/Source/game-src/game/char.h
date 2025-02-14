# Search


class CPetSystem;

# Add after

#ifdef ENABLE_SUPPORT_SYSTEM
	#include "SupportSystem.h"
class CSupportSystem;
#endif


# Search

	public:

# Add before

#ifdef ENABLE_SUPPORT_SYSTEM
	public:
		CSupportSystem*			GetSupportSystem()				{ return m_supportSystem; }
		void			SendSupportSkillPacket(DWORD skill_vnum);
		void SetSupport() { m_bIsSupport = true; }
		bool IsSupport() { return m_bIsSupport; }
		void SetOwner(LPCHARACTER owner) { m_Owner = owner; }
		LPCHARACTER GetOwner() { return m_Owner; }
		void SetSupportInt(int count) { m_dwSupportInt = count; }
		DWORD GetSupportInt() { return m_dwSupportInt; }
	protected:
		CSupportSystem*			m_supportSystem;
		bool m_bIsSupport;
		LPCHARACTER m_Owner;
		DWORD m_dwSupportInt;
#endif 
