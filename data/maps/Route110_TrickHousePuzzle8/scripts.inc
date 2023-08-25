Route110_TrickHousePuzzle8_MapScripts::
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} kapıdaki gizli kodu yazdı.\pNUMARA USTASI'nı seviyorum.\n… … … … … … … …\pKilit açıldı!$"

Route110_TrickHousePuzzle8_Text_VincentIntro:
	.string "Pek çok eğitmen bu kadar ileriye\ngidememiştir.$"

Route110_TrickHousePuzzle8_Text_VincentDefeat:
	.string "Bu senin de sert olduğun anlamına\ngeliyor olmalı.$"

Route110_TrickHousePuzzle8_Text_VincentPostBattle:
	.string "POKéMON LİGİ ŞAMPİYONU'nu mu yendin?\nBu çok fazla!$"

Route110_TrickHousePuzzle8_Text_KeiraIntro:
	.string "Benimle dövüştüğün için kendini şanslı\nsay!$"

Route110_TrickHousePuzzle8_Text_KeiraDefeat:
	.string "Bu doğru değil! Kaybedemem!$"

Route110_TrickHousePuzzle8_Text_KeiraPostBattle:
	.string "Beni yenmen bir mucize.\nBununla övünebilirsin.$"

Route110_TrickHousePuzzle8_Text_LeroyIntro:
	.string "Sen de NUMARA EVİ meydan okumasını\nsürdürüyorsun.$"

Route110_TrickHousePuzzle8_Text_LeroyDefeat:
	.string "Anlıyorum… Olağanüstü bir tarzınız\nvar.$"

Route110_TrickHousePuzzle8_Text_LeroyPostBattle:
	.string "Sizin gibi birini görmek NUUMARA\nUSTASINI memnun etmeli.$"


