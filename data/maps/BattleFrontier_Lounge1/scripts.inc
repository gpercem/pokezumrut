BattleFrontier_Lounge1_MapScripts::
	.byte 0

@ NPC that rates pokemon based on their IVs
BattleFrontier_Lounge1_EventScript_Breeder::
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_BreederIntro
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder::
	special ChoosePartyMon
	waitstate
	goto_if_ne VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_ShowMonToBreeder
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge1_EventScript_CancelMonSelect
	end

BattleFrontier_Lounge1_EventScript_BreederIntro::
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder::
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon, MSGBOX_DEFAULT
	return

@ BufferVarsForIVRater buffers the following values
@ VAR_0x8005: Sum of the mons IVs
@ VAR_0x8006: Stat id of highest IV stat
@ VAR_0x8007: IV of the highest IV stat
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder::
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge1_EventScript_ShowEggToBreeder
	special BufferVarsForIVRater
	goto_if_le VAR_0x8005, 90, BattleFrontier_Lounge1_EventScript_AverageTotalIVs       @ Average of 15
	goto_if_le VAR_0x8005, 120, BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs @ Average of 20
	goto_if_le VAR_0x8005, 150, BattleFrontier_Lounge1_EventScript_HighTotalIVs         @ Average of 25
	goto_if_ge VAR_0x8005, 151, BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs     @ Average of > 25
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder::
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

@ Comment on the highest IV stat
BattleFrontier_Lounge1_EventScript_HighestIVStat::
	goto_if_eq VAR_0x8006, STAT_HP, BattleFrontier_Lounge1_EventScript_HighestIVHP
	goto_if_eq VAR_0x8006, STAT_ATK, BattleFrontier_Lounge1_EventScript_HighestIVAtk
	goto_if_eq VAR_0x8006, STAT_DEF, BattleFrontier_Lounge1_EventScript_HighestIVDef
	goto_if_eq VAR_0x8006, STAT_SPEED, BattleFrontier_Lounge1_EventScript_HighestIVSpeed
	goto_if_eq VAR_0x8006, STAT_SPATK, BattleFrontier_Lounge1_EventScript_HighestIVSpAtk
	goto_if_eq VAR_0x8006, STAT_SPDEF, BattleFrontier_Lounge1_EventScript_HighestIVSpDef
	end

@ Comment on the highest IV value
BattleFrontier_Lounge1_EventScript_HighestIVValue::
	goto_if_le VAR_0x8007, 15, BattleFrontier_Lounge1_EventScript_HighestIVLow
	goto_if_le VAR_0x8007, 25, BattleFrontier_Lounge1_EventScript_HighestIVMid
	goto_if_le VAR_0x8007, 30, BattleFrontier_Lounge1_EventScript_HighestIVHigh
	goto_if_ge VAR_0x8007, 31, BattleFrontier_Lounge1_EventScript_HighestIVMax
	end

BattleFrontier_Lounge1_EventScript_EndBreederComments::
	release
	end

BattleFrontier_Lounge1_EventScript_AverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_AverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs::
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighestIVHP::
	msgbox BattleFrontier_Lounge1_Text_BestAspectHP, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpeed::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpeed, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpAtk::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpDef::
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVLow::
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMid::
	msgbox BattleFrontier_Lounge1_Text_StatImpressive, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVHigh::
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMax::
	msgbox BattleFrontier_Lounge1_Text_StatFlawless, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_CancelMonSelect::
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1::
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2::
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro:
	.string "Yetmiş yıldır POKéMON\nyetiştiriyorum!\pBana efsanevi POKéMON\nyetiştiricisi de derler!\pBenim gibi olduğunda, POKéMON'a\nbaktığın anda yeteneklerini\lanlayabilirsin.\pSen bir eğitmensin. POKéMON'larının\nyeteneklerini bilmek istemez misin?\pGel! POKéMON'larına bakalım!$"

BattleFrontier_Lounge1_Text_AverageAbility:
	.string "…Hmm…\pBunu, genel olarak, ortalama bir\nyetenek olarak tanımlayabilirim.$"

BattleFrontier_Lounge1_Text_BetterThanAverageAbility:
	.string "…Hmm…\pBunu genel olarak ortalamanın\nüzerinde bir yeteneğe sahip olarak\ltanımlayabilirim.$"

BattleFrontier_Lounge1_Text_ImpressiveAbility:
	.string "…Hmm…\pBunun, genel olarak, oldukça etkileyici\nbir yetenek olduğunu söyleyebilirim!$"

BattleFrontier_Lounge1_Text_OutstandingAbility:
	.string "…Hmm…\pBunun, genel olarak, olağanüstü bir\nyeteneğe sahip olduğunu\lsöyleyebilirim!$"

BattleFrontier_Lounge1_Text_BestAspectHP:
	.string "En iyi yanının canı olduğunu\nsöyleyebilirim.$"

BattleFrontier_Lounge1_Text_BestAspectAtk:
	.string "Bu arada, en iyi yönünün SALDIRI\nolduğunu söyleyebilirim…$"

BattleFrontier_Lounge1_Text_BestAspectDef:
	.string "Bu arada, en iyi yönünün SAVUNMASI\nolduğunu söyleyebilirim…$"

BattleFrontier_Lounge1_Text_BestAspectSpAtk:
	.string "Bu arada, en iyi yönünün ÖZEL\nSALDIRISI olduğunu söyleyebilirim…$"

BattleFrontier_Lounge1_Text_BestAspectSpDef:
	.string "Bu arada, en iyi yönünün ÖZEL\nSAVUNMASI olduğunu söyleyebilirim…$"

BattleFrontier_Lounge1_Text_BestAspectSpeed:
	.string "En iyi özelliğine HIZ diyebilirim…$"

BattleFrontier_Lounge1_Text_StatRelativelyGood:
	.string "Bu istatistik nispeten iyi. …Hm… Ben\nböyle diyorum.$"

BattleFrontier_Lounge1_Text_StatImpressive:
	.string "Değerler oldukça iyi …Hm…\nDiyebileceğim bu kadar.$"

BattleFrontier_Lounge1_Text_StatOutstanding:
	.string "Bu değerler olağanüstü! …Hm…\nİşte ben böyle diyorum.$"

BattleFrontier_Lounge1_Text_StatFlawless:
	.string "Kusursuz! Mükemmel bir şey! …Hm…\nBen böyle diyorum.$"

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice:
	.string "Ne? Tavsiyelerime ayıracak vaktin yok\nmu?\pHer zaman büyüklerinizin\ndeneyimlerinden bir şeyler öğrenmeye\lhevesli olmalısınız!$"

BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending:
	.string "Evet, şimdi ne var?\pİlgilenmem gereken bir işim var! Bir\ndahaki sefere sakla!$"

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon:
	.string "Ah, genç adam! POKéMON'unun\nyetenekleri ilgini çekiyor mu?\pİşte, işte! Hadi POKéMON'una bir göz\natalım!$"

BattleFrontier_Lounge1_Text_EvenICantTell:
	.string "Ben bir uzmanım ama ben bile\nyumurtadan çıkmamış bir POKéMON\lhakkında bir şey söyleyemem!\pBana bir POKemon göster! Görmem\ngereken şey bir POKemon!$"

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding:
	.string "POKéMON'umun olağanüstü olduğunu\nsöyledi! Onu dikkatlice büyüttüğüme\lsevindim!$"

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt:
	.string "POKéMON'umun olağanüstü olduğunu\nsöyledi! Ama onu büyütmek için özel bir\lşey yapmadım.$"


