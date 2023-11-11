LavaridgeTown_House_MapScripts::
	.byte 0

LavaridgeTown_House_EventScript_OldMan::
	msgbox LavaridgeTown_House_Text_WifeWarmingEggInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_House_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox LavaridgeTown_House_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LavaridgeTown_House_Text_WifeWarmingEggInHotSprings:
	.string "Eşim kaplıcada bir yumurtaya\nbakıyor. Bana böyle demişti.\pBakımevine iki POKéMON bırakmış.\nBakımevi sahipleri bir yumurta\lbulmuş ve eşime vermiş!$"

LavaridgeTown_House_Text_Zigzagoon:
	.string "ZİGZAGOON: Pişuu!$"


