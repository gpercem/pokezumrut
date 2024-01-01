BattleFrontier_Lounge6_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_MEOWTH
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox BattleFrontier_Lounge6_Text_WouldYouLikeToTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge6_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge6_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, BattleFrontier_Lounge6_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	updatefollowerpokemongraphic
	msgbox BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt, MSGBOX_DEFAULT
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade:
	.string "Benim POKéMON'um bir {STR_VAR_2}. Onu\ntanıyor musun? Oldukça şirin ve hoş\lbir şey.\pBu ufaklıkla gururla takas\nyapabilirim!\pBenim {STR_VAR_2}'me karşılık bir\n{STR_VAR_1} takas etmek ister misin?$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt:
	.string "Oh, bu çok güzel! Teşekkür ederim! Ona\niyi davranacağıma söz veriyorum!\pUmarım {STR_VAR_2}'me de iyi\ndavranırsın!$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon:
	.string "Oh, özür dilerim! Bir {STR_VAR_1}\ndışında başka bir şeyle takas etme\lniyetinde değilim.$"

BattleFrontier_Lounge6_Text_WellThatsFineToo:
	.string "Oh, yapmayacak mısın? O zaman bu da\niyi. Lütfen bizi tekrar ziyaret edin.$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined:
	.string "Hahah! Bir SKITTY hayal\nettiğimden çok daha şirin. Çok\lsevindim!$"
