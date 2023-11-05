BattleFrontier_Lounge2_MapScripts::
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMultiLink
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro::
	.string "Merhaba! SAVAŞ SINIRI ile ilgili\nhaberler söz konusu olduğunda, ben bir\lnumarayım.\pBeni SINIR MANYAĞI olarak\ndüşünebilirsiniz.\pSadece kontrol ediyorum, ama siz bir\nEĞİTİMCİSİNİZ, değil mi?\pSAVAŞ SINIRI hakkında topladığım\nen yeni haberleri memnuniyetle\lpaylaşacağım.$"

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord::
	.string "Merhaba! Beni son haber hakkında\nsorguya çekmek için mi uğradın?\lAh, pekala!$"

BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight::
	.string "İyi mi? İyi mi? Eee?\pEminim verdiğim bilgiler işinize\nyaramıştır, değil mi?$"

BattleFrontier_Lounge2_Text_FacilityIsHottest::
	.string "Bakalım şimdi.\pGörünüşe göre {STR_VAR_1} giden en\nsıcak yer.$"

BattleFrontier_Lounge2_Text_BattleTowerIsHottest::
	.string "Bakalım şimdi.\pGörünüşe göre SAVAŞ KULESİ\n{STR_VAR_1} en sıcak olanı.$"

BattleFrontier_Lounge2_Text_SalonMaidenIsThere::
	.string "Bahse girerim bunu bilmiyordunuz!\pSCOTT'un SINIR LİDERİ dediği en iyi\neğitmenlerden biri orada.\pBurayı işleten SALON HANIMI adında\ngizemli bir eğitmen.$"

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons::
	.string "SALON HANIMI ile savaştınız mı?\pRakibini ölçerken, görünüşe göre bu\nPOKéMON'ları kullanıyor:\pPSİŞİK tip PSI POKéMON, ATEŞ tip\nVOLKAN POKéMON ve NORMAL tip UYUYAN\lPOKéMON.$"

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons::
	.string "Ciddi olduğu zamanlarda SALON HANIMI\nile savaştınız mı?\pDümdüz savaşırken, görünüşe göre bu\nPOKéMON'ları kullanıyor:\pBir EJDERHA ve PSİKİK EON POKéMON, bir\nELEKTRİK tipi THUNDER POKéMON ve bir\lNORMAL tipi SLEEPING POKéMON.$"

BattleFrontier_Lounge2_Text_DomeAceIsThere::
	.string "Bahse girerim bunu bilmiyordunuz!\pSCOTT'un SINIR LİDERLERİ dediği\nen iyi eğitmenlerden biri orada.\pBurayı işleten KUBBE LİDERİ\nadında gösterişli bir eğitmen.$"

BattleFrontier_Lounge2_Text_DomeAceSilverMons::
	.string "DOME ACE ile savaştınız mı?\pRakibine hafif davrandığında, bu üç\nPOKéMON'u kullanır:\pBİR EJDERHA & UÇAN EJDERHA POKéMONU,\nBİR SU & YER ÇAMUR BALIK POKéMONU ve\lBİR ATEŞ & UÇAN ALEV POKéMONU.$"

BattleFrontier_Lounge2_Text_DomeAceGoldMons::
	.string "Ciddi olduğu zamanlarda DOME ACE ile\nsavaştınız mı?\pStratejisini gösterirken bu üç\nPOKéMON'u kullanır:\pBİR EJDERHA & UÇAN EON POKéMON, BİR SU\n& YER ÇAMUR BALIK POKéMONU ve BİR\lÇELİK & PSİŞİK TİP DEMİR BACAK\lPOKéMONU.$"

BattleFrontier_Lounge2_Text_FactoryHeadIsThere::
	.string "Bahse girerim bunu bilmiyordunuz!\pSCOTT'un SINIR LİDERLERİ dediği\nüst düzey eğitmenlerden biri orada.\pBurayı yöneten FABRİKA KAFASI denen\ngarip bir eğitmen.$"

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons::
	.string "FABRİKA LİDERİ ile savaştınız mı?\pBir düşüneyim… Savaşa girdiğinde,\nsadece üç kiralık POKéMON alır.\pSeninle hemen hemen aynı koşullar\naltında savaşır.$"

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons::
	.string "Ciddi olduğunda FABRİKA LİDERİ ile\nsavaştınız mı?\pCiddi bir şekilde savaşa girdiğinde,\nyine de üç kiralık POKéMON alır.\pSizinle hemen hemen aynı koşullar\naltında savaşır.$"

BattleFrontier_Lounge2_Text_PikeQueenIsThere::
	.string "Bahse girerim bunu bilmiyordunuz!\pSCOTT'un SINIR LİDERLERİ dediği en iyi\neğitmenlerden biri orada.\pBurayı işleten PIKE QUEEN adında\nkorkunç bir eğitmen.$"

BattleFrontier_Lounge2_Text_PikeQueenSilverMons::
	.string "Daha önce YILAN KRALİÇESİ ile\nsavaştınız mı?\pKeyfi yerinde olduğunda bu üç\nPOKéMON'u kullandığı söyleniyor:\pZEHİR tipi bir DİŞLİ YILAN POKéMON, bir\nBÖCEK & KAYA KALIBI POKéMON ve bir SU\ltipi TENDER POKéMON.$"

