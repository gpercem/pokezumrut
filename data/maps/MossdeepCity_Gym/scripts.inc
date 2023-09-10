MossdeepCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_Gym_OnLoad
	.byte 0

@ NOTE: Mossdeep Gym was redesigned between R/S and E. Leftover (and now functionally unused) scripts are commented below

@ All the below checks are leftover from RS. FLAG_MOSSDEEP_GYM_SWITCH_X is never set
MossdeepCity_Gym_OnLoad:
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_SetSwitch1Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_CheckSwitch2::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_SetSwitch2Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_CheckSwitch3::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_SetSwitch3Metatiles
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_CheckSwitch4::
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_SetSwitch4Metatiles
	end

@ All the below set metatile scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_SetSwitch1Metatiles::
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch2
	end

MossdeepCity_Gym_EventScript_SetSwitch2Metatiles::
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch3
	end

MossdeepCity_Gym_EventScript_SetSwitch3Metatiles::
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_CheckSwitch4
	end

MossdeepCity_Gym_EventScript_SetSwitch4Metatiles::
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	end

MossdeepCity_Gym_EventScript_TateAndLiza::
	trainerbattle_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaIntro, MossdeepCity_Gym_Text_TateAndLizaDefeat, MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons, MossdeepCity_Gym_EventScript_TateAndLizaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MossdeepCity_Gym_EventScript_TateAndLizaRematch
	goto_if_unset FLAG_RECEIVED_TM04, MossdeepCity_Gym_EventScript_GiveCalmMind2
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_TateAndLizaDefeated::
	message MossdeepCity_Gym_Text_ReceivedMindBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_MOSSDEEP_GYM
	setflag FLAG_BADGE07_GET
	setflag FLAG_HIDE_AQUA_HIDEOUT_GRUNTS
	clearflag FLAG_HIDE_SLATEPORT_CITY_STERNS_SHIPYARD_MR_BRINEY
	clearflag FLAG_UNKNOWN_0x393
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_SLATEPORT_CITY_HARBOR_PATRONS
	clearflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_TEAM_MAGMA
	clearflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_2F_STEVEN
	setvar VAR_MOSSDEEP_CITY_STATE, 1
	setflag FLAG_HIDE_MOSSDEEP_CITY_SPACE_CENTER_1F_STEVEN
	setvar VAR_MOSSDEEP_SPACE_CENTER_STATE, 1
	call MossdeepCity_Gym_EventScript_GiveCalmMind
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox MossdeepCity_Gym_Text_RegisteredTateAndLiza, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_TATE_AND_LIZA_MATCH_CALL
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind2::
	giveitem ITEM_TM04
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM04
	release
	end

MossdeepCity_Gym_EventScript_GiveCalmMind::
	giveitem ITEM_TM04
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox MossdeepCity_Gym_Text_ExplainCalmMind, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM04
	return

MossdeepCity_Gym_EventScript_TateAndLizaRematch::
	trainerbattle_rematch_double TRAINER_TATE_AND_LIZA_1, MossdeepCity_Gym_Text_TateAndLizaPreRematch, MossdeepCity_Gym_Text_TateAndLizaRematchDefeat, MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons
	msgbox MossdeepCity_Gym_Text_TateAndLizaPostRematch, MSGBOX_AUTOCLOSE
	end

@ All the below switch scripts are leftover from RS and are functionally unused
MossdeepCity_Gym_EventScript_Switch1::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_1, MossdeepCity_Gym_EventScript_ClearSwitch1
	setflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed::
	special DrawWholeMapView
	playse SE_CLICK
	releaseall
	end

MossdeepCity_Gym_EventScript_ClearSwitch1::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 5, 5, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 2, 7, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch2::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_2, MossdeepCity_Gym_EventScript_ClearSwitch2
	setflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch2::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 8, 14, METATILE_RSMossdeepGym_RedArrow_Down, FALSE
	setmetatile 8, 10, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch3::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_3, MossdeepCity_Gym_EventScript_ClearSwitch3
	setflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Left, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch3::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 15, 17, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 17, 15, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_Switch4::
	lockall
	goto_if_set FLAG_MOSSDEEP_GYM_SWITCH_4, MossdeepCity_Gym_EventScript_ClearSwitch4
	setflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Up, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Down, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_ClearSwitch4::
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Gym_Movement_WaitAfterSwitchUse
	waitmovement 0
	setmetatile 1, 23, METATILE_RSMossdeepGym_RedArrow_Right, FALSE
	setmetatile 5, 24, METATILE_RSMossdeepGym_Switch_Up, TRUE
	goto MossdeepCity_Gym_EventScript_DrawMapAfterSwitchUsed
	end

