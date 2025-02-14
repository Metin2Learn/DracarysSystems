quest vote4bonus begin
	state start begin
		when letter begin
			send_letter(gameforge[pc.get_language()].vote4bonus._1)
		end

		when button or info begin
			local lang = pc.get_language()
			say_title(string.format("%s:", gameforge[lang].vote4bonus._1))
			say("")
			local r = pc.can_get_bonus_vote()
			if r == 0 then
				say(gameforge[lang].common.unknownerr)
				return
			elseif r == 1 then
				say(gameforge[lang].vote4bonus._8)
				return
			end
			
			if r == 2 then
				say(gameforge[lang].vote4bonus._2)
				say(gameforge[lang].vote4bonus._3)
			elseif r == 3 then
				say(gameforge[lang].vote4bonus._4)
				local b = select(gameforge[lang].vote4bonus._5, gameforge[lang].vote4bonus._6, gameforge[lang].vote4bonus._7, gameforge[lang].common.cancel)
				if b == 4 then
					return
				end
				
				say_title(string.format("%s:", gameforge[lang].vote4bonus._1))
				say("")
				local a = pc.set_bonus_for_vote(b)
				if a == 1 then
					say(gameforge[lang].vote4bonus._8)
				elseif a == 2 then
					say(gameforge[lang].vote4bonus._9)
					say_reward(gameforge[lang].vote4bonus._5)
				elseif a == 3 then
					say(gameforge[lang].vote4bonus._9)
					say_reward(gameforge[lang].vote4bonus._6)
				elseif a == 4 then
					say(gameforge[lang].vote4bonus._9)
					say_reward(gameforge[lang].vote4bonus._7)
				else
					say(gameforge[lang].common.unknownerr)
				end
			else
				say(gameforge[lang].common.unknownerr)
			end
		end
	end
end

