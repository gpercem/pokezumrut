MauvilleCity_BikeShop_MapScripts::
	.byte 0

MauvilleCity_BikeShop_EventScript_Rydel::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, MauvilleCity_BikeShop_EventScript_AskSwitchBikes
	goto_if_set FLAG_DECLINED_BIKE, MauvilleCity_BikeShop_EventScript_SkipGreeting
	msgbox MauvilleCity_BikeShop_Text_RydelGreeting, MSGBOX_DEFAULT
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_SkipGreeting::
	msgbox MauvilleCity_BikeShop_Text_DidYouComeFromFarAway, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_YesFar
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_NotFar
	end

MauvilleCity_BikeShop_EventScript_ChooseBike::
	message MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne
	waitmessage
	multichoice 21, 8, MULTI_BIKE, TRUE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_GetMachBike
	case 1, MauvilleCity_BikeShop_EventScript_GetAcroBike
	end

MauvilleCity_BikeShop_EventScript_NotFar::
	setflag FLAG_DECLINED_BIKE
	msgbox MauvilleCity_BikeShop_Text_GuessYouDontNeedBike, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_YesFar::
	setflag FLAG_RECEIVED_BIKE
	goto MauvilleCity_BikeShop_EventScript_ChooseBike
	end

MauvilleCity_BikeShop_EventScript_GetMachBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseMachBike, MSGBOX_DEFAULT
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_GetAcroBike::
	msgbox MauvilleCity_BikeShop_Text_ChoseAcroBike, MSGBOX_DEFAULT
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes, MSGBOX_DEFAULT
	special SwapRegisteredBike
	release
	end

MauvilleCity_BikeShop_EventScript_AskSwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_WantToSwitchBikes, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_BikeShop_EventScript_SwitchBikes
	goto_if_eq VAR_RESULT, NO, MauvilleCity_BikeShop_EventScript_KeepBike
	end

@ If the player does not have a bike on them Rydel assumes its stored in the PC
MauvilleCity_BikeShop_EventScript_SwitchBikes::
	msgbox MauvilleCity_BikeShop_Text_IllSwitchBikes, MSGBOX_DEFAULT
	checkitem ITEM_ACRO_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchAcroForMach
	checkitem ITEM_MACH_BIKE
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_BikeShop_EventScript_SwitchMachForAcro
	msgbox MauvilleCity_BikeShop_Text_OhYourBikeIsInPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_KeepBike::
	msgbox MauvilleCity_BikeShop_Text_HappyYouLikeIt, MSGBOX_DEFAULT
	release
	end

MauvilleCity_BikeShop_EventScript_SwitchAcroForMach::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedAcroForMach, MSGBOX_DEFAULT
	removeitem ITEM_ACRO_BIKE
	giveitem ITEM_MACH_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_SwitchMachForAcro::
	incrementgamestat GAME_STAT_TRADED_BIKES
	msgbox MauvilleCity_BikeShop_Text_ExchangedMachForAcro, MSGBOX_DEFAULT
	removeitem ITEM_MACH_BIKE
	giveitem ITEM_ACRO_BIKE
	goto MauvilleCity_BikeShop_EventScript_ComeBackToSwitchBikes
	end

MauvilleCity_BikeShop_EventScript_Assistant::
	msgbox MauvilleCity_BikeShop_Text_HandbooksAreInBack, MSGBOX_NPC
	end

MauvilleCity_BikeShop_EventScript_MachBikeHandbook::
	message MauvilleCity_BikeShop_Text_MachHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage::
	multichoice 0, 0, MULTI_MACH_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_HowToRide
	case 1, MauvilleCity_BikeShop_EventScript_HowToTurn
	case 2, MauvilleCity_BikeShop_EventScript_SandySlopes
	case 3, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitMachHandbook
	end

