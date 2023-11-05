BattleFrontier_Lounge5_MapScripts::
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown::
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman::
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt::
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy::
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting::
	.string "Ehehe! POKéMON'un ne düşündüğünü\nanlayabiliyorum!\pLütfen! POKéMON'unu görebilir miyim?$"

BattleFrontier_Lounge5_Text_NatureGirlNoneShown::
	.string "Yuh! Ucuzcu!$"

BattleFrontier_Lounge5_Text_NatureGirlHardy::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Çok\nfazla ahı olsa bile savaşacak!$"

BattleFrontier_Lounge5_Text_NatureGirlLonely::
	.string "Hmhm…\pBu sinsi olmayı sevdiğini söylüyor! Ama\nyeterince acı çekerse, karşılık\lverecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlBrave::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Ama\nyeterince ah alırsa, kendisi için\lendişelenecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlAdamant::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Çok\nfazla ahı olsa bile savaşacak!$"

BattleFrontier_Lounge5_Text_NatureGirlNaughty::
	.string "Hmhm…\pBu kendi başının çaresine baktığını\nsöylüyor! Ama eğer yeteri kadar ah\lalırsa, karşılık verecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlBold::
	.string "Hmhm…\pBu sinsi olmayı sevdiğini söylüyor! Ama\nyeterince ah alırsa, kendisi için\lendişelenecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Çok\nfazla ahı olsa bile savaşacak!$"

BattleFrontier_Lounge5_Text_NatureGirlRelaxed::
	.string "Hmhm…\pBu sinsi olmayı sevdiğini söylüyor! Ama\nyeterince acı çekerse, karşılık\lverecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlImpish::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Ama\nyeterince ah alırsa, kendisi için\lendişelenecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlLax::
	.string "Hmhm…\pBu sinsi olmayı sevdiğini söylüyor! Bir\nsürü ahı olsa bile sinsi olmayı\lsevdiğini söylüyor!$"

BattleFrontier_Lounge5_Text_NatureGirlTimid::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Ama\nyeterince ah alırsa, sinsileşir!$"

BattleFrontier_Lounge5_Text_NatureGirlHasty::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Çok\nfazla ahı olsa bile savaşacak!$"

BattleFrontier_Lounge5_Text_NatureGirlSerious::
	.string "Hmhm…\pBu sinsi olmayı sevdiğini söylüyor! Bir\nsürü ahı olsa bile sinsi olmayı\lsevdiğini söylüyor!$"

BattleFrontier_Lounge5_Text_NatureGirlJolly::
	.string "Hmhm…\pBu sinsi olmayı sevdiğini söylüyor! Ama\nyeterince ah alırsa, kendisi için\lendişelenecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlModest::
	.string "Hmhm…\pBu, kendi başının çaresine baktığını\nsöylüyor! Çok fazla ahı olsa da olmasa\lda kendisi için endişelendiğini\lsöylüyor!$"

BattleFrontier_Lounge5_Text_NatureGirlMild::
	.string "Hmhm…\pBu kendi başının çaresine baktığını\nsöylüyor! Ama eğer yeteri kadar ah\lalırsa, sinsileşecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlBashful::
	.string "Hmhm…\pBu, kendi başının çaresine baktığını\nsöylüyor! Bir sürü ahı olsa bile\lkendisi için endişelendiğini söylüyor!$"

BattleFrontier_Lounge5_Text_NatureGirlRash::
	.string "Hmhm…\pBu sinsi olmayı sevdiğini söylüyor! Bir\nsürü ahı olsa bile sinsi olmayı\lsevdiğini söylüyor!$"

BattleFrontier_Lounge5_Text_NatureGirlCalm::
	.string "Hmhm…\pBu, kendi başının çaresine baktığını\nsöylüyor! Bir sürü ahı olsa bile\lkendisi için endişelendiğini söylüyor!$"

BattleFrontier_Lounge5_Text_NatureGirlGentle::
	.string "Hmhm…\pBu kendi başının çaresine baktığını\nsöylüyor! Ama eğer yeteri kadar ah\lalırsa, karşılık verecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlSassy::
	.string "Hmhm…\pBu, savaşmayı sevdiğini söylüyor! Ama\nyeterince ah alırsa, sinsileşir!$"

BattleFrontier_Lounge5_Text_NatureGirlCareful::
	.string "Hmhm…\pBu kendi başının çaresine baktığını\nsöylüyor! Ama eğer yeteri kadar ah\lalırsa, sinsileşecektir!$"

BattleFrontier_Lounge5_Text_NatureGirlEgg::
	.string "Bu çok aptalca! Bir yumurta uyuyor!\nOnunla konuşamam!$"

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon::
	.string "Ne kadar büyüleyici! Bu küçük bayan\nPOKéMON'u anlayabildiğini iddia\lediyor!$"

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound::
	.string "Küçük kızın çok derin bir şey\nsöylediğini hissediyorum.$"

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot::
	.string "Bir şey biliyorum!\pO küçük kız kırmızı evde çok oynuyor!$"


