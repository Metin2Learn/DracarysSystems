-- author: dracaryS
-- __test_dungeon__

quest deviltower_zone begin
	state start begin

		when 20348.chat."Test Dungeon" begin
			say_title(mob_name(20348))
			say("")
			say("Test dungeon for re-join algorithm.")
			local selectedIdx = select("Enter Dungeon", "Cancel")
			if selectedIdx == 1 then
				pc.warp(216500,727000)
			end
		end

		when kill with npc.get_race() == 8015 and pc.get_map_index() == 66 begin
			timer("devil_1_floor", 6)
		end

		when devil_1_floor.timer with pc.get_map_index() == 66 begin
			d.new_jump_all(66, 2048+126, 6656+384)
			d.setf("level", 2)
			d.setf("can_back_dungeon", 1) -- active back dungeon when first enter!
			d.regen_file("data/dungeon/deviltower/2_regen.txt")
		end

		when login with pc.get_map_index() >= 660000 and pc.get_map_index() <= 669999 begin
			pc.set_warp_location(65, 5905, 1105)
		end
		
		when 1093.kill with pc.get_map_index() >= 660000 and pc.get_map_index() <= 669999 begin
			d.setf("can_back_dungeon", 0) -- deactive back dungeon after dungeon done!
		end

	end
end


