
when reward_check begin
	state start begin
		when levelup with pc.get_level() == 115 begin
			--REWARD_115=1
			game.set_reward(1)
		end
		when levelup with pc.get_level() == 120 begin
			--REWARD_120=3
			game.set_reward(3)
		end
	end
end
