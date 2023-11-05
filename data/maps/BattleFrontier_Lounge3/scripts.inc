BattleFrontier_Lounge3_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols
	goto_if_le VAR_0x8004, 2, BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet
	end

BattleFrontier_Lounge3_EventScript_Bet5::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet10::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_Bet15::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount
	end

BattleFrontier_Lounge3_EventScript_PlaceBet::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet
	end

BattleFrontier_Lounge3_EventScript_FinishBet::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler::
	msgbox BattleFrontier_Lounge3_Text_Oh, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge
	goto BattleFrontier_Lounge3_EventScript_LostChallenge
	end

BattleFrontier_Lounge3_EventScript_WonChallenge::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge::
	msgbox BattleFrontier_Lounge3_Text_NotInterested, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge
	end

BattleFrontier_Lounge3_EventScript_Man::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FatMan::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere::
	.string "…Ne istiyorsunuz?\pBurada biraz meşgul olduğumuzu\ngörmüyor musun? İşiniz daha sonraya\lkalamaz mı?$"

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling::
	.string "…Ha? Bana sert bir eğitmen gibi\ngöründün.\pHeheh… Dinle, sana bir teklifim var.\pBurada küçük bir grubumuz var ve\nSAVAŞ SINIRI'nda olup bitenlerle\lküçük bir oyun oynuyoruz.\pKurallar gerçekten basit.\pİlk olarak, SAVAŞ CEPHESİ'ndeki\ntesislerden birini seçiyoruz.\pSonra, her birimiz o tesisin meydan\nokumasını üstlenen farklı bir EĞİTMEN\lseçiyoruz ve Savaş Puanlarımızla\lbahse giriyoruz.\pEn iyi rekora sahip EĞİTMEN üzerine\nbahse giren kişi havuzdaki tüm Savaş\lPuanlarını alır.\pKulağa basit geliyor, değil mi? Her\nneyse.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle::
	.string "Benim aradığım SAVAŞ KULESİ'nin TEKLİ\nSAVAŞ ODALARINA meydan okuyacak bir\lEĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble::
	.string "Benim aradığım SAVAŞ KULESİ'nin ÇİFT\nSAVAŞ ODALARINA meydan okuyacak bir\lEĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti::
	.string "Aradığım şey, SAVAŞ KULESİ'nin ÇOKLU\nSAVAŞ ODALARINA meydan okuyacak bir\lEĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle::
	.string "Aradığım şey SAVAŞ KUBBESİ'nin TEKLİ\nSAVAŞ Turnuvasına katılacak bir\lEĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble::
	.string "Aradığım şey SAVAŞ KUBBESİ'nin ÇİFTE\nSAVAŞ Turnuvasına katılacak bir\lEĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle::
	.string "Aradığım şey BATTLE FACTORY'nin\nTakas Tekli Turnuvasına\lkatılacak bir EĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN görmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble::
	.string "Aradığım şey BATTLE FACTORY'nin\nBattle Swap Double Turnuvasına\lkatılacak bir EĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN görmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle::
	.string "Aradığım şey, SAVAŞ SARAYI'nın TEKLİ\nSAVAŞ HALKALARINA meydan okuyacak\lbir EĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble::
	.string "Aradığım şey, SAVAŞ SARAYI'nın ÇİFT\nSAVAŞLI SALONLARINA meydan okuyacak\lbir EĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattleArena::
	.string "Aradığım şey SAVAŞ ARENASI'nın Set KO\nTurnuvasına katılacak bir EĞİTMEN.\pAncak şu ana kadar, bu kazanma\nkalitesine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePike::
	.string "Aradığım şey, SAVAŞ YILANI'nın Savaş\nSeçimi'ne katılacak bir EĞİTMEN.\pAncak şu ana kadar, bu kazanma\nniteliğine sahip bir EĞİTMEN\lgörmedim.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid::
	.string "Aradığım şey SAVAŞ PİRAMİDİ'nin Savaş\nGörevi'ne katılacak bir EĞİTMEN.\pAncak şu ana kadar, bu kazanma\nniteliğine sahip bir EĞİTMEN görmedim.$"

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe::
	.string "Senin de bundan faydalanmanı\nsağlayacağım. Ne dersin? Benim için bu\letkinliğe katılmaya ne dersin?$"

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints::
	.string "Pekala, bu mükemmel. Savaş puanlarının\nbir kısmını bana vermeye ne dersin?\pGüven bana, daha sonra sana\nminnettarlığımı göstereceğim.$"

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot::
	.string "Harika, harika! Beni ne kadar fark\nedebilirsin?$"

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints::
	.string "Oh, hayır, hayır, hayır! Yeterince\nSavaş Puanın yok!\pKeşke etrafta maymunluk yapıp\nherkesin zamanını boşa harcamasaydın!$"

