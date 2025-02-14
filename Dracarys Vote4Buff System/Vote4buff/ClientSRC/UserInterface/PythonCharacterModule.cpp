       //OptimistAdam\\
////---www.metin2hub.com---\\\


//Search
	PyModule_AddIntConstant(poModule, "NEW_AFFECT_DRAGON_SOUL_DECK1",		CInstanceBase::NEW_AFFECT_DRAGON_SOUL_DECK1);
	PyModule_AddIntConstant(poModule, "NEW_AFFECT_DRAGON_SOUL_DECK2",		CInstanceBase::NEW_AFFECT_DRAGON_SOUL_DECK2);

//add under
#ifdef ENABLE_VOTE_FOR_BONUS
	PyModule_AddIntConstant(poModule, "AFFECT_VOTEFORBONUS", CInstanceBase::AFFECT_VOTEFORBONUS);
#endif