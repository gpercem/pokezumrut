.set LOCALID_LITTLE_BOY, 5

Route119_WeatherInstitute_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119_WeatherInstitute_1F_OnTransition
	.byte 0

Route119_WeatherInstitute_1F_OnTransition:
	call_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos
	end

Route119_WeatherInstitute_1F_EventScript_SetLittleBoyPos::
	setobjectxyperm LOCALID_LITTLE_BOY, 0, 5
	setobjectmovementtype LOCALID_LITTLE_BOY, MOVEMENT_TYPE_FACE_RIGHT
	return

Route119_WeatherInstitute_1F_EventScript_LittleBoy::
	lock
	faceplayer
	special GetPlayerBigGuyGirlString
	goto_if_eq VAR_WEATHER_INSTITUTE_STATE, 0, Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere
	msgbox Route119_WeatherInstitute_1F_Text_WowYoureStrong, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LittleBoyTeamAquaHere::
	msgbox Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker1::
	lock
	faceplayer
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route119_WeatherInstitute_1F_EventScript_StudyingRain
	setvar VAR_0x8004, 0
	call_if_set FLAG_DEFEATED_KYOGRE, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	call_if_set FLAG_DEFEATED_GROUDON, Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated
	goto_if_eq VAR_0x8004, 2, Route119_WeatherInstitute_1F_EventScript_StudyingRain  @ Both defeated
	msgbox Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_LegendaryDefeated::
	addvar VAR_0x8004, 1
	return

Route119_WeatherInstitute_1F_EventScript_StudyingRain::
	msgbox Route119_WeatherInstitute_1F_Text_ProfStudyingRain, MSGBOX_DEFAULT
	release
	end

Route119_WeatherInstitute_1F_EventScript_InstituteWorker2::
	msgbox Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo, MSGBOX_NPC
	end

Route119_WeatherInstitute_1F_EventScript_Bed::
	lockall
	msgbox Route119_WeatherInstitute_1F_Text_TakeRestInBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	releaseall
	end

Route119_WeatherInstitute_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_1, Route119_WeatherInstitute_1F_Text_Grunt1Intro, Route119_WeatherInstitute_1F_Text_Grunt1Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_WEATHER_INST_4, Route119_WeatherInstitute_1F_Text_Grunt4Intro, Route119_WeatherInstitute_1F_Text_Grunt4Defeat
	msgbox Route119_WeatherInstitute_1F_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

Route119_WeatherInstitute_1F_Text_Grunt1Intro:
	.string "Patronumuz burada yapılan\naraştırmayla ilgilendi ve bizi\lgönderdi.\pKarışmayı bırak!$"

Route119_WeatherInstitute_1F_Text_Grunt1Defeat:
	.string "Kahretsin…\nBir çocuğa yenildim…$"

Route119_WeatherInstitute_1F_Text_Grunt1PostBattle:
	.string "Yaptıklarımızın sebebini patron\nbiliyor.\pBen sadece bir haydutum.\nOnun ne düşündüğü hakkında\lne bilebilirim ki?$"

Route119_WeatherInstitute_1F_Text_Grunt4Intro:
	.string "Ha?\nBir çocuğun burada ne işi var?$"

Route119_WeatherInstitute_1F_Text_Grunt4Defeat:
	.string "Ne?\nNasıl kaybederim?!$"

Route119_WeatherInstitute_1F_Text_Grunt4PostBattle:
	.string "Ah, hayır…\nBir çocuğa yenildiğim için\lazar işiteceğim…\pYatakta biraz kestirmeliyim.$"

Route119_WeatherInstitute_1F_Text_EveryoneWentUpstairs:
	.string "Ben uyurken herkes üst kata çıktı!$"

Route119_WeatherInstitute_1F_Text_WowYoureStrong:
	.string "Vay canına, gerçekten çok güçlüsün!\pKeşke ben de senin gibi bir eğitmen\nolabilsem!$"

Route119_WeatherInstitute_1F_Text_ProfStudyingRain:
	.string "Profesör yağmuru seviyor.\nBu bir gerçek.\pAma yağmur yağmaya devam ederse,\ninsanların başı belaya girecek.\lBu da başka bir gerçek.\pBu nedenle PROFESÖR, yağmurun iyi bir\nşekilde kullanılıp kullanılamayacağını\laraştırıyor.$"

Route119_WeatherInstitute_1F_Text_NoticingAbnormalWeather:
	.string "ENSTİTÜ'nün 2. katında, HOENN bölgesi\nüzerindeki hava durumu modellerini\linceliyoruz.\pSon zamanlarda geçici ve münferit\nkuraklık ve şiddetli yağmur vakaları\lfark ediyoruz…$"

Route119_WeatherInstitute_1F_Text_WhatWereAquasUpTo:
	.string "Merhaba!\nSenin sayende kurtulduk!\pAnlamadığım şey, AQUA'nın neyin\npeşinde olduğu.$"

Route119_WeatherInstitute_1F_Text_TakeRestInBed:
	.string "Bir yatak var…\nBiraz dinlenelim.$"


