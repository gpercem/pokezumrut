.set LOCALID_WALLY, 6
.set LOCALID_WALLYS_UNCLE, 7
.set LOCALID_SCOTT, 11

MauvilleCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_OnTransition
	.byte 0

MauvilleCity_OnTransition:
	setflag FLAG_VISITED_MAUVILLE_CITY
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	clearflag FLAG_HIDE_SLATEPORT_MUSEUM_POPULATION
	setflag FLAG_SYS_TV_START
	clearflag FLAG_MAUVILLE_GYM_BARRIERS_STATE
	setvar VAR_MAUVILLE_GYM_STATE, 0
	call_if_set FLAG_GOT_TM24_FROM_WATTSON, MauvilleCity_EventScript_MoveWattsonBackToGym
	end

MauvilleCity_EventScript_MoveWattsonBackToGym::
	clearflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	setflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setflag FLAG_WATTSON_REMATCH_AVAILABLE
	return

MauvilleCity_EventScript_Boy::
	msgbox MauvilleCity_Text_NurseHurtMonBackToHealth, MSGBOX_NPC
	end

MauvilleCity_EventScript_Maniac::
	msgbox MauvilleCity_Text_AllSortsOfPeopleComeThrough, MSGBOX_NPC
	end

MauvilleCity_EventScript_Woman::
	msgbox MauvilleCity_Text_RydelVeryGenerous, MSGBOX_NPC
	end

MauvilleCity_EventScript_RichBoy::
	msgbox MauvilleCity_Text_PokemonCanJumpYouOnBike, MSGBOX_NPC
	end

MauvilleCity_EventScript_CitySign::
	msgbox MauvilleCity_Text_CitySign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GymSign::
	msgbox MauvilleCity_Text_GymSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_BikeShopSign::
	msgbox MauvilleCity_Text_BikeShopSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_GameCornerSign::
	msgbox MauvilleCity_Text_GameCornerSign, MSGBOX_SIGN
	end

MauvilleCity_EventScript_SchoolKidM::
	lock
	faceplayer
	goto_if_set FLAG_TV_EXPLAINED, MauvilleCity_EventScript_TVExplained
	msgbox MauvilleCity_Text_ExplainTV, MSGBOX_DEFAULT
	setflag FLAG_TV_EXPLAINED
	release
	end

MauvilleCity_EventScript_TVExplained::
	msgbox MauvilleCity_Text_BeenCheckingOutTV, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_UncleAskPlayerToBattleWally
	msgbox MauvilleCity_Text_UncleHesTooPeppy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_UncleAskPlayerToBattleWally::
	msgbox MauvilleCity_Text_UncleCanYouBattleWally, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_WALLYS_UNCLE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MauvilleCity_EventScript_Wally::
	lockall
	goto_if_set FLAG_DECLINED_WALLY_BATTLE_MAUVILLE, MauvilleCity_EventScript_WallyRequestBattleAgain
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWantToChallengeGym, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_UncleYourePushingIt, MSGBOX_DEFAULT
	msgbox MauvilleCity_Text_WallyWeCanBeatAnyone, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_WALLY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_Text_WallyWillYouBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_EventScript_BattleWallyPrompt::
	call_if_eq VAR_RESULT, YES, MauvilleCity_EventScript_BattleWally
	goto_if_eq VAR_RESULT, NO, MauvilleCity_EventScript_DeclineWallyBattle
	closemessage
	switch VAR_FACING
	case DIR_NORTH, MauvilleCity_EventScript_WallyAndUncleExitNorth
	case DIR_EAST, MauvilleCity_EventScript_WallyAndUncleExitEast
	end

MauvilleCity_EventScript_WallyAndUncleExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerFaceUncleNorth
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerNorth
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitNorth2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitNorth2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitNorth2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_WallyAndUncleExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast1
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast1
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast1
	waitmovement 0
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleApproachPlayerEast
	waitmovement 0
	msgbox MauvilleCity_Text_UncleVisitUsSometime, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchWallyExitEast2
	applymovement LOCALID_WALLYS_UNCLE, MauvilleCity_Movement_WallysUncleExitEast2
	applymovement LOCALID_WALLY, MauvilleCity_Movement_WallyExitEast2
	waitmovement 0
	goto MauvilleCity_EventScript_DefeatedWally
	end

MauvilleCity_EventScript_DefeatedWally::
	removeobject LOCALID_WALLY
	removeobject LOCALID_WALLYS_UNCLE
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	clearflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLYS_UNCLE
	setflag FLAG_DEFEATED_WALLY_MAUVILLE
	setvar VAR_WALLY_CALL_STEP_COUNTER, 0
	setflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottApproachPlayerNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottApproachPlayerEast
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox MauvilleCity_Text_ScottYouDidntHoldBack, MSGBOX_DEFAULT
	closemessage
	addvar VAR_SCOTT_STATE, 1
	call_if_eq VAR_FACING, DIR_NORTH, MauvilleCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MauvilleCity_EventScript_ScottExitEast
	removeobject LOCALID_SCOTT
	releaseall
	end

