VerdanturfTown_FriendshipRatersHouse_MapScripts::
	.byte 0

VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater::
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case FRIENDSHIP_NONE, VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou
	case FRIENDSHIP_1_TO_49, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary
	case FRIENDSHIP_50_TO_99, VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou
	case FRIENDSHIP_100_TO_149, VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou
	case FRIENDSHIP_150_TO_199, VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot
	case FRIENDSHIP_200_TO_254, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy
	case FRIENDSHIP_MAX, VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou::
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou:
	.string "POKéMON'una bir bakayım. Seni ne\nkadar sevdiğine bakacağım.\pHım. POKéMON'un…$"

VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou:
	.string "Seni çok seviyor. Daha çok sevmesi\nmümkün olmayacak kadar hem de.\pOnu görünce ben bile mutlu\noluyorum.$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy:
	.string "Çok mutlu görünüyor.\nBelli ki seni çok seviyor.$"

VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot:
	.string "Seni seviyor. Biraz daha ilgi\nistiyor gibi görünüyor.$"

VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou:
	.string "Sana alışıyor.\nSana inanıyor gibi görünüyor.$"

VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou:
	.string "Henüz sana alışmamış.\pSeni ne seviyor ne de senden\nnefret ediyor.$"

VerdanturfTown_FriendshipRatersHouse_Text_VeryWary:
	.string "Çok temkinli.\nGözlerinde bir hırçınlık var.\lSenden hiç hoşlanmıyor.$"

VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou:
	.string "Bunu söylemek benim için biraz zor…\pPOKéMON'un senden nefret ediyor.\nBu seni rahatsız etmiyor mu?$"

VerdanturfTown_FriendshipRatersHouse_Text_Pikachu:
	.string "Pika pika!$"


