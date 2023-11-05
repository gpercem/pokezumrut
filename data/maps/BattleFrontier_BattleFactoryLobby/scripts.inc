.set LOCALID_ATTENDANT_SINGLES, 1
.set LOCALID_ATTENDANT_DOUBLES, 6

BattleFrontier_BattleFactoryLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp
	.byte 0

BattleFrontier_BattleFactoryLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryLobby_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting, MSGBOX_DEFAULT
	closemessage
	factory_setswapped
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
	factory_set FACTORY_DATA_WIN_STREAK, 0
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_save 0
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle
	end

BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	factory_save 0
	playse SE_SAVE
	waitse

BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle::
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle

BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume
	waitmessage
	factory_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	setvar VAR_0x8006, 2
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant::
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant
	end

BattleFrontier_BattleFactoryLobby_EventScript_Attendant::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_0, 0
	factory_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed
	setvar VAR_0x8006, 0
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM, 8, 13
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_SINGLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant::
	setvar VAR_LAST_TALKED, LOCALID_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleFactoryLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge

BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge::
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Picnicker::
	lock
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleFactoryLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle:
	.string "Eğitmenlerin zekasının test edildiği\nyer!\pSAVAŞ FABRİKASI'na hoş geldiniz!\pBen Savaş Takası Tekli Turnuvası için\nrehberinizim.$"

BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge:
	.string "TEKLİ DEĞİŞİM TAKAS mücadelesine\nkatılmak ister misiniz?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge:
	.string "TEKLİ SAVAŞ TAKASI Turnuvası, sadece\nkiralık POKéMON kullanılarak yapılan\lTEKLİ BİR SAVAŞ yarışmasıdır.\pÖncelikle, bu etkinlik için size özel\nolarak üç POKéMON ödünç verilecektir.\pVerilen kiralık POKéMON'ları\nkullanarak TEK SAVAŞ yapmalısınız.\pKazanırsanız, kiralık\nPOKéMON'larınızdan birini takas\letmenize izin verilir.\pBu savaş ve takas döngüsünü\ntekrarlayın - üst üste yedi kez\lkazanırsanız Savaş Puanı kazanırsınız.\pMücadelenizi yarıda kesmek isterseniz,\nlütfen oyunu kaydedin.\pKaydetmezseniz, mücadelenizden\ndiskalifiye edilirsiniz.$"

BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit:
	.string "Bir sonraki ziyaretinizi dört gözle\nbekliyoruz.$"

BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode:
	.string "Hangi seviyede mücadele etmek\nistiyorsunuz? 50. Seviye mi yoksa Açık\lSeviye mi?$"

BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge:
	.string "Mücadelenize başlamadan önce, oyunu\nkaydetmem gerekiyor. Sorun olur mu?$"

BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping:
	.string "Tamam, sen yarışırken POKéMON'unu\nsaklayacağım.$"

BattleFrontier_BattleFactoryLobby_Text_StepThisWay:
	.string "Lütfen bu taraftan.$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMonsSaveResults:
	.string "Katıldığınız için teşekkürler!\pKiralık POKéMON'umuz karşılığında\nPOKéMON'unuzu iade edeceğim.\pEtkinlik sonuçlarını da kaydetmeliyim.\nLütfen bekleyin.$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMons:
	.string "Kiralık POKéMON'umuz karşılığında\nPOKéMON'unuzu geri vereceğim.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins:
	.string "Tebrikler! Üst üste yedi Savaş Takası\nmaçı kazandınız!$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePointsForStreak:
	.string "7 galibiyetlik serinizin anısına size bu\nSavaş Puan(lar)ını veriyoruz.$"

BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints:
	.string "Oh, oh, oh!\pSavaş Puanlarınız maksimuma ulaştı.\pLütfen biraz Savaş Puanı kullandıktan\nsonra geri gelin.$"

BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume:
	.string "Biz de seni bekliyorduk!\pMücadelenize devam etmeden önce,\noyunu kaydetmeliyim.$"

BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting:
	.string "Bunu söylediğim için üzgünüm ama geçen\nsefer oyunu bırakmadan önce\lkaydetmediniz.\pSonuç olarak, mücadelenizden\ndiskalifiye edildiniz.$"

BattleFrontier_BattleFactoryLobby_Text_WellReturnMons:
	.string "Kişisel POKéMON'unuzu geri vereceğiz.$"

BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem:
	.string "{PLAYER} {STR_VAR_1} ödülünü aldı.$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle:
	.string "Eğitmenlerin zekasının test edildiği\nyer!\pSAVAŞ FABRİKASI'na hoş geldiniz!\pBen Battle Swap İkili Turnuvası için\nrehberinizim.$"

BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge:
	.string "Battle Swap Double mücadelesine\nkatılmak ister misiniz?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge:
	.string "İkili Savaş Takası Turnuvası, yalnızca\nkiralık POKéMON'ların kullanıldığı bir\lÇİFT SAVAŞ yarışmasıdır.\pÖncelikle, bu etkinlik için size özel\nolarak üç POKéMON ödünç verilecektir.\pVerilen kiralık POKéMON'ları\nkullanarak bir ÇİFT SAVAŞ\lgerçekleştirmelisiniz.\pKazanırsanız, kiralık\nPOKéMON'larınızdan birini takas\letmenize izin verilir.\pBu savaş ve takas döngüsünü\ntekrarlayın - üst üste yedi kez\lkazanırsanız Savaş Puanı kazanırsınız.\pMücadelenizi yarıda kesmek isterseniz,\nlütfen oyunu kaydedin.\pYarıda kesmeden önce kaydetmezseniz\ndiskalifiye olursunuz.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead:
	.string "FABRİKA BAŞKANI'nı yendiğiniz ve üst\nüste yedi maç kazandığınız için\ltebrikler!$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints:
	.string "Zengin bilgi birikiminiz ve keskin\nzekanızın takdiri olarak size bu Savaş\lPuan(lar)ını veriyoruz.$"

BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave:
	.string "POKéMON'unu kiralık POKéMON'umuzla\ndeğiştirmeme izin ver.\pSavaş verilerini kaydetmem gerekiyor,\nbu yüzden lütfen bekleyin.$"

BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch:
	.string "Son BATTLE FACTORY maçınızı FRONTIER\nPASS'ınıza kaydetmek ister misiniz?$"

BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves:
	.string "Merhaba! Sen, oradaki!\pYükseltilmiş bir POKéMON takımına\nsahip olmanız gerekmediği için\lburadaki etkinliklerin kolay olduğunu\lmu düşünüyorsunuz?\pBen olsam bu kadar kolay\nkazanacağımdan pek emin olmazdım.\pPOKéMON ve hareketleri hakkında\nkapsamlı bir bilgiye sahip değilseniz,\lkazanmaya devam etmek zor olacaktır.$"

BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon:
	.string "Zayıf bir POKéMON ile değiştirdim…\nSahip olmak için iyi bir tür olduğunu\ldüşündüm…\pBizi sildiler süpürdüler.$"

BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons:
	.string "İşler hiç de istediğim gibi gitmiyor.\pİyi olup olmadıklarını görmek için\nsavaş sırasında rakibinizin\lPOKéMON'unu kontrol etmeniz gerekir.$"

BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints:
	.string "Buradaki personelin bir sonraki\nrakibiniz hakkında size nasıl birkaç\lipucu verdiğini biliyor musunuz?\pBen yetişkin bir adamım ama onların\nipuçlarını anlamakta zorlanıyorum.$"

BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried:
	.string "Gerçekten çok güçlüyüm ama çok kolay\nsıkılıyorum, bu yüzden sürekli takas\lyapmaya ve savaşmaya devam ettim.\pHer neyse, Savaş Takası etkinliklerine\ngirmeye devam ettiğimde, kiralık\lPOKéMON'u değiştirdiklerini fark\lettim.$"

BattleFrontier_BattleFactoryLobby_Text_RulesAreListed:
	.string "Savaş Takası kuralları listelenmiştir.$"

BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading:
	.string "Hangi başlığı okumak istersiniz?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules:
	.string "Bir Savaş Takası etkinliğinde yalnızca\nüç POKéMON kullanabilirsiniz.\pİster kiralıyor ister takas ediyor\nolun, takımınızda aynı POKéMON'dan iki\lveya daha fazla bulunamaz.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules:
	.string "Sadece yeni yendiğiniz ANTRENÖR ile\nPOKéMON takas edebilirsiniz.\pSadece yenilmiş ANTRENÖR tarafından\nkullanılan POKéMON'ları takas\ledebilirsiniz.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules:
	.string "Kazandığınız her savaştan sonra,\nmağlup ettiğiniz rakibinizin\lPOKéMON'larından biriyle takas\lyapabilirsiniz.\pEtkinlikteki yedinci ANTRENÖR ile\nPOKéMON takası yapamazsınız.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules:
	.string "POKéMON takası yaparken dikkat\netmeniz gereken iki önemli nokta\lvardır.\pBirincisi, takas yaparken, almak üzere\nolduğunuz POKéMON'un istatistiklerini\lkontrol edemezsiniz.\pİkincisi, takımınızdaki POKéMON'lar,\nonları kiraladığınız sıraya bağlı\lolarak sırayla dizilir.\pBu sıra, takas yapıldığında bile\ndeğişmeden kalır.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules:
	.string "Açık Seviyede, kiralık POKéMON ve rakip\nANTRENÖR POKéMON'larının hepsi Seviye\l100'dür.$"
