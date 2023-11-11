.set LOCALID_WALDAS_DAD, 6

RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	waitstate
	goto_if_eq VAR_0x8004, 1, RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase::
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda::
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard:
	.string "Her gün çok zor geçiyor.\pZor olan ne diye soruyorsundur.\pHer gün yemek için ne yapacağımı bulmaya\nçalışmak.\pHer gün yemek bulmak gerçekten kolay\ndeğil.$"

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase:
	.string "Merhaba! PEPPER ailesinin evine\nhoş geldin.\pSana bir sorum var.\nHiç bebek bakıcılığı yaptın mı?\pBen yeni bir babayım, yani çocuk\nyetiştirmek benim için yeni bir şey.\pVe bir sorunum var. Kızım WALDA\nyeterince gülmüyor.\pOna komik bir şey söylesem belki\ngülebilir.\pBana söyleyebileceğin komik bir kelime\nya da söz var mı?$"

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase:
	.string "Son zamanlarda onu eğlendirmek için\n{STR_VAR_1} diyorum.\pDaha iyi bir kelime ya da\nsöz biliyor musun?$"

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
	.string "Bu harika.\nÖnerini duyayım.$"

RustboroCity_Flat1_2F_Text_OhIsThatRight:
	.string "Öyle mi?\pEğer iyi bir öneriyle gelirsen\ncan kulağıyla dinlerim.$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
	.string "Anlıyorum.\nBir deneyelim, olur mu?$"

RustboroCity_Flat1_2F_Text_OhShesLaughing:
	.string "{STR_VAR_1}.\n{STR_VAR_1}.\pEvet! Gülüyor!\nBen de onun kadar mutluyum!$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
	.string "Ah, anlıyorum.\nBir deneyelim, olur mu?$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
	.string "{STR_VAR_1}. {STR_VAR_1}.\pHmmm… Hiç gülümsemiyor.\nBelki de WALDA ciddi bir\lçocuktur…$"

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
	.string "Demek hiç güzel kelime bilmiyorsun.\nO zaman kendim düşünsem iyi olur.\pHmm… {STR_VAR_1} nasıl olur?\nBakalım işe yarayacak mı?$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
	.string "{STR_VAR_1}. {STR_VAR_1}.\pHmmm… Hiç gülümsemiyor.\nBelki de WALDA ciddi bir\lçocuktur…$"

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
	.string "Demek hiç güzel kelime bilmiyorsun.\nSanırım onu daha önce kullandığım\ldeyimle eğlendirmeye çalışacağım.\pHer neyse, iyi bir önerin varsa bana\nsöylemekten çekinme, tamam mı?$"

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper:
	.string "Teşekkür ederim!\pSayende, WALDA'm benim için güldü!\pAslında o kadar da özel görünmüyor\nolabilirim ama DEVON ŞİRKETİ'nin en\liyi araştırmacılarından biriyim.\pPeki, karşılığında bir şey yapmama ne\ndersin?\pBuldum! PC POKéMON Depolama\nSistemindeki KUTULAR için bazı yeni\lduvar kağıdı desenleri ekleyeceğim.\pDuvar kağıdı deseni menüsünden\nARKADAŞLAR'ı seç.\pBu sana yeni duvar kağıdı desenlerine\nerişim sağlayacaktır.$"

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
	.string "Bu bir POKéMON peluş bebeği!$"


