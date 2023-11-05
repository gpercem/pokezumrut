BattleFrontier_Lounge7_MapScripts::
	.byte 0

BattleFrontier_Lounge7_EventScript_LeftMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_1
	goto_if_set FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor
	msgbox BattleFrontier_Lounge7_Text_LeftTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_BEAUTY_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetLeftTutor::
	msgbox BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 0
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_1
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_Softboiled
	case 1, BattleFrontier_Lounge7_EventScript_SeismicToss
	case 2, BattleFrontier_Lounge7_EventScript_DreamEater
	case 3, BattleFrontier_Lounge7_EventScript_MegaPunch
	case 4, BattleFrontier_Lounge7_EventScript_MegaKick
	case 5, BattleFrontier_Lounge7_EventScript_BodySlam
	case 6, BattleFrontier_Lounge7_EventScript_RockSlide
	case 7, BattleFrontier_Lounge7_EventScript_Counter
	case 8, BattleFrontier_Lounge7_EventScript_ThunderWave
	case 9, BattleFrontier_Lounge7_EventScript_SwordsDance
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_Softboiled::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SeismicToss::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_DreamEater::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaPunch::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MegaKick::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_BodySlam::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RockSlide::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Counter::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderWave::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_SwordsDance::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_RightMoveTutor::
	lock
	faceplayer
	setvar VAR_TEMP_C, SCROLL_MULTI_BF_MOVE_TUTOR_2
	goto_if_set FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR, BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor
	msgbox BattleFrontier_Lounge7_Text_RightTutorIntro, MSGBOX_DEFAULT
	setflag FLAG_MET_FRONTIER_SWIMMER_MOVE_TUTOR
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_AlreadyMetRightTutor::
	msgbox BattleFrontier_Lounge7_Text_RightTutorWelcomeBack, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_ChooseRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	special ShowBattlePointsWindow
	setvar VAR_TEMP_E, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 0
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove::
	message BattleFrontier_Lounge7_Text_TeachWhichMove
	waitmessage
	setvar VAR_TEMP_E, 1
	setvar VAR_0x8004, SCROLL_MULTI_BF_MOVE_TUTOR_2
	setvar VAR_0x8006, 1
	special ShowScrollableMultichoice
	waitstate
	copyvar VAR_TEMP_D, VAR_RESULT
	switch VAR_RESULT
	case 0, BattleFrontier_Lounge7_EventScript_DefenseCurl
	case 1, BattleFrontier_Lounge7_EventScript_Snore
	case 2, BattleFrontier_Lounge7_EventScript_MudSlap
	case 3, BattleFrontier_Lounge7_EventScript_Swift
	case 4, BattleFrontier_Lounge7_EventScript_IcyWind
	case 5, BattleFrontier_Lounge7_EventScript_Endure
	case 6, BattleFrontier_Lounge7_EventScript_PsychUp
	case 7, BattleFrontier_Lounge7_EventScript_IcePunch
	case 8, BattleFrontier_Lounge7_EventScript_ThunderPunch
	case 9, BattleFrontier_Lounge7_EventScript_FirePunch
	case 10, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect
	end

BattleFrontier_Lounge7_EventScript_DefenseCurl::
	setvar VAR_0x8008, 16
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Snore::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_MudSlap::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Swift::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcyWind::
	setvar VAR_0x8008, 24
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_Endure::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_PsychUp::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_IcePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ThunderPunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_FirePunch::
	setvar VAR_0x8008, 48
	goto BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection
	end

BattleFrontier_Lounge7_EventScript_ExitTutorMoveSelect::
	special CloseBattleFrontierTutorWindow
	special CloseBattlePointsWindow
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge7_EventScript_CancelChooseMon::
	msgbox BattleFrontier_Lounge7_Text_YouDontWantTo, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_D is the move selection
@ VAR_TEMP_E is which move tutor was spoken to
BattleFrontier_Lounge7_EventScript_ConfirmMoveSelection::
	copyvar VAR_0x8004, VAR_TEMP_D
	copyvar VAR_0x8005, VAR_TEMP_E
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	copyvar VAR_0x8004, VAR_TEMP_C
	msgbox BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge7_EventScript_ChooseNewMove
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge7_EventScript_TeachTutorMove
	msgbox BattleFrontier_Lounge7_Text_HaventGotEnoughPoints, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge7_EventScript_ChooseNewMove
	end

