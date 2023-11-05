.set LOCALID_ATTENDANT, 1
.set LOCALID_HINT_GIVER, 2

BattleFrontier_BattlePyramidLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

@ Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical
BattleFrontier_BattlePyramidLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth:
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePyramidLobby_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving::
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	closemessage
	pyramid_set PYRAMID_DATA_WIN_STREAK, 0
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing::
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints::
	special DoBattlePyramidMonsHaveHeldItem
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_setprize
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge::
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge

BattleFrontier_BattlePyramidLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pyramid_init
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	pyramid_seedfloor
	pyramid_settrainers
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePyramidLobby_EventScript_HintGiver::
	lockall
	applymovement LOCALID_HINT_GIVER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint::
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	return

@ Shouldnt occur
BattleFrontier_BattlePyramidLobby_EventScript_NoHint::
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment::
	copyvar VAR_0x8004, VAR_RESULT
	special GetBattlePyramidHint
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPoison::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBurn::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintIce::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintRock::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFighting::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWeather::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBug::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintDark::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWater::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintGhost::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintSteel::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintNormal::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PYRAMID
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag

BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag::
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
	waitmovement 0
	return

BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside:
	walk_right
	face_left
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel:
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake, MSGBOX_DEFAULT
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	special TryStoreHeldItemsInPyramidBag
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag, MSGBOX_DEFAULT
	return

@ When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep::
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag::
	special ChooseItemsToTossFromPyramidBag
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty::
	special BattlePyramidChooseMonHeldItems
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems::
	special DoBattlePyramidMonsHaveHeldItem
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems
	return

BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem, MSGBOX_DEFAULT
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_Woman::
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid:
	.string "EĞİTİMCİLERİN cesaretinin test\nedildiği yer!\pSAVAŞ PİRAMİDİ'ne hoş geldiniz!\pBen sizin Savaş Görevi rehberinizim.$"

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge:
	.string "Savaş Görevi mücadelesine atılmak için\ncesaretiniz var mı?$"

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge:
	.string "Gelecekte meydan okumanızı\nbekliyoruz!$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid:
	.string "Savaş Görevi, PİRAMİT'i keşfetmeniz\nve zirveye ulaşmaya çalışmanız\lgereken bir savaş etkinliğidir.\pPİRAMİT'te yedi katlı labirentler\nvardır ve bunların hepsi sadece\lyetenekli EĞİTMENLERLE değil aynı\lzamanda vahşi POKéMON'larla da\ldoludur.\pHiçbirinde bir eşya olmayan üç POKéMON\nile girmelisiniz.\pTırmanışınızda, eşyalar için size bir\nSAVAŞ ÇANTASI verilecektir.\pMücadelenizde başarısız olursanız,\nSAVAŞ ÇANTASINA yerleştirilen\lherhangi bir eşya kaybolur.\pMücadelenizi yarıda kesmek\nistiyorsanız, DİNLEN seçeneğini\lseçmeli ve oyunu kaydetmelisiniz.\pYarıda kesmeden önce kaydetmezseniz\ndiskalifiye olursunuz.$"

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode:
	.string "PİRAMİT, 50. Seviye ve Açık Seviye\nolmak üzere iki kurs sunmaktadır. Siz\lhangisine katılacaksınız?$"

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons:
	.string "Çok güzel. Şimdi, lütfen size eşlik\netmesini istediğiniz üç POKéMON'u\lseçin.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Ufak bir sorun var, maceracı!\pMücadele için gerekli üç POKéMON'a\nsahip değilsin gibi görünüyor.\pLütfen POKéMON'undaki tüm eşyaları\nalmayı da unutma.\pEGGS{STR_VAR_1} uygun değil.\pHazır olduğunuzda lütfen benimle\nkonuşun.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50:
	.string "Ufak bir sorun var, maceracı!\pMücadele için gerekli üç POKéMON'a\nsahip değilsin gibi görünüyor.\pÜç POKéMON farklı olmalı ve her biri 50.\nSeviyeden yüksek olmamalıdır.\pLütfen POKéMON'undaki tüm eşyaları\nalmayı da unutma.\pEGGS{STR_VAR_1} uygun değildir.\pHazır olduğunuzda, lütfen benimle\nkonuşun.$"

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge:
	.string "SAVAŞ PİRAMİDİ'ne girmeden önce oyun\nkaydedilmelidir. Tamam mı?$"

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid:
	.string "Çok güzel. Şimdi size SAVAŞ\nPİRAMİDİ'ni göstereceğim.$"

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping:
	.string "Siz keşfederken ÇANTA'nızı güvende\ntutacağız, {PLAYER}.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag:
	.string "Karşılığında, lütfen daha önce\nkullandığınız bu SAVAŞ ÇANTASINI alın.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag:
	.string "Karşılığında, lütfen bu SAVAŞ\nÇANTASI'nı alın.$"

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag:
	.string "{PLAYER} ÇANTAYI SAVAŞ ÇANTASI ile\ndeğiştirdi.$"

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel:
	.string "Bu zemin paneline bastığınızda,\nPİRAMİT'te daha yüksek bir kata\ltaşınacaksınız.\pUmarım senin iyiliğin için görevin\ngüvenli bir şekilde ilerler!$"

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag:
	.string "Büyük bir sorun var kaşif!\pMücadelenizi sonlandırmadan önce\nkaydetmediniz.\pSonuç olarak, üzülerek söylüyorum ki\nyarışmanız diskalifiye edildi.\pİşte sizin için tuttuğumuz ÇANTA.\p{PLAYER} ÇANTAYI geri aldı.$"

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid:
	.string "Seni tekrar görmek harika!\pPİRAMİT'i fethetmişsin! Ne kadar\nmuhteşem!$"

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake:
	.string "Ufak bir sorun var.\pEn az bir POKéMON bir eşya tutuyor.\pSöylediğim için üzgünüm ama\nPİRAMİT'te elde edilen eşyalar\lalınamaz.$"

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag:
	.string "POKéMON'unuz tarafından tutulan tüm\neşyalar SAVAŞ ÇANTANIZA taşınacaktır,\l{PLAYER}.$"

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep:
	.string "Üzülerek söylüyorum ki SAVAŞ ÇANTASI\ntüm eşyalarınızı alamaz.\pLütfen SAVAŞ ÇANTASI'nda ve\nPOKéMON'unuzda tutacağınız eşyaları\lseçin.$"

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem:
	.string "En az bir POKéMON hâlâ bir eşya\ntutuyor.$"

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep:
	.string "Lütfen SAVAŞ ÇANTASINDA ve\nPOKéMON'unuzla birlikte\lsaklayacağınız eşyaları seçin.$"

BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld:
	.string "{PLAYER} POKéMON'un sahip olduğu her\nşeyi geri verdi.$"

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept:
	.string "Kullandığınız SAVAŞ ÇANTASI bir\nsonraki mücadeleniz için hazır\ltutulacaktır.\p{PLAYER} ÇANTA'nın geri dönmesi için\nSAVAŞ ÇANTASI'nı ters çevirdi.$"

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait:
	.string "Sonuçlarınızı kaydetmeliyim. Lütfen\nbekleyin.$"

BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis:
	.string "SAVAŞ PİRAMİDİ'ni fethetmenin bir\nhatırası olarak, lütfen bunu alın.$"

BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem:
	.string "{PLAYER} {STR_VAR_1} ödülünü aldı.$"

BattleFrontier_BattlePyramidLobby_Text_BagIsFull:
	.string "…Ah… ÇANTANIZ dolu görünüyor.\pLütfen ÇANTA'nızın içindekileri\ndüzenledikten sonra geri dönün.$"

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag:
	.string "Senin için ne kadar üzücü…\pİşte sizin için tuttuğumuz ÇANTA.\pÇANTAYI geri aldık.$"

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge:
	.string "Bir sonraki meydan okumanızı dört\ngözle bekliyoruz!$"

BattleFrontier_BattlePyramidLobby_Text_HereIsPrize:
	.string "Gelişinizi dört gözle bekliyorduk!\pİşte PİRAMİT'i fethettiğiniz için\nödülünüz.$"

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait:
	.string "Hoş geldiniz.\pPİRAMİT'te sizi ne gibi\ntalihsizliklerin beklediğini\lsöylemekten memnuniyet duyacağım…$"

BattleFrontier_BattlePyramidLobby_Text_Aah:
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "… … … … … …\n"
	.string "Aah!$"

