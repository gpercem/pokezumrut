AlteringCave_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AlteringCave_OnTransition
	.byte 0

AlteringCave_OnTransition:
	setflag FLAG_LANDMARK_ALTERING_CAVE
	end

AlteringCave_Event_ItemEonTicket::
	finditem ITEM_EON_TICKET
	setflag FLAG_ENABLE_SHIP_SOUTHERN_ISLAND
	msgbox AlteringCave_Text_ItemEonTicket, MSGBOX_DEFAULT
	closemessage
	end

	
AlteringCave_Text_ItemEonTicket:
	.string "Bu bir gemi bileti.\pBırakılalı uzun zaman olmuş gibi\nduruyor.$"
