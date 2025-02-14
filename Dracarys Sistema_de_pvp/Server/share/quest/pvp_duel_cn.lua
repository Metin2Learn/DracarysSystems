quest pvp_duel_manager begin
    state start begin
        when login with pc.is_gm() begin
            send_letter("传送到 PvP 竞技场")
        end
        when button or info begin
            if pc.is_gm() then
                say_title("罗纳克面板")
                say("")
                say("您想要传送吗？")
                local x = select("是", "取消")
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
            say("您想加入 PvP 竞技吗？")
            local x = select("是，我想加入..", "不，谢谢..")
            if x == 1 then
                pvp_duel_warpbase()
            else
                return
            end
        end

        when 60001.chat."注册 PvP 竞技" begin
            say_title(mob_name(60001))
            say("")
            say("您想注册 PvP 竞技吗？")
            local x = select("是", "取消")
            if x == 1 then
                local betMoney = pvp_duel_getflag("pvp_bet")
                if betMoney > 0 then
                    say_title(mob_name(60001))
                    say("")
                    say("该竞技有 "..betMoney.." 金币作为赌注")
                    say("您仍然想注册吗？")
                    local z = select("是，我想注册..", "不，谢谢..")
                    if z != 1 then
                        return
                    end
                end
                say_title(mob_name(60001))
                say("")
                local returnValue = pvp_duel_register()
                if returnValue == 99 then -- 成功注册！
                    say("您已成功注册！")
                elseif returnValue == 0 then -- 算法出错！
                    say("算法出错！")
                elseif returnValue == 1 then -- 事件未激活
                    say("事件未激活！")
                elseif returnValue == 2 then -- 注册时间已过
                    say("注册时间已结束！")
                elseif returnValue == 3 then -- 注册人数已满
                    say("注册人数已满！")
                elseif returnValue == 4 then -- 职业不匹配
                    say("您的职业无法参加 PvP 竞技！")
                elseif returnValue == 5 then -- 等级低于最低要求
                    say("您的等级低于最低要求！")
                elseif returnValue == 6 then -- 等级超过最高要求
                    say("您的等级高于最高要求！")
                elseif returnValue == 7 then -- 不同的地图索引
                    say("您不能在不同的地图上注册！")
                elseif returnValue == 8 then -- 赌注不足
                    say("您的赌注不足！")
                elseif returnValue == 9 then -- 已经注册过
                    say("您已经为此角色注册过了！")
                elseif returnValue == 10 then -- 相同 IP 注册
                    say("同一台电脑只能注册一次！")
                end
            else
                return
            end
        end

        when 60001.chat."<GM> PvP 竞技状态设置" with pc.is_gm() begin
            say_title(mob_name(60001))
            say("")
            say("请选择您想要的操作")
            local x = select("开启事件", "关闭事件", "取消")
            if x == 1 then
                cmdchat("OpenPvPDuelPanel")
            elseif x == 2 then
                pvp_duel_close()
                say("成功关闭！")
            else
                return
            end
        end

        when 60001.chat."<GM> PvP 竞技物品封锁" with pc.is_gm() begin
            say_title(mob_name(60001))
            say("")
            say("请选择您想要的操作")
            local x = select("添加封锁物品", "移除封锁物品", "查看封锁物品", "取消")
            if x >= 1 and x <= 2 then
                say("请输入您想要封锁的物品 VNUM！")
                local itemVnum = tostring(input(''))
                say("您确认要封锁这个物品吗？")
                local z = select("是", "取消")
                if z == 1 then
                    if x == 1 then
                        pvp_duel_setflag(string.format("block_%s", itemVnum), 1)
                    elseif x == 2 then
                        pvp_duel_setflag(string.format("block_%s", itemVnum), 0)
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