BattleFrontier_BattlePyramidLobby_Text_HintParalysis:
	.string "Bir kıvılcım yağmuru görüyorum.\p…Ve içinde, POKéMON'unuzun felçle\nmücadele ettiğini görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintPoison:
	.string "Zehir görüyorum.\p…Ve POKemon'unuzun zehirin\netkilerinden acı çektiğini görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintBurn:
	.string "Parlak kırmızı alevler görüyorum.\p…ve POKéMON'unuzun yanıklardan acı\nçektiğini görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste:
	.string "Karşılıksız öfkenin muazzam baskısını\nhissediyorum.\pBu bir lanet.\p…Ve POKéMON'unuzun Güç Puanlarının\ntükendiğini ve STRUGGLE kullanmaktan\lbaşka çaresi kalmadığını görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintLevitate:
	.string "POKéMON'un havalandığını görüyorum.\p…Ve POKéMON'unuzun güçsüz ZEMİN\ntipi hareketlerle hüsrana uğradığını\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility:
	.string "Yerin altından yükselen müthiş bir\nenerji hissediyorum.\p…Ve POKéMON'unuzun gücün\npençesinden kaçamadığını görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintIce:
	.string "Buz tipi POKéMON görüyorum.\p…Ve POKéMON'unuzun buzun dondurucu\netkisiyle savaştığını görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintExplosion:
	.string "Kullanıcıyı tehlikeye atan bir hareket\ntelaşı görüyorum…\p…ve senin POKéMON'unun onlara\ndüştüğünü görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintPsychic:
	.string "PSİŞİK tipi POKEMON görüyorum.\p…Ve senin POKéMON'unun PSİKOLOJİK\nhareketlerden eziyet çektiğini\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintRock:
	.string "KAYA tipi POKéMON görüyorum.\p…Ve POKéMON'unuzun KAYA\nhareketlerinden muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintFighting:
	.string "DÖVÜŞ tipi POKéMON görüyorum.\p…Ve POKéMON'unuzun DÖVÜŞ\nhareketleri tarafından dövüldüğünü\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintWeather:
	.string "YAĞMUR DANSI… GÜNEŞLİ GÜN…\nKUM FIRTINASI… DOLU…\pHavayla birlikte güçlenen POKéMON'lar\ngörüyorum.\p…Ve POKéMON'unuzun farklı türde\nhamlelerle karıştırıldığını\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintBug:
	.string "BÖCEK tipi POKéMON görüyorum.\p…Ve POKéMON'unuzun farklı türde\nsaldırılardan muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintDark:
	.string "Karanlık tip POKéMON görüyorum.\p…Ve POKéMON'unuzun KARANLIK tipi\nhareketlerden muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintWater:
	.string "SU tipi POKéMON görüyorum.\p…Ve POKéMON'unuzun SU tipi\nhareketlerden muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintGhost:
	.string "HAYALET tipi POKéMON görüyorum.\p…Ve POKéMON'unuzun HAYALET tipi\nhareketlerden muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintSteel:
	.string "ÇELİK tipi POKéMON görüyorum.\p…Ve POKéMON'unuzun son derece güçlü\nhareketlerden muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon:
	.string "UÇUŞ POKéMON görüyorum.\p…Ve POKéMON'unuzun son derece güçlü\nhareketlerden muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve:
	.string "Taşların gücünden evrimleşenleri\ngörüyorum.\pAyrıca ateşi, suyu ve elektriği de\nhissediyorum.\p…Ve POKEMON'unuzun bu üç güçten\nmuzdarip olduğunu görüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_HintNormal:
	.string "NORMAL tip POKéMON görüyorum.\p…Ve POKéMON'unuzun son derece güçlü\nhareketlerden muzdarip olduğunu\lgörüyorum…$"

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot:
	.string "Fallarıma inansanız da inanmasanız da,\nseçim sizin…\pGelecek her an değişebilir… İyi\nyolculuklar dilerim…$"

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning:
	.string "Biliyor muydunuz?\pEğer hızlı koşarsanız, ANTRENÖRLER\nsizi fark edebilir ve savaşmak için\lpeşinizden gelebilir.\pBu nedenle, EĞİTMENLERDEN kaçınmak\nistiyorsanız, gözlerini yakalamayın,\lancak dikkatli ve sessizce yanlarından\lgizlice geçin.$"

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems:
	.string "Aaaaaaaarrrrgh!\pBir sürü eşyam vardı ama kaybettiğimde\nhepsini kaybettim!\pAwaaaaaaarrrrgh!$"

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing:
	.string "Tekrar hoş geldiniz! Akla hayale\ngelmeyeni yaptınız!\pPİRAMİT KRALI'nı yendiniz ve SAVAŞ\nPİRAMİDİ'ni fethettiniz!$"

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints:
	.string "Genç kaşif! Cesaretini takdir etmek\niçin sana bu Savaş Puan(lar)ını\lveriyoruz!$"

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed:
	.string "Savaş Görevi kuralları listelenmiştir.$"

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading:
	.string "Hangi başlığı okumak istersiniz?$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules:
	.string "PİRAMİT fethedildiğinde, içinde\ngörünen vahşi POKéMON farklı türlerle\ldeğiştirilir.\pKeşfedin, gözlemleyin ve ne tür vahşi\nPOKéMON'larla karşılaşabileceğinizi\löğrenin.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules:
	.string "PİRAMİT'in içinde sizi bekleyen\nEĞİTİMCİLER var.\pHer katta en fazla sekiz EĞİTMEN\nvardır.\pBir EĞİTMENİ yendiğinizde, maceranız\niçin yararlı bir ipucu alacaksınız.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules:
	.string "PİRAMİT'teki labirentler her\ngirdiğinizde kendilerini yeniden\ldüzenler.\pLabirentler iyi aydınlatılmamıştır.\nDikkatli bir şekilde ilerlemelisiniz.\pVahşi bir POKéMON'u veya bir\nEĞİTİMCİ'yi yendiğinizde ışık daha\lparlak hale gelir.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules:
	.string "SAVAŞ ÇANTASI, PİRAMİT'teyken\nÇANTANIZ olarak hizmet eder.\pSeviye 50 ve Açık Seviye maceraları\niçin birer tane olmak üzere iki ayrı\lSAVAŞ ÇANTASI vardır.\pHer biri on çeşit eşyadan en fazla 99\nparça alabilir.\pGörevinizde başarısız olursanız SAVAŞ\nÇANTASININ içindekiler kaybolur.$"


