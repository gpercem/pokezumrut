MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
	.string "Liderimizin söylediği her şeyi\nanlıyorum. Ama ne var biliyor musun?\pSüper-kadim bir POKéMON'u çalmak ve\nbirinin METEORUNU araklamak\lgibi şeyler yapmak…\pBence biraz fazla ileri gidiyoruz.\nSen ne düşünüyorsun?$"

MagmaHideout_3F_2R_Text_Grunt10Defeat:
	.string "Evet, sanırım bir şeyleri yanlış\nyapıyoruz.$"

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
	.string "Biliyor musun, sana yenilmek bazı\nşeyleri sorgulamamı sağladı.\pBir dahaki sefere liderimizi\ngördüğümde ona ne yaptığımızı\lsoracağım.$"


