@ NOTE: Route 104's sail to Dewford script references local IDs from Dewford's map.
@  These are labeled in DewfordTown/scripts.inc
.set LOCALID_RIVAL, 34

Route104_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route104_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_OnTransition
	.byte 0

Route104_OnFrame:
	map_script_2 VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_StartSailToDewford
	.2byte 0

Route104_EventScript_StartSailToDewford::
	lockall
	goto Route104_EventScript_SailToDewford
	end

Route104_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call Route104_EventScript_TrySetRivalPos
	call Route104_EventScript_ShowOrHideWhiteHerbFlorist
	end

Route104_EventScript_ShowOrHideWhiteHerbFlorist::
	goto_if_unset FLAG_MET_PRETTY_PETAL_SHOP_OWNER, Route104_EventScript_HideWhiteHerbFlorist
	goto_if_unset FLAG_BADGE03_GET, Route104_EventScript_HideWhiteHerbFlorist
	clearflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_HideWhiteHerbFlorist::
	setflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
	return

Route104_EventScript_TrySetRivalPos::
	goto_if_ge VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_DontSetRivalPos
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, Route104_EventScript_DontSetRivalPos
	goto_if_unset FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_DontSetRivalPos
	setobjectxyperm LOCALID_RIVAL, 17, 52
	return

Route104_EventScript_DontSetRivalPos::
	return

Route104_EventScript_Rival::
	lockall
	setvar VAR_0x8008, 1
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

Route104_EventScript_RivalTrigger::
	lockall
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_RUSTBORO_CITY_STATE, 8
	setvar VAR_ROUTE104_STATE, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 10
	addobject LOCALID_RIVAL
	clearflag FLAG_HIDE_ROUTE_104_RIVAL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerBackUp
	waitmovement 0
	applymovement LOCALID_RIVAL, Route104_Movement_RivalExitBrineysCottage
	waitmovement 0
	delay 20
	setvar VAR_0x8008, 0
	call RustboroCity_EventScript_PlayRivalMusic
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	goto Route104_EventScript_RivalEncounter

@ Unused, shares script with Rustboro encounter instead
Route104_EventScript_PlayRivalMusic::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_PlayMayMusic
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_PlayBrendanMusic
	return

Route104_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

Route104_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

Route104_EventScript_RivalEncounter::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_MayEncounter
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_BrendanEncounter
	end

Route104_EventScript_MayEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_MayDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_MayAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_MayWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredMay, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_MayHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_RIVAL
	msgbox Route104_Text_MayMinesDecentLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_Movement_RivalWalkSlowLeft:
	walk_slow_left
	step_end

Route104_Movement_RivalApproachPlayer:
	walk_down
	face_right
	step_end

Route104_Movement_PlayerFaceRival:
	delay_4
	walk_in_place_faster_left
	step_end

Route104_EventScript_MayAskToBattle::
	msgbox Route104_Text_MayLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleMay::
	msgbox Route104_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleMayTreecko
	case 1, Route104_EventScript_BattleMayTorchic
	case 2, Route104_EventScript_BattleMayMudkip
	end

Route104_EventScript_MayDefeated::
	msgbox Route104_Text_MayPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_RestoreMusic::
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

Route104_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, Route104_Text_MayDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_MayDefeated
	end

Route104_EventScript_BrendanEncounter::
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_BrendanDefeated
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_BrendanAskToBattle
	setflag FLAG_REGISTER_RIVAL_POKENAV
	msgbox Route104_Text_BrendanWeShouldRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredBrendan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerFaceRival
	applymovement LOCALID_RIVAL, Route104_Movement_RivalWalkSlowLeft
	msgbox Route104_Text_BrendanHowsYourPokedex, MSGBOX_DEFAULT
	closemessage
	waitmovement 0
	applymovement LOCALID_RIVAL, Route104_Movement_RivalApproachPlayer
	waitmovement 0
	copyobjectxytoperm LOCALID_RIVAL
	msgbox Route104_Text_BrendanDoingGreatLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	call Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BrendanAskToBattle::
	msgbox Route104_Text_BrendanLetsBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_BattleBrendan::
	msgbox Route104_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route104_EventScript_BattleBrendanTreecko
	case 1, Route104_EventScript_BattleBrendanTorchic
	case 2, Route104_EventScript_BattleBrendanMudkip
	end

