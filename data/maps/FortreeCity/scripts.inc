FortreeCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition:
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man::
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible::
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl::
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan::
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy::
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid::
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign::
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign::
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon::
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE
	goto_if_eq VAR_RESULT, TRUE, FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope::
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope::
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee:
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky:
	.string "Kimse bana inanmıyor ama\n"
	.string "havada devasa bir pokemon gördüm.\p"
	.string "O sanki Rota 131'e kıvrılarak\n"
	.string "uçuyordu.\p"
	.string "Bu arada… (koklar)…\n"
	.string "Um… Sen, ah…yanık kokuyorsun.\p"
	.string "Volkan veya ona benzer bir yerde miydin?$"

FortreeCity_Text_SomethingBlockingGym:
	.string "Pokemon salonuna girmek istiyorum,\n"
	.string "fakat bir şey yolu kapatıyor.\p"
	.string "Bunca zahmetten sonra eğitimime\n"
	.string "Rota 120'de devam ettim…$"

FortreeCity_Text_ThisTimeIllBeatWinona:
	.string "Yanıma gururlu-ve-neşeli pokemonlarımı\n"
	.string "aldım. Bu sefer, WİONA'yı yeneceğim.$"

FortreeCity_Text_TreesGrowByDrinkingRainwater:
	.string "Toprak yağmur suyunu emer, ve\n"
	.string "ağaçlar bu suyu tüketir…\p"
	.string "Bizim Fortree Şehrimiz oluştu çünkü\n"
	.string "burada su ve toprak var.$"

FortreeCity_Text_EveryoneHealthyAndLively:
	.string "Şehir ağaçların üzerindeki evlerden\n"
	.string "oluşuyor.\p"
	.string "Belki de bu yaşam tarzı sayesinde,\n"
	.string "herkes sağlıklı ve canlı.\p"
	.string "Nedense ben bile-- burada kendimi\n"
	.string "otuz yaş genç hissediyorum.$"

FortreeCity_Text_BugPokemonComeThroughWindow:
	.string "Ağaçların tepesinde yaşamak güzel.\p"
	.string "Bazı BÖCEK POKEMONLAR camdan içeriye\n"
	.string "doğru giriyorlar.\l"
	.string "Bazen çok ürkünç olabiliyorlar.$"

FortreeCity_Text_PokemonThatEvolveWhenTraded:
	.string "Duyduğuma göre bazı POKEMONLAR sen\n"
	.string "onları takas ettiğinde evrimleşebiliyormuş.$"

FortreeCity_Text_SomethingUnseeable:
	.string "Bu yolda görülemeyen bir şey var.$"

FortreeCity_Text_UnseeableUseDevonScope:
	.string "Bu yolda görülemeyen bir şey var.\p"
	.string "DEVON DÜRBÜNÜ'NÜ kullanmak ister misin?$"

FortreeCity_Text_UsedDevonScopePokemonFled:
	.string "{PLAYER} DEVON DÜRBÜNÜ'NÜ kullandı.\p"
	.string "Görünmez bir POKEMON başarıyla görünür\n"
	.string "hale geldi!\p"
	.string "Ürkünç POKEMON kaçtı!$"

FortreeCity_Text_CitySign:
	.string "FORTREE CITY\n"
	.string "“Bu ağaçüstü şehir doğayla bir\l"
	.string "bütündür.”$"

FortreeCity_Text_GymSign:
	.string "FORTREE ŞEHRİ POKEMON SALONU\n"
	.string "LİDER:WİONA\p"
	.string "Dünyaya doğru uçan kuş\n"
	.string "kullanıcısı.”$"

