DewfordTown_House1_MapScripts::
	.byte 0

DewfordTown_House1_EventScript_Man::
	msgbox DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Woman::
	msgbox DewfordTown_House1_Text_LifeGoesSlowlyOnIsland, MSGBOX_NPC
	end

DewfordTown_House1_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox DewfordTown_House1_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

DewfordTown_House1_Text_LotToBeSaidForLivingOnIsland:
	.string "Böyle küçük bir adada POKéMON ve aile\nile uyum içinde yaşamak için\lsöylenecek çok şey var.$"

DewfordTown_House1_Text_LifeGoesSlowlyOnIsland:
	.string "Kocamla burada evlenmek için\nSLATEPORT ŞEHRİ'nin limanından\lgelmiştik.\pBu küçük adada hayat yavaş akıyor.\nAma güzel denizle çevrili olmak da bir\lmutluluk.$"

DewfordTown_House1_Text_Zigzagoon:
	.string "ZIGZAGOON: Guguuh!$"
