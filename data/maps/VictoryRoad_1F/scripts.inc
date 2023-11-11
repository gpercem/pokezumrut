.set LOCALID_WALLY_ENTRANCE, 4

VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 2, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_WALLY_ENTRANCE, 3, 24
	setobjectmovementtype LOCALID_WALLY_ENTRANCE, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_WALLY_ENTRANCE
	applymovement LOCALID_WALLY_ENTRANCE, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_WALLY_ENTRANCE
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy::
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn::
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore:
	.string "WALLY: Merhaba, {PLAYER}!\pEminim beni burada gördüğüne\nşaşırmışsındır!\pBuraya kadar gelebildim ve hepsi senin\nsayende!\pSana karşı kaybetmek beni daha da\ngüçlendirdi!\pAma artık kaybetmeyeceğim!\pKazanacağım! Bana cesaret ve güç\nveren POKéMON'larım için!\pTamam… İşte geliyorum!$"

VictoryRoad_1F_Text_WallyEntranceDefeat:
	.string "Vay canına, {PLAYER}.\nHer şeye rağmen güçlüsün!$"

VictoryRoad_1F_Text_WallyPostEntranceBattle:
	.string "WALLY: Bugün seni yenemedim, {PLAYER},\nama bir gün seni yakalayacağım!$"

VictoryRoad_1F_Text_WallyIntro:
	.string "WALLY: Merhaba!\pSon seferden bu yana daha da\ngüçlendim!\lSana göstermek istiyorum, {PLAYER}!\pTamam… İşte geliyorum!$"

VictoryRoad_1F_Text_WallyDefeat:
	.string "Vay canına, {PLAYER}.\nHer şeye rağmen güçlüsün!$"

VictoryRoad_1F_Text_WallyPostBattle:
	.string "WALLY: Bu sefer de seni yenemedim…\nAma bir gün, {PLAYER}, seni\lyakalayacağım…\pVe POKéMON LİGİ'ne meydan okuyacağım!$"

VictoryRoad_1F_Text_EdgarIntro:
	.string "Buraya kadar birkaç kez geldim ama\nson kısım o kadar uzun ki…$"

VictoryRoad_1F_Text_EdgarDefeat:
	.string "Hayalim yine burada bitiyor.$"

VictoryRoad_1F_Text_EdgarPostBattle:
	.string "Buraya kadar gelebildin.\nMomentumunu koru ve şampiyonluğa\lyürü!\pBunu yapabilecek biri varsa, o da\nsensin!$"

VictoryRoad_1F_Text_AlbertIntro:
	.string "Bunca yolu şimdi kaybetmek için\ngelmedim. Böyle bir olasılık yok!$"

VictoryRoad_1F_Text_AlbertDefeat:
	.string "İmkansız…\nKaybettim.$"

VictoryRoad_1F_Text_AlbertPostBattle:
	.string "Kaybettim.\pBu, ŞAMPİYON olmak için gerekli\nniteliklere sahip olmadığım anlamına\lgeliyor.$"

VictoryRoad_1F_Text_HopeIntro:
	.string "Görünüşte sonsuz ve zorlu olan bu yol\nadının hakkını veriyor.$"

VictoryRoad_1F_Text_HopeDefeat:
	.string "Savaş stilin harika…$"

VictoryRoad_1F_Text_HopePostBattle:
	.string "ŞAMPİYON olma potansiyeline sahip\ngörünüyorsun.$"

VictoryRoad_1F_Text_QuincyIntro:
	.string "ZAFER YOLU ne mi?\nKazanırsan size söylerim!$"

VictoryRoad_1F_Text_QuincyDefeat:
	.string "Tamam!\nAferin sana!$"

VictoryRoad_1F_Text_QuincyPostBattle:
	.string "Buradan sağ salim geçmek, POKéMON\nŞAMPİYONU olmayı hedefleyen her\lEĞİTMEN için son sınavdır.\pBu yüzden buraya ZAFER YOLU deniyor.$"

VictoryRoad_1F_Text_KatelynnIntro:
	.string "Buraya kadar gelen birine\nsöyleyecek bir şeyim yok.\lHadi başlayalım!$"

VictoryRoad_1F_Text_KatelynnDefeat:
	.string "Bu bir rezalet.$"

VictoryRoad_1F_Text_KatelynnPostBattle:
	.string "Hımph, devam et.\nBakalım umurumda olacak mı?$"
