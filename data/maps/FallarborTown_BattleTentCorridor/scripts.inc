.set LOCALID_ATTENDANT, 1

FallarborTown_BattleTentCorridor_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, FallarborTown_BattleTentCorridor_OnFrame
	.byte 0

FallarborTown_BattleTentCorridor_OnFrame:
	map_script_2 VAR_TEMP_0, 0, FallarborTown_BattleTentCorridor_EventScript_EnterCorridor
	.2byte 0

FallarborTown_BattleTentCorridor_EventScript_EnterCorridor::
	lockall
	setvar VAR_TEMP_0, 1
	applymovement LOCALID_ATTENDANT, FallarborTown_BattleTentCorridor_Movement_WalkToDoor
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_BattleTentCorridor_Movement_WalkToDoor
	waitmovement 0
	opendoor 2, 1
	waitdooranim
	applymovement LOCALID_ATTENDANT, FallarborTown_BattleTentCorridor_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, FallarborTown_BattleTentCorridor_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 1
	waitdooranim
	setvar VAR_0x8006, 0
	warp MAP_FALLARBOR_TOWN_BATTLE_TENT_BATTLE_ROOM, 4, 4
	waitstate
	releaseall
	end

FallarborTown_BattleTentCorridor_Movement_WalkToDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

FallarborTown_BattleTentCorridor_Movement_PlayerEnterDoor:
	walk_up
FallarborTown_BattleTentCorridor_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

FallarborTown_ContestHall_Text_DoAllRightInPreliminary:
	.string "Ön eleme turunda iyi iş çıkardık ama\ntemyizi asla kazanamayız…\pBelki de diğer yarışmacıların ne\nyaptığını izlemem gerektiği anlamına\lgeliyordur…$"

FallarborTown_ContestHall_Text_MonAllTheseRibbons:
	.string "Bak! POKéMON'um bütün bu\nKURDELELERİ kazandı!\pPOKéMON'un hiç KURDELE kazandı mı?\nOnları POKéNAV'ından kontrol\ledebilirsin.$"

FallarborTown_ContestHall_Text_CantWinEverywhere:
	.string "SALON LİDERLERİNİ yenemiyorum…\nHiçbir yarışma kazanamıyorum.\pBuraya, oraya ve her yere gittim ama\nhepsi boşunaydı.$"

FallarborTown_ContestHall_Text_SuperRankStage:
	.string "POKéMON YARIŞMALARI\nSÜPER RÜTBESİ!$"


