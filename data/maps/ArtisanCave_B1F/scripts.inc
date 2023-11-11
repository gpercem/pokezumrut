ArtisanCave_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ArtisanCave_B1F_OnTransition
	.byte 0

ArtisanCave_B1F_OnTransition:
	setflag FLAG_LANDMARK_ARTISAN_CAVE
	end

ArtisanCave_B1F_EventScript_ItemOldSeaMap::
	finditem ITEM_OLD_SEA_MAP
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	msgbox ArtisanCave_B1F_Text_OldSeaMap, MSGBOX_DEFAULT
	closemessage
	end

ArtisanCave_B1F_Text_OldSeaMap:
	.string "Bu eksi harita, uzun süredir\nburadaymış gibi duruyor.\pBelki BAY BRİNEY bu konuda bana\nyardımcı olabilir.$"

ArtisanCave_OutsideEast_EventScript_Gokhan::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_OLD_SEA_MAP, ArtisanCave_OutsideEast_EventScript_Gokhan_Defeated
	waitse
	playse SE_PIN
	msgbox ArtisanCave_OutsideEast_Text_Hi, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GOKHAN, ArtisanCave_OutsideEast_Text_GokhanDefeat
	goto ArtisanCave_OutsideEast_GiveItem
	end


ArtisanCave_OutsideEast_GiveItem::
	msgbox ArtisanCave_OutsideEast_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	closemessage
	face_right
	release
	end

ArtisanCave_OutsideEast_EventScript_Gokhan_Defeated::
	waitmovement 0
	msgbox ArtisanCave_OutsideEast_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

ArtisanCave_OutsideEast_Text_Hi:
	.string "GÖKHAN: Selam, {PLAYER}{KUN}.\nBen bu oyunun çevirmeniyim.\pBuralara kadar geldiğine göre\nbir savaş yapabiliriz.$"

ArtisanCave_OutsideEast_Text_GokhanDefeat:
	.string "Tebrikler, güzel bir maçtı.$"

ArtisanCave_OutsideEast_Text_MyPredictionCameTrue:
	.string "GÖKHAN: Tekrardan tebrikler.\pBu haritayı LILYCOVE'daki BRINEY'e\ngötürmeye ne dersin?$"
