.set LOCALID_ARCHIE, 1
.set LOCALID_MAXIE, 2
.set LOCALID_TABITHA, 3
.set LOCALID_MAGMA_GRUNT_2, 22
.set LOCALID_MAGMA_GRUNT_1, 29


MtChimney_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtChimney_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtChimney_OnTransition
	.byte 0

MtChimney_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 1
	end

MtChimney_OnResume:
	setstepcallback STEP_CB_ASH
	end

MtChimney_EventScript_Archie::
	lock
	faceplayer
	call_if_unset FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieGoStopTeamMagma
	call_if_set FLAG_EVIL_LEADER_PLEASE_STOP, MtChimney_EventScript_ArchieBusyFighting
	closemessage
	applymovement LOCALID_ARCHIE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_EVIL_LEADER_PLEASE_STOP
	release
	end

MtChimney_EventScript_ArchieGoStopTeamMagma::
	msgbox MtChimney_Text_ArchieGoStopTeamMagma, MSGBOX_DEFAULT
	return

MtChimney_EventScript_ArchieBusyFighting::
	msgbox MtChimney_Text_ArchieIHaveMyHandsFull, MSGBOX_DEFAULT
	return

MtChimney_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MtChimney_Text_MeteoriteWillActivateVolcano, MSGBOX_DEFAULT
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAXIE, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAXIE, Common_Movement_Delay48
	waitmovement 0
	msgbox MtChimney_Text_MaxieIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_MAXIE_MT_CHIMNEY, MtChimney_Text_MaxieDefeat
	msgbox MtChimney_Text_MaxieYouHaventSeenLastOfMagma, MSGBOX_DEFAULT
	closemessage
	delay 30
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_TABITHA
	removeobject LOCALID_MAGMA_GRUNT_2
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_MAGMA
	fadescreen FADE_FROM_BLACK
	setobjectxyperm LOCALID_ARCHIE, 10, 12
	addobject LOCALID_ARCHIE
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieApproachPlayerEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieApproachPlayerNorth
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox MtChimney_Text_ArchieThankYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, MtChimney_EventScript_ArchieExitEast
	call_if_eq VAR_FACING, DIR_NORTH, MtChimney_EventScript_ArchieExitNorth
	removeobject LOCALID_ARCHIE
	setflag FLAG_HIDE_MT_CHIMNEY_TEAM_AQUA
	setflag FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY
	clearflag FLAG_HIDE_FALLARBOR_HOUSE_PROF_COZMO
	setflag FLAG_HIDE_METEOR_FALLS_1F_1R_COZMO
	clearflag FLAG_HIDE_MT_CHIMNEY_LAVA_COOKIE_LADY
	releaseall
	end

MtChimney_EventScript_ArchieApproachPlayerEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieApproachPlayerNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieApproachPlayerNorth
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitEast::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitEast
	waitmovement 0
	return

MtChimney_EventScript_ArchieExitNorth::
	applymovement LOCALID_ARCHIE, MtChimney_Movement_ArchieExitNorth
	waitmovement 0
	return

MtChimney_EventScript_LavaCookieLady::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MtChimney_Text_LavaCookiesJust200, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_DeclineLavaCookie
	checkmoney 200
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_NotEnoughMoney
	msgbox MtChimney_Text_ThankYouDear, MSGBOX_DEFAULT
	checkitemspace ITEM_LAVA_COOKIE
	call_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RemoveMoney
	giveitem ITEM_LAVA_COOKIE
	goto_if_eq VAR_RESULT, FALSE, MtChimney_EventScript_BagIsFull
	hidemoneybox
	release
	end

MtChimney_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_RemoveMoney::
	removemoney 200
	updatemoneybox
	return

MtChimney_EventScript_DeclineLavaCookie::
	msgbox MtChimney_Text_OhFineThen, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_EventScript_NotEnoughMoney::
	msgbox MtChimney_Text_YouveNotGotTheMoney, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MtChimney_Movement_ArchieApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

MtChimney_Movement_ArchieExitEast:
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_ArchieApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

MtChimney_Movement_ArchieExitNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused2:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused3:
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused4:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused5:
	delay_16
	delay_16
	delay_16
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused6:
	delay_16
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused7:
	delay_16
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	step_end

MtChimney_Movement_Unused8:
	delay_16
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

