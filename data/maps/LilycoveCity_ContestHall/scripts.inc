@ VAR_LAST_TALKED would have made all these direct references unnecessary
.set LOCALID_SMART_MC, 4
.set LOCALID_SMART_JUDGE, 5
.set LOCALID_SMART_CONTESTANT_1, 6
.set LOCALID_SMART_CONTESTANT_2, 7
.set LOCALID_SMART_CONTESTANT_3, 8
.set LOCALID_SMART_CONTESTANT_4, 9
.set LOCALID_SMART_AUDIENCE_4, 11
.set LOCALID_SMART_AUDIENCE_2, 12
.set LOCALID_BEAUTY_MC, 13
.set LOCALID_BEAUTY_JUDGE, 14
.set LOCALID_BEAUTY_CONTESTANT_1, 15
.set LOCALID_BEAUTY_CONTESTANT_2, 16
.set LOCALID_BEAUTY_CONTESTANT_3, 17
.set LOCALID_BEAUTY_CONTESTANT_4, 18
.set LOCALID_BEAUTY_AUDIENCE_1, 19
.set LOCALID_BEAUTY_AUDIENCE_3, 20
.set LOCALID_BEAUTY_AUDIENCE_2, 21
.set LOCALID_SMART_AUDIENCE_3, 22
.set LOCALID_CUTE_MC, 23
.set LOCALID_CUTE_JUDGE, 24
.set LOCALID_CUTE_CONTESTANT_1, 25
.set LOCALID_CUTE_CONTESTANT_2, 26
.set LOCALID_CUTE_CONTESTANT_3, 27
.set LOCALID_CUTE_CONTESTANT_4, 28
.set LOCALID_CUTE_AUDIENCE_1, 29
.set LOCALID_CUTE_AUDIENCE_3, 30
.set LOCALID_CUTE_AUDIENCE_2, 31

LilycoveCity_ContestHall_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest:
	.string "Bu POKéMON daha önce buradaki\nGÜZELLİK YARIŞMASI'nı kazanmıştı.\pPeki, tahmin et ne oldu?\nBugün, bir ZEKA YARIŞMASI da\lkazandı!\pYeteneklerim beni bile korkutuyor.$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests:
	.string "Bir sürü YARIŞMAYA katıldım, bu yüzden\nişlerin nasıl yürüdüğünü biliyorum.\pEğer bir HAVALILIK YARIŞMASI'ndaysan,\nhavalı hareketler cazip geliyor.\pAma akıllı hareketler ve sevimli\nhareketler iyi puan kazandırmıyor.$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks:
	.string "Daha önce kazanan genç adamda bir sürü\nfarklı {POKEBLOCK} vardı.\pSende de o kadar çok olsa kazanabilir\nmisin?$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous:
	.string "Vay canına, burası ne kadar büyük!\pHavadaki gerilim… Kasabalardaki\nyarışma salonları gibi değil.$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal:
	.string "Pekala, AKILLI POKEMON ve\nANTRENÖRLERİ, hazır mısınız?!\pEn iyi gösterinizi yapın! Hadi itiraz\nedelim!$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest:
	.string "JÜRİ: Bu YARIŞMA hoşuna gitti mi?\pÜç arkadaşınla birlikte geri gel ve\nhepiniz bir YARIŞMA'ya katılın!$"

LilycoveCity_ContestHall_Text_EnteredWrongContest:
	.string "Ayayay…\nYanlış yarışmaya katılmışım.\pBu POKéMON'umla ZEKA YARIŞMASI'na\ngirdim.\pHadi, zekanı kullan ve ROCK SMASH\nhareketiyle şaşırt onları!$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart:
	.string "Bu POKéMON'u zeki yetiştirmek için\nyıllarca ve tüm bilgeliğimi harcadım.\pGenç bir yavru POKéMON tarafından\nkolayca alt edilemez.\pSevgili karım, bunu görüyor musun?$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext:
	.string "İşte bu kadar!\pEğer POKéMON'um akıllıca bir hamle\nyaparsa, seyircilerin heyecanı doruğa\lçıkacak!$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife:
	.string "Ah, canım, hayır!\pSevgili ZUBAT'ımın LEECH LIFE'ı o kadar\ntatlı ki, onu tekrar tekrar kullanmaya\ldevam ettim!\pAma bu zalim insanlar bunu hiç takdir\netmiyor!$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa:
	.string "Kiyaaah!\nHarikasın, büyükbaba!$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves:
	.string "EĞİTMENLER aynı tür POKéMON'la\ngirdiklerinde bile, hepsi farklı tür\lhareketler kullanırlar.\pTıpkı insanların savaşmak için farklı\ntarzlara sahip olması gibi.$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers:
	.string "Bence POKéMON'lar eğitmenlerinden\ndaha zekilerdir. Hem de çok.$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests:
	.string "Kim ne derse desin, ZEKA\nYARIŞMALARINI hala seviyorum.\pŞu entelektüel yeşil renk…\nÇok… Çok… Havalı.$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest:
	.string "SUNUCU: Sen de GÜZELLİK YARIŞMASI'na\nkatılıyor musun? İyi şanslar!$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty:
	.string "Buradaki her POKéMON bozulmamış\nbir güzelliğe sahip!\pNeredeyse puanlamayı unutuyordum!$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty:
	.string "Bu kadar güzel bir POKéMON…\nBunun gibi bir tane daha yok.\pHerkesin gözü benimkinde olacak.$"

