MtPyre_1F_MapScripts::
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag::
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF::
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man::
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood:
	.string "Birçok türden varlık PYRE DAĞI\nyamaçlarında dolaşır durur…\pNe olacağı belli olmaz. Al bunu.\nBu senin iyiliğin için.$"

MtPyre_1F_Text_ExplainCleanseTag:
	.string "Bir POKéMON'a TEMİZ ETİKET vererek\nkendini vahşi POKéMON'lardan\luzak tutabilirsin.$"

MtPyre_1F_Text_ComeToPayRespects:
	.string "Ölen POKéMON'ların ruhlarına saygı\ngöstermek için mi geldin?\pPOKéMON'una çok değer veriyor\nolmalısın.$"

MtPyre_1F_Text_RestingPlaceOfZigzagoon:
	.string "Burası benim ZIGZAGOON'umun son\ndinlenme yeri.\lOnu çok seviyordum.$"


