.set LOCALID_VIVI, 1
.set LOCALID_VICTOR, 2
.set LOCALID_VICTORIA, 3
.set LOCALID_VICKY, 4

Route111_WinstrateFamilysHouse_MapScripts::
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace::
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky::
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo::
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection::
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou:
	.string "POKéMON'u bu kadar ustaca kullanan\ngördüğüm ilk eğitmen sensin.\pAma sana söylemeliyim ki oğlum senden\ndaha güçlü.\pPOKéMON LİGİ mücadelesine bile katıldı,\nhaberin olsun.$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace:
	.string "Bu MAÇO BİLEKLİK'i antrenmanlarda\nPOKéMON'umuzu daha etkili bir şekilde\lgüçlendirmek için kullanıyoruz.\pBurada hepimizi yendiğine göre,\nihtiyacın var mı bilmiyorum ama MAÇO\lBİLEKLİK'imizi almanı istiyoruz.$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles:
	.string "Söz konusu POKéMON savaşları\nolduğunda, oldukça tutkulu olma\leğilimindeyiz.$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers:
	.string "Annem babamdan daha güçlü.\pBen annemden daha güçlüyüm.\pVe büyükannem benden daha güçlü!\pAma ağabeyim büyükannemden bile daha\ngüçlü.$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong:
	.string "Güçlü olduğunuza şüphe yok.\pAma torunumla dövüşecek olsaydın,\nhayal kırıklığı içinde ağlardın.\pO, ailemizin tanıdığı tüm\neğitmenlerden çok daha güçlü.\pŞimdiye kadar POKéMON LİGİ\nŞAMPİYONU'na meydan okumuş olmalı.\pTorunumu tanıyorsam, o ŞAMPİYON olur!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort:
	.string "Torunum şu anda POKéMON LİGİ\nŞAMPİYONU'na meydan okuyor olmalı.\pTorunumu tanıyorsam, o ŞAMPİYON olur!$"