MauvilleCity_EventScript_ScottApproachPlayerNorth::
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottApproachPlayerEast::
	setobjectxyperm LOCALID_SCOTT, 12, 13
	addobject LOCALID_SCOTT
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottApproachPlayerEast
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitNorth
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitNorth
	waitmovement 0
	return

MauvilleCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MauvilleCity_Movement_PlayerWatchScottExitEast
	applymovement LOCALID_SCOTT, MauvilleCity_Movement_ScottExitEast
	waitmovement 0
	return

MauvilleCity_EventScript_BattleWally::
	msgbox MauvilleCity_Text_WallyHereICome, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_MAUVILLE, MauvilleCity_Text_WallyDefeat
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_WallyIllGoBackToVerdanturf, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_ThankYouNotEnoughToBattle, MSGBOX_DEFAULT
	applymovement LOCALID_WALLY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox MauvilleCity_Text_UncleNoNeedToBeDown, MSGBOX_DEFAULT
	return

MauvilleCity_EventScript_DeclineWallyBattle::
	setflag FLAG_DECLINED_WALLY_BATTLE_MAUVILLE
	msgbox MauvilleCity_Text_WallyMyUncleWontKnowImStrong, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_WallyRequestBattleAgain::
	applymovement LOCALID_WALLY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MauvilleCity_Text_WallyPleaseBattleMe, MSGBOX_YESNO
	goto MauvilleCity_EventScript_BattleWallyPrompt
	end

MauvilleCity_Movement_WallyExitNorth1:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

MauvilleCity_Movement_WallyExitEast1:
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallyExitNorth2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_WallyExitEast2:
	delay_16
	delay_16
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	delay_8
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast2:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitNorth:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchScottExitEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitEast1:
	delay_16
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_PlayerWatchWallyExitNorth1:
	delay_16
	walk_in_place_faster_left
	step_end

MauvilleCity_Movement_WallysUncleExitNorth1:
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

MauvilleCity_Movement_WallysUncleExitEast1:
	walk_left
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_PlayerFaceUncleNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerNorth:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_WallysUncleApproachPlayerEast:
	walk_right
	walk_up
	step_end

MauvilleCity_Movement_WallysUncleExitNorth2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_WallysUncleExitEast2:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottApproachPlayerNorth:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

MauvilleCity_Movement_ScottApproachPlayerEast:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

MauvilleCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MauvilleCity_EventScript_Wattson::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM24_FROM_WATTSON, MauvilleCity_EventScript_ReceivedThunderbolt
	goto_if_eq VAR_NEW_MAUVILLE_STATE, 2, MauvilleCity_EventScript_CompletedNewMauville
	goto_if_set FLAG_GOT_BASEMENT_KEY_FROM_WATTSON, MauvilleCity_EventScript_BegunNewMauville
	msgbox MauvilleCity_Text_WattsonNeedFavorTakeKey, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setflag FLAG_GOT_BASEMENT_KEY_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_BegunNewMauville::
	msgbox MauvilleCity_Text_WattsonWontBeChallenge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_CompletedNewMauville::
	msgbox MauvilleCity_Text_WattsonThanksTakeTM, MSGBOX_DEFAULT
	giveitem ITEM_TM24
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_TM24_FROM_WATTSON
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_ReceivedThunderbolt::
	msgbox MauvilleCity_Text_WattsonYoungTakeCharge, MSGBOX_DEFAULT
	release
	end

MauvilleCity_EventScript_RegisterWallyCall::
	lockall
	pokenavcall MauvilleCity_Text_WallyPokenavCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MauvilleCity_Text_RegisteredWally, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WALLY_MATCH_CALL
	clearflag FLAG_ENABLE_FIRST_WALLY_POKENAV_CALL
	releaseall
	end

MauvilleCity_Text_UncleHesTooPeppy:
	.string "AMCA: Bu çocuk POKéMON'u sayesinde\n"
	.string "mutlu. Umarım daha mutlu olur…\l"
	.string "But he's become a bit too peppy…$"

MauvilleCity_Text_WallyWantToChallengeGym:
	.string "WALLY: Avv, AMCA, lütfen?\p"
	.string "SALONLA mücadele edip ne kadar\n"
	.string "iyi olduğumu görmek istiyorum.\p"
	.string "Lütfen? Görebilir miyim? Lütfen?$"

MauvilleCity_Text_UncleYourePushingIt:
	.string "AMCA: Sakin ol, WALLY.\p"
	.string "POKéMON'un ile yaşamaya başladığından beri\n"
	.string "epey büyüdün ve güçlendin.\p"
	.string "Ama aniden bir SALON mücadelesi yapmak\n"
	.string "için zorlaman doğru mu?$"

