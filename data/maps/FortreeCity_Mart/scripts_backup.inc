FortreeCity_Mart_MapScripts::
	.byte 0

FortreeCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart FortreeCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_REVIVE
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_WOOD_MAIL
	.2byte ITEM_NONE
	release
	end

FortreeCity_Mart_EventScript_Woman::
	msgbox FortreeCity_Mart_Text_SuperRepelBetter, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Girl::
	msgbox FortreeCity_Mart_Text_StockUpOnItems, MSGBOX_NPC
	end

FortreeCity_Mart_EventScript_Boy::
	msgbox FortreeCity_Mart_Text_RareCandyMakesMonGrow, MSGBOX_NPC
	end

FortreeCity_Mart_Text_SuperRepelBetter:
	.string "SÜPER SPREY uzun süre kalır,\n"
	.string "ve seni daha uzun süre korur.\p"
	.string "Sıradan SPREYDEN çok daha iyi.$"

FortreeCity_Mart_Text_StockUpOnItems:
	.string "Her zaman fazladan eşya depolarım.\n"
	.string "Elbet ihtiyacım olur.\p"
	.string "Ne zaman ne olacağını bilemezsin.\n"
	.string "Güvende olmak en iyisi!$"

FortreeCity_Mart_Text_RareCandyMakesMonGrow:
	.string "NADİR ŞEKER, POKéMON'una\n"
	.string "bir seviye atlatır.$"

