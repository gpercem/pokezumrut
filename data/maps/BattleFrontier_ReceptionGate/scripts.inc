.set LOCALID_GREETER, 1
.set LOCALID_GUIDE, 2
.set LOCALID_SCOTT, 4

BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_GUIDE, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
	.string "Buraya ilk kez mi geliyorsunuz? Lütfen\nbu tarafa gelin!$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
	.string "POKéMON savaşının ön safları!\nSAVAŞ SINIRI'na hoş geldiniz!$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
	.string "İlk kez gelen ziyaretçiler için\nSINIR BİLETİ veriyoruz.\pSAVAŞ SINIRI'ndaki tüm tesislerde\nkullanım içindir.\pBuyurun!$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
	.string "{PLAYER}, SINIR BİLETİ aldı.$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
	.string "{PLAYER}, EĞİTMEN KARTINI SINIR\nBİLETİNE yerleştirdi.$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
	.string "SAVAŞ SINIRI'nın sunduğu şeyleri\nbeğeneceğinizi umuyoruz!$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
	.string "???: {PLAYER}{KUN}!\nGelmişsin!$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
	.string "REHBER: Ah!\nSCOTT, efendim!\nİyi günler, efendim!$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
	.string "SCOTT: Seni burada görmek harika,\ngerçekten öyle!\pUmarım zaman ayırır ve her yeri\nkeşfedersin.\pDoğal olarak, savaşmanın özünü de\ndeneyimleyeceğini umuyorum.\pBurada benim de odam var, vaktin\nolursa ziyaret etmekten çekinme.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
	.string "Ben sizin SAVAŞ SINIRI'ndaki\ntesisler için rehberinizim.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
	.string "Hangisi hakkında bilgi edinmek\nistersiniz?$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
	.string "SAVAŞ SINIRI'nın sembolü olarak\nkabul edilen devasa kuledir.\pKulede TEKLİ, ÇİFTLİ, MULTİ ve LİNK\nMULTİ SAVAŞLAR için dört çeşit SAVAŞ\lODASI bulunmaktadır.$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
	.string "SAVAŞ KUBBESİ, devasa kubbe\nşeklindeki büyük binadır.\pSavaş Turnuvaları adı verilen\netkinlikler bu tesiste düzenlenir.\pSavaş Turnuvaları, TEKLİ ve ÇİFTLİ\nSAVAŞLAR için olmak üzere iki parkurda\lsunulur.$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
	.string "SAVAŞ SARAYI, SAVAŞ SINIRI\nsağındaki kırmızı binadır.\pTEKLİ ve ÇİFTLİ SAVAŞLAR için iki\nçeşit SAVAŞ SALONU vardır.$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
	.string "SAVAŞ ARENASI, SAVAŞ SINIRI'nın sağ\norta kısmında yer alan dojo benzeri bir\lbinadır.\pSAVAŞ ARENASI'nda KO Turnuvası adı\nverilen bir etkinlik gerçekleştirilir.$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
	.string "SAVAŞ FABRİKASI, bize en yakın\nolan büyük binadır.\pBurada Savaş Takası adı verilen bir\netkinlik düzenlenmektedir.\pSavaş Takası etkinliği TEKLİ ve ÇİFTLİ\nSAVAŞLAR için iki kur halinde\lsunulmaktadır.$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
	.string "SAVAŞ YILANI, SAVAŞ SINIRI'nın\norta kısmında bulunan POKéMON\lşeklindeki binadır.\pSavaş Seçimi adı verilen bir etkinlik\nburada gerçekleştirilir.$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
	.string "SAVAŞ PİRAMİDİ, devasa bir\npiramittir.\pBurada Savaş Görevi adı verilen bir\netkinlik gerçekleştirilir.$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
	.string "SIRALAMA SALONU SAVAŞ KULESİ'nin\nyakınında yer almaktadır.\pOrada, SAVAŞ CEPHESİ'nin birçok\nzorluğunu üstlenen EĞİTİMCİLER\ltarafından bırakılan en fantastik\lkayıtları görebilirsiniz.$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
	.string "DEĞİŞİM SERVİSİ KÖŞESİ SAVAŞ\nKULESİ'nin yakınındadır.\pSAVAŞ ÇATISI'nda kazandığınız Savaş\nPuanlarını burada muhteşem ödüllerle\ltakas edebilirsiniz.$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
	.string "SAVAŞ SINIRI'ndaki tesisler\ntarafından sunulan tüm mücadelelerde\lortak olan temel kurallar için\lrehberinizim.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
	.string "Ne hakkında bilgi edinmek istersiniz?$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
	.string "SAVAŞ SINIRI tesislerindeki tüm\nmücadeleler iki parkurdan\loluşmaktadır - Seviye 50 ve Açık\lSeviye.$"

