quest pvp_duel_manager begin
	state start begin
		when login with pc.is_gm() begin
			send_letter("���͵� PvP ����")
		end
		when button or info begin
			if pc.is_gm() then
				say_title("Ronark ���")
				say("")
				say("����Ҫ������")
				local x = select("�ǵ�","ȡ��")
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
			say("����Ҫ�μ� PvP ������")
			local x = select("�ǵģ�����μ�..", "����лл..")
			if x == 1 then
				pvp_duel_warpbase()
			else
				return
			end
		end

		when 11001.chat."ע�� PvP ����" begin
			say_title(mob_name(11001))
			say("")
			say("����Ҫע�� PvP ������")
			local x = select("�ǵ�","ȡ��")
			if x == 1 then
				
				local betMoney = pvp_duel_getflag("pvp_bet")
				if betMoney > 0 then
					say_title(mob_name(11001))
					say("")
					say("������ "..betMoney.." �����Ϊ��ע")
					say("����Ȼ��Ҫע����")
					local z = select("�ǵģ�����μ�..", "����лл..")
					if z != 1 then
						return
					end
				end
				say_title(mob_name(11001))
				say("")
				local returnValue = pvp_duel_register()
				if returnValue == 99 then--�ɹ���
					say("���ѳɹ�ע�ᣡ")
				elseif returnValue == 0 then--��������
					say("�㷨�������⣡")
				elseif returnValue == 1 then--�¼�δ����
					say("�¼�δ���")
				elseif returnValue == 2 then--û��ʣ��ע��ʱ��
					say("ע��ʱ���ѽ�����")
				elseif returnValue == 3 then--�ﵽ���ע������
					say("ע������������")
				elseif returnValue == 4 then--ְҵ��ͬ
					say("��Ľ�ɫְҵ�޷��μ� PvP��")
				elseif returnValue == 5 then--�ȼ�С�����Ҫ��
					say("��ĵȼ��������Ҫ��")
				elseif returnValue == 6 then--�ȼ��������Ҫ��
					say("��ĵȼ��������Ҫ��")
				elseif returnValue == 7 then--��ͼ������ͬ
					say("�㲻����������ͼע�ᣡ")
				elseif returnValue == 8 then--��ע����
					say("��Ķ�ע���㣡")
				elseif returnValue == 9 then--��ע��
					say("���Ѿ��������ɫע����ˣ�")
				elseif returnValue == 10 then--ͬһIP��ע��
					say("ÿ̨����ֻ��ע��һ�Σ�")
				end
			else
				return
			end
		end

		when 11001.chat."<GM> PvP ����״̬����" with pc.is_gm() begin
			say_title(mob_name(11001))
			say("")
			say("��ѡ������Ҫ�Ĳ���")
			local x = select("�����¼�","�ر��¼�", "ȡ��")
			if x == 1 then
				cmdchat("OpenPvPDuelPanel")
			elseif x == 2 then
				pvp_duel_close()
				say("�ɹ��رգ�")
			else
				return
			end
		end

		when 11001.chat."<GM> PvP ������Ʒ����" with pc.is_gm() begin
			say_title(mob_name(11001))
			say("")
			say("��ѡ������Ҫ�Ĳ�����")
			local x = select("��ӷ�����Ʒ","�Ƴ�������Ʒ","�鿴������Ʒ", "ȡ��")
			if x >= 1 and x <= 2 then
				say("����������Ҫ����Ʒ VNUM��")
				local itemVnum = tostring(input(''))
				say("��ȷ��Ҫ�����")
				local z = select("�ǵ�","ȡ��")
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
