VerdanturfTown_Mart_MapScripts::
	.byte 0

VerdanturfTown_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart VerdanturfTown_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
VerdanturfTown_Mart_Pokemart:
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_NEST_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPECIAL
	.2byte ITEM_FLUFFY_TAIL
	.2byte ITEM_NONE
	release
	end

VerdanturfTown_Mart_EventScript_Boy::
	msgbox VerdanturfTown_Mart_Text_XSpecialIsCrucial, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_ExpertF::
	msgbox VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent, MSGBOX_NPC
	end

VerdanturfTown_Mart_EventScript_Lass::
	msgbox VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon, MSGBOX_NPC
	end

VerdanturfTown_Mart_Text_XSpecialIsCrucial:
	.string "Herhangi bir POKéMON maçı için X ÖZEL\neşyası çok önemlidir.\pSadece bir savaş için olsa bile\nbazı saldırıların gücünü artırır.$"

VerdanturfTown_Mart_Text_NoStrategyGuidesForBattleTent:
	.string "SAVAŞ ÇADIRI için herhangi bir kazanma\nstratejisi kılavuzu satmıyor gibi\lgörünüyorlar…\pGörünüşe göre insan kendi aklına\ngüvenmek zorunda…$"

VerdanturfTown_Mart_Text_NestBallOnWeakenedPokemon:
	.string "YUVA TOPU zayıflamış POKéMON'lar\nüzerinde daha iyi çalışır.\pVERDANTURF onu satın alabileceğin\ntek yerdir.$"


