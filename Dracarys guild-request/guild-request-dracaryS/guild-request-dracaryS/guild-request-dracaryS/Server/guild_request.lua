quest guild_request begin
	state start begin
		when 11000.chat."Guild Request" or 11002.chat."Guild Request" or 11004.chat."Guild Request" begin
			cmdchat("OpenGuildRequest")
			setskin(NOWINDOW)
		end
	end
end
