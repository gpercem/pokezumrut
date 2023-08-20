.set LOCALID_STAIR_GUARD, 2

RustboroCity_DevonCorp_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition:
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
	setobjectxyperm LOCALID_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter::
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
	.string "Merhaba.\nDEVON ŞİRKETİ'ne hoş geldiniz.\pHayatınızı güzelleştiren ürünler ve\nilaçlar üretmekten gurur duyuyoruz.$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
	.string "Araştırma personelimizden biri aptalca\nbir şekilde önemli bir paketi çaldırdı.$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
	.string "Hey, şu KOŞU AYAKKABILARI!\nOnlar bizim ürünlerimizden biri!\pBirinin bizim yaptığımız ürünü\nkullandığını görmek beni mutlu ediyor.$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
	.string "Şu çalınan paket.\pElbette önemli ama herkesin\nkullanabileceği bir şey değil.\pTahminime göre, o soyguncu pek zeki biri\ndeğildi.$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
	.string "Görünüşe göre çalınan DEVON\nPAKEDİ'ni geri almışlar.$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
	.string "Üzgünüm, buraya sadece yetkili kişilerin\ngirmesine izin veriliyor.$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
	.string "Bu aptallığın da ötesinde.\nNasıl soyulabiliriz ki?$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
	.string "Merhabalar!\nBurada her zaman hoş karşılanırsınız!$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
	.string "Taş ve metal örnekleri cam vitrinde\nsergileniyor.\pÜzerinde bazı yazılar olan bir panel var.\pDEVON ŞİRKETİ, taş ocaklarından\ntaş üreterek işe başladı.\pŞirket ayrıca kumdaki talaşlardan demir\nde üretiyordu.\pDEVON, hammadde üreticisi olarak\nbaşladığı bu yolda böyle gelişti.\pDEVON artık çok çeşitli endüstriyel\nürünlerin üreticisidir.$"

RustboroCity_DevonCorp_1F_Text_ProductDisplay:
	.string "Prototipler ve test ürünleri cam vitrini\ndolduruyor.\pBu panelde bir açıklama var…\pEndüstriyel ürünlerin yanı sıra DEVON\nartık daha iyi yaşam tarzları için\lçeşitli eşyalar ve eczacılık ürünleri de\lpazarlamaktadır.\pYakın zamanda DEVON, POKé TOPLARI ve\nPOKéNAV sistemleri de dahil olmak üzere\lPOKéMON EĞİTMENLERİ için araçlar\lpazarlamaya başladı.$"


