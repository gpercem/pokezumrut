.set LOCALID_WOMAN_1, 19
.set LOCALID_MAN_1, 20

LilycoveCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition:
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad:
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles::
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, TRUE
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, TRUE
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, TRUE
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, TRUE
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, TRUE
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, TRUE
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, TRUE
	return

LilycoveCity_EventScript_BerryGentleman::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry::
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3::
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone::
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy::
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone::
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2::
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone::
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2::
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1::
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF::
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2::
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone::
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1::
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan::
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1::
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1::
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign::
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign::
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign::
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign::
	lockall
	specialvar VAR_0x8004, CountPlayerMuseumPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings::
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady::
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign::
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign::
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign::
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt::
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer::
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1::
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2::
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3::
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4::
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival::
	lock
	faceplayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LilycoveCity_EventScript_May
	goto_if_eq VAR_RESULT, FEMALE, LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain::
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle::
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	goto_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain::
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle::
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle::
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay::
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_MayCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge::
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge::
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges::
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier::
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan::
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_EventScript_BrendanCollectBadges
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges::
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague::
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier::
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM::
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, LilycoveCity_EventScript_KnowAboutBerryBlender
	call_if_eq VAR_RESULT, NO, LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender::
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender::
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle:
	.string "MAY: N'aber, {PLAYER}{KUN}?\nSen de mi alışveriş yapıyorsun?\pBir sürü PELUŞ ve POSTER aldım.\pElbette bir sürü de POKéMON yakaladım\nve onları da düzgün bir şekilde\lyetiştiriyorum.\pAslında ben daha çok senin POKéMON'u\ndüzgün yetiştirip yetiştirmediğin\lkonusunda meraklıyım, {PLAYER}{KUN}.\pHadi savaşıp POKéMON'larımıza bakalım.$"

LilycoveCity_Text_MayNotRaisingPokemon:
	.string "MAY: Neden, {PLAYER}{KUN}?\nPOKéMON'unu geliştirmiyor musun?\pBu eğitmenliğe yakışır bir\ndavranış değil…$"

LilycoveCity_Text_MayBattleMe:
	.string "MAY: Haydi savaşalım da POKéMON'larını\nbir test edelim!$"

LilycoveCity_Text_MayWontBeBeaten:
	.string "MAY: Benim POKéMON'larım seninkilere\nyenilmeyecek, {PLAYER}{KUN}!$"

LilycoveCity_Text_MayDefeat:
	.string "MAY: … … … … … … … …\pROTA 103'te seninle yaptığım savaşı\nhatırlıyorum, {PLAYER}{KUN}.\pO savaş sayesinde bu kadar\ngüçlenebildin. Değil mi, {PLAYER}{KUN}?$"

LilycoveCity_Text_MayGoingBackToLittleroot:
	.string "MAY: Yakında LİTTLEROOT'a geri\ndönmeyi düşünüyorum.\pÇok fazla POKéMON yakaladım ve\nPOKéDEX'im ilerliyor, bu yüzden babama\lgöstermek için eve gidiyorum.$"

LilycoveCity_Text_MayYouGoingToCollectBadges:
	.string "MAY: Ne yapacaksın, {PLAYER}{KUN}?\pTüm SALON ROZETLERİNİ toplayıp POKéMON\nLİGİ mücadelesine mi katılacaksın?\pSen ROZET toplarken ben de\nPOKéDEX'im üzerinde çalışacağım.\pSenden önce tamamlayacağım!\pSonra görüşürüz!$"

LilycoveCity_Text_MayYouGoingToPokemonLeague:
	.string "MAY: Ne yapacaksın, {PLAYER}{KUN}?\pPOKéMON LİGİ mücadelesine mi\nkatılacaksın?\pYoksa POKéDEX'ini mi tamamlayacaksın?\pSavaşta sana yenilmiş olabilirim ama\nPOKéDEX'imi senden önce bitireceğim!\pGörüşürüz!$"

