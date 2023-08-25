Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "Hey! {PLAYER}{KUN}!\pHer yer bu kadar dağınık olduğu için\nüzgünüm… Araştırmaya daldığımda, her\lşey bu hale geliyor…\pBu utanç verici… Lütfen bunun\nkarşılığında bunu bir sır olarak\lsakla.$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "POKéMON Depolama Sistemim hakkında\ntavsiyede bulunabilir miyim?\pKutularını, içlerinde hangi\nPOKéMON'un olduğunu anlayabileceğin\lşekilde düzenlemelisin.$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "LANETTE'in araştırma notları.\nKutular hakkında bilgi var.\pKutuları her biri 30 POKéMON alacak\nşekilde tasarladım.\pHer bir EĞİTMEN, PC sisteminde 420\nPOKéMON depolayabilir.\pOkumaya devam edecek misin?$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "POKéMON'un düzenlenmesini\nkolaylaştırmak için bir işaretleme\lsistemi ekledim.\pHer bir kutu adını ve duvar kağıdı\ntasarımını, saklanan POKéMON'u memnun\letmek için değiştirilebilir hale\lgetirdim.\pOkumaya devam edecek misin?$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "Bir POKéMON depolanırken, en son\nincelenen kutuya gönderiliyor.\pEğer bu kutu doluysa, alınan POKéMON\nbir sonraki kutuda saklanır.\pBaşka bir deyişle, bir kutu\nincelendiğinde, otomatik olarak\lPOKéMON'un gönderileceği kutu olarak\lseçilir.$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "{PLAYER} defteri kapattı.$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "Bilgisayarda birinden bir e-posta var.\p… … … … … … …\pDepolama Sisteminiz benimkinden daha\nfazla kolaylık sunuyor.\pEğlenceli ve kullanışlı kılan pek çok\nkullanıcı dostu özelliği de var.\pGeliştirilmesinde rol oynadığım için\ngurur duyuyorum.\pDepolama Sistemleri konusundaki\naraştırmalarınıza devam edeceğinizi\lumuyorum.\pİmza: BİLL\n… … … … … … … … …$"


