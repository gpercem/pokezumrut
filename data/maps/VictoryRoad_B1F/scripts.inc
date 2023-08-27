VictoryRoad_B1F_MapScripts::
	.byte 0

VictoryRoad_B1F_EventScript_Samuel::
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon::
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle::
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell::
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle::
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro:
	.string "POKéMON LİGİ'ne yaklaştığım\ndüşüncesi…\pHeyecandan titriyorum.$"

VictoryRoad_B1F_Text_SamuelDefeat:
	.string "Hiçbir şey yapamadım.$"

VictoryRoad_B1F_Text_SamuelPostBattle:
	.string "POKéMON LİGİ yine hayal oldu…\nNe hayal kırıklığı ama…$"

VictoryRoad_B1F_Text_ShannonIntro:
	.string "POKéMON LİGİ'ne ilerlemek için\nPOKéMON'unun güvenine ihtiyacın\lvar.$"

VictoryRoad_B1F_Text_ShannonDefeat:
	.string "İlişkiniz sağlam görünüyor.$"

VictoryRoad_B1F_Text_ShannonPostBattle:
	.string "Her zaman birlikte olan POKéMON'lar\nve EĞİTMENLER arasında güven zamanla\lartar.$"

VictoryRoad_B1F_Text_MichelleIntro:
	.string "Burada bulunmak hedefim değil.\pBurası sadece POKéMON LİGİ'ne\ngiden yolda bir durak.$"

VictoryRoad_B1F_Text_MichelleDefeat:
	.string "İşte böyle!$"

VictoryRoad_B1F_Text_MichellePostBattle:
	.string "Kesinlikle iyi iş çıkaracaksın!\nPOKéMON'larının hepsi gitmeye\lhevesli!$"

VictoryRoad_B1F_Text_MitchellIntro:
	.string "POKéMON'um hayranlık uyandırıcıdır!$"

VictoryRoad_B1F_Text_MitchellDefeat:
	.string "Daha önce senin gibi biriyle hiç\ntanışmamıştım.$"

VictoryRoad_B1F_Text_MitchellPostBattle:
	.string "Savaş dışında bile, senden ve\nPOKEMON'undan yayılan inanılmaz bir\lgüç hissediyorum.$"

VictoryRoad_B1F_Text_HalleIntro:
	.string "Tamam, heyecana gerek yok!\nSakin ol, sakin olalım!$"

VictoryRoad_B1F_Text_HalleDefeat:
	.string "Vay be!\nHarika!$"

VictoryRoad_B1F_Text_HallePostBattle:
	.string "Elbette, burası ZAFER YOLU.\pAma şimdiye kadar izlediğin yoldan\nçok da farklı değil.\pYolun geri kalanında her şeyin tadını\nçıkarmaya çalış!$"