BattleFrontier_Lounge7_EventScript_TeachTutorMove::
	msgbox BattleFrontier_Lounge7_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	special GetBattleFrontierTutorMoveIndex
	fadescreen FADE_TO_BLACK
	special CloseBattlePointsWindow
	special CloseBattleFrontierTutorWindow
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_Lounge7_EventScript_CancelChooseMon
	msgbox BattleFrontier_Lounge7_Text_IllTakeBattlePoints, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	release
	end

BattleFrontier_Lounge7_EventScript_ChooseNewMove::
	goto_if_eq VAR_TEMP_E, 0, BattleFrontier_Lounge7_EventScript_ChooseNewLeftTutorMove
	goto BattleFrontier_Lounge7_EventScript_ChooseNewRightTutorMove
	end

BattleFrontier_Lounge7_EventScript_Sailor::
	msgbox BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong, MSGBOX_NPC
	end

BattleFrontier_Lounge7_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful, MSGBOX_NPC
	end

BattleFrontier_Lounge7_Text_LeftTutorIntro:
	.string "Buhahaha!\pŞimdi bakınca anlayamazsınız ama\neskiden sert bir ANTRENÖRdüm.\pEtraftaki en sert GÜZEL olarak ün\nsalmıştım, benden söylemesi!\p… … … … … …\pŞimdi ne oldu? Bana inanmıyorsun.\pBen şuradaki palavracı kadın gibi\ndeğilim. Ben gerçekten yetenekliyim!\pSana kanıtlamama izin ver.\nPOKéMON'unuza özel ve sevimli\lhareketler öğretebilirim.\pAma derslerim bedava değil. Öğrettiğim\nhareketlerin bedelini birazcık Savaş\lPuanı ile ödemeye ne dersiniz?$"

BattleFrontier_Lounge7_Text_LeftTutorWelcomeBack:
	.string "Buhahaha!\pÖzel ve bir o kadar da sevimli POKéMON\nhareketlerini öğrenmek için geri mi\ldöndün?$"

BattleFrontier_Lounge7_Text_TeachWhichMove:
	.string "İyi, iyi, buraya bak! Hangi hareketi\nöğreteyim?$"

BattleFrontier_Lounge7_Text_MoveWillBeXBattlePoints:
	.string "Hareket {STR_VAR_1}, değil mi? Bu\n{STR_VAR_2} olacak. Savaş Puanları,\ltamam mı?$"

BattleFrontier_Lounge7_Text_TeachMoveToWhichMon:
	.string "Tamam, tamam, şimdi hareketi öğretmem\ngereken POKemon'u seç.$"

BattleFrontier_Lounge7_Text_HaventGotEnoughPoints:
	.string "Bu da ne… Yeterince Savaş Puanın\nyok!$"

BattleFrontier_Lounge7_Text_IllTakeBattlePoints:
	.string "Şimdi ne kadar yetenekli olduğumu\ngörüyor musun? Savaş puanlarınızı\lalacağım, teşekkürler!$"

BattleFrontier_Lounge7_Text_YouDontWantTo:
	.string "Neymiş o? İstemiyorsun…\pNe kadar yetenekli olduğumu görmek\nistiyorsanız, istediğiniz zaman beni\lgörmeye gelin!$"

BattleFrontier_Lounge7_Text_RightTutorIntro:
	.string "Hihihi!\pŞimdi görmenin zor olduğunu biliyorum\nama eskiden harika bir ANTRENÖRDÜM.\pEtraftaki en yenilmez YÜZÜCÜ olarak ün\nsalmıştım, benden söylemesi!\p… … … … … …\pSorun nedir? Bana inanmıyorsun.\pBen oradaki soytarı kadın gibi değilim.\nBen gerçekten tecrübeliyim!\pBunu sana kanıtlayabilirim.\nPokemon'unuza zor ama güzel\lhareketler öğretebilirim.\pAma derslerim bedava değil. Öğrettiğim\nhareketlerin bedelini birazcık Savaş\lPuanı ile ödemeye ne dersiniz?$"

BattleFrontier_Lounge7_Text_RightTutorWelcomeBack:
	.string "Hihihi!\pZor ama güzel POKéMON hareketlerini\nöğrenmeye mi geldin?$"

