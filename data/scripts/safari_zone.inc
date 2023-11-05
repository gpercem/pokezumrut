SafariZone_EventScript_OutOfBallsMidBattle::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	end

SafariZone_EventScript_Exit::
	setvar VAR_SAFARI_ZONE_STATE, 1
	special ExitSafariMode
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_WouldYouLikeToExit:
	.string "SAFARİ BÖLGESİ'nden hemen çıkmak\nister misiniz?$"

SafariZone_Text_TimesUp:
	.string "Ding-dong! Zaman doldu!\nSAFARİ Oyununuz sona erdi.$"

SafariZone_Text_OutOfBalls:
	.string "SAFARİ TOPLARINIZ bitti. SAFARİ\nOyununuz sona erdi.$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "BESLEYİCİ üzerine bir {POKEBLOCK}\nyerleştirmek ister misiniz?$"

SafariZone_Text_PokeblockStillHere:
	.string "Daha önce bıraktığınız {STR_VAR_1}\nhala burada.$"

SafariZone_Text_PokeblockWasPlaced:
	.string "{STR_VAR_1}, {POKEBLOCK} BESLEYİCİ\nüzerine yerleştirildi.$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "SAFARİ BÖLGESİ'ne hoş geldiniz!\pBurada, HOENN'de nadiren görülen\nbirçok POKéMON türüne tanık\lolabilirsiniz.\pVe onları doğal yaşam alanlarında\nvahşi, evcilleşmemiş halleriyle\lgöreceksiniz.\pDahası, POKéMON EĞİTMENLERİ için\nkapıları açtık.\pPOKéMON'u yakalamanız için sizi teşvik\nediyoruz!\pİçeri gelin ve SAFARİ BÖLGESİ'nin\ntadını çıkarın!$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "SAFARİ BÖLGESİ'ne hoş geldiniz!\nBuraya ilk kez mi geliyorsunuz?$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "İçeri gelin ve SAFARİ BÖLGESİ'nin\ntadını çıkarın!$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "SAFARİ BÖLGESİNE girdiğinizde,\nPOKéMON yakalamak için 30 SAFARİ TOPU\lile başlarsınız.\pSAFARİ TOPLARINIZ bittiğinde veya 500\nadım yürüdüğünüzde SAFARİ Oyunu sona\lerer.\pİçeri gelin ve SAFARİ BÖLGESİ'nin\ntadını çıkarın!$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "SAFARİ BÖLGESİ'ne hoş geldiniz!\pSadece 500¥ karşılığında\nistediğinizi yakalayabilirsiniz!\lSAFARİ Oyunu oynamak ister misiniz?$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "Tamam. Lütfen başka zaman oynayın!$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "Yeterince paran yok. Özür dilerim.$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "500¥ lütfen.$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "İşte SAFARİ TOPLARINIZ.$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "{PLAYER} 30 SAFARİ TOPU aldı.$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "Oyununuz bittiğinde size haber\nvereceğiz.\pO zamana kadar, keyfinize bakın\nlütfen! Çılgın gezinize başlayın!$"

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "Affedersiniz! Bilgisayar kutunuz dolu.$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "Affedersiniz! Görünüşe göre\n{POKEBLOCK} KASANIZ yok.\pEğer {POKEBLOCK} kullanırsanız\nSAFARİ oyununuz çok daha verimli\lolacaktır.\pLütfen bir {POKEBLOCK} KASASI ile geri\ngelin.\pLILYCOVE YARIŞMA SALONU'ndan bir\n{POKEBLOCK} KASASI edinebilirsiniz.$"

SafariZone_South_Text_StillHaveTimeExit:
	.string "Hâlâ zamanınız var.\nSAFARİ BÖLGESİ'nden şimdi çıkmak\lister misiniz?$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "Lütfen vahşi maceranızın geri\nkalanının tadını çıkarın!$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "Tamam.\pKalan SAFARİ TOPLARINIZI geri\nalacağım.\pOynadığınız için teşekkürler. Tekrar\ngörüşmek dileğiyle.$"

SafariZone_South_Text_GoodLuck:
	.string "İyi şanslar!\pBir şeye ihtiyacınız olursa, lütfen\nbana söylemekten çekinmeyin!$"

SafariZone_South_Text_Boy:
	.string "Biliyor muydunuz?\pBu kare kutuya bir {POKEBLOCK}\nkoyarsanız, POKéMON etrafta toplanır.$"