BattleFrontier_Lounge3_Text_ThanksOffYouGo::
	.string "Heheh! Çok teşekkürler! Hadi bakalım!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle::
	.string "Hemen SAVAŞ KULESİ'nin TEKLİ SAVAŞ\nODALARINA gidin!\pKazanmanız gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble::
	.string "Hemen SAVAŞ KULESİ'nin ÇİFT SAVAŞ\nODALARI'na gidin!\pKazanmanız gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti::
	.string "SAVAŞ KULESİ'nin ÇOKLU SAVAŞ\nODALARINA hemen gidin!\pKazanmanız gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle::
	.string "SAVAŞ KUBBESİ'nin TEKLİ SAVAŞ\nTurnuvasına hemen katılın!\pBu kazanılması gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği size bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble::
	.string "SAVAŞ KUBBESİ'nin ÇİFTE SAVAŞ\nTurnuvasına hemen katılın!\pBu kazanılması gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği size bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle::
	.string "BATTLE FACTORY'nin Battle Swap Tekli\nTurnuvasına hemen katılın!\pKazanmanız gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği size bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble::
	.string "BATTLE FACTORY'nin Battle Swap İkili\nTurnuvasına hemen katılın!\pKazanmanız gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği size bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle::
	.string "Hemen SAVAŞ SARAYI'nın TEKLİ SAVAŞ\nSALONLARINA gidin!\pBu kazanılması gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble::
	.string "Hemen SAVAŞ SARAYI'nın ÇİFT SAVAŞ\nSALONU'na gidin!\pBu kazanılması gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattleArena::
	.string "SAVAŞ ARENASI'nın Set KO Turnuvasına\nhemen katılın!\pBu kazanılması gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattlePike::
	.string "Hemen SAVAŞ YILANI'nın Savaş Seçimi'ne\ngidin!\pBu kazanılması gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_GetToBattlePyramid::
	.string "Hemen SAVAŞ PİRAMİDİ'nin Savaş\nGörevi'ne gidin!\pKazanmanız gereken bir durum!\nŞansınızı kaçırmayın! İkimizin de\lgeleceği sana bağlı!$"

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints::
	.string "Oh, sensin… İyi deneme…\pBunu söylemekten nefret ediyorum ama\nSavaş Puanlarınızı geri veremem.\pSanırım bir dahaki sefere daha çok\nçalışmamız için bizi motive etmesine\lizin vermeliyiz!$"

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints::
	.string "Oh, evet! Merhaba, şampiyon!\pYapabileceğini biliyordum! Biliyordum!\nİkimiz de büyük kazananlarız!\pSavaş Puanlarınızı geri vereceğim ve\ntabii ki benden de biraz ekstra!$"

BattleFrontier_Lounge3_Text_ObtainedBattlePoints::
	.string "{PLAYER} {STR_VAR_1} Savaş Puanı\nelde etti.$"

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge::
	.string "Eğer başka bir meydan okumaya\nhazırsanız, lütfen beni düşünün!$"

BattleFrontier_Lounge3_Text_NotInterested::
	.string "İlgilenmiyor musun?! Şansını\ndenemekten bu kadar korkmamalısın!$"

BattleFrontier_Lounge3_Text_Oh::
	.string "Oh…$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer::
	.string "Yine yanlış EĞİTMENü destekledim!\pBelki de herkes gibi normal bir şekilde\nmücadele etmeliyim…$"

BattleFrontier_Lounge3_Text_TrainerGoodButRattled::
	.string "Şu eğitmen.\pİyi ama SAVAŞ KUBBESİ'da hayatta kalmak\niçin çok kolay sarsılıyor…$"

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne::
	.string "Hahah!\nBir kazanan gördüğümde anlarım!$"

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges::
	.string "Şu eğitmenler… Ne yapıyorlar?\nMücadelelere katılmaları gerekirdi.$"
