.set LOCALID_ATTENDANT, 1

VerdanturfTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, VerdanturfTown_BattleTentCorridor_OnFrame
	.byte 0

VerdanturfTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

VerdanturfTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_VERDANTURF_TOWN_BATTLE_TENT_BATTLE_ROOM, 6, 5
	waitstate
	releaseall
	end

VerdanturfTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

VerdanturfTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
VerdanturfTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

VerdanturfTown_ContestHall_Text_WhichContestYouEntering:
	.string "Hangi yarışmaya katılıyorsun?\nBir tavsiye ister misin?\pHerhangi bir yarışmada, örneğin bir\nŞİRİNLİK YARIŞMASI'nda, ilk turda\lPOKéMON'unu sadece şirinliğe göre\ldeğerlendirdiklerini sanmıyorum.\pPOKéMON'u daha iyi yetiştirmenin\nyollarını bulmalısın.$"

VerdanturfTown_ContestHall_Text_RaisedMonToBeCute:
	.string "POKéMON'umu sevimli olması için\nyetiştirdim.\pPOKéMON'umu şirinlik yarışmasına\nsokabileceğimi öğrendim!\pPOKéMON'umu sevgiyle büyüttüğüm için\nçok mutluyum…$"

VerdanturfTown_ContestHall_Text_MyMonRules:
	.string "Benim PokéMON'um müthiştir!\pHavalı, sert ama güzel, sevimli ve\nakıllı. Eksiksiz!\pHer yarışmayı kazanabilir.$"

VerdanturfTown_ContestHall_Text_NormalRankStage:
	.string "POKéMON YARIŞMALARI NORMAL RÜTBE\nSAHNESİ!$"


