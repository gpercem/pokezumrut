LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
	.string "Aman Tanrım!\nYalnız mı seyahat ediyorsun?\lAma çok gençsin! Aferin sana!\pEminim benim çocuklarım da senden bir\niki şey öğrenebilir!\pBen mi? Ben {POKEBLOCK} ustasıyım.\pBiraz ciddileşirsem, harika\n{POKEBLOCK}'lar hazırlayabilirim.\pBir {POKEBLOCK} ustasından bir şeyler\nöğrenmek ister misin?$"

LilycoveCity_House3_Text_OhAreYouSure:
	.string "Emin misin?\pHer zaman her şeyi kendi başına\nyapmaya çalışmamalısın, canım!$"

LilycoveCity_House3_Text_ExplainPokeblocks:
	.string "Harika! Sen akıllı bir ruhsun!\nSıkı dur, çünkü anlatması zordur!\pHazır mısın?\pEğer {POKEBLOCK}'lara bakarsan,\nnasıl hissettirdiklerine göre\lderecelendirildiklerini görürsünüz.\pHissetme derecesi ne kadar düşükse, o\nkadar iyidir. Bunu sakın unutma!\pİyi bir {POKEBLOCK} düşük bir his\nderecesine ve yüksek bir seviyeye\lsahiptir.\pPOKéMON'lar, sıradan {POKEBLOCK}'lardan\ndaha fazla iyi {POKEBLOCK} yiyebilir.\pVe bu çok önemlidir.\pEğer mükemmel {POKEBLOCK} yapmak istiyorsan\nfarklı türde MEYVE kullanmalısın.\pCimri olma. MEYVE çeşitleri {POKEBLOCK}'ların\nkalitesini etkiler.\pVe başka bir şey daha.\pNe kadar kişi MEYVE karıştırırsa,\n{POKEBLOCK}'lar o kadar iyi olur.\pBu yüzden diğer insanlarla konuşmalı\nve birlikte {POKEBLOCK} yapmalısın.\pİyi {POKEBLOCK}'lar yapmak için\nbilmen gereken her şey bu kadar.\pHerkes sevdiği POKéMON'a, düzgün\n{POKEBLOCK}'lara ve sevgi dolu bir\laileye sahip olsaydı, dünya daha mutlu\lbir yer olurdu.\pPes etme, canım!$"

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
	.string "Eşim dördüz doğurduğunda, emin ol\nşok olmuştum.\pAma şimdi onları birlikte oynarken\ngörmek beni mutlu ediyor.$"

LilycoveCity_House3_Text_GoingToWinMultiBattles:
	.string "ÇOKLU SAVAŞLAR yapıyoruz ama\nkazanacağımı biliyorum.$"

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
	.string "KAYIT KÖŞESİ'nde bir şeyleri\nkarıştırmayı seviyoruz.\pAma ne karıştırıyoruz?$"

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
	.string "MEYVE ÖĞÜTÜCÜ ile süper\n{POKEBLOCK}'lar yapacağız!$"

LilycoveCity_House3_Text_GoingToEnterContest:
	.string "POKéMON'umun gücüyle övünmek\nistiyorum, bu yüzden birlikte bir\lYARIŞMA'ya katılacağız.$"


