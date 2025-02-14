# Search

	g->SetLadderPoint(p->lLadderPoint);
	g->SetWarData(p->lWin, p->lDraw, p->lLoss);

# Add after

#ifdef ENABLE_GUILD_REQUEST
	CGuildManager::Instance().SortGuildCache();
#endif