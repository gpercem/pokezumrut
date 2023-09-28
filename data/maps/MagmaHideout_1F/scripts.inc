MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "MAGMA TAKIMI yoklama yaptığında\nsıraya girdiğimizde önemli koruma\lgörevleri alırız.\pBu yüzden bu köşede sıkışıp kaldım.\nYoklamaya hep geç kalıyorum!$"

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "Ben de antrenmanlara hep geç\nkalıyorum!\pBunu söylemekten nefret ediyorum ama\nben pısırığım.$"

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "Tamam, bundan sonra biraz daha çaba\ngöstermeye çalışacağım…$"

MagmaHideout_1F_Text_Grunt2Intro:
	.string "Liderimiz bize CHİMNEY DAĞI'nı\nkazmamızı söyledi, biz de kazdık.\pVe kazı sırasında aklımızı başımızdan\nalan bir şeyle karşılaştık!\pNe bulduk dersin?\pFuhahaha!\nBeni yenersen sana söylerim!$"

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "Arrgh!\nDayak yedim!$"

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "Yine de söylemeyeceğim.\nOraya vardığında öğrenirsin!\pSürprizleri sona saklamak daha iyi\nolur, değil mi?$"


