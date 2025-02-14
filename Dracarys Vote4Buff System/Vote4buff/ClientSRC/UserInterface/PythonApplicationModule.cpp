       //OptimistAdam\\
////---www.metin2hub.com---\\\


//add 

#ifdef ENABLE_VOTE_FOR_BONUS
	PyModule_AddIntConstant(poModule, "ENABLE_VOTE_FOR_BONUS", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_VOTE_FOR_BONUS", 0);
#endif