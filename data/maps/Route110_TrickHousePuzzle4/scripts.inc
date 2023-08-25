Route110_TrickHousePuzzle4_MapScripts::
	.byte 0

Route110_TrickHousePuzzle4_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_4_STATE, 0, Route110_TrickHousePuzzle4_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle4_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_4_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle4_EventScript_Cora::
	trainerbattle_single TRAINER_CORA, Route110_TrickHousePuzzle4_Text_CoraIntro, Route110_TrickHousePuzzle4_Text_CoraDefeat
	msgbox Route110_TrickHousePuzzle4_Text_CoraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Yuji::
	trainerbattle_single TRAINER_YUJI, Route110_TrickHousePuzzle4_Text_YujiIntro, Route110_TrickHousePuzzle4_Text_YujiDefeat
	msgbox Route110_TrickHousePuzzle4_Text_YujiPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_EventScript_Paula::
	trainerbattle_single TRAINER_PAULA, Route110_TrickHousePuzzle4_Text_PaulaIntro, Route110_TrickHousePuzzle4_Text_PaulaDefeat
	msgbox Route110_TrickHousePuzzle4_Text_PaulaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle4_Text_WroteSecretCodeLockOpened:
	.string "{PLAYER} kapıdaki gizli kodu yazdı.\pNUMARA USTASI harika. … … … … … …\n… …\pKilit açıldı!$"

Route110_TrickHousePuzzle4_Text_CoraIntro:
	.string "Bunu düşünmek çok zahmetli. Ben\nsadece savaşmak istedim!$"

Route110_TrickHousePuzzle4_Text_CoraDefeat:
	.string "Kaybetmiş olsam da, yine de en çok\nsavaşmayı seviyorum!$"

Route110_TrickHousePuzzle4_Text_CoraPostBattle:
	.string "Sizce de öyle değil mi? EĞİTMENLER\norada olsaydı her yere giderdiniz.$"

Route110_TrickHousePuzzle4_Text_YujiIntro:
	.string "Heh! Bunun gibi kayaları tek\nparmağımla kenara fırçalayabilirim!$"

Route110_TrickHousePuzzle4_Text_YujiDefeat:
	.string "Kayaları itebiliyorum ama bulmacayı\nçözemiyorum.$"

Route110_TrickHousePuzzle4_Text_YujiPostBattle:
	.string "Kaslı olmak yeterli değil… Kafanızı\nkullanmalısınız. Zeki ol!$"

Route110_TrickHousePuzzle4_Text_PaulaIntro:
	.string "NUMARA EVİ gittikçe daha hileli\nbir hal alıyor, değil mi?$"

Route110_TrickHousePuzzle4_Text_PaulaDefeat:
	.string "Aaak!$"

Route110_TrickHousePuzzle4_Text_PaulaPostBattle:
	.string "Sonuna kadar gelebilen var mı?$"