SafariZone_South_Text_Man:
	.string "Daha derine gitmek istiyorum ama\nBİSİKLET getirmeyi unuttum.\pİçimden bir ses nadir POKéMON'ların\ndış bölgelerde yaşadığını söylüyor.$"

SafariZone_Southwest_Text_Woman:
	.string "Bazen POKéMON'a bir {POKEBLOCK}\nfırlattığımda görmezden geliniyor.\pPOKéMON'ların yedikleri şeyler\nhakkında sevdikleri ve sevmedikleri\lşeyler var mı?$"

SafariZone_Northwest_Text_Man:
	.string "Hof pof…\nHof pof…\pBuraya kadar gelebildim…\nAma…\pÇok yorgunum… POKéMON yakalayacak\nenerjim yok…$"

SafariZone_North_Text_Fisherman:
	.string "HOENN'de görmediğiniz SU POKEMON'unu\nbulma görevindeyim.\pGölün nerede olduğu hakkında bir\nfikrin var mı?$"

SafariZone_North_Text_Man:
	.string "Burada bir sürü nadir POKéMON\nyakalayacağım ve onları arkadaşlarımla\ltakas edeceğim!$"

SafariZone_South_Text_Youngster:
	.string "{POKEBLOCK} BESLEYİCİ üzerine bir\n{POKEBLOCK} koydum. Ama kaybolmuş\lgibi görünüyor.\pSanırım POKéMON onu ben fark etmeden\nyemiş olmalı.$"

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "SAFARİ BÖLGESİ EĞİTMEN İPUÇLARI!\pVahşi POKéMON'lara {POKEBLOCK}\natarak kaçma ihtimallerini azalt.$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "Yorgun ayaklarınızı rahatlatın.\nDİNLENME EVİ$"

SafariZone_RestHouse_Text_Youngster:
	.string "Hiç {POKEBLOCK}'um yok ama çok sayıda\nPOKéMON yakaladım.\pBir SAFARİ TOPU atmadan önce onlara\nyaklaşarak yakalama şansınızı\lartırabilirsiniz.$"

SafariZone_RestHouse_Text_PsychicM:
	.string "Eğer {POKEBLOCK} kullanırsan,\nvahşi POKéMON o kadar çabuk\lkaçmayacaktır.\pKolayca kaçmayan POKéMON'lara\n{POKEBLOCK}S vermenin pek bir faydası\lyoktur.$"

SafariZone_RestHouse_Text_FatMan:
	.string "Eğer BESLEYİCİ üzerine bir\n{POKEBLOCK} koyarsan, POKéMON'lar ona\lçekilir.\pSanırım aynı tür doğaya sahip\nPOKéMON'lar belli bir {POKEBLOCK}\ltarafından çekiliyor.$"

SafariZone_South_Text_AreaOffLimits1:
	.string "Bu alan hala yapım aşamasındadır.\nBurası yasak bölge, üzgünüm!$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "SAFARİ BÖLGESİ'nin genişletme projesi\nartık tamamlandı.\pYeni alanın keyfini çıkaracağınızı\numuyoruz.$"

SafariZone_South_Text_AreaOffLimits2:
	.string "Bu alan hala yapım aşamasındadır.\nBurası yasak bölge, üzgünüm!$"

SafariZone_Southeast_Text_LittleGirl:
	.string "Vay be! Whee! Bu POKéMON'ların\nhiçbirini daha önce görmemiştim!$"

SafariZone_Southeast_Text_FatMan:
	.string "Bu bölgedeki POKéMON'ların hepsi benim\niçin yeni.\pVe bu nadir POKéMON'ları yakalamama\nizin var! Çok havalı!$"

SafariZone_Southeast_Text_RichBoy:
	.string "Buradaki POKéMON'lar HOENN'den başka\nbir yerden gelmiş gibi görünüyor.$"

SafariZone_Northeast_Text_Boy:
	.string "Elimde sadece birkaç SAFARİ TOPU\nkaldı.\pNe yakalamam gerektiğine karar\nvermekte zorlanıyorum.$"

SafariZone_Northeast_Text_Woman:
	.string "Burada PIKACHU görebileceğini\nduydum. Nerede olabilir?$"

SafariZone_Northeast_Text_Girl:
	.string "Of ya! Hiçbir şey yakalayamıyorum!\pBir şey yakalayamazsam giriş ücretini\nboşa harcamış olacağım!$"