LilycoveCity_Text_MayYouGoingToBattleFrontier:
	.string "MAY: Ne yapacaksın, {PLAYER}{KUN}?\pSAVAŞ SINIRI mücadelesine katılacak\nmısın?\pYoksa POKéDEX'ini mi tamamlayacaksın?\pSavaşta sana yenilmiş olabilirim ama\nPOKéDEX'imi senden önce bitireceğim!\pGörüşürüz!$"

LilycoveCity_Text_BrendanShoppingLetsBattle:
	.string "BRENDAN: Selam, {PLAYER}.\pBabamın ayak işlerini yapıyorum. Hayır,\npeluş bebek falan almayacağım.\pHer neyse, uzun zaman oldu.\pKimin daha iyi POKéMON yetiştirdiğini\ngörmek için savaş yapmak ister misin?$"

LilycoveCity_Text_BrendanNoConfidence:
	.string "BRENDAN: Sorun ne?\nKendine güvenin yok mu?$"

LilycoveCity_Text_BrendanBattleMe:
	.string "BRENDAN: Haydi savaşalım da POKéMON'larını\nbir test edelim!$"

LilycoveCity_Text_BrendanWontBeBeaten:
	.string "BRENDAN: Haha, tabii ki de sana\nkaybetmeyeceğim.$"

LilycoveCity_Text_BrendanDefeat:
	.string "BRENDAN: Hıh…\nÇok güçlenmişsin.\pBu beni biraz üzdü.\nEğitmen olarak senden öndeydim.$"

LilycoveCity_Text_BrendanGoingBackToLittleroot:
	.string "BRENDAN: Eve, LİTTLEROOT'a gitmeyi\nplanlıyorum.\pBabama POKéDEX'inde yardım ettiğimi\nbiliyorsun.\pOldukça iyi gidiyor, o yüzden\ngidip ona göstermeliyim.$"

LilycoveCity_Text_BrendanYouGoingToCollectBadges:
	.string "BRENDAN: Ne yapacaksın, {PLAYER}?\pTüm SALON ROZETLERİNİ toplayıp POKéMON\nLİGİ mücadelesine mi katılacaksın?\pSen ROZET toplarken ben de\nPOKéDEX'im üzerinde çalışacağım.\pSenden önce tamamlayacağım!\pSonra görüşürüz!$"

LilycoveCity_Text_BrendanYouGoingToPokemonLeague:
	.string "BRENDAN: Ne yapacaksın, {PLAYER}?\pPOKéMON LİGİ mücadelesine mi\nkatılacaksın?\pYoksa POKéDEX'ini mi tamamlayacaksın?\pSavaşta sana yenilmiş olabilirim ama\nPOKéDEX'imi senden önce bitireceğim!\pGörüşürüz!$"

LilycoveCity_Text_BrendanYouGoingToBattleFrontier:
	.string "BRENDAN: Ne yapacaksın, {PLAYER}?\pSAVAŞ SINIRI mücadelesine katılacak\nmısın?\pYoksa POKéDEX'ini mi tamamlayacaksın?\pSavaşta sana yenilmiş olabilirim ama\nPOKéDEX'imi senden önce bitireceğim!\pGörüşürüz!$"

LilycoveCity_Text_MovedLootIntoHideoutToday:
	.string "Fufufu…\pBugün gizli sığınağımıza daha fazla\nganimet taşıdık.\pKimsin sen?!\nB-ben kendi kendime konuşuyordum!$"

LilycoveCity_Text_ChanceToDoBigThings:
	.string "Ben sadece bir haydutum. Bu yüzden\nPATRON'un ne düşündüğünü bilmiyorum…\pAma AQUA TAKIMI'nda olduğum için büyük\nşeyler yapma şansım olacağını biliyorum!\pSen de kimsin?!\nB-ben kendi kendime konuşuyordum!$"

LilycoveCity_Text_DontGoNearCaveInCove:
	.string "Hey, sen!\pKoydaki mağaraya yaklaşma!\pNeden mi? Bir nedene ihtiyacın yok!\nBen bir yetişkinim, bu yüzden\nbeni dinlemelisin!$"

