LilycoveCity_CoveLilyMotel_2F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllHoennMons
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare::
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	special Special_ShowDiploma
	waitstate
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex:
	.string "Ben oyun tasarımcısıyım.\pBu doğru mu? Bir POKéDEX üzerinde\nmi çalışıyorsun?\pTamamlamaya çalışmak zor ama pes etme.\pEğer tamamlarsan, lütfen gelip bana\ngöster.$"

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis:
	.string "Vay canına! Bu harika!\nEvet, kesinlikle harika!\pBu POKéDEX tamamen dolu! POKéMON'ları\ngerçekten seviyor olmalısın!\pÇok etkilendim!\pBaşarından dolayı sana bir şey\nvereyim!$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer:
	.string "Ben mi? Benimle mi konuşuyorsun?\nBen yazılımcıyım.\pBurada slotlar nasıldır acaba?$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist:
	.string "Ben grafik tasarımcısıyım!\nHOENN POKéMON'ları ilginç, değil\nmi?$"

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute:
	.string "Kız yücüler çok şirinler, değil mi?\nSevimli bir yüzücüyle savaşmak\liçin…\pBu harika!\pVe ikizler! Çok tatlılar, değil mi?\nİkizlerle 2'ye 2 savaş.\pVayy, dayanılmaz derecede eğlenceli!$"

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart:
	.string "Deniz meltemi kalbimi gıdıklıyor.\nBurası harika bir yer!$"

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy:
	.string "İnsanların size ne zaman ve nerede\nmeydan okuyacağını asla bilemezsiniz.\pİşte bu yüzden GAME BOY ADVANCE'ım\nolmadan evden asla çıkmam.$"

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles:
	.string "SCOTT: … … … … … …\n… … … … …\nZzz…\p… … … … … Ha?! Aa, pardon!\nUyukluyordum!\pŞu POKéMON yarışmasına bakmaya\ngeldim.\pİtiraf etmeliyim ki, oldukça eğlenceli\ngörünüyor ama…\pBeni saf biri olarar düşün.\nSavaşları ve sert eğitmenleri tercih\lederim.\pAma bu sadece benim fikrim.\p{PLAYER}{KUN}, umarım SALONLAR,\nYARIŞMALAR, SAVAŞ ÇADIRLARI gibi her\lşeyden keyif alırsın!$"

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy:
	.string "SCOTT: Bence bir YARIŞMA kazanmak\niçin strateji gerekir.\pYARIŞMA stratejileri geliştirmek, daha\niyi bir EĞİTMEN olmanın bir yoludur,\ldiyebilirim.$"


