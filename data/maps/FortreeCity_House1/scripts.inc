FortreeCity_House1_MapScripts::
	.byte 0

FortreeCity_House1_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_FORTREE_NPC_TRADE_COMPLETED, FortreeCity_House1_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_PLUSLE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox FortreeCity_House1_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, FortreeCity_House1_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, FortreeCity_House1_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, FortreeCity_House1_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	updatefollowerpokemongraphic
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_MonYouTakeCare, MSGBOX_DEFAULT
	setflag FLAG_FORTREE_NPC_TRADE_COMPLETED
	release
	end

FortreeCity_House1_EventScript_DeclineTrade::
	msgbox FortreeCity_House1_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox FortreeCity_House1_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_TradeCompleted::
	msgbox FortreeCity_House1_Text_GoingToMakeVolbeatStrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House1_EventScript_ExpertF::
	msgbox FortreeCity_House1_Text_TradingMemoriesWithOthers, MSGBOX_NPC
	end

FortreeCity_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House1_Text_YouWillTradeWontYou:
	.string "Voaaahh! Ona ihtiyacım var!\n"
	.string "Bana bir {STR_VAR_1} getirmen gerek!\l"
	.string "Bunun için herşeyi yaparım!\p"
	.string "…Ah… Bunu duydun mu?\n"
	.string "Yüreğimin derinliklerinden\lhaykırdığımı?\p"
	.string "Bunu duydun, takas yapacak mısın?\n"
	.string "Senin {STR_VAR_1}'in için benim\l{STR_VAR_2}'im, var mısın?$"

FortreeCity_House1_Text_MonYouTakeCare:
	.string "Ah... evet, işte bu!\p"
	.string "{STR_VAR_1}, hoş geldin!\n"
	.string "{STR_VAR_2}, kendine iyi bak!$"

FortreeCity_House1_Text_ThisIsntAMon:
	.string "Ah... hayır, bu doğru değil.\n"
	.string "Bu bir {STR_VAR_1} değil.$"

FortreeCity_House1_Text_YouWontTradeMe:
	.string "Hayır? Takas yapmayacak mısın?\n"
	.string "Hem de sana kalbimi açmama rağmen?$"

FortreeCity_House1_Text_GoingToMakeVolbeatStrong:
	.string "Şu andan itibaren VOLBEAT'imi\n"
	.string "daha güçlü yapmaya çalışacağım!\p"
	.string "Umarım sen de PLUSLE için bunu yaparsın!$"

FortreeCity_House1_Text_TradingMemoriesWithOthers:
	.string "POKéMON'unu başkaları ile takas etmek…\p"
	.string "Anılarını başkalarının anıları ile\n"
	.string "takas etmek gibi birşey.$"

FortreeCity_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Gumomoh?$"

