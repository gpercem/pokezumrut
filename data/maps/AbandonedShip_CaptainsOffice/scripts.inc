AbandonedShip_CaptainsOffice_MapScripts::
	.byte 0

AbandonedShip_CaptainsOffice_EventScript_CaptSternAide::
	lock
	faceplayer
	goto_if_set FLAG_EXCHANGED_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	checkitem ITEM_SCANNER
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner
	goto_if_set FLAG_ITEM_ABANDONED_SHIP_HIDDEN_FLOOR_ROOM_2_SCANNER, AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus
	msgbox AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_CanYouDeliverScanner::
	msgbox AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_EventScript_ThisIsSSCactus::
	msgbox AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus, MSGBOX_DEFAULT
	release
	end

AbandonedShip_CaptainsOffice_Text_NoSuccessFindingScanner:
	.string "Kaptan STERN adına bu gemiyi\naraştırıyorum.\pAyrıca benden bir TARAYICI bulmamı\nistedi, ama henüz bulamadım…$"

AbandonedShip_CaptainsOffice_Text_OhCanYouDeliverScanner:
	.string "Aa! Bu bir tarayıcı!\pDinle, bunu Kaptan STERN'e teslim\nedebilir misin??\pBu gemiyi biraz daha araştırmak\nistiyorum.$"

AbandonedShip_CaptainsOffice_Text_ThisIsSSCactus:
	.string "Bu geminin adı S.S. KAKTÜS.\nEski bir döneme ait gibi görünüyor.$"


