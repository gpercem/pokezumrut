ShoalCave_LowTideIceRoom_MapScripts::
	.byte 0

ShoalCave_Text_AuroraTicket:
	.string "Bu bir gemi bileti.\pBırakılalı uzun zaman olmuş gibi\nduruyor.$"

ShoalCave_OutsideEast_EventScript_ItemAuroraTicket::
	finditem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	msgbox ShoalCave_Text_AuroraTicket, MSGBOX_DEFAULT
	closemessage
	end