MossdeepCity_Gym_EventScript_WarpToEntrance::
	lockall
	warpmossdeepgym MAP_MOSSDEEP_CITY_GYM, 7, 30
	waitstate
	releaseall
	end

MossdeepCity_Gym_EventScript_Preston::
	trainerbattle_single TRAINER_PRESTON, MossdeepCity_Gym_Text_PrestonIntro, MossdeepCity_Gym_Text_PrestonDefeat
	msgbox MossdeepCity_Gym_Text_PrestonPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Virgil::
	trainerbattle_single TRAINER_VIRGIL, MossdeepCity_Gym_Text_VirgilIntro, MossdeepCity_Gym_Text_VirgilDefeat
	msgbox MossdeepCity_Gym_Text_VirgilPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE, MossdeepCity_Gym_Text_BlakeIntro, MossdeepCity_Gym_Text_BlakeDefeat
	msgbox MossdeepCity_Gym_Text_BlakePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Hannah::
	trainerbattle_single TRAINER_HANNAH, MossdeepCity_Gym_Text_HannahIntro, MossdeepCity_Gym_Text_HannahDefeat
	msgbox MossdeepCity_Gym_Text_HannahPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Samantha::
	trainerbattle_single TRAINER_SAMANTHA, MossdeepCity_Gym_Text_SamanthaIntro, MossdeepCity_Gym_Text_SamanthaDefeat
	msgbox MossdeepCity_Gym_Text_SamanthaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Maura::
	trainerbattle_single TRAINER_MAURA, MossdeepCity_Gym_Text_MauraIntro, MossdeepCity_Gym_Text_MauraDefeat
	msgbox MossdeepCity_Gym_Text_MauraPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Sylvia::
	trainerbattle_single TRAINER_SYLVIA, MossdeepCity_Gym_Text_SylviaIntro, MossdeepCity_Gym_Text_SylviaDefeat
	msgbox MossdeepCity_Gym_Text_SylviaPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nate::
	trainerbattle_single TRAINER_NATE, MossdeepCity_Gym_Text_NateIntro, MossdeepCity_Gym_Text_NateDefeat
	msgbox MossdeepCity_Gym_Text_NatePostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Macey::
	trainerbattle_single TRAINER_MACEY, MossdeepCity_Gym_Text_MaceyIntro, MossdeepCity_Gym_Text_MaceyDefeat
	msgbox MossdeepCity_Gym_Text_MaceyPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Clifford::
	trainerbattle_single TRAINER_CLIFFORD, MossdeepCity_Gym_Text_CliffordIntro, MossdeepCity_Gym_Text_CliffordDefeat
	msgbox MossdeepCity_Gym_Text_CliffordPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Nicholas::
	trainerbattle_single TRAINER_NICHOLAS, MossdeepCity_Gym_Text_NicholasIntro, MossdeepCity_Gym_Text_NicholasDefeat
	msgbox MossdeepCity_Gym_Text_NicholasPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_Kathleen::
	trainerbattle_single TRAINER_KATHLEEN, MossdeepCity_Gym_Text_KathleenIntro, MossdeepCity_Gym_Text_KathleenDefeat
	msgbox MossdeepCity_Gym_Text_KathleenPostBattle, MSGBOX_AUTOCLOSE
	end

MossdeepCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_MOSSDEEP_GYM, MossdeepCity_Gym_EventScript_GymGuidePostVictory
	msgbox MossdeepCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

MossdeepCity_Gym_EventScript_GymGuidePostVictory::
	msgbox MossdeepCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

@ Leftover from RS, functionally unused
MossdeepCity_Gym_Movement_WaitAfterSwitchUse:
	delay_16
	delay_16
	step_end

MossdeepCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE07_GET, MossdeepCity_Gym_EventScript_GymStatueCertified
	goto MossdeepCity_Gym_EventScript_GymStatue
	end

