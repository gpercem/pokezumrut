SeafloorCavern_Room3_MapScripts::
	.byte 0

SeafloorCavern_Room3_EventScript_Shelly::
	trainerbattle_single TRAINER_SHELLY_SEAFLOOR_CAVERN, SeafloorCavern_Room3_Text_ShellyIntro, SeafloorCavern_Room3_Text_ShellyDefeat
	msgbox SeafloorCavern_Room3_Text_ShellyPostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_5, SeafloorCavern_Room3_Text_Grunt5Intro, SeafloorCavern_Room3_Text_Grunt5Defeat
	msgbox SeafloorCavern_Room3_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room3_Text_ShellyIntro:
	.string "Ahahahaha!\pDenizaltı olmadan buraya gelmeyi nasıl\nbaşardın? Ne etkileyici bir çocuk!\pAma…\nBuraya burnunu sokmana izin veremem.\pVe, HAVA ENSTİTÜSÜ'nde olanların\nintikamını almak istiyorum…\pSana biraz acı tattıracağım!\nKendini hazırla!$"

SeafloorCavern_Room3_Text_ShellyDefeat:
	.string "Ahahahaha!\pEyvah!$"

SeafloorCavern_Room3_Text_ShellyPostBattle:
	.string "Ahahahaha!\nÇok güçlüsün.\pBir AQUA TAKIMI üyesi olmaman büyük\nhayal kırıklığı.\pPatronumuzun bizden biri olarak vaat\nettiği muhteşem dünyanın tadını\lçıkarabilirdin…$"

SeafloorCavern_Room3_Text_Grunt5Intro:
	.string "Hayalimizin gerçek olması için\nPOKéMON'unun gücüne ihtiyacımız var.\pAma senin gibi işgüzarlar POKéMON'un\ngücünü böyle bir yerde bile bizimle\luğraşmak için kullanıyor!\pHayat istediğimiz gibi işlemiyor!$"

SeafloorCavern_Room3_Text_Grunt5Defeat:
	.string "Haa!$"

SeafloorCavern_Room3_Text_Grunt5PostBattle:
	.string "Biliyorsun, liderimizin güdülerini\nsorgulamaya cesaret edemeyiz.\pAma sen, patronumuza karşı\ngeliyorsun.\pBelki de… Sen…$"


