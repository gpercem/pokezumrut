.set LOCALID_NURSE, 1
.set LOCALID_LANETTE, 4

FallarborTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FallarborTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

FallarborTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FallarborTown_PokemonCenter_1F_EventScript_Girl::
	msgbox FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_ExpertM::
	msgbox FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_Lanette::
	lock
	faceplayer
	msgbox FallarborTown_PokemonCenter_1F_Text_LanetteGreeting, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_NORTH, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth
	case DIR_WEST, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth::
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest::
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExited::
	playse SE_SLIDING_DOOR
	removeobject LOCALID_LANETTE
	clearflag FLAG_HIDE_LANETTES_HOUSE_LANETTE
	release
	end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Text_LanetteGreeting:
	.string "Merhaba.\nSen misin?\pDemek adın {PLAYER}{KUN}.\nEğitmen olduğunu görebiliyorum.\pYani benim geliştirdiğim POKéMON\nDepolama Sistemini kullanıyorsun.\pBu sonuca basit bir tümdengelimle\nulaştım.\pBenimle konuştun çünkü bu\nbilgisayardaki bir şeye erişmek\listedin.\pAh, kusura bakma.\nBen LANETTE.\pDürüst olmak gerekirse, seninle\ntanıştığıma memnun oldum.\lDepolama Sistemini kullanman harika.\pEğer mümkünse, lütfen beni evimde\nziyaret et. Evim ROTA 114 üzerinde.$"

FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown:
	.string "Acaba POKéMON'lar çok çok uzun zaman\nönce neye benziyorlardı?\pBelki kasabanın kenarındaki FOSİL\nMANYAĞI bunu bilir.$"

FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees:
	.string "FALLARBOR'un tarlalarına, volkanik\nkülde bile gelişen dayanıklı ağaçların\lfidelerini dikiyoruz.$"


