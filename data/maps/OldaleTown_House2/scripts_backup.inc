OldaleTown_House2_MapScripts::
	.byte 0

OldaleTown_House2_EventScript_Woman::
	msgbox OldaleTown_House2_Text_PokemonLevelUp, MSGBOX_NPC
	end

OldaleTown_House2_EventScript_Man::
	msgbox OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon, MSGBOX_NPC
	end

OldaleTown_House2_Text_PokemonLevelUp:
	.string "POKéMON'lar savaştıkça seviye\n"
	.string "atlarlar ve güçlenirler.$"

OldaleTown_House2_Text_YoullGoFurtherWithStrongPokemon:
	.string "Eğer POKéMON'unu yeterince\n"
	.string "güçlendirirsen, çok uzaklara\l"
	.string "gitme gücünü kendinde bulursun.$"