BattleFrontier_Lounge7_Text_ThinkLadiesDontGetAlong:
	.string "Bu hanımlar, birbirlerini kötüleme\nşekillerine bakarak, muhtemelen\lanlaşamadıklarını düşünüyorsunuz.\pAma bu doğru olsaydı, burada birlikte\nkalmazlardı, değil mi?$"

BattleFrontier_Lounge7_Text_LadiesWereStrongAndBeautiful:
	.string "Ben daha küçücük bir GENÇKEN, bu\nhanımlar güçlü ve güzeldi.\pBiz ANTRENÖRLER için birer idoldüler.\pŞimdi bile, yaş onların yeteneklerini\nköreltmedi.\pAslında, POKéMON hareketleri daha da\ncilalı hale geldi.\pAma… Bazı nedenlerden dolayı, yardım\nedemem ama şunu hissediyorum…\pZaman çok acımasız.$"

BattleFrontier_Lounge7_Text_SoftboiledDesc::
	.string "Kullanıcının maksimum HP'sinin yarısına\nkadar kurtarır.$"

BattleFrontier_Lounge7_Text_SeismicTossDesc::
	.string "Kullanıcının seviyesine eşit hasar\nverir.$"

BattleFrontier_Lounge7_Text_DreamEaterDesc::
	.string "Uyuyan bir düşmana verilen hasarın\nyarısını geri kazandırır.$"

BattleFrontier_Lounge7_Text_MegaPunchDesc::
	.string "İnanılmaz bir güçle atılan güçlü bir\nyumruk.$"

BattleFrontier_Lounge7_Text_MegaKickDesc::
	.string "Yoğun kuvvete sahip son derece güçlü\nbir tekme.$"

BattleFrontier_Lounge7_Text_BodySlamDesc::
	.string "Felce neden olabilecek bir tüm vücut\ndarbesi.$"

BattleFrontier_Lounge7_Text_RockSlideDesc::
	.string "Büyük kayalar fırlatılır. İrkilmeye\nneden olabilir.$"

BattleFrontier_Lounge7_Text_CounterDesc::
	.string "Herhangi bir fiziksel darbeye iki kat\ngüçle misilleme yapar.$"

BattleFrontier_Lounge7_Text_ThunderWaveDesc::
	.string "Düşmanı felç eden zayıf bir elektrik\nsarsıntısı.$"

BattleFrontier_Lounge7_Text_SwordsDanceDesc::
	.string "SALDIRI'yı keskin bir şekilde\nyükselten bir dövüş dansı.$"

BattleFrontier_Lounge7_Text_DefenseCurlDesc::
	.string "Zayıf noktaları kapatmak ve SAVUNMAYI\nyükseltmek için kıvrılır.$"

BattleFrontier_Lounge7_Text_SnoreDesc::
	.string "Sadece uykudayken kullanılabilen\nyüksek sesli bir saldırı.$"

BattleFrontier_Lounge7_Text_MudSlapDesc::
	.string "İsabet oranını düşürmek için düşmanın\nyüzüne çamur fırlatır.$"

BattleFrontier_Lounge7_Text_SwiftDesc::
	.string "Asla ıskalamayan yıldız şekilli ışınlar\npüskürtür.$"

BattleFrontier_Lounge7_Text_IcyWindDesc::
	.string "Düşmanın HIZINI düşüren tüyler\nürpertici bir saldırı.$"

BattleFrontier_Lounge7_Text_EndureDesc::
	.string "Herhangi bir at- tack'e 1 tur boyunca\ndayanır ve 1HP bırakır.$"

BattleFrontier_Lounge7_Text_PsychUpDesc::
	.string "Düşmanın efekt(ler)ini kopyalar ve\nkullanıcıya verir.$"

BattleFrontier_Lounge7_Text_IcePunchDesc::
	.string "Düşmanı dondurabilecek buz gibi bir\nyumruk.$"

BattleFrontier_Lounge7_Text_ThunderPunchDesc::
	.string "Düşmanı felç edebilen elektrikli bir\nyumruk.$"

BattleFrontier_Lounge7_Text_FirePunchDesc::
	.string "Düşmanı yakabilecek ateşli bir yumruk.$"
