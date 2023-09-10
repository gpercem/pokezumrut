SSTidalLowerDeck_MapScripts::
	.byte 0

SSTidalLowerDeck_EventScript_Phillip::
	trainerbattle_single TRAINER_PHILLIP, SSTidalLowerDeck_Text_PhillipIntro, SSTidalLowerDeck_Text_PhillipDefeat
	msgbox SSTidalLowerDeck_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_EventScript_Leonard::
	trainerbattle_single TRAINER_LEONARD, SSTidalLowerDeck_Text_LeonardIntro, SSTidalLowerDeck_Text_LeonardDefeat
	msgbox SSTidalLowerDeck_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_Text_PhillipIntro:
	.string "Arrrh!\nBu kocaman yeri temizlemekten\lbıktım usandım!\pHadi hızlı bir savaş yapalım!$"

SSTidalLowerDeck_Text_PhillipDefeat:
	.string "Küçük kardeşim, ben kaybettim!$"

SSTidalLowerDeck_Text_PhillipPostBattle:
	.string "Biz temiz kardeşleriz!\pYaşlı olan deterjanı döker, genç olan\nda fırçalar!$"

SSTidalLowerDeck_Text_LeonardIntro:
	.string "Burası geminin gövdesinin dibi.\nBolca yer var.\lBir POKéMON savaşı iyi gider.$"

SSTidalLowerDeck_Text_LeonardDefeat:
	.string "Abi, ben kaybettim!$"

SSTidalLowerDeck_Text_LeonardPostBattle:
	.string "Biz temiz kardeşleriz!\pYaşlı olan deterjanı döker, genç olan\nda fırçalar!$"


