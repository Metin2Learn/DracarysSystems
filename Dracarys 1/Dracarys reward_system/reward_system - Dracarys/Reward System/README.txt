-- dracaryS

I don't write reward check part because every server files function different..

But you adapt your server files with easy config.

Example in lua:

	game.set_reward(REWARD_INDEX)


	when 2493.kill with d.getf("soloDungeon") == 1 begin
		--REWARD_CRYSTAL_DRAGON=8,
		game.set_reward(8)
	end
	when levelup with pc.get_level() == 115 begin
		--REWARD_115=1
		game.set_reward(1)
	end
	when levelup with pc.get_level() == 120 begin
		--REWARD_120=3
		game.set_reward(3)
	end

Example in C++

	CHARACTER_MANAGER::Instance().SetRewardData(REWAR_INDEX , PLAYER_NAME, true);


	if(iNormalHitBonus>=60)
	{
		LPCHARACTER ch = pItem->GetOwner();
		if(ch)
			CHARACTER_MANAGER::Instance().SetRewardData(REWARD_AVERAGE,ch->GetName(), true);
	}
