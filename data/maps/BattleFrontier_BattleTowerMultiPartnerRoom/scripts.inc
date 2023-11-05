.set LOCALID_ATTENDANT, 1

BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_ATTENDANT
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement OBJ_EVENT_ID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner:
	.string "Lütfen burada toplanan EĞİTMENLER\narasından bir ortak bulun.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner:
	.string "{PLAYER}, takımınız için bir ortak\nbulamadınız.\pAramayı bırakıp resepsiyona dönmek\nister misiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2:
	.string "O zaman lütfen burada toplanan\nEĞİTMENLER arasından bir ortak bulun.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "Bir ortak seçtiğiniz için teşekkür\nederiz.\pŞimdi size ÇOKLU SAVAŞ ODA'nızı\ngöstereceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "Ben {STR_VAR_1}'in no. {STR_VAR_2}\nçırağıyım. Bana {STR_VAR_3}\ldiyebilirsin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "{STR_VAR_1}'in tavsiyesi üzerine,\n{STR_VAR_2} ile birlikte bir\l{STR_VAR_3} getirdim ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pLütfen, size takım olarak katılmama\nizin verin.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "Teşekkür ederim! Şimdi gidip kayıt\nolacağım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "Seninle bir takım kurmayı gerçekten\nçok istiyordum, {PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "Ben {STR_VAR_1}'in no. {STR_VAR_2}\nçırağıyım. Benim adım {STR_VAR_3}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "{STR_VAR_1}'den tavsiye aldım ve\n{STR_VAR_2} ile bir {STR_VAR_3}\lseçtim ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pLütfen, bir tag team oluşturalım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "Çok teşekkür ederim! Kayıt işlemini\nçabucak halledeceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{PLAYER}, seninle ortak olmayı\numuyordum…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "Benim adım {STR_VAR_3} ve ben\n{STR_VAR_1}'in no. {STR_VAR_2}'nin\lçırağıyım.\pOf.\pÖzür dilerim! Bu gerilim beni ağlatıyor.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "{STR_VAR_3} bana tavsiyede bulundu,\nbu yüzden {STR_VAR_1} ile bir\l{STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pÖff… Lütfen, lütfen benimle takım\nol!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "Oh, gerçekten mi? Yapacak mısın?\nHarika! Fena! Awoooh!\pOh… Özür dilerim… Çok mutluyum,\nağlıyorum…\pHemen gidip kayıt yaptıracağım. Lütfen\ngitme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "Oh, a-ama…\nOf… Vaaaaah!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "Merhabalar! Ben {STR_VAR_3}! Ben\n{STR_VAR_1}'in no. {STR_VAR_2}'nin\lçırağıyım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "{STR_VAR_3} ekibimi tavsiye etti. Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}, sahip\nolduğum şey bu! Güzel, değil mi?\pHadi bakalım! Bir tag team oluşturalım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "Yaşasın! Harika! Tamam, gidip kayıt\nolacağım, tamam mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "Aaa, neden? Takım olmak istedim,\n{PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "Ben {STR_VAR_3}, ünlü {STR_VAR_1}'in\nÜnlü {STR_VAR_1}'in {STR_VAR_2}\lçırağıyım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "Tavsiye için {STR_VAR_3}'e baktım. Bir\n{STR_VAR_1} - {STR_VAR_2} kullanarak$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "ve bir {STR_VAR_1} ile bir\n{STR_VAR_2}, işte benim çiftim.\pLütfen, bana bir etiket takımında\nkatılır mısınız?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "Teşekkür ederim! Hemen kayıt\nolacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "Sana bir takımda katılmayı umuyordum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "Um… Benimle konuşmak için zaman\nayırdığınız için içtenlikle mutluyum.\pBen {STR_VAR_3}. Ben {STR_VAR_1}'in\nno. {STR_VAR_2}'nin çırağıyım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "{STR_VAR_3} bana tavsiye verdi. Bunun\niçin çok minnettarım.\p{STR_VAR_1} ve {STR_VAR_2} ile\nbirlikte bir {STR_VAR_2} ekibim var.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}. Çok\nşey istediğimin farkındayım…\pİsteyeceğinizi sanmıyorum ama size\nortak olarak katılabilir miyim?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "Gerçekten mi? Buna inanamıyorum! Size\nkatılmama izin verdiğinize\linanamıyorum! Seni hayal kırıklığına\luğratmayacağım!\pUm… Eğer gerçekten sorun değilse,\nhemen şimdi kayıt olacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "Oh… Yeterince iyi olduğumu\ndüşünmemiştim…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "Merhaba, ben {STR_VAR_3}. Ben\n{STR_VAR_1}'in no. {STR_VAR_2}'nin\lçırağıyım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "{STR_VAR_3} bana şu takımı kurmamın\niyi olacağını söyledi: {STR_VAR_1}\lkullanan bir {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "ve {STR_VAR_1}'in nasıl\nkullanılacağını bilen bir {STR_VAR_2}.\pFena değil, ha? Seninle takım olmamı\nister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "Tamam, size katıldığıma sevindim!\nUmarım benim için işleri\lkarıştırmazsın! Şimdi kaydımı\lyapacağım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "Ne? Neden beni geri çevirdin? Sen\nkarakter yargıcı değilsin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "Ben {STR_VAR_3} ve bir TRIATHLETE'im.\nHer gün koşu, antrenman ve rap\lyapmakla meşgulüm.\pAynı zamanda {STR_VAR_1}'in no.\n{STR_VAR_2}'nin çırağıyım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "Bu {STR_VAR_3}'ün önerdiği şeydir.\nBir {STR_VAR_1} - {STR_VAR_2}\lkullanarak$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "ve {STR_VAR_1} kullanan bir\n{STR_VAR_2}.\pMeşgul olmama rağmen onları\nyetiştirmek için çok çaba sarf\lediyorum.\pHadi bir ekip oluşturalım ve deneyelim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "Teşekkürler, işte ruh bu! Ben kayıt\nyaptırırken sıkı dur, tamam mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "Burada olmak için yoğun programımdan\nzaman ayırdım! Bana bir mola verin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "Merhaba! Nasıl gidiyor?\pBen {STR_VAR_3}, {STR_VAR_1}'in no.\n{STR_VAR_2}'nin çırağıyım. Sizinle\ltanıştığıma memnun oldum!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "Dinleyin, dinleyin! Tavsiye edilen\nPOKéMON {STR_VAR_3} hakkında bir\lşeyler duymalısınız. Bir {STR_VAR_2}\lile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\nElbette onları mükemmel bir şekilde\lyetiştirdim!\pPeki, takım olmak ister misin? Harika\nbir kombinasyon olacağına eminim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "Yaşasın, bence bu eğlenceli olacak!\nGidip kayıt olacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "Oh, çok kötüsün! Tavsiye üzerine\ngeldim, biliyorsun.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "Lütfen kendimi tanıtmama izin verin.\nBen {STR_VAR_3}.\p{STR_VAR_1}'in numarası olarak hizmet\nveriyorum. {STR_VAR_2}'nin çırağıyım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "{STR_VAR_3}'ün bilge tavsiyesine\nbaşvurdum ve {STR_VAR_1} ile\l{STR_VAR_2}'den oluşan ekibimi\lkurdum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "ve {STR_VAR_1} ile bir {STR_VAR_2}.\pLütfen benimle takım olmayı kabul edin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "Oh… Çok sevindim! Elimden geleni\nyapacağıma söz veriyorum!\pElbette bizi kaydettireceğim! Lütfen\nbekleyin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "Ben de sana katılmayı umuyordum,\n{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "Eek! Benimle konuştun! Ben… Ben çok\nsevindim!\pBen {STR_VAR_3}'üm! Ben\n{STR_VAR_1}'in no. {STR_VAR_2}'nin\lçırağıyım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "{STR_VAR_3}'ün tavsiyesi üzerine,\n{STR_VAR_2} kullanarak bir\l{STR_VAR_1} eğittim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "ve bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak.\pLütfen, dileğimi yerine getirebilir\nmisiniz? Senin takım arkadaşın olmak\listiyorum!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "Eek! Başım dönüyor! Çok teşekkür\nederim! Hemen gidip kaydımızı\lyaptıracağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "Waaah! Hiç acımıyor musun? Ama bu seni\ndaha havalı yapıyor.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "Yeehaw! Ben {STR_VAR_1}'in no.\n{STR_VAR_2} çırağıyım!\pBenim adım {STR_VAR_3}, merhaba,\nmerhaba!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "Akıl hocam {STR_VAR_3} bir\n{STR_VAR_1}-usta {STR_VAR_2}\ltavsiye etti$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "ve bir {STR_VAR_1}-master\n{STR_VAR_2}.\pİyi iş, ha? Benimle ortak olacaksın,\ndeğil mi?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "Tamam, mükemmel! Kayıt işlemlerini\nhemen halledeceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "Gwaaah! Sen hesapçı birisin, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "Hey! Büyük bir sorun var! Bu BATTLE\nTOWER'ın son günü!\p… … … … … … Sadece şaka\nyapıyorum!\pİnsanlar bana {STR_VAR_3} diyor ve\nben de diyorum! Ben {STR_VAR_1}'in\l1000. çırağıyım! Aslında, ben hayır.\l{STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "{STR_VAR_3} bana bazı tavsiyelerde\nbulundu. {STR_VAR_1} ile {STR_VAR_2}\lve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "{STR_VAR_1} ile {STR_VAR_2}. Her\ntürden on tane var! Aslında, her\lbirinden sadece bir tane!\pNe dersiniz? Benimle etiket\nsavaşlarını denemek ister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "Yaşasın! Teşekkür olarak sana bir\nPOKéMON vereceğim!\pŞaka yapıyorum! Ama gerçekten gidip\nkayıt yaptıracağım, tamam mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "Oh, bu çok soğuk! Bunun için BATTLE\nTOWER'ı yıkmam gerekecek!\pTabii ki yıkmayacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "Hey, orada, sallanıyorum ve\nyuvarlanıyorum! POKéMON, kontrol\lbende!\pBen {STR_VAR_3} rappin' SAILOR. Beni\nferyat eden biriyle karıştırmayın!\pBen {STR_VAR_1}'in hayır'ıyım.\n{STR_VAR_2}'nin çırağıyım. Beni\lkovmak için acele etmemelisin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "{STR_VAR_3}'ün tavsiyesi ile Uydum,\ngurur ekibimi bir araya getirdim! Bir\l{STR_VAR_1} - {STR_VAR_2} kullanarak$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "ve bir {STR_VAR_1} kullanan\n{STR_VAR_2}!\pToplantımızı, kutlamak için bir takım\nzaferiyle anmalıyız!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "Hey, hey, tarzını beğendim! Kaydımız,\ndosyaya gideceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "Oh, hey, {PLAYER}, işte bu soğuk! Eğer\nbu kadar cesur olabilirsem!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "Yippee-yahoo! Oh, kaçma! Sadece\neğleniyordum!\pMerhaba! Ben {STR_VAR_3}! Ben\n{STR_VAR_1}'in no. {STR_VAR_2}'nin\lçırağıyım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "{STR_VAR_3} bana ne yapmam\ngerektiğini söyledi. Yani bir\l{STR_VAR_1} - {STR_VAR_2} kullanarak$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "ve bir tane {STR_VAR_1} kullanarak\n{STR_VAR_2} seçtim.\pPeki, ne diyorsunuz? Hadi, günümü\ngüzelleştir!\pLütfen, sana yalvarıyorum! Size\nkatılmama izin verin, beni mavi\lbırakmayın!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "Evet! Şans benimle! Bu beni kesinlikle\nmutlu ediyor!\pMücadeleye katılmadan önce, hemen\nkayıt yaptıracağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "Beni geri mi çeviriyorsun? Kaşlarımı\nçattırıyorsun!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "Öksürük!\pÜzgünüm, üşütmüşüm. Ama POKemon'um\niyi.\pBenim adım {STR_VAR_3},\n{STR_VAR_1}'in no. {STR_VAR_2}\lçırağıyım. Öksür!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "{STR_VAR_3}'ün tavsiyesini dikkate\naldım ve {STR_VAR_1} ile\l{STR_VAR_2}'den oluşan ekibimi bir\laraya getirdim ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pOnları her gün çalıştırdım, rüzgarda ve\nyağmurda bile.\pSanırım bu yüzden soğuk algınlığım var.\pİşte ben buyum. Eşim olmak ister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "Teşekkürler, minnettarım! Öksür,\nöksür! Ben kayıt olurken bekleyin.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "Oh, yapmayacak mısın? Bence iyi bir\nçift oluruz.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "Oh, merhaba! Bu sinir bozucu.\pBen {STR_VAR_3}. Ben {STR_VAR_1}'in\n{STR_VAR_1}'in {STR_VAR_2} numaralı\lçırağıyım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "{STR_VAR_3} bu takımın iyi olacağını\nsöyledi-- bir {STR_VAR_2} ile\l{STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pBu konuda kendimi mahcup hissediyorum\nama size katılmama izin verir misiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "Oh, Tanrım, teşekkür ederim! Utangaç\nhissediyorum ama elimden geleni\lyapacağım!\pGidip kayıt işlemlerini halledeyim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "Oh, lütfen hayır deme! Zaten yeterince\nutangaç hissediyorum…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "Ben {STR_VAR_3}'üm ve bu yalan değil.\nBen {STR_VAR_1}'in no.\l{STR_VAR_2}'nin çırağıyım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "{STR_VAR_3} ekibimi tavsiye etti.\pTavsiye kulağa samimi geldiğinden,\n{STR_VAR_1}'ımı yanımda getirmeye\lkarar verdim - {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "benim {STR_VAR_1}- kullanarak\n{STR_VAR_2}.\pEğer mümkünse, beni takım arkadaşın\nolarak kabul etmeni istiyorum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "Beni gerçekten kabul edecek misin?\nAksi halde çok kötü olurdu.\pAma kabul ettiğine göre, sorun yok.\nGidip ikimizi de kaydettireceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "Hm? Şimdi neden reddediyorsun? Bu\nsenin şaka anlayışın mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "Ben {STR_VAR_1}, ve ben bir LASS'ım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "Elimde {STR_VAR_1} kullanan bir\n{STR_VAR_2} ve bir$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{STR_VAR_1} kullanan {STR_VAR_2}.\nBunlar benim yanımda olanlar.\pOrtağım olur musun?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "Teşekkür ederim! Gidip kayıt\nyaptıracağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "Ortağım olmak istemiyor musun? Sonra\npişman olacaksın!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "Merhaba!\pBen GENÇ {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "Elimde ne olduğunu bilmek ister\nmisiniz? Bir {STR_VAR_2} ile\l{STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pBenim takım arkadaşım olacaksın, değil\nmi?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "Yaşasın! Gidip kayıt olacağım, tamam\nmı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "Aaa! Eğer POKéMON'umla bir tag team\nkurarsan, durdurulamaz oluruz!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
	.string "Yahoo! Ben HIKER {STR_VAR_1}'ım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "Yanımda ne var biliyor musunuz? Benim\n{STR_VAR_1} - {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "benim {STR_VAR_1} kullanan\n{STR_VAR_2}!\pKulağa hoş geliyor, değil mi? Bir tag\nteam oluşturmak ister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "Yahoo! Gidip kayıt yaptırayım o zaman.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "Yanımda seninle savaşmak isterdim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "Merhaba! Ben {STR_VAR_1}, ve ben bir\nGÜZELİM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "Neyi yükselttiğimi biliyor musunuz? Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pSiz ne düşünüyorsunuz? Birlikte bir\ntag team yapmak ister misiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "Harika! Şimdi kayıt işlemlerini\nhalledeceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "Ne büyük hayal kırıklığı!\pİkimiz birlikte en iyisi olurduk!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "Hey!\pKim olduğumu biliyor musun? Ben\n{STR_VAR_1} BALIKÇIYIM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "Yanımda {STR_VAR_1} kullanan bir ekip\nvar - {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak.\pEe, ne dersin? Benim yanımda savaşacak\nmısın?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "Güzel, güzel! Bana bırakın!\pŞimdi gidip bizi kaydettireceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "Biz de mükemmel bir şekilde eşleştik.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "Sizinle tanıştığıma memnun oldum. Ben\n{STR_VAR_1}, bir LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "Bana {STR_VAR_1} ve {STR_VAR_2}'den\noluşan bir ekip eşlik ediyor.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pUmarım onayınızı alırım. Çünkü seni\nortağım olarak görmek istiyorum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "Size içtenlikle teşekkür ederim. Kayıt\nişlemlerini ben halledeceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "Eminim ki beni ortağın olarak\nalmadığına pişman olacaksın.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "Ben TRIATHLETE {STR_VAR_1}'im!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "Elimde ne var… {STR_VAR_1} ile bir\n{STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}! Bu\nbenim çiftim!\pLütfen? Benimle bir tag team oluşturur\nmusun?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "Teşekkürler! Gişeye gidip kayıt\nyaptıracağım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "İkimiz birlikte olsaydık, kesinlikle çok\nzorlanırdık!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "Merhaba! Ben BUG CATCHER\n{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "Bakın bende ne var! Bir {STR_VAR_2}\nile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pDinleyin! Bir tag team oluşturmak\nister misiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "Yakaladım seni!\pGidip gişede kayıt işlerini halledeyim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "POKéMON'um harika. Umarım pişman\nolmazsın!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "İyi günler! Ben OKUL ÇOCUĞU\n{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "Yükseltmekte olduğum şey,\n{STR_VAR_1} kullanan bir {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "ve {STR_VAR_1} kullanan bir\n{STR_VAR_2}.\pÇok da kötü değil, öyle değil mi? Bir\netiket takımı oluşturmak ister\lmisiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "Çok teşekkür ederim! Kayıt işlemlerini\nhalledeceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "Bu çok kötü.\pOrtağınız olarak sizden bir şeyler\nöğrenebileceğimi umuyordum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "Hey! Sana kim olduğumu söyleyeyim! Ben\nZENGİN ÇOCUK {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "Tahmin edin ne buldum! Bir {STR_VAR_2}\nile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pSana benimle bir tag team'de olma\nşansını sunmaya hazırım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "Akıllıca bir hareket!\pKayıt işlemini çabucak bitireceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "Onca insan arasından beni geri mi\nçevireceksin? Bu kararından kesinlikle\lpişman olacaksın!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "Hiyah! Ben SİYAH KUŞAK\n{STR_VAR_1}'ım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "Arkadaşlarım olarak, {STR_VAR_1}\nkullanan bir {STR_VAR_2} var.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "ve {STR_VAR_1} kullanarak bir\n{STR_VAR_2}.\pLütfen, dileğimi yerine getirin! Senin\netiket ortağın olmama izin ver!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "Hiyah! Hemen gidip kayıt yaptıracağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "Anlıyorum… Umarım bir dahaki\ngörüşmemizde bir fırsat olur…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "Merhabalar! Ben {STR_VAR_1}, ve ben\nbir TUBER'ım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "Elimde ne olduğunu söyleyeyim. Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\nLütfen takımınızda yer alabilir miyim?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "Teşekkür ederim! Şimdi gidip bizi\nkaydettireceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "Eğer ortak olsaydık, çok güçlü\nolabilirdik!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "Selamlar… Ben HEX MANIAC\n{STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "Yanımda bir {STR_VAR_1} ile birlikte\n{STR_VAR_2} kullanan bir {STR_VAR_1}\ltaşıyorum$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "{STR_VAR_1}-kullanarak\n{STR_VAR_2}…\pSana yalvarıyorum… Bana bir takımda\nkatıl…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "Teşekkür ederim… Bizi\nkaydettireceğim…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "Size katılmayı çok istedim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "Nasılsınız? Ben {STR_VAR_1}, ve ben\nbir POKéMON ÜRETİCİSİYİM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "İyi birkaç tane yetiştiriyorum! Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pNe dersiniz? Benimle bir tag team\nyapmak ister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "Çok teşekkür ederim!\pBen gidip kayıt işlerini halledeyim, siz\nburada bekleyin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "Senin ortağın olmayı dört gözle\nbekliyordum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "Pekala, merhaba! Ben TRIATHLETE\n{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "Ne ile çalıştığımı bilmek ister misiniz?\nBir {STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pEee? Benimle takım olmak ister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "İyi gidiyorsun!\pÇabuk olacağım ve kayıt işlemlerini\ntamamlayacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "Sen ve ben, en iyisi olurduk. Bu çok\nkötü.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "Hey, oradaki! Benim adım {STR_VAR_1}!\nBen bir TRIATHLETE'im!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "Dayanıklı ekibimle koşulara çıkıyorum -\nbir {STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pHiç fena değil, ha? Birlikte bir etiket\ntakımında olmalıyız!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "Tamamdır! Hemen gidip kaydımı\nyaptıracağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "Senin takım arkadaşın olarak\nsavaşmayı çok isterdim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "Ben BATTLE GIRL {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "Bir {STR_VAR_1}'i {STR_VAR_2}\nkullanarak güçlendiriyorum ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak!\pBu kombinasyonu beğendin mi? Sen ve\nben birleşmeye ne dersin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "Teşekkürler!\pKayıt işlemlerini hemen halledeceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "Seninle en iyi takımı kurabileceğimizi\ndüşünmüştüm.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "Ben TRIATHLETE {STR_VAR_1}'im!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "{STR_VAR_1}'i nasıl kullanacağını bilen\nbir {STR_VAR_2} ile çalışıyorum$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "ve {STR_VAR_1} ile bir {STR_VAR_2}!\pBir tag team olabiliriz. Harika olmaz\nmıydı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "Teşekkür ederim!\pGidip kaydımızı yaptıracağım, hemen\nşimdi!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "Aaa, bu çok kötü. Etraftaki en zorlu\ntakım biz olurduk!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "Ben mi? Ben TUBER {STR_VAR_1}'ım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "Yanımda ne var? Bir {STR_VAR_2} ile\n{STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pHey? Benimle takım olacaksın, değil mi?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "Tamam! Tamam!\pGidip kayıt olacağım! Birlikte mükemmel\nolalım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "Benim POKéMON'um kesinlikle zor…\nTakım olmak istememen çok kötü.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "Yay-hey! Bana GİTARİST {STR_VAR_1}\ndeyin!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "Maiyetime bir bakın! Bir {STR_VAR_2}\nile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pYay-hey! Oldukça vahşi, değil mi? Takım\nhalinde düet yapmamız gerekecek!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "Yay-hey! Tamamdır! Kayıt işlemlerini\nşimdi yapacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "POKéMON'um taş gibi! Pişman olacaksın,\nsana söylüyorum!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "Sizinle tanıştığıma memnun oldum. Ben\n{STR_VAR_1}, bir BEYEFENDİYİM.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "Güvenilir {STR_VAR_1}'ım bana eşlik\nediyor - {STR_VAR_2}'yi kullanarak ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak.\pBir takım ortaklığı düzenlemesinde\nbana katılmanızı rica edebilir miyim?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "Güveniniz için teşekkür ederim. Kayıt\nişlemlerini tamamlayacağım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "Bu çok talihsiz bir durum.\pBir sonraki fırsatı dört gözle\nbekleyeceğim…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "Merhaba, ben {STR_VAR_1} ve bir\nPOKéFAN'ım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "Şu anda yanımda {STR_VAR_1}\nhareketini bilen bir {STR_VAR_2} var\lve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pGördüklerini beğendin mi? Neden benim\netiket ortağım olmuyorsun?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "Teşekkür ederim! Kayıtla\nilgileneceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "Benim POKéMON'um birinci sınıftır…\nBunu takdir edememeniz çok kötü.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "Hm! Ben {STR_VAR_1}, ve bir UZMAN'ım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "Güçlendirdiğim POKéMON bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pBenimle tag team yapmaya ne dersin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "Hm! Bizi hemen kaydettireceğim! İkimiz\nde elimizden geleni yapalım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "Umarım seçiminiz gerçekten doğrudur…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "Merhaba, merhaba. Ben {STR_VAR_1}, ve\nben bir UZMAN'ım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "POKéMON'umu iyice büyüttüm. Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}--\nelimdekiler bunlar.\pBenimle takım olmak istemez misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "Güzel, güzel. Hemen kayıt işlemlerini\nhalledeceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "Belki bir dahaki buluşmamızda bir ekip\noluşturabiliriz.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "Ben EJDERHA TAMACISI {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "Güçlendirdiğim takım bir {STR_VAR_2}\nile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pNe dersin? Ortağım olmak ister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "Tamam, elimden geleni yapacağım! Şimdi\ngidip kayıt olacağım, tamam mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "Benden daha sert bir ortak\nbulamazsınız!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "Ben KUŞ TUTUCUYUM {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "Elimde hangi POKéMON var? Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pSence de iyi bir takım olmaz mıyız?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "Harika, teşekkürler! Kayıt\nişlemleriyle ilgileneceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "POKéMON'um ve ben güçlüyüz. Ne hayal\nkırıklığı.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "Ben NINJA BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "POKéMON takımım bir {STR_VAR_2} ile\n{STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pHadi birlikte bir tag team'de olalım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "Yaşasın! Gidip kayıt olayım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "Benim sert POKéMON'umu yanınıza\nalmadığınız için pişman olacaksınız!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "Merhaba! Ben PARASOL LADY\n{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "Şimdi bana eşlik eden {STR_VAR_1}\nkullanan {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "{STR_VAR_1} kullanan bir {STR_VAR_2}.\pGüzel değiller mi? Bir etiket takımında\nbize katılmak ister misiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "Çok teşekkürler!\pGidip gişede kayıt yaptıracağım.\nBirbirimizi hayal kırıklığına\luğratmayalım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "POKéMON'um muazzam derecede güçlü.\nNe kadar hayal kırıklığı…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "Merhaba. Ben {STR_VAR_1}, ve ben bir\nBUG MANIAC'ım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "POKéMON'umu buldum, evet. Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}--\nbulduklarım bunlar.\pBir tag team oluşturabilir miyiz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "Tamam! Tamam! Anlaşıldı!\pKayıt için geç kalmayacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "Bulduğum POKéMON ile kaybetmezdik.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "Ahoy, oradakiler! Ben SAILOR\n{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "Size gurur ve neşe kaynağımı\ngöstereyim! Bir {STR_VAR_2} ile\l{STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pTabii ki beni geri çevirmeyeceksin.\nTakım olacağız, değil mi?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "Daha azını beklemiyordum! Şimdi gidip\nkayıt yaptıracağım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "Muhalefeti darmadağın edebilirdik! Çok\nkötü!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "Merhaba, ben {STR_VAR_1}. Ben bir\nKOLEKSİYONCUYUM.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "Koleksiyonumdaki mücevherler\n{STR_VAR_1} ile {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pHarika, değil mi? Birlikte bir takımda\nolmalıyız.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "Oh, evet!\pZaman kaybetmeyelim. Gidip ikimizi de\nkaydedeceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "Bu çok üzücü. POKéMON'umu takdir\netmiyorsun.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "Merhaba, ben {STR_VAR_1}. Ben bir\nPOKéMON RANGER'ım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "Bana eşlik eden {STR_VAR_1} kullanan\nbir {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pSence de etkileyici bir takım olmaz\nmıyız?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "Bu süper! Şimdi kayıtla ilgileneceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "Bir dahaki sefere POKéMON'umu seç,\nolur mu?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "Benim adım {STR_VAR_1}. Ben bir\nPOKéMON RANGER'ım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "Size ekibimden bahsedeyim. Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pKüçük ekibimle bir tag team\noluşturmaya ne dersiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "Elimizden gelenin en iyisini yapacağız!\nKayıt işlemlerini hemen halledeceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "Umarım bir dahaki sefere benim\nPOKéMON'umu seçersiniz.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "Tanıştığımıza memnun oldum. Ben\n{STR_VAR_1}. Kendimi bir AROMA BAYANI\lolarak görüyorum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "{STR_VAR_1} kullanan bir {STR_VAR_2}\nile seyahat ediyorum ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "{STR_VAR_1} kullanan bir {STR_VAR_2}.\pUmarım ilginizi çekerler. Ortağım olmak\nister misiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "Kabulünüz beni onurlandırdı. Hemen\ngidip kaydımı yaptıracağım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "Bir dahaki buluşmamızda bir takım\noluşturabilirsek harika olur.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "Kim olduğumu bilmek ister misin? Ben\n{STR_VAR_1}, RUIN MANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "Yanımda bulunan POKéMON'lar\n{STR_VAR_1} ile bir {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pİlgi çekici, değil mi? Sen ve ben ortak\nolmaya ne dersin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "Doğru bir karar! Gidip kayıt\nevraklarını halledeyim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "Hmm… Sanırım benim POKéMON'um sert…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "Ben COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "Şu anda sahip olduğum POKéMON bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\nGüzel, değil mi?\pSence de bir tag team yapsak çok\nhavalı olmaz mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "Harika! Hemen gidip kayıt işlemlerini\nyapacağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "Gelmiş geçmiş en iyi takım olacağımızı\ndüşünmüştüm.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "Ben COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "Yetiştirmekte olduğum takımda\n{STR_VAR_1} ile bir {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pKulağa hoş geliyor mu? Etiket ortağı\nolmaya ne dersiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "Kulağa hoş geliyor! Kayıt yaptırsam iyi\nolacak.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "Ne kadar zorlu bir takım olacağımızı\ndüşünüyordum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "Heyo! Ben {STR_VAR_1}, POKéMANIAC!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "Benim gibi bir adamın nesi var? Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}, işte\nbu!\pHadi yapalım şu işi! Bir tag team olarak\netrafta dolanacağız!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "İyi karar! İkimizi de kaydettireceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "Benim POKEMON'um acımasızdır! Pişman\nolursan bu benim suçum değil!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "Hey, oradaki! Ben KINDLER\n{STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "Eğitimimin ne ortaya çıkardığını\nbiliyor musunuz? Bir {STR_VAR_2} ile\l{STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pPeki, ne diyorsunuz? Bir tag team\noluşturmak ister misin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "Tamamdır! Kayıt işlemlerini\nhalledeceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "Bir dahaki sefere karşılaştığımızda\nbenimle ortak olacağına söz ver.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "Ben {STR_VAR_1}, ve ben bir\nKAMPÇIYIM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "Bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak ve bir$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "{STR_VAR_1} - {STR_VAR_2}\nkullanarak.\pSence takım olmak eğlenceli olur mu?\nEminim eğlenceli olur!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "Evet! Kayıt olmaya gidiyorum!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "Bir dahaki sefere, tamam mı? Senin\ntakımında olmak istiyorum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "Merhaba! Ben {STR_VAR_1}, ve ben bir\nPİKNİKÇİYİM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "Aldığım POKéMON bir {STR_VAR_2} ile\n{STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pBenimle bir takıma katılmak ister\nmisin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "Teşekkür ederim! Kaydı şimdi\nyapacağım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "Başka bir zaman size katılabilirsem iyi\nolur.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "Ben PSİKİYATRİSTİM {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "Yetiştirdiğim ikili, {STR_VAR_1} ile bir\n{STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pBenimle bir tag team oluşturmak ister\nmisin?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "Tabii ki! Kayıt işlemlerini ben\nhallederim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "Eğer tekrar karşılaşırsak, o zaman\nseninle takım olmak isterim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "Ben {STR_VAR_1}. Ben bir\nPSİKİYATRİSTİM.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "Bir {STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}--\nonlar benim öğrencilerim.\pBir tag-team ortaklığı kurma fikri\nilginizi çekmiyor mu?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "Teşekkür ederim. Gidip kayıt\nişlemlerini halledeyim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "Umarım bir ittifak kurmak için bir şans\ndaha olur.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "Ben OKUL ÇOCUĞUYUM {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "Bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "ve bir {STR_VAR_1} kullanan\n{STR_VAR_2} benim POKéMON çiftim.\pLütfen takım arkadaşınız olabilir\nmiyim?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "Ooh, teşekkür ederim! Hemen gişede\nkaydımı yaptıracağım!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "Lütfen? Bir dahaki sefere size\nkatılabilir miyim?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "Merhaba! Adım {STR_VAR_1}! Ben bir\nPOKéMON ÜRETİCİSİYİM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "Yükselttiğim POKéMON, {STR_VAR_1}\nkullanan bir {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak.\pKulağa ilginç geliyor mu? O zaman bir\netiket takımı oluşturmaya ne dersiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "Tamamdır! Kayıt işini bana bırak!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "Bir dahaki sefere benimle takım\nolmalısın, tamam mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "Ben {STR_VAR_1} ve bir POKéFAN\nolduğumu söylemekten gurur\lduyuyorum.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "Yetiştirdiğim sevgili POKéMON'lar\n{STR_VAR_1} ile bir {STR_VAR_2} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}.\pÇok şirinler, değil mi? Bir takım\nyapmalıyız!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "Teşekkür ederim, canım! Kayıt olmaya\ngidiyorum!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "Sevgili POKéMON'um en iyisidir, bilmeni\nisterim. Ne kadar sinir bozucu!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "Merhaba, ben SWIMMER {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "Bir {STR_VAR_1} - {STR_VAR_2}\nkullanarak$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "ve bir {STR_VAR_1} kullanan\n{STR_VAR_2} benim eğittiklerim.\pSen ve ben, bir takım olalım.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "Bu harika! İkimizi de kaydettireceğim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "Eğer tekrar karşılaşırsak, bana bir\ntakım borçlusun!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "Neler oluyor? Ben {STR_VAR_1}, ve ben\nbir TRIATHLETE'im.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "Birkaç tane düzgün POKéMON'um var.\nBir {STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pBirlikte bir tag team yaparsak harika\nolur, ne dersiniz?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "Tamamdır! Ben kayıt olurken sen bekle,\ntamam mı?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "Bir dahaki sefere size katılmama izin\nvereceğinizi umuyorum, nasıl olur?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "Ben TRIATHLETE {STR_VAR_1}'im!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "Bir {STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "{STR_VAR_1}'in nasıl kullanılacağını\nbilen başka bir {STR_VAR_2}. Bu benim\lçiftim.\pSiz ne düşünüyorsunuz? İyi bir takım\nolduğumuzu söyleyebilirim.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "Bu cevabı sevdim! Kayıt işlemlerini\nçabucak bitireceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "Ortaklık kurmam için bana bir şans\ndaha vereceksiniz, değil mi?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "Merhaba! Merhaba! Ben {STR_VAR_1},\nve ben bir YÜZÜCÜYÜM!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "Ne yetiştirdiğime bir bakın! Bir\n{STR_VAR_2} ile {STR_VAR_1} ve$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "bir {STR_VAR_2} ile {STR_VAR_1}!\pGüzel, değil mi? Bir takım oluşturmak da\ngüzel olurdu!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "Çok minnettarım! Bu kayıt işini\nhalledeceğim!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "Eğer tekrar karşılaşırsak, benimle\ntakım olmalısın. Bunu yapacaksın, değil\lmi?$"


