.set LOCALID_HIDEOUT_GUARD, 5

JaggedPass_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, JaggedPass_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, JaggedPass_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, JaggedPass_OnLoad
	.byte 0

JaggedPass_OnResume:
	setstepcallback STEP_CB_ASH
	call_if_eq VAR_JAGGED_PASS_STATE, 0, JaggedPass_EventScript_CheckHasMagmaEmblem
	end

JaggedPass_EventScript_CheckHasMagmaEmblem::
	checkitem ITEM_MAGMA_EMBLEM
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_SetReadyToOpenHideout
	return

JaggedPass_EventScript_SetReadyToOpenHideout::
	setvar VAR_JAGGED_PASS_STATE, 1
	return

JaggedPass_OnTransition:
	call_if_eq VAR_JAGGED_PASS_ASH_WEATHER, 1, JaggedPass_EventScript_SetWeatherAsh
	end

JaggedPass_EventScript_SetWeatherAsh::
	setweather WEATHER_VOLCANIC_ASH
	doweather
	return

JaggedPass_OnLoad:
	goto_if_le VAR_JAGGED_PASS_STATE, 1, JaggedPass_EventScript_ConcealHideoutEntrance
	end

JaggedPass_EventScript_ConcealHideoutEntrance::
	setmetatile 16, 17, METATILE_Lavaridge_RockWall, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_RockWall, TRUE
	end

JaggedPass_EventScript_OpenMagmaHideout::
	lockall
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	msgbox JaggedPass_Text_BoulderShakingInResponseToEmblem, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 16  @ num shakes
	setvar VAR_0x8007, 3   @ shake delay
	special ShakeCamera
	waitstate
	playse SE_EFFECTIVE
	setmetatile 16, 17, METATILE_Lavaridge_CaveEntrance_Top, TRUE
	setmetatile 16, 18, METATILE_Lavaridge_CaveEntrance_Bottom, FALSE
	special DrawWholeMapView
	delay 30
	setvar VAR_JAGGED_PASS_STATE, 2
	waitse
	releaseall
	end

JaggedPass_EventScript_MagmaHideoutGuard::
	lockall
	goto_if_set FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS, JaggedPass_EventScript_GuardDefeated
	waitse
	playse SE_PIN
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GruntIntro, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_GRUNT_JAGGED_PASS, JaggedPass_Text_GruntDefeat
	setflag FLAG_BEAT_MAGMA_GRUNT_JAGGED_PASS
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_GuardDefeated::
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox JaggedPass_Text_GoWhereverYouWant, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HIDEOUT_GUARD, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

JaggedPass_EventScript_Eric::
	trainerbattle_single TRAINER_ERIC, JaggedPass_Text_EricIntro, JaggedPass_Text_EricDefeat
	msgbox JaggedPass_Text_EricPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Diana::
	trainerbattle_single TRAINER_DIANA_1, JaggedPass_Text_DianaIntro, JaggedPass_Text_DianaDefeat, JaggedPass_EventScript_RegisterDiana
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_DianaRematch
	msgbox JaggedPass_Text_DianaPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterDiana::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_DianaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_DIANA_1
	release
	end

JaggedPass_EventScript_DianaRematch::
	trainerbattle_rematch TRAINER_DIANA_1, JaggedPass_Text_DianaRematchIntro, JaggedPass_Text_DianaRematchDefeat
	msgbox JaggedPass_Text_DianaPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Ethan::
	trainerbattle_single TRAINER_ETHAN_1, JaggedPass_Text_EthanIntro, JaggedPass_Text_EthanDefeat, JaggedPass_EventScript_RegisterEthan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, JaggedPass_EventScript_EthanRematch
	msgbox JaggedPass_Text_EthanPostBattle, MSGBOX_DEFAULT
	release
	end

JaggedPass_EventScript_RegisterEthan::
	special PlayerFaceTrainerAfterBattle
	msgbox JaggedPass_Text_EthanRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ETHAN_1
	release
	end

JaggedPass_EventScript_EthanRematch::
	trainerbattle_rematch TRAINER_ETHAN_1, JaggedPass_Text_EthanRematchIntro, JaggedPass_Text_EthanRematchDefeat
	msgbox JaggedPass_Text_EthanPostRematch, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Julio::
	trainerbattle_single TRAINER_JULIO, JaggedPass_Text_JulioIntro, JaggedPass_Text_JulioDefeat
	msgbox JaggedPass_Text_JulioPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_EventScript_Autumn::
	trainerbattle_single TRAINER_AUTUMN, JaggedPass_Text_AutumnIntro, JaggedPass_Text_AutumnDefeat
	msgbox JaggedPass_Text_AutumnPostBattle, MSGBOX_AUTOCLOSE
	end