MauvilleCity_BikeShop_EventScript_HowToRide::
	message MauvilleCity_BikeShop_Text_HowToRideMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_HowToTurn::
	message MauvilleCity_BikeShop_Text_HowToTurnMachBike
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_SandySlopes::
	message MauvilleCity_BikeShop_Text_SandySlopes
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseMachHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitMachHandbook::
	release
	end

MauvilleCity_BikeShop_EventScript_AcroBikeHandbook::
	message MauvilleCity_BikeShop_Text_AcroHandbookWhichPage
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage::
	multichoice 0, 0, MULTI_ACRO_BIKE_INFO, FALSE
	switch VAR_RESULT
	case 0, MauvilleCity_BikeShop_EventScript_Wheelies
	case 1, MauvilleCity_BikeShop_EventScript_BunnyHops
	case 2, MauvilleCity_BikeShop_EventScript_Jumps
	case 3, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	case MULTI_B_PRESSED, MauvilleCity_BikeShop_EventScript_ExitAcroHandbook
	end

MauvilleCity_BikeShop_EventScript_Wheelies::
	message MauvilleCity_BikeShop_Text_Wheelies
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_BunnyHops::
	message MauvilleCity_BikeShop_Text_BunnyHops
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_Jumps::
	message MauvilleCity_BikeShop_Text_Jumps
	waitmessage
	goto MauvilleCity_BikeShop_EventScript_ChooseAcroHandbookPage
	end

MauvilleCity_BikeShop_EventScript_ExitAcroHandbook::
	release
	end

MauvilleCity_BikeShop_Text_RydelGreeting:
	.string "Vay, vay, burada kimler varmış?\nÇok enerjik bir müşteri!\pBen mi? Bana RYDEL diyebilirsin.\nBen bu bisiklet dükkanının sahibiyim.$"

MauvilleCity_BikeShop_Text_DidYouComeFromFarAway:
	.string "KOŞU AYAKKABILARIN…\nÇok pisler.\pÇok uzaklardan mı geldin?$"

MauvilleCity_BikeShop_Text_GuessYouDontNeedBike:
	.string "Öyle mi?\pO zaman sanırım bisikletlerime\nihtiyacın yok.$"

MauvilleCity_BikeShop_Text_ExplainBikesChooseWhichOne:
	.string "RYDEL: Hm, hm…\n… … … …\pBu kadar yolu LİTTLEROOT'tan\ngeldiğini mi söylüyorsun?\pAman Tanrım!\nBu gülünç derecede uzak!\pBenim bisikletlerimden biri sende\nolsaydı rüzgar esintisini hissederek\lher yere kolayca gidebilirdin!\pBak ne diyeceğim!\nSana bir BİSİKLET vereceğim!\pAma bir saniye bekle!\pSana iki BİSİKLET çeşidim olduğunu\nsöylemeyi unuttum!\pBunlar HIZ ve AKRO BİSİKLETİ!\pHIZ BİSİKLETİ, rüzgarı vücutlarıyla\nhissetmek isteyen bisikletçiler\liçindir!\pAKRO BİSİKLET ise teknik sürüşleri\ntercih edenler içindir!\pBen cömert biriyimdir, bu yüzden\nhangisini istersen alabilirsin!\pHangisini istersin?$"

MauvilleCity_BikeShop_Text_ChoseMachBike:
	.string "{PLAYER} HIZ BİSİKLETİ seçti.$"

MauvilleCity_BikeShop_Text_ChoseAcroBike:
	.string "{PLAYER} AKRO BİSİKLETİ seçti.$"

MauvilleCity_BikeShop_Text_ComeBackToSwitchBikes:
	.string "Eğer bisiklet değiştirmek istersen, gel\nbeni gör!$"

MauvilleCity_BikeShop_Text_WantToSwitchBikes:
	.string "Bisikletleri değiştirmeyi mi\ndüşünüyordun?$"

MauvilleCity_BikeShop_Text_IllSwitchBikes:
	.string "Tamam, sorun değil! Senin için\nbisikletleri değiştireceğim!$"

