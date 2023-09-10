MtPyre_2F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CaveHole_CheckFallDownHole
	map_script MAP_SCRIPT_ON_TRANSITION, CaveHole_FixCrackedGround
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_2F_SetHoleWarp
	.byte 0

MtPyre_2F_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_MT_PYRE_1F
	end

MtPyre_2F_EventScript_Woman::
	msgbox MtPyre_2F_Text_MemoriesOfSkitty, MSGBOX_NPC
	end

MtPyre_2F_EventScript_PokefanM::
	msgbox MtPyre_2F_Text_TumbledFromFloorAbove, MSGBOX_NPC
	end

MtPyre_2F_EventScript_Mark::
	trainerbattle_single TRAINER_MARK, MtPyre_2F_Text_MarkIntro, MtPyre_2F_Text_MarkDefeat
	msgbox MtPyre_2F_Text_MarkPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Luke::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_LukeIntro, MtPyre_2F_Text_LukeDefeat, MtPyre_2F_Text_LukeNotEnoughMons
	msgbox MtPyre_2F_Text_LukePostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Dez::
	trainerbattle_double TRAINER_DEZ_AND_LUKE, MtPyre_2F_Text_DezIntro, MtPyre_2F_Text_DezDefeat, MtPyre_2F_Text_DezNotEnoughMons
	msgbox MtPyre_2F_Text_DezPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH, MtPyre_2F_Text_LeahIntro, MtPyre_2F_Text_LeahDefeat
	msgbox MtPyre_2F_Text_LeahPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_EventScript_Zander::
	trainerbattle_single TRAINER_ZANDER, MtPyre_2F_Text_ZanderIntro, MtPyre_2F_Text_ZanderDefeat
	msgbox MtPyre_2F_Text_ZanderPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_2F_Text_MemoriesOfSkitty:
	.string "Sevgili SKITTY'min anıları…\nDüşündükçe gözlerim doluyor.$"

MtPyre_2F_Text_TumbledFromFloorAbove:
	.string "Ah, uf.\nHer yerde delikler var.\pFark etmediğim içim yukarıdaki\nkattan yuvarlandım.$"

MtPyre_2F_Text_MarkIntro:
	.string "Hey! POKéMON mu arıyorsun?\nBenden sonra geldin! Çok kabasın!$"

MtPyre_2F_Text_MarkDefeat:
	.string "Ayieeeeh!\nÖzür dilerim, affet beni, lütfen!$"

MtPyre_2F_Text_MarkPostBattle:
	.string "İnsanlar buraya pek sık gelmiyor, ben\nde nadir POKéMON olur diye düşündüm.$"

MtPyre_2F_Text_LukeIntro:
	.string "LUKE: Buraya bir görev için geldik.\pHeheh, eğer ona ne kadar havalı\nolduğumu gösterirsem, bana aşık\lolacak. Biliyorum!\pEvet! Seni yeneceğim ve ona\nne kadar havalı olduğumu\lgöstereceğim!$"

MtPyre_2F_Text_LukeDefeat:
	.string "LUKE: Eyvah eyvah!$"

MtPyre_2F_Text_LukePostBattle:
	.string "LUKE: Kaybettik ama sorun değil!\nBurada senin yanındayım.$"

MtPyre_2F_Text_LukeNotEnoughMons:
	.string "LUKE: Beni yenmek istiyorsan, biraz daha\nPOKEMON getir.\pGetirmezsen kız arkadaşıma ne kadar\nhavalı olduğumu gösteremem!$"

MtPyre_2F_Text_DezIntro:
	.string "DEZ: Buraya erkek arkadaşımla bir\ncesaretle geldim.\pGerçekten korkutucu ama erkek\narkadaşımla birlikteyim. Sorun yok.\pBiliyorum! Seni yenerek erkek\narkadaşımın havalı görünmesini\lsağlayacağım!$"

MtPyre_2F_Text_DezDefeat:
	.string "DEZ: Waaaah! Korkuyorum!$"

MtPyre_2F_Text_DezPostBattle:
	.string "DEZ: Biz aşığız, bu yüzden kaybetmek\numurumuzda değil!$"

MtPyre_2F_Text_DezNotEnoughMons:
	.string "DEZ: Bize meydan okumak istiyorsan, en\naz iki POKéMON getirmelisin.\pErkek arkadaşım güçlüdür. Sadece bir\nPOKéMON yeterli olmaz.$"

MtPyre_2F_Text_LeahIntro:
	.string "Sen yabancı biri gibisin…\nBaşına bir şey gelmeden git!$"

MtPyre_2F_Text_LeahDefeat:
	.string "Hmm… Dayanıklısın.$"

MtPyre_2F_Text_LeahPostBattle:
	.string "Ailemiz, büyük büyükannemin\nzamanından beri burada eğitmenlik\lyapıyor…\pBu dağı korumak benim görevim.$"

MtPyre_2F_Text_ZanderIntro:
	.string "Kiyaaaaah!\nDehşete düştüm!$"

MtPyre_2F_Text_ZanderDefeat:
	.string "Hayır!\nAklımı kaybettim!$"

MtPyre_2F_Text_ZanderPostBattle:
	.string "Ne zaman hareket eden bir şey görsem\nkorkuyorum.\pBuraya antrenman yapmaya\ngelmemeliydim.$"


