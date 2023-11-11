MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

@ Bard
MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar VAR_0x8004, 0
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, 1
	special PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

@ Hipster
MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag FLAG_UNLOCKED_TRENDY_SAYINGS
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	waitstate
	goto_if_eq VAR_0x8004, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq VAR_0x8004, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	waitstate
	goto_if_eq VAR_0x8006, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq VAR_0x8006, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, StorytellerGetFreeStorySlot
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	waitstate
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, StorytellerUpdateStat
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasStorytellerAlreadyRecorded
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, Script_StorytellerInitializeRandomStat
	goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

@ Unused
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

@ Giddy will continue to tell stories regardless of whether yes or no is selected below.
@ Each story there is a 10% chance it will be his last. Otherwise he will stop at 10 stories.
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "Merhaba, ben Tüccar'ım.\nBenimle dekorasyon takası yapmak\lister misin?$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "Of…\nBuna üzüldüm…$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "Ama zaten dekorasyon ticareti yaptık.$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "İstediğin bir dekoratif eşyası\ngörürsen, söyle.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "Hiçbir şey istemiyor musun?\nİstenmediğimi hissediyorum.$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "Bu dekoratif eşya bir zamanlar\n{STR_VAR_1}'e aitti.\pOnu istiyor musun?$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "Ah… Bekle bir saniye.\nTek bir dekorasyonun bile yok!$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "Tamam, bana takas edeceğin\ndekorasyonu seç.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "Benimle ticaret yapmayacak mısın?\nİstenmediğimi hissediyorum…$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "Depolanabilecek tüm {STR_VAR_2}'a\nsahipsin. Bunun için yeriniz yok.$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "Tamam, o zaman benim {STR_VAR_3} ile\nsenin {STR_VAR_2}'ni takas edeceğiz.$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "Bu dekorasyon parçası kullanımda.\nTakas edemezsin.$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "O zaman takas ederiz! Dekorasyonumu\nsenin bilgisayarına göndereceğim.$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "Olamaz! Özür dilerim!\nBu gerçekten nadir bir dekorasyon\lparçası.\pBunu takas edemem!\pBaşka bir şey olur mu?$"

MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "Ben hikâye anlatıcısıyım. Sana efsanevi\nEĞİTMENLERİN hikayelerini\lanlatabilirim.\pMasalımı dinleyecek misin?$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "Of…\nBu üzdü…$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "Bu efsaneleri biliyorum.\nHangi masalı anlatayım?$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "Ama ben efsanevi bir eğitmen\ntanımıyorum. Dolayısıyla, hiç masal\lbilmiyorum.\pEfsanevi bir hikayeye layık bir\nEĞİTMEN nereden bulunur?$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "Bu da ne?! Sen… Sen…\p{STR_VAR_1} kez {STR_VAR_2}?!\pBu gerçekten muhteşem!\nYeni bir efsanenin doğuşu!$"

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "Bu beni düşündürüyor, keşfedilmeyi\nbekleyen daha etkileyici efsaneleri\lolan başka ANTRENÖRLER olabilir mi?$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "Eğitmen misin?\pO zaman söyle bana, hiç efsanevi bir\nhikayen var mı?$"

MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "Bu arada… Bir efsanevi hikaye daha\ndinlemek ister misin?$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "Hmm… Ben tatmin olmadım…\pKeşke bana efsane denmeye layık\nhaber getirseydin.$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "Keşke daha fazla insan efsanevi\nANTRENÖRLERLE ilgili destansı\lhikâyelerimi dinlemekle ilgilense.$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "Kayıtçı Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "kayıt mı ettin$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN oyunu {STR_VAR_1}\nkez kaydetti!\p{STR_VAR_3}'ten daha dikkatli bir\nEĞİTMEN asla bulunamaz!$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "Trend Belirleyen Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "trend mi başlattın$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez yeni\ntrend başlattı!\p{STR_VAR_3} tüm HOENN bölgesi için\ntrendleri belirliyor!$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "Bahçıvan Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "meyve mi diktin$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "Bu, {STR_VAR_3} adlı EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez MEYVE\ndikti!\p{STR_VAR_3} efsanevi bir MEYVE\naşığıdır!$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "Bisikletçi Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "bisiklet mi değiştirdin$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "Bu, {STR_VAR_3} adlı eğitmenin\nhikayesidir.\pBu EĞİTMEN bisikletini {STR_VAR_1}\nkez değiştirdi!\p{STR_VAR_3} bisikletini derinden ve\ntutkuyla seviyor olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "Röportajcı Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "röportaj mı yaptın$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN ile {STR_VAR_1} kez\nröportaj yapıldı!\p{STR_VAR_3} çok dikkat çeken bir\nEĞİTMEN olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "Savaşçı Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "mi savaştın$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez\nsavaş yaptı!\p{STR_VAR_3} savaşma şansını asla\ngeri çeviremeyen bir EĞİTMEN olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "POKéMON Yakalayan Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "POKéMON mu yakaladın$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez\nPOKéMON yakaladı!\p{STR_VAR_3}, vahşi POKéMON'ların\nefsanevi yakalayıcısıdır!$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "Balıkçı Eğitmeni$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "balık mı tuttun$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTİMCİ {STR_VAR_1}'i yakaladı\nBalık tutarken POKéMON!\p{STR_VAR_3} efsanevi bir balıkçılık\nuzmanıdır!$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "YUMURTA ISITMA ANTRENÖRÜ$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "yumurta mı çatlattın$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu ANTRENÖR {STR_VAR_1}'i yumurtadan\nçıkardı. EGGS'den POKéMON!\p{STR_VAR_3} EGGS'in efsanevi bir\nsavaşçısıdır!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "Evolver TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "POKéMON mu evrimleştirdin$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1}'i POKéMON\nevrimleşiyor!\p{STR_VAR_3} POKéMON'un nihai\nevrimleştiricisidir!$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "POKéMON MERKEZİNİ SEVEN EĞİTMEN$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "POKéMON MERKEZİ'ne mi girdin$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikâyesidir.\pBu ANTRENÖR POKéMON MERKEZLERİNDE\n{STR_VAR_1} kez POKéMON iyileştirdi!\pPOKéMON MERKEZLERİNİN\n{STR_VAR_3}'ten daha büyük bir aşığı\lolamaz!$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "Evci Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "evde mi dinlendin$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "Bu, {STR_VAR_3} adlı bir ANTRENÖR'ün\nhikayesidir.\pBu ANTRENÖR evde POKéMON\n{STR_VAR_1}'ı defalarca iyileştirdi!\p{STR_VAR_3}'ten daha iyi bir ev kuşu\nolamaz!$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "SAFARİ-SEVER EĞİTMEN$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "Safari Bölgesi'ne mi girdin$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez SAFARİ\nBÖLGESİ'ne girdi!\p{STR_VAR_3} vahşi tarafı SAFARİ\nBÖLGESİ'nde ortaya çıkması gereken\lbir EĞİTMEN!$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "Kesici Eğitmen"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "KES saldırısı mı kullandın$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1}'i defalarca\nKESTİ!\p{STR_VAR_3} sadece KESMEYİ seven bir\nEĞİTMEN!$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "KAYA PARÇALAYAN ANTRENÖR$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "kaya mı parçaladın$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez KAYA\nPARÇALAMA kullandı!\p{STR_VAR_3} bir taşı bile\nparçalamadan bırakamayan bir EĞİTMEN\lolmalı!$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "Hareket Seven Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "GİZLİ ÜS mü taşıdın$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTİMCİ {STR_VAR_1} GİZLİ\nÜSSÜ'nü defalarca taşıdı!\p{STR_VAR_3} evleri sık sık taşımayı\nseven bir EĞİTİCİ!$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "SPLASH-Mutlu ANTRENÖR$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "SPLASH mi kullandın$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez SPLASH\nkullandı!\p{STR_VAR_3} etrafta PÜSKÜRTMEYİ\nseven bir EĞİTMEN!$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "İnatçı Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "STRUGGLE mı kullandın$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez\nSTRUGGLE'a güvenmek zorunda kaldı!\p{STR_VAR_3} zorluklara asla boyun\neğmeyen inatçı bir EĞİTMEN!$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "SLOT Şampiyonu$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "SLOT'ta bingo mu vurdun$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} numaralı\nYUVALARDA büyük ikramiyeyi defalarca\lkazandı.\p{STR_VAR_3} YUVALARDA şanslı olan bir\nEĞİTMEN!$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "RULET'te mi kazandın$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "Arka arkaya ROULETTE galibiyetleri\nvardı$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikayesidir.\pBu ANTRENÖR ROULETTE {STR_VAR_1}\noyununu üst üste defalarca kazandı.\pTop ROULETTE'de sektiğinde\n{STR_VAR_3} şanslıydı!$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "BATTLE TOWER Challenger$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "SAVAŞ KULESİ'ne mi katıldın$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez SAVAŞ\nKULESİ mücadelesine katıldı!\p{STR_VAR_3}, SAVAŞ KULESİ'nde\nmükemmelliği hedefleyen bir EĞİTMEN!$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "Karışım Seven Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "{POKEBLOCK} mu yaptın$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {POKEBLOCK}LARI\n{STR_VAR_1} kez yaptı!\pBERRY BLENDER kullanmakta\n{STR_VAR_3}'ten daha iyisi yoktur!$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "YARIŞMA-SEVER EĞİTMEN$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "yarışmaya mı girdin$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikayesidir.\pBu ANTRENÖR {STR_VAR_1} kez\nYARIŞMALARA katıldı!\p{STR_VAR_3} başkalarına POKéMON\ngöstermeyi seviyor olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "Yarışma Ustası$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "yarışma mı kazandın$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikayesidir.\pBu ANTRENÖR {STR_VAR_1} kez YARIŞMA\nkazandı!\p{STR_VAR_3} inanılmaz bir YARIŞMA\nustası olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "Mutlu Alışverişçi$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "alışveriş mi yaptın$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTİMCİ mağazalardan {STR_VAR_1}\nkez ürün satın aldı!\p{STR_VAR_3} alışveriş yapmak için\ndoğmuş insanlardan biri olmalı.$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "Eşya Bulma Eğitmeni$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "gizli eşya mı buldun$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} bir ÖĞE\nBULUCU'yu defalarca kullandı!\p{STR_VAR_3} gizli eşyaları bulmak için\ntoprağı eşelemekten hoşlanıyor olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "Yağmurla Islanan TRENER$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "yağmur mu yağdırdın$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTİMCİ {STR_VAR_1} kez yağmurla\nıslandı!\p{STR_VAR_3}'ün karizması yağmuru bile\nçekiyor olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "Hevesli POKéDEX Okuyucusu$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "POKéDEX'e mi baktın$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikayesidir.\pBu EĞİTMEN bir POKéDEX'i {STR_VAR_1}\nkez kontrol etti!\p{STR_VAR_3} bir POKéDEX'teki\nPOKéMON'u incelemeyi seviyor olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "Kurdele Koleksiyoncusu$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "kurdele mi aldın$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez KURDELE\naldı!\p{STR_VAR_3} KURDELE toplamayı seven\nbir EĞİTMEN olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "Çıkıntı Atlama Eğitmeni$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "tepeden aşağı mı atladın$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez\nçıkıntılardan aşağı atladı!\pEğer atlanması gereken bir çıkıntı\nvarsa, {STR_VAR_3} bunu görmezden\lgelemez!$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "Efsanevi TV İzleyicisi$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "TV mi izledin$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} kez TV\nizlemiş!\p{STR_VAR_3} televizyon izlemeyi\nseviyor olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "Zaman Bilincine Sahip Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "saate mi baktın$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} saatini\ndefalarca kontrol etti!\p{STR_VAR_3} zamanın farkında olan\ndakik bir EĞİTMEN olmalı.$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "POKéMON LOTO Sihirbazı$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "POKéMON LOTO mu kazandın$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "Bu, {STR_VAR_3} adlı bir ANTRENÖR'ün\nhikayesidir.\pBu ANTRENÖR {STR_VAR_1} kez POKéMON\nLOTERIES kazandı!\p{STR_VAR_3}'ün POKéMON takası\nyapabileceği birçok arkadaşı olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "Gündüz Bakımı Kullanan Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "bakımevine mi bıraktın$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMENİN\nhikayesidir.\pBu EĞİTMEN, POKéMON'u {STR_VAR_1}\nkez GÜNDÜZ BAKIMI'na bıraktı!\p{STR_VAR_3} POKéMON'u agresif bir\nşekilde yükselten gerçek bir çalışkan\lolmalı!$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "KABLO ARABA SEVEN EĞİTMEN$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "teleferiğe mi bindin$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "Bu, {STR_VAR_3} adlı bir TRAINER'ın\nhikayesidir.\pBu EĞİTMEN {STR_VAR_1} KABLO\nARABASINA defalarca bindi!\p{STR_VAR_3} sürekli inip çıkan meşgul\nbir EĞİTMEN olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "Kaplıca Aşığı Eğitmen$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "kaplıcalara mı girdin$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "Bu, {STR_VAR_3} adlı bir EĞİTMEN'in\nhikayesidir.\pBu EĞİTİMCİ {STR_VAR_1} kez\nkaplıcalarda yıkandı!\p{STR_VAR_3} bebek gibi pürüzsüz bir\ncilde sahip bir EĞİTMEN olmalı!$"

MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "Ben SERSEM'im! Sizin için heyecan verici\nbir hikâyem var!\pHikayemi dinlemek ister misiniz?$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "Of… Beni hüzünlü hissettirdin…$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "Ayrıca, düşünüyordum da…$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "Sanırım hepsi bu kadar.\pTekrar sohbet etmeliyiz! Güle güle!$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "Merhaba, ben BARD'ım.\nŞarkımı dinlemek ister misiniz?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "Of… Beni hüzünlü hissettirdin…$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "Ne kadar dokunaklı bir şarkı… Keşke\nbaşkaları için de çalabilsem…$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "Ne olmuş yani? Şarkımı beğendin mi?\pAma sözler konusunda pek mutlu\ndeğilim.\pBenim için yeni sözler yazmaya ne\ndersin?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "Oh… Beni hüzünlü hissettirdin…$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "Çok teşekkür ederim! Sizin için\nsöyleyeyim.$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "Şarkının böyle mi olmasını istiyordun?$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "Tamam! Tamam! Bu kadar o zaman. Bir\nsüre bu şarkıyı söyleyeceğim.$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "Hey, yo! Bana HIPSTER derler. Sana\nneyin moda olduğunu öğreteceğim.$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "Ama, hey, ben size zaten neyin moda\nolduğunu ve neler olduğunu öğrettim.\pBu güzel sözleri diğer insanlara da\nyaymak istiyorum.$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "Ama siz zaten neyin moda olduğu ve\nneler yaşandığı hakkında çok şey\lbiliyorsunuz.\pSana öğretecek yeni bir şeyim yok!$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "Hey, {STR_VAR_1} hakkında bir şey\nduydun mu?\pNe anlama geliyor? Şey… Babana ya da\nannene sor, tamam mı?$"
