FortreeCity_House2_MapScripts::
	.byte 0

FortreeCity_House2_EventScript_HiddenPowerGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM10, FortreeCity_House2_EventScript_ExplainHiddenPower
	call_if_unset FLAG_MET_HIDDEN_POWER_GIVER, FortreeCity_House2_EventScript_Greeting
	msgbox FortreeCity_House2_Text_CoinInWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 1, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_CorrectTryAgainWhichHand2, MSGBOX_DEFAULT
	multichoice 21, 8, MULTI_RIGHTLEFT, TRUE
	switch VAR_RESULT
	case 0, FortreeCity_House2_EventScript_WrongGuess
	msgbox FortreeCity_House2_Text_YourHiddenPowerHasAwoken, MSGBOX_DEFAULT
	giveitem ITEM_TM10
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM10
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_Greeting::
	msgbox FortreeCity_House2_Text_HiddenPowersArousedByNature, MSGBOX_DEFAULT
	setflag FLAG_MET_HIDDEN_POWER_GIVER
	return

FortreeCity_House2_EventScript_ExplainHiddenPower::
	msgbox FortreeCity_House2_Text_ExplainHiddenPower, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_EventScript_WrongGuess::
	msgbox FortreeCity_House2_Text_YouGuessedWrong, MSGBOX_DEFAULT
	release
	end

FortreeCity_House2_Text_HiddenPowersArousedByNature:
	.string "İnsanlar… POKéMONLAR…\p"
	.string "Onların saklı olan güçleri\n"
	.string "doğal çevrelerinin içinde barınıyor…$"

FortreeCity_House2_Text_CoinInWhichHand:
	.string "İçindeki gizli gücü uyandırması için\n"
	.string "bu yaşlı kadına izin ver…\p"
	.string "Bir elimde para var.\p"
	.string "Şimdi söyle, Hangi elimde?\n"
	.string "sağ mı? yoksa sol mu?$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand:
	.string "Ah! Evet, doğru!\p"
	.string "Şimdi tekrar deneyelim.\p"
	.string "Parayı hangi elimde sakladım?\n"
	.string "Sağ mı yoksa sol mu?$"

FortreeCity_House2_Text_CorrectTryAgainWhichHand2:
	.string "Ah! Evet, doğru!\p"
	.string "Şimdi tekrar deneyelim.\p"
	.string "Parayı hangi elimde sakladım?\n"
	.string "Sağ mı yoksa sol mu?$"

FortreeCity_House2_Text_YourHiddenPowerHasAwoken:
	.string "Ah! Harika!\n"
	.string "Gizli gücün uyandı!\p"
	.string "İşte, bunu al ve POKéMON'unun\n"
	.string "gizli gücünü açığa çıkar.$"

FortreeCity_House2_Text_ExplainHiddenPower:
	.string "GİZLİ GÜÇ, POKéMON'unla beraber\n"
	.string "farklılık gösteren bir harekettir.$"

FortreeCity_House2_Text_YouGuessedWrong:
	.string "Hayır, bu yanlış.\n"
	.string "Yanlış bildin.$"