MauvilleCity_Text_WallyWeCanBeatAnyone:
	.string "WALLY: Zorlamıyorum.\p"
	.string "Eğer RALTS'ın gücünü kombine edersem\n"
	.string "herkesi alt edebiliriz!$"

MauvilleCity_Text_WallyWillYouBattleMe:
	.string "WALLY: Ah! Selam, {PLAYER}!\p"
	.string "Tanıştığımızdan beri ben, artık\n"
	.string "daha güçlüyüm.\p"
	.string "{PLAYER}, sana ve AMCAMA bunu\n"
	.string "göstermek istiyorum.\p"
	.string "{PLAYER}, lütfen, benimle bir\n"
	.string "savaş yapar mısın?$"

MauvilleCity_Text_WallyMyUncleWontKnowImStrong:
	.string "WALLY: Ah... Eğer benimle savaşmazsan\n"
	.string "{PLAYER}, AMCAM ne kadar güçlendiğimi\l"
	.string "anlayamayacak.$"

MauvilleCity_Text_UncleCanYouBattleWally:
	.string "AMCA: {PLAYER}{KUN}, değil mi?\n"
	.string "WALLY adına bir ricada bulunabilir miyim\l"
	.string "Onunla bir seferlik savaşır mısın?\p"
	.string "Şuan ne sebeple olursa olsun\n"
	.string "beni dinleyecek gibi durmuyor.$"

MauvilleCity_Text_WallyPleaseBattleMe:
	.string "WALLY: {PLAYER}, lütfen!\n"
	.string "Savaş benimle, lütfen.$"

MauvilleCity_Text_WallyHereICome:
	.string "WALLY: {PLAYER}, teşekkür ederim.\p"
	.string "Tamam. İşte geliyorum!$"

MauvilleCity_Text_WallyDefeat:
	.string "WALLY: … … … … … … …\p"
	.string "… … … … … … … …\p"
	.string "B-ben kaybettim…$"

MauvilleCity_Text_WallyIllGoBackToVerdanturf:
	.string "WALLY: AMCA…\n"
	.string "VERDANTURF'a geri döneceğim…$"

MauvilleCity_Text_ThankYouNotEnoughToBattle:
	.string "{PLAYER}, teşekkürler.\n"
	.string "EĞİTMEN olmak zor, değil mi?\p"
	.string "Sadece POKéMON'a sahip olmak ve\n"
	.string "savaşa sokmak yetmez. Gerçek bir\l"
	.string "EĞİTMEN olmak böyle birşey değil.$"

MauvilleCity_Text_UncleNoNeedToBeDown:
	.string "AMCA: WALLY, kendini üzmene hiç\n"
	.string "gerek yok.\p"
	.string "Seni bundan daha ve daha güçlü\n"
	.string "olmaman için tutan ne?\p"
	.string "Hadi, eve gidelim.\n"
	.string "Herkes seni bekliyor.$"

MauvilleCity_Text_UncleVisitUsSometime:
	.string "AMCA: {PLAYER}{KUN}, şimdi fark ettim\n"
	.string "sen, WALLY'e POKéMON'unu yakalarken\l"
	.string "göz kulak olan EĞİTMENSİN\l"
	.string "değil mi?\p"
	.string "Neden bir ara bizi ziyarete\n"
	.string "VERDANTURF'a gelmiyorsun?\l"
	.string "Eminim ki WALLY çok mutlu olacak.$"


MauvilleCity_Text_WallyPokenavCall:
	.string "… … … … … …\n"
	.string "… … … … … Beep!\p"
	.string "WALLY: Ah, merhaba, {PLAYER}!\p"
	.string "Sana sadece amcamın bana bir\n"
	.string "POKéNAV aldığını söyleyecektim!\p"
	.string "Artık seninle her zaman bağlantıda\n"
	.string "olacağım, {PLAYER}!\p"
	.string "… … … … … …\n"
	.string "… … … … … (çıt)!$"

MauvilleCity_Text_RegisteredWally:
	.string "WALLY POKéNAV'a\n"
	.string "kaydedildi.$"

MauvilleCity_Text_ScottYouDidntHoldBack:
	.string "SCOTT: Hehe…\n"
	.string "Maçınızı izliyordum!\p"
	.string "Bu WALLY çocuğuyla,\n"
	.string "arkadaşsınız değil mi?\p"
	.string "Ama sen kendini tutmadın ve\n"
	.string "onu etkileyici bir şekilde yendin.\p"
	.string "Evet! İşte bu olması gereken\n"
	.string "POKéMON savaşı!\p"
	.string "Bu tür EĞİTMENLER idolümdür!\p"
	.string "… … … … … …\n"
	.string "Seni destekliyor olacağım!$"

