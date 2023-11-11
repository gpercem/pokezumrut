ProfileMan_EventScript_Man::
	lock
	faceplayer
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_GivenProfileBefore
	msgbox ProfileMan_Text_CollectTrainerProfiles, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_AskToSeeProfile::
	msgbox ProfileMan_Text_MayISeeYourProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateProfile
	case 1, ProfileMan_EventScript_DeclineShowProfile
	case 2, ProfileMan_EventScript_Info
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineShowProfile
	end

ProfileMan_EventScript_Info::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeProfile
	end

ProfileMan_EventScript_CreateProfile::
	msgbox ProfileMan_Text_LetsSeeItThen, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_CancelShowProfile::
	msgbox ProfileMan_Text_NotIntoItRightNow, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_ShowProfile::
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox ProfileMan_Text_FantasticProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_DeclineShowProfile::
	msgbox ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile, MSGBOX_DEFAULT
	release
	end

ProfileMan_EventScript_GivenProfileBefore::
	msgbox ProfileMan_Text_YouHaveWonderfulSmile, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_AskToSeeNewProfile::
	msgbox ProfileMan_Text_MayISeeYourNewProfile, MSGBOX_DEFAULT
	multichoice 17, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, ProfileMan_EventScript_CreateNewProfile
	case 1, ProfileMan_EventScript_DeclineNewProfile
	case 2, ProfileMan_EventScript_InfoNewProfile
	case MULTI_B_PRESSED, ProfileMan_EventScript_DeclineNewProfile
	end

ProfileMan_EventScript_InfoNewProfile::
	msgbox ProfileMan_Text_EasyChatExplanation, MSGBOX_DEFAULT
	goto ProfileMan_EventScript_AskToSeeNewProfile
	end

ProfileMan_EventScript_CreateNewProfile::
	msgbox ProfileMan_Text_EvenBetterThanLastProfile, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, ProfileMan_EventScript_CancelShowProfile
	goto_if_eq VAR_RESULT, 1, ProfileMan_EventScript_ShowProfile
	end

ProfileMan_EventScript_DeclineNewProfile::
	msgbox ProfileMan_Text_LikeProfileWayItIs, MSGBOX_DEFAULT
	release
	end

@ Unused
ProfileMan_EventScript_Ret::
	return

ProfileMan_Text_CollectTrainerProfiles:
	.string "Merhaba, eğitmen!\nHarika bir gülümsemen var.\pBenim bir hobim var - POKéMON\nEĞİTMENLERİNİN profillerini toplamak.$"

ProfileMan_Text_MayISeeYourProfile:
	.string "Ee, ne dersin?\nProfilini görebilir miyim?$"

ProfileMan_Text_EasyChatExplanation:
	.string "Dört kelime veya cümleyi bir araya\ngetirerek kendi profilini\loluşturursun.\pBurada sana dört metin parçasını\nkullanan bir profil örneği\lgöstereceğim.\pKendi profilini oluşturmak için bu\ndört parçayı istediğin şekilde başka\lmetin parçalarıyla değiştirebilirsin.\pKullanabileceğin çok sayıda metin\nparçası vardır.\pBunlar POKéMON, yaşam tarzları ve\nhobiler gibi gruplar halinde\ldüzenlenmiştir, böylece onları aramak\ldaha kolaydır.\pBu yüzden, ilk olarak, bir seçenek\nlistesini görüntülemek için\lmetin parçaları grubunu seç.\pArdından, istediğin seçeneği seç.\pKalan metin seçenekleri için\ntekrarla ve kendi profilini yap.$"

ProfileMan_Text_LetsSeeItThen:
	.string "Evet! Evet! Teşekkür ederim!\nGörelim o zaman.$"

ProfileMan_Text_ImagineYouWouldHaveWonderfulProfile:
	.string "Ne, gerçekten mi?\pSenin gibi birinin harika bir profili\nolacağını hayal ediyorum…$"

ProfileMan_Text_NotIntoItRightNow:
	.string "Ha? Şu an ilgilenmiyor musun?\pBenim için her zaman uygun!$"

ProfileMan_Text_YouHaveWonderfulSmile:
	.string "Merhaba, eğitmen!\nHarika bir gülümsemen var.$"

ProfileMan_Text_MayISeeYourNewProfile:
	.string "Yeni profilini görebilir miyim?$"

ProfileMan_Text_EvenBetterThanLastProfile:
	.string "Evet! Evet! Teşekkür ederim!\pUmarım bana daha önce gösterdiğin\nprofilden daha iyidir.$"

ProfileMan_Text_LikeProfileWayItIs:
	.string "Profilini bu haliyle seviyorsun.\pSeni suçlamıyorum, şu anki haliyle\nharika bir profil.$"

ProfileMan_Text_FantasticProfile:
	.string "F-fantastik!\pProfilin, harika! Gerçekten\ntam da seni anlatıyor.\pBu profili duyan herkes senin büyüne\nkapılır!\pTeşekkür ederim!$"

ProfileMan_Text_YouKnowSecretSaying:
	.string "Oh? Gizli deyişi biliyorsun!\pBu, artık GİZEMLİ OLAY KULÜBÜ'nün bir\nüyesi olduğunuz anlamına geliyor!$"
