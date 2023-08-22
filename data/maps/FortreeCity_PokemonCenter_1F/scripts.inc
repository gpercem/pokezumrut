.set LOCALID_NURSE, 1

FortreeCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man::
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy::
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone:
	.string "Dinle, çocuk, bir POKéDEX üzerinde\n"
	.string "çalışıyorsun?\p"
	.string "SAFARİ BÖLGESİNE git.\n"
	.string "Sana tavsiyem bu.$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat:
	.string "Hiç REKOR KÖŞESİNDE bir şey\n"
	.string "başardın mı?\p"
	.string "Gayet düzenli. EĞİTMENLERİN rekorlarını\n"
	.string "karıştırır ve eşler.\p"
	.string "Nasıl çalıştığını pek bilmiyorum,\n"
	.string "çok havalı. Epey heyecan verici!$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav:
	.string "Ah, vaov, POKéNAV'in var!\n"
	.string "Hem de benimkinden!\p"
	.string "POKéNAV'in DİREKT ARAMA sistemini\n"
	.string "biliyor muydun?\p"
	.string "Kullan ve kayıtlı EĞİTMENLER ile\n"
	.string "istediğin zaman sohbet et.\p"
	.string "Ayrıca sana seninle rövanş maçı\n"
	.string "yapmak isteyen EĞİTMENLERİ gösterir.\p"
	.string "Gerçekten şık! Bu DEVON adamları\n"
	.string "ne yaptıklarını iyi biliyorlar!$"

