.set LOCALID_COLE, 2
.set LOCALID_GERALD, 3
.set LOCALID_AXLE, 4
.set LOCALID_DANIELLE, 5

LavaridgeTown_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition:
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers
	end

@ Unclear where/if these temp vars are getting checked
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars::
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars::
	return

LavaridgeTown_Gym_1F_EventScript_CheckBuryTrainers::
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryGerald::
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryAxle::
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_CheckBuryDanielle::
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_BURIED
LavaridgeTown_Gym_1F_EventScript_EndCheckBuryTrainers::
	return

LavaridgeTown_Gym_1F_EventScript_Flannery::
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM50, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated::
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2::
	giveitem ITEM_TM50
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM50
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat::
	giveitem ITEM_TM50
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM50
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch::
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_COLE, LOCALID_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_ColePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript::
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	goto_if_eq VAR_RESULT, 1, EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_AXLE, LOCALID_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_KEEGAN, LOCALID_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_DANIELLE, LOCALID_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_GERALD, LOCALID_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JACE, LOCALID_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JEFF, LOCALID_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli::
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_ELI, LOCALID_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue::
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice:
	.string "Hey, nasıl gidiyor, ŞAMPİYON\nadayı {PLAYER}?\pLAVARIDGE'in SALON LİDERİ FLANNERY\nATEŞ tipi POKéMON kullanıyor.\pPOKéMON tutkusu bir volkandan daha\ngüçlü ve daha sıcak yanıyor.\pOna çok yaklaşma - yanarsın!\nAma onu suyla söndürebilirsin!$"

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory:
	.string "Yo!\nBu kavurucu bir savaştı!$"

LavaridgeTown_Gym_1F_Text_ColeIntro:
	.string "Ovovovovov!\nAman, çok sıcak!$"

LavaridgeTown_Gym_1F_Text_ColeDefeat:
	.string "Gözlerimdeki ter kör etti beni.$"

LavaridgeTown_Gym_1F_Text_ColePostBattle:
	.string "Sıcak kuma gömülmek kan dolaşımını\nhızlandırıyor.\pEklemlerindeki ağrıyı iyileştirmek\niçin oldukça etkili!$"

LavaridgeTown_Gym_1F_Text_AxleIntro:
	.string "Stresimi atmaya çalışıyorum.\nGelip beni strese sokma!$"

LavaridgeTown_Gym_1F_Text_AxleDefeat:
	.string "Umarım FLANNERY seni ateşler!$"

LavaridgeTown_Gym_1F_Text_AxlePostBattle:
	.string "Haaah…\nHof…\pUzun süre sıcak kuma gömülü kalınca\nçok yorucu oluyor…$"

LavaridgeTown_Gym_B1F_Text_KeeganIntro:
	.string "Şimdiye kadar yorulmuş olmalısın.\nSıcak kum içinde dinlenmek istersin,\ldeğil mi?\pAncak iradeni korumanın tüm eğitmenler\niçin önemli bir yetenek olduğunu\lbilmelisin.$"

LavaridgeTown_Gym_B1F_Text_KeeganDefeat:
	.string "Yan yan, yan benimle…$"

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle:
	.string "Cidden çok yeteneklisin…\nAma liderimiz FLANNERY senden güçlü.\pKendine dikkat etmezsen, ciddi şekilde\nyanarsın.$"

LavaridgeTown_Gym_1F_Text_GeraldIntro:
	.string "POKéMON'un 200 derece sıcağa\ndayanabilir mi?$"

LavaridgeTown_Gym_1F_Text_GeraldDefeat:
	.string "Yeterince sıcak yanmadım…$"

LavaridgeTown_Gym_1F_Text_GeraldPostBattle:
	.string "Magmanın sıcaklığı 200 derece.\pSenin POKéMON'un beni yendi, yani\nmagmada kolayca hayatta kalabilir.$"

LavaridgeTown_Gym_1F_Text_DanielleIntro:
	.string "Tamam, seninle savaşacağım.$"

LavaridgeTown_Gym_1F_Text_DanielleDefeat:
	.string "Ama sen çok güçlüsün.$"

LavaridgeTown_Gym_1F_Text_DaniellePostBattle:
	.string "Tıpkı FLANNERY gibi güzel ve güçlü bir\nEĞİTMEN olacağım.$"

LavaridgeTown_Gym_B1F_Text_JaceIntro:
	.string "Pekala!\nHeyecanım soğumadan yapalım şunu!$"

LavaridgeTown_Gym_B1F_Text_JaceDefeat:
	.string "Hava çok sıcak ama kalbim buz tutmuş\ndurumda.$"

LavaridgeTown_Gym_B1F_Text_JacePostBattle:
	.string "İçindeki savaşçı ruhun yanma şekline\nbakılırsa, liderimize karşı bir\lşansın olabilir.$"

LavaridgeTown_Gym_B1F_Text_JeffIntro:
	.string "Alevlerin nasıl çılgınca parladığını\ngörüyor musun? Kazanmamı beklerken\lalevleniyorlar!$"

LavaridgeTown_Gym_B1F_Text_JeffDefeat:
	.string "Bir şeyler doğru gitmedi.$"

LavaridgeTown_Gym_B1F_Text_JeffPostBattle:
	.string "Ne olmuş yani? Ne olmuş diyorum?\nSıcak küllerin üzerinde yalınayak\lyürüyebilirim!\p…Ama sen aklından bile geçirme!$"

LavaridgeTown_Gym_B1F_Text_EliIntro:
	.string "Dağları sevdiğim kadar volkanları\nda çok severim.$"

LavaridgeTown_Gym_B1F_Text_EliDefeat:
	.string "Sanırım kontrolü hiç elime alamadan\nkaybettim.$"

LavaridgeTown_Gym_B1F_Text_EliPostBattle:
	.string "Burada kalıyorum çünkü FLANNERY'nin\ngücüne hayran kaldım.\pHehehehe.$"

LavaridgeTown_Gym_1F_Text_FlanneryIntro:
	.string "Hoş geldin…\nHayır, bir saniye.\pSeni çelimsiz EĞİTMEN, buraya geldiğini\ngörmek şaşırtıcı!\pBu görev bana… Hayır, bekle.\nE-hem.\pBen FLANNERY, SALON LİDERİ'yim!\pEe…\nEvet, kısa süredir liderim ama beni\nhafife alma!\pBüyük babamdan miras kalan\nyeteneklerimle, bu topraklarda\lgeliştirdiğim ateşli hareketleri\lsana göstereceğim!$"

LavaridgeTown_Gym_1F_Text_FlanneryDefeat:
	.string "Ah…\nZorlandığımı söyleyebilirim…\pBen…\nDaha yeni SALON LİDERİ oldum.\pOlmadığım biri olmak için çok uğraştım.\pİşleri doğal yolumla yapmalıyım.\nEğer yapmazsam, POKéMON'larımın\lkafası karışacak.\pBana bunu öğrettiğin için teşekkürler.\nBunu hak ediyorsun.$"

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge:
	.string "{PLAYER}, FLANNERY'den ISI ROZETİ\naldı.$"

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis:
	.string "Eğer bir ISI ROZETİN varsa, Seviye\n50'ye kadar olan tüm POKéMON'lar,\lhatta başkalarından takas yoluyla\laldıkların bile, sana itaat edecektir.\pVe POKéMON'un savaş dışında HM\nhareketi GÜÇ'ü kullanmasını sağlar.\pBu benim minnettarlığımın bir\nsimgesidir. Almaktan çekinme!$"

LavaridgeTown_Gym_1F_Text_ExplainOverheat:
	.string "Bu TM50, AŞIRI ISINMA içerir.\pBu saldırı rakibe ciddi hasar verir.\pAma aynı zamanda kullanan POKéMON'un\nÖZ. SLD'sını da ciddi bir şekilde\lazaltır. Uzun süreli savaşlar için\luygun olmayabilir.$"

LavaridgeTown_Gym_1F_Text_RegisteredFlannery:
	.string "FLANNERY, POKéNAV'a kaydedildi\n.$"

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle:
	.string "Gücün bana birini hatırlatıyor.\pHatırladım!\nPETALBURG SALONU LİDERİ NORMAN\lgibi savaşıyorsun.$"

LavaridgeTown_Gym_1F_Text_GymStatue:
	.string "LAVARIDGE KÖYÜ POKéMON SALONU$"

LavaridgeTown_Gym_1F_Text_GymStatueCertified:
	.string "LAVARIDGE TOWN POKéMON SALONU\pFLANNERY'NİN ONAYLI EĞİTMENLERİ:\n{PLAYER}$"

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch:
	.string "Bir savaşı kaybetmek beni\nyıldırmaz.\pPOKéMON'ları seviyorum.\nSavaşmayı seviyorum.\lVe… bu salonu seviyorum!\pHadi tekrar savaşta yeteneklerimizi\nbirbirimize gösterelim!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat:
	.string "Vay be!\nPatlamanın eşiğindeyim!$"

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch:
	.string "Maçı kaybettim ama tamamen memnunum.\pBu kadar hararetli bir savaştan zevk\nalmak pek sık nasip olmuyor.\pBir ara yine böyle bir maç yapalım!$"

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons:
	.string "Bir savaşı kaybetmek beni\nyıldırmaz.\pPOKéMON'ları seviyorum.\nSavaşmayı seviyorum.\lVe… bu salonu seviyorum!\pHadi tekrar savaşta yeteneklerimizi\nbirbirimize gösterelim!\pBekle. Savaşabilecek sadece bir\nPOKéMON'un mu var?\pBunu söylemekten nefret ediyorum ama\nbeni görmeye gelirken en az iki\lPOKéMON getirmelisin.$"
