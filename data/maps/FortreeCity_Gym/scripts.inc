FortreeCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, FortreeCity_Gym_OnWarp
	.byte 0

FortreeCity_Gym_OnTransition:
	special RotatingGate_InitPuzzle
	end

FortreeCity_Gym_OnWarp:
	map_script_2 VAR_TEMP_0, VAR_TEMP_0, FortreeCity_Gym_EventScript_InitRotatingGates
	.2byte 0

FortreeCity_Gym_EventScript_InitRotatingGates::
	special RotatingGate_InitPuzzleAndGraphics
	end

FortreeCity_Gym_EventScript_Winona::
	trainerbattle_single TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaIntro, FortreeCity_Gym_Text_WinonaDefeat, FortreeCity_Gym_EventScript_WinonaDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_Gym_EventScript_WinonaRematch
	goto_if_unset FLAG_RECEIVED_TM40, FortreeCity_Gym_EventScript_GiveAerialAce2
	msgbox FortreeCity_Gym_Text_WinonaPostBattle, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_WinonaDefeated::
	message FortreeCity_Gym_Text_ReceivedFeatherBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_FORTREE_GYM
	setflag FLAG_BADGE06_GET
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers
	call FortreeCity_Gym_EventScript_GiveAerialAce
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox FortreeCity_Gym_Text_RegisteredWinona, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_WINONA_MATCH_CALL
	setvar VAR_SCOTT_FORTREE_CALL_STEP_COUNTER, 0
	setflag FLAG_SCOTT_CALL_FORTREE_GYM
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce2::
	giveitem ITEM_TM40
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM40
	release
	end

FortreeCity_Gym_EventScript_GiveAerialAce::
	giveitem ITEM_TM40
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox FortreeCity_Gym_Text_ExplainAerialAce, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM40
	return

FortreeCity_Gym_EventScript_WinonaRematch::
	trainerbattle_rematch_double TRAINER_WINONA_1, FortreeCity_Gym_Text_WinonaPreRematch, FortreeCity_Gym_Text_WinonaRematchDefeat, FortreeCity_Gym_Text_WinonaRematchNeedTwoMons
	msgbox FortreeCity_Gym_Text_WinonaPostRematch, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Jared::
	trainerbattle_single TRAINER_JARED, FortreeCity_Gym_Text_JaredIntro, FortreeCity_Gym_Text_JaredDefeat
	msgbox FortreeCity_Gym_Text_JaredPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Edwardo::
	trainerbattle_single TRAINER_EDWARDO, FortreeCity_Gym_Text_EdwardoIntro, FortreeCity_Gym_Text_EdwardoDefeat
	msgbox FortreeCity_Gym_Text_EdwardoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Flint::
	trainerbattle_single TRAINER_FLINT, FortreeCity_Gym_Text_FlintIntro, FortreeCity_Gym_Text_FlintDefeat
	msgbox FortreeCity_Gym_Text_FlintPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Ashley::
	trainerbattle_single TRAINER_ASHLEY, FortreeCity_Gym_Text_AshleyIntro, FortreeCity_Gym_Text_AshleyDefeat
	msgbox FortreeCity_Gym_Text_AshleyPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Humberto::
	trainerbattle_single TRAINER_HUMBERTO, FortreeCity_Gym_Text_HumbertoIntro, FortreeCity_Gym_Text_HumbertoDefeat
	msgbox FortreeCity_Gym_Text_HumbertoPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_Darius::
	trainerbattle_single TRAINER_DARIUS, FortreeCity_Gym_Text_DariusIntro, FortreeCity_Gym_Text_DariusDefeat
	msgbox FortreeCity_Gym_Text_DariusPostBattle, MSGBOX_AUTOCLOSE
	end

FortreeCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_FORTREE_GYM, FortreeCity_Gym_EventScript_GymGuidePostVictory
	msgbox FortreeCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_GymGuidePostVictory::
	msgbox FortreeCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

FortreeCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE06_GET, FortreeCity_Gym_EventScript_GymStatueCertified
	goto FortreeCity_Gym_EventScript_GymStatue
	end

