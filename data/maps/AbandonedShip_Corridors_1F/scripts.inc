AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
	.string "Simidimin gemide olmasının nesi bu\nkadar komik?$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "Vay canına, beni bunalttın!$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "Simide tutunarak POKé TOPU atmak\nkolay iş değil!$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "Burası çok eğlenceli değil mi?\nBurada olmak bile beni\lheyecanlandırıyor!$"
