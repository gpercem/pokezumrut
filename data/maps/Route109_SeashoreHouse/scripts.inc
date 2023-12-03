Route109_SeashoreHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
	.byte 0

Route109_SeashoreHouse_OnTransition:
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
	end

Route109_SeashoreHouse_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
	setflag FLAG_TEMP_2
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_DefeatedTrainers::
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
	giveitem ITEM_SODA_POP, 6
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
	setflag FLAG_RECEIVED_6_SODA_POP
	release
	end

Route109_SeashoreHouse_EventScript_BagFull::
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
	showmoneybox 0, 0
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_BuySodaPop::
	checkmoney 300
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
	checkitemspace ITEM_SODA_POP
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
	removemoney 300
	updatemoneybox
	giveitem ITEM_SODA_POP
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughMoney::
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_NotEnoughSpace::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Route109_SeashoreHouse_EventScript_Dwayne::
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Johanna::
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_Simon::
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
	end

Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
	release
	end

Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
	release
	end

Route109_SeashoreHouse_Text_SeashoreHouseIntro:
	.string "LEBİDERYA EVİ'nin sahibi benim.\n"
	.string "Bana BAY DENİZ diyebilirsin!\p"
	.string "Her şeyden çok sevdiğim şey alevli\n"
	.string "savaşları izlemektir.\p"
	.string "Ruhunun ateşini görmek istiyorum!\p"
	.string "Eğer buradaki tüm eğitmenleri\n"
	.string "yenersen, emeklerini ödüllendiririm.$"

Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
	.string "Şöyle güzel savaşlar görelim senden!\p"
	.string "Bu LEBİDERYA EVİ'ni sırf bu yüzden\n"
	.string "açtım ve yönetiyorum!$"

Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
	.string "Alev alev yaktın ortalığı!\n"
	.string "Savaşların harika ötesiydi!\p"
	.string "Bu savaşların için sana bunları\n"
	.string "hediye etmek istiyorum…\p"
	.string "Yarım düzine SODA POP. Senindir!$"

Route109_SeashoreHouse_Text_BagFull:
	.string "Ee, hey hey. Çantan doluymuş.\n"
	.string "Çantanı boşaltana kadar\nsaklayabilirim.$"

Route109_SeashoreHouse_Text_WantToBuySodaPop:
	.string "SODA POP almak ister misin?\n"
	.string "POKéMON'lar buna bayılırlar!\p"
	.string "Şişesi ¥300!\n"
	.string "Çekinme, al biraz!$"

Route109_SeashoreHouse_Text_HereYouGo:
	.string "Al bakalım!$"

Route109_SeashoreHouse_Text_NotEnoughMoney:
	.string "Yeterli paran yok.$"

Route109_SeashoreHouse_Text_ThatsTooBad:
	.string "Hayır mı?\n"
	.string "Nasıl istersen.$"

Route109_SeashoreHouse_Text_DwayneIntro:
	.string "LEBİDERYA EVİ'nde savaş yapmak\n"
	.string "istiyorsan, benden daha ateşli\l"
	.string "bir eğitmen bulamazsın, canım!$"

Route109_SeashoreHouse_Text_DwayneDefeated:
	.string "Çok sıcak bir savaştı!\n"
	.string "Tebrik ediyorum, canım!$"

Route109_SeashoreHouse_Text_DwaynePostBattle:
	.string "SLATEPORT'a gelince durup buz gibi\n"
	.string "SODA POP almaya ve alev alev\lsavaşlar yapmaya bayılıyorum!$"

Route109_SeashoreHouse_Text_JohannaIntro:
	.string "Sıkıcı savaşlara girmeye değmez bile.\p"
	.string "Asıl böyle zorlu savaşlar POKéMON'ları\n"
	.string "ve eğitmenleri geliştirir!$"

Route109_SeashoreHouse_Text_JohannaDefeated:
	.string "Alev alev!$"

Route109_SeashoreHouse_Text_JohannaPostBattle:
	.string "Uf, amma susadım.\n"
	.string "Gidip SODA POP alacağım.$"

Route109_SeashoreHouse_Text_SimonIntro:
	.string "Sana POKéMON'larımın gücünü\n"
	.string "göstereceğim, ağlama sakın!$"

Route109_SeashoreHouse_Text_SimonDefeated:
	.string "…Kaybettim, ama ağlamak yok…$"

Route109_SeashoreHouse_Text_SimonPostBattle:
	.string "Eğer POKéMON'larımdan biri su\n"
	.string "üstünde yüzdürebilme saldırısını\l"
	.string "bilseydi, üstünde yüzerdim ve şu\lsimitten kurtulurdum.$"

