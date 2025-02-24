SootopolisCity_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_Gym_1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Gym_1F_OnTransition
	.byte 0

SootopolisCity_Gym_1F_OnTransition:
	setvar VAR_ICE_STEP_COUNT, 1
	end

SootopolisCity_Gym_1F_OnResume:
	setstepcallback STEP_CB_SOOTOPOLIS_ICE
	end

SootopolisCity_Gym_1F_OnLoad:
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special SetSootopolisGymCrackedIceMetatiles
	end

SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles::
	goto_if_lt VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_StopCheckingStairs  @ All stairs ice
	goto_if_lt VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_OpenFirstStairs
	goto_if_lt VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs
	setmetatile 8, 4, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 5, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs::
	setmetatile 8, 10, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 11, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstStairs::
	setmetatile 8, 15, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 16, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_StopCheckingStairs::
	return

SootopolisCity_Gym_1F_OnFrame:
	map_script_2 VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs
	map_script_2 VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs
	map_script_2 VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs
	map_script_2 VAR_ICE_STEP_COUNT, 0, SootopolisCity_Gym_1F_EventScript_FallThroughIce
	.2byte 0

SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_FallThroughIce::
	lockall
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Gym_1F_Movement_FallThroughIce
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_SOOTOPOLIS_CITY_GYM_B1F
	waitstate
	end

SootopolisCity_Gym_1F_Movement_FallThroughIce:
	set_invisible
	step_end

SootopolisCity_Gym_1F_EventScript_Juan::
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanIntro, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_JuanDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto_if_unset FLAG_RECEIVED_TM03, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanDefeated::
	message SootopolisCity_Gym_1F_Text_ReceivedRainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_BADGE08_GET
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	setvar VAR_SOOTOPOLIS_CITY_STATE, 6
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	call SootopolisCity_Gym_1F_EventScript_GiveWaterPulse
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_Gym_1F_Text_RegisteredJuan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_JUAN_MATCH_CALL
	release
	end

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse::
	giveitem ITEM_TM03
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM03
	return

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2::
	giveitem ITEM_TM03
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM03
	release
	end

SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge::
	msgbox SootopolisCity_Gym_1F_Text_GoGetFortreeBadge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanRematch::
	trainerbattle_rematch_double TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanPreRematch, SootopolisCity_Gym_1F_Text_JuanRematchDefeat, SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons
	msgbox SootopolisCity_Gym_1F_Text_JuanPostRematch, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory
	msgbox SootopolisCity_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_GymStatueCertified::
	msgbox SootopolisCity_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_GymStatue::
	msgbox SootopolisCity_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_Text_GymGuideAdvice:
	.string "Hey! Nasıl gidiyor, ŞAMPİYON\nadayı {PLAYER}?\pSOOTOPOLİS'in SALON LİDERİ JUAN, SU\ntipi POKéMON'ların ustasıdır.\pVe JUAN'a giden yolda buzlu zemin\nilerlemeni engelleyecek…\pDinle, üzgünüm ama sana verebileceğim\ntüm tavsiye bu.\pYolun geri kalanını kendin gitmelisin!$"

SootopolisCity_Gym_1F_Text_GymGuidePostVictory:
	.string "Yo! Sözde tüm HOENN'in en iyisi olan\nJUAN'ı bile yenmişsin!\pTamam!\nEĞİTMEN KARTINI kontrol et.\pEğer tüm rozetleri aldıysan, POKéMON\nLİGİ mücadelesi için hazırsın\ldemektir!$"

SootopolisCity_Gym_1F_Text_JuanIntro:
	.string "Bu kadar çekingen olmamalıyım.\pWALLACE'a POKEMON hakkında bilinmesi\ngereken her şeyi öğreten bendim.\pBir keresinde, SALON LİDERİ olarak\ngörevimi bırakmıştım.\pBenim yerime WALLACE'a salonu\nemanet etmiştim.\pAncak geri dönmem için zorlayıcı bir\nneden ortaya çıktı.\pBu kadar gevezelik yeter.\nMaçımıza başlayalım, olur mu?\pLütfen sanatıma tanıklık et.\nPOKéMON'larımın illüzyonlarını seyret!$"

