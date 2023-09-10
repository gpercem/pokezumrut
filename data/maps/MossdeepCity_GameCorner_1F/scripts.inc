MossdeepCity_GameCorner_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_GameCorner_1F_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MossdeepCity_GameCorner_1F_OnWarp
	map_script MAP_SCRIPT_ON_LOAD, CableClub_OnLoad
	.byte 0

MossdeepCity_GameCorner_1F_OnWarp:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_CheckTurnAttendant
	.2byte 0

MossdeepCity_GameCorner_1F_OnFrame:
	map_script_2 VAR_CABLE_CLUB_STATE, USING_MINIGAME, CableClub_EventScript_ExitMinigameRoom
	.2byte 0

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_InfoMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_InfoMan2
	release
	end

@ Script is redundant, the label in the goto also does lock and faceplayer
MossdeepCity_GameCorner_1F_EventScript_OldMan::
	lock
	faceplayer
	goto MossdeepCity_GameCorner_1F_EventScript_OldMan2
	release
	end


@ Everything below is leftover from RS
@ The house that was here in RS was moved to Sootopolis and replaced by the Game Corner
@ The text below is unused and duplicated in its replacement in Sootopolis City
@ And the BG Door event was moved inaccessibly into a wall

RS_MysteryEventsHouse_EventScript_Door::
	msgbox RS_MysteryEventsHouse_Text_DoorIsLocked, MSGBOX_SIGN
	end

RS_MysteryEventsHouse_Text_OldManGreeting:
	.string "Gençken bir POKéMON ANTRENÖRÜ olarak\ndünyayı dolaştım.\pArtık yaşlı bir akbaba olduğum için tek\neğlencem genç EĞİTMENLERİN savaşını\lizlemek.$"

RS_MysteryEventsHouse_Text_DoorIsLocked:
	.string "Kapı kilitli görünüyor.$"

RS_MysteryEventsHouse_Text_ChallengeVisitingTrainer:
	.string "{STR_VAR_1} adında bir ANTRENÖR evimi\nziyaret ediyor.\p{STR_VAR_1}'e meydan okumak ister\nmisiniz?$"

RS_MysteryEventsHouse_Text_YouWontBattle:
	.string "Savaşmayacak mısın? Seni savaşırken\ngöremeyeceğim için hayal kırıklığına\luğradım.$"

RS_MysteryEventsHouse_Text_KeepItToA3On3:
	.string "Oh, güzel, güzel!\pAma evim o kadar da sağlam değil.\p3'e 3 maç yapmanızı rica edebilir\nmiyim?$"

RS_MysteryEventsHouse_Text_SaveYourProgress:
	.string "İki savaştan önce ilerlemenizi\nkaydetmelisiniz.$"

RS_MysteryEventsHouse_Text_HopeToSeeAGoodMatch:
	.string "Umarım iyi bir eşleşme olur!$"

RS_MysteryEventsHouse_Text_BattleTie:
	.string "Böylece, bir çekişmeye dönüştü.\pİki tarafın da bir adım bile atmadığı\nmuhteşem bir maçtı!$"

RS_MysteryEventsHouse_Text_BattleWon:
	.string "Bu mükemmeldi!\pKendimi gençliğimde yeniden görmek\ngibiydi!$"

RS_MysteryEventsHouse_Text_BattleLost:
	.string "Ah, senin için çok kötü!\pAma iyi bir maçtı. Umarım bir dahaki\nsefere kazanabilirsin.$"
