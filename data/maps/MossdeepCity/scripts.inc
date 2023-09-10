.set LOCALID_GRUNT_1, 10
.set LOCALID_GRUNT_2, 11
.set LOCALID_GRUNT_3, 12
.set LOCALID_GRUNT_4, 13
.set LOCALID_MAXIE, 14
.set LOCALID_SCOTT, 16

MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM08, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM08, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement OBJ_EVENT_ID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "Bunu STEVEN'dan aldım ama ne işe\nyaradığını bilmiyorum.\pSanırım adı KRAL KAYASI.\nİster misin?$"

MossdeepCity_Text_YouCanKeepIt:
	.string "Neden istiyorsun ki?\NTuhaf birisin.\pSende kalabilir ama STEVEN'dan sır\nolarak sakla.$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "STEVEN'ın evi tam şurada!$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "Evet, sen de öyle düşünüyorsun!\nGarip bir taşla ne yapacaksın ki?$"

MossdeepCity_Text_WailmerWatching:
	.string "MOSSDEEP'in etrafında vahşi şeyleri\ngörebilirsin.\pAdı neydi…\nEe…\pWAİ, WAİ, WAİ…\pWAİLMER!$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "Adanın UZAY MERKEZİ, devasa roketler\nfırlatıyor.\pSon zamanlarda aldıkları bir mektup\nyüzünden bir tür kargaşa var.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "Adanın UZAY MERKEZİ, devasa roketler\nfırlatıyor.$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "Bir denizci dostumdan AQUA'nın\nLİLYCOVE'da dükkan açtığını duydum.\pAyrıca birinin gelip onları yere\nserdiğini de duydum!\pAma buradaki MOSSDEEP, MAGMA TAKIMI\ntarafından hedef alındı.\pNeyin peşinde olduklarını öğrenmek\nistiyorsan, UZAY MERKEZİ'ni ziyaret et.$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "Ben bir denizciyim, bu yüzden deniz\nbenim için daha önemli.\pAma biliyor musun? Uzun bir\nyolculuktan sonra karaya döndüğümde\lrahatladığımı hissediyorum!$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "Tüm dünya bu ada gibi bitki ve\nçiçeklerle kaplı olsaydı keşke.$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "Tüm canlıların, her ne kadar evlerini\nkarada yapsalar da yaşamlarını devam\lettirebilmesi için denize ihtiyacı\lvardır.\pCanlılar, ömrünü tamamladıktan sonra\ntoprak olur ve karaya geri döner.\pVe deniz her zaman karayla\nbağlantılıdır.\pEvet, tıpkı buradaki kıyı şeridi gibi.$"

MossdeepCity_Text_SurfExhilarating:
	.string "Gemide yolculuk iyidir.\pAma POKéMON ile denizi SÖRF kullanarak\ngeçmek…\pİşte bu heyecan verici bir yolculuk!\nSence de öyle değil mi, genç?$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "Bu taşın, UZAY MERKEZİ'ndeki insanlar\niçin özel bir anlamı var.\pRoketlerinin güvenli bir şekilde\nuçmasını diledikleri için buraya\lkoydular.\pBir dilek tuttuğunda ne\nkullanırsın? Bir yıldızdan mı dilek\ldilersin?\pGerçekleşmesi için bir dilek etiketi\nkullanıyorum. Yaptığım şey bu.$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "Bu, beyaz bir kaya.$"

MossdeepCity_Text_GymSign:
	.string "MOSSDEEP ŞEHRİ POKéMON SALON\nLİDERLERİ: LIZA & TATE\pMistik kombinasyon!$"

MossdeepCity_Text_CitySign:
	.string "MOSSDEEP ŞEHRİ\n"
	.string "Sloganımız: POKéMON'ları sevin!$"

MossdeepCity_Text_SpaceCenterSign:
	.string "MOSSDEEP UZAY MERKEZİ\nUzaya en yakın yer.$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "İyi misin?\nBen harikayım!\pMOSSDEEP'in SALON LİDERİ'nin\noldukça güçlü olduğunu duydum, bu yüzden\lgelip kendim görmeye karar verdim.\pAma bu kasabada yanlış giden bir\nşeyler var.\pİnsanlar bir uyarı mektubundan ve\nUZAY MERKEZİ'nden bahsediyor.\pYine de bunun beni ilgilendirdiğini\nsanmıyorum.$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Ahh… Dalgaların ayaklarımı yıkamasına\nizin vermek harika hissettiriyor…\pDalgalardan bahsetmişken, şu ada şehri\nSOOTOPOLİS'i biliyor musun?\pSanırım oradaki salona yeni bir\nLİDER geldi.\pİnsanlar bana yeni liderin bir zamanlar\nWALLACE'a akıl hocalığı yaptığını\lsöylüyor.$"


