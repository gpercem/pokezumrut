RustboroCity_CuttersHouse_MapScripts::
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM01, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM01
	setflag FLAG_RECEIVED_HM01
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
	.string "Bu kararlı ifaden…\nBu kıvrak hareketlerin…\lVe iyi eğitilmiş POKéMON'ların…\pBelli ki yetenekli bir eğitmensin!\pHayır, bekle, tek kelime etme.\nSadece sana bakarak bile\lsöyleyebilirim.\pEminim bu GİZLİ MAKİNEYİ iyi bir şekilde\nkullanabilirsin.\pMütevazı ya da utangaç olmaya gerek\nyok. Hadi, al bunu!$"

RustboroCity_CuttersHouse_Text_ExplainCut:
	.string "Bu GİZLİ MAKİNE veya kısaca HM;\nCUT, yani KESME saldırısını içerir.\pBir HM saldırısı, POKéMON tarafından\nsavaş dışında kullanılabilen bir\lsaldırısıdır.\pKesmeyi öğrenen herhangi bir POKéMON,\neğitmeni TAŞ ROZETİ'ni kazandıysa ince\lağaçları kesebilir.\pVe bir TM'nin aksine, bir HM birden fazla\nkez kullanılabilir.$"

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
	.string "RUSTBORO şehri genişletirlerken babam\nda yardım etti.\pArazideki ağaçları temizlemek için\nPOKéMON'una KESME'yi kullandırdı.$"


