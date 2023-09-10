SootopolisCity_House4_MapScripts::
	.byte 0

SootopolisCity_House4_EventScript_Man::
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman::
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea:
	.string "Dinle, sana iyi bir şey söyleyeceğim.\pBuralarda denizin içinde antik bir\nharabe olması gerekiyor.\pOrada keşfedilmeyi bekleyen hazineler\nolabilir.$"

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon:
	.string "Antik hazineler…\pVar olsalardı güzel olurdu ama\nolmasalar bile POKéMON'umla su altında\lgezintiye çıkmak çok güzel.$"

SootopolisCity_House4_Text_Azumarill:
	.string "AZUMARİLL: Marurii.$"


