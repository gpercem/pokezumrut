.set LOCALID_SUDOWOODO, 14

BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "Burası SAVAŞ KULESİ!\nEn zorlu EĞİTMENLERE karşı\nseri sürdürün!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "Burası SAVAŞ SARAYI!\nGözünüz POKéMON savaşlarında olsun!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "Burası SAVAŞ ARENASI!\nEn zorlu takımlar toplansın!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "Burası SAVAŞ PİRAMİDİ!\nSavaş görevi boyunca ilerleyin!$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "SAVAŞ SINIRI SIRALAMA SALONU\nGözünüzü yeni rekorlara dikin!$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "SAVAŞ PUANI TAKAS SERVİSİ KÖŞESİ\nSavaş Puanlarınızı değiştirin!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "Vay canına! Çok büyük!\pSAVAŞ KULESİ özel hissettiriyor.\nDiğerlerinden farklı.$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "En büyük arzum hem SAVAŞ SINIRI'nı\nhem de POKéMON LİGİ'ni fethetmek.\pVe eğer hayallerim gerçekleşirse.\pBen… Ben yan komşum Mimi'ye benimle\narkadaş olup olamayacağını soracağım!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "SAVAŞ PİRAMİDİ çok sert! Zirveye\nçıkamıyorum!\pBaşka seçeneğim olmadığına göre, belki\ndışarıdan tırmanabilirim…$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "Karanlıkta büyürüm… Evet… Bana\nlayık olan nedir? SAVAŞ PİRAMİDİ'nden\lbaşkası değil.\pKaranlıkta ve tam bir çaresizlik içinde\ndolaşmaya ne dersiniz?$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "Bir hafta boyunca uyumadım ama sonra\nen iyi takımı kurdum!\pKendimi kaybederken göremiyorum, şaka\ndeğil. SAVAŞ ARENASI'na giriyoruz!$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "Seni de mi buraya SCOTT getirdi? Bu\nadamın nesi var böyle?\pYetenekli eğitmenleri nasıl tespit\nedeceğini gerçekten biliyor gibi\lgörünüyor ama…\pOnu hiç şahsen savaşırken görmedim.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "ZIGG! Sana güveniyorum, dostum!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "ZIGZAGOON boş boş bakıyor…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "İnsanlar bana işgüzar diyor ama elimde\ndeğil.\pŞapkan eğri duruyor! Oh, hayır, çöpler\nyerde! Oops, neredeyse yemek vakti!\pSAVAŞ SARAYI'nda sadece izlemeye\ndayanabilir miyim bilmiyorum…$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "Şu anda o kadar etkileyici görünmüyor\nolabilirim ama bir zamanlar SALON\lLİDERLERİNİ yenmiştim.\pKim bilir, belki de zafer için bir şans\ndaha vermeliyim.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "BİSİKLET üzerinde hızlıyım ve bu dövüş\ntarzım için de geçerli.\pMaçları göz açıp kapayıncaya kadar\nkazanırım!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "POKéMON'da babamdan daha iyiyim.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "Devam et, tatlım!\nGit baban için birkaç\lgalibiyet al!\pTıpkı annen gibisin, bu yüzden baskın\nolacaksın!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "Buraya gelmek kolay olmadı ama BATTLE\nARENA'daki bu güzel kızı duymuştum.\pOnun yerine ne buldum biliyor musunuz?\pTerli, pis kokulu ve ilkel dövüş\nsanatçılarından oluşan bir kalabalık!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "Bazen gerçekten önemli görünen yaşlı\nbir adamın oraya girdiğini görüyorum.\pElinde gerçekten harika POKéMON'lar\nvar. Gerçekten iyi birine benziyor.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "Şunu biliyor muydun?\nSAVAŞ PİRAMİDİ efsanesini?\pAltın zirveye ulaşan kendinden emin bir\nEĞİTİMCİ geldiğinde, insanlar arasında\lbir adam ortaya çıkacaktır.\pBu efsaneyi bilmiyor musunuz? Tabii ki\nbilmiyorum! Ben uydurdum!\pBu ne anlama geliyor? Bunu söyleyemem\ndostum!$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "Adamım! Ah adamım!\nDaha önce hiç kaybetmemiştim!\pAma hiçbir kurtarıcı lütuf olmadan\nsilindim!\pVe sonra bana yeteneğim olmadığı mı\nsöylendi?! Adamım!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "Bu adam SAVAŞ KULESİ\nmücadelesindeyken korkunç derecede\lzorlu bir ANTRENÖRLE karşılaştı.\pŞimdi ona bir bakın.\pSAVAŞ KULESİ'ne gitmeye karar\nverirseniz dikkatli olmanız gerekir.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "Evet! Sonunda yeterince Savaş Puanım\nvar!\pSanırım başka bir dev peluş bebekle\ntakas edeceğim!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "Oh, evet, tamam! Demek burası SIRALAMA\nSALONU!\pTarihe süper bir şampiyon olarak\ngeçmek ve adımı gelecek nesiller için\lburaya yazdırmak istiyorum.$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "Sen yanımdayken her şeyi yapabilirim.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "Aah, harikasın canım!\pOoh, artık bekleyemiyorum!\pHadi MULTİ SAVAŞ ODASI'na\ngidelim hemen!\pSAVAŞ SALONU'na girersek eğer\nsevgimizi herkes görebilir!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "SAVAŞ SINIRI sadece zorlu\nEĞİTMENLER için değildir.\pGörünüşe göre özel yetenekleri olan\nbirçok kişi davet edilmiş.\pŞu adam SCOTT…\pBurayı daha büyük bir amaca hizmet\netmek için inşa etmiş olabilir.$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "Affedersin, genç adam. Gözleriniz iyi\ngörüyor mu?\pBuradan geçen garip bir ağaç var ve\nyorgun gözlerime kıpır kıpır\lgörünüyor.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "Affedersin, genç adam. İyi bir\nhafızanız var mı?\pBir zamanlar burada garip bir ağaç\nvarmış gibi hissediyorum.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "Ben… Ben onu gördüm!\pİleride uzun kuyruklu, yapışkan bir\ntür POKéMON vardı!\pBir kayanın altında saklanıyordu ve\nbana bakıp duruyordu!$"
