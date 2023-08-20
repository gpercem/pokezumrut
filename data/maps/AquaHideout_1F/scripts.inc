AquaHideout_1F_MapScripts::
	.byte 0

@ The below two entrance guards give hints about what to do to progress the story
AquaHideout_1F_EventScript_HideoutEntranceGrunt1::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint1
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint1
	msgbox AquaHideout_1F_Text_OurBossIsSnatchingSomething, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint1::
	msgbox AquaHideout_1F_Text_WhereMightMagmaHideoutBe, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint1::
	msgbox AquaHideout_1F_Text_BossWentToJackASubmarine, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_HideoutEntranceGrunt2::
	lock
	faceplayer
	goto_if_set FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT, AquaHideout_1F_EventScript_SlateportHint2
	goto_if_set FLAG_RECEIVED_RED_OR_BLUE_ORB, AquaHideout_1F_EventScript_MagmaHideoutHint2
	msgbox AquaHideout_1F_Text_BossIsOnRoute122, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_MagmaHideoutHint2::
	msgbox AquaHideout_1F_Text_TeamMagmaAtMtChimney, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_SlateportHint2::
	msgbox AquaHideout_1F_Text_BossIsInSlateportCity, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_AQUA_HIDEOUT_1, AquaHideout_1F_Text_Grunt1Intro, AquaHideout_1F_Text_Grunt1Defeat, AquaHideout_1F_EventScript_Grunt1Defeated
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

AquaHideout_1F_EventScript_Grunt1Defeated::
	msgbox AquaHideout_1F_Text_Grunt1PostBattle, MSGBOX_DEFAULT
	release
	end

AquaHideout_1F_Text_OurBossIsSnatchingSomething:
	.string "Ne? Ne? Ne?\nAQUA TAKIMI'ndan ne istiyorsun?\pPatronumuz burada değil!\nÖnemli bir şey almaya gitti!\p… … Nereye mi gitti?\pVahaha! Sana gerçekten bu kadar önemli\nbir şeyi söyleyeceğimi mi sandın?$"

AquaHideout_1F_Text_WhereMightMagmaHideoutBe:
	.string "Ne? Ne? Ne?\nSen bir MAGMA TAKIMI haydutu musun?\pDuyduğuma göre MAGMA TAKIMI,\nsığınaklarında muhteşem güçlü bir\lPOKéMON'u uyandırmaya çalışıyormuş.\pAma saklandıkları yer neresi olabilir?$"

AquaHideout_1F_Text_BossWentToJackASubmarine:
	.string "Ne? Ne? Ne?\nAQUA TAKIMI'ndan ne istiyorsun?\pPatronumuz burada değil! Bir\ndenizaltıyı soymaya gitti!\p… Nerede mi?\pVahaha! Sana gerçekten bu kadar önemli\nbir şey söyleyeceğimi mi sanıyorsun?$"

AquaHideout_1F_Text_BossIsOnRoute122:
	.string "Ne? Ne? Ne?\nAQUA TAKIMI'ndan ne istiyorsun?\pPatronumuz burada değil!\nPYRE DAĞI'na gidiyor!\p… Neden mi gitti?\pVahaha! Gerçekten sana bu kadar önemli\nbir şey söyleyeceğimi mi sanıyorsun?$"

AquaHideout_1F_Text_TeamMagmaAtMtChimney:
	.string "Ne? Ne? Ne?\nSen bir MAGMA TAKIMI haydutu musun?\pMAGMA TAKIMI'nın CHİMNEY DAĞI'nda harika\nbir POKéMON'un peşinde olduğunu duydum.\pAma o POKéMON neye benziyor?$"

AquaHideout_1F_Text_BossIsInSlateportCity:
	.string "Ne? Ne? Ne?\nAQUA TAKIMI'ndan ne istiyorsun?\pPatronumuz burada değil!\nSLATEPORT ŞEHRİ'ne gidiyor!\p… Neden mi gitti?\pVahaha! Sana gerçekten bu kadar önemli\nbir şey söyleyeceğimi mi sanıyorsun?$"

AquaHideout_1F_Text_Grunt1Intro:
	.string "Ayiyiyi!\nŞüpheli biri tespit edildi!$"

AquaHideout_1F_Text_Grunt1Defeat:
	.string "Grrrrr…\nKaybettim!$"

AquaHideout_1F_Text_Grunt1PostBattle:
	.string "Takım için kaybettim ama işimi yaptım.$"


