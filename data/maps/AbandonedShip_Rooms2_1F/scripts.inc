AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  @ Kira speaks for both when registering KiraAndDan
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "DAN: Hazine ararken bir EĞİTMEN bulduk!$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "DAN: Birlikte çalışmamıza rağmen\nkazanamadık…$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "DAN: Hiç hazine bulamıyoruz…\nAcaba birileri çoktan buldu mu?$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "DAN: İki POKéMON'un bile yok.\nBizi bu şekilde yenmeyi bekleyemezsin.$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "KİRA: Hazine arıyorduk.\pOnun yerine bir EĞİTMEN bulduk!$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "KİRA: Aaa, çok güçlü!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "KİRA: Hazineler nerede olabilir?\pHazineleri bulduğumuzda ne alacağıma\nçoktan karar verdim!$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "KİRA: İki POKéMON'un yok mu?\nBaşka bir zaman savaşmamız gerekecek!$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "KİRA: Beni çok kızdırıyorsun!\nBu yüzden seni kaydedeceğim!$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "DAN: Bunca zamandır hazineleri arıyorduk.\pPOKéMON'larımız da güçlendi.\nİstersen sana gösterelim.$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "DAN: Her zamanki gibi güçlüsün!$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "DAN: Hazine bulamıyoruz, POKéMON'da\nkaybediyoruz…\pEve gitmek istiyorum… Ama bunu\nsöylersem bana çok kızıyor…$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "DAN: İki POKéMON'un bile yok.\nBizi bu şekilde yenmeyi bekleyemezsin.$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "KİRA: Yine karşılaştık!\pSen de bizim gibi hazine aramaktan\nvazgeçmedin, değil mi?\pKaybedenin aramaktan vazgeçmesine\nbahse girelim mi?$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "KİRA: Yine kaybettik…$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "KİRA: POKéMON'umuzu biraz daha\nyükseltmeden ve buradaki hazineleri\lbulmadan gitmiyoruz!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "KİRA: İki POKEMON'un yok mu?\nBaşka bir zaman savaşmamız gerekecek!$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "Yüzmede iyi değilim ama savaşlarda\niyiyim!$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "Eyvah. Bu pek iyi gitmedi.$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "Bu gemide çıplak ayakla dolaşmak biraz\niğrenç.$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "Güç ve şefkat…\nBunlar bir eğitmenin hazineleridir!$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "Sende parıldayan bir şeyler var.$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "Kamaraların birinde bir şeyin\nparıldadığını gördüm.$"
