VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "WALLY: Sana karşı kaybettim, {PLAYER},\nama artık kendimi kötü hissetmiyorum.\pÇünkü hayatta yeni bir amacım var.\nRALTS'ımla birlikte POKéMON\lSALONLARINA meydan okuyacağım ve\lharika bir EĞİTMEN olacağım.\pBeni iyi izle, {PLAYER}.\nSenden daha güçlü olacağım.\pBunu başardığımda, sana başka bir\nsavaş için meydan okuyacağım.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "Sadece beni izle, {PLAYER}.\nSenden daha güçlü olacağım.\pBunu yaptığımda, sana başka bir savaş\niçin meydan okuyacağım.$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "AMCA: Hey! {PLAYER}{KUN}!\nWALLY yan tarafta.\pAma evlat, sana söylemem gereken bir\nşey var.\pBu doğal ortam WALLY'nin sağlığı için\nharika bir yer.\pBelki de sadece çevre değildir.\nÇocuğa umut veren POKéMON'ları\lolabilir.$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "WALLY gitti…\nTek başına kaçtı…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "AMCA: Bu doğru mu?\nWALLY tek başına o kadar uzağa\lgitmiş.\pEe, hakkını veriyor.\nAmcasıyım sonuçta.$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "Öyle mi?\nDoğru, hatırladım!\pSen WALLY'nin bana bahsettiği\n{PLAYER}'sın.\pBen WALLY'nin kuzeniyim.\nTanıştığımıza memnun oldum!\pWALLY buraya geldiğinden beri çok\ndaha canlı ve sağlıklı oldu.$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "WALLY için endişelenme.\nO iyi olacak.\pKüçük kuzenimi iyi tanıyorum.$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Sayende kız arkadaşımı her gün\ngörebiliyorum.\pMutlu muyum?\nBenden mutlusu olamaz!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "Kızımın erkek arkadaşı çok azimli ve\ntutkulu bir insan.\pSırf kızımı görebilmek için durmadan\ntünel kazıyor.\pKızım biraz endişeli, bu yüzden sık sık\ntünele gidiyor.$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "İnanılmaz bir şey. Kızımın erkek\narkadaşı tüneli eliyle kazdı!\pİnanılmaz bir şey!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "Eğer WALLY'e bir şey olursa,\nPETALBURG'daki ailesinin yüzüne asla\lbakamam…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "WALLY, EVER GRANDE'de mi?\pPETALBURG'daki ailesi bunu duysa çok\nşaşırırdı!$"


