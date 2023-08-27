Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
	.string "Şuradaki RUSTURF TÜNELİ…\pİlk başta, en yeni makinelerle kayayı\ndelen büyük bir çalışma ekibimiz vardı.\lAncak, durmak zorunda kaldık.\pBölgedeki vahşi POKéMON üzerinde\nolumsuz bir etkimiz olduğu ortaya\lçıktı.\pYani, burada hiçbir şey yapmadan\nbeklemekten başka bir şey\lyapamıyoruz.$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
	.string "Yalnız başına VERDANTURF'a giden yolu\nkazmaya çalışan bir adam var.\lKendisi çaresiz durumda.\pMakine kullanmadan azar azar kazarsa\nPOKéMON'u rahatsız etmeyeceğini ve\ldoğal çevreye zarar vermekten\lkaçınacağını söylüyor.\pAcaba başarabildi mi?$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
	.string "Bu TÜNELİ kullanmadan VERDANTURF'a\nulaşmak için, denizi geçerek DEWFORD'a\lgitmen, SLATEPORT'a yelken açman\lve ardından MAUVILLE'den geçmen\lgerekir.$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
	.string "Bunu duydun mu?\nVERDANTURF'a giden TÜNEL açılmış!\pBir şeyi ne kadar istersen\ngerçekleşme olasılığı o kadar artar.$"


