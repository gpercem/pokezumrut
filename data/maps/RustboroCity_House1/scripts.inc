RustboroCity_House1_MapScripts::
	.byte 0

RustboroCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	updatefollowerpokemongraphic
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
	release
	end

RustboroCity_House1_EventScript_DeclineTrade::
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_TradeCompleted::
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
	release
	end

RustboroCity_House1_EventScript_Hiker::
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
	end

RustboroCity_House1_Text_IllTradeIfYouWant:
	.string "Ne? POKéMON'um sevimli mi? Elbette, bunu\nbiliyordum.\pAma eğer gerçekten istiyorsan, seninle\ntakas etmeye hazırım.\pİstersen {STR_VAR_2}'mi bir\n{STR_VAR_1} ile takas edebilirim.$"

RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
	.string "Eheheh…\nLütfen POKéMON'uma iyi davran.$"

RustboroCity_House1_Text_DoesntLookLikeMonToMe:
	.string "Ha? Bu bana {STR_VAR_1} gibi\ngelmedi.$"

RustboroCity_House1_Text_YouDontWantToThatsOkay:
	.string "Eğer istemiyorsan, sorun değil.\nAma POKéMON'um çok şirindir.$"

RustboroCity_House1_Text_AnyPokemonCanBeCute:
	.string "Eğer özenle ve şefkatle\nyetiştirirsen her POKéMON sevimli\lolabilir.$"

RustboroCity_House1_Text_AllSortsOfPlaces:
	.string "Her yerde, her türlü POKéMON'lar ve\ninsanlar vardır.\pBunu büyüleyici buluyorum, bu yüzden\nher yere gidiyorum.$"


