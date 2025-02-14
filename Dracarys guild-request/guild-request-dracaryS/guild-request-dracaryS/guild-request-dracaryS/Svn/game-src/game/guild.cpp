# Search

	m_data.master_pid = cp.master->GetPlayerID();

# Add after

#ifdef ENABLE_GUILD_REQUEST
	m_data.empire = cp.master->GetEmpire();
#endif

# Search

CGuild::CGuild(TGuildCreateParameter& cp)

# Change function - be careful.

CGuild::CGuild(TGuildCreateParameter& cp)
{
	Initialize();
	m_general_count = 0;
	m_iMemberCountBonus = 0;
	strlcpy(m_data.name, cp.name, sizeof(m_data.name));
	m_data.master_pid = cp.master->GetPlayerID();
#ifdef ENABLE_GUILD_REQUEST
	m_data.empire = cp.master->GetEmpire();
#endif
	strlcpy(m_data.grade_array[0].grade_name, "Leader", sizeof(m_data.grade_array[0].grade_name));
	m_data.grade_array[0].auth_flag = GUILD_AUTH_ADD_MEMBER | GUILD_AUTH_REMOVE_MEMBER | GUILD_AUTH_NOTICE | GUILD_AUTH_USE_SKILL;

	for (int i = 1; i < GUILD_GRADE_COUNT; ++i)
	{
		strlcpy(m_data.grade_array[i].grade_name, "...", sizeof(m_data.grade_array[i].grade_name));
		m_data.grade_array[i].auth_flag = 0;
	}

	std::unique_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery(
		"INSERT INTO player.guild(name, master, sp, level, exp, skill_point, skill"
#ifdef ENABLE_GUILD_REQUEST
		", empire"
#endif
		") "
		"VALUES('%s', %u, 1000, 1, 0, 0, '\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0\\0'"
#ifdef ENABLE_GUILD_REQUEST
		", %d"
#endif
		")",  m_data.name, m_data.master_pid
#ifdef ENABLE_GUILD_REQUEST
		, m_data.empire
#endif
	));

	m_data.guild_id = pmsg->Get()->uiInsertID;

	for (int i = 0; i < GUILD_GRADE_COUNT; ++i)
	{
		DBManager::instance().Query("INSERT INTO player.guild_grade VALUES(%u, %d, '%s', %d)",
			m_data.guild_id,
			i + 1,
			m_data.grade_array[i].grade_name,
			m_data.grade_array[i].auth_flag);
	}

	ComputeGuildPoints();
	m_data.power = m_data.max_power;
	m_data.ladder_point = 0;
	db_clientdesc->DBPacket(HEADER_GD_GUILD_CREATE, 0, &m_data.guild_id, sizeof(DWORD));

	TPacketGuildSkillUpdate guild_skill;
	guild_skill.guild_id = m_data.guild_id;
	guild_skill.amount = 0;
	guild_skill.skill_point = 0;
	memset(&guild_skill.skill_levels, 0, sizeof(guild_skill.skill_levels));
	db_clientdesc->DBPacket(HEADER_GD_GUILD_SKILL_UPDATE, 0, &guild_skill, sizeof(guild_skill));

	CHARACTER_MANAGER::instance().for_each_pc(FGuildNameSender(GetID(), GetName()));
	RequestAddMember(cp.master, GUILD_LEADER_GRADE);
}


# Search

	for (int i = 0; i < GUILD_SKILL_COUNT; ++i)
		abSkillUsable[i] = true;

# Add after

#ifdef ENABLE_GUILD_REQUEST
	m_request_index = 0;
#endif


# Search

	if (ch)
	{
		LoginMember(ch);
		ch->UpdatePacket();
	}
	else
		P2PLoginMember(p->dwPID);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	if (IsHaveRequest(p->dwPID))
		RemoveRequestData(p->dwPID, true);
#endif

# Search

void CGuild::LoadGuildMemberData(SQLMsg* pmsg)

# Change