MauvilleCity_BikeShop_Text_ExchangedMachForAcro:
	.string "{PLAYER}, HIZ BİSİKLETİNİ bir\nAKRO BİSİKLET ile değiştirdi.$"

MauvilleCity_BikeShop_Text_ExchangedAcroForMach:
	.string "{PLAYER}, AKRO BİSİKLETİNİ bir\nHIZ BİSİKLETİ ile değiştirdi.$"

MauvilleCity_BikeShop_Text_HappyYouLikeIt:
	.string "Güzel, güzel!\nBeğenmene sevindim!$"

MauvilleCity_BikeShop_Text_OhYourBikeIsInPC:
	.string "Sana verdiğim bisiklete ne oldu?\pAnladım, bilgisayarını kullanarak\nsaklamışsın.\pO zaman bilgisayarın deposundan çıkar,\nben de seve seve değiştireyim!\pMaceranda rüzgar hep arkanda olsun!$"

MauvilleCity_BikeShop_Text_HandbooksAreInBack:
	.string "Burada çalışırken BİSİKLETLER\nhakkında yeni şeyler öğreniyorum.\pBİSİKLET'ini nasıl süreceğin\nkonusunda tavsiyeye ihtiyacın\lvarsa, arkada birkaç el kitabı var.$"

MauvilleCity_BikeShop_Text_MachHandbookWhichPage:
	.string "Bu HIZ BİSİKLETİ hakkında bir el\nkitabı.\pHangi sayfayı okumak istersiniz?$"

MauvilleCity_BikeShop_Text_HowToRideMachBike:
	.string "Bir BİSİKLET kontrol tuşlarının\nyönünde hareket eder.\pYavaş başlayıp sonra hızlanacaktır.\pDurdurmak için kontrol tuşlarını\nbırakın. BİSİKLET duracaktır.\pFarklı bir sayfa okumak ister misiniz?$"

MauvilleCity_BikeShop_Text_HowToTurnMachBike:
	.string "HIZ BİSİKLETİ hızlıdır, ancak çok\nçabuk duramaz.\pVirajları almak biraz zor olabilir.\pVirajdan önce kontrol tuşlarını\nbırakın ve yavaşlayın.\pFarklı bir sayfa okumak ister misiniz?$"

MauvilleCity_BikeShop_Text_SandySlopes:
	.string "HOENN bölgesinde küçük kumlu\nyamaçlar bulunmaktadır.\pİnce kumlar tırmanmayı imkansız\nhale getirir.\pAncak bir HIZ BİSİKLETİNİZ varsa\nkumlu yamaçtan geçebilirsiniz.\pFarklı bir sayfa okumak ister misiniz?$"

MauvilleCity_BikeShop_Text_AcroHandbookWhichPage:
	.string "Bu AKRO BİSİKLET hakkında bir el\nkitabı.\pHangi sayfayı okumak istersiniz?$"

MauvilleCity_BikeShop_Text_Wheelies:
	.string "Sürüş sırasında B Düğmesine basın ve\nön tekerlek yukarı kalksın.\pKontrol tuşlarını kullanarak ön teker\nyukarıdayken sürebilirsiniz.\pBu tekniğe ön kaldırma denir.\pFarklı bir sayfa okumak ister misiniz?$"

MauvilleCity_BikeShop_Text_BunnyHops:
	.string "B Düğmesine basılı tutarak,\nBİSİKLETİNİZ yerinde zıplayabilir.\pBu tekniğe tavşan zıplaması denir.\pZıplarken de binebilirsiniz.\pFarklı bir sayfa okumak ister misiniz?$"

MauvilleCity_BikeShop_Text_Jumps:
	.string "Zıplamak için B Düğmesine ve kontrol\ntuşlarına aynı anda basın.\pYana doğru zıplamak için kontrol\ntuşunu yana doğru bastırın.\pZıplarken BİSİKLET'in yön\ndeğiştirmesini sağlamak için geriye\ldoğru basın.\pFarklı bir sayfa okumak ister misiniz?$"