LilycoveCity_ContestHall_Text_OverdidGrooming:
	.string "Vaaaah!\pBu yarışma için POKéMON'umu özenle\nfırçaladım ve bakımını yaptım…\pAma biraz abarttım… POKéMON'umun\ncildi pürüzlü pürüzlü oldu…\pNe yapmalıyım?$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam:
	.string "Bu AURORA BEAM o kadar göz kamaştırıcı\nki, JÜRİ onu göremeyecek bile.\pBir saniye…\nO zaman anlamı kalmaz ki!$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe:
	.string "Bu güzel POKéMON tıpkı benim gençliğime\nbenziyor.\pBunu söylediğimde kocam içtiği\nkahveyi kustu.\pKomik bir şey mi söyledim?$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy:
	.string "Bir GÜZELLİK YARIŞMASI kazanırsam, bu\nbeni elbette mutlu eder. En azından\lnormalden daha fazla.$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon:
	.string "Vahahahah!\pŞu güzel POKéMON'lara bir bakar mısın?\nBu tür şatafatlara bayılıyorum!$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone:
	.string "Her zaman sadece güzelliğinizle\nkazanamazsınız.\pBenimki gibi güzel ve parlak olması için\nPOKéMON'unuza bakım yapmalısınız.$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest:
	.string "SUNUCU: Ee! Merhaba!\nBir yarışmanın ortasındayız!\pLütfen kayıt bankomuza girin\nve öyle gelin, tamam mı?$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals:
	.string "JÜRİ: Ne kadar çekici ve sevimli\nyarışmacılar bunlar!$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted:
	.string "Olamaz… Benim tatlı AZURILL'imin\ndikkatini başka bir POKéMON dağıttı.$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest:
	.string "POKéMON'um savaşlarda kazanamaz\nama onu bir YARIŞMA'ya koy da izle!$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel:
	.string "POKéMON'umun PETAL DANCE hareketi\nbir harika.\pKimsenin onun performansını bozmasına\nizin vermeyeceğim.$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter:
	.string "Herkesin POKéMON'u çok sevimli.\pAncak, eğer benim POKéMON'um sevimli bir\nyarışmaya girseydi…\pDiğerlerinden çok daha şirin\nolacağına eminim.$"

LilycoveCity_ContestHall_Text_MyChildIsInContest:
	.string "Çocuğum bu yarışmaya girdi.$"

LilycoveCity_ContestHall_Text_ComeOnDear:
	.string "Hadi bir tanem.\nDevam et!\pSenin POKéMON'un en iyisi!$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest:
	.string "Bence şuradaki kız aralarındaki en\ntatlısı.\pNe?\nPOKéMON'ları mı değerlendiriyorlardı?$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn:
	.string "Tüm bu sevimli POKéMON'ları görünce\nkendi POKéMON'umu almak istiyorum!\pGidip biraz yakalayacağım!$"

LilycoveCity_ContestHall_Text_BeautyContestStage:
	.string "GÜZELLİK YARIŞMASI SAHNESİ\nGÜZEL POKéMON'LARI SEYREDİN!$"

LilycoveCity_ContestHall_Text_CuteContestStage:
	.string "SEVİMLİLİK YARIŞMASI SAHNESİ\nSEVİMLİ POKéMON'LARLA ŞENLENİN!$"

LilycoveCity_ContestHall_Text_SmartContestStage:
	.string "ZEKA YARIŞMASI SAHNESİ\nDAHİ POKéMON'LAR BURADA!$"


