.set LOCALID_MOM, 1
.set LOCALID_RIVAL_MOM, 4
.set LOCALID_RIVAL, 7

LittlerootTown_BrendansHouse_1F_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, LittlerootTown_BrendansHouse_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_1F_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_BrendansHouse_1F_OnFrame
	.byte 0

LittlerootTown_BrendansHouse_1F_OnLoad:
	call_if_lt VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes
	call_if_set FLAG_RECEIVED_RUNNING_SHOES, LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual
	end

LittlerootTown_BrendansHouse_1F_EventScript_SetMovingBoxes::
	setmetatile 5, 4, METATILE_BrendansMaysHouse_MovingBox_Open, TRUE
	setmetatile 5, 2, METATILE_BrendansMaysHouse_MovingBox_Closed, TRUE
	return

LittlerootTown_BrendansHouse_1F_EventScript_CheckShowShoesManual::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual
	return

LittlerootTown_BrendansHouse_1F_EventScript_ShowRunningShoesManual::
	setmetatile 3, 7, METATILE_BrendansMaysHouse_BookOnTable, TRUE
	return

LittlerootTown_BrendansHouse_1F_OnTransition:
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV
	end

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToStairs::
	setobjectxyperm LOCALID_MOM, 8, 4
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToTV::
	setobjectxyperm LOCALID_MOM, 4, 5
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_1F_EventScript_MoveMomToDoor::
	setobjectxyperm LOCALID_MOM, 9, 8
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_UP
	return

@ Many of the below scripts have no gender check because they assume youre in the correct house
@ The below SS Ticket script uses Mays house state by accident(?), but theyre both set identically after the intro
LittlerootTown_BrendansHouse_1F_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 3, LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 5, LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 6, LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 1, LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor
	map_script_2 VAR_LITTLEROOT_HOUSES_STATE_MAY, 3, PlayersHouse_1F_EventScript_GetSSTicketAndSeeLatiTV
	.2byte 0

LittlerootTown_BrendansHouse_1F_EventScript_GoUpstairsToSetClock::
	lockall
	msgbox PlayersHouse_1F_Text_GoSetTheClock, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	applymovement LOCALID_MOM, LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs
	waitmovement 0
	warp MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F, 7, 1
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_PushTowardStairs:
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_EnterHouseMovingIn::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	goto PlayersHouse_1F_EventScript_EnterHouseMovingIn
	end

LittlerootTown_BrendansHouse_1F_EventScript_PetalburgGymReport::
	lockall
	setvar VAR_0x8004, MALE
	setvar VAR_0x8005, LOCALID_MOM
	goto PlayersHouse_1F_EventScript_PetalburgGymReportMale
	end

LittlerootTown_BrendansHouse_1F_EventScript_YoureNewNeighbor::
	lockall
	playse SE_PIN
	applymovement LOCALID_RIVAL_MOM, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL_MOM, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_RIVAL_MOM, LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach
	waitmovement 0
	special GetRivalSonDaughterString
	msgbox RivalsHouse_1F_Text_OhYoureTheNewNeighbor, MSGBOX_DEFAULT
	setflag FLAG_MET_RIVAL_MOM
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2
	releaseall
	end

LittlerootTown_BrendansHouse_1F_Movement_RivalMomApproach:
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_GoSeeRoom::
	lockall
	setvar VAR_0x8004, LOCALID_MOM
	setvar VAR_0x8005, MALE
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto PlayersHouse_1F_EventScript_MomGoSeeRoom
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival0::
	lockall
	setvar VAR_0x8008, 0
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival1::
	lockall
	setvar VAR_0x8008, 1
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_BrendansHouse_1F_EventScript_MeetRival
	end

LittlerootTown_BrendansHouse_1F_EventScript_MeetRival::
	playse SE_EXIT
	delay 10
	addobject LOCALID_RIVAL
	delay 30
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call_if_ne VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2
	msgbox RivalsHouse_1F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 0, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0
	call_if_eq VAR_0x8008, 1, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1
	call_if_eq VAR_0x8008, 2, LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2
	playse SE_EXIT
	removeobject LOCALID_RIVAL
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_BRENDAN
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	delay 30
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_1F_EventScript_PlayerFaceBrendan::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer0::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer1::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanApproachPlayer2::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer0:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer1:
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanApproachPlayer2:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs0::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs1::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_EventScript_BrendanGoUpstairs2::
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2
	waitmovement 0
	return

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit0:
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit1:
	delay_16
	delay_8
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_PlayerWatchBrendanExit2:
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs0:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs1:
	walk_in_place_faster_right
	walk_right
	walk_in_place_faster_up
	walk_up
	walk_up
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	step_end

LittlerootTown_BrendansHouse_1F_Movement_BrendanGoUpstairs2:
	walk_in_place_faster_left
	walk_left
	walk_in_place_faster_up
	walk_up
	walk_up
	step_end

PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "ANNE: Gördün mü, {PLAYER}?\n"
	.string "Çok güzel değil mi?$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "Taşınanların POKéMON'ları temizlik\n"
	.string "ve taşıma işlerini bizim için yapıyor.\l"
	.string "Bu çok kullanışlı!\p"
	.string "{PLAYER}, senin odan yukarı katta.\n"
	.string "Git bir bak, canım!\p"
	.string "Baban senin için bir duvar saati\n"
	.string "almış.\l"
	.string "Onu kurmayı unutma!$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "ANNE: Ee, {PLAYER}?\n"
	.string "Odanı gördüğüne sevindin mi?$"

PlayersHouse_1F_Text_GoSetTheClock:
	.string "ANNE: {PLAYER}.\p"
	.string "Gidip odandaki saati kur, tatlım.$"

PlayersHouse_1F_Text_OhComeQuickly:
	.string "ANNE: Aa! {PLAYER}, {PLAYER}!\n"
	.string "Çabuk! Çabuk gel!$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "ANNE: Bak! Burası PETALBURG Salonu!\n"
	.string "Belki baban da televizyona çıkar!$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "ANNE: Of… Bitti bile.\p"
	.string "Sanırım baban çıktı ancak kaçırdık.\n"
	.string "Tüh.$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Aa evet.\n"
	.string "Babanın bir arkadaşı burada yaşıyor.\p"
	.string "Adı PROF. BIRCH.\p"
	.string "Hemen yanımızdaki evde yaşıyor,\n"
	.string "yani gidip kendini tanıtabilirsin.$"

PlayersHouse_1F_Text_SeeYouHoney:
	.string "ANNE: Görüşürüz, balım!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "ANNE: Kendini\n"
	.string "PROF. BIRCH'e tanıttın mı?$"

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "ANNE: Nasılsın, {PLAYER}?\n"
	.string "Yorgun görünüyorsun.\p"
	.string "Biraz dinlensen iyi olur.$"

PlayersHouse_1F_Text_TakeCareHoney:
	.string "ANNE: Kendine iyi bak, tatlım!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "ANNE: Ha? Şu rozeti sana baban mı verdi?\p"
	.string "O zaman sana şunu vereyim!$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "Kendini çok zorlama, canım.\n"
	.string "Her zaman evine dönebilirsin.\p"
	.string "Hadi balım!$"

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "ANNE: Ne oldu canım? POKéNAV mı?\n"
	.string "DEVON'dan biri mi verdi?\p"
	.string "O zaman beni kaydetmeye ne dersin?\p"
	.string "… … …$"

PlayersHouse_1F_Text_RegisteredMom:
	.string "ANNE, POKéNAV'a\n"
	.string "kaydedildi.$"

PlayersHouse_1F_Text_Vigoroth1:
	.string "Fugiiiiih!$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "Huggoh, uggo uggo…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "MUHABİR: …PETALBURG SALONU'ndan\n"
	.string "bildireceklerimiz bu kadar.$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "Televizyonda bir film var.\p"
	.string "İki adam bir piyano üstünde dans\n"
	.string "ediyorlar.\p"
	.string "Gitsem iyi olur!$"

PlayersHouse_1F_Text_RunningShoesManual:
	.string "Bu KOŞU AYAKKABILARI için bir\n"
	.string "kullanım kılavuzu.\p"
	.string "“B Butonuna basıp bu KOŞU\n"
	.string "AYAKKABILARINI giyebilirsiniz.\p"
	.string "“KOŞU AYAKKABILARINI giyin ve\n"
	.string "tozunuzu yutturun!”$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "BABA: Hm?\p"
	.string "Hey, bu sensin {PLAYER}!\p"
	.string "Seni göreli çok uzun zaman oldu,\n"
	.string "ve bayağı… güçlü görünüyorsun.\p"
	.string "Görünümün öyle gösteriyor.\n"
	.string "Ama bu yaşlı adam da hâlâ yerli\lyerinde!\p"
	.string "Evet, sana vereceğim bir şey var.\n"
	.string "BAY BRINEY isimli biri bunu sana\l"
	.string "gönderdi.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "BABA: Hm, bir gemi bileti mi?\p"
	.string "SLATEPORT ve LILYCOVE'de limanlar\n"
	.string "olduğunu biliyorum.$"

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "PETALBURG SALONU'na dönsem iyi olur.\p"
	.string "Ben yokken eve baktığın için\n"
	.string "teşekkürler.$"

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "ANNE: Baban…\p"
	.string "Uzun zamandan beri ilk defa eve geri\n"
	.string "geldi ve konuştuğu tek şey POKéMON.\p"
	.string "Biraz rahatlamalı ve keyfini çıkarmalı.$"

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "ANNE: Bu bir son dakika haberi mi?$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "Sırada son dakika haberimiz var!\p"
	.string "HOENN sakinleri, uçan BZZT…renkli\n"
	.string "bir POKéMON gördüklerini söylüyorlar.\p"
	.string "Bu POKéMON'un kimliği şu anda\n"
	.string "bilinmiyor.\p"
	.string "Şimdi standart film programımıza\n"
	.string "geri dönüyoruz.$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "ANNE: {PLAYER}, onu gördün mü?\p"
	.string "Spikerin söylediği POKéMON hangi\n"
	.string "renkteydi?$"

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "ANNE: Çok tuhaf!\n"
	.string "Hala bilinmeyen POKéMON'lar var.$"
