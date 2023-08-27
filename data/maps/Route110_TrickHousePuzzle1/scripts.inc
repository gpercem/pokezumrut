Route110_TrickHousePuzzle1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route110_TrickHousePuzzle1_OnLoad
	.byte 0

Route110_TrickHousePuzzle1_OnLoad:
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 2, Route110_TrickHousePuzzle1_EventScript_OpenDoor
	end

Route110_TrickHousePuzzle1_EventScript_OpenDoor::
	setmetatile 13, 1, METATILE_TrickHousePuzzle_Stairs_Down, FALSE
	end

Route110_TrickHousePuzzle1_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_1_STATE, 0, Route110_TrickHousePuzzle1_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle1_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_1_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle1_EventScript_Sally::
	trainerbattle_single TRAINER_SALLY, Route110_TrickHousePuzzle1_Text_SallyIntro, Route110_TrickHousePuzzle1_Text_SallyDefeat
	msgbox Route110_TrickHousePuzzle1_Text_SallyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Eddie::
	trainerbattle_single TRAINER_EDDIE, Route110_TrickHousePuzzle1_Text_EddieIntro, Route110_TrickHousePuzzle1_Text_EddieDefeat
	msgbox Route110_TrickHousePuzzle1_Text_EddiePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_EventScript_Robin::
	trainerbattle_single TRAINER_ROBIN, Route110_TrickHousePuzzle1_Text_RobinIntro, Route110_TrickHousePuzzle1_Text_RobinDefeat
	msgbox Route110_TrickHousePuzzle1_Text_RobinPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle1_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} kapıdaki gizli kodu yazdı.\pTRICK MASTER muhteşem. … … … … …\n… … …\pKilit açıldı!$"

Route110_TrickHousePuzzle1_Text_SallyIntro:
	.string "Yeni öğrendiğim kesme saldırısı ile\nzafere giden yolu kesip biçeceğim!$"

Route110_TrickHousePuzzle1_Text_SallyDefeat:
	.string "Neden bu kadar ciddisin?$"

Route110_TrickHousePuzzle1_Text_SallyPostBattle:
	.string "Kesip biçmekten asla yorulmam!$"

Route110_TrickHousePuzzle1_Text_EddieIntro:
	.string "Kazara bu garip eve girdim.$"

Route110_TrickHousePuzzle1_Text_EddieDefeat:
	.string "Ve şimdi kaybettim.$"

Route110_TrickHousePuzzle1_Text_EddiePostBattle:
	.string "Yolumu kaybettim, bir savaşı kaybettim\nve şimdi daha da kaybolmuş\ldurumdayım… Çıkamıyorum…$"

Route110_TrickHousePuzzle1_Text_RobinIntro:
	.string "Numara ustası kim?$"

Route110_TrickHousePuzzle1_Text_RobinDefeat:
	.string "Düşüncelerimde kaybolmuşken\nkaybettim!$"

Route110_TrickHousePuzzle1_Text_RobinPostBattle:
	.string "Sen güçlüsün!\nKimsin sen?$"


