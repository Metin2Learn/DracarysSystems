# Add


#ifdef ENABLE_GUILD_REQUEST
#include "packet.h"
#endif

# Search

int		power;

# Add after

#ifdef ENABLE_GUILD_REQUEST
	BYTE	empire;
#endif

# Search

int			GetGuildWarLossCount() const { return m_data.loss; }

# Add after

#ifdef ENABLE_GUILD_REQUEST
	BYTE		GetEmpire()const { return m_data.empire; }
	WORD		GetIndex()const { return m_request_index; }
	void		SetIndex(WORD index) { m_request_index = index; }
	bool		IsHaveRequest(DWORD pid);
	void		SaveRequestData(const TGuild_request& t, bool isFirst = false);
	void		RemoveRequestData(DWORD pid, bool isFirst = false, bool isFromMaster = false);
	void		ReloadRequest();
	std::vector<TGuild_request> m_request;
#endif

# Search

void LoadGuildMemberData(SQLMsg* pmsg);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	WORD	m_request_index;
	void LoadGuildRequestData(SQLMsg* pmsg);
#endif