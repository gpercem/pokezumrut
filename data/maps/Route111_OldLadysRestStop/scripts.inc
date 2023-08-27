Route111_OldLadysRestStop_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route111_OldLadysRestStop_OnTransition
	.byte 0

Route111_OldLadysRestStop_OnTransition:
	setflag FLAG_LANDMARK_OLD_LADY_REST_SHOP
	end

Route111_OldLadysRestStop_EventScript_OldLady::
	lock
	faceplayer
	msgbox Route111_OldLadysRestStop_Text_RestUpHere, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_Rest::
	msgbox Route111_OldLadysRestStop_Text_TakeYourTimeRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route111_OldLadysRestStop_EventScript_Rest
	goto_if_eq VAR_RESULT, NO, Route111_OldLadysRestStop_EventScript_DeclineRest
	end

Route111_OldLadysRestStop_EventScript_DeclineRest::
	msgbox Route111_OldLadysRestStop_Text_DontNeedToBeShy, MSGBOX_DEFAULT
	release
	end

Route111_OldLadysRestStop_Text_RestUpHere:
	.string "Ah, canım benim.\nPOKéMON'un yorulmadı mı?\pİstersen burada dinlenebilirsin.\nBu iyi bir fikir olur. Hadi, dinlen.$"

Route111_OldLadysRestStop_Text_TakeYourTimeRestUp:
	.string "Hadi, acele etme.\nDinlen biraz!$"

Route111_OldLadysRestStop_Text_StillTiredTakeAnotherRest:
	.string "Ah, canım benim.\nPOKéMON'ların hala yorgun mu?\pBurada biraz daha dinlenebilirsin.\nBu iyi bir fikir olur. Hadi, dinlen.$"

Route111_OldLadysRestStop_Text_DontNeedToBeShy:
	.string "Öyle mi?\nBu konuda utanmana gerek yok.$"


