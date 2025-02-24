MauvilleCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MauvilleCity_Gym_OnLoad
	.byte 0

MauvilleCity_Gym_OnLoad:
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_DeactivatePuzzle
	switch VAR_MAUVILLE_GYM_STATE
	case 0, MauvilleCity_Gym_EventScript_UpdateBarriers
	case 1, MauvilleCity_Gym_EventScript_Switch1Pressed
	case 2, MauvilleCity_Gym_EventScript_Switch2Pressed
	case 3, MauvilleCity_Gym_EventScript_Switch3Pressed
	case 4, MauvilleCity_Gym_EventScript_Switch4Pressed
	end

MauvilleCity_Gym_EventScript_UpdateBarriers::
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetAltBarriers
	end

MauvilleCity_Gym_EventScript_SetAltBarriers::
	setmetatile 3, 11, METATILE_MauvilleGym_RedBeamV1_On, TRUE
	setmetatile 3, 12, METATILE_MauvilleGym_RedBeamV2_On, TRUE
	setmetatile 3, 13, METATILE_MauvilleGym_PoleTop_On, TRUE
	setmetatile 4, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 5, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 4, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 5, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 7, 10, METATILE_MauvilleGym_RedBeamH1_On, FALSE
	setmetatile 8, 10, METATILE_MauvilleGym_RedBeamH2_On, FALSE
	setmetatile 7, 11, METATILE_MauvilleGym_RedBeamH3_On, TRUE
	setmetatile 8, 11, METATILE_MauvilleGym_RedBeamH4_On, TRUE
	setmetatile 4, 13, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 13, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 14, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 14, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 1, 10, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 2, 10, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 1, 11, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 2, 11, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	setmetatile 6, 8, METATILE_MauvilleGym_PoleBottom_On, TRUE
	setmetatile 6, 9, METATILE_MauvilleGym_FloorTile, FALSE
	setmetatile 6, 10, METATILE_MauvilleGym_PoleTop_Off, FALSE
	setmetatile 4, 6, METATILE_MauvilleGym_GreenBeamH1_Off, FALSE
	setmetatile 5, 6, METATILE_MauvilleGym_GreenBeamH2_Off, FALSE
	setmetatile 4, 7, METATILE_MauvilleGym_GreenBeamH3_Off, FALSE
	setmetatile 5, 7, METATILE_MauvilleGym_GreenBeamH4_Off, FALSE
	end

MauvilleCity_Gym_EventScript_Switch1Pressed::
	setvar VAR_0x8004, 0
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch2Pressed::
	setvar VAR_0x8004, 1
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch3Pressed::
	setvar VAR_0x8004, 2
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_Switch4Pressed::
	setvar VAR_0x8004, 3
	special MauvilleGymPressSwitch
	goto MauvilleCity_Gym_EventScript_UpdateBarriers
	end

MauvilleCity_Gym_EventScript_DeactivatePuzzle::
	special MauvilleGymDeactivatePuzzle
	end

MauvilleCity_Gym_EventScript_Wattson::
	trainerbattle_single TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonIntro, MauvilleCity_Gym_Text_WattsonDefeat, MauvilleCity_Gym_EventScript_WattsonDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_Gym_EventScript_WattsonRematch
	goto_if_unset FLAG_RECEIVED_TM34, MauvilleCity_Gym_EventScript_GiveShockWave2
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_Gym_EventScript_CompletedNewMauville
	msgbox MauvilleCity_Gym_Text_WattsonPostBattle, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonDefeated::
	message MauvilleCity_Gym_Text_ReceivedDynamoBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 3
	clearflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	setflag FLAG_DEFEATED_MAUVILLE_GYM
	setflag FLAG_BADGE03_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers
	special MauvilleGymDeactivatePuzzle
	special DrawWholeMapView
	playse SE_UNLOCK
	call MauvilleCity_Gym_EventScript_GiveShockWave
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Gym_Text_RegisteredWattson, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WATTSON_MATCH_CALL
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave2::
	giveitem ITEM_TM34
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM34
	release
	end

MauvilleCity_Gym_EventScript_GiveShockWave::
	giveitem ITEM_TM34
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MauvilleCity_Gym_Text_ExplainShockWave, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM34
	return

MauvilleCity_Gym_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_WattsonRematch::
	trainerbattle_rematch_double TRAINER_WATTSON_1, MauvilleCity_Gym_Text_WattsonPreRematch, MauvilleCity_Gym_Text_WattsonRematchDefeat, MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons
	msgbox MauvilleCity_Gym_Text_WattsonPostRematch, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 1, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 1
	setvar VAR_0x8004, 0
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 2, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 2
	setvar VAR_0x8004, 1
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 3, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 3
	setvar VAR_0x8004, 2
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_SwitchDoNothing
	goto_if_eq VAR_MAUVILLE_GYM_STATE, 4, MauvilleCity_Gym_EventScript_SwitchDoNothing
	setvar VAR_MAUVILLE_GYM_STATE, 4
	setvar VAR_0x8004, 3
	goto MauvilleCity_Gym_EventScript_PressFloorSwitch
	end

