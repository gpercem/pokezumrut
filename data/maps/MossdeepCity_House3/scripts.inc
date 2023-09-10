MossdeepCity_House3_MapScripts::
	.byte 0

MossdeepCity_House3_EventScript_SuperRodFisherman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SUPER_ROD, MossdeepCity_House3_EventScript_ReceivedSuperRod
	msgbox MossdeepCity_House3_Text_YouWantSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_House3_EventScript_DeclineSuperRod
	msgbox MossdeepCity_House3_Text_SuperRodIsSuper, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	setflag FLAG_RECEIVED_SUPER_ROD
	msgbox MossdeepCity_House3_Text_TryDroppingRodInWater, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_ReceivedSuperRod::
	msgbox MossdeepCity_House3_Text_GoAfterSeafloorPokemon, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_EventScript_DeclineSuperRod::
	msgbox MossdeepCity_House3_Text_DontYouLikeToFish, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House3_Text_YouWantSuperRod:
	.string "Hey sen, EĞİTMEN!\nSÜPER OLTA gerçekten süperdir!\pİstediğinizi söyle, ama bu bebek\ndeniz dibinden bile POKéMON\lyakalayabilir!\pNe düşünüyorsun?\nİstiyorsun, değil mi?$"

MossdeepCity_House3_Text_SuperRodIsSuper:
	.string "Emin ol, emin ol!\nSonuçta, SÜPER OLTA gerçekten\lsüperdir!$"

MossdeepCity_House3_Text_TryDroppingRodInWater:
	.string "Eğer su bulursan, oltanı salla\nve ne çıkacağını gör!$"

MossdeepCity_House3_Text_DontYouLikeToFish:
	.string "Ha?\nBalık tutmayı sevmez misin?$"

MossdeepCity_House3_Text_GoAfterSeafloorPokemon:
	.string "SUPER OLTA ile deniz dibindeki\nPOKéMON'ların peşinden gidebilirsin.$"


