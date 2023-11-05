.set LOCALID_SS_TIDAL, 2
.set LOCALID_FERRY_ATTENDANT, 3
.set LOCALID_MANIAC_1, 9
.set LOCALID_MANIAC_2, 10
.set LOCALID_GIRL, 12
.set LOCALID_CAMPER, 14
.set LOCALID_FISHERMAN_2, 18
.set LOCALID_MAN_4, 23

BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

BattleFrontier_OutsideWest_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
	.string "Burası SAVAŞ KUBBESİ!\nSüperstar olma yolunda!$"

BattleFrontier_OutsideWest_Text_BattleFactorySign:
	.string "Burası SAVAŞ FABRİKASI!\nEn güçlü POKéMON'lar!$"

BattleFrontier_OutsideWest_Text_BattlePikeSign:
	.string "Burası SAVAŞ YILANI! Üç yoldan birini\nseçin!$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
	.string "Burası SAVAŞ KULESİ.\pANTRENÖRLER, eleme tarzı maçlar için\nen iyi yetişmiş POKéMON'larını getirir.$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
	.string "Merhaba, gemi için mi geldiniz?\nBiletinizi görebilir miyim?$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
	.string "{PLAYER}'ın BİLETİ yok…\pÇok özür dilerim.\pFeribota binmek için biletiniz olmalı.$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
	.string "{PLAYER} BİLETİ gösterdi.\pMükemmel! Bu bilet geçerli.\pNereye gitmek istersiniz?$"

BattleFrontier_OutsideWest_Text_SlateportItIs:
	.string "SLATEPORT ŞEHRİ, o zaman!$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
	.string "LILYCOVE ŞEHRİ, o zaman!$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
	.string "Lütfen başka bir zaman bizimle yelken\naçın!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
	.string "Lütfen gemiye binin ve kalkışı\nbekleyin.$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
	.string "O zaman nereye gitmek istersiniz?$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
	.string "Arkadaşlarım arasında en iyisi benim.\nAma burada… İşe yaramaz oldum!$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
	.string "SAVAŞ KULESİ'ne gitmek istiyorum ama\nelimde SAVAŞ ORTADOĞUSU haritası\lolmasına rağmen onu bulamıyorum.\pBurası çok büyük!$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
	.string "Buraya gelir gelmez bir meydan okuma\nyapmak istedim.\pAma yolda beni deniz tuttu…$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "Buraya herkes gelemez, biliyorsunuz\ndeğil mi?\pBuraya sadece güçlü olduğu kabul\nedilen eğitmenler getirilir.\pBu yüzden birçok eğitmenin SAVAŞ\nÇATISI'ndan haberi bile yok.$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
	.string "Hey, kardeşim.\pHiç POKéMON'umuz olmasa bile meydan\nokuyabileceğimize emin misin?$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
	.string "Eminim her şey yoluna girecektir.\pSanırım…\pAma o büyük korkunç adamı hatırlıyor\nmusun? Sana POKéMON'u ödünç\lvereceğim! demişti.$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
	.string "Burası SAVAŞ FABRİKASI. Burada\ngüçlü POKéMON'lar kiralayabilirsin.\pAma merak ediyordum da…\nBu kiralık POKéMON'lar kimin?$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "SEVİPER yüzünden SAVAŞ YILANINA\ngirmekten korkuyorum.\pAma buraya kadar geldim, bu yüzden her\nşeyi fethetmeye çalışacağım!\l…Ürperdim…$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
	.string "Taş, kağıt, makas oynayalım! Bir, iki,\nüç!\p… … … … … …$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
	.string "Yaşasın! Ben kazandım!\nMeydan okumaya gideceğim!$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
	.string "Oh, hayır… Kaybettim.\pSanırım bugün pek şanslı değilim.\nSAVAŞ YILANI meydan okumamı\lyarına erteleyeceğim.$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
	.string "Sanırım burada bilinmeyen bir nedenle\nbalık tutmayı savaşmaya tercih eden\ltek kişi benim.\pNe? Burada hiçbir şey yakalayamıyor\nmusun? Bu hayal kırıklığı…$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
	.string "Bugün, ne olursa olsun, bir Sembol elde\nedene kadar savaşmaya devam\ledeceğim.$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
	.string "SAVAŞ KUBBESİ'ne meydan okumaya\nmı gidiyorsun?\pSana iyi şanslar dilerim. İkimiz de\nyolumuzu kazanalım ve meydan\lokumalarda buluşalım.$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
	.string "Büyükbaba, bu tarafa! SAVAŞ KUBBESİ\nburada! Git yakala onları, büyükbaba!$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
	.string "Demek burası SAVAŞ KUBBESİ?\nCentilmenlerin beni yenmesine izin\lvermeyeceğim!\pAma giriş nerede?$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
	.string "Çok uzun zaman önce burada hiçbir şey\nyoktu.\pAma şimdi şuraya bak! İnanılmaz! Bunu\ngörmesi için annemi getireceğim.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "Sonunda SAVAŞ SINIRI'na geldim!\pEminim ki insanların dikkatlerini\nçekebilirim!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "Ham, ham.\pGörünüşe göre bu meydan sert\ninsanlarla dolu.\pHam, ham.$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
	.string "Ham, ham…\pBir süre önce SAVAŞ YILANI'nda\nyaşlı bir kadınla tanıştım.\pGerçekten huysuz bir şekilde\nkorkutucu gözleri vardı.\pHam, ham.\pÇok sinirlendi: Yemeyi keser misin!\nSonra bana saldırdı.\pTüyler ürpertici ve korkutucu bir\ndeneyimdi.\pHam, ham.$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
	.string "Ha? Ağzından çıkanı kulağın duyuyor\nmu? Bu bir şey değil!\pEn son onun için tezahürat yaptığımda\ngözlerimiz buluştu ve kıvılcımlar\luçuştu!$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
	.string "Ne?! Pfft!\pBu sadece senin yanında oturduğum için\noldu!\pLİDER sadece tezahüratım çok\nyüksek olduğu için bize doğru baktı!$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
	.string "Şşşt!\nSessiz olun!\pSiz fanatik taraftarlar, salon\nlideri için tezahürat yapmaya devam\letmelisiniz!\pLİDER benim!\nBenim için tek idol!$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
	.string "Şurada kavga eden insanlar.\pİnanması zor ama onlar da bir zamanlar\nANTRENÖRDÜ, hem de iyi antrenörlerdi.\pEskiden inanılmaz derecede serttiler\nve çok da ünlüydüler.\pAma bir turnuvada bu belirli ANTRENÖR\ntarafından yok edildiler.\pO kadar iyi kırbaçlandılar ki,\nANTRENÖR'e vuruldular.\pŞimdi sadece ANTRENÖR hayranı oldular.\nArtık her gün SAVAŞ KUBBESİ'nde\lidol için tezahürat yapmaya gidiyorlar.$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
	.string "Birisinin SAVAŞ SINIRI'nda bir\nyerde alışılmadık derecede uzun\lkuyruğu olan bir POKéMON gördüğüne\ldair bir söylenti duydum.\pÇok sevimli olmalı. Bundan eminim.\pZorluklar bekleyebilir. Keyifli\nyaratığı bulmaya kararlıyım!$"