BattleFrontier_Lounge2_Text_PikeQueenGoldMons::
	.string "Ciddi olduğunda YILAN KRALİÇESİ ile\nsavaştınız mı?\pCidden sinirlendiğinde, bu üç\nPOKéMON'u kullandığı söylenir:\pZEHİR tipi bir DİŞLİ YILAN POKéMON, bir\nÇELİK & YER DEMİRİ YILAN POKéMON ve\lbir SU & UÇAN tip bir ZALİM POKéMON.$"

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere::
	.string "Bahse girerim bunu bilmiyordunuz!\pSCOTT'un SINIR LİDERLERİ dediği\nen iyi eğitmenlerden biri orada.\pBurayı yöneten ARENA TİKONU adında\nsevimli bir eğitmen.$"

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons::
	.string "Daha önce ARENA TYCOON ile savaştınız\nmı?\pDüşmanın yeteneğini değerlendirirken,\nsözde bu POKéMON'ları kullanır:\pBİR BUG VE SAVAŞAN TEK KORNA POKéMON,\nKARANLIK TİP AY IŞIĞI POKéMONU ve BİR\lBUG VE HAYALET KABİNİ POKéMONU.$"

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons::
	.string "Ciddi olduğunda ARENA TİKONU ile\nsavaştınız mı?\pKendini korumak için savaştığında,\nsözde bu POKéMON'ları kullanıyor:\pKARANLIK tip AY IŞIĞI POKéMONU,\nHAYALET & ZEHİR GÖLGE POKéMONU ve ÇİM\l& MÜCADELE tip MANTAR POKéMONU.$"

BattleFrontier_Lounge2_Text_PalaceMavenIsThere::
	.string "Bahse girerim bunu bilmiyordunuz!\pSCOTT'un SINIR LİDERLERİ dediği\nüst düzey eğitmenlerden biri orada.\pBurayı yöneten, SARAY MAVİSİ denen\nuğursuz bir eğitmen.$"

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons::
	.string "Daha önce PALACE MAVEN ile savaştınız\nmı?\pRakibinin ruhunu test ederken, bu\nPOKéMON'ları kullandığı söylenir:\pZEHİR ve UÇAN tipte bir YARASA\nPOKéMONU, NORMAL tipte bir TEMBEL\lPOKéMON ve SU ve BUZ tipte bir TAŞIMA\lPOKéMONU.$"

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons::
	.string "Ciddi olduğunda SARAY MAVİSİ ile\nsavaştınız mı?\pTüm gücünü savaşa verdiğinde, bu\nPOKéMON'ları kullandığı söylenir:\pATEŞ tipi LEGENDARY POKéMON, NORMAL\ntip LAZY POKéMON ve SU tipi AURORA\lPOKéMON.$"

BattleFrontier_Lounge2_Text_PyramidKingIsThere::
	.string "Bahse girerim bunu bilmiyordunuz!\pSCOTT'un SINIR LİDERLERİ dediği en iyi\neğitmenlerden biri orada.\pBurayı yöneten PİRAMİT KRALI adında\nateşli bir eğitmen.$"

BattleFrontier_Lounge2_Text_PyramidKingSilverMons::
	.string "Daha önce PYRAMID KING ile savaştınız\nmı?\pDüşmanın gücünü kontrol ederken,\ngörünüşe göre bu POKéMON'ları\lkullanıyor:\pKAYA tipi KAYA ZİRVE POKéMON, BUZ tipi\nBUZBERG POKéMON ve ÇELİK tipi DEMİR\lPOKéMON.$"

BattleFrontier_Lounge2_Text_PyramidKingGoldMons::
	.string "PYRAMID KING'le ciddiyken hiç\nsavaştınız mı?\pSıcak güçle pompalandığında, görünüşe\ngöre bu POKéMON'ları kullanıyor:\pBUZ VE UÇAN DONDURUCU POKéMON,\nELEKTRİK VE UÇAN ELEKTRİK POKéMONU\lve ATEŞ VE UÇAN ALEV tipi POKéMON.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1::
	.string "Elbette, ÇİFT SAVAŞLARA\ngirebileceğiniz birkaç yer var.\pAncak SAVAŞ KULESİ'nin ÇİFTLİ SAVAŞ\nODALARI temeldir!\pÇİFTLİ SAVAŞLARIN burada, SAVAŞ\nORTASINDA nasıl oynandığını\löğrenmeniz gereken yer burasıdır.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2::
	.string "Buradaki savaşlarda kendinizi izleyin.\pSadece ÇİFT SAVAŞLAR için\ngeliştirdikleri stratejileri olan\lANTRENÖRLER olduğunu duydum.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3::
	.string "Burada DOUBLE BATTLES konusunda\nkendinize güvendiğinizde ve rahat\lolduğunuzda, DOUBLE BATTLES sunan\ldiğer yerlere meydan okumayı\ldüşünmelisiniz.$"

BattleFrontier_Lounge2_Text_MultiBattleAdvice::
	.string "Her türden EĞİTİMCİ SAVAŞ SALONU'nda\ntoplanıyor.\pDüşünsenize, arkadaşlarınızla ya da\ntakipçilerinizle karşılaşabilirsiniz!\lDikkatli bakmalısınız!$"

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice::
	.string "Eğer bir arkadaşınızla oynuyorsanız,\nLINK ÇOKLU SAVAŞ ODASI'na gidin.\pGüçlü bir arkadaşınızla oynuyorsanız,\nzorlu düşmanlar görmeyi\lbekleyebilirsiniz!$"

BattleFrontier_Lounge2_Text_NewsGatheringPower::
	.string "Ne inanılmaz bir haber toplama gücü!\nAkıl hocamın eşi benzeri yok!$"

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation::
	.string "Ne inanılmaz bir gözlem gücü! Akıl\nhocamın eşi benzeri yok!$"

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion::
	.string "Ne inanılmaz bir ikna gücü böyle!\nAkıl hocamdan iyisi yoktur!$"

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe::
	.string "…Burası da ne böyle?\nBurası beni korkutuyor…$"