SootopolisCity_Gym_1F_Text_JuanDefeat:
	.string "Ahahaha, mükemmel!\nÇok iyi, kazanan sensin.\pSende her şeyin üstesinden\ngelebilecek parlak bir yetenek\lseziyorum.\pAncak, benimle ve hatta WALLACE ile\nkıyaslandığında, zarafetten\lyoksunsun.\pBelki de sana kıyafetlerimi ödünç\nvermeliyimdir?\p… … … … … …\n… … … … … …\pHahaha, sadece şaka yapıyorum!\pKıyafetlerim yerine seni bununla\nödüllendireceğim, YAĞMUR ROZETİ!$"

SootopolisCity_Gym_1F_Text_ReceivedRainBadge:
	.string "{PLAYER}, JUAN'dan YAĞMUR ROZETİ\naldı.$"

SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis:
	.string "YAĞMUR ROZETİNE sahip olmak, tüm\nPOKéMON'larının her emrine tam\lolarak itaat etmesini sağlayacaktır.\pYAĞMUR ROZETİ aynı zamanda HM\nsaldırısı ŞELALE'yi kullanarak\lşelalere tırmanmanı sağlar.\pVe yaptığımız savaşı asla unutmaman\niçin bunu al…$"

SootopolisCity_Gym_1F_Text_ExplainWaterPulse:
	.string "Sana verdiğim TEKNİK MAKİNE,\nSU VURUŞU içeriyor.\pSaldırı, ultrasonik dalgalarla\ndüşmanı şaşırtır.\p… … … … … …$"

SootopolisCity_Gym_1F_Text_RegisteredJuan:
	.string "JUAN, POKéNAV'a kaydedildi.$"

SootopolisCity_Gym_1F_Text_JuanPostBattle:
	.string "HOENN'in tüm rozetlerini\ntoplayan eğitmenler nihai hedefe\ldoğru yol almalıdır.\pPOKéMON LİGİ.\pHOENN'in en doğusuna, EVER GRANDE\nadasına seyahat et.\pOrada POKéMON LİGİ'ni bulacaksın.$"

SootopolisCity_Gym_1F_Text_GoGetFortreeBadge:
	.string "HOENN'de elde etmeniz gereken sadece\nbir RÜTBE kaldı.\pPOKéMON LİGİ'ne meydan okumak\nistiyorsan, FORTREE'deki GYM'den son\lRÜTBEYİ almalısın.$"

SootopolisCity_Gym_1F_Text_GymStatue:
	.string "SOOTOPOLİS ŞEHRİ POKéMON SALONU$"

SootopolisCity_Gym_1F_Text_GymStatueCertified:
	.string "SOOTOPOLİS ŞEHRİ POKéMON SALONU\pJUAN'IN ONAYLI EĞİTMENLERİ:\n{PLAYER}$"

SootopolisCity_Gym_1F_Text_JuanPreRematch:
	.string "JUAN: Ah, bu salon her zamanki\ndinginlik haline geri dönmüştü…\pAma genç tayfunumuz bizi tekrar\nsınamak için geri döndü!\pEvet, dostum, kesinlikle!\pSeninle istediğin tempoda dans\netmekten mutluluk duyarım!$"

SootopolisCity_Gym_1F_Text_JuanRematchDefeat:
	.string "Ahahaha, kazanan sensin!\nBeni yine yendin!$"

SootopolisCity_Gym_1F_Text_JuanPostRematch:
	.string "JUAN: Sana benim çırağım olmanı\nsöylesem, eminim reddedersin.\pPaltomu sana hediye etmek isterdim.\pAma yine reddedeceksin.\nÖyle tahmin ediyorum.\pVe bu, dostum, asaletin kesin bir\nişaretidir!$"

SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons:
	.string "JUAN: Ah, bu salon her zamanki\ndinginlik haline geri dönmüştü…\pAma genç tayfunumuz bizi tekrar\nsınamak için geri döndü!\pEvet, dostum, kesinlikle! Seninle dans\netmekten mutluluk duyacağım…\pAh, hayır, hayır, hayır.\nYanında sadece bir POKéMON var.\pİki, belki daha fazla POKéMON'la\ndönmeni dilerim, lütfen.$"


