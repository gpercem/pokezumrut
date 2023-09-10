MtPyre_5F_MapScripts::
	.byte 0

@ Seems like the scripts for the 4F and 5F were swapped

MtPyre_4F_EventScript_Tasha::
	trainerbattle_single TRAINER_TASHA, MtPyre_4F_Text_TashaIntro, MtPyre_4F_Text_TashaDefeat
	msgbox MtPyre_4F_Text_TashaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_4F_Text_TashaIntro:
	.string "Korkutucu şeyleri severim…\n"
	.string "Bu hastalık gibi bir şey…\p"
	.string "Ve buradayken de…\n"
	.string "Korkudan tir tir titriyorum…$"

MtPyre_4F_Text_TashaDefeat:
	.string "Kaybetmek… Nefret ederim.$"

MtPyre_4F_Text_TashaPostBattle:
	.string "Korkunç şeyler görmek istiyorum…\n"
	.string "Gidemem…\p"
	.string "Kalmalıyım…\n"
	.string "Benle kalmaz mısın?$"