MtChimney_Movement_Unused9:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused10:
	walk_down
	step_end

MtChimney_Movement_Unused11:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused12:
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused13:
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	delay_16
	walk_down
	walk_down
	step_end

MtChimney_Movement_Unused14:
	lock_facing_direction
	walk_fast_left
	unlock_facing_direction
	face_right
	step_end

MtChimney_Movement_Unused15:
	walk_left
	walk_in_place_faster_right
	delay_16
	step_end

MtChimney_EventScript_BusyAquaGrunt1::
	msgbox MtChimney_Text_MagmaOutnumbersUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt2::
	msgbox MtChimney_Text_LessHabitatForWaterPokemon, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyAquaGrunt3::
	msgbox MtChimney_Text_MagmasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MT_CHIMNEY, MtChimney_Text_TabithaIntro, MtChimney_Text_TabithaDefeat
	msgbox MtChimney_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_2, MtChimney_Text_Grunt2Intro, MtChimney_Text_Grunt2Defeat
	msgbox MtChimney_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_BusyMagmaGrunt1::
	msgbox MtChimney_Text_TeamAquaAlwaysMessingWithPlans, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt2::
	msgbox MtChimney_Text_MeteoritesPackAmazingPower, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt3::
	msgbox MtChimney_Text_YouBetterNotMessWithUs, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt4::
	msgbox MtChimney_Text_AquasNameSimilar, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt5::
	msgbox MtChimney_Text_DouseThemInFire, MSGBOX_SIGN
	end

MtChimney_EventScript_BusyMagmaGrunt6::
	msgbox MtChimney_Text_KeepMakingMoreLand, MSGBOX_SIGN
	end

MtChimney_EventScript_MagmaPoochyena::
	msgbox MtChimney_Text_Bufoh, MSGBOX_SIGN
	end

MtChimney_EventScript_AquaPoochyena::
	msgbox MtChimney_Text_Bushaa, MSGBOX_SIGN
	end

MtChimney_EventScript_MeteoriteMachine::
	lockall
	goto_if_unset FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, MtChimney_EventScript_MachineOn
	goto_if_set FLAG_RECEIVED_METEORITE, MtChimney_EventScript_MachineOff
	msgbox MtChimney_Text_RemoveTheMeteorite, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MtChimney_EventScript_LeaveMeteoriteAlone
	msgbox MtChimney_Text_PlayerRemovedMeteorite, MSGBOX_DEFAULT
	giveitem ITEM_METEORITE
	setflag FLAG_RECEIVED_METEORITE
	releaseall
	end

MtChimney_EventScript_LeaveMeteoriteAlone::
	msgbox MtChimney_Text_PlayerLeftMeteorite, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOff::
	msgbox MtChimney_Text_MachineMakesNoResponse, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_MachineOn::
	msgbox MtChimney_Text_MetoriteFittedOnMachine, MSGBOX_DEFAULT
	releaseall
	end

MtChimney_EventScript_RouteSign::
	msgbox MtChimney_Text_RouteSign, MSGBOX_SIGN
	end

MtChimney_EventScript_Shelby::
	trainerbattle_single TRAINER_SHELBY_1, MtChimney_Text_ShelbyIntro, MtChimney_Text_ShelbyDefeat, MtChimney_EventScript_DefeatedShelby
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_RematchShelby
	msgbox MtChimney_Text_ShelbyPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_DefeatedShelby::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_ShelbyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SHELBY_1
	release
	end

MtChimney_EventScript_RematchShelby::
	trainerbattle_rematch TRAINER_SHELBY_1, MtChimney_Text_ShelbyRematchIntro, MtChimney_Text_ShelbyRematchDefeat
	msgbox MtChimney_Text_ShelbyPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Melissa::
	trainerbattle_single TRAINER_MELISSA, MtChimney_Text_MelissaIntro, MtChimney_Text_MelissaDefeat
	msgbox MtChimney_Text_MelissaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sheila::
	trainerbattle_single TRAINER_SHEILA, MtChimney_Text_SheilaIntro, MtChimney_Text_SheilaDefeat
	msgbox MtChimney_Text_SheilaPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Shirley::
	trainerbattle_single TRAINER_SHIRLEY, MtChimney_Text_ShirleyIntro, MtChimney_Text_ShirleyDefeat
	msgbox MtChimney_Text_ShirleyPostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MT_CHIMNEY_1, MtChimney_Text_Grunt1Intro, MtChimney_Text_Grunt1Defeat
	msgbox MtChimney_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MtChimney_EventScript_Sawyer::
	trainerbattle_single TRAINER_SAWYER_1, MtChimney_Text_SawyerIntro, MtChimney_Text_SawyerDefeat, MtChimney_EventScript_SawyerDefeated
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtChimney_EventScript_SawyerRematch
	msgbox MtChimney_Text_SawyerPostBattle, MSGBOX_DEFAULT
	release
	end