BattleFrontier_ReceptionGate_Text_Level50Info:
	.string "Seviye 50 kursu, Seviye 50'ye kadar ve\nSeviye 50 dahil POKéMON'lara açıktır.\pAncak karşılaşacağınız hiçbir\nEĞİTMENİN 50. Seviyenin altında\lPOKéMON'a sahip olmayacağını lütfen\lunutmayın.\pBu kurs, SAVAŞ SINIRI'ndaki\nsavaşlar için giriş seviyesidir.\pBaşlamak için, bu kursa meydan\nokuyacağınızı umuyoruz.$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
	.string "Açık Seviye kursu, mücadelelere giren\nPOKéMON seviyelerine herhangi bir\lsınırlama getirmez.\pRakiplerinizin seviyeleri,\nPOKéMON'unuzun seviyelerine uyacak\lşekilde ayarlanacaktır.\pAncak, karşılaştığınız hiçbir EĞİTMEN\n60. Seviyenin altında bir POKéMON'a\lsahip olmayacaktır.$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
	.string "Neredeyse her tür POKéMON tüm\ntesislerdeki mücadelelere katılabilir.\pAncak YUMURTA ve belirli POKéMON\ntürlerine izin verilmemektedir.\pYarışmalar için gereken POKéMON sayısı\ntesise göre değişecektir.\pAncak tüm tesislerde aynı türden iki\nveya daha fazla POKéMON'a izin\lverilmez.$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
	.string "Bir SAVAŞ SINIRI tesisinde bir\nmücadeleye girerken, POKéMON aynı tür\leşyayı tutmuyor olabilir.\pLütfen bir mücadeleye giren tüm\nPOKéMON'ların farklı eşyalara sahip\lolduğundan emin olun.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
	.string "Ben sizin SINIR BİLETİ rehberinizim.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
	.string "Hangisi hakkında bilgi edinmek\nistersiniz?$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
	.string "SAVAŞ ÇATISI'nda yedi tesis\nbulunmaktadır.\pYetenekleriyle takdir kazanan\nANTRENÖRLER, tesislerin her birinden\lsembollerle ödüllendirilebilir.\pBir sembol kazanmak için,\nANTRENÖRLERİN diğer ANTRENÖRLERİ\larka arkaya yenmesi ve etkinlikleri\ltekrar tekrar kazanması gerekebilir.\pSembol kazanmak kesinlikle kolay\ndeğildir. Size bol şans diliyorum!$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
	.string "SINIR BİLETİ'nize savaş\nkaydetmek mümkündür.\pBir arkadaşınızla veya\narkadaşlarınızla yaptığınız bir savaşı\lkaydedebilirsiniz.\pVeya SAVAŞ YILANI veya SAVAŞ\nPİRAMİDİ'ndeki maçlar hariç SAVAŞ\lSINIRI'nda yapılan bir savaşı\lkaydedebilirsiniz.\pBir savaşın sonunda maçınızı\nkaydetmeyi seçebilirsiniz.$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
	.string "Savaş Puanları, SAVAŞ CEPHESİ'nde\nolağanüstü mücadele eden\lEĞİTİMCİLERE verilen ödüllerdir.\pSavaş Puanlarınızı TAKAS SERVİSİ\nKÖŞESİNDE ödüller karşılığında takas\ledebilirsiniz.$"


