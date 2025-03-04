quest pvp_duel_manager begin
	state start begin
		when login with pc.is_gm() begin
			send_letter("传送到 PvP 赛事")
		end
		when button or info begin
			if pc.is_gm() then
				say_title("Ronark 面板")
				say("")
				say("你想要传送吗？")
				local x = select("是的","取消")
				if x == 1 then
					pvp_duel_warpbase()
				else
					return
				end
			end
		end

		when 11001.chat."PvP Duel" or 11002.chat."PvP Duel" or 11003.chat."PvP Duel" with game.get_event_flag("pvp_duel_active") == 1 begin
			say_title(mob_name(11001))
			say("")
			say("你想要参加 PvP 赛事吗？")
			local x = select("是的，我想参加..", "不，谢谢..")
			if x == 1 then
				pvp_duel_warpbase()
			else
				return
			end
		end

		when 11001.chat."注册 PvP 赛事" begin
			say_title(mob_name(11001))
			say("")
			say("你想要注册 PvP 赛事吗？")
			local x = select("是的","取消")
			if x == 1 then
				
				local betMoney = pvp_duel_getflag("pvp_bet")
				if betMoney > 0 then
					say_title(mob_name(11001))
					say("")
					say("赛事有 "..betMoney.." 金币作为赌注")
					say("你仍然想要注册吗？")
					local z = select("是的，我想参加..", "不，谢谢..")
					if z != 1 then
						return
					end
				end
				say_title(mob_name(11001))
				say("")
				local returnValue = pvp_duel_register()
				if returnValue == 99 then--成功！
					say("你已成功注册！")
				elseif returnValue == 0 then--无描述！
					say("算法出现问题！")
				elseif returnValue == 1 then--事件未激活
					say("事件未激活！")
				elseif returnValue == 2 then--没有剩余注册时间
					say("注册时间已结束！")
				elseif returnValue == 3 then--达到最大注册人数
					say("注册人数已满！")
				elseif returnValue == 4 then--职业不同
					say("你的角色职业无法参加 PvP！")
				elseif returnValue == 5 then--等级小于最低要求
					say("你的等级低于最低要求！")
				elseif returnValue == 6 then--等级高于最高要求
					say("你的等级高于最高要求！")
				elseif returnValue == 7 then--地图索引不同
					say("你不能在其他地图注册！")
				elseif returnValue == 8 then--赌注不足
					say("你的赌注不足！")
				elseif returnValue == 9 then--已注册
					say("你已经用这个角色注册过了！")
				elseif returnValue == 10 then--同一IP已注册
					say("每台电脑只能注册一次！")
				end
			else
				return
			end
		end

		when 11001.chat."<GM> PvP 赛事状态设置" with pc.is_gm() begin
			say_title(mob_name(11001))
			say("")
			say("请选择你想要的操作")
			local x = select("开启事件","关闭事件", "取消")
			if x == 1 then
				cmdchat("OpenPvPDuelPanel")
			elseif x == 2 then
				pvp_duel_close()
				say("成功关闭！")
			else
				return
			end
		end

		when 11001.chat."<GM> PvP 赛事物品封锁" with pc.is_gm() begin
			say_title(mob_name(11001))
			say("")
			say("请选择你想要的操作。")
			local x = select("添加封锁物品","移除封锁物品","查看封锁物品", "取消")
			if x >= 1 and x <= 2 then
				say("请输入你想要的物品 VNUM！")
				local itemVnum = tostring(input(''))
				say("你确定要添加吗？")
				local z = select("是的","取消")
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
