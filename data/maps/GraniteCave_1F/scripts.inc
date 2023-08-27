GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM05, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM05
	setflag FLAG_RECEIVED_HM05
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Hey, sen.\nİlerisi çok karanlık olacak.\pEtrafı görmen de zorlaşacak.\pDaha demin buradan biri geçti…\nSTEVEN'dı sanırım.\pFLAŞ'ı nasıl kullanacağını biliyordu,\nbu yüzden iyi olmalı, ama…\pBiz YÜRÜYÜŞÇÜLER için, karşılaştığımız\nkişilere yardım etmek bizim\lözelliğimizdir.\pBuyur, bunu sana vereyim.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "Gizli hareket FLAŞ'ı bir POKéMON'a\nöğret ve kullan.\pMağaraların zifiri karanlığını bile\naydınlatır.\pAncak bunu kullanmak için DEWFORD'un\nPOKéMON salonundaki SALON ROZETİ'ne\lihtiyacın var.$"


