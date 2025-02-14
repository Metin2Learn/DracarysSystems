
quest pvp_duel_manager begin
	state start begin
		when login with pc.is_gm() begin
			send_letter("Warp to PvP Tournament")
		end
		when button or info begin
			if pc.is_gm() then
				say_title("Ronark Panel")
				say("")
				say("Do you want to warp?")
				local x = select("Yes","Cancel")
				if x == 1 then
					pvp_duel_warpbase()
				else
					return
				end
			end
		end

		when guild_war_observer1.chat."PvP Duel" or guild_war_observer2.chat."PvP Duel" or guild_war_observer3.chat."PvP Duel" with game.get_event_flag("pvp_duel_active") == 1 begin
			say_title(mob_name(11001))
			say("")
			say("Do you want join pvp duel?")
			local x = select("Yes, I want..", "No, thanks..")
			if x == 1 then
				pvp_duel_warpbase()
			else
				return
			end
		end

		when 60001.chat."Register PvP Duel" begin
			say_title(mob_name(60001))
			say("")
			say("Do you want to register pvp duel?")
			local x = select("Yes","Cancel")
			if x == 1 then
				
				local betMoney = pvp_duel_getflag("pvp_bet")
				if betMoney > 0 then
					say_title(mob_name(60001))
					say("")
					say("Duel has "..betMoney.." money for bet")
					say("Do you still want register?")
					local z = select("Yes, I want..", "No, thanks..")
					if z != 1 then
						return
					end
				end
				say_title(mob_name(60001))
				say("")
				local returnValue = pvp_duel_register()
				if returnValue == 99 then--successfully!
					say("You successfully register!")
				elseif returnValue == 0 then--no desc!
					say("Something wrong in algorithm!")
				elseif returnValue == 1 then--event not active
					say("Event not active!")
				elseif returnValue == 2 then--no left register time
					say("Register time done!")
				elseif returnValue == 3 then--max register
					say("Register count done!")
				elseif returnValue == 4 then--different job
					say("You can't join pvp with your character job!")
				elseif returnValue == 5 then--level < minlevel
					say("Your level lower than minimum level!")
				elseif returnValue == 6 then--level > maxlevel
					say("Your level bigger than max level!")
				elseif returnValue == 7 then--different mapindex
					say("You can't register with other map index!")
				elseif returnValue == 8 then--not enought bet price
					say("You don't have enought bet price!")
				elseif returnValue == 9 then--already register
					say("You already register with this character!")
				elseif returnValue == 10 then--already register with same ip!
					say("You can register only once for one computer!")
				end
			else
				return
			end
		end

		when 60001.chat."<GM> PvP Duel Status Settings" with pc.is_gm() begin
			say_title(mob_name(60001))
			say("")
			say("Select Your want")
			local x = select("Open Event","Close Event", "Cancel")
			if x == 1 then
				cmdchat("OpenPvPDuelPanel")
			elseif x == 2 then
				pvp_duel_close()
				say("Succesfully close!")
			else
				return
			end
		end

		when 60001.chat."<GM> PvP Duel Item Block" with pc.is_gm() begin
			say_title(mob_name(60001))
			say("")
			say("Select Your want.")
			local x = select("Add Block Item","Remove Block Item","Show Me Block Items", "Cancel")
			if x >= 1 and x <= 2 then
				say("Put your want item vnum!")
				local itemVnum = tostring(input(''))
				say("Do you want to put this?")
				local z = select("Yes","Cancel")
				if z == 1 then
					if x == 1 then
						pvp_duel_setflag(string.format("block_%s",itemVnum),1)
					elseif x == 2 then
						pvp_duel_setflag(string.format("block_%s",itemVnum),0)
					else
						return
					end
				else
					return
				end

			elseif x == 3 then
				pvp_duel_printblockitem()
			else
				return
			end
		end

	end
end