void CGuild::LoadGuildMemberData(SQLMsg* pmsg)
{
#ifdef ENABLE_GUILD_REQUEST
	if (pmsg->Get()->uiNumRows == 0)
	{
		CGuildManager::instance().SortGuildCache();
		return;
	}
#else
	if (pmsg->Get()->uiNumRows == 0)
		return;
#endif

	m_general_count = 0;

	m_member.clear();

	for (uint i = 0; i < pmsg->Get()->uiNumRows; ++i)
	{
		MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);

		DWORD pid = strtoul(row[0], (char**)NULL, 10);
		BYTE grade = (BYTE)strtoul(row[1], (char**)NULL, 10);
		BYTE is_general = 0;

		if (row[2] && *row[2] == '1')
			is_general = 1;

		DWORD offer = strtoul(row[3], (char**)NULL, 10);
		BYTE level = (BYTE)strtoul(row[4], (char**)NULL, 10);
		BYTE job = (BYTE)strtoul(row[5], (char**)NULL, 10);
		char* name = row[6];

		if (is_general)
			m_general_count++;

		m_member.insert(std::make_pair(pid, TGuildMember(pid, grade, is_general, job, level, offer, name)));
		CGuildManager::instance().Link(pid, this);
	}
#ifdef ENABLE_GUILD_REQUEST
	CGuildManager::instance().SortGuildCache();
#endif
}

# Search

void CGuild::LoadGuildData(SQLMsg* pmsg)

# Change

void CGuild::LoadGuildData(SQLMsg* pmsg)
{
	if (pmsg->Get()->uiNumRows == 0)
	{
		sys_err("Query failed: getting guild data %s", pmsg->stQuery.c_str());
		return;
	}

	int c = 0;
	MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);
	m_data.master_pid = strtoul(row[c++], (char**)NULL, 10);
	m_data.level = (BYTE)strtoul(row[c++], (char**)NULL, 10);
	m_data.exp = strtoul(row[c++], (char**)NULL, 10);
	strlcpy(m_data.name, row[c++], sizeof(m_data.name));

	m_data.skill_point = (BYTE)strtoul(row[c++], (char**)NULL, 10);
	if (row[c])
		thecore_memcpy(m_data.abySkill, row[c], sizeof(BYTE) * GUILD_SKILL_COUNT);
	else
		memset(m_data.abySkill, 0, sizeof(BYTE) * GUILD_SKILL_COUNT);
	c++;

	m_data.power = MAX(0, strtoul(row[c++], (char**)NULL, 10));

	str_to_number(m_data.ladder_point, row[c++]);

	if (m_data.ladder_point < 0)
		m_data.ladder_point = 0;

	str_to_number(m_data.win, row[c++]);
	str_to_number(m_data.draw, row[c++]);
	str_to_number(m_data.loss, row[c++]);
	str_to_number(m_data.gold, row[c++]);
#ifdef ENABLE_GUILD_REQUEST
	str_to_number(m_data.empire, row[c++]);
#endif

	ComputeGuildPoints();
}

# Search

void CGuild::Load(DWORD guild_id)

# Change

void CGuild::Load(DWORD guild_id)
{
	Initialize();

	m_data.guild_id = guild_id;

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildData, this, std::placeholders::_1),
		"SELECT master, level, exp, name, skill_point, skill, sp, ladder_point, win, draw, loss, gold"
#ifdef ENABLE_GUILD_REQUEST
		", empire"
#endif
		" FROM player.guild WHERE id = %u", m_data.guild_id);

	sys_log(0, "GUILD: loading guild id %12s %u", m_data.name, guild_id);

	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildGradeData, this, std::placeholders::_1),"SELECT grade, name, auth+0 FROM player.guild_grade WHERE guild_id = %u", m_data.guild_id);
	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildMemberData, this, std::placeholders::_1),"SELECT pid, grade, is_general, offer, level, job, name FROM player.guild_member, player.player WHERE guild_id = %u and pid = id", guild_id);
#ifdef ENABLE_GUILD_REQUEST
	DBManager::instance().FuncQuery(std::bind(&CGuild::LoadGuildRequestData, this, std::placeholders::_1), "SELECT pid, name, level, race, skillIndex FROM player.request_list WHERE guild_id = %u", guild_id);
#endif
}









# Add