Route104_EventScript_BrendanDefeated::
	msgbox Route104_Text_BrendanPostBattle, MSGBOX_DEFAULT
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
	releaseall
	end

Route104_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, Route104_Text_BrendanDefeat
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
	goto Route104_EventScript_BrendanDefeated
	end

Route104_Movement_PlayerBackUp:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Route104_Movement_RivalExitBrineysCottage:
	walk_down
	step_end

Route104_EventScript_ExpertF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104, Route104_EventScript_ReceivedBerry
	msgbox Route104_Text_PlantBerriesInSoilTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_CHESTO_BERRY
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_ReceivedBerry::
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_WhiteHerbFlorist::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_WHITE_HERB, Route104_EventScript_ReceivedWhiteHerb
	msgbox Route104_Text_DontNeedThisTakeIt, MSGBOX_DEFAULT
	giveitem ITEM_WHITE_HERB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_WHITE_HERB
	release
	end

Route104_EventScript_ReceivedWhiteHerb::
	msgbox Route104_Text_FlowerShopSellingSaplings, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl1::
	msgbox Route104_Text_BrineyLivesInSeasideCottage, MSGBOX_NPC
	end

Route104_EventScript_BugCatcher::
	msgbox Route104_Text_WhatsItLikeAtBottomOfSea, MSGBOX_SIGN
	end

Route104_EventScript_BrineysCottageSign::
	msgbox Route104_Text_MrBrineysCottage, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignPetalburg::
	msgbox Route104_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignRustboro::
	msgbox Route104_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route104_EventScript_FlowerShopSign::
	msgbox Route104_Text_PrettyPetalFlowShop, MSGBOX_SIGN
	end

Route104_EventScript_TrainerTipsDoubleBattles::
	msgbox Route104_Text_TrainerTipsDoubleBattles, MSGBOX_SIGN
	end

Route104_EventScript_Boy1::
	msgbox Route104_Text_ThrowBallAtWeakenedPokemon, MSGBOX_NPC
	end

Route104_EventScript_Woman::
	msgbox Route104_Text_OnlyThrowBallAtWildPokemon, MSGBOX_NPC
	end

Route104_EventScript_Boy2::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM09, Route104_EventScript_ReceivedBulletSeed
	msgbox Route104_Text_LikeFillingMouthWithSeedsTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM09
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM09
	release
	end

Route104_EventScript_ReceivedBulletSeed::
	msgbox Route104_Text_TMsAreOneTimeUse, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Girl2::
	msgbox Route104_Text_ImNotATrainer, MSGBOX_NPC
	end

Route104_EventScript_SailToDewford::
	setobjectsubpriority LOCALID_BRINEY_R104, MAP_ROUTE104, 0
	setobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE104, 0
	applymovement LOCALID_BRINEY_R104, Route104_Movement_BrineyBoardBoat
	waitmovement 0
	removeobject LOCALID_BRINEY_R104
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerBoardBoat
	waitmovement 0
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	call Common_EventScript_PlayBrineysBoatMusic
	goto_if_set FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordNoCall
	goto_if_unset FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordDadCalls
	end

Route104_EventScript_SailToDewfordNoCall::
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewford
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewford
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_SailToDewfordDadCalls::
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewfordBeforeDadCalls
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewfordBeforeDadCalls
	waitmovement 0
	pokenavcall Route104_Text_DadPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route104_Text_RegisteredDadInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_NORMAN_MATCH_CALL
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewfordAfterDadCalls
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewfordAfterDadCalls, MAP_ROUTE104
	waitmovement LOCALID_BOAT_R104, MAP_ROUTE104
	waitmovement 0
	goto Route104_EventScript_ArriveInDewford

