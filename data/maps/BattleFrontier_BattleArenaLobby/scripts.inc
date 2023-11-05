.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleArenaLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth::
	setvar VAR_TEMP_1, 1
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_0, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_0, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge

BattleFrontier_BattleArenaLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge::
	setvar VAR_TEMP_0, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_0, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	call_if_eq VAR_RESULT, FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50
	call_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR, 9, 13
	setvar VAR_TEMP_0, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor:
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

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena:
	.string "EĞİTİMCİLERİN savaşçı ruhunun test\nedildiği yer!\pSAVAŞ ARENASINA hoş geldiniz!\pSet KO Turnuvası için rehberiniz\nbenim!$"

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge:
	.string "SAVAŞ ARENASI mücadelesine\nkatılmak ister misiniz?$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge:
	.string "Başka bir fırsatta meydan okumanızı\nbekliyoruz!$"

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge:
	.string "SAVAŞ ARENA'sında KO Turnuvası'nı\ngerçekleştiriyoruz.\pTüm katılımcılar üç POKéMON'dan oluşan\nbir takımla katılır.\pÜç POKéMON, görünecekleri sıraya göre\ndizilmelidir.\pSavaş sırasında, POKéMON'lar önceden\nbelirlenmiş sıraya göre her seferinde\lbir tane belirecektir.\pBir POKéMON savaşa girdiğinde, maç\nsonuçlanana kadar dışarıda kalmalıdır.\pBir maç üç turda kararsız kalırsa,\nyargılamaya gider.\pMücadelenizi yarıda kesmek isterseniz,\nlütfen oyunu kaydedin.\pKaydetmezseniz, mücadelenize devam\nedemezsiniz.\pArt arda yedi ANTRENÖRÜ yenme\nbaşarısını gösterirseniz, size Savaş\lPuanı vereceğiz.$"

BattleFrontier_BattleArenaLobby_Text_OkayToSave:
	.string "Size SAVAŞ ARENASI'nı göstermeden\nönce, kaydetmelisiniz. Tamam mı?$"

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode:
	.string "SAVAŞ ARENASI, Seviye 50 ve Açık Seviye\nolmak üzere iki mücadele seviyesi\lsunar. Sizin seçiminiz hangisi?$"

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons:
	.string "Pekâlâ, şimdi üç POKemon'unuzu seçin\nlütfen.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen:
	.string "Sevgili meydan okuyucum!\pGiriş için gerekli olan üç POKéMON'a\nsahip değilsiniz.\pKatılmak için üç farklı çeşit POKéMON\ngetirmelisiniz.\pAyrıca aynı tür öğeleri\niçermemelidirler.\pEGGS{STR_VAR_1} uygun değildir.\pHazırlıklarınızı yaptıktan sonra\nlütfen geri dönün.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50:
	.string "Sevgili meydan okuyucum!\pGiriş için gerekli olan üç POKéMON'a\nsahip değilsiniz.\pKatılmak için üç farklı türde POKéMON\ngetirmelisiniz.\pÜç farklı POKéMON'un hepsi Seviye 50\nveya daha düşük olmalıdır.\pAyrıca aynı türden öğeler\niçermemelidir.\pEGGS{STR_VAR_1} uygun değildir.\pHazırlıklarınızı yaptıktan sonra\nlütfen geri dönün.$"

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena:
	.string "Şimdi size Savaş Arenası'na kadar\nrehberlik edeceğim.$"

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown:
	.string "Sevgili meydan okuyucum!\pOyunu kapatmadan önce kaydetmediniz,\ndeğil mi?\pTalihsiz bir durum, ancak bu durum\nmeydan okumanızdan diskalifiye\ledilmenize neden oldu.\pElbette yeni bir meydan okuma ile\nbaşlayabilirsiniz.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins:
	.string "Yedi EĞİTMEN karşısında elde\nettiğiniz muhteşem galibiyetler dizisi\liçin sizi kutluyoruz!$"

BattleFrontier_BattleArenaLobby_Text_RecordAchievement:
	.string "Başarınız kaydedilecektir. Ben oyunu\nkaydederken lütfen bekleyin.$"

BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize:
	.string "7 galibiyetlik serinizin anısına size bu\nödülü takdim ediyoruz.$"

BattleFrontier_BattleArenaLobby_Text_ReceivedPrize:
	.string "{PLAYER} {STR_VAR_1} ödülünü aldı.$"

BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize:
	.string "Oh? Çantanız dolu görünüyor.\pYer açmanızı ve ödülünüz için geri\ndönmenizi tavsiye ederim.$"

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave:
	.string "Katıldığınız için çok teşekkür ederim!\pBen oyunu kaydederken lütfen\nbekleyin.$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge2:
	.string "Başka bir fırsatta meydan okumanızı\nbekliyoruz!$"

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame:
	.string "Gelişinizi dört gözle bekliyorduk.\pSize SAVAŞ ARENASI'nı göstermeden\nönce oyunu kaydetmeliyim. Lütfen\lbekleyin.$"

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch:
	.string "Son SAVAŞ ARENASI maçınızı SINIR\nBİLETİNİZE kaydedeyim mi?$"

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack:
	.string "Hakemin kararında kaybettim…\pSadece savunma hareketlerini kullanıp\nsaldırmamanın iyi bir fikir olduğunu\lsanmıyorum…$"

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked:
	.string "Değerlendirmeyi kazandım!\pRakibin POKéMON'una tutarlı bir\nşekilde vurmak işe yaradı!$"

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw:
	.string "Maçımız berabere ilan edildi.\pZamanımız dolduğunda, hem benim hem de\nrakibin POKéMON'unda yaklaşık aynı\lmiktarda HP kalmıştı.$"

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant:
	.string "SAVAŞ ARENASI'nda POKéMON sırası\nold2106ukça önemlidir.\pÖrneğin, ilk POKéMON'unuzun belirli tür\ndezavantajları varsa, ikinci\lPOKéMON'unuzu ilkine karşı süper\letkili hareketlere sahip bir POKéMON\lyapmayı deneyin.\pBunun etkili bir takım oluşturmanın iyi\nbir yolu olacağını düşünüyorum.$"

BattleFrontier_BattleArenaLobby_Text_RulesAreListed:
	.string "Set KO Turnuvası'nın kuralları\nlistelenmiştir.$"

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading:
	.string "Hangi başlığı okumak istersiniz?$"

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules:
	.string "Set KO Turnuvasının standart\nsavaşlardan farklı olarak özel\lkuralları vardır.\pİlk olarak, bir savaş sadece üç tur\nsürer.\pÜç tur sonunda sonuca karar\nverilemezse, jüriye gider.\pHAKEM, POKéMON'ların nasıl savaştığına\ngöre kazananı seçecektir.\pAyrıca, bir POKéMON, savaşının\nsonucuna karar verilene kadar\ldeğiştirilemez.$"

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules:
	.string "İlk değerlendirme faktörü Zihin dir. Bu\nfaktör, savaşçıların ne kadar agresif\lolduklarını değerlendirir.\pDeğerlendirme, eğitmenlerin\nsaldırgan hareketlerin kullanılmasını\lne sıklıkla emrettiğine dayanmaktadır.$"

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules:
	.string "İkinci değerlendirme faktörü Beceri\ndir. Bu faktör POKéMON hareketlerinin\lne kadar etkili kullanıldığını\ldeğerlendirir.\pBir hamle başarılı bir şekilde\nçalıştıysa, Beceri derecesi yükselir.\pEğer bir hamle başarısız olursa, Beceri\npuanı düşer.\pEğer bu bir saldırı hamlesiyse, hamle\nsüper etkili ise Beceri derecesi\lyükselir ve çok etkili değilse düşer.\pKORUMA ve DEDEKTİF gibi hareketler\niçin Beceri puanı yükselmez.\pRakip KORUMA veya DEDEKSİYON\nkullandıysa ve POKéMON'unuz bir\lhareketle vuramadıysa, Beceri puanı\ldüşmez.$"

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules:
	.string "Üçüncü değerlendirme faktörü Vücut-\ntur. Bu faktör, bir savaşın sonunda ne\lkadar can kaldığına dayanır.\pDerecelendirme, bir POKéMON'un\nsavaşın başında ne kadar cana sahip\lolduğunu ve sonunda ne kadar kaldığını\ldikkate alır.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon:
	.string "ARENA LİDERİ'undan koparılan bir\nzafer ve yedi EĞİTMENLİK bir seri!\pEn görkemli mücadeleniz için sizi\nkutluyoruz!$"

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints:
	.string "Sevgili meydan okuyucum, yorulmak\nbilmeyen ruhunuzun takdiri olarak,\llütfen bu Savaş Puan(lar)ını kabul\ledin.$"