LilycoveCity_Text_IfWorldBecomesOurs:
	.string "Eğer bu dünya bizim, yani AQUA\nTAKIMI'nın olursa, POKéMON'lar için de\ldaha mutlu bir yer olacaktır.$"

LilycoveCity_Text_WailmerLeapOutOfWater:
	.string "Hey! WAILMER!\nHemen sudan çık!$"

LilycoveCity_Text_GetLostMessingUpTraining:
	.string "Ha?\nNe istiyorsun?\pEğitimimizi mahvediyorsun.\nKaybol.$"

LilycoveCity_Text_ContestHallInTown:
	.string "Bu kasabada bir POKéMON YARIŞMA\nSALONU var.\pBu da ülkenin dört bir yanından iyi\nyetiştirilmiş POKéMON'ların geleceği\lanlamına geliyor.\pKalbim heyecanla atıyor!$"

LilycoveCity_Text_StrangeCaveInCove:
	.string "Kasabanın kenarındaki koyda bulunan\nşu garip mağarayı gördün mü?$"

LilycoveCity_Text_GoingToMoveDeleterForHMs:
	.string "POKéMON'uma bir YARIŞMAYA katılmak için\nbazı yeni saldırılar öğreteceğim.\pBu yüzden, SALDIRI SİLİCİ'ye gideceğim\nve ona HM saldırılarını unutturacağım.$"

LilycoveCity_Text_ImFromKanto:
	.string "KANTO'dan geldim.\pHOENN bölgesi suyu ve yemyeşil doğasıyla\nçok güzel.\pHa?\nBekle bir saniye…\pSadece bu bölgede yaşayan nadir\nPOKéMON'lar olabilir mi?$"

LilycoveCity_Text_TeamAquaBeenTrainingWailmer:
	.string "AQUA TAKIMI koyda WAILMER'larını\neğitiyor.\pBiz yelkenciler, onlar yolumuzdayken\nteknelerimizi denize indiremiyoruz!$"

LilycoveCity_Text_SomeonePuntedTeamAquaOut:
	.string "Ahoy, biliyor muydun?\pBirisi bizim için AQUA TAKIMI'nı\nyoldan çekmiş!\pBu WAILMER'ı koydan çıkardı, böylece\nteknelerimizi tekrar dışarı\lçıkarabiliriz.$"

LilycoveCity_Text_SomeoneStoleMyPokemon:
	.string "Deniz kenarındaki bir handa dalgaların\nsesini dinleyerek rahatlatıcı bir uyku\lçekiyordum…\pBiri POKéMON'umu çalana kadar!\pÇalan kimlerdi?\nAQUA TAKIMI mı, MAGMA TAKIMI mı?$"

LilycoveCity_Text_MissingPokemonCameBack:
	.string "Kayıp POKéMON'um…\nBen fark etmeden geri geldi!$"

LilycoveCity_Text_ImArtDealer:
	.string "Ben bir SANAT TÜCCARIYIM.\pGüzel sanatların, özellikle de tabloların\nalıcısı ve satıcısıyım.\pDuyduğuma göre buradaki müzede\nmuhteşem eserler sergileniyormuş.$"

LilycoveCity_Text_SeaRemainsForeverYoung:
	.string "Biz yaşlanıp buruşsak bile deniz,\nyaşamın canlı parlaklığıyla sonsuza dek\lgenç kalır…\pFihohoho fihohohohoho…$"

LilycoveCity_Text_SixtyYearsAgoHusbandProposed:
	.string "Kocam bana burada evlenme teklif edeli\naltmış yıl oldu.\pDeniz her zamanki gibi güzelliğini\lkoruyor.\pMufufufu mufufufufufu…$"

LilycoveCity_Text_TeamAquaRenovatedCavern:
	.string "Bu koydaki tuhaf mağarayı biliyor\nmusun?\pOrası doğal bir oluşumdu, ancak daha\nsonra AQUA TAKIMI geldi ve işlerini\lyaptılar.\pKendilerine doğasever AQUA TAKIMI\ndiyorlar!\pAma yaptıklarıyla söyledikleri hiç\nuyuşmuyor!$"

