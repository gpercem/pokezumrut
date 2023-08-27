VictoryRoad_B2F_MapScripts::
	.byte 0

VictoryRoad_B2F_EventScript_Vito::
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen::
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline::
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie::
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix::
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne::
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro:
	.string "Tüm ailemle birlikte çalıştım!\nArtık kimse beni yenemez!$"

VictoryRoad_B2F_Text_VitoDefeat:
	.string "Ailemden daha mı iyisin?!\nBu mümkün mü?!$"

VictoryRoad_B2F_Text_VitoPostBattle:
	.string "Ailemdeki herkesten daha iyiydim.\nDaha önce hiç kaybetmemiştim.\pGüvenimi kaybettim. Belki eve giderim.$"

VictoryRoad_B2F_Text_OwenIntro:
	.string "Etrafta sert bir çocuk olduğunu\nduymuştum. Seni mi kastediyorlar?$"

VictoryRoad_B2F_Text_OwenDefeat:
	.string "Bu karides çok güçlü!$"

VictoryRoad_B2F_Text_OwenPostBattle:
	.string "Duyduğum dedikodulara göre, o sert\nçocuk PETALBURG şehrindenmiş.$"

VictoryRoad_B2F_Text_CarolineIntro:
	.string "Biraz yorulmuş olmalısın.$"

VictoryRoad_B2F_Text_CarolineDefeat:
	.string "Hiç yorulma belirtin yok!$"

VictoryRoad_B2F_Text_CarolinePostBattle:
	.string "ZAFER YOLU ve POKéMON LİGİ uzun ve\nyorucu mücadelelerdir.\lYorgunluğa dikkat et!$"

VictoryRoad_B2F_Text_JulieIntro:
	.string "Çok sayıda salon rozetin var diye\nrehavete kapılmamalısın.\pHer zaman senden daha iyi olan biri\nolacaktır!$"

VictoryRoad_B2F_Text_JulieDefeat:
	.string "Sen benden daha iyisin!$"

VictoryRoad_B2F_Text_JuliePostBattle:
	.string "Topladığın rozetlere bak ve\nkarşılaştığın EĞİTMENLERİ hatırla.$"

VictoryRoad_B2F_Text_FelixIntro:
	.string "Buraya kadar geldim, ama gerginlik\nmideme korkunç bir ağrı veriyor…$"

VictoryRoad_B2F_Text_FelixDefeat:
	.string "Oof…\nAğrıyor…$"

VictoryRoad_B2F_Text_FelixPostBattle:
	.string "POKéMON LİGİ'ne yaklaştığımı bildiğim\niçin gerilmekten kendimi\lalamıyorum.\pSakin görünmek için elimden geleni\nyapıyorum.$"

VictoryRoad_B2F_Text_DianneIntro:
	.string "Seçkinler arasındaki seçkinler bu\nmağarada toplanıyor.\pNasıl buldun?$"

VictoryRoad_B2F_Text_DianneDefeat:
	.string "Zerre kadar sarsılmadım!$"

VictoryRoad_B2F_Text_DiannePostBattle:
	.string "Cesaretin var!\nBu hoşuma gitti! Devam et!$"


