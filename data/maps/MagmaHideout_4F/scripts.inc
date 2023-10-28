.set LOCALID_GROUDON, 1
.set LOCALID_GRUNT_1, 2
.set LOCALID_GRUNT_2, 3
.set LOCALID_GRUNT_3, 4
.set LOCALID_TABITHA, 5
.set LOCALID_MAXIE, 6
.set LOCALID_GROUDON_SLEEPING, 7

MagmaHideout_4F_MapScripts::
	.byte 0

MagmaHideout_4F_EventScript_Maxie::
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, FALSE
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 150
	removeobject LOCALID_GROUDON_SLEEPING
	addobject LOCALID_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_GROUDON
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setvar VAR_SLATEPORT_CITY_STATE, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_TABITHA
	setflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach:
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

MagmaHideout_4F_Movement_GroudonExit:
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround:
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha::
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro:
	.string "Ben de GROUDON'u görmek istiyorum ama\nkuyruğunu bile görmeme izin\lvermiyorlar…\pBu beni gerçekten hayal kırıklığına\nuğrattı.\pOlamaz! GROUDON hakkında boşboğazlık\nettim!$"

MagmaHideout_4F_Text_Grunt11Defeat:
	.string "Sanırım stresliyken kazanmak\nimkansız oluyor…$"

MagmaHideout_4F_Text_Grunt11PostBattle:
	.string "Acaba GROUDON'un kuyruğu var mı?$"

MagmaHideout_4F_Text_Grunt12Intro:
	.string "Fuhahaha! Çok yakında! Çok yakında!\nBüyük hedefimize ulaşacağız!$"

MagmaHideout_4F_Text_Grunt12Defeat:
	.string "Grrr… Buraya kadar geldim, sonucu\nbu mu?$"

MagmaHideout_4F_Text_Grunt12PostBattle:
	.string "MAXIE, efendim!\nDavetsiz bir misafir size doğru\lgeliyor!$"

MagmaHideout_4F_Text_Grunt13Intro:
	.string "Daha işim bitmedi!\nBeni kolayca geçemezsin!$"

MagmaHideout_4F_Text_Grunt13Defeat:
	.string "Beni devirmek o kadar kolay mıydı?$"

MagmaHideout_4F_Text_Grunt13PostBattle:
	.string "Hadi, bir maç daha.$"

MagmaHideout_4F_Text_TabithaIntro:
	.string "Hehehe! Buraya kadar geldiğine\ngöre söylesem iyi olur!\pBu doğru!\nİleride, GROUDON uyuyor!\pMAXIE birkaç saniye önce GROUDON'a\ngitti!\pÇok yakında uyanacak!\nHehehe! Hehehe!$"

MagmaHideout_4F_Text_TabithaDefeat:
	.string "Tekrar yenildim…\nHehe…$"

MagmaHideout_4F_Text_TabithaPostBattle:
	.string "…Ve sen benimle vakit kaybederken,\nMAXIE GROUDON'u uyandırmıştır bile…$"

MagmaHideout_4F_Text_MaxieAwakenGroudon:
	.string "MAXİE: GROUDON.\pHiçbir şey seni magma ile yıkanmış\nuykundan uyandıramaz.\pAradığın şey bu MAVİ KÜRE.\nÖyle değil mi?\pSana MAVİ KÜREYİ getirdim.\nParıltısı seni uyandırsın!\pVe göster…\nGöster bana tüm gücünü!$"

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong:
	.string "MAXİE: GROUDON!\nSorun ne?\pAnahtar MAVİ KÜRE değil miydi?\pGROUDON! Nereye gittin…$"

MagmaHideout_4F_Text_MaxieOhItWasYou:
	.string "MAXİE: Demek sendin.\pSeni orada burada davetsizce\ndolaşırken görmüştüm.\pŞimdi anladım!\nUcuz bir numara çekmiş olmalısın!$"

MagmaHideout_4F_Text_MaxieDefeat:
	.string "POKéMON'ları idare etmekte seni bu\nkadar usta yapan nedir?$"

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon:
	.string "GROUDON'un kaçmasının bir nedeni\nolmalı.\pBunu söylemeye çalışıyorsun, değil mi?\p… … … … … …\n… … … … … …\pBunu bilmediğimi mi sanıyorsun?\pGROUDON gittiğine göre, artık bu lanet\nyanardağa gerek yok.\pGROUDON'un peşinden gidiyorum, bu\nyüzden burada yollarımız\layrılıyor!$"
