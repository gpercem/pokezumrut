MossdeepCity_House1_MapScripts::
	.byte 0

MossdeepCity_House1_EventScript_BlackBelt::
	lock
	faceplayer
	bufferleadmonspeciesname STR_VAR_1
	msgbox MossdeepCity_House1_Text_HmmYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPokeblockNameByMonNature
	goto_if_eq VAR_RESULT, 0, MossdeepCity_House1_EventScript_NeutralNature
	msgbox MossdeepCity_House1_Text_ItLikesXPokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_NeutralNature::
	msgbox MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_Woman::
	msgbox MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes, MSGBOX_NPC
	end

MossdeepCity_House1_Text_HmmYourPokemon:
	.string "Hmm!\nŞu sendeki {STR_VAR_1}…$"

MossdeepCity_House1_Text_ItLikesXPokeblocks:
	.string "{STR_VAR_1} seviyor, değil mi?\pHayır, bundan eminim!\nKesinlikle {STR_VAR_1} seviyor!$"

MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks:
	.string "Herhangi bir {POKEBLOCK}'u seviyor\nya da sevmiyor gibi görünmüyor.$"

MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes:
	.string "Kocam POKéMON'ların ne tür\n{POKEBLOCK}'lardan hoşlandığını bir\lbakışta anlayabilir.$"


