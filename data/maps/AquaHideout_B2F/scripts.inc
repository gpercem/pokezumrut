.set LOCALID_MATT, 1
.set LOCALID_SUBMARINE, 4

AquaHideout_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AquaHideout_B2F_OnTransition
	.byte 0

AquaHideout_B2F_OnTransition:
	call_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, AquaHideout_B2F_EventScript_PreventMattNoticing
	end

AquaHideout_B2F_EventScript_PreventMattNoticing::
	setvar VAR_TEMP_1, 1
	return

AquaHideout_B2F_EventScript_MattNoticePlayer::
	lockall
	setvar VAR_0x8008, LOCALID_MATT
	playse SE_PIN
	applymovement VAR_0x8008, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_TEMP_1, 1
	releaseall
	end

AquaHideout_B2F_EventScript_Matt::
	trainerbattle_single TRAINER_MATT, AquaHideout_B2F_Text_MattIntro, AquaHideout_B2F_Text_MattDefeat, AquaHideout_B2F_EventScript_SubmarineEscape
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_SubmarineEscape::
	setvar VAR_0x8008, LOCALID_MATT
	setvar VAR_0x8009, LOCALID_SUBMARINE
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_OurBossGotThroughHisPreparations, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8008, Common_Movement_WalkInPlaceFasterLeft
	applymovement VAR_0x8009, AquaHideout_B2F_Movement_SumbarineDepartLeft
	waitmovement 0
	removeobject VAR_0x8009
	delay 20
	applymovement VAR_0x8008, Common_Movement_FacePlayer
	waitmovement 0
	msgbox AquaHideout_B2F_Text_MattPostBattle, MSGBOX_DEFAULT
	setflag FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE
	setflag FLAG_HIDE_LILYCOVE_CITY_AQUA_GRUNTS
	release
	end

AquaHideout_B2F_Movement_SumbarineDepartLeft:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@ Unused
AquaHideout_B2F_Movement_SumbarineDepartRight:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

AquaHideout_B2F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_4, AquaHideout_B2F_Text_Grunt4Intro, AquaHideout_B2F_Text_Grunt4Defeat, AquaHideout_B2F_EventScript_Grunt4Defeated
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt4Defeated::
	msgbox AquaHideout_B2F_Text_Grunt4PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_B2F_EventScript_Grunt6::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_6, AquaHideout_B2F_Text_Grunt6Intro, AquaHideout_B2F_Text_Grunt6Defeat
	msgbox AquaHideout_B2F_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_EventScript_Grunt8::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_8, AquaHideout_B2F_Text_Grunt8Intro, AquaHideout_B2F_Text_Grunt8Defeat
	msgbox AquaHideout_B2F_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_B2F_Text_MattIntro:
	.string "Hehehe…\pÇoktan geldin, değil mi?\nSeni hafife almışız!\pAma bu kadar!\pŞimdiye kadar gördüğün haydutlardan\nnçok daha iyiyim.\pZaman kazanmaya çalışmıyorum.\nSeni un ufak edeceğim!$"

AquaHideout_B2F_Text_MattDefeat:
	.string "Hehehe…\nBen de kaybettim…$"

AquaHideout_B2F_Text_OurBossGotThroughHisPreparations:
	.string "Hehehe!\pBen seninle uğraşırken, patronumuz\nhazırlıklarını tamamladı bile!$"

AquaHideout_B2F_Text_MattPostBattle:
	.string "Hehehe!\pPatronumuz çoktan denizin altındaki\nbir mağaraya doğru yola çıktı!\pEğer peşinden gideceksen,\nLILYCOVE'un ötesindeki büyük, geniş\ldenizi araştırsan iyi olur.\pAma o zamana kadar bulabilecek misin?\nHehehe!$"

AquaHideout_B2F_Text_Grunt4Intro:
	.string "Vahahah, beklemekten yoruldum!\nBana da bir savaş borçlusun!$"

AquaHideout_B2F_Text_Grunt4Defeat:
	.string "Beklemekten bıktım…\nİyice sersemledim…$"

AquaHideout_B2F_Text_Grunt4PostBattle:
	.string "PATRON…\nYeterince iyi miydim?$"

AquaHideout_B2F_Text_Grunt6Intro:
	.string "Işınlanma panelleri, sığınağın\ngururu ve neşesi!\pNerede olduğunu bilmiyorsun, değil mi?\pDüşmanı korkut ve yor, sonra\nbombayı patlat! Planımız bu!$"

AquaHideout_B2F_Text_Grunt6Defeat:
	.string "Neyin var senin?\nHiç yorgun görünmüyorsun!$"

AquaHideout_B2F_Text_Grunt6PostBattle:
	.string "Aklıma gelmişken…\nUSTA TOPU'nu nereye koyduğumu\lhatırlayamıyorum.\pEğer onu bulamazsam patron\nbeni azarlayacak…$"

AquaHideout_B2F_Text_Grunt8Intro:
	.string "AQUA TAKIMI'na katıldığımda, öğrenmem\ngereken ilk şey bu panellerin\lnasıl çalıştığı oldu.$"

AquaHideout_B2F_Text_Grunt8Defeat:
	.string "Işınlanma panellerini düşünmekle\nçok meşguldüm.$"

AquaHideout_B2F_Text_Grunt8PostBattle:
	.string "Nasıl daha etkili savaşabileceğimi\nöğrenmem gerekecek…$"
