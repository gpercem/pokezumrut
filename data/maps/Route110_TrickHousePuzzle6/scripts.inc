Route110_TrickHousePuzzle6_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_TrickHousePuzzle6_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route110_TrickHousePuzzle6_OnWarp
	.byte 0

Route110_TrickHousePuzzle6_OnTransition:
	special RotatingGate_InitPuzzle
	end

Route110_TrickHousePuzzle6_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, Route110_TrickHousePuzzle6_EventScript_InitPuzzle
	.2byte 0

Route110_TrickHousePuzzle6_EventScript_InitPuzzle::
	special RotatingGate_InitPuzzleAndGraphics
	end

Route110_TrickHousePuzzle6_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_6_STATE, 0, Route110_TrickHousePuzzle6_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle6_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_6_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle6_EventScript_Sophia::
	trainerbattle_single TRAINER_SOPHIA, Route110_TrickHousePuzzle6_Text_SophiaIntro, Route110_TrickHousePuzzle6_Text_SophiaDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SophiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Benny::
	trainerbattle_single TRAINER_BENNY, Route110_TrickHousePuzzle6_Text_BennyIntro, Route110_TrickHousePuzzle6_Text_BennyDefeat
	msgbox Route110_TrickHousePuzzle6_Text_BennyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_EventScript_Sebastian::
	trainerbattle_single TRAINER_SEBASTIAN, Route110_TrickHousePuzzle6_Text_SebastianIntro, Route110_TrickHousePuzzle6_Text_SebastianDefeat
	msgbox Route110_TrickHousePuzzle6_Text_SebastianPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle6_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} kapıdaki gizli kodu yazdı.\pHİLE USTASI benim hayatım. … … …\n… … … … …\pKilit açıldı!$"

Route110_TrickHousePuzzle6_Text_SophiaIntro:
	.string "Tuhaf bir ev olduğunu duyduğumda,\nkontrol etmem gerekti.$"

Route110_TrickHousePuzzle6_Text_SophiaDefeat:
	.string "Zorlu bir EĞİTMEN keşfettim!$"

Route110_TrickHousePuzzle6_Text_SophiaPostBattle:
	.string "Burayı kontrol ederken iyi vakit\ngeçirdiğime eminim.\pTekrar etmeye değer bulduğum bir\nmeydan okuma!$"

Route110_TrickHousePuzzle6_Text_BennyIntro:
	.string "Belki KUŞ POKEMON'umu duvarın\nüzerinden uçurabilirim.$"

Route110_TrickHousePuzzle6_Text_BennyDefeat:
	.string "Gvaaah! Patlattım!$"

Route110_TrickHousePuzzle6_Text_BennyPostBattle:
	.string "Ehehehe… Sanırım hile yapmaya\nçalıştığım için kaybettim.$"

Route110_TrickHousePuzzle6_Text_SebastianIntro:
	.string "Bu dönen kapılar yüzünden başım\ndönüyor.$"

Route110_TrickHousePuzzle6_Text_SebastianDefeat:
	.string "Her şey dönüp duruyor. Buna daha\nfazla dayanamayacağım.$"

Route110_TrickHousePuzzle6_Text_SebastianPostBattle:
	.string "Hiç etkilenmiş gibi görünmüyorsun.\nYoksa poker suratını mı takındın?$"