MauvilleCity_Gym_EventScript_PressFloorSwitch::
	special MauvilleGymSetDefaultBarriers
	special MauvilleGymPressSwitch
	special DrawWholeMapView
	playse SE_UNLOCK
	goto_if_set FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_ClearBarriersAltState
	goto_if_unset FLAG_MAUVILLE_GYM_BARRIERS_STATE, MauvilleCity_Gym_EventScript_SetBarriersAltState
	releaseall
	end

MauvilleCity_Gym_EventScript_SwitchDoNothing::
	releaseall
	end

MauvilleCity_Gym_EventScript_SetBarriersAltState::
	setflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_ClearBarriersAltState::
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	releaseall
	end

MauvilleCity_Gym_EventScript_Kirk::
	trainerbattle_single TRAINER_KIRK, MauvilleCity_Gym_Text_KirkIntro, MauvilleCity_Gym_Text_KirkDefeat
	msgbox MauvilleCity_Gym_Text_KirkPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Shawn::
	trainerbattle_single TRAINER_SHAWN, MauvilleCity_Gym_Text_ShawnIntro, MauvilleCity_Gym_Text_ShawnDefeat
	msgbox MauvilleCity_Gym_Text_ShawnPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Ben::
	trainerbattle_single TRAINER_BEN, MauvilleCity_Gym_Text_BenIntro, MauvilleCity_Gym_Text_BenDefeat
	msgbox MauvilleCity_Gym_Text_BenPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Vivian::
	trainerbattle_single TRAINER_VIVIAN, MauvilleCity_Gym_Text_VivianIntro, MauvilleCity_Gym_Text_VivianDefeat
	msgbox MauvilleCity_Gym_Text_VivianPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_Angelo::
	trainerbattle_single TRAINER_ANGELO, MauvilleCity_Gym_Text_AngeloIntro, MauvilleCity_Gym_Text_AngeloDefeat
	msgbox MauvilleCity_Gym_Text_AngeloPostBattle, MSGBOX_AUTOCLOSE
	end

MauvilleCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MAUVILLE_GYM, MauvilleCity_Gym_EventScript_GymGuidePostVictory
	msgbox MauvilleCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MauvilleCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

MauvilleCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE03_GET, MauvilleCity_Gym_EventScript_GymStatueCertified
	goto MauvilleCity_Gym_EventScript_GymStatue
	end

MauvilleCity_Gym_EventScript_GymStatueCertified::
	msgbox MauvilleCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_EventScript_GymStatue::
	msgbox MauvilleCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MauvilleCity_Gym_Text_GymGuideAdvice:
	.string "Hey, nasıl gidiyor, ŞAMPİYON\nadayı {PLAYER}?\pMAUVILLE SALONU LİDERİ WATTSON,\nELEKTRİK tipi POKéMON kullanıyor.\pEğer ona SU tipi POKéMON ile meydan\nokursan, onları çarpar! Bzzt!\pVe salonun her yerine anahtar\nkontrollü kapılar koymuş! Eksantrik!\pHey, devam et ve kendin gör!$"

MauvilleCity_Gym_Text_GymGuidePostVictory:
	.string "Vay canına, elektrik saçıyorsun!\nKapıyı açmak için güç verdin!$"

MauvilleCity_Gym_Text_KirkIntro:
	.string "Benim elektrikli ruhum, hayallerini\nparamparça edecek, vuu-huu!$"

MauvilleCity_Gym_Text_KirkDefeat:
	.string "Gerilim tavan!$"

MauvilleCity_Gym_Text_KirkPostBattle:
	.string "POKéMON ve rock, ikisine de bayılırım,\nvuu-huu!$"

MauvilleCity_Gym_Text_ShawnIntro:
	.string "WATTSON'ın emrinde çalıştım!\nKolay kolay kaybetmem!$"

MauvilleCity_Gym_Text_ShawnDefeat:
	.string "Fişim çekildi…$"

MauvilleCity_Gym_Text_ShawnPostBattle:
	.string "SALON LİDERİMİZ WATTSON çok uzun\nzamandır buralarda.\pBaban doğmadan önce bile mücadele\nediyordu o sert adam.$"

MauvilleCity_Gym_Text_BenIntro:
	.string "Bu spor salonunda bulmacalar var!\nEğlenceli değil mi?$"

MauvilleCity_Gym_Text_BenDefeat:
	.string "Kaybetmek hiç eğlenceli değil.$"

