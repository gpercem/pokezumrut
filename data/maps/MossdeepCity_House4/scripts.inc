MossdeepCity_House4_MapScripts::
	.byte 0

MossdeepCity_House4_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, MossdeepCity_House4_EventScript_CanBattleAtSecretBases
	msgbox MossdeepCity_House4_Text_BrotherLikesToFindBases, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_CanBattleAtSecretBases::
	msgbox MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NinjaBoy::
	lock
	faceplayer
	special CheckPlayerHasSecretBase
	goto_if_eq VAR_RESULT, FALSE, MossdeepCity_House4_EventScript_NoSecretBase
	special GetSecretBaseNearbyMapName
	msgbox MossdeepCity_House4_Text_YouMadeSecretBaseNearX, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_NoSecretBase::
	msgbox MossdeepCity_House4_Text_MakeSecretBase, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House4_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox MossdeepCity_House4_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MossdeepCity_House4_Text_BrotherLikesToFindBases:
	.string "Küçük kardeşim insanların GİZLİ\nÜSLERİNİ bulmayı sevdiğini söylüyor.$"

MossdeepCity_House4_Text_BrotherLikesToVisitBasesAndBattle:
	.string "Küçük kardeşim insanların GİZLİ\nÜSLERİNİ ziyaret etmeyi ve POKéMON\lsavaşları yapmayı sevdiğini söylüyor.$"

MossdeepCity_House4_Text_YouMadeSecretBaseNearX:
	.string "{STR_VAR_1} yakınında bir\nGİZLİ ÜS kuran sen miydin?$"

MossdeepCity_House4_Text_MakeSecretBase:
	.string "Bir yerlerde gizli bir üs kurmalısın.\nGidip bulacağım!$"

MossdeepCity_House4_Text_Skitty:
	.string "SKİTTY: Miyaan?$"


