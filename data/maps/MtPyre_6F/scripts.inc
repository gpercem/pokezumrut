MtPyre_6F_MapScripts::
	.byte 0

MtPyre_6F_EventScript_Valerie::
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie::
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric::
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro:
	.string "Buradayken…\nİçim bir tuhaf oluyor…$"

MtPyre_6F_Text_ValerieDefeat:
	.string "Gücüm azalıyor…$"

MtPyre_6F_Text_ValeriePostBattle:
	.string "Belki de bu his, burada uyuyan\nruhlardan geliyordur…$"

MtPyre_6F_Text_ValerieRegister:
	.string "Fufufu… Maçı kaybettim ama…\nÖzel yeteneklerimi kullanabilirim.\pEllerimi POKéNAV'ına sürmeden…\nHiyah!$"

MtPyre_6F_Text_ValerieRematchIntro:
	.string "Arkanda bir şey…\nO da ne…$"

MtPyre_6F_Text_ValerieRematchDefeat:
	.string "O şey kayboldu.$"

MtPyre_6F_Text_ValeriePostRematch:
	.string "POKéMON'lar burada dinlenirler…$"

MtPyre_6F_Text_CedricIntro:
	.string "Yönünü mü kaybettin?\nKorkma çünkü ben buradayım!$"

MtPyre_6F_Text_CedricDefeat:
	.string "Kaybolmadın mı?$"

MtPyre_6F_Text_CedricPostBattle:
	.string "Kaybolmuş bir eğitmenin paniğe\nkapılacağı ve yenilmesinin kolay\lolacağı hissine kapıldım.\pBu pis bir şeydi.\nBir daha denemeyeceğim…$"


