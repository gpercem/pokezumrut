.set LOCALID_TWIN, 2

VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	end

VerdanturfTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_TwinTunnelOpen
	msgbox VerdanturfTown_Text_ManTryingToDigTunnel, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_TwinTunnelOpen::
	msgbox VerdanturfTown_Text_ManDugTunnelForLove, MSGBOX_DEFAULT
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

VerdanturfTown_EventScript_Man::
	msgbox VerdanturfTown_Text_AirCleanHere, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Camper::
	msgbox VerdanturfTown_Text_MakeBattleTentDebut, MSGBOX_NPC
	end

VerdanturfTown_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_EventScript_BoyTunnelOpen
	msgbox VerdanturfTown_Text_GuyTryingToBustThroughCave, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_BoyTunnelOpen::
	msgbox VerdanturfTown_Text_EasyToGetToRustboroNow, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_ManTryingToDigTunnel:
	.string "Babam bana bu tünelin ürkek\nPOKEMON'larla dolu olduğunu\lsöyledi.\pYüksek sesten korkuyorlarmış ve\nbüyük bir kargaşa çıkarıyorlarmış.\pBu yüzden büyük tünel projesini\ndurdurmak zorunda kalmışlar.\pAma bir adam var. Tüneli tek başına\nkazmaya çalışıyor!$"

VerdanturfTown_Text_ManDugTunnelForLove:
	.string "Sevdiği kadın için tünel kazan bir adam\nvarmış.\pGerçekten anlamıyorum, ama hey!\nBu işimize yarayacak!$"

VerdanturfTown_Text_AirCleanHere:
	.string "Rüzgârların esme şekline göre volkanik\nküller asla bu yöne doğru savrulmaz.\pBuranın havası temiz ve ferhatır.\nBurada yaşamak zayıf ve hasta\linsanlar için bile harikalar yaratır.$"

VerdanturfTown_Text_MakeBattleTentDebut:
	.string "POKéMON'um ve ben bir galibiyet\nserisi sürdürüyoruz.\pBu kasabanın SAVAŞ ÇADIRI'nda\nsavaşmaya karar verdim.$"

VerdanturfTown_Text_GuyTryingToBustThroughCave:
	.string "POKéMON MART'ın yanındaki mağarayı\ngördün mü?\pOrada diğer tarafa geçebilmek için\nkayaları parçalamaya çalışan bir adam\lvar.\pİçinden geçebilirsek harika olur…\nRUSTBORO'yu ziyaret etmemizi\lkolaylaştırır.$"

VerdanturfTown_Text_EasyToGetToRustboroNow:
	.string "POKéMON MART'ın yanındaki mağara\nartık diğer tarafa açılan bir tünel.\pBu harika! Artık RUSTBORO'da yeni\nDEVON ürünleri için alışveriş yapmak\lçok kolay.$"

VerdanturfTown_Text_TownSign:
	.string "VERDANTURF KASABASI\pÇimenlerin tatlı kokusunu taşıyan\nrüzgârlı yaylalar.$"

VerdanturfTown_Text_WandasHouse:
	.string "WANDA'NIN EVİ$"

VerdanturfTown_Text_BattleTentSign:
	.string "VERDANTURF SAVAŞ ÇADIRI\nSavaşlarda Gözleriniz Bayram Etsin!$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "RUSTURF TÜNELİ\nRUSTBORO ve VERDANTURF'u Birbirine\lBağlıyor!\pTünel projesi iptal edildi.$"


