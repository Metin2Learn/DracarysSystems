# Search

	m_bOpeningSafebox = false;

# Add after

#ifdef __RENEWAL_BRAVE_CAPE__
	m_pkBraveCapeEvent = NULL;
#endif

# search

	event_cancel(&m_pkMiningEvent);

# add after

#ifdef __RENEWAL_BRAVE_CAPE__
	event_cancel(&m_pkBraveCapeEvent);
#endif


# Add

#ifdef __RENEWAL_BRAVE_CAPE__
struct FuncAggregateMonsterNew
{
	LPCHARACTER m_ch;
	int m_dwRange;
	FuncAggregateMonsterNew(LPCHARACTER ch, int range) : m_ch(ch), m_dwRange(range){}
	void operator()(LPENTITY ent)
	{
		if (ent->IsType(ENTITY_CHARACTER))
		{
			LPCHARACTER ch = (LPCHARACTER)ent;
			if (!ch->IsMonster() || ch->GetVictim())
				return;
			if (DISTANCE_APPROX(ch->GetX() - m_ch->GetX(), ch->GetY() - m_ch->GetY()) < m_dwRange)
			{
				if (ch->CanBeginFight())
					ch->BeginFight(m_ch);
			}
		}
	}
};
EVENTFUNC(brave_cape_event)
{
	char_event_info* info = dynamic_cast<char_event_info*>(event->info);
	if (info == NULL)
	{
		sys_err("<brave_cape_event> <Factor> Null pointer");
		return 0;
	}
	LPCHARACTER	ch = info->ch;
	if (ch == NULL)
		return 0;
	if (!ch->FindAffect(AFFECT_BRAVE_CAPE))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Brave affect is done loop event closed.");
		ch->m_pkBraveCapeEvent = NULL;
		return 0;
	}
	LPSECTREE pSec = ch->GetSectree();
	if (pSec)
	{
		FuncAggregateMonsterNew f(ch, ch->GetProtectTime("brave_cape_range"));
		pSec->ForEachAround(f);
	}
	return PASSES_PER_SEC(ch->GetProtectTime("brave_cape_time"));
}
void CHARACTER::GetBraveCapeCMDCompare(const char* c_pszArgument)
{
	std::vector<std::string> vecArgs;
	split_argument(c_pszArgument, vecArgs);
	if (vecArgs.size() < 2) { return; }
	else if (vecArgs[1] == "active")
	{
		if (vecArgs.size() < 4) { return; }
		if (!FindAffect(AFFECT_BRAVE_CAPE))
		{
			ChatPacket(CHAT_TYPE_INFO, "You don't has brave cape affect.");
			return;
		}
		if (m_pkBraveCapeEvent)
		{
			ChatPacket(CHAT_TYPE_INFO, "Already brave cape working..");
			return;
		}
		const std::vector<WORD> m_dwBlockedMapIdx = { 1, 21, 41 };
		if (std::find(m_dwBlockedMapIdx.begin(), m_dwBlockedMapIdx.end(), GetMapIndex()) != m_dwBlockedMapIdx.end())
		{
			ChatPacket(CHAT_TYPE_INFO, "You can't use brave cape on this map!");
			return;
		}

		int loopTime, eventRange;
		if (!str_to_number(loopTime, vecArgs[2].c_str()) || !str_to_number(eventRange, vecArgs[3].c_str()))
			return;

		if (loopTime < 2 || loopTime > 60 || eventRange < 1000 || eventRange > 15000)
			return;

		SetProtectTime("brave_cape_time", loopTime);
		SetProtectTime("brave_cape_range", eventRange);

		char_event_info* info = AllocEventInfo<char_event_info>();
		info->ch = this;
		m_pkBraveCapeEvent = event_create(brave_cape_event, info, 0);
		ChatPacket(CHAT_TYPE_COMMAND, "SetBraveCapeStatus 1");
		ChatPacket(CHAT_TYPE_INFO, "Brave cape event started..");

	}
	else if (vecArgs[1] == "deactive")
	{
		if (!m_pkBraveCapeEvent)
		{
			ChatPacket(CHAT_TYPE_INFO, "You don't has brave cape loop event!");
			return;
		}
		SetProtectTime("brave_cape_time", 0);
		SetProtectTime("brave_cape_range", 0);
		event_cancel(&m_pkBraveCapeEvent);
		m_pkBraveCapeEvent = NULL;
		ChatPacket(CHAT_TYPE_INFO, "Brave cape event closed..");
		ChatPacket(CHAT_TYPE_COMMAND, "SetBraveCapeStatus 0");
	}
}
#endif