MauvilleCity_Text_WattsonNeedFavorTakeKey:
	.string "WATTSON: Ah, {PLAYER}{KUN}!\n"
	.string "Epey gayretli gözüküyorsun!\l"
	.string "Bu iyi bir şey, wahahahaha!\p"
	.string "Pekala! Kararımı verdim!\n"
	.string "Bana bir iyilik yap, {PLAYER}{KUN}!\p"
	.string "MAUVILLE ŞEHRİ'nin YENİ MAUVILLE diye\n"
	.string "adlandırılan bir yeraltı sektörü var.\p"
	.string "{PLAYER}{KUN}, senden oraya gidip\n"
	.string "JENERATÖRÜ kapatmanı isteyeceğim.\p"
	.string "JENERATÖR birazcık düzensiz çalışıyor\n"
	.string "bu yüzden yaklaşmak güvenli değil.\p"
	.string "İşte, girebilmen için YENİ MAUVILLE'in\n"
	.string "ANAHTARI.$"

MauvilleCity_Text_WattsonWontBeChallenge:
	.string "WATTSON: Endişelenme.\n"
	.string "Sana bir zorluk çıkartmayacaktır.\p"
	.string "ROTA 110 dan kısa bir SÖRF ile\n"
	.string "YENİ MAUVILLE'in girişini bulabilirsin\p"
	.string "İşte bu, işte şimdi güvenimi kazandın!\n"
	.string "Wahahahaha!$"

MauvilleCity_Text_WattsonThanksTakeTM:
	.string "WATTSON: Wahahahaha!\p"
	.string "Biliyordum, {PLAYER}{KUN}! Sana danışarak\n"
	.string "doğru kararı verdiğimi biliyordum!\p"
	.string "Bu da teşekkürüm--bir TM THUNDERBOLT\n"
	.string "içerir!\p"
	.string "Devam et, bunu hak ettin!$"

MauvilleCity_Text_WattsonYoungTakeCharge:
	.string "WATTSON: Wahahahaha!\p"
	.string "Genç adımların şarj olup devam\n"
	.string "ettiklerini görmek beni neşelendiriyor!$"

MauvilleCity_Text_NurseHurtMonBackToHealth:
	.string "Savaş ve diğer şeyler için POKéMON'a\n"
	.string "sahip olmak havalı…\p"
	.string "Ama POKéMON'un zarar görürse,\n"
	.string "iyileşmesi için onu hemşireye götür.$"

MauvilleCity_Text_AllSortsOfPeopleComeThrough:
	.string "Bu kasabanın yolları doğuya, batıya,\n"
	.string "kuzeye ve güneye her yöne uzar.\p"
	.string "Bu yüzden, buraya her türden insan\n"
	.string "daima gelir.$"

MauvilleCity_Text_RydelVeryGenerous:
	.string "Henüz RYDEL'ın BİSİKLETİNE sahip\p"
	.string "değil misin? RYDEL, dükkan sahibi,\n"
	.string "çok cömert bir adam.$"

MauvilleCity_Text_PokemonCanJumpYouOnBike:
	.string "BİSİKLET sürerken bile,\n"
	.string "vahşi bir POKéMON sana saldırabilir.$"

MauvilleCity_Text_CitySign:
	.string "MAUVILLE ŞEHRİ\n"
	.string "“Eğlenceli, aydın ve parlak şehir!”$"

MauvilleCity_Text_GymSign:
	.string "MAUVILLE ŞEHRİ POKéMON SALONU\n"
	.string "LİDER: WATTSON\l"
	.string "“Neşeli ve şok edici bir adam!”$"

MauvilleCity_Text_BikeShopSign:
	.string "“Çakılın üzerinde sür ve ruhunu\n"
	.string "çalkala!”\l"
	.string "RYDEL'IN BİSİKLETLERİ$"

MauvilleCity_Text_GameCornerSign:
	.string "“Herkes için oyun merkezi!”\n"
	.string "MAUVILLE OYUN KÖŞESİ$"

MauvilleCity_Text_ExplainTV:
	.string "Selam, TV'yi kontrol ettin mi?\p"
	.string "Son zamanlarda bir sürü harika\n"
	.string "şov başladı.\p"
	.string "TV harika. Bazen arkadaşlarımı\n"
	.string "ekranda görüyorum.\p"
	.string "Ve, bazen, seni de aniden TV de\n"
	.string "gösterebiliyorlar.\p"
	.string "Bazen ben de TV ye çıkmayı diliyorum.\p"
	.string "Bu yüzden herhangi bir yerdeyken\n"
	.string "TV'yi kontrol etmelisin.$"

MauvilleCity_Text_BeenCheckingOutTV:
	.string "Selam, TV'yi kontrol ettin mi?$"
