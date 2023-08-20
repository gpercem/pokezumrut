AbandonedShip_Rooms_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms_1F_EventScript_Gentleman::
	msgbox AbandonedShip_Rooms_1F_Text_TakingALookAround, MSGBOX_NPC
	end

AbandonedShip_Rooms_1F_EventScript_Demetrius::
	trainerbattle_single TRAINER_DEMETRIUS, AbandonedShip_Rooms_1F_Text_DemetriusIntro, AbandonedShip_Rooms_1F_Text_DemetriusDefeat
	msgbox AbandonedShip_Rooms_1F_Text_DemetriusPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_EventScript_Thalia::
	trainerbattle_single TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaIntro, AbandonedShip_Rooms_1F_Text_ThaliaDefeat, AbandonedShip_Rooms_1F_EventScript_RegisterThalia
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms_1F_EventScript_ThaliaRematch
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms_1F_EventScript_RegisterThalia::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_THALIA_1
	release
	end

AbandonedShip_Rooms_1F_EventScript_ThaliaRematch::
	trainerbattle_rematch TRAINER_THALIA_1, AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro, AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat
	msgbox AbandonedShip_Rooms_1F_Text_ThaliaPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms_1F_Text_TakingALookAround:
	.string "Bu tür gemiler nadirdir, bu yüzden\netrafa bir göz atıyorum.\pHmhm… Başka kamaralar da var gibi\ngörünüyor…$"

AbandonedShip_Rooms_1F_Text_ThaliaIntro:
	.string "Seni buraya getiren nedir?\nMerak ediyor olmalısın!$"

AbandonedShip_Rooms_1F_Text_ThaliaDefeat:
	.string "Sadece meraklı değil, aynı zamanda\ngüçlüsün…$"

AbandonedShip_Rooms_1F_Text_ThaliaPostBattle:
	.string "Yandaki adam.\pSadece gezdiğini söylüyor ama bundan\nemin değilim.$"

AbandonedShip_Rooms_1F_Text_ThaliaRegister:
	.string "Sen çok güçlü bir eğitmensin!\nSeni anı olarak kaydetmeme izin ver!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchIntro:
	.string "Seni geri döndüren şey nedir?\nGerçekten merak ediyor olmalısın!$"

AbandonedShip_Rooms_1F_Text_ThaliaRematchDefeat:
	.string "Çok güçlüsün.$"

AbandonedShip_Rooms_1F_Text_ThaliaPostRematch:
	.string "Bu adamın bir şeylerin peşinde\nolduğuna eminim! Çok şüpheli davranıyor!$"

AbandonedShip_Rooms_1F_Text_DemetriusIntro:
	.string "Yupii! Beni buldun!\n…Ha?$"

AbandonedShip_Rooms_1F_Text_DemetriusDefeat:
	.string "Sen benim annem değilsin.$"

AbandonedShip_Rooms_1F_Text_DemetriusPostBattle:
	.string "Annemle başım belada, o yüzden kaçtım.\nNerede olduğumu söyleme!$"


