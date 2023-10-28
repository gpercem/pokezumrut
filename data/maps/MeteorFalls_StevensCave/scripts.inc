.set LOCALID_STEVEN, 1

MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "STEVEN: Vay canına, {PLAYER}{KUN}.\nBeni bulabilmene şaşırdım.\pBeni kayalarla uğraşan bir deli\nolarak mı görüyorsun?\pHayır, göründüğü gibi değil.\pSOOTOPOLİS UZAY MERKEZİ'nde yan yana\nsavaştık.\pNe kadar iyi olduğumu biliyor\nolmalısın.\pPekala, {PLAYER}{KUN}, eğer ciddi bir\nmeydan okuma olacaksa, benden\lacımamı bekleme!$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "Senin…\nBu kadar güçlü olduğunu bilmiyordum.$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "STEVEN: Düşünüyorum da, DEWFORD'daki\nGRANİT MAĞARASI'nda yollarımız\lkesiştiğinden beri içimde böyle bir his\lvardı.\pEninde sonunda ŞAMPİYON olacağını\ndüşünmüştüm.\pTahminlerim genelde doğru çıkar.\pPeki bundan sonra nereye gideceksin?\p… … … … … …\n… … … … … …\pFufufu, bunu sana ben bile\nsöyleyemezdim.$"


