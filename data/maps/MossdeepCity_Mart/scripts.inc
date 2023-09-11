MossdeepCity_Mart_MapScripts::
	.byte 0

MossdeepCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MossdeepCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MossdeepCity_Mart_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_DIVE_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_NONE
	release
	end

MossdeepCity_Mart_EventScript_Woman::
	msgbox MossdeepCity_Mart_Text_ReviveIsFantastic, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Boy::
	msgbox MossdeepCity_Mart_Text_MaxRepelLastsLongest, MSGBOX_NPC
	end

MossdeepCity_Mart_EventScript_Sailor::
	msgbox MossdeepCity_Mart_Text_NetAndDiveBallsRare, MSGBOX_NPC
	end

MossdeepCity_Mart_Text_ReviveIsFantastic:
	.string "CANLANDIRICI muhteşemdir!\pBayılmış bir POKéMON'a ver ve\nPOKéMON ayağa kalksın.\pAncak dikkatli ol, CANLANDIRICI\nsaldırıların kullanılmış PP'sini geri\lgetirmez.$"

MossdeepCity_Mart_Text_MaxRepelLastsLongest:
	.string "MAKS SPREY, tüm zayıf POKéMON'ları\nuzak tutar.\pSpreyler arasında en uzun süre\ndayananı budur.$"

MossdeepCity_Mart_Text_NetAndDiveBallsRare:
	.string "AĞ ve DALIŞ TOPLARI sadece\nMOSSDEEP'te üretilen nadir POKé\lTOPLARIDIR.\pAĞ TOPU, BÖCEK tipi ve SU tipi\nPOKéMON'lara karşı etkilidir.\pDALIŞ TOPU en iyi denizin dibindeki\nPOKéMON'larda işe yarar.$"
	