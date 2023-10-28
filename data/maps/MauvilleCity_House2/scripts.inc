MauvilleCity_House2_MapScripts::
	.byte 0

MauvilleCity_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_House2_EventScript_AcceptTrade
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade::
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	removeitem ITEM_HARBOR_MAIL
	giveitem ITEM_COIN_CASE
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade::
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport:
	.string "Eğer bir BİSİKLETİM olsaydı, alışveriş\niçin SLATEPORT'a bisikletle gidip\lgelirdim.\pSLATEPORT'taki POKéMON MART'tan\nLİMAN MEKTUBU satın alabilirdim…$"

MauvilleCity_House2_Text_TradeHarborMailForCoinCase:
	.string "Aa! LİMAN MEKTUBUN mu var?\nOnu bir JETON KUTUSU ile takas\leder misin?$"

MauvilleCity_House2_Text_IllTradeYouCoinCase:
	.string "Çok mutlu oldum!\nTamam, seninle bir jeton kasası\ntakas edeceğim!$"

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner:
	.string "Bu JETON KUTUSUNU, OYUN KÖŞESİ'nde\nkullanılabilirsin.$"

MauvilleCity_House2_Text_ThatsDisappointing:
	.string "Ne hayal kırıklığı ama.\pOYUN KÖŞESİ'ne girmek için JETON\nKUTUSU gerektiğini unutma.$"



