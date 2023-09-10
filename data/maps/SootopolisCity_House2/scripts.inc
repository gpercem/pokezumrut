SootopolisCity_House2_MapScripts::
	.byte 0

SootopolisCity_House2_EventScript_ExpertF::
	lock
	faceplayer
	msgbox SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SootopolisCity_House2_EventScript_KnowAboutOrbs
	call_if_eq VAR_RESULT, NO, SootopolisCity_House2_EventScript_DontKnowAboutOrbs
	release
	end

SootopolisCity_House2_EventScript_KnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_YesTwoOrbsSideBySide, MSGBOX_DEFAULT
	return

SootopolisCity_House2_EventScript_DontKnowAboutOrbs::
	msgbox SootopolisCity_House2_Text_OughtToVisitAndSee, MSGBOX_DEFAULT
	return

SootopolisCity_House2_Text_DidYouKnowAboutMtPyreOrbs:
	.string "PYRE DAĞI…\pZirvesinde yan yana yerleştirilmiş iki\nküre var. Bunu biliyor muydun?$"

SootopolisCity_House2_Text_YesTwoOrbsSideBySide:
	.string "Evet, iki küre yan yana.\pOnları bir arada görmek…\nOldukça rahatlatıcı…$"

SootopolisCity_House2_Text_OughtToVisitAndSee:
	.string "Öyle mi?\nBelki de ziyaret etmeli ve\lgörmelisin…$"


