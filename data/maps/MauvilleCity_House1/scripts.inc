MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM06, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM06
	setflag FLAG_RECEIVED_HM06
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
	.string "Vuuhu!\pİnsanların bana KAYA DARBESİ ADAM\ndediğini duyuyorum ama ben bunu biraz\laşağılayıcı buluyorum.\pBence biraz daha saygıyı hak ediyorum,\nbelki de KAYA KRALI gibi.\pVuuhu!\pHer neyse, POKéMON'un oldukça güçlü\ngörünüyor.\pBunu sevdim!\nAl, bu GİZLİ MAKİNE senindir!$"

MauvilleCity_House1_Text_ExplainRockSmash:
	.string "Bu HM'de KAYA DARBESİ var.\pEğer yolunu kesen büyük kayalarla\nkarşılaşırsan…\pO zaman HM saldırısını kullan ve onları\nyolundan çek!\pEvet, evet!\nKayaları parçala ve geç! Vuuhu!$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
	.string "Evet, eğer bir kayayı parçalarsan,\nkarşına bir POKéMON çıkabilir.\pVuuhu!$"