Route104_EventScript_ArriveInDewford::
	delay 50
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerExitBoat
	waitmovement 0
	call Common_EventScript_StopBrineysBoatMusic
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerMoveForBriney
	waitmovement 0
	setobjectxyperm LOCALID_BRINEY_DEWFORD, 12, 8
	addobject LOCALID_BRINEY_DEWFORD
	setobjectsubpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN, 0
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
	applymovement LOCALID_BRINEY_DEWFORD, Route104_Movement_BrineyExitBoat
	waitmovement 0
	addobject LOCALID_BOAT_DEWFORD
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
	call Common_EventScript_StopBrineysBoatMusic
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
	hideobjectat LOCALID_BOAT_R104, MAP_ROUTE104
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
	resetobjectsubpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN
	copyobjectxytoperm LOCALID_BRINEY_DEWFORD
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 0
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_DeliverLetterReminder
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_LandedInDewford
	end

Route104_EventScript_DeliverLetterReminder::
	msgbox Route104_Text_LandedInDewfordDeliverLetter, MSGBOX_DEFAULT
	releaseall
	end

Route104_EventScript_LandedInDewford::
	msgbox DewfordTown_Text_BrineyLandedInDewford, MSGBOX_DEFAULT
	releaseall
	end

Route104_Movement_SailToDewfordBeforeDadCalls:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	step_end

Route104_Movement_SailToDewfordAfterDadCalls:
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_SailToDewford:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_faster_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_faster_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerBoardBoat:
	walk_left
	walk_down
	walk_down
	step_end

Route104_Movement_PlayerExitBoat:
	walk_down
	step_end

Route104_Movement_PlayerMoveForBriney:
	walk_down
	walk_left
	walk_in_place_faster_right
	step_end

Route104_Movement_BrineyBoardBoat:
	walk_down
	walk_down
	step_end

Route104_Movement_BrineyExitBoat:
	walk_down
	walk_in_place_faster_left
	step_end

Route104_EventScript_Ivan::
	trainerbattle_single TRAINER_IVAN, Route104_Text_IvanIntro, Route104_Text_IvanDefeat
	msgbox Route104_Text_IvanPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY, Route104_Text_BillyIntro, Route104_Text_BillyDefeat
	msgbox Route104_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Haley::
	trainerbattle_single TRAINER_HALEY_1, Route104_Text_HaleyIntro, Route104_Text_HaleyDefeat, Route104_EventScript_TryRegisterHaleyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchHaley
	setvar VAR_0x8004, TRAINER_HALEY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterHaleyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaleyAfterBattle
	release
	end

Route104_EventScript_RegisterHaleyAfterBattle::
	msgbox Route104_Text_HaleyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_TryRegisterHaley::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaley
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterHaley::
	msgbox Route104_Text_HaleyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_HALEY_1
	release
	end

Route104_EventScript_RematchHaley::
	trainerbattle_rematch TRAINER_HALEY_1, Route104_Text_HaleyRematchIntro, Route104_Text_HaleyRematchDefeat
	msgbox Route104_Text_HaleyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Winston::
	trainerbattle_single TRAINER_WINSTON_1, Route104_Text_WinstonIntro, Route104_Text_WinstonDefeat, Route104_EventScript_TryRegisterWinstonAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchWinston
	setvar VAR_0x8004, TRAINER_WINSTON_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterWinstonAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinstonAfterBattle
	release
	end

Route104_EventScript_RegisterWinstonAfterBattle::
	msgbox Route104_Text_WinstonRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_TryRegisterWinston::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinston
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterWinston::
	msgbox Route104_Text_WinstonRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_WINSTON_1
	release
	end

Route104_EventScript_RematchWinston::
	trainerbattle_rematch TRAINER_WINSTON_1, Route104_Text_WinstonRematchIntro, Route104_Text_WinstonRematchDefeat
	msgbox Route104_Text_WinstonPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Cindy::
	trainerbattle_single TRAINER_CINDY_1, Route104_Text_CindyIntro, Route104_Text_CindyDefeat, Route104_EventScript_TryRegisterCindyAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchCindy
	setvar VAR_0x8004, TRAINER_CINDY_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_TryRegisterCindyAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindyAfterBattle
	release
	end

