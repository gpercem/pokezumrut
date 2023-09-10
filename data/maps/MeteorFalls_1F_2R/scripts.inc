MeteorFalls_1F_2R_MapScripts::
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas::
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas::
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay::
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay::
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  @ John speaks for both during register
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay::
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro:
	.string "Burası biz EJDERHA kullanıcılarının\neğitim yaptığı yerdir.\pŞampiyonlar bile ara sıra ziyaret\nederler.\pBuranın ne kadar özel olduğunu anladın\nmı?$"

MeteorFalls_1F_2R_Text_NicolasDefeat:
	.string "Ahh!\nBu kadar güçlü olmanı beklemiyordum!$"

MeteorFalls_1F_2R_Text_NicolasPostBattle:
	.string "Önümüzdeki yol uzun ve çetin.\pPOKéMON'um ve ben ne zaman daha iyi\nolacağız ki?$"

MeteorFalls_1F_2R_Text_NicolasRegister:
	.string "Gücün hakkında daha fazla şey bilmek\nistiyorum.\lSeni POKéNAV'ıma kaydetmeliyim.$"

MeteorFalls_1F_2R_Text_NicolasRematchIntro:
	.string "Senle tanıştığımızdan beri, en\niyiyi hedefleyerek sıkı çalıştık.\pNe kadar güçlendiğimizi gör!$"

MeteorFalls_1F_2R_Text_NicolasRematchDefeat:
	.string "Ağh!\nBu kadar güçlü olmanı beklemiyordum!$"

MeteorFalls_1F_2R_Text_NicolasPostRematch:
	.string "Belli ki POKéMON eğitimine devam\netmişsin.\pSen güçlü kaldığın sürece, ben de daha\ngüçlü olabilirim!$"

MeteorFalls_1F_2R_Text_JohnIntro:
	.string "JOHN: POKéMON'lar ile her zaman ikili\nolarak birlikte mücadele ettik.\lKendimize güveniyoruz.$"

MeteorFalls_1F_2R_Text_JohnDefeat:
	.string "JOHN: Aman Tanrım.\nKaybettik, aşkım.$"

MeteorFalls_1F_2R_Text_JohnPostBattle:
	.string "JOHN: Biz elli yıldır evliyiz.\pDüşünüyorum da, sevgili karımı henüz\nbir savaşta yenemedim.$"

MeteorFalls_1F_2R_Text_JohnNotEnoughMons:
	.string "JOHN: Vay, vay, ne genç bir eğitmen!\pBizimle savaşacak mısın?\nEğer istiyorsan, daha fazla POKéMON\lile dönmen gerekecek.$"

MeteorFalls_1F_2R_Text_JohnRegister:
	.string "JOHN: Hey, eğer fırsatın olursa\nbizimle tekrar savaşır mısın?$"

MeteorFalls_1F_2R_Text_JayIntro:
	.string "JAY: Elli yıldır evliyiz.\pBir çift olarak paylaştığımız bağ\nasla koparılamaz.$"

MeteorFalls_1F_2R_Text_JayDefeat:
	.string "JAY: Tanrım.\nKaybettik, sevgili kocam.$"

MeteorFalls_1F_2R_Text_JayPostBattle:
	.string "JAY: Elli yıllık evlilik…\pEğer tartışırsak, bunu her zaman bir\nPOKéMON savaşıyla çözebiliyoruz…$"

MeteorFalls_1F_2R_Text_JayNotEnoughMons:
	.string "JAY: Vay, vay, sen genç bir\neğitmensin.\pEğer bizimle savaşmak istiyorsan, daha\nfazla POKéMON ile geri gelmen\lgerekecek.$"

MeteorFalls_1F_2R_Text_JohnRematchIntro:
	.string "JOHN: POKéMON ile her zaman ikili\nolarak birlikte mücadele ettik.\lKendimize güveniyoruz.$"

MeteorFalls_1F_2R_Text_JohnRematchDefeat:
	.string "JOHN: Aman Tanrım.\nKaybettik, sevgili karım.$"

MeteorFalls_1F_2R_Text_JohnPostRematch:
	.string "JOHN: Elli yıldır evliyiz.\pDüşünüyorum da, sevgili eşim ve ben,\ngün be gün mücadele ettik…$"

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons:
	.string "JAY: Vay, vay, ne genç bir\neğitmen!\pBizimle savaşacak mısın? Eğer öyleyse,\ndaha fazla POKéMON ile dönmeniz\lgerekecek.$"

MeteorFalls_1F_2R_Text_JayRematchIntro:
	.string "JAY: Elli yıldır evliyiz.\pBunca zaman birbirimize destek olduk.\nKendimizi güçlü kıldık.$"

MeteorFalls_1F_2R_Text_JayRematchDefeat:
	.string "JAY: Tanrım.\nKaybettik, sevgili kocam.$"

MeteorFalls_1F_2R_Text_JayPostRematch:
	.string "JAY: Elli yıllık evlilik…\nBirçok şey oldu.\pUmarım birlikte mutlu anılar\nbiriktirmeye devam ederiz.$"

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons:
	.string "Vay, vay, sen genç bir EĞİTMEN\ndeğil misin?\pEğer bizimle savaşmak istiyorsan, daha\nfazla POKéMON ile geri gelmen\lgerekecek.$"