MtChimney_EventScript_SawyerDefeated::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtChimney_Text_SawyerRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_SAWYER_1
	release
	end

MtChimney_EventScript_SawyerRematch::
	trainerbattle_rematch TRAINER_SAWYER_1, MtChimney_Text_SawyerRematchIntro, MtChimney_Text_SawyerRematchDefeat
	msgbox MtChimney_Text_SawyerPostRematch, MSGBOX_AUTOCLOSE
	end

MtChimney_Text_MeteoriteWillActivateVolcano:
	.string "METEOR'un gücü…\pBu makine ile gücünü artırarak\nCHİMNEY DAĞI'nın volkanik aktivitesi anında\lyoğunlaşacak…\pEnerjisi kraterin derinliklerinde\nbüyüyecek ve… Fufufu…$"

MtChimney_Text_MaxieIntro:
	.string "Hm? Kimsin sen?\p… … … … … …\n… … … … … …\pARCHIE'nin AQUA TAKIMI'nın işlerine\nkarışan bir çocuktan yakındığını\lduymuştum.\pKastettiği sen olmalısın.\pHımph!\nDemek bize, yani MAGMA TAKIMI'na\lkarışmayı düşünüyorsun?\pİyi dinle. Uzun zaman önce canlılar\nyaşamak ve büyümek için toprağı\lkullanırlardı.\pİşte bu yüzden toprak çok önemlidir!\nHer şeyin beşiğidir!\pBu yüzden MAGMA TAKIMI, kendini kara\nkütlesinin genişlemesine adamıştır.\pİnsanlığın ve POKéMON'ların daha da\nilerlemesi için!\pVe bunun için, bu dağın içinde uyuyan\nşeyin gücüne ihtiyacımız var…\pBu kadarını öğrenmene gerek yoktu.\pAma, önemli değil! Büyük tasarımımıza\nburnunu sokmanın sonuçlarını sana\lgöstereceğim!$"

MtChimney_Text_MaxieDefeat:
	.string "Ne?!\pBen, MAXIE, hazırlıksız mı yakalandım?!$"

MtChimney_Text_MaxieYouHaventSeenLastOfMagma:
	.string "Yeterli.\nBu sefer geri çekileceğim.\pAma bunun MAGMA TAKIMI'nı son\ngörüşün olduğunu düşünme.\pFufufu…\pMETEOR olmadan bile, eğer o KÜRE'yi\nelde edersek… Fufufu…$"

MtChimney_Text_TabithaIntro:
	.string "Hehehe!\pDemek buraya kadar geldin!\pAma çok geç kaldın! METEOR\nŞELALESİ'ndeki METEOR'u çoktan\lpatrona teslim ettim!$"

MtChimney_Text_TabithaDefeat:
	.string "Hehehe…\pKaybetmiş olsam bile, eğer liderimiz o\nşeyi uyandırırsa…$"

MtChimney_Text_TabithaPostBattle:
	.string "Patron acele et!\nOna meteorun enerjisini ver!\pHehehe…$"

MtChimney_Text_Grunt2Intro:
	.string "Biz MAGMA TAKIMI olarak herkesin\niyiliği için çok çalışıyoruz.\pO şeyin gücü daha fazla toprak\nyaratırsa, yaşanacak daha fazla yer\lolur.\pHerkes mutlu olurdu!$"

MtChimney_Text_Grunt2Defeat:
	.string "Ha?\nNe demek kaybettim?$"

MtChimney_Text_Grunt2PostBattle:
	.string "Patronumuz Bu herkesi mutlu edecek\ndiyor.\pAma neden herkes yolumuza çıkıp\nduruyor?$"

MtChimney_Text_Grunt1Intro:
	.string "Eğer daha fazla kara olsaydı, kendime\nait büyük bir ev alabilirdim!\pOnu sertleşmiş lavların üzerine inşa\nedeceğim!$"