MossdeepCity_Gym_EventScript_GymStatueCertified::
	msgbox MossdeepCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_GymStatue::
	msgbox MossdeepCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_Gym_EventScript_YellowFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 0
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_BlueFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 1
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_GreenFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 2
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_PurpleFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 3
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_EventScript_RedFloorSwitch::
	playse SE_SWITCH
	waitse
	playse SE_REPEL
	initrotatingtilepuzzle FALSE
	moverotatingtileobjects 4
	waitmovement 0
	turnrotatingtileobjects
	waitmovement 0
	freerotatingtilepuzzle
	end

MossdeepCity_Gym_Text_GymGuideAdvice:
	.string "Hey, nasıl gidiyor, şampiyon\nadayı {PLAYER}?\pBuradaki liderler PSİŞİK tipi\nPOKéMON kullanıyor.\pOnlara DÖVÜŞ veya ZEHİR tipi\nPOKéMON ile karşı koyarsan, korkunç\lhasar verirler!\pAyrıca, olağanüstü kombinasyon\nsaldırılarıyla üzerine geleceklerdir.\pKazanmak istiyorsan, onlara\nPOKéMON'unla ne kadar sıkı\lolduğunu göstermen gerekecek.\lHadi bakalım!$"

MossdeepCity_Gym_Text_GymGuidePostVictory:
	.string "Vay canına, hayret vericisin!\nSen harika bir eğitmensin!$"

MossdeepCity_Gym_Text_PrestonIntro:
	.string "Savaşlar ruhunun gücüne bağlıdır!\nZayıf ruhlular asla kazanamaz!$"

MossdeepCity_Gym_Text_PrestonDefeat:
	.string "Kaybettim!\nRuhumu tekrar yumuşatmalıyım!$"

MossdeepCity_Gym_Text_PrestonPostBattle:
	.string "Kararsızlar kaybeder.\nBu benim sana uyarım.$"

MossdeepCity_Gym_Text_VirgilIntro:
	.string "Yeteneğini göreyim!$"

MossdeepCity_Gym_Text_VirgilDefeat:
	.string "Muhteşem bir yeteneğe sahipsin!$"

MossdeepCity_Gym_Text_VirgilPostBattle:
	.string "Eğer dünyada dahiler varsa, o zaman\nsalon liderlerimiz onlardandır!\pAncak, sen onlardan bile daha yetenekli\nolabilirsin…$"

MossdeepCity_Gym_Text_BlakeIntro:
	.string "Fufufufu…\nPOKé TOPU'nu telekinetik olarak\lhavaya kaldırmamı izle!\pVrooooooooaaaa!\n… … … … … … …\pBazen uyumsuz oluyorum.$"

MossdeepCity_Gym_Text_BlakeDefeat:
	.string "POKéMON savaş becerilerim yeterince\nsenkronize değil!$"

MossdeepCity_Gym_Text_BlakePostBattle:
	.string "POKé TOPU psişik olarak\nkaldırılamayacak kadar ağırdı.\lAma bu toz bulutu ise…\pVuhuuuuuuuuuu!\n… … … … … …\pHayır, hile yapmıyorum!\nOna üflemedim! Gerçekten!$"

MossdeepCity_Gym_Text_HannahIntro:
	.string "Bana karşı kaybettiğinde, kendine çok\nyüklenme.\pZayıf olduğundan değil, ben çok\ngüçlüyüm!$"

MossdeepCity_Gym_Text_HannahDefeat:
	.string "Sen çok güçlüsün!$"

MossdeepCity_Gym_Text_HannahPostBattle:
	.string "Kaybettiğim için kendime kızmayacağım.\nSadece daha sıkı çalışmam gerekiyor.\pOlumlu düşünmek, bu benim güçlü yanım!$"

MossdeepCity_Gym_Text_SamanthaIntro:
	.string "Görüyorum… Geleceğini görüyorum…\pEğer beni yenebilirsen, sana geleceğini\nsöyleyeceğim!$"

MossdeepCity_Gym_Text_SamanthaDefeat:
	.string "Teslim oluyorum!$"

MossdeepCity_Gym_Text_SamanthaPostBattle:
	.string "Salon liderlerimizle son derece\nyoğun bir mücadele vereceksin…\pSonuç…\nBunu söyleyemem!$"