FortreeCity_Gym_EventScript_GymStatueCertified::
	msgbox FortreeCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_EventScript_GymStatue::
	msgbox FortreeCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_Gym_Text_GymGuideAdvice:
	.string "Hey! nasıl gidiyor, ŞAMPİYON-\n"
	.string "adayı {PLAYER}?\p"
	.string "FORTREE ŞEHRİ SALON LİDERİ WİNONA\n"
	.string "UÇUŞ-tipi POKéMON üstadıdır.\p"
	.string "O seni bu salonun arkasında,\n"
	.string "dönen kapıların ardında bekliyor.\p"
	.string "O yeni mücadelecilerle savaşmayı bekliyor\n"
	.string "kim onunla aşık atmayı deneyecek!\p"
	.string "Tamam, ilerle o halde!$"

FortreeCity_Gym_Text_GymGuidePostVictory:
	.string "Başardın!\n"
	.string "Bunun üstesinden geldin!$"

FortreeCity_Gym_Text_JaredIntro:
	.string "KUŞ POKéMONLARININ zarif savaş stiline\n"
	.string "kendini hazırla!$"

FortreeCity_Gym_Text_JaredDefeat:
	.string "S-Sen…\n"
	.string "Çok güçlüsün…$"

FortreeCity_Gym_Text_JaredPostBattle:
	.string "Bir EĞİTMEN beklenmedik geri dönüşlere\n"
	.string " ve olaylara karşı akıllıca davranmalı.\p"
	.string "LİDERİMİZE ulaşabilecek kadar\n"
	.string "akıllı mısın?$"

FortreeCity_Gym_Text_EdwardoIntro:
	.string "KUŞ POKéMON severler bu salona\n"
	.string "katılabilirler.\p"
	.string "Bir FORTREE SALONU üyesi olarak\n"
	.string "kaybetmeyi kabullenemem!$"

FortreeCity_Gym_Text_EdwardoDefeat:
	.string "Bu katlanmak için çok fazla\n"
	.string "geldi…$"

FortreeCity_Gym_Text_EdwardoPostBattle:
	.string "Dünya çok büyük bir yer ve\n"
	.string "içinde sayısız EĞİTMEN var.\p"
	.string "Daha çok çalışmaya ve kendimi daha\n"
	.string "da güçlendirmeye gidiyorum.$"

FortreeCity_Gym_Text_FlintIntro:
	.string "WİNONA'nın,SALON LİDERİMİZİN,\n"
	.string "seninle uğraşmasına gerek yok!\p"
	.string "Ben senin için yeterince iyiyim!$"

FortreeCity_Gym_Text_FlintDefeat:
	.string "WİNONA, B-Ben…\n"
	.string "Yenildim!$"

FortreeCity_Gym_Text_FlintPostBattle:
	.string "WİNONA tatlı ve güçlüdür.\n"
	.string "O nihai LİDER!\p"
	.string "(Kızarır)…$"

FortreeCity_Gym_Text_AshleyIntro:
	.string "WİNONA beni özel olarak eğitti!\n"
	.string "Beni kolaylıkla yenemezsin!$"

FortreeCity_Gym_Text_AshleyDefeat:
	.string "Yenildim…$"

FortreeCity_Gym_Text_AshleyPostBattle:
	.string "WİNONA'YA şükürler olsun ki sayesinde\n"
	.string "FORTREE halkı korkmadan yaşıyor.$"

FortreeCity_Gym_Text_HumbertoIntro:
	.string "WİNONA savaşa başladığında, yüzü\n"
	.string "güzel bir azimle ışıldar…\p"
	.string "Senin bu sevgili ışığı söndürmene\n"
	.string "izin vermem!$"

FortreeCity_Gym_Text_HumbertoDefeat:
	.string "Ağh!\n"
	.string "Seni engelleyemedim.$"

FortreeCity_Gym_Text_HumbertoPostBattle:
	.string "İzlesen iyi olur!\n"
	.string "WİNONA'ya bakarken dikkatin dağılmasın\l"
	.string "yoksa bir çırpıda çökebilirsin!$"

FortreeCity_Gym_Text_DariusIntro:
	.string "UÇUŞ-tipi POKéMONLARIN bütün\n"
	.string "türlerini bilsen iyi olur.\p"
	.string "Bunu bilirsun, değil mi?$"

FortreeCity_Gym_Text_DariusDefeat:
	.string "İşi biliyor gibisin!$"

FortreeCity_Gym_Text_DariusPostBattle:
	.string "Elbette, beni yendin.\n"
	.string "Ama dikkatle izlesen iyi olur.\l"
	.string "WİNONA'nın POKéMONLARI çok güçlüdür.$"

