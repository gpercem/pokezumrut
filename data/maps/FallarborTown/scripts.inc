FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "Bir şeyler oluyor ve bu hiç hoşuma\ngitmiyor!\pPROF. COZMO'nun evine girip çıkan\ngizemli tipler gördüm.$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "Bu bölge eski günlerden beri meteorlarla\nanılır.\pMETEOR ŞELALESİ'nin uzun zaman önce\ndüşen bir göktaşı tarafından oyulduğu\lsöylenir.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "Bak! Şuna bir bak!\nBu benim AZURİLL'im!\pKaygan, pürüzsüz ve peluş gibi!$"

FallarborTown_Text_Azurill:
	.string "AZURİLL: Rooreelooo.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "LAVARİDGE SALONU LİDERİ FLANNERY'e\nmeydan okudun mu?\pO kızın büyükbabası ünlüydü.\nBir zamanlar POKéMON LİGİ'ndeki\lELİT DÖRTLÜ'den biriydi.\pFLANNERY'nin kendi başına büyük bir\nEĞİTMEN olduğunu görmek beni\lşaşırtmıyor.$"

FallarborTown_Text_BattleTentSign:
	.string "FALLARBOR SAVAŞ ÇADIRI\n“En Büyük Takımlar Toplansın!”$"

FallarborTown_Text_TownSign:
	.string "FALLARBOR KÖYÜ\n“Küçük bir çiftlik topluluğu.”$"

FallarborTown_Text_MoveTutorSign:
	.string "SALDIRI ÖĞRETMENİNİN EVİ\nPOKéMON'lara yeni saldırı öğretilir.$"