MossdeepCity_Gym_Text_MauraIntro:
	.string "Geçtiğin yollar…\nYaşadıkların…\pÖğrendiğin her şeyle gel!$"

MossdeepCity_Gym_Text_MauraDefeat:
	.string "Büyük bir yol kat ettin!$"

MossdeepCity_Gym_Text_MauraPostBattle:
	.string "Gayretle çalışanları parlak bir\ngelecek beklemektedir.\pTembellik edenler içinse sonunda\nsadece umutsuzluk vardır.\pNe ekersen onu biçersin…$"

MossdeepCity_Gym_Text_SylviaIntro:
	.string "Hayatımı riske atsam bile, bu savaşı\nkazanacağım!$"

MossdeepCity_Gym_Text_SylviaDefeat:
	.string "Yaptığın şey…\nBeni dehşete düşürüyor…$"

MossdeepCity_Gym_Text_SylviaPostBattle:
	.string "Bana meydan okumaya nasıl cüret\nedersin?\pBaşına korkunç bir şey gelirse bu\nbenim suçum olmayacak.$"

MossdeepCity_Gym_Text_NateIntro:
	.string "Hohoho.\pPSİŞİK tiplerin ne kadar inatçı\nolabileceğini göstermemi istiyorsun.$"

MossdeepCity_Gym_Text_NateDefeat:
	.string "Aman Tanrım!\nSavaş stilin harika!$"

MossdeepCity_Gym_Text_NatePostBattle:
	.string "Ne kadar kötü olursa olsun, yenilginin\nbeni sarsmasına izin vermem.$"

MossdeepCity_Gym_Text_KathleenIntro:
	.string "Sana mükemmel, korkunç bir zaman\ngeçirteceğim!$"

MossdeepCity_Gym_Text_KathleenDefeat:
	.string "H-hayıııır!$"

MossdeepCity_Gym_Text_KathleenPostBattle:
	.string "Canlılığın bulaşıcı!\nÇabuk uzaklaş benden!$"

MossdeepCity_Gym_Text_CliffordIntro:
	.string "Yaşımı başımı almış olabilirim ama bana\npatronluk taslamamanı öneririm.$"

MossdeepCity_Gym_Text_CliffordDefeat:
	.string "Ah, gençliğin gücüyle dolup\ntaşıyorsun!$"

MossdeepCity_Gym_Text_CliffordPostBattle:
	.string "Görünüşe göre gençlik enerjinin\nüstesinden gelemedim.$"

MossdeepCity_Gym_Text_MaceyIntro:
	.string "Sona kadar gidemezsin!\nBen varken asla!$"

MossdeepCity_Gym_Text_MaceyDefeat:
	.string "Nasıl bu kadar güçlü olabiliyorsun?$"

MossdeepCity_Gym_Text_MaceyPostBattle:
	.string "Hımph! Güçlü olabilirsin ama PSİŞİK\ntiplere uygun değilsin!\pSavaşma şeklin yetersiz!$"

MossdeepCity_Gym_Text_NicholasIntro:
	.string "Vroooa!\nSavaş gücümün tadına bak!$"

MossdeepCity_Gym_Text_NicholasDefeat:
	.string "Of! Bitti!$"

MossdeepCity_Gym_Text_NicholasPostBattle:
	.string "Pekâlâ! Bundan sonra yenilmez\nbir POKéMON gücü geliştireceğim.$"

MossdeepCity_Gym_Text_TateAndLizaIntro:
	.string "TATE: Hehehe… Şaşırdın mı?\p"
	.string "LİZA: Fufufu… Şaşırdın mı?\p"
	.string "TATE: İki SALON LİDERİ olmamıza?\n"
	.string "LİZA: İki SALON LİDERİ olmamıza?\p"
	.string "TATE: Biz ikiziz!\n"
	.string "LİZA: Biz ikiziz!\p"
	.string "TATE: Konuşmamıza gerek yok çünkü…\n"
	.string "LİZA: Birbirimizin ne diyeceğini…\p"
	.string "TATE: Aklımızdan düşünüp…\n"
	.string "LİZA: Anlayabiliyoruz!\p"
	.string "TATE: Bu kombinasyonumuz olağanüstü…\n"
	.string "LİZA: Bizi yenebilir misin?$"