FortreeCity_Gym_Text_WinonaIntro:
	.string "Ben WİNONA. Ben FORTREE POKéMON\n"
	.string "SALONU'nun LİDERİYİM.\p"
	.string "Ben KUŞ POKéMONLARIYLA bir olur\n"
	.string "ve onlarla havada süzülürüm…\p"
	.string "KUŞ POKéMONLARI'nın zarif koreografisi ile\n"
	.string "Ben…\p"
	.string "Savaş ne kadar meşakkatli olursa olsun\n"
	.string "zarafetle zaferi elde ederim!$"

FortreeCity_Gym_Text_WinonaDefeat:
	.string "Daha önce hiç bu kadar zarifçe\n"
	.string "POKéMONU'nu yöneten bir eğitmen\l"
	.string "görmemiştim…\p"
	.string "Cesaretini takdir etmek için,\n"
	.string "Sana bu SALON ROZETİNİ sunuyorum.$"

FortreeCity_Gym_Text_ReceivedFeatherBadge:
	.string "{PLAYER} WİNONADAN TÜY ROZETİNİ\n"
	.string "aldı.$"

FortreeCity_Gym_Text_ExplainFeatherBadgeTakeThis:
	.string "Bu TÜY ROZETİ ile birlikte\n"
	.string "70 SV'e kadar tüm POKéMONLARIN\l"
	.string ",takasla elde edilenler dahil, itaat eder.\p"
	.string "Ayrıca artık FLY HM'sini dışarıda\n"
	.string "savaş dışında kullanabilirsin.\p"
	.string "Ve bu…\n"
	.string "Benden sana bir hediye.$"

FortreeCity_Gym_Text_ExplainAerialAce:
	.string "TM40 AERIAL ACE'i içerir.\p"
	.string "Hızını…\n"
	.string "Hiçbir POKéMON karşılayamaz.\p"
	.string "… … … … … …$"

FortreeCity_Gym_Text_RegisteredWinona:
	.string "SALON LİDERİ WİNONA\n"
	.string "POKéNAV'a kayıt edildi.$"

FortreeCity_Gym_Text_WinonaPostBattle:
	.string "Sana karşı kaybetmiş olsam da\n"
	.string "KUŞ POKéMONUMA bağlı kalacağım.$"

FortreeCity_Gym_Text_GymStatue:
	.string "FORTREE ŞEHRİ POKéMON SALONU$"

FortreeCity_Gym_Text_GymStatueCertified:
	.string "FORTREE ŞEHRİ POKéMON SALONU\p"
	.string "WİNONA'nın onayladığı eğitmenler:\n"
	.string "{PLAYER}$"

FortreeCity_Gym_Text_WinonaPreRematch:
	.string "WİNONA: Biz insanlar asla zeminin\n"
	.string "uyguladığı yer çekiminden kaçamayız.\p"
	.string "Ama mükemellik için çabalarsak\n"
	.string "uçabilecek gücü kendimizde buluruz!\p"
	.string "Hüküm süren bir ŞAMPİYON olarak\n"
	.string "zirveye doğru tırmandın.\p"
	.string "Lütfen, gücünü kavrayabileceğim bir\n"
	.string "uçuş yapalım!$"

FortreeCity_Gym_Text_WinonaRematchDefeat:
	.string "Yenildim ve yine senin mesafene erişemedim…$"

FortreeCity_Gym_Text_WinonaPostRematch:
	.string "WİNONA: Kaybetsem bile artık\n"
	.string "kalbimin kanatları kırık değil.\p"
	.string "Ben tekrar tekrar yükselebilir\n"
	.string "ve uçabilirim.\p"
	.string "Buna inanıyorum!$"

FortreeCity_Gym_Text_WinonaRematchNeedTwoMons:
	.string "WİNONA: Biz insanlar asla zeminin\n"
	.string "uyguladığı yer çekiminden kaçamayız.\p"
	.string "Ama mükemellik için çabalarsak\n"
	.string "uçabilecek gücü kendimizde buluruz!\p"
	.string "Hüküm süren bir ŞAMPİYON olarak\n"
	.string "zirveye doğru tırmandın.\p"
	.string "Lütfen, gücünü kavrayabileceğim bir\n"
	.string "uçuş yapalım!\p"
	.string "Ah olamaz… Yanında sadece bir\n"
	.string "POKéMON mu var?\p"
	.string "Lütfen en az iki POKéMON ile geri\n"
	.string "geldiğinizden emin olun.$"
