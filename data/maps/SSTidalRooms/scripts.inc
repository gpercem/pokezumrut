SSTidalRooms_MapScripts::
	.byte 0

SSTidalRooms_EventScript_SnatchGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM49, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM49
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM49
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch::
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed::
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Colton::
	trainerbattle_single TRAINER_COLTON, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah::
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas::
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret::
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi::
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_Text_TakeRestOnBed:
	.string "Burada bir yatak var…\nBiraz dinlenelim.$"

SSTidalRooms_Text_ColtonIntro:
	.string "Sık sık LİLYCOVE şehrine giderim.\pYarışmalara katılmaktan hoşlanıyorum.$"

SSTidalRooms_Text_ColtonDefeat:
	.string "Keyifli bir maçtı!$"

SSTidalRooms_Text_ColtonPostBattle:
	.string "Bir sonraki yarışmada ne tür\nPOKéMON'lar göreceğimi hayal ederken\lçok heyecanlanıyorum. Bu beklenti beni\lheyecanlandırıyor!$"

SSTidalRooms_Text_MicahIntro:
	.string "Arkadaşların güçlü mü?$"

SSTidalRooms_Text_MicahDefeat:
	.string "Arkadaşların gerçekten de güçlü.$"

SSTidalRooms_Text_MicahPostBattle:
	.string "Arkadaşlarının insan olması gerekmez.\nBenim için POKéMON değerli dostlardır!$"

SSTidalRooms_Text_ThomasIntro:
	.string "Çocuk…\nKapıyı çaldın mı?$"

SSTidalRooms_Text_ThomasDefeat:
	.string "Mağlubiyet aceleye getirilmeden veya\npaniğe kapılmadan kabul edilmelidir.$"

SSTidalRooms_Text_ThomasPostBattle:
	.string "Herhangi bir durumda asla\nsinirlenmemek, görgü ve davranış\lkurallarındandır.$"

SSTidalRooms_Text_JedIntro:
	.string "JED: Bu konuda biraz utangaç\nhissediyorum ama…\lSana sevgi dolu gücümüzü\lgöstereceğiz!$"

SSTidalRooms_Text_JedDefeat:
	.string "JED: Ahh…$"

SSTidalRooms_Text_JedPostBattle:
	.string "JED: İlk defa aşk dolu gücümüz galip\ngelemedi!\lHarika bir eğitmen olmalısın!$"

SSTidalRooms_Text_JedNotEnoughMons:
	.string "JED: Sadece bir POKéMON'un mu var?\nBu çok yalnız değil mi?$"

SSTidalRooms_Text_LeaIntro:
	.string "LEA: Biraz aptalca hissediyorum ama…\nSana aşk dolu gücümüzü göstereceğiz!$"

SSTidalRooms_Text_LeaDefeat:
	.string "LEA: Böö!$"

SSTidalRooms_Text_LeaPostBattle:
	.string "LEA: İnanamıyorum!\nAşk dolu gücümüz yenildi…\lSen harika bir eğitmensin!$"

SSTidalRooms_Text_LeaNotEnoughMons:
	.string "LEA: Savaşmak istedim… Ama iki tane\nbile POKéMON'un yok…$"

SSTidalRooms_Text_GarretIntro:
	.string "Ah, tam zamanında geldin.\pGörüyorsun ki sıkıldım.\nBeni eğlendirebilirsin.$"

SSTidalRooms_Text_GarretDefeat:
	.string "…Bu iş görür.$"

SSTidalRooms_Text_GarretPostBattle:
	.string "Belki de babamın benim için bir yat\nalmasını sağlamalıyım.\lBen ve POKéMON'larım için!$"

SSTidalRooms_Text_NaomiIntro:
	.string "Çok sevimli bir eğitmensin.\nÇay içmek ister misin?\lYoksa savaşmayı mı tercih edersin?$"

SSTidalRooms_Text_NaomiDefeat:
	.string "Anlıyorum.\nSen aktif birisin.$"

SSTidalRooms_Text_NaomiPostBattle:
	.string "Lüks bir gemiyle dünya seyahatinin\nkendine has cazibeleri olduğunu\lsöylemeliyim…\pAncak, HOENN'i gemiyle gezmenin\nçekici bir yanı olduğunu da itiraf\letmeliyim.$"

SSTidalRooms_Text_NotSuspiciousTakeThis:
	.string "Ee… Selam!\nBen… Ben şüpheli davranmıyorum!\lIm… Bunu alabilirsin!\lBedavaya!\pDürüst olmak gerekirse, bunu birinden\nçalmadım! Asla böyle bir şey yapmam!\lBu temiz!\lKullanabilirsin!$"

SSTidalRooms_Text_ExplainSnatch:
	.string "KAPKAÇ, belirli saldırıların faydalı\netkilerini bir düşman veya dost\ltarafından kullanılmadan önce çalar.$"


