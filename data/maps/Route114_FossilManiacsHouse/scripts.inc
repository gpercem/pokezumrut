Route114_FossilManiacsHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_FossilManiacsHouse_OnTransition
	.byte 0

Route114_FossilManiacsHouse_OnTransition:
	setflag FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE
	end

Route114_FossilManiacsHouse_EventScript_FossilManiacsBrother::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM28, Route114_FossilManiacsHouse_EventScript_ReceivedDig
	msgbox Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother, MSGBOX_DEFAULT
	giveitem ITEM_TM28
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM28
	release
	end

Route114_FossilManiacsHouse_EventScript_ReceivedDig::
	msgbox Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance, MSGBOX_DEFAULT
	release
	end

Route114_FossilManiacsHouse_EventScript_RockDisplay::
	msgbox Route114_FossilManiacsHouse_Text_RocksFillDisplayCase, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_EventScript_Bookshelf::
	msgbox Route114_FossilManiacsHouse_Text_CrammedWithBooks, MSGBOX_SIGN
	end

Route114_FossilManiacsHouse_Text_HaveThisToDigLikeMyBrother:
	.string "Abim fosil manyağıdır…\nFOSİLLERİ seven iyi bir adamdır…\pÇukur kazmayı da çok seviyor…\nBu çukuru tek başına kazdı…\pBunu alabilirsin, böylece sen de\nabim gibi delik açabilirsin.$"

Route114_FossilManiacsHouse_Text_DigReturnsYouToEntrance:
	.string "Eğer bir mağaranın içinde DİG\nkullanırsan, girişe geri dönersin…$"

Route114_FossilManiacsHouse_Text_RocksFillDisplayCase:
	.string "Tuhaf şekillerdeki kayalar rafları\ndolduruyor…$"

Route114_FossilManiacsHouse_Text_CrammedWithBooks:
	.string "TABAKALARIN BİRLEŞİMİ…\nYAĞMURUN TOPRAĞI ŞEKİLLENDİRMESİ…\lTAŞLAR, TOPRAK VE KAYA…\pBu tür kitaplarla dolu.$"