#ifdef ENABLE_GUILD_REQUEST
void CGuild::ReloadRequest()
{
	LoadGuildRequestData(DBManager::instance().DirectQuery("SELECT pid, name, level, race, skillIndex FROM player.request_list WHERE guild_id = %u", GetID()));
}
bool CGuild::IsHaveRequest(DWORD pid)
{
	if (m_request.size())
	{
		for (auto it = m_request.begin(); it != m_request.end(); ++it)
		{
			if (it->pid == pid)
				return true;
		}
	}
	return false;
}
void CGuild::SaveRequestData(const TGuild_request& t, bool isFirst)
{
	if (m_request.size())
	{
		for (auto it = m_request.begin(); it != m_request.end(); ++it)
		{
			if (it->pid == t.pid)
				return;
		}
	}
	m_request.emplace_back(t);

	std::string playerName = "";
	LPCHARACTER ch = CHARACTER_MANAGER::Instance().FindByPID(t.pid);
	if (ch)
	{
		playerName = ch->GetName();
		CGuildManager::Instance().SendData(ch, ch->GetProtectTime("request.tabIndex"), ch->GetProtectTime("request.pageIndex"), NULL);
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("751"), GetName());
	}
	else
	{
		auto CCIch = P2P_MANAGER::Instance().FindByPID(t.pid);
		if (CCIch)
			playerName = CCIch->szName;
	}

	LPCHARACTER chLeader = GetMasterCharacter();
	if (chLeader)
	{
		CGuildManager::Instance().SendData(chLeader, chLeader->GetProtectTime("request.tabIndex"), chLeader->GetProtectTime("request.pageIndex"), NULL);
		if (playerName == "")
			chLeader->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("750"));
		else
			chLeader->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("749"), playerName.c_str());
	}

	if (isFirst)
	{
		char szQuery[QUERY_MAX_LEN];
		snprintf(szQuery, sizeof(szQuery), "INSERT INTO player.request_list(guild_id, pid, name, level, race, skillIndex) VALUES(%u, %u, '%s', %d, %d, %d)",GetID(),t.pid,t.name,t.level,t.race,t.skillIndex);
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery(szQuery));

		TPacketGGGuild p;
		p.bHeader = HEADER_GG_GUILD;
		p.bSubHeader = GUILD_SUBHEADER_UPDATE_REQUEST;
		p.dwGuild = GetID();
		P2P_MANAGER::Instance().Send(&p, sizeof(p));
	}

}
void CGuild::RemoveRequestData(DWORD pid, bool isFirst, bool isFromMaster)
{
	if (m_request.size())
	{
		for (auto it = m_request.begin(); it != m_request.end(); ++it)
		{
			if (it->pid == pid)
			{
				m_request.erase(it);
				break;
			}
		}
	}

	std::string playerName = "";
	LPCHARACTER ch = CHARACTER_MANAGER::Instance().FindByPID(pid);
	if (ch)
	{
		playerName = ch->GetName();
		CGuildManager::Instance().SendData(ch, ch->GetProtectTime("request.tabIndex"), ch->GetProtectTime("request.pageIndex"), NULL);

		if(ch->GetGuild() != this)
		{
			if(isFromMaster)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("760"),GetName());
			else
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("759"), GetName());
		}
	}
	else
	{
		auto CCIch = P2P_MANAGER::Instance().FindByPID(pid);
		if (CCIch)
			playerName = CCIch->szName;
	}

	LPCHARACTER chLeader = GetMasterCharacter();
	if (chLeader)
	{
		CGuildManager::Instance().SendData(chLeader, chLeader->GetProtectTime("request.tabIndex"), chLeader->GetProtectTime("request.pageIndex"), NULL);
		if (isFromMaster)
			chLeader->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("758"));
	}

	if (isFirst)
	{
		std::unique_ptr<SQLMsg> pMsg(DBManager::instance().DirectQuery("DELETE FROM player.request_list WHERE pid = %d and guild_id = %d", pid, GetID()));

		TPacketGGGuild p;
		p.bHeader = HEADER_GG_GUILD;
		p.bSubHeader = GUILD_SUBHEADER_UPDATE_REQUEST;
		p.dwGuild = GetID();
		P2P_MANAGER::Instance().Send(&p, sizeof(p));
	}
}
void CGuild::LoadGuildRequestData(SQLMsg* pmsg)
{
	if (pmsg->Get()->uiNumRows == 0)
		return;
	m_request.clear();
	for (uint i = 0; i < pmsg->Get()->uiNumRows; ++i)
	{
		MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);

		TGuild_request p;
		str_to_number(p.pid, row[0]);
		strlcpy(p.name, row[1], sizeof(p.name));
		str_to_number(p.level, row[2]);
		str_to_number(p.race, row[3]);
		str_to_number(p.skillIndex, row[4]);
		m_request.emplace_back(p);
	}
}
#endif
