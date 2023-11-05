.set LOCALID_CAPT_STERN, 1
.set LOCALID_ARCHIE, 2
.set LOCALID_GRUNT_1, 3
.set LOCALID_GRUNT_2, 4

SlateportCity_OceanicMuseum_2F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern::
	lock
	followerintopokeball
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, TRUE
	addobject LOCALID_GRUNT_1
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_GRUNT_2
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	call_if_ne VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	call_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	call_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_ARCHIE
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_GOODS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	removeobject LOCALID_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	call_if_eq VAR_REGISTER_BIRCH_STATE, 0, SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	updatefollowerpokemongraphic
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch::
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts::
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest::
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth:
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest:
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle:
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated:
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_faster_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment::
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel::
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica::
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3::
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts:
	.string "Öyle mi?\nSTERN'i mi arıyorsun?\pŞu anda tam karşında duruyor.\pHey!\nBunlar BAY STONE'dan sipariş\lettiğim parçalar olmalı.\pTeşekkür ederim! Bu harika!\nArtık keşif gezimiz için hazırlanabiliriz.$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts:
	.string "Hehehe, durun!\nO parçalar bizimdir!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou:
	.string "KAPTAN STERN: Ne?\nSiz kimsiniz?$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua:
	.string "Biz AQUA TAKIMI'yız!\pPatronumuz o parçaları istiyor!\nÇeneni kapa ve onları ver!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat:
	.string "Olamaaaz!\nBir çocuk beni yendi!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious:
	.string "Adamım, bu bir felaket…\nPatron çok kızacak…$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis:
	.string "Hımph, sümüklü bebe!\nBırak ben halledeyim!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat:
	.string "Ne?!\nBen de kaybettim!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid:
	.string "Şimdi ne olacak? Eğer parçaları\nalamazsak, başımız belada!\pİşgüzar bir çocuk tarafından\nyenileceğimizi hesaba katmamıştım!$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong:
	.string "Parçaları çalmanın neden bu kadar\nuzun sürdüğünü görmeye geldim.\lSiz aptallar bir çocuk tarafından mı\loyalanıyordunuz?$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning:
	.string "Biz AQUA TAKIMI'yız ve denizi\nseviyoruz!\pVe ben AQUA TAKIMI'nın lideri,\nARCHİE'yim!\pBize neden müdahale ediyorsun?\p…Hayır! Olamaz!\nSen MAGMA TAKIMI'ndan mısın?\pBekle, bu doğru olamaz.\nRolüne uygun giyinmemişsin.\p… … … … … …\n… … … … … …\pPOKéMON'lar, insanlar…\nTüm yaşam denize bağlıdır.\pBu yüzden AQUA TAKIMI, kendini\ndenizlerin genişlemesine adamıştır.\pSence de öyle değil mi?\nYaptığımız şey muhteşem bir\lgirişim.\pAh, güzel…\nAsıl amacımızı anlamak için hâlâ\lçok gençsin.\pAma seni uyarıyorum, bir daha\nplanlarımıza müdahale etmeyi\laklından bile geçirme.\pSonuçları sana pahalıya patlar!\pVe bunu sakın unutma!$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs:
	.string "KAPTAN STERN: Sen…\nTamam, demek adın {PLAYER}{KUN}…\pHer neyse, bu gergin bir durumdu!\nBeni kurtardığın için teşekkürler!\pAa, evet, neredeyse unutuyordum,\nDEVON parçalarını getirmiştin!$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo:
	.string "KAPTAN STERN: Eyvah!\nKaybedecek zamanımız yok!\pÇok yakında okyanus tabanı keşif\ngezimize çıkmamız gerekiyor.\pTekrar teşekkürler, ama şimdi gitmem\ngerek!\pYine de etrafta dolaşmaktan ve\ntesislerimize göz atmaktan çekinme.$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip:
	.string "Burada bir gemi maketi gördüm.\pBana DEWFORD yakınlarındaki\nterk edilmiş gemiyi hatırlattı…$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum:
	.string "Sakın müzenin içinde koşturmaya\nkalkma!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine:
	.string "Vay canına, denizaltı harika!\nBen de binmek istiyorum!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1:
	.string "“SU KALİTESİ ÖRNEK 1” yazıyor.\pDenizin tamamı birbirine bağlı, ancak\nsu bölgelere göre farklılık gösteriyor\lgibi görünüyor.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2:
	.string "“SU KALİTESİ ÖRNEK 2” yazıyor.\pDeniz suyunun tuzluluk oranı da\nbölgelere göre farklılık gösteriyor\lmu?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment:
	.string "Lastik bir top genişliyor ve küçülüyor.\p“Denizde suyun kendi ağırlığı basınç\nuygular.\pSığ sularda basınç çok ağır değildir.\pAncak aşırı derin sularda basınç küçük\nbir alanda on binlerce tona bile\lulaşabilir.”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel:
	.string "“HOENN BÖLGESİ MODELİ”\pHOENN bölgesinin minyatür bir\nkopyası.\pLİTTLEROOT KÖYÜ bunun neresinde?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay:
	.string "Deniz suyunun akışını gösteren bir\nekran.\p“Denizin dibine yakın yerlerde su,\nsıcaklık ve tuzluluk gibi faktörlerdeki\lfarklılıklar nedeniyle akar.”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay:
	.string "Deniz suyunun akışını gösteren bir\nekran.\p“Yüzeye doğru, deniz suyu rüzgârlar\ntarafından yönlendirilen akıntılar\lşeklinde akar.”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica:
	.string "“S.S. TİDAL GEMİSİ”\pSTERN'in tersanesinde yapım\naşamasında olan geminin bir kopyası.$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica:
	.string "“KEŞİF DENİZALTISI 1”\pYüksek performanslı okyanus tabanı\nkeşif denizaltısının bir kopyası.$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica:
	.string "“DALGIÇ KAPSÜLÜ”\pDeniz tabanı keşfi için kompakt,\ninsansız bir kapsülün kopyası.$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica:
	.string "“S.S. ANNE”\pDünyanın çevresini dolaşan lüks yolcu\ngemisinin bir kopyası.$"