JaggedPass_Text_EricIntro:
	.string "CHİMNEY DAĞI…\nENGEBELİ YOL…\pİşte bir dağda hep istediğim şey\nbuydu.\pBu pürüzlü engebeler…\nRuhumu sarsıyor!$"

JaggedPass_Text_EricDefeat:
	.string "Kaybetmek acı verici!$"

JaggedPass_Text_EricPostBattle:
	.string "Evet, savaşta kaybettim.\pAma söz konusu dağ sevgisi olduğunda,\nben seni yenerim!$"

JaggedPass_Text_DianaIntro:
	.string "Burası sıradan bir yürüyüş yeri değil.\nPiknik için uygun değil.$"

JaggedPass_Text_DianaDefeat:
	.string "Aa, hayır!\nZemin çok engebeli…$"

JaggedPass_Text_DianaPostBattle:
	.string "Biliyor muydun?\pBazı insanlar bu korkunç engebeli\ngeçide bisikletleriyle tırmanabiliyor.$"

JaggedPass_Text_DianaRegister:
	.string "Buralara yine uğrar mısın?\nEğer dönersen, bir rövanş istiyorum.$"

JaggedPass_Text_DianaRematchIntro:
	.string "Piknikler nereye gidersen git\neğlencelidir. Tıpkı POKéMON'lar gibi!$"

JaggedPass_Text_DianaRematchDefeat:
	.string "Kaybettim çünkü zemin çok\nengebeliydi!$"

JaggedPass_Text_DianaPostRematch:
	.string "Kaybettiğimi unutacağım ve bu\nengebeli yürüyüşün tadını çıkaracağım.$"

JaggedPass_Text_EthanIntro:
	.string "ENGEBELİ YOL üzerinde yürümek zordur.\nEğitim için iyi bir yer.$"

JaggedPass_Text_EthanDefeat:
	.string "Savaş bitmiş bile.$"

JaggedPass_Text_EthanPostBattle:
	.string "Eğer bir AKRO BİSİKLETİM olsaydı,\nçıkıntılardan atlayabilirdim.$"

JaggedPass_Text_EthanRegister:
	.string "Bu engebeli araziye alıştığımda\nkazanacağımdan emin olabilirsin!\pBeni POKéNAV'ına kaydedebilir\nmisin?$"

JaggedPass_Text_EthanRematchIntro:
	.string "Bu araziye alıştım.\pArtık tırmanırken şarkı bile\nsöylüyorum.$"

JaggedPass_Text_EthanRematchDefeat:
	.string "Bu engebeli zeminde savaşmak hâlâ\nkolay değil…$"

JaggedPass_Text_EthanPostRematch:
	.string "MAUVILLE ŞEHRİ'ndeki RYDEL'den bir\nAKRO BİSİKLET almalıyım.$"

JaggedPass_Text_GruntIntro:
	.string "Hey! Ne yapıyorsun burada?\pBöyle bir yerde ne işim mi var?\nSeni ne ilgilendirir?$"

JaggedPass_Text_GruntDefeat:
	.string "Arrhh…\nKeşke saklandığım yerden çıkmasaydım.$"

JaggedPass_Text_GoWhereverYouWant:
	.string "Tamam, taa-mam!\nKabul ediyorum, sen güçlüsün!\pBenim için endişelenme.\nNereye istersen git!$"

JaggedPass_Text_BoulderShakingInResponseToEmblem:
	.string "Bu kaya, MAGMA SEMBOLÜNE tepki\nolarak sallanıyor!$"

JaggedPass_Text_JulioIntro:
	.string "Aiyeeh!\nHızlı hızlı engebeli yoldan aşağı\linmek çok korkutucu!$"

JaggedPass_Text_JulioDefeat:
	.string "Dağılıyormuşum gibi hissediyorum.$"

JaggedPass_Text_JulioPostBattle:
	.string "Bisikletim o kadar çok zıpladı ki belim\nağrımaya başladı.$"

JaggedPass_Text_AutumnIntro:
	.string "Bu tepeye her gün tırmanıyorum.\nGücüme güveniyorum!$"

JaggedPass_Text_AutumnDefeat:
	.string "Hmm…\nNeyi yanlış yaptım?$"

JaggedPass_Text_AutumnPostBattle:
	.string "Tepenin biraz yukarısındaki şu garip\nkaya çıkıntısı da ne?$"