MtChimney_Text_Grunt1Defeat:
	.string "Hayalim büyük bir ev…$"

MtChimney_Text_Grunt1PostBattle:
	.string "Senin gibi bir çocuk, dalgaların\narasında sıçramalı!$"

MtChimney_Text_TeamAquaAlwaysMessingWithPlans:
	.string "Şu sinir bozucu AQUA TAKIMI…\nHep planlarımızı bozuyorlar!$"

MtChimney_Text_MeteoritesPackAmazingPower:
	.string "METEORLAR inanılmaz bir güce sahiptir!$"

MtChimney_Text_YouBetterNotMessWithUs:
	.string "Bize bulaşmasan iyi edersin!\pHerkesin iyiliği için o şeyi uyandırmaya\nçalışıyoruz!$"

MtChimney_Text_AquasNameSimilar:
	.string "Biz MAGMA TAKIMIYIZ!\pOnlar AQUA TAKIMI!\pBizimki gibi bir isim kullanmaları beni\nçok sinirlendiriyor!$"

MtChimney_Text_DouseThemInFire:
	.string "Evet!\nOnları ateşte boğ!$"

MtChimney_Text_KeepMakingMoreLand:
	.string "Daha fazla kara oluşturmaya devam\nedeceğiz!$"

MtChimney_Text_Bufoh:
	.string "Bufoh!$"

MtChimney_Text_ArchieGoStopTeamMagma:
	.string "ARCHİE: Grr, {PLAYER}! Ortaya çıkacağını\ntahmin etmeliydim!\pMAGMA TAKIMI haydutlarının neyin\npeşinde olduğunu kendin gör!\pÇalınan METEORİT'in gücünü volkana\nenjekte etmeye çalışıyorlar!\pBöyle bir şey yapmak volkanın\npatlamasına neden olur!$"

MtChimney_Text_ArchieIHaveMyHandsFull:
	.string "ARCHİE: Grrr…\pO MAXIE'yi durdurmak istiyorum, ama\nyapamıyorum!\pEllerim aynı anda üç rakiple savaşmakla\ndoluyken olmaz!$"

MtChimney_Text_ArchieThankYou:
	.string "ARCHiE: {PLAYER}! Teşekkürler!\pYardımınla MAGMA TAKIMI'nın yıkıcı\nplanını bozduk!\pAma… Sen… Kimin tarafındasın?\pAh, önemli değil.\pUyanık kalacağız ve MAGMA TAKIMI'nı\ntakip etmeye devam edeceğiz.\pGörüşmek üzere, {PLAYER}!$"

MtChimney_Text_MagmaOutnumbersUs:
	.string "Lanet olsun… MAGMA TAKIMI sayıca\nbizden üstün! Onlara yetişemiyoruz!$"

MtChimney_Text_LessHabitatForWaterPokemon:
	.string "Eğer karaları genişletirlerse,\nSU POKéMON'ları için daha az yaşam\lalanı olacak!$"

MtChimney_Text_MagmasNameSimilar:
	.string "Biz AQUA TAKIMI'yız!\pOnlar MAGMA TAKIMI!\pBöyle kafa karıştırıcı bir isim\nkullanmaları beni yakıyor!$"

MtChimney_Text_Bushaa:
	.string "Bushaa!$"

MtChimney_Text_LavaCookiesJust200:
	.string "LAV KURABİYELERİ, CHİMNEY DAĞI'nın\nmeşhur lezzetidir.\pBir tane deneyin.\nSadece 200 yen.$"

MtChimney_Text_ThankYouDear:
	.string "Teşekkür ederim, canım!$"

MtChimney_Text_YouveNotGotTheMoney:
	.string "Ah, canım.\nParan yoksa hiçbir şey alamazsın.$"

MtChimney_Text_OhFineThen:
	.string "Oh, iyi o zaman.$"

MtChimney_Text_MetoriteFittedOnMachine:
	.string "Gizemli makineye bir METEOR\ntakılı…\pMakine enerjiyi METEOR'da depoluyor\ngibi görünüyor.$"

MtChimney_Text_RemoveTheMeteorite:
	.string "Gizemli makineye bir METEOR\ntakılı…\pMETEOR'u çıkarmak istiyor musun?$"

