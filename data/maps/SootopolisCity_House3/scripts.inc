SootopolisCity_House3_MapScripts::
	.byte 0

SootopolisCity_House3_EventScript_Woman::
	lock
	faceplayer
	msgbox SootopolisCity_House3_Text_JuanHasManyFansDoYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SootopolisCity_House3_EventScript_HaveFans
	msgbox SootopolisCity_House3_Text_LonesomeTryWorkingHarder, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_HaveFans::
	msgbox SootopolisCity_House3_Text_YouMustBePrettyStrong, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House3_EventScript_Girl::
	msgbox SootopolisCity_House3_Text_TrainerFanClubWasWild, MSGBOX_NPC
	end

SootopolisCity_House3_Text_JuanHasManyFansDoYou:
	.string "Sen bir POKéMON eğitmenisin, değil mi?\pSOOTOPOLİS'teki JUAN'ın birçok\nhayranı var. Öğrencisi WALLACE'den\lbile fazla!\pSenin var mı?$"

SootopolisCity_House3_Text_YouMustBePrettyStrong:
	.string "O zaman oldukça güçlü olmalısın.$"

SootopolisCity_House3_Text_LonesomeTryWorkingHarder:
	.string "Ah, canım…\nBiraz yalnızsın.\pHayran kitlesi edinmek için biraz daha\nçalış.$"

SootopolisCity_House3_Text_TrainerFanClubWasWild:
	.string "HOENN'in dışından bile kendini adamış\ntaraftarlar geliyor.\pLİLYCOVE'daki EĞİTMEN HAYRAN KULÜBÜ,\ngittiğimde gerçekten çok çılgındı.$"


