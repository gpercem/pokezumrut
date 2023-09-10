.set LOCALID_DOCK, 1

SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
	.string "Bu buraya, bu da şuraya giderse…\pO zaman bu şey nereye gidiyor?\nPeki ya şu zımbırtı?\pAaarh!\nBu işin içinden çıkamıyorum!$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
	.string "Hm? Merhaba, ben DOCK.\pKAPTAN STERN beni bir gemi tasarlamam\niçin görevlendirdi.\pAa! Şu şey…\nElindeki şey DEVON PAKEDİ mi?\pKAPTAN. STERN bir yere gitti.\nYapacak işleri olduğunu söyledi.\pGidip KAPTAN STERN'i bulabilir misin?\nMüzede olabileceğini tahmin ediyorum.$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
	.string "Gidip KAPTAN STERN'i bulabilir misin?\nSanırım müzeye gideceğini\lsöylemişti.$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
	.string "Gemi yapımı bir sanattır.\pBirçok şey sadece hesaplanarak\nçözülemez.\pDenizleri bilen bir emektarın\ntavsiyelerine ihtiyacım var.$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
	.string "Merhaba!\nBAY BRİNEY bize yardım etmek\niçin aramıza katıldı.\pBu tecrübeli denizci sayesinde, gemi\nyapımı hızlı bir şekilde ilerliyor.$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
	.string "Gemi nihayet hazır!\pYeni S.S. TİDAL gerçekten bir\nteknoloji harikası!\pAma içimden bir ses daha da iyisini\nyapabileceğimizi söylüyor.\pBilirsin, teknolojinin ilerleyişi asla\nsona ermez.$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "MR BRİNEY: Hey, {PLAYER}{KUN}!\nGörüşmeyeli uzun zaman oldu!\pEvet, seninle tanıştığından beri, bu\nyaşlı denizci kendini oynak hissediyor!\pBu yüzden DOCK'a gemi yapımında\nyardım etmeye karar verdim.\pEvet, ne de olsa gemiler çok fazla\ninsan taşıyabiliyor.\pAma bence DOCK gerçekten özel biri.\pOnun teknoloji becerisi ve benim\ntecrübemle, harika bir gemi inşa\ledebileceğimize eminim, evet!$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "Mevsimler, hava, ayın gökyüzündeki\nkonumu…\pBu gibi şeyler deniz seviyesinin\nyüksekliğini değiştirir.\pBu doğru!\nDeniz canlı gibidir!$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "Beni çok kolay deniz tutar.\nBu yüzden buradan yardım ediyorum.$"


