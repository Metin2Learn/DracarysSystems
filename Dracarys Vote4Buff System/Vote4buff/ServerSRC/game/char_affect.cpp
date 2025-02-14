       //OptimistAdam\\
////---www.metin2hub.com---\\\



//search
int CHARACTER::ProcessAffect()
{
	bool	bDiff	= false;
//{...}
		else
			pkAff->lDuration = remain + 1;
	}

//add under
#ifdef ENABLE_VOTE_FOR_BONUS
	pkAff = FindAffect(AFFECT_VOTEFORBONUS);
	if (pkAff)
	{
		int32_t remain = pkAff->lDuration - get_global_time();
		if (remain <= 0)
		{
			RemoveAffect(AFFECT_VOTEFORBONUS);
			bDiff = true;
		}
	}
#endif