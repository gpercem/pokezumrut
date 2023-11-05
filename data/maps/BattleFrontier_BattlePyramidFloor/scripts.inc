BattleFrontier_BattlePyramidFloor_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidFloor_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidFloor_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidFloor_OnTransition
	.byte 0

BattleFrontier_BattlePyramidFloor_OnFrame:
	map_script_2 VAR_TEMP_D, 1, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight
	map_script_2 VAR_TEMP_E, 0, BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight::
	lockall
	@ pyramid_updatelight, cant use macro because it straddles the loop
	setvar VAR_0x8004, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar VAR_0x8005, 4
	setvar VAR_0x8006, PYRAMID_LIGHT_INCR_RADIUS
	setvar VAR_0x8007, SE_SAVE
	setvar VAR_RESULT, 0
BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop::
	special CallBattlePyramidFunction
	delay 2
	goto_if_ne VAR_RESULT, 2, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop
	setvar VAR_TEMP_D, 0
	releaseall
	end

BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic::
	playbgm MUS_B_PYRAMID, FALSE
	setvar VAR_TEMP_E, 1
	end

BattleFrontier_BattlePyramidFloor_OnResume:
	pyramid_setfloorpal
	frontier_getstatus
	switch VAR_TEMP_0
	case 0, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	frontier_isbattletype BATTLE_TYPE_TRAINER  @ VAR_RESULT seems to be ignored here
	setvar VAR_TEMP_D, 1
BattleFrontier_BattlePyramidFloor_EventScript_ResetParty::
	pyramid_resetparty
	end

BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	pyramid_set PYRAMID_DATA_TRAINER_FLAGS, 255
BattleFrontier_BattlePyramid_EventScript_WarpToLobby::
	pyramid_updatelight 0, PYRAMID_LIGHT_SET_RADIUS
	pyramid_clearhelditems
	special HealPlayerParty
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_OnTransition:
	call BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius::
	pyramid_updatelight 32, PYRAMID_LIGHT_SET_RADIUS
	return

BattlePyramid_WarpToNextFloor::
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM  @ Floor number
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	goto_if_eq VAR_RESULT, 7, BattlePyramid_WarpToTop
	pyramid_seedfloor
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	waitstate
	end

BattlePyramid_WarpToTop::
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP, 17, 17
	waitstate
	end

@ TRAINER_PHILLIP is used as a placeholder
BattlePyramid_TrainerBattle::
	trainerbattle TRAINER_BATTLE_PYRAMID, TRAINER_PHILLIP, 0, BattleFacility_TrainerBattle_PlaceholderText, BattleFacility_TrainerBattle_PlaceholderText
	pyramid_showhint
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattlePyramid_FindItemBall::
	pyramid_setitem
	callstd STD_FIND_ITEM
	goto_if_eq VAR_0x8007, 0, BattlePyramid_FindItemBallEnd
	pyramid_hideitem
BattlePyramid_FindItemBallEnd::
	end

BattlePyramid_Retire::
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

BattleFacility_TrainerBattle_PlaceholderText:
	.string "Bu örnek bir mesajdır.$"

gText_BattlePyramidConfirmRest::
	.string "BATTLE PYRAMID göreviniz\nkaydedilecek, böylece şimdilik\lçıkabilirsiniz. Sorun olur mu?$"

gText_BattlePyramidConfirmRetire::
	.string "PİRAMİT görevini bırakmak istediğine\nemin misin?$"

BattlePyramid_Text_ExitHintUp1::
	.string "Bu katın çıkışı o yöndedir: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft1::
	.string "Bu katın çıkışı o yöndedir: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight1::
	.string "Bu katın çıkışı o yöndedir: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown1::
	.string "Bu katın çıkışı o yöndedir: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp2::
	.string "Bu kattaki çıkış {UP_ARROW} yönündedir.$"

BattlePyramid_Text_ExitHintLeft2::
	.string "Bu kattaki çıkış {LEFT_ARROW}\nyönündedir.$"

BattlePyramid_Text_ExitHintRight2::
	.string "Bu kattaki çıkış {RIGHT_ARROW}\nyönündedir.$"

BattlePyramid_Text_ExitHintDown2::
	.string "Bu kattaki çıkış {DOWN_ARROW}\nyönündedir.$"

BattlePyramid_Text_ExitHintUp3::
	.string "Çıkış şu {LEFT_ARROW} yolunun\nüzerinde.$"

BattlePyramid_Text_ExitHintLeft3::
	.string "Çıkış şu {LEFT_ARROW} yolun üzerinde.$"

BattlePyramid_Text_ExitHintRight3::
	.string "Çıkış şu {LEFT_ARROW} yolun üzerinde.$"

BattlePyramid_Text_ExitHintDown3::
	.string "Çıkış şu {DOWN_ARROW} yolunun üzerinde.$"

BattlePyramid_Text_ExitHintUp4::
	.string "Bu katta çıkış {UP_ARROW} yönünde bir\nyerdedir.$"

BattlePyramid_Text_ExitHintLeft4::
	.string "Bu katta çıkış {LEFT_ARROW} yönünde\nbir yerdedir.$"

BattlePyramid_Text_ExitHintRight4::
	.string "Bu katta çıkış {RIGHT_ARROW} yönünde\nbir yerdedir.$"

BattlePyramid_Text_ExitHintDown4::
	.string "Bu katta çıkış {DOWN_ARROW} yönünde\nbir yerdedir.$"

BattlePyramid_Text_ExitHintUp5::
	.string "Çıkış mı? Bu {UP_ARROW} yolu.$"

BattlePyramid_Text_ExitHintLeft5::
	.string "Çıkış mı? Şu {LEFT_ARROW} yol.$"

BattlePyramid_Text_ExitHintRight5::
	.string "Çıkış mı? Şu {RIGHT_ARROW} yol.$"

BattlePyramid_Text_ExitHintDown5::
	.string "Çıkış mı? Bu {DOWN_ARROW} yolu.$"

BattlePyramid_Text_ExitHintUp6::
	.string "Çıkış {UP_ARROW} yönünde olur.$"

BattlePyramid_Text_ExitHintLeft6::
	.string "Çıkış {LEFT_ARROW} yönünde olur.$"

BattlePyramid_Text_ExitHintRight6::
	.string "Çıkış {RIGHT_ARROW} yönünde olur.$"

BattlePyramid_Text_ExitHintDown6::
	.string "Çıkış {DOWN_ARROW} yönünde olur.$"

BattlePyramid_Text_EightItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunacak sekiz eşya kaldı.$"

BattlePyramid_Text_SevenItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunacak yedi eşya kaldı.$"

BattlePyramid_Text_SixItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunacak altı eşya kaldı.$"

BattlePyramid_Text_FiveItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunacak beş eşya kaldı.$"

BattlePyramid_Text_FourItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunacak dört eşya kaldı.$"

BattlePyramid_Text_ThreeItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunacak üç eşya kaldı.$"

BattlePyramid_Text_TwoItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunması gereken iki eşya kaldı.$"

BattlePyramid_Text_OneItemRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunması gereken bir eşya kaldı.$"

BattlePyramid_Text_ZeroItemsRemaining1::
	.string "Eşya mı arıyorsunuz?\pBulunacak hiçbir şey kalmadı!$"

BattlePyramid_Text_EightItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBurada yatan sekiz parça var.$"

BattlePyramid_Text_SevenItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBuralarda yedi tane eşya kaldı.$"

BattlePyramid_Text_SixItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBuralarda altı tane eşya kaldı.$"

BattlePyramid_Text_FiveItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBurada yatan beş parça var.$"

BattlePyramid_Text_FourItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBuralarda dört tane eşya kaldı.$"

BattlePyramid_Text_ThreeItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBuralarda üç tane eşya kaldı.$"

BattlePyramid_Text_TwoItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBurada iki parça kaldı.$"

BattlePyramid_Text_OneItemRemaining2::
	.string "Çünkü sen kazandın, sana küçük bir sır\nvereceğim!\pBurada sadece bir parça var.$"

BattlePyramid_Text_ZeroItemsRemaining2::
	.string "Kazandığın için sana küçük bir sır\nvereceğim!\pBuralarda hiçbir şey kalmadı.$"

BattlePyramid_Text_EightItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen\nsekiz eşya kaldı.$"

BattlePyramid_Text_SevenItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen\nyedi eşya kaldı.$"

BattlePyramid_Text_SixItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen\naltı eşya kaldı.$"

BattlePyramid_Text_FiveItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen\nbeş eşya kaldı.$"

BattlePyramid_Text_FourItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen\ndört eşya kaldı.$"

BattlePyramid_Text_ThreeItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen üç\neşya kaldı.$"

BattlePyramid_Text_TwoItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen iki\neşya kaldı.$"

BattlePyramid_Text_OneItemRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen\ntek bir eşya kaldı.$"

BattlePyramid_Text_ZeroItemsRemaining3::
	.string "Eşya stoğunuz ne durumda?\pSanırım bu katta bulunmayı bekleyen\nbaşka eşya kalmadı. Kendine iyi bak!$"

BattlePyramid_Text_EightItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde sekiz eşya daha var gibi\ngörünüyor.$"

BattlePyramid_Text_SevenItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde yedi eşya daha var gibi\ngörünüyor.$"

BattlePyramid_Text_SixItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde altı eşya daha var gibi\ngörünüyor.$"

BattlePyramid_Text_FiveItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde beş eşya daha var gibi\ngörünüyor.$"

BattlePyramid_Text_FourItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde dört eşya daha var gibi\ngörünüyor.$"

BattlePyramid_Text_ThreeItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde üç eşya daha var gibi görünüyor.$"

BattlePyramid_Text_TwoItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde iki eşya daha var gibi\ngörünüyor.$"

BattlePyramid_Text_OneItemRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde sadece bir eşya daha var gibi\ngörünüyor.$"

BattlePyramid_Text_ZeroItemsRemaining4::
	.string "Güçlüsün, bu yüzden bir ipucu\nkazandın!\pYerde başka eşya yok gibi görünüyor.$"

BattlePyramid_Text_EightItemsRemaining5::
	.string "PİRAMİT'in bu katında sekiz madde\nolduğunu duydum.$"

BattlePyramid_Text_SevenItemsRemaining5::
	.string "PİRAMİT'in bu katında, yedi madde\nolduğunu duydum…$"

BattlePyramid_Text_SixItemsRemaining5::
	.string "PİRAMİT'in bu katında altı madde\nolduğunu duydum.$"

BattlePyramid_Text_FiveItemsRemaining5::
	.string "PİRAMİT'in bu katında beş madde\nolduğunu duydum.$"

BattlePyramid_Text_FourItemsRemaining5::
	.string "PİRAMİT'in bu katında dört madde\nolduğunu duydum.$"

BattlePyramid_Text_ThreeItemsRemaining5::
	.string "PİRAMİT'in bu katında üç madde\nolduğunu duydum.$"

BattlePyramid_Text_TwoItemsRemaining5::
	.string "PİRAMİT'in bu katında iki şey olduğunu\nduydum.$"

BattlePyramid_Text_OneItemRemaining5::
	.string "PİRAMİT'in bu katında bir eşya\nolduğunu duydum.$"

BattlePyramid_Text_ZeroItemsRemaining5::
	.string "PİRAMİT'in bu katında hiç eşya\nolmadığını duydum.$"

BattlePyramid_Text_EightItemsRemaining6::
	.string "Hiç eşya topladınız mı?\pSanırım bu katta sekiz eşya daha var.$"

BattlePyramid_Text_SevenItemsRemaining6::
	.string "Hiç eşya topladınız mı?\pSanırım bu katta yedi eşya daha var.$"

BattlePyramid_Text_SixItemsRemaining6::
	.string "Hiç eşya topladın mı?\pSanırım bu katta altı eşya daha var.$"

BattlePyramid_Text_FiveItemsRemaining6::
	.string "Hiç eşya topladın mı?\pSanırım bu katta beş eşya daha var.$"

BattlePyramid_Text_FourItemsRemaining6::
	.string "Hiç eşya topladınız mı?\pSanırım bu katta dört eşya daha var.$"

BattlePyramid_Text_ThreeItemsRemaining6::
	.string "Hiç eşya topladın mı?\pSanırım bu katta üç eşya daha var.$"

BattlePyramid_Text_TwoItemsRemaining6::
	.string "Hiç eşya topladın mı?\pSanırım bu katta iki eşya daha var.$"

BattlePyramid_Text_OneItemRemaining6::
	.string "Hiç eşya topladınız mı?\pSanırım bu katta bir eşya daha var.$"

BattlePyramid_Text_ZeroItemsRemaining6::
	.string "Hiç eşya topladınız mı?\pSanırım bu katta başka eşya yok.$"

BattlePyramid_Text_SevenTrainersRemaining1::
	.string "Gerçekten harikaydınız!\pAma hala benden başka yedi zorlu\nEĞİTMEN var!$"

BattlePyramid_Text_SixTrainersRemaining1::
	.string "Gerçekten harikaydınız!\pAma benden başka hala altı zorlu\nEĞİTMEN var!$"

BattlePyramid_Text_FiveTrainersRemaining1::
	.string "Gerçekten harikaydınız!\pAma benden başka hala beş zorlu\nEĞİTMEN var!$"

BattlePyramid_Text_FourTrainersRemaining1::
	.string "Gerçekten harikaydınız!\pAma benden başka hala dört zorlu\nEĞİTMEN var!$"

BattlePyramid_Text_ThreeTrainersRemaining1::
	.string "Gerçekten harikaydınız!\pAma benden başka hala üç zorlu\nEĞİTMEN var!$"

BattlePyramid_Text_TwoTrainersRemaining1::
	.string "Gerçekten harikaydınız!\pAma benden başka hala iki zorlu\nANTRENÖR var!$"

BattlePyramid_Text_OneTrainersRemaining1::
	.string "Gerçekten harikaydın!\pAma hala benden başka sert bir\nANTRENÖR var!$"

BattlePyramid_Text_ZeroTrainersRemaining1::
	.string "Gerçekten harikaydın!\pSeni yenebilecek kimse kalmadı!$"

BattlePyramid_Text_SevenTrainersRemaining2::
	.string "Bu çok üzücü!\pAma yedi eğitmen kaldı! Biri seni\nalçaltacak!$"

BattlePyramid_Text_SixTrainersRemaining2::
	.string "Bu çok üzücü!\pAma altı eğitmen kaldı! Biri seni\nalçaltacak!$"

BattlePyramid_Text_FiveTrainersRemaining2::
	.string "Bu çok üzücü!\pAma beş eğitmen kaldı! Biri seni\nalçaltacak!$"

BattlePyramid_Text_FourTrainersRemaining2::
	.string "Bu çok üzücü!\pAma dört eğitmen kaldı! Biri seni\nalçaltacak!$"

BattlePyramid_Text_ThreeTrainersRemaining2::
	.string "Bu çok üzücü!\pAma üç eğitmen kaldı! Biri seni\nalçaltacak!$"

BattlePyramid_Text_TwoTrainersRemaining2::
	.string "Bu çok üzücü!\pAma iki eğitmen kaldı! Biri seni\nalçaltacak!$"

BattlePyramid_Text_OneTrainersRemaining2::
	.string "Bu çok üzücü!\pAma bir eğitmen kaldı! Eminim\nalçakgönüllü olacaksın!$"

BattlePyramid_Text_ZeroTrainersRemaining2::
	.string "Bu çok üzücü!\pAma sizinle ilgilenebilecek başka\nEĞİTMEN yok!$"

BattlePyramid_Text_SevenTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pAma bu katta yedi tane daha ANTRENÖR\nvar. Hepsini yenebilir misin?$"

BattlePyramid_Text_SixTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pAma bu katta altı tane daha ANTRENÖR\nvar. Hepsini yenebilir misin?$"

BattlePyramid_Text_FiveTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pAma bu katta beş eğitmen daha var.\nHepsini yenebilir misin?$"

BattlePyramid_Text_FourTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pAma bu katta dört eğitmen daha var.\nHepsini yenebilir misin?$"

BattlePyramid_Text_ThreeTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pAma bu katta üç eğitmen daha var.\nHepsini yenebilir misin?$"

BattlePyramid_Text_TwoTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pAma bu katta iki eğitmen daha var.\nİkisini de yenebilir misin?$"

BattlePyramid_Text_OneTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pAma bu katta hâlâ bir eğitmen daha var.\nBaşarabilir misin?$"

BattlePyramid_Text_ZeroTrainersRemaining3::
	.string "Bu oldukça etkileyici!\pBu kattaki tüm eğitmenleri geçtin.$"

BattlePyramid_Text_SevenTrainersRemaining4::
	.string "Belki bu katta kalan yedi EĞİTİMCİYİ\nsüpürürsünüz.$"

BattlePyramid_Text_SixTrainersRemaining4::
	.string "Belki bu katta kalan altı EĞİTİMCİYİ\nsüpürürsünüz.$"

BattlePyramid_Text_FiveTrainersRemaining4::
	.string "Belki bu katta kalan beş EĞİTİMCİYİ\nsüpürürsünüz.$"

BattlePyramid_Text_FourTrainersRemaining4::
	.string "Belki bu katta kalan dört EĞİTİMCİYİ\ntarayabilirsiniz.$"

BattlePyramid_Text_ThreeTrainersRemaining4::
	.string "Belki bu katta kalan üç EĞİTİMCİYİ\nsüpürerek geçebilirsiniz.$"

BattlePyramid_Text_TwoTrainersRemaining4::
	.string "Belki bu katta kalan iki EĞİTİMCİYİ\nsüpürerek geçebilirsiniz.$"

BattlePyramid_Text_OneTrainersRemaining4::
	.string "Belki de bu katta kalan tek eğitmenle\ntaramanızı tamamlayabilirsiniz.$"

BattlePyramid_Text_ZeroTrainersRemaining4::
	.string "Artık seni yenebilecek tek bir kişi bile\nkalmadı…$"

BattlePyramid_Text_SevenTrainersRemaining5::
	.string "Kalan yedi uzman EĞİTMENİ yenmek için\ngerekenlere sahip olabilirsiniz.$"

BattlePyramid_Text_SixTrainersRemaining5::
	.string "Kalan altı uzman EĞİTMENİ yenmek için\ngerekenlere sahip olabilirsiniz.$"

BattlePyramid_Text_FiveTrainersRemaining5::
	.string "Kalan beş uzman EĞİTMENİ yenmek için\ngerekenlere sahip olabilirsiniz.$"

BattlePyramid_Text_FourTrainersRemaining5::
	.string "Geriye kalan dört uzman EĞİTMENİ\nyenmek için gerekenlere sahip\lolabilirsiniz.$"

BattlePyramid_Text_ThreeTrainersRemaining5::
	.string "Kalan üç uzman EĞİTMENİ yenmek için\ngerekenlere sahip olabilirsiniz.$"

BattlePyramid_Text_TwoTrainersRemaining5::
	.string "Kalan iki uzman EĞİTMENİ yenmek için\ngerekenlere sahip olabilirsiniz.$"

BattlePyramid_Text_OneTrainersRemaining5::
	.string "Geriye kalan tek uzman ANTRENÖRÜ\nyenmek için gerekenlere sahip\lolabilirsiniz.$"

BattlePyramid_Text_ZeroTrainersRemaining5::
	.string "Yeteneklerin tartışılmaz.\pBurada sizi yenme şansı olan başka\neğitmen yok.$"

BattlePyramid_Text_SevenTrainersRemaining6::
	.string "Kalan yedi ANTRENÖR'e karşı kazanmaya\ndevam edebilir misin?$"

BattlePyramid_Text_SixTrainersRemaining6::
	.string "Kalan altı ANTRENÖR'e karşı kazanmaya\ndevam edebilir misin?$"

BattlePyramid_Text_FiveTrainersRemaining6::
	.string "Kalan beş ANTRENÖR'e karşı kazanmaya\ndevam edebilir misin?$"

BattlePyramid_Text_FourTrainersRemaining6::
	.string "Kalan dört ANTRENÖR'e karşı\nkazanmaya devam edebilir misin?$"

BattlePyramid_Text_ThreeTrainersRemaining6::
	.string "Kalan üç ANTRENÖR'e karşı kazanmaya\ndevam edebilir misin?$"

BattlePyramid_Text_TwoTrainersRemaining6::
	.string "Kalan iki ANTRENÖR'e karşı kazanmaya\ndevam edebilir misin?$"

BattlePyramid_Text_OneTrainersRemaining6::
	.string "Kalan son ANTRENÖR'e karşı kazanmaya\ndevam edebilir misin?$"

BattlePyramid_Text_ZeroTrainersRemaining6::
	.string "Şu anda seni işe alabilecek bir eğitmen\nkalmadı.$"