Route104_EventScript_RegisterCindyAfterBattle::
	msgbox Route104_Text_CindyRegister2, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_TryRegisterCindy::
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindy
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_RegisterCindy::
	msgbox Route104_Text_CindyRegister1, MSGBOX_DEFAULT
	register_matchcall TRAINER_CINDY_1
	release
	end

Route104_EventScript_RematchCindy::
	trainerbattle_rematch TRAINER_CINDY_1, Route104_Text_CindyRematchIntro, Route104_Text_CindyRematchDefeat
	msgbox Route104_Text_CindyPostRematch, MSGBOX_AUTOCLOSE
	end

Route104_EventScript_Gina::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_GinaIntro, Route104_Text_GinaDefeat, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_GinaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Mia::
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_MiaIntro, Route104_Text_MiaDefeat, Route104_Text_MiaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route104_Text_MiaPostBattle, MSGBOX_DEFAULT
	release
	end

Route104_EventScript_Darian::
	trainerbattle_single TRAINER_DARIAN, Route104_Text_DarianIntro, Route104_Text_DarianDefeat
	msgbox Route104_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_Text_BrineyLivesInSeasideCottage:
	.string "Şu deniz kenarındaki kulübede\n"
	.string "BAY BRINEY yaşıyor.\p"
	.string "O, bir zamanlar ne kadar fırtınalı\n"
	.string "olursa olsun denizden korkmayan biriydi.$"


Route104_Text_WhatsItLikeAtBottomOfSea:
	.string "Deniz, ha?\pDenizin dibi nasıldır acaba?$"

Route104_Text_ThrowBallAtWeakenedPokemon:
	.string "Eğer bir POKé TOPU atacaksan, önce\nvahşi POKéMON'u zayıflat.\pZehirlenmiş, yakılmış veya uyutulmuşsa\nyakalamak daha kolay olacaktır.$"

Route104_Text_OnlyThrowBallAtWildPokemon:
	.string "Başkasının POKéMON'unu çalmaya\nçalışırsan hırsız olursun.\pPOKé TOPLARINI sadece vahşi\nPOKéMON'lara atmalısın.$"

Route104_Text_ImNotATrainer:
	.string "Hayır, ben eğitmen değilim.\pAma bu doğru, EĞİTMENLER göz göze\ngelirse, bu savaşmak için bir meydan\lokumadır.\pEğer savaşmak istemiyorsan, onların\ngörüş alanından uzak dur.$"

Route104_Text_LikeFillingMouthWithSeedsTakeThis:
	.string "Ağzımı tohumlarla doldurmayı ve\nhızla tükürmeyi seviyorum!\pBunu alabilirsin, sen de bir dene!\pBunu bir POKéMON üzerinde\nkullandığında, tohumları hızla\lfırlatan bir saldırı öğretecektir.$"

Route104_Text_TMsAreOneTimeUse:
	.string "Bir tavsiye!\pTM, yani TEKNİK MAKİNE, sadece\nbir kere kullanılabilir.\pBir kere kullandın mı, biter.\nKullanmadan önce iki kez düşün!$"

Route104_Text_DontNeedThisTakeIt:
	.string "Bu ÇİÇEK DÜKKANI geçenlerde fidan\nsatmaya başladı.\pBu beni çok mutlu etti, ve ben de\nalışverişi abarttım.\pArtık bu BEYAZ OT'a ihtiyacım yok.\nAlır mısın lütfen?$"

Route104_Text_FlowerShopSellingSaplings:
	.string "Bu ÇİÇEK DÜKKANI geçenlerde fidan\nsatmaya başladı.\pBu beni çok mutlu etti, alışverişi\nabarttım. Nereye koysam ki?$"

Route104_Text_MrBrineysCottage:
	.string "BAY BRINEY'İN KULÜBESİ$"

Route104_Text_RouteSignPetalburg:
	.string "ROTA 1O4\n{RIGHT_ARROW} PETALBURG ŞEHRİ$"

Route104_Text_RouteSignRustboro:
	.string "ROTA 1O4\n{UP_ARROW} RUSTBORO ŞEHRİ$"