LilycoveCity_Text_TeamAquaLotGoneForGood:
	.string "Koydaki mağara.\pFark etmesi biraz zaman aldı ama\nşu anda tamamen boş.\pAQUA TAKIMI temelli gitmiş olmalı.$"

LilycoveCity_Text_CitySign:
	.string "LİLYCOVE ŞEHRİ\pKaranın bitip denizin başladığı yer.$"

LilycoveCity_Text_ContestHallSign:
	.string "POKéMON YARIŞMA SALONU\nEĞİTMENLER için toplanma yeri!$"

LilycoveCity_Text_MotelSign:
	.string "KOY ZAMBAĞI MOTEL\pBizi LILYCOVE'daki KOY ZAMBAĞI\nolarak hatırlayın.$"

LilycoveCity_Text_MuseumSign:
	.string "LİLYCOVE MÜZESİ\pPOKéMON Başyapıt Koleksiyonu\nsergileniyor!$"

LilycoveCity_Text_MuseumSignPlayersExhibit:
	.string "LİLYCOVE MÜZESİ\p{PLAYER}'ın POKéMON Koleksiyonu\nsergileniyor!$"

LilycoveCity_Text_HarborSignUnderConstruction:
	.string "LİLYCOVE ŞEHİR LİMANI\pS.S. TİDAL feribotu, SLATEPORT\nŞEHRİ'nde yapım aşamasındadır.\pHizmetin kısa süre içinde başlaması\nplanlanıyor.$"

LilycoveCity_Text_HarborSign:
	.string "LİLYCOVE ŞEHİR LİMANI\pS.S. TİDAL feribotunda keyifli bir\nyolculuğun tadını çıkarın.$"

LilycoveCity_Text_TrainerFanClubSign:
	.string "POKéMON EĞİTMEN HAYRAN KULÜBÜ\pTableanın her yerine eğitmen\nisimleri karalanmış…$"

LilycoveCity_Text_DepartmentStoreSign:
	.string "LİLYCOVE ALIŞVERİŞ MERKEZİ\pHarika ürünlerle doluyuz!\pİhtiyacınız olan bir şeyi bulmak için\nharika bir yer!$"

LilycoveCity_Text_MoveDeletersHouseSign:
	.string "SALDIRI SİLİCİ'NİN EVİ\pİstenmeyen POKéMON saldırıları silinir.$"

LilycoveCity_Text_DoYouKnowAboutBerryBlender:
	.string "MEYVE MİKSERİ makinesi hakkında\nbilginiz var mı?$"

LilycoveCity_Text_FasterSpinBetterPokeblocks:
	.string "Daha hızlı dönmesi için insanların\nbirlikte çalışması gerekiyor.\pNe kadar hızlı döndürürsen, o kadar iyi\n{POKEBLOCK} elde edebileceğini duydum.$"

LilycoveCity_Text_ExplainBerryBlender:
	.string "Bu, {POKEBLOCK} adı verilen bir tür\nşekerleme yapmak için kullanılır.\pEğer bir POKéMON'a iyi bir {POKEBLOCK}\nverirsen, durumu çok daha iyi\lolacaktır.$"

LilycoveCity_Text_HeardTowerCalledSkyPillar:
	.string "Denizin ortasında bir yerde bir\nkule olduğunu duydum.\pDuyduğuma göre adı GÖK SÜTUNU'ymuş.$"

LilycoveCity_Text_SawTallTowerOnRoute131:
	.string "ROTA 131 civarında bir yerde yüksek\nbir kule gördüm.\pBu yoksa…?$"

LilycoveCity_Text_JustArrivedAndSawRarePokemon:
	.string "Balayı tatilimiz için buraya yeni geldik.\pGökyüzünde uçan EJDERHA tipi bir\nPOKEMON gördük.\pHOENN bölgesinde böyle havalı\nPOKéMON'lar yaşıyor mu?$"

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon:
	.string "Balayımızda, görebildiğimiz kadar çok\nnadir POKéMON görmeye yemin ettik.\pBu yüzden gelir gelmez nadir bir POKéMON\ngördüğümüz için çok mutlu olduk!$"


