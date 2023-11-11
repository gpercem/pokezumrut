.set LOCALID_ATTENDANT, 1
.set LOCALID_NURSE, 2
.set LOCALID_GIRL, 4
.set LOCALID_MAN, 5

TrainerHill_Entrance_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, TrainerHill_Entrance_OnResume
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, TrainerHill_Entrance_OnReturn
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Entrance_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, TrainerHill_Entrance_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, TrainerHill_Entrance_OnFrame
	.byte 0

TrainerHill_Entrance_OnTransition:
	setflag FLAG_LANDMARK_TRAINER_HILL
	getplayerxy VAR_TEMP_D, VAR_RESULT
	end

@ Unused
TrainerHill_Entrance_OnWarp:
	end

TrainerHill_Entrance_OnResume:
	trainerhill_resumetimer
	setvar VAR_TEMP_0, 0
	trainerhill_getusingereader
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_TryFaceAttendant  @ VAR_RESULT always FALSE here
	setobjectxy OBJ_EVENT_ID_PLAYER, 9, 6
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_TryFaceAttendant::
	trainerhill_getwon
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	end

TrainerHill_Entrance_EventScript_PlayerDontFaceAttendant::
	end

TrainerHill_Entrance_OnReturn:
	addobject LOCALID_NURSE
	addobject LOCALID_ATTENDANT
	addobject LOCALID_MAN
	addobject LOCALID_GIRL
	end

TrainerHill_Entrance_OnLoad:
	call_if_eq VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_OpenCounterDoor
	end

TrainerHill_Entrance_EventScript_OpenCounterDoor::
	setmetatile 17, 10, METATILE_TrainerHill_GreenFloorTile, FALSE
	return

TrainerHill_Entrance_OnFrame:
	map_script_2 VAR_TEMP_0, 0, TrainerHill_Entrance_EventScript_ExitChallenge
	map_script_2 VAR_TEMP_D, 17, TrainerHill_Entrance_EventScript_ExitElevator
	map_script_2 VAR_TEMP_5, 1, TrainerHill_Entrance_EventScript_EntryTrigger
	map_script_2 VAR_TEMP_1, 1, TrainerHill_EventScript_WarpToEntranceCounter
	.2byte 0

TrainerHill_Entrance_EventScript_ExitElevator::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerExitElevator
	waitmovement 0
	setmetatile 17, 10, METATILE_TrainerHill_CounterDoor, TRUE
	special DrawWholeMapView
	playse SE_CLICK
	waitse
	setvar VAR_TEMP_D, 0
	releaseall
	end

TrainerHill_Entrance_EventScript_ExitChallenge::
	setvar VAR_TEMP_0, 1
	trainerhill_getstatus
	switch VAR_RESULT
	case TRAINER_HILL_PLAYER_STATUS_LOST, TrainerHill_Entrance_EventScript_ExitChallengeLost
	case TRAINER_HILL_PLAYER_STATUS_ECARD_SCANNED, TrainerHill_Entrance_EventScript_ExitChallengeECard
	case TRAINER_HILL_PLAYER_STATUS_NORMAL, TrainerHill_Entrance_EventScript_EndExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeLost::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_TooBadTremendousEffort, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_PlayerExitChallenge

TrainerHill_Entrance_EventScript_ExitChallengeECard::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	msgbox TrainerHill_Entrance_Text_MovedReceptionHereForSwitch, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_PlayerExitChallenge::
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	special HealPlayerParty
	releaseall
TrainerHill_Entrance_EventScript_EndExitChallenge::
	end

TrainerHill_Entrance_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

TrainerHill_Entrance_EventScript_Attendant::
	lock
	faceplayer
	trainerhill_inchallenge
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_ThanksForPlaying
	msgbox TrainerHill_Entrance_Text_HopeYouGiveItYourBest, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AttendantEnd

TrainerHill_Entrance_EventScript_ThanksForPlaying::
	msgbox TrainerHill_Entrance_Text_ThankYouForPlaying, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AttendantEnd::
	release
	end

TrainerHill_Entrance_EventScript_EntryTrigger::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PlayerFaceAttendant
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_Closed
	msgbox TrainerHill_Entrance_Text_WelcomeToTrainerHill, MSGBOX_DEFAULT
	trainerhill_getsaved
	call_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveGame
	trainerhill_allfloorsused
	goto_if_eq VAR_RESULT, TRUE, TrainerHill_Entrance_EventScript_AllFloorsUsed
	msgbox TrainerHill_Entrance_Text_TrainersUpToFloorX, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers

TrainerHill_Entrance_EventScript_AllFloorsUsed::
	msgbox TrainerHill_Entrance_Text_TrainersInEveryRoom, MSGBOX_DEFAULT
TrainerHill_Entrance_EventScript_AskChallengeTrainers::
	message TrainerHill_Entrance_Text_LikeToChallengeTrainers
	waitmessage
	multichoice 15, 6, MULTI_YESNOINFO, FALSE
	switch VAR_RESULT
	case 0, TrainerHill_Entrance_EventScript_ChooseChallenge
	case 1, TrainerHill_Entrance_EventScript_CancelEntry
	case 2, TrainerHill_Entrance_EventScript_Info
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Info::
	msgbox TrainerHill_Entrance_Text_ExplainTrainerHill, MSGBOX_DEFAULT
	goto TrainerHill_Entrance_EventScript_AskChallengeTrainers
	end

