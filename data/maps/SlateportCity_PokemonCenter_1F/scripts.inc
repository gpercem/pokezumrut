.set LOCALID_NURSE, 1

SlateportCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SlateportCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SlateportCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_SLATEPORT_CITY
	call Common_EventScript_UpdateBrineyLocation
	end

SlateportCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

SlateportCity_PokemonCenter_1F_EventScript_Sailor::
	msgbox SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_EventScript_Woman::
	msgbox SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend, MSGBOX_NPC
	end

SlateportCity_PokemonCenter_1F_Text_RaiseDifferentTypesOfPokemon:
	.string "Savaşmak için bir ipucu ister misin?\pFarklı POKéMON türlerini dengeli bir\nşekilde yetiştirmek diyebilirim.\pSadece bir POKéMON'u güçlü yapmak iyi\ndeğildir.\pEğer tür dezavantajı varsa, hiç şansı\nolmayabilir.$"

SlateportCity_PokemonCenter_1F_Text_TradedMonWithFriend:
	.string "Arkadaşlarımla POKéMON takası\nyapıyorum.\pEğer takas edilen POKéMON'un elinde\nbir eşya varsa, bu beni iki kat daha\lmutlu ediyor!$"