Route104_Text_PrettyPetalFlowShop:
	.string "TAÇ YAPRAK ÇİÇEKÇİ DÜKKÂNI$"

Route104_Text_TrainerTipsDoubleBattles:
	.string "EĞİTMEN İPUÇLARI\pHOENN bölgesinde, ÇİFT SAVAŞ adı verilen\n2'ye 2 POKéMON savaşları\lyapılmaktadır.\pÇift savaşta, EĞİTMEN listenin\nsolundaki ve en üstteki olmak üzere iki\lPOKéMON gönderir. POKéMON'ların\lnasıl sıralandığı önemlidir.$"

Route104_Text_MayWeShouldRegister:
	.string "MAY: Merhaba, {PLAYER}{KUN}!\pDEVON, POKéNAV'ına MAÇ ARAMASI\ngüncellemesi kurdu, değil mi?\pBirbirimizi kaydetmeliyiz, böylece\nistediğimiz zaman iletişim kurabiliriz.$"

Route104_Text_RegisteredMay:
	.string "{PLAYER}, MAY'i POKéNAV'a kaydetti.$"

Route104_Text_MayHowsYourPokedex:
	.string "MAY: Bu arada, {PLAYER}{KUN},\nPOKéDEX'in nasıl gidiyor?$"

Route104_Text_MayMinesDecentLetsBattle:
	.string "Benimki oldukça iyi gidiyor.\pPekâlâ…\nKüçük bir savaşa ne dersin?$"

Route104_Text_MayHaventRaisedPokemon:
	.string "MAY: Sorun ne?\pPOKéMON'unu fazla geliştirmedin mi?\pBu bir eğitmene yakışmaz!$"

Route104_Text_MayLetsBattle:
	.string "Ne düşünüyorsun? Burada küçük\nbir savaşa ne dersin?$"

Route104_Text_MayIntro:
	.string "Daha yeni EĞİTMEN oldun,\n{PLAYER}{KUN}. Kaybetmeyeceğim!$"

Route104_Text_MayDefeat:
	.string "Vay canına!\nBeklediğimden daha iyisin!$"

Route104_Text_MayPostBattle:
	.string "MAY: POKéMON'u ele alış şeklinle\noldukça iyi olduğunu söyleyebilirim.\pAma onları sadece savaştırmak yerine,\nonlara BRINEY'in davrandığı gibi\ldavranmalısın.\pPOKéMON'lar ile arkadaş olmak önemli.$"

Route104_Text_BrendanWeShouldRegister:
	.string "BRENDAN: Selam, {PLAYER}{KUN}!\pDEVON, POKéNAV'ına MAÇ ARAMASI\ngüncellemesi kurdu, değil mi?\pBirbirimizi kaydetmeliyiz, böylece\nistediğimiz zaman iletişim kurabiliriz.$"

Route104_Text_RegisteredBrendan:
	.string "{PLAYER}, BRENDAN'ı POKéNAV'a\nkaydetti.$"

Route104_Text_BrendanHowsYourPokedex:
	.string "POKéDEX'in nasıl gidiyor?\nHiç sayfa doldurabildin mi?$"

Route104_Text_BrendanDoingGreatLetsBattle:
	.string "Benimki harika gidiyor!\pBir savaşta ne kadar iyi olduğumu\ngörmek ister misin?$"

Route104_Text_BrendanNoConfidence:
	.string "Sorun ne?\nPOKéMON'una güvenmiyor musun?$"

Route104_Text_BrendanLetsBattle:
	.string "Ne dersin?\nBenimle savaşmak ister misin?$"

Route104_Text_BrendanIntro:
	.string "Daha yeni EĞİTMEN olduğunu biliyorum\nama kolay olmayacak!$"

Route104_Text_BrendanDefeat:
	.string "Hmm…\nOldukça iyisin.$"

Route104_Text_BrendanPostBattle:
	.string "POKéMON'ları idare etmekte oldukça\niyisin.\pAma, bilirsin, sadece POKéMON savaşı\nyapmamalısın.\pTıpkı BAY BRINEY gibi POKéMON'unla\narkadaş olman da önemli.$"
