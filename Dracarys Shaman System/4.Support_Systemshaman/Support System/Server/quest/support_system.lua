quest SupportSystem begin
	state start begin
		when 61020.use or 61021.use begin
			if get_global_time() > item.get_socket(4) then 
				syschat("Your support shaman time done!")
				return
			end
			if true == supports.is_summon(item.get_value(0)) then
				supports.unsummon(item.get_value(0))
			else
				supports.summon(item.get_value(0), "Support", false)
			end
		end

		when 61022.use or 61023.use begin
			if true == supports.is_summon(item.get_value(0)) then
				supports.unsummon(item.get_value(0))
			else
				if supports.count_summoned() < 1 then
					supports.summon(item.get_value(0), "Support", false)
				else
					syschat("Support shaman already active!")
				end
			end
		end
	end
end
