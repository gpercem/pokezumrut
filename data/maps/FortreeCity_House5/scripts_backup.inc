FortreeCity_House5_MapScripts::
	.byte 0

FortreeCity_House5_EventScript_PokefanF::
	msgbox FortreeCity_House5_Text_TreeHousesAreGreat, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Man::
	msgbox FortreeCity_House5_Text_AdaptedToNature, MSGBOX_NPC
	end

FortreeCity_House5_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox FortreeCity_House5_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House5_Text_TreeHousesAreGreat:
	.string "FORTREE'nin ağaç evleri müthiş!\p"
	.string "Bence burası POKéMONLAR ile birlikte\n"
	.string "yaşanılabilecek en iyi yer.$"

FortreeCity_House5_Text_AdaptedToNature:
	.string "POKéMONLAR ve insanlar hayatta\n"
	.string "kalabilmek için doğaya adapte\loldular.\p"
	.string "Rahatça yaşabilmek için doğayı\n"
	.string "değiştirmemize gerek yok.$"

FortreeCity_House5_Text_Zigzagoon:
	.string "ZIGZAGOON: Bufuu!$"

