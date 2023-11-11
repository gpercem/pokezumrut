Roulette_EventScript_Table1::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 0
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Table2::
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NoCoinCase
	setvar VAR_0x8004, 1
	getpokenewsactive POKENEWS_GAME_CORNER
	goto_if_eq VAR_RESULT, FALSE, Roulette_EventScript_Play
	addvar VAR_0x8004, ROULETTE_SPECIAL_RATE
	goto Roulette_EventScript_Play
	end

Roulette_EventScript_Play::
	special PlayRoulette
	waitstate
	end

Roulette_Text_PlayMinimumWagerIsX::
	.string "Buradaki en düşük giriş {STR_VAR_1}.\n"
	.string "Oynamak ister misin?$"

Roulette_Text_NotEnoughCoins::
	.string "Yeterli JETON yok.$"

Roulette_Text_SpecialRateTable::
	.string "Özel masa gelsin!$"

Roulette_Text_ControlsInstruction::
	.string "İstediğini kontrol tuşları ile\n"
	.string "seç ve A tuşuna bas.$"

Roulette_Text_ItsAHit::
	.string "Sayı!$"

Roulette_Text_Jackpot::
	.string "Bingo!$"

Roulette_Text_NothingDoing::
	.string "Hiçbir şey çıkmadı!$"

Roulette_Text_YouveWonXCoins::
	.string "{STR_VAR_1} JETON kazandın!$"

Roulette_Text_NoCoinsLeft::
	.string "JETON kalmadı…$"

Roulette_Text_KeepPlaying::
	.string "Devam mı?$"

Roulette_Text_BoardWillBeCleared::
	.string "RULET tablosu silinecek.$"

@ Unused
Roulette_Text_YouDontHaveACoinCase::
	.string "You don't have a COIN CASE.$"

Roulette_Text_CoinCaseIsFull::
	.string "Your COIN CASE is full!\n"
	.string "Coins can be exchanged for prizes.$"