MauvilleCity_Gym_Text_BenPostBattle:
	.string "WATTSON, anahtarlarla küçük tuzaklar\nkurmayı sevdiğini söylüyor.$"

MauvilleCity_Gym_Text_VivianIntro:
	.string "Cazibeme ve POKéMON saldırılarıma\nşok olacaksın!$"

MauvilleCity_Gym_Text_VivianDefeat:
	.string "Gücün karşısında şok oldum!$"

MauvilleCity_Gym_Text_VivianPostBattle:
	.string "MAUVILLE'in WATTSON tarafından\nkurulduğunu duymuştum.\pBiz eğitmen olmadan çok önce o çoktan\nbir eğitmendi.\lHer türlü şeyi biliyor olmalı!$"

MauvilleCity_Gym_Text_AngeloIntro:
	.string "Parlak şeylere bayılırım!$"

MauvilleCity_Gym_Text_AngeloDefeat:
	.string "Ah…\nGözlerim kamaştı…$"

MauvilleCity_Gym_Text_AngeloPostBattle:
	.string "WATTSON'ın alnı parlıyor.\nBu beni mutlu ediyor!$"

MauvilleCity_Gym_Text_WattsonIntro:
	.string "WATTSON: Şehri dönüştürme planımdan\nvazgeçtim, bitti gitti.\pBu yüzden zamanımı spor salonumda kapı\ntuzakları yapmaya harcıyorum.\pHa? Sen burada ne yapıyorsun peki?\nTüm hileli kapılarımı geçtin mi?\pHahahahah!\nİşte bu çok eğlenceli!\pDevrelerinin yanmasına hazır ol!$"

MauvilleCity_Gym_Text_WattsonDefeat:
	.string "Hahahahah!\nİyi, kaybettim!\pSonunda beni heyecanlandıran biri!\nAl şu rozeti!$"

MauvilleCity_Gym_Text_ReceivedDynamoBadge:
	.string "{PLAYER}, WATTSON'dan DİNAMO ROZETİ\naldı.$"

MauvilleCity_Gym_Text_ExplainDynamoBadgeTakeThis:
	.string "DİNAMO ROZETİ, POKéMON'larının\nsavaş dışında KAYA DARBESİ\lkullanabilmesini sağlar.\pAyrıca POKéMON'unu da biraz daha\nhızlı hale getirir.\pHmm… Bunu da almalısın!$"

MauvilleCity_Gym_Text_ExplainShockWave:
	.string "Bu TM34, ŞOK DALGASI içerir.\pAsla ıskalamayan güvenilir bir\nsaldırıdır! Ona güvenebilirsin!\p… … … … … …$"

MauvilleCity_Gym_Text_RegisteredWattson:
	.string "SALON LİDERİ WATTSON, POKéNAV'a\nkaydedildi.$"

MauvilleCity_Gym_Text_WattsonPostBattle:
	.string "Senin gibi gelecek vaat eden genç\nbir EĞİTMEN gördüğümde mutlulukla\ldoluyorum!$"

MauvilleCity_Gym_Text_WattsonGoForthAndEndeavor:
	.string "Hahahahah!\nHadi çabalamaya devam et, genç!$"

MauvilleCity_Gym_Text_GymStatue:
	.string "MAUVİLLE ŞEHRİ POKéMON SALONU$"

MauvilleCity_Gym_Text_GymStatueCertified:
	.string "MAUVİLLE ŞEHRİ POKéMON SALONU\pWATTSON'IN ONAYLI EĞİTMENLERİ:\n{PLAYER}$"

MauvilleCity_Gym_Text_WattsonPreRematch:
	.string "Ah-ha! Sonunda geldin!\nNe istediğini biliyorum.\lPOKéMON'umla savaşmak istiyorsun!\pHahahahaha!\pSenden kıvılcımlar çıkaracağım!\nUyarmadı deme sakın!$"

MauvilleCity_Gym_Text_WattsonRematchDefeat:
	.string "Oof…\nPilimiz bitti…$"

MauvilleCity_Gym_Text_WattsonPostRematch:
	.string "Pilimizi tekrar şarj etmemiz\ngerekecek.\pTamamen şarj olduğumuzda, meydan\nokumanı memnuniyetle kabul edeceğiz.\pBir ara tekrar gel, olur mu?$"

MauvilleCity_Gym_Text_WattsonRematchNeedTwoMons:
	.string "Ah-ha! Sonunda geldin!\nNe istediğini biliyorum.\lPOKéMON'umla savaşmak istiyorsun!\pHahahahaha!\pAman! Bekle!\nYanında sadece bir POKéMON var!\pBeni iki ya da daha fazla POKéMON'la\ngörmeye gel, tamam mı?$"


