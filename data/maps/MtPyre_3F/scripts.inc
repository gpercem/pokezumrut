MtPyre_3F_MapScripts::
	.byte 0

MtPyre_3F_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla::
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro, MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle::
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle::
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro:
	.string "Dağın zengin atmosferi psişik gücümü\nyükseltti!\pSenin gibi sıradan bir çocuk…\nKazanmayı mı hayal ediyor?$"

MtPyre_3F_Text_WilliamDefeat:
	.string "Kendime acıyorum.$"

MtPyre_3F_Text_WilliamPostBattle:
	.string "Psişik güçlerim kesinlikle arttı\nama yine de…$"

MtPyre_3F_Text_KaylaIntro:
	.string "Ahahahaha!\pBurası çocuklara göre bir yer değil,\nen azından sana!$"

MtPyre_3F_Text_KaylaDefeat:
	.string "Tertemiz kaybettim.$"

MtPyre_3F_Text_KaylaPostBattle:
	.string "Bu, eğitimimin hala yeterli olmadığı\nanlamına geliyor…\pZirveye doğru çalışmaya devam\netmeliyim.\pHadi bakalım!$"

MtPyre_3F_Text_GabrielleIntro:
	.string "Neden buraya geldin?$"

MtPyre_3F_Text_GabrielleDefeat:
	.string "Bu inanılmazdı!\nÇok özel bir eğitmensin.$"

MtPyre_3F_Text_GabriellePostBattle:
	.string "Hayatını kaybeden POKéMON'lar…\nŞu anda yanında olan POKéMON'lar…\pVe gelecekte karşılaşacakların…\pHepsine eşit derecede değer vermelisin.\nLütfen şunu unutma.$"

MtPyre_3F_Text_GabrielleRegister:
	.string "Biraz daha büyüdüklerinde\nPOKéMON'larını görmek isterim…\pLütfen, POKéNAV'ına bir bakayım.$"

MtPyre_3F_Text_GabrielleRematchIntro:
	.string "Bu sensin…\pBana büyümüş POKEMON'unu göstermeye\nmi geldin?$"

MtPyre_3F_Text_GabrielleRematchDefeat:
	.string "Ne kadar harika!\nSen özel bir insansın.$"

MtPyre_3F_Text_GabriellePostRematch:
	.string "Hayatını kaybeden POKéMON'lar…\nŞu anda yanında olan POKéMON'lar…\pVe gelecekte karşılaşacakların…\pHepsine eşit derecede değer vermelisin.\nBunu unutmamışsın.$"

