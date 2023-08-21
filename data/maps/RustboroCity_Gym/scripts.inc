RustboroCity_Gym_MapScripts::
	.byte 0

RustboroCity_Gym_EventScript_Roxanne::
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM39, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated::
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb::
	giveitem ITEM_TM39
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM39
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch::
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh::
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc::
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory::
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified::
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue::
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne::
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice:
	.string "Hey, nasıl gidiyor?\pDinle, dostum! ŞAMPİYON olmak ister\nmisin?\pBen EĞİTMEN değilim ama sana\nkazanma tavsiyesi verebilirim.\pAnlaştık o zaman! Birlikte POKéMON\nŞAMPİYONLUĞU'nu hedefleyeceğiz!\pBir EĞİTMEN olarak görevin SALON\nROZETİ toplamak.\pAma SALON LİDERLERİ kolay lokma\ndeğildir!\pİşte bu noktada ben devreye giriyorum!\nUzman tavsiyesi vermek için buradayım!\pSALON LİDERİ ROXANNE, KAYA tipi\nPOKéMON kullanıcısıdır.\pKAYA tipi çok dayanıklıdır, ancak SU tipi\nve ÇİMEN tipi hareketlere dayanamaz.\pSALON LİDERİ'ni yenersen daha sonra\nbeni görmeye gel.\pHadi bakalım!$"

RustboroCity_Gym_Text_GymGuidePostVictory:
	.string "Vay be! Ne nefes kesici bir zafer!\nTavsiyem işe yaramış olmalı!\pHarika!\nEĞİTMEN KARTINI kontrol et.\pAldığın TAŞ ROZET, kartın üzerinde\nolmalı.\pBaşka bir deyişle...\pŞAMPİYONLUĞA giden merdivenlerin ilk\nbasamağını tırmandın!\pBu harika bir his olmalı!$"

RustboroCity_Gym_Text_JoshIntro:
	.string "Biz salon eğitmenlerini hafife\nalma!\pSana neden daha iyi olduğumuzu\ngöstereceğim!$"

RustboroCity_Gym_Text_JoshDefeat:
	.string "Benim için çok iyiydin.$"

RustboroCity_Gym_Text_JoshPostBattle:
	.string "KAYA türünün korkunç gücüne dair daha\nhiçbir şey görmedin!$"

RustboroCity_Gym_Text_TommyIntro:
	.string "Beni yenemezsen, ROXANNE'e karşı hiç\nşansın olmaz!$"

RustboroCity_Gym_Text_TommyDefeat:
	.string "Vay canına!\nPotansiyelin var!$"

RustboroCity_Gym_Text_TommyPostBattle:
	.string "ROXANNE benden birkaç kat daha güçlü.\pTetikte olsan iyi olur!$"

RustboroCity_Gym_Text_MarcIntro:
	.string "Şehrin ortasında olabiliriz ama ne\nolmuş yani?\pKAYA POKEMON'larımın saldırmak için\nboş alana ihtiyacı var!$"

RustboroCity_Gym_Text_MarcDefeat:
	.string "Adamım, adamım!\nRakibimiz çok alıngandı!$"

RustboroCity_Gym_Text_MarcPostBattle:
	.string "Liderimizin hakkını vermeliyim.\pGenç yaşında KAYA tipini seçmesi akıl ve\nmantık gerektirir.$"

RustboroCity_Gym_Text_RoxanneIntro:
	.string "Merhaba, ben ROXANNE, RUSTBORO POKéMON\nSALON LİDERİ.\pPOKéMON EĞİTMEN OKULU'nda\nöğrendiklerimi savaşta uygulayabilmek\liçin bir SALON LİDERİ oldum.\pLütfen hangi POKéMON'lar ile\nsavaştığını gösterir misin?$"