TrainerHill_Entrance_EventScript_ChooseChallenge::
	multichoice 13, 2, MULTI_TAG_MATCH_TYPE, FALSE
	switch VAR_RESULT
	case 4, TrainerHill_Entrance_EventScript_CancelEntry
	case MULTI_B_PRESSED, TrainerHill_Entrance_EventScript_CancelEntry
	trainerhill_setmode VAR_RESULT
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 1
	setvar VAR_TEMP_5, 0
	special HealPlayerParty
	msgbox TrainerHill_Entrance_Text_TimeProgessGetSetGo, MSGBOX_DEFAULT
	trainerhill_start
	releaseall
	end

TrainerHill_Entrance_EventScript_CancelEntry::
	setvar VAR_TEMP_5, 0
	msgbox TrainerHill_Entrance_Text_PleaseVisitUsAgain, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_EventScript_SaveGame::
	msgbox TrainerHill_Entrance_Text_SaveGameBeforeEnter, MSGBOX_DEFAULT
	trainerhill_setsaved
	setvar VAR_TEMP_5, 1
	call Common_EventScript_SaveGame
	goto_if_eq VAR_RESULT, FALSE, TrainerHill_Entrance_EventScript_SaveFailed
	trainerhill_setsaved
	return

TrainerHill_Entrance_EventScript_SaveFailed::
	trainerhill_clearsaved
	goto TrainerHill_Entrance_EventScript_CancelEntry
	end

TrainerHill_Entrance_EventScript_Closed::
	msgbox TrainerHill_Entrance_Text_StillGettingReady, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, TrainerHill_Entrance_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

TrainerHill_Entrance_Movement_PlayerFaceAttendant:
	face_right
	step_end

TrainerHill_Entrance_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

@ Unused
TrainerHill_Entrance_Movement_FaceUp:
	face_up
	step_end

TrainerHill_Entrance_Movement_PlayerExitElevator:
	walk_down
	walk_down
	step_end

TrainerHill_Entrance_EventScript_Records::
	lockall
	fadescreen FADE_TO_BLACK
	special ShowTrainerHillRecords
	waitstate
	releaseall
	end

TrainerHill_Entrance_EventScript_Man::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ManTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_ManTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_CantWaitToTestTheWaters, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Girl::
	goto_if_unset FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_GirlTrainerHillClosed
	msgbox TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_GirlTrainerHillClosed::
	msgbox TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen, MSGBOX_NPC
	end

TrainerHill_Entrance_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_set FLAG_SYS_GAME_CLEAR, TrainerHill_Entrance_EventScript_ExpandedPokemart
	pokemart TrainerHill_Entrance_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Basic:
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

TrainerHill_Entrance_EventScript_ExpandedPokemart::
	pokemart TrainerHill_Entrance_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
TrainerHill_Entrance_Pokemart_Expanded:
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_DIRE_HIT
	.2byte ITEM_GUARD_SPEC
	.2byte ITEM_X_ACCURACY
	.2byte ITEM_NONE
	release
	end

TrainerHill_Entrance_Text_StillGettingReady:
	.string "Burası, savaşların keyfini\nçıkarabileceğin EĞİTMEN TEPESİ.\pNe yazık ki, hâlâ bir şeyler\nhazırlıyoruz. Lütfen daha sonra\ltekrar gelin!$"

TrainerHill_Entrance_Text_WelcomeToTrainerHill:
	.string "Hoş geldiniz!\pBurası birçok savaşlarının\ntadını çıkarabileceğiniz\lEĞİTMEN TEPESİ!$"

TrainerHill_Entrance_Text_SaveGameBeforeEnter:
	.string "Buraya ilk ziyaretin mi?\pGirmeden önce lütfen oyununuzu\nkaydedin.$"

TrainerHill_Entrance_Text_TrainersUpToFloorX:
	.string "Bakalım… Şu anda burada olan\neğitmenler…\p{STR_VAR_1}. kata kadar.$"

TrainerHill_Entrance_Text_TrainersInEveryRoom:
	.string "Bakalım… Şu anda burada olan\neğitmenler…\pHer odada toplanmış eğitmenler var\ngibi görünüyor.$"

TrainerHill_Entrance_Text_LikeToChallengeTrainers:
	.string "Bekleyen eğitmenlere meydan okumak\nister misiniz?$"

TrainerHill_Entrance_Text_TimeProgessGetSetGo:
	.string "İlerlemenizi zamanlayacağım.\nBol şans!\pHazır…\pBaşla!$"

TrainerHill_Entrance_Text_PleaseVisitUsAgain:
	.string "Lütfen bizi tekrar ziyaret edin!$"

TrainerHill_Entrance_Text_TooBadTremendousEffort:
	.string "Bu çok kötüydü.\pBence mücadelenizde muazzam bir çaba\nsarf ettiniz.\pLütfen geri gel ve tekrar dene!$"

