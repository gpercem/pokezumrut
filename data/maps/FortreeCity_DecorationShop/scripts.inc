FortreeCity_DecorationShop_MapScripts::
	.byte 0

FortreeCity_DecorationShop_EventScript_PokefanM::
	msgbox FortreeCity_DecorationShop_Text_MerchandiseSentToPC, MSGBOX_NPC
	end

FortreeCity_DecorationShop_EventScript_Girl::
	msgbox FortreeCity_DecorationShop_Text_BuyingDeskForDolls, MSGBOX_NPC
	end

FortreeCity_DecorationShop_EventScript_ClerkDesks::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration FortreeCity_DecorationShop_PokemartDecor_Desks
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_DecorationShop_PokemartDecor_Desks:
	.2byte DECOR_SMALL_DESK
	.2byte DECOR_POKEMON_DESK
	.2byte DECOR_HEAVY_DESK
	.2byte DECOR_RAGGED_DESK
	.2byte DECOR_COMFORT_DESK
	.2byte DECOR_BRICK_DESK
	.2byte DECOR_CAMP_DESK
	.2byte DECOR_HARD_DESK
	.2byte DECOR_NONE
	release
	end

FortreeCity_DecorationShop_EventScript_ClerkChairs::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration FortreeCity_DecorationShop_PokemartDecor_Chairs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
FortreeCity_DecorationShop_PokemartDecor_Chairs:
	.2byte DECOR_SMALL_CHAIR
	.2byte DECOR_POKEMON_CHAIR
	.2byte DECOR_HEAVY_CHAIR
	.2byte DECOR_RAGGED_CHAIR
	.2byte DECOR_COMFORT_CHAIR
	.2byte DECOR_BRICK_CHAIR
	.2byte DECOR_CAMP_CHAIR
	.2byte DECOR_HARD_CHAIR
	.2byte DECOR_NONE
	release
	end

FortreeCity_DecorationShop_Text_MerchandiseSentToPC:
	.string "Buradan satın aldığınız eşyalar\n"
	.string "PC'nize gönderilir.\p"
	.string "Bu harika! Keşke benim evime de böyle\n"
	.string "teslim ediebilseydi.$"

FortreeCity_DecorationShop_Text_BuyingDeskForDolls:
	.string "Tatlı PELUŞLARIMI üstüne koyabilmek\n"
	.string "için bir güzel masa alıyorum.\p"
	.string "Eğer GİZLİ ÜSSÜMÜ dekore etmeseydim\n"
	.string "PELUŞLARIM kirlenecek ve\l"
	.string "kıymıklarla dolacaktı.$"