MtChimney_Text_PlayerRemovedMeteorite:
	.string "{PLAYER}, gizemli makineden METEOR'u\nçıkardı.$"

MtChimney_Text_PlayerLeftMeteorite:
	.string "{PLAYER}, METEOR'u olduğu yerde\nbıraktı.$"

MtChimney_Text_MachineMakesNoResponse:
	.string "Bu gizemli makine…\nHiçbir tepki vermiyor.$"

MtChimney_Text_RouteSign:
	.string "{DOWN_ARROW} ENGEBELİ YOL\nLAVARİDGE KÖYÜ İLERİDE$"

MtChimney_Text_ShelbyIntro:
	.string "Kaplıcalara gittim ve yorgun\nkemiklerimi tazeledim. Şu anda kendimi\lgüçlü hissediyorum!$"

MtChimney_Text_ShelbyDefeat:
	.string "Aman Tanrım.\nSen gayet iyisin!$"

MtChimney_Text_ShelbyPostBattle:
	.string "Vay, vay. Kaybettim.\nArtık kendime usta diyemeceğim.$"

MtChimney_Text_ShelbyRegister:
	.string "Teşekkürler evlat.\nEğlenceliydi, sanki kendi torunumla\ldövüşüyormuşum gibi oldu.\pLütfen, rövanş için beni tekrar\ngörmeye gel.$"

MtChimney_Text_ShelbyRematchIntro:
	.string "Kalbini POKéMON'ununkiyle\nbirleştirebilirsen, neden olmasın,\lharika şeyler başarabilirsin.$"

MtChimney_Text_ShelbyRematchDefeat:
	.string "Aman Tanrım.\nSen gayet iyisin!$"

MtChimney_Text_ShelbyPostRematch:
	.string "Belki de kalbin, POKéMON'unun\nkalbiyle bir olmuştur.$"

MtChimney_Text_MelissaIntro:
	.string "İçimde bir ateş yanıyor, bebeğim.\nDuramıyorum! Savaşmalıyım!$"

MtChimney_Text_MelissaDefeat:
	.string "Çok ateşli bir maçtı!$"

MtChimney_Text_MelissaPostBattle:
	.string "CHİMNEY DAĞI'nın sıcağı beni yakıyor\nbebeğim!$"

MtChimney_Text_SheilaIntro:
	.string "Sonunda CHİMNEY DAĞI'na ulaştım.\nPOKéMON savaşı yapmak istiyorum!$"

MtChimney_Text_SheilaDefeat:
	.string "Savaşma şeklin…\nCHİMNEY DAĞI'nın patlaması gibi!$"

MtChimney_Text_SheilaPostBattle:
	.string "Dediğim gibi, sonunda CHİMNEY DAĞI'na\nulaştım. Sadece biraz gezersem\lyazık olur…\pSavaşlara girmek ve hatıra olarak\nKURABİYE almak istiyorum.$"

MtChimney_Text_ShirleyIntro:
	.string "Kaplıcada yıkandığımdan beri kendimi\nharika hissediyorum! Kazanacağıma\leminim!$"

MtChimney_Text_ShirleyDefeat:
	.string "Pff!\nSudan ürperiyorum.$"

MtChimney_Text_ShirleyPostBattle:
	.string "Kaplıcalara bir kez daha girmem\ngerekecek. Bana katılmak ister misin?\pŞaka yapıyorum!$"

MtChimney_Text_SawyerIntro:
	.string "Güzel bir dağmış burası!\nEşlik edilecek çok insan var!$"

MtChimney_Text_SawyerDefeat:
	.string "Sen de ateşlisin!$"

MtChimney_Text_SawyerPostBattle:
	.string "Sanırım yerel halkla birlikte\nLAVARİDGE KAPLICASI'na gitmem\lgerekiyor!$"

MtChimney_Text_SawyerRegister:
	.string "Senin gibi küçük afacanları\nseverim. Seni POKéNAV'ıma kaydedeyim.$"

MtChimney_Text_SawyerRematchIntro:
	.string "Etrafım ateşli insanlarla çevrili.\nKaybetmeyeceğim!$"

MtChimney_Text_SawyerRematchDefeat:
	.string "Hâlâ eskisi gibi ateş saçıyorsun!$"

MtChimney_Text_SawyerPostRematch:
	.string "Aslında burası oldukça sıcakmış.\nBiraz kalın giyinmişim.$"