MossdeepCity_Gym_Text_TateAndLizaDefeat:
	.string "TATE: Ne?! Kombinasyonumuz…\nLİZA: Paramparça oldu!\pTATE: Elden bir şey gelmez.\nSen kazandın…\pLİZA: Öyleyse, takdir\nolarak, bunu al.$"

MossdeepCity_Gym_Text_ReceivedMindBadge:
	.string "{PLAYER}, TATE ve LİZA'dan\nAKIL ROZETİ aldı.$"

MossdeepCity_Gym_Text_ExplainMindBadgeTakeThis:
	.string "TATE: ZİHİN ROZETİ, ÖZ. SLD ve\nÖZ. SVN artırır.\pLİZA: Ayrıca savaş dışında HM hareketi\nDALIŞ'ı kullanmanı sağlar.\pTATE: Bunu da almalısın.$"

MossdeepCity_Gym_Text_ExplainCalmMind:
	.string "TATE: TM04'ün içinde…\nLİZA: SAKİNLEŞ vardır!\pTATE: ÖZ SLD ve…\nLİZA: ÖZ. SVN yükseltir!\pTATE: PSİŞİK POKéMON'lar için\nmükemmel bir harekettir!\p… … … … … …$"

MossdeepCity_Gym_Text_RegisteredTateAndLiza:
	.string "TATE & LİZA, POKéNAV'a kaydedildi.$"

MossdeepCity_Gym_Text_TateAndLizaPostBattle:
	.string "TATE: Görünüşe göre sen ve\nPOKéMON'un arasındaki bağ, ikizler\lolarak paylaştığımız bağdan çok daha\lgüçlü.\pLİZA: Daha da güçleneceksin!\nSeninle savaştık, o yüzden biliyoruz.$"

MossdeepCity_Gym_Text_TateAndLizaNeedTwoMons:
	.string "TATE: Hehehe… Şaşırdın mı?\p"
	.string "LİZA: Fufufu… Şaşırdın mı?\p"
	.string "TATE: İki SALON LİDERİ olmamıza?\n"
	.string "LİZA: İki SALON LİDERİ olmamıza?\p"
	.string "TATE: Olamaz! Sadece bir…\n"
	.string "LİZA: POKéMON'un var!\p"
	.string "TATE: Bizimle savaşabilmen için…\n"
	.string "LİZA: İkiden fazla olmalıdır!\n"

MossdeepCity_Gym_Text_GymStatue:
	.string "MOSSDEEP ŞEHRİ POKéMON SALONU$"

MossdeepCity_Gym_Text_GymStatueCertified:
	.string "MOSSDEEP ŞEHRİ POKéMON SALONU\pLİZA VE TATE'İN ONAYLI\nEĞİTMENLERİ: {PLAYER}$"

MossdeepCity_Gym_Text_TateAndLizaPreRematch:
	.string "TATE: POKéMON'lar…\nLİZA: POKéMON'lar…\pTATE: Takımının kombinasyonu\ndeğişince…\pLİZA: Savaş tarzın da değişir.\pTATE: Ama ben…\nLİZA: Ama ben…\pTATE: Her zaman LİZA ile olacağım!\nLİZA: Her zaman TATE ile olacağım!\pTATE: Kombinasyonumuz…\nLİZA: Sana tekrar tekrar göstereceğiz!$"

MossdeepCity_Gym_Text_TateAndLizaRematchDefeat:
	.string "TATE: Sen ve POKéMON'un…\nLİZA: Sanki kardeşmişsiniz gibi!$"

MossdeepCity_Gym_Text_TateAndLizaPostRematch:
	.string "TATE: Bizi yıkabilirsin ama\niçimizde asla yıkılmayacağız!\pLİZA: Çünkü ikimiz her zaman\nbirbirimizi destekleriz!$"

MossdeepCity_Gym_Text_TateAndLizaRematchNeedTwoMons:
	.string "TATE: Yine döndün…\nLİZA: Yine döndün…\pTATE: Bizle bir rövanş için.\nLİZA: Bizle bir rövanş için.\pTATE: Ama…\nLİZA: Maçımız için…\pTATE: Sadece bir POKéMON getirmişsin!\nLİZA: Sadece bir POKéMON getirmişsin!\pTATE: Geri döndüğünde en az…\nLİZA: İki POKéMON getirmen gerek.$"