RustboroCity_Gym_Text_RoxanneDefeat:
	.string "Yani… Kaybettim…\pGörünüşe göre daha öğrenecek çok şeyim\nvar…\pAnlıyorum.\pPOKéMON LİGİ'nin kurallarına göre\nEĞİTMENLERE bir SALON LİDERİNİ yenmeleri\lhalinde bu rozet verilecektir.\pLütfen resmi POKéMON LİGİ TAŞ\nROZETİNİ kabul et.$"

RustboroCity_Gym_Text_ReceivedStoneBadge:
	.string "{PLAYER} ROXANNE'den TAŞ ROZETİ'ni\naldı.$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
	.string "TAŞ ROZET, POKéMON'unun SALDIRI\ngücünü artırır.\pAyrıca savaş dışında HM saldırısı KES'i\nkullanmalarını sağlar.\pLütfen bunu da yanına al.$"

RustboroCity_Gym_Text_ExplainRockTomb:
	.string "Bu TEKNİK MAKİNE, yani TM39,\nROCK TOMB saldırısını içerir.\pSadece kayaları düşürerek hasar\nvermekle kalmaz, aynı zamanda HIZ'ı\lda düşürür.\pBir TM kullanırsan, saldırıyı anında\nbir POKéMON'a öğretirsin.\pUnutma, bir TM yalnızca bir kez\nkullanılabilir, bu yüzden kullanmadan\lönce iki kez düşün.$"

RustboroCity_Gym_Text_RoxannePostBattle:
	.string "Çok güçlü olduğun için diğer SALON\nLİDERLERİNE de meydan okumalısın.\pNe kadar EĞİTMEN ile savaşırsan\no kadar çok şey öğrenirsin.$"

RustboroCity_Gym_Text_GymStatue:
	.string "RUSTBORO ŞEHRİ POKéMON SALONU$"

RustboroCity_Gym_Text_GymStatueCertified:
	.string "RUSTBORO ŞEHRİ POKéMON SALONU\pROXANNE'İN ONAYLI EĞİTMENLERİ:\n{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall:
	.string "… … … … … …\n… … … … … … Bip!\pMerhaba, {PLAYER}. Ben RUSTBORO\nŞEHRİ'nden ROXANNE.\pBRAWLY'den duyduğuma göre eğitmenler\narasında inanılmaz bir hızla\lyükseliyormuşsun.\pSeni yenemeyeceğimi düşünmemeyi tercih\nederim.\pSöz veriyorum, bana tekrar meydan\nokuyabilmen için SALONU düzenleyeceğim.\pUmarım sen de bu fırsatı en az\nbenim kadar dört gözle bekliyorsundur!\p… … … … … …\n… … … … … … Tık!$"

RustboroCity_Gym_Text_RegisteredRoxanne:
	.string "SALON LİDERİ ROXANNE, POKéNAV'a\nkaydedildi.$"

RustboroCity_Gym_Text_RoxannePreRematch:
	.string "ROXANNE: Seni tekrar gördüğüme çok\nsevindim.\pBen ROXANNE, buranın SALON LİDERİ.\pEminim son görüşmemizden bu yana ikimiz\nde pek çok mücadele yaşadık.\pNe kadar iyi olduğumuzu görmek isterim.\nHadi savaşalım!$"

RustboroCity_Gym_Text_RoxanneRematchDefeat:
	.string "Grr…\nYine kaybettim…$"

RustboroCity_Gym_Text_RoxannePostRematch:
	.string "ROXANNE: Konu POKéMON ile savaşmak\nolduğunda hâlâ öğrenecek çok şeyim var.\pBu farkındalık, savaşmayı daha çok\nsevmemi sağlıyor!$"

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
	.string "ROXANNE: Seni tekrar gördüğüme çok\nsevindim.\pBen ROXANNE, buranın SALON LİDERİ.\pEminim son karşılaşmamızdan bu yana\nikimiz de birçok mücadele yaşadık.\pNe kadar iyi olduğumuzu görmek\nisterim…\pOlamaz… Yanında sadece bir POKéMON\nmu var?\pLütfen en az bir POKéMON daha getir.$"
