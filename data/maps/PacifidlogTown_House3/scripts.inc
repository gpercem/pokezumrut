PacifidlogTown_House3_MapScripts::
	.byte 0

PacifidlogTown_House3_EventScript_Trader::
	lock
	faceplayer
	goto_if_set FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED, PacifidlogTown_House3_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_HORSEA
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox PacifidlogTown_House3_Text_WillingToTradeIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PacifidlogTown_House3_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, PacifidlogTown_House3_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, PacifidlogTown_House3_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	updatefollowerpokemongraphic
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou, MSGBOX_DEFAULT
	setflag FLAG_PACIFIDLOG_NPC_TRADE_COMPLETED
	release
	end

PacifidlogTown_House3_EventScript_DeclineTrade::
	msgbox PacifidlogTown_House3_Text_NotDesperateOrAnything, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_TradeCompleted::
	msgbox PacifidlogTown_House3_Text_ReallyWantedToGetBagon, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House3_EventScript_Girl::
	msgbox PacifidlogTown_House3_Text_IsThatAPokedex, MSGBOX_NPC
	end

PacifidlogTown_House3_Text_WillingToTradeIt:
	.string "Şu {STR_VAR_2}'a bak!\pBu dün doğum günümü kutlamak için\nyakaladığım {STR_VAR_2}!\pOnu istediğini biliyorum!\nNe de olsa paha biçilemez!\pBak sana ne diyeceğim. Onu bir\n{STR_VAR_1} ile takas edebilirim.$"

PacifidlogTown_House3_Text_ItsSubtlyDifferentThankYou:
	.string "Bu bir {STR_VAR_1} mi?\pBir tür {STR_VAR_2} gibi ama yine de\nnedense farklı duruyor.\pTeşekkür ederim!$"

PacifidlogTown_House3_Text_WontAcceptAnyLessThanRealMon:
	.string "Hayır, hayır, hayır!\nGerçek bir {STR_VAR_1} olmayan\lhiçbir şeyi kabul etmem!$"

PacifidlogTown_House3_Text_NotDesperateOrAnything:
	.string "Yani takas yapmacak mıyız?\pSorun değil.\nTakas için yalvarmıyorum sonuçta.$"

PacifidlogTown_House3_Text_ReallyWantedToGetBagon:
	.string "Kendi başıma arayabileceğimi\nbiliyorum ama…\pAma başka bir ANTRENÖRÜN yakaladığı\nbir BAGON'u gerçekten almak istedim…$"

PacifidlogTown_House3_Text_IsThatAPokedex:
	.string "Bu bir POKéDEX mi?\nBir sürü farklı POKéMON'la tanıştın mı?\pKeşke ben de senin gibi olsaydım.$"