TrainerHill_Entrance_Text_HopeYouGiveItYourBest:
	.string "Umarım elinden gelenin en iyisini\nyaparsın.$"

TrainerHill_Entrance_Text_MovedReceptionHereForSwitch:
	.string "EĞİTMENLER yer değiştirdiğinde,\nburası telaşlı olabiliyor.\pİzdihamı önlemek için resepsiyon\nbankosunu buraya taşıdık.\pRahatsızlık için özür dileriz.$"

TrainerHill_Entrance_Text_ThankYouForPlaying:
	.string "Oynadığınız için teşekkürler!$"

TrainerHill_Entrance_Text_ExplainTrainerHill:
	.string "EĞİTMEN TEPESİ'nde, Zaman Saldırısı\nadında bir etkinlik düzenliyoruz.\pBu, bu sayaçtan çatıdaki sahibimize ne\nkadar sürede ulaştığınızı ölçen bir\lyarıştır.\pEn hızlı süreler Zaman Panosunda\nyayınlanır-arkadaşlarınızla yarışmayı\ldeneyin.\pYol boyunca yapılan EĞİTMEN\nsavaşlarında Exp. Puanı veya para\lverilmeyecektir.$"

TrainerHill_Entrance_Text_NeedAtLeastTwoPokemon:
	.string "Üzgünüm ama yanınızda sadece bir\nPOKéMON var gibi görünüyor.\pBu etkinliğe katılmak için en az iki\nPOKéMON'a ihtiyacınız olacak.$"

TrainerHill_Roof_Text_YouFinallyCameBravo:
	.string "Hm! Hm!\pSonunda geldin! Evet, geldin!\pBekle! Söyleme! Buraya kadar neden\ntek başına geldiğini biliyorum!\pBeni, EĞİTMEN TEPESİ'nin sahibini\ngörmek istedin, çünkü…\pBenimle bir takım kurmak\nistiyorsun! Ye-huu!\p…Ha? Bundan değil mi?\pHer neyse, seni yukarı çıkarken\nizledim. Muhteşem mücadele!\lBravo, gerçekten!$"

TrainerHill_Roof_Text_HaveTheMostMarvelousGift:
	.string "Senin gibi muhteşem biri için en\nmuhteşem hediyeye sahibim!$"

TrainerHill_Roof_Text_FullUpBeBackLaterForThis:
	.string "Ah, hayır, çantan dolu!\nBunun için daha sonra geleceksin!$"

TrainerHill_Roof_Text_GotHereMarvelouslyQuickly:
	.string "Dur bakalım!\nBuraya ne çabuk geldin.\pNe kadar muhteşem! Beni görmek için bu\nkadar acele etmene gerek yoktu!\pBu çok hoş. Resepsiyondaki Zaman\nPanosunu güncelleyeceğim!$"

TrainerHill_Roof_Text_YouWerentVeryQuick:
	.string "Ama, ya…\nBuraya çok çabuk gelemedin.$"

TrainerHill_Roof_Text_ArriveZippierNextTime:
	.string "Belki bir dahaki sefere daha hızlı\ngelirsen beni daha çok memnun\ledersin.\pO zaman seninle bir takım\noluşturmaktan memnuniyet duyarım!\pBir dahaki sefere, amigo!$"

TrainerHill_Roof_Text_BuiltTrainerHillToFindPartner:
	.string "EĞİTMEN TEPESİ'ni sadece ve sadece\ntek bir sebep için inşa ettirdim!\pBirlikte bir takım\noluşturabileceğim en uygun partneri\lbulmak için!$"

TrainerHill_Entrance_Text_ChallengeTime:
	.string "{STR_VAR_1} dk. {STR_VAR_2}.{STR_VAR_3} sn.$"

TrainerHill_Entrance_Text_WhatSortOfTrainersAreAhead:
	.string "Önümüzde ne tür EĞİTMEN ve\nPOKéMON kombinasyonları olduğunu kim\lbilebilir?\pTek bildiğim, yoluma çıkan herkesi bir\nkenara atacağım!$"

TrainerHill_Entrance_Text_CantWaitToTestTheWaters:
	.string "Bu EĞİTMEN TEPESİ'ne her yerden\nzorlu EĞİTMENLERİN geldiğini duydum.\pSuyunu test etmek için\nsabırsızlanıyorum!\pYoluma çıkan herkesi kenara atacağım!$"

TrainerHill_Entrance_Text_FriendsTryingToReachTimeBoardTop:
	.string "Şuradaki Zaman panosunu görüyor\nmusun?\pArkadaşlarım ve ben kimin en kısa\nsürede zirveye ulaşabileceğini\lgörmeye çalışıyoruz.$"

TrainerHill_Entrance_Text_DoYouKnowWhenTheyOpen:
	.string "Burayı ne zaman açacaklarını biliyor\nmusun?\pİlk meydan okuyan olmak için burada\nbekliyorum!$"

TrainerHill_Elevator_Text_ReturnToReception:
	.string "Resepsiyon bankosuna dönmek ister\nmisiniz?$"
