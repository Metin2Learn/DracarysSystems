# Search

	m_mapGuild.clear();

# Add after

#ifdef ENABLE_GUILD_REQUEST
	m_mapNameGuild.clear();
	m_mapNameAll.clear();
	m_mapNameShinsoo.clear();
	m_mapNameChunjo.clear();
	m_mapNameJinno.clear();
#endif

# Search

	m_mapGuild.insert(std::make_pair(pg->GetID(), pg));

# Add after

#ifdef ENABLE_GUILD_REQUEST
	SortGuildCache();
#endif

# Add


#ifdef ENABLE_GUILD_REQUEST
#include <cmath>
#include "p2p.h"
bool sortGuild(const CGuild* a, const CGuild* b)
{
	return (a->GetLevel() > b->GetLevel() && a->GetLadderPoint() > b->GetLadderPoint());
}
void CGuildManager::SortGuildCache()
{
	m_mapNameGuild.clear();
	m_mapNameAll.clear();
	m_mapNameShinsoo.clear();
	m_mapNameChunjo.clear();
	m_mapNameJinno.clear();
	if (m_mapGuild.size())
	{
		for (auto it = m_mapGuild.begin(); it != m_mapGuild.end(); ++it)
		{
			CGuild* guild = it->second;
			m_mapNameGuild.emplace(guild->GetName(), guild);
			m_mapNameAll.emplace_back(guild);
		}
	}
	std::sort(m_mapNameAll.begin(), m_mapNameAll.end(), sortGuild);
	if (m_mapNameAll.size())
	{
		for (DWORD j = 0; j < m_mapNameAll.size(); ++j)
		{
			CGuild* guild = m_mapNameAll[j];
			guild->SetIndex(j + 1);
			if (guild->GetEmpire() == 1)
				m_mapNameShinsoo.emplace_back(guild);
			else if (guild->GetEmpire() == 2)
				m_mapNameChunjo.emplace_back(guild);
			else if (guild->GetEmpire() == 3)
				m_mapNameJinno.emplace_back(guild);
		}
	}
}
void CGuildManager::SendRequest(LPCHARACTER ch, DWORD guildID, BYTE requestIndex)
{
	// 0 - PLAYER SEND REQUEST
	// 1 - PLAYER REMOVE REQUEST
	// 2 - MASTER ACCEPT REQUEST
	// 3 - MASTER DONT ACCEPT REQUEST
	

	if (requestIndex == 0)
	{
		if (ch->GetGuild() != NULL)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("757"));
			return;
		}

		auto it = m_mapGuild.find(guildID);
		if (it != m_mapGuild.end())
		{
			CGuild* guild = it->second;
			if (guild->IsHaveRequest(ch->GetPlayerID()))
				return;
			else if (ch->GetEmpire() != guild->GetEmpire())
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("756"), guild->GetName());
				return;
			}


			TGuild_request p;
			p.pid = ch->GetPlayerID();
			strlcpy(p.name, ch->GetName(), sizeof(p.name));
			p.level = ch->GetLevel();
			p.race = ch->GetRaceNum();
			p.skillIndex = ch->GetSkillGroup();

			guild->SaveRequestData(p, true);
		}
	}
	else if (requestIndex == 1)
	{
		auto it = m_mapGuild.find(guildID);
		if (it != m_mapGuild.end())
		{
			CGuild* guild = it->second;
			if (!guild->IsHaveRequest(ch->GetPlayerID()))
				return;
			guild->RemoveRequestData(ch->GetPlayerID(), true);
		}
	}
	else if (requestIndex == 2)
	{
		CGuild* guild = ch->GetGuild();
		if (!guild)
			return;
		else if (!guild->IsHaveRequest(guildID))
			return;

		bool isOkey = false;
		auto itGuild = guild->GetMember(ch->GetPlayerID());
		if (ch == guild->GetMasterCharacter())
			isOkey = true;
		else if (itGuild && guild->HasGradeAuth(itGuild->grade, GUILD_AUTH_ADD_MEMBER))
			isOkey = true;

		if (!isOkey)
			return;
		

		LPCHARACTER tch = CHARACTER_MANAGER::Instance().FindByPID(guildID);
		if (!tch)
		{
			auto p2ptch = P2P_MANAGER::Instance().FindByPID(guildID);
			if (p2ptch == NULL)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("755"));
			else
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("754"), p2ptch->bChannel);
		}
		else
		{
			if (tch->GetGuild() != NULL)
			{
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("753"), tch->GetName());
				return;
			}
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("752"));
			guild->Invite(ch, tch);
		}
	}
	else if (requestIndex == 3)
	{
		CGuild* guild = ch->GetGuild();
		if (guild)
		{
			if (!guild->IsHaveRequest(guildID))
				return;
			bool isOkey = false;
			auto itGuild = guild->GetMember(ch->GetPlayerID());
			if (ch == guild->GetMasterCharacter())
				isOkey = true;
			else if(itGuild && guild->HasGradeAuth(itGuild->grade, GUILD_AUTH_ADD_MEMBER))
				isOkey = true;
			if(isOkey)
				guild->RemoveRequestData(guildID, true, true);
		}
	}
}
void CGuildManager::SendData(LPCHARACTER ch, BYTE tabIndex, DWORD pageIndex, const char* guildName)
{
	const std::vector<CGuild*> m_cache[] = { m_mapNameAll, m_mapNameShinsoo, m_mapNameChunjo, m_mapNameJinno };
	if (tabIndex >= _countof(m_cache)+1) //+1 for request window..
		return;

	ch->SetProtectTime("request.tabIndex", tabIndex);
	ch->SetProtectTime("request.pageIndex", pageIndex);

	TPacketGCGuildRequest p;
	p.header = HEADER_GC_GUILD_REQUEST;
	p.size = sizeof(p);
	int pageCount = 1;
	TEMP_BUFFER buf;
	if (tabIndex == 4)
	{
		std::vector<TGuild_request> m_data;
		m_data.clear();
		CGuild* guild = ch->GetGuild();
		if(guild != NULL)
		{
			bool isOkey = false;
			auto itGuild = guild->GetMember(ch->GetPlayerID());
			if(guild->GetMasterCharacter() == ch)
				isOkey = true;
			else if(itGuild && guild->HasGradeAuth(itGuild->grade, GUILD_AUTH_ADD_MEMBER))
				isOkey = true;
			if (guild && isOkey)
			{
				int maxIteminGui = 8;
				int mapSize = guild->m_request.size();
				pageCount = int(ceil(float(mapSize) / float(maxIteminGui)));
				if (mapSize)
				{
					if (pageIndex > pageCount)
						return;
					int start = (pageIndex - 1) * maxIteminGui;
					if (start < 0)
						start = 0;
					int end = ((pageIndex - 1) * maxIteminGui) + maxIteminGui;
					if (end < 0)
						end = 0;
					for (int x = start; x <= end; ++x)
					{
						if (x >= mapSize)
							break;
						auto it = guild->m_request.begin();
						std::advance(it, x);
						TGuild_request p;
						p.index = x+1;
						p.level = it->level;
						p.pid = it->pid;
						p.race = it->race;
						p.skillIndex = it->skillIndex;
						strlcpy(p.name, it->name, sizeof(p.name));
						m_data.emplace_back(p);
					}
				}
			}
		}
	

		
		int dataSize = m_data.size();
		p.size += sizeof(TGuild_request) * dataSize;
		p.sub_index = SUB_REQUEST_REQUEST;
		buf.write(&p, sizeof(TPacketGCGuildRequest));
		buf.write(&tabIndex, sizeof(BYTE));
		buf.write(&pageIndex, sizeof(DWORD));
		buf.write(&pageCount, sizeof(int));
		buf.write(&dataSize, sizeof(int));
		if (dataSize)
			buf.write(m_data.data(), sizeof(TGuild_request) * dataSize);		
	}
	else
	{
		std::vector<TGuildRequest> m_data;
		m_data.clear();
		if (guildName != NULL)
		{
			auto it = m_mapNameGuild.find(guildName);
			if (it != m_mapNameGuild.end())
			{
				auto guild = it->second;
				TGuildRequest g;
				strlcpy(g.name, guild->GetName(), sizeof(g.name));
				g.index = guild->GetIndex();
				g.g_id = guild->GetID();
				g.level = guild->GetLevel();
				g.ladder_point = guild->GetLadderPoint();
				g.member[0] = guild->GetMemberCount();
				g.member[1] = guild->GetMaxMemberCount();
				g.isRequest = guild->IsHaveRequest(ch->GetPlayerID());
				m_data.emplace_back(g);
			}
		}
		else
		{
			int maxIteminGui = 8;
			int mapSize = m_cache[tabIndex].size();
			pageCount = int(ceil(float(mapSize) / float(maxIteminGui)));
			if (mapSize)
			{
				if (pageIndex > pageCount)
					return;
				int start = (pageIndex - 1) * maxIteminGui;
				if (start < 0)
					start = 0;
				int end = ((pageIndex - 1) * maxIteminGui) + maxIteminGui;
				if (end < 0)
					end = 0;
				for (int x = start; x <= end; ++x)
				{
					if (x >= mapSize)
						break;
					auto it = m_cache[tabIndex].begin();
					std::advance(it, x);
					auto guild = *it;
					TGuildRequest g;
					strlcpy(g.name, guild->GetName(), sizeof(g.name));
					g.index = guild->GetIndex();
					g.g_id = guild->GetID();
					g.level = guild->GetLevel();
					g.ladder_point = guild->GetLadderPoint();
					g.member[0] = guild->GetMemberCount();
					g.member[1] = guild->GetMaxMemberCount();
					g.isRequest = guild->IsHaveRequest(ch->GetPlayerID());
					m_data.emplace_back(g);
				}
			}
		}

		int dataSize = m_data.size();
		p.size += sizeof(TGuildRequest) * dataSize;
		
		if (guildName != NULL)
		{
			p.sub_index = SUB_REQUEST_NAME;
			buf.write(&p, sizeof(TPacketGCGuildRequest));
			buf.write(&tabIndex, sizeof(BYTE));
			buf.write(&dataSize, sizeof(int));
			if (dataSize)
				buf.write(m_data.data(), sizeof(TGuildRequest) * dataSize);
		}
		else
		{
			p.sub_index = SUB_REQUEST_PAGEINDEX;
			buf.write(&p, sizeof(TPacketGCGuildRequest));
			buf.write(&tabIndex, sizeof(BYTE));
			buf.write(&pageIndex, sizeof(DWORD));
			buf.write(&pageCount, sizeof(int));
			buf.write(&dataSize, sizeof(int));
			if (dataSize)
				buf.write(m_data.data(), sizeof(TGuildRequest) * dataSize);
		}
	}
	ch->GetDesc()->Packet(buf.read_peek(), buf.size());
}
#endif

# Search

	CGuildMarkManager::instance().DeleteMark(guild_id);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	SortGuildCache();
#endif