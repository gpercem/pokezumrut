#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "data.h"
#include "event_data.h"
#include "frontier_util.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "link.h"
#include "menu.h"
#include "palette.h"
#include "recorded_battle.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "trainer_hill.h"
#include "window.h"
#include "constants/battle_dome.h"
#include "constants/battle_string_ids.h"
#include "constants/frontier_util.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/trainer_hill.h"
#include "constants/weather.h"

struct BattleWindowText
{
    u8 fillValue;
    u8 fontId;
    u8 x;
    u8 y;
    u8 letterSpacing;
    u8 lineSpacing;
    u8 speed;
    u8 fgColor;
    u8 bgColor;
    u8 shadowColor;
};

static void ChooseMoveUsedParticle(u8 *textPtr);
static void ChooseTypeOfMoveUsedString(u8 *dst);
static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst);

static EWRAM_DATA u8 sBattlerAbilities[MAX_BATTLERS_COUNT] = {0};
EWRAM_DATA struct BattleMsgData *gBattleMsgDataPtr = NULL;

// todo: make some of those names less vague: attacker/target vs pkmn, etc.

static const u8 sText_Trainer1LoseText[] = _("{B_TRAINER1_LOSE_TEXT}");
static const u8 sText_PkmnGainedEXP[] = _("{B_BUFF1}, {B_BUFF2}\n{B_BUFF3} EXP. aldı!\p");
static const u8 sText_EmptyString4[] = _("");
static const u8 sText_ABoosted[] = _(" ekstra");
static const u8 sText_PkmnGrewToLv[] = _("{B_BUFF1}, \nSV. {B_BUFF2} oldu!{WAIT_SE}\p");
static const u8 sText_PkmnLearnedMove[] = _("{B_BUFF1},\n{B_BUFF2} öğrendi!{WAIT_SE}\p");
static const u8 sText_TryToLearnMove1[] = _("{B_BUFF1}, {B_BUFF2}\nöğrenmeye çalışıyor.\p");
static const u8 sText_TryToLearnMove2[] = _("Ama {B_BUFF1} dört\nsaldırıdan fazla öğrenemiyor.\p");
static const u8 sText_TryToLearnMove3[] = _("Bir saldırı silinip\n{B_BUFF2} için yer açılsın mı?");
static const u8 sText_PkmnForgotMove[] = _("{B_BUFF1},\n{B_BUFF2} unuttu.\p");
static const u8 sText_StopLearningMove[] = _("{PAUSE 32}{B_BUFF2}\nöğrenilmesin mi?");
static const u8 sText_DidNotLearnMove[] = _("{B_BUFF1}, {B_BUFF2}\nöğrenemedi.\p");
static const u8 sText_UseNextPkmn[] = _("Sonraki POKéMON'u kullanacak\nmısın?");
static const u8 sText_AttackMissed[] = _("{B_ATK_NAME_WITH_PREFIX},\nsaldırısını ıskaladı!");
static const u8 sText_PkmnProtectedItself[] = _("{B_DEF_NAME_WITH_PREFIX}\nkendini korudu!");
static const u8 sText_AvoidedDamage[] = _("{B_DEF_NAME_WITH_PREFIX} {B_DEF_ABILITY}\nsayesinde korundu!");
static const u8 sText_PkmnMakesGroundMiss[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_DEF_ABILITY}\nile YER saldırısından korundu!");
static const u8 sText_PkmnAvoidedAttack[] = _("{B_DEF_NAME_WITH_PREFIX}, saldırıdan\nkaçınabildi!");
static const u8 sText_ItDoesntAffect[] = _("Bu, {B_DEF_NAME_WITH_PREFIX}'ı\netkilemedi…");
static const u8 sText_AttackerFainted[] = _("{B_ATK_NAME_WITH_PREFIX}\nbayıldı!\p");
static const u8 sText_TargetFainted[] = _("{B_DEF_NAME_WITH_PREFIX}\nbayıldı!\p");
static const u8 sText_PlayerGotMoney[] = _("{B_PLAYER_NAME}, kazandığı\niçin ¥{B_BUFF1} aldı!\p");
static const u8 sText_PlayerWhiteout[] = _("{B_PLAYER_NAME}'ın kullanılabilir\nPOKéMON'u kalmadı!\p");
static const u8 sText_PlayerWhiteout2[] = _("{B_PLAYER_NAME} kaçtı!{PAUSE_UNTIL_PRESS}");
static const u8 sText_PreventsEscape[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}, {B_SCR_ACTIVE_ABILITY} ile\nkaçmayı engelliyor!\p");
static const u8 sText_CantEscape2[] = _("Kaçamazsın!\p");
static const u8 sText_AttackerCantEscape[] = _("{B_ATK_NAME_WITH_PREFIX} kaçamıyor!");
static const u8 sText_HitXTimes[] = _("{B_BUFF1} kez vurdu!");
static const u8 sText_PkmnFellAsleep[] = _("{B_EFF_NAME_WITH_PREFIX}\nuykuya daldı!");
static const u8 sText_PkmnMadeSleep[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\n{B_EFF_NAME_WITH_PREFIX}'ı uyuttu!");
static const u8 sText_PkmnAlreadyAsleep[] = _("{B_DEF_NAME_WITH_PREFIX} zaten\nuyuyor!");
static const u8 sText_PkmnAlreadyAsleep2[] = _("{B_ATK_NAME_WITH_PREFIX}\nzaten uyuyor!");
static const u8 sText_PkmnWasntAffected[] = _("{B_DEF_NAME_WITH_PREFIX}\netkilenmedi!");
static const u8 sText_PkmnWasPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX}\nzehirlendi!");
static const u8 sText_PkmnPoisonedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\n{B_EFF_NAME_WITH_PREFIX}'ı zehirledi!");
static const u8 sText_PkmnHurtByPoison[] = _("{B_ATK_NAME_WITH_PREFIX} zehirden\netkilendi!");
static const u8 sText_PkmnAlreadyPoisoned[] = _("{B_DEF_NAME_WITH_PREFIX} zaten\nzehirlenmişti.");
static const u8 sText_PkmnBadlyPoisoned[] = _("{B_EFF_NAME_WITH_PREFIX} ağır bir\nşekilde zehirlendi!");
static const u8 sText_PkmnEnergyDrained[] = _("{B_DEF_NAME_WITH_PREFIX}'ın enerjisi\nemildi!");
static const u8 sText_PkmnWasBurned[] = _("{B_EFF_NAME_WITH_PREFIX} yandı!");
static const u8 sText_PkmnBurnedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı,\n{B_EFF_NAME_WITH_PREFIX}'ı yaktı!");
static const u8 sText_PkmnHurtByBurn[] = _("{B_ATK_NAME_WITH_PREFIX} yanığı\nyüzünden hasar gördü!");
static const u8 sText_PkmnAlreadyHasBurn[] = _("{B_DEF_NAME_WITH_PREFIX}'ın zaten\nyanığı var.");
static const u8 sText_PkmnWasFrozen[] = _("{B_EFF_NAME_WITH_PREFIX},\nkaskatı kesildi!");
static const u8 sText_PkmnFrozenBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\n{B_EFF_NAME_WITH_PREFIX}'ı dondurdu!");
static const u8 sText_PkmnIsFrozen[] = _("{B_ATK_NAME_WITH_PREFIX}\ndonuk!");
static const u8 sText_PkmnWasDefrosted[] = _("{B_DEF_NAME_WITH_PREFIX}'ın\nbuzu çözüldü!");
static const u8 sText_PkmnWasDefrosted2[] = _("{B_ATK_NAME_WITH_PREFIX}'ın\nbuzu çözüldü!");
static const u8 sText_PkmnWasDefrostedBy[] = _("{B_ATK_NAME_WITH_PREFIX}'ın buzu\n{B_CURRENT_MOVE} ile çözüldü!");
static const u8 sText_PkmnWasParalyzed[] = _("{B_EFF_NAME_WITH_PREFIX} felç kaldı!\nSaldırısı başarılı olmayabilir!");
static const u8 sText_PkmnWasParalyzedBy[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı,\n{B_EFF_NAME_WITH_PREFIX}'ı felç bıraktı!\lSaldırısı başarılı olmayabilir!");
static const u8 sText_PkmnIsParalyzed[] = _("{B_ATK_NAME_WITH_PREFIX} felçli!\nSaldıramıyor!");
static const u8 sText_PkmnIsAlreadyParalyzed[] = _("{B_DEF_NAME_WITH_PREFIX} zaten\nfelçli!");
static const u8 sText_PkmnHealedParalysis[] = _("{B_DEF_NAME_WITH_PREFIX}'ın\nfelci geçti!");
static const u8 sText_PkmnDreamEaten[] = _("{B_DEF_NAME_WITH_PREFIX}'ın\nrüyası yenildi!");
static const u8 sText_StatsWontIncrease[] = _("{B_ATK_NAME_WITH_PREFIX}'ın {B_BUFF1}'ı\ndaha yükselemiyor!");
static const u8 sText_StatsWontDecrease[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_BUFF1}'ı\ndaha düşemiyor!");
static const u8 sText_TeamStoppedWorking[] = _("Takımının {B_BUFF1}'ı\nartık çalışmıyor!");
static const u8 sText_FoeStoppedWorking[] = _("Düşmanın {B_BUFF1}'ı\nartık çalışmıyor!");
static const u8 sText_PkmnIsConfused[] = _("{B_ATK_NAME_WITH_PREFIX}'ın kafası\nkarışık!");
static const u8 sText_PkmnHealedConfusion[] = _("{B_ATK_NAME_WITH_PREFIX}'ın kafa karışıklığı\ngeçti!");
static const u8 sText_PkmnWasConfused[] = _("{B_EFF_NAME_WITH_PREFIX}'ın kafası karıştı!");
static const u8 sText_PkmnAlreadyConfused[] = _("{B_DEF_NAME_WITH_PREFIX}'ın kafası\nzaten karışık!");
static const u8 sText_PkmnFellInLove[] = _("{B_DEF_NAME_WITH_PREFIX}\naşık oldu!");
static const u8 sText_PkmnInLove[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_SCR_ACTIVE_NAME_WITH_PREFIX}'a\naşık!");
static const u8 sText_PkmnImmobilizedByLove[] = _("{B_ATK_NAME_WITH_PREFIX}, sevdası\nyüzünden saldıramadı!");
static const u8 sText_PkmnBlownAway[] = _("{B_DEF_NAME_WITH_PREFIX},\nuçuruldu!");
static const u8 sText_PkmnChangedType[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_BUFF1} türüne\ndönüştü!");
static const u8 sText_PkmnFlinched[] = _("{B_ATK_NAME_WITH_PREFIX} ürktü!");
static const u8 sText_PkmnRegainedHealth[] = _("{B_DEF_NAME_WITH_PREFIX} can\nkazandı!");
static const u8 sText_PkmnHPFull[] = _("{B_DEF_NAME_WITH_PREFIX}'ın\nCAN'ı tam!");
static const u8 sText_PkmnRaisedSpDef[] = _("{B_ATK_PREFIX2}'ın {B_CURRENT_MOVE}'ı\nÖZ. SVN arttırdı!");
static const u8 sText_PkmnRaisedSpDefALittle[] = _("{B_ATK_PREFIX2}'ın {B_CURRENT_MOVE}'ı\nÖZ. SVN'yı biraz arttırdı!");
static const u8 sText_PkmnRaisedDef[] = _("{B_ATK_PREFIX2}'ın {B_CURRENT_MOVE}'ı\nSAVUNMA'yı arttırdı!");
static const u8 sText_PkmnRaisedDefALittle[] = _("{B_ATK_PREFIX2}'ın {B_CURRENT_MOVE}'ı\nSAVUNMA'yı biraz arttırdı!");
static const u8 sText_PkmnCoveredByVeil[] = _("{B_ATK_PREFIX2}'ın takımı bir\nörtü ile kaplandı!");
static const u8 sText_PkmnUsedSafeguard[] = _("{B_DEF_NAME_WITH_PREFIX}'ın takımı\nSAFEGUARD ile korundu!");
static const u8 sText_PkmnSafeguardExpired[] = _("{B_ATK_PREFIX3}'ın takımı artık\nSAFEGUARD ile korunmuyor!");
static const u8 sText_PkmnWentToSleep[] = _("{B_ATK_NAME_WITH_PREFIX}, uykuya\ndaldı!");
static const u8 sText_PkmnSleptHealthy[] = _("{B_ATK_NAME_WITH_PREFIX} uyudu ve\nsağlığına kavuştu!");
static const u8 sText_PkmnWhippedWhirlwind[] = _("{B_ATK_NAME_WITH_PREFIX} bir\nkasırga çıkardı!");
static const u8 sText_PkmnTookSunlight[] = _("{B_ATK_NAME_WITH_PREFIX}, güneş\nışığını çekti!");
static const u8 sText_PkmnLoweredHead[] = _("{B_ATK_NAME_WITH_PREFIX} başını eğdi!");
static const u8 sText_PkmnIsGlowing[] = _("{B_ATK_NAME_WITH_PREFIX} parlıyor!");
static const u8 sText_PkmnFlewHigh[] = _("{B_ATK_NAME_WITH_PREFIX} yükseğe uçtu!");
static const u8 sText_PkmnDugHole[] = _("{B_ATK_NAME_WITH_PREFIX} delik kazdı!");
static const u8 sText_PkmnHidUnderwater[] = _("{B_ATK_NAME_WITH_PREFIX} su altına\nsaklandı!");
static const u8 sText_PkmnSprangUp[] = _("{B_ATK_NAME_WITH_PREFIX} zıpladı!");
static const u8 sText_PkmnSqueezedByBind[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_ATK_NAME_WITH_PREFIX}'ın\nBIND'ı ile sarıldı!");
static const u8 sText_PkmnTrappedInVortex[] = _("{B_DEF_NAME_WITH_PREFIX} girdaba\nhapsoldu!");
static const u8 sText_PkmnTrappedBySandTomb[] = _("{B_DEF_NAME_WITH_PREFIX}, SAND TOMB\nile hapsoldu!");
static const u8 sText_PkmnWrappedBy[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_ATK_NAME_WITH_PREFIX}\ntarafından sarıldı!");
static const u8 sText_PkmnClamped[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'ı\nsıkıştırdı!");
static const u8 sText_PkmnHurtBy[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_BUFF1}\ntarafından hasar gördü!");
static const u8 sText_PkmnFreedFrom[] = _("{B_ATK_NAME_WITH_PREFIX} {B_BUFF1}'dan\nkurtuldu!");
static const u8 sText_PkmnCrashed[] = _("{B_ATK_NAME_WITH_PREFIX} devam etti\nve çarptı!");
const u8 gText_PkmnShroudedInMist[] = _("{B_ATK_PREFIX2}, SİS\nile kaplandı!");
static const u8 sText_PkmnProtectedByMist[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} SİS tarafından\nkorundu!");
const u8 gText_PkmnGettingPumped[] = _("{B_ATK_NAME_WITH_PREFIX} odaklanıyor!");
static const u8 sText_PkmnHitWithRecoil[] = _("{B_ATK_NAME_WITH_PREFIX} geri tepme\nile vurdu!");
static const u8 sText_PkmnProtectedItself2[] = _("{B_ATK_NAME_WITH_PREFIX} kendini\nkorudu!");
static const u8 sText_PkmnBuffetedBySandstorm[] = _("{B_ATK_NAME_WITH_PREFIX}, kum fırtınasından\netkilendi!");
static const u8 sText_PkmnPeltedByHail[] = _("{B_ATK_NAME_WITH_PREFIX} DOLU'dan\netkilendi!");
static const u8 sText_PkmnsXWoreOff[] = _("{B_ATK_PREFIX1}'ın {B_BUFF1}'ı\nsona erdi!");
static const u8 sText_PkmnSeeded[] = _("{B_DEF_NAME_WITH_PREFIX} tohumlandı!");
static const u8 sText_PkmnEvadedAttack[] = _("{B_DEF_NAME_WITH_PREFIX}, saldırıdan\nkaçındı!");
static const u8 sText_PkmnSappedByLeechSeed[] = _("{B_ATK_NAME_WITH_PREFIX}'ın canı\nLEECH SEED ile çekildi!");
static const u8 sText_PkmnFastAsleep[] = _("{B_ATK_NAME_WITH_PREFIX} uyuyor.");
static const u8 sText_PkmnWokeUp[] = _("{B_ATK_NAME_WITH_PREFIX} uyandı!");
static const u8 sText_PkmnUproarKeptAwake[] = _("Ama {B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın UPROAR'ı\nonu uyutmuyor!");
static const u8 sText_PkmnWokeUpInUproar[] = _("{B_ATK_NAME_WITH_PREFIX} UPROAR ile\nuyandı!");
static const u8 sText_PkmnCausedUproar[] = _("{B_ATK_NAME_WITH_PREFIX} bir\ngürültü başlattı!");
static const u8 sText_PkmnMakingUproar[] = _("{B_ATK_NAME_WITH_PREFIX} gürültü yapıyor!");
static const u8 sText_PkmnCalmedDown[] = _("{B_ATK_NAME_WITH_PREFIX} sakinleşti.");
static const u8 sText_PkmnCantSleepInUproar[] = _("Ama {B_DEF_NAME_WITH_PREFIX} UPROAR\nvarken uyuyamıyor!");
static const u8 sText_PkmnStockpiled[] = _("{B_ATK_NAME_WITH_PREFIX}\n{B_BUFF1} kez DEPOLADI!");
static const u8 sText_PkmnCantStockpile[] = _("{B_ATK_NAME_WITH_PREFIX} daha fazla\nSTOCKPILE kullanamıyor!");
static const u8 sText_PkmnCantSleepInUproar2[] = _("Ama {B_DEF_NAME_WITH_PREFIX}, UPROAR\nvarken uyuyamıyor!");
static const u8 sText_UproarKeptPkmnAwake[] = _("Ama UPROAR, {B_DEF_NAME_WITH_PREFIX}'ı\nuyanık tutuyor!");
static const u8 sText_PkmnStayedAwakeUsing[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_DEF_ABILITY}\nile uyanık kaldı!");
static const u8 sText_PkmnStoringEnergy[] = _("{B_ATK_NAME_WITH_PREFIX} enerjisini\ndepoluyor!");
static const u8 sText_PkmnUnleashedEnergy[] = _("{B_ATK_NAME_WITH_PREFIX} enerjisini\nsaldı!");
static const u8 sText_PkmnFatigueConfusion[] = _("{B_ATK_NAME_WITH_PREFIX} yorulduğu için\nkafası karıştı!");
static const u8 sText_PlayerPickedUpMoney[] = _("{B_PLAYER_NAME}, ¥{B_BUFF1}\nçaldı!\p");
static const u8 sText_PkmnUnaffected[] = _("{B_DEF_NAME_WITH_PREFIX},\netkilenmedi!");
static const u8 sText_PkmnTransformedInto[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_BUFF1}'a\ndönüştü!");
static const u8 sText_PkmnMadeSubstitute[] = _("{B_ATK_NAME_WITH_PREFIX} bir\nKOPYA oluşturdu!");
static const u8 sText_PkmnHasSubstitute[] = _("{B_ATK_NAME_WITH_PREFIX}'ın zaten\nKOPYA'sı var!");
static const u8 sText_SubstituteDamaged[] = _("KOPYA, {B_DEF_NAME_WITH_PREFIX}\niçin saldırıyı üstüne aldı!\p");
static const u8 sText_PkmnSubstituteFaded[] = _("{B_DEF_NAME_WITH_PREFIX}'ın\nKOPYA'sı söndü!\p");
static const u8 sText_PkmnMustRecharge[] = _("{B_ATK_NAME_WITH_PREFIX} tekrar\nşarj olmalı!");
static const u8 sText_PkmnRageBuilding[] = _("{B_DEF_NAME_WITH_PREFIX}'ın ÖFKE'si\nbüyüyor!");
static const u8 sText_PkmnMoveWasDisabled[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_BUFF1}'ı\nengellendi!");
static const u8 sText_PkmnMoveDisabledNoMore[] = _("{B_ATK_NAME_WITH_PREFIX}'ın engeli\nkalktı!");
static const u8 sText_PkmnGotEncore[] = _("{B_DEF_NAME_WITH_PREFIX}, TEZAHÜRAT\naldı!");
static const u8 sText_PkmnEncoreEnded[] = _("{B_ATK_NAME_WITH_PREFIX}'ın TEZAHÜRAT'ı\nsona erdi!");
static const u8 sText_PkmnTookAim[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'ı\nhedef aldı!");
static const u8 sText_PkmnSketchedMove[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_BUFF1}'ı\nÇİZDİ!");
static const u8 sText_PkmnTryingToTakeFoe[] = _("{B_ATK_NAME_WITH_PREFIX}, kendisiyle\ndüşmanını da götürmek istiyor!");
static const u8 sText_PkmnTookFoe[] = _("{B_DEF_NAME_WITH_PREFIX}, kendisiyle\n{B_ATK_NAME_WITH_PREFIX}'ı da götürdü!");
static const u8 sText_PkmnReducedPP[] = _("{B_DEF_NAME_WITH_PREFIX}'ın\n{B_BUFF1}'si, {B_BUFF2} azaldı!");
static const u8 sText_PkmnStoleItem[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'ın\n{B_LAST_ITEM} eşyasını çaldı!");
static const u8 sText_TargetCantEscapeNow[] = _("{B_DEF_NAME_WITH_PREFIX} artık\nkaçamayacak!");
static const u8 sText_PkmnFellIntoNightmare[] = _("{B_DEF_NAME_WITH_PREFIX} bir\nKABUS'a yakalandı!");
static const u8 sText_PkmnLockedInNightmare[] = _("{B_ATK_NAME_WITH_PREFIX} bir KABUS\ngörüyor!");
static const u8 sText_PkmnLaidCurse[] = _("{B_ATK_NAME_WITH_PREFIX} CAN'ından verdi\nve {B_DEF_NAME_WITH_PREFIX}'ı lanetledi!");
static const u8 sText_PkmnAfflictedByCurse[] = _("{B_ATK_NAME_WITH_PREFIX} LANET'ten\netkilendi!");
static const u8 sText_SpikesScattered[] = _("DİKENLER düşmanının tarafına\nsaçıldı!");
static const u8 sText_PkmnHurtBySpikes[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}, DİKEN\nyüzünden hasar gördü!");
static const u8 sText_PkmnIdentified[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'ı\ntanımladı!");
static const u8 sText_PkmnPerishCountFell[] = _("{B_ATK_NAME_WITH_PREFIX}'ın ÖLÜM sayacı\n{B_BUFF1} oldu!");
static const u8 sText_PkmnBracedItself[] = _("{B_ATK_NAME_WITH_PREFIX} kendini\nbağladı!");
static const u8 sText_PkmnEnduredHit[] = _("{B_DEF_NAME_WITH_PREFIX} vuruştan\nkaçındı!");
static const u8 sText_MagnitudeStrength[] = _("{B_BUFF1} ŞİDDETİNDE DEPREM!");
static const u8 sText_PkmnCutHPMaxedAttack[] = _("{B_ATK_NAME_WITH_PREFIX} CAN'ından verdi\nve SALDIRI'sını maksimum yaptı!");
static const u8 sText_PkmnCopiedStatChanges[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'ın\ndurumlarını kopyaladı!");
static const u8 sText_PkmnGotFree[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'ın\n{B_BUFF1}'dan kurtuldu!");
static const u8 sText_PkmnShedLeechSeed[] = _("{B_ATK_NAME_WITH_PREFIX},\nLEECH SEED'den kurtuldu!");
static const u8 sText_PkmnBlewAwaySpikes[] = _("{B_ATK_NAME_WITH_PREFIX} DİKEN'lerden\nkurtuldu!");
static const u8 sText_PkmnFledFromBattle[] = _("{B_ATK_NAME_WITH_PREFIX} savaştan kaçtı!");
static const u8 sText_PkmnForesawAttack[] = _("{B_ATK_NAME_WITH_PREFIX} bir\nsaldırıyı önceden gördü!");
static const u8 sText_PkmnTookAttack[] = _("{B_DEF_NAME_WITH_PREFIX},\n{B_BUFF1} saldırısını yedi!");
static const u8 sText_PkmnChoseXAsDestiny[] = _("{B_ATK_NAME_WITH_PREFIX}, kaderini\n{B_CURRENT_MOVE} seçti!");
static const u8 sText_PkmnAttack[] = _("{B_BUFF1}'ın saldırısı!");
static const u8 sText_PkmnCenterAttention[] = _("{B_ATK_NAME_WITH_PREFIX} ilginin\nmerkezi oldu!");
static const u8 sText_PkmnChargingPower[] = _("{B_ATK_NAME_WITH_PREFIX} güç\ndepolamaya başladı!");
static const u8 sText_NaturePowerTurnedInto[] = _("NATURE POWER,\n{B_CURRENT_MOVE} oldu!");
static const u8 sText_PkmnStatusNormal[] = _("{B_ATK_NAME_WITH_PREFIX}'ın durumu\nnormale döndü!");
static const u8 sText_PkmnSubjectedToTorment[] = _("{B_DEF_NAME_WITH_PREFIX}, TORMENT'e\nmaruz kaldı!");
static const u8 sText_PkmnTighteningFocus[] = _("{B_ATK_NAME_WITH_PREFIX} odağını\ngüçlendiriyor!");
static const u8 sText_PkmnFellForTaunt[] = _("{B_DEF_NAME_WITH_PREFIX} TAUNT'a\ndüştü!");
static const u8 sText_PkmnReadyToHelp[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'a\nyardıma hazır!");
static const u8 sText_PkmnSwitchedItems[] = _("{B_ATK_NAME_WITH_PREFIX}, düşmanla\neşyaları değiştirdi!");
static const u8 sText_PkmnObtainedX[] = _("{B_ATK_NAME_WITH_PREFIX},\n{B_BUFF1} aldı.");
static const u8 sText_PkmnObtainedX2[] = _("{B_DEF_NAME_WITH_PREFIX},\n{B_BUFF2} aldı.");
static const u8 sText_PkmnObtainedXYObtainedZ[] = _("{B_ATK_NAME_WITH_PREFIX}\n{B_BUFF1} aldı.\p{B_DEF_NAME_WITH_PREFIX}\n{B_BUFF2} aldı.");
static const u8 sText_PkmnCopiedFoe[] = _("{B_ATK_NAME_WITH_PREFIX} copied\n{B_DEF_NAME_WITH_PREFIX}'s {B_DEF_ABILITY}!");
static const u8 sText_PkmnMadeWish[] = _("{B_ATK_NAME_WITH_PREFIX} bir DİLEK\ndiledi!");
static const u8 sText_PkmnWishCameTrue[] = _("{B_BUFF1}'ın dileği\ngerçek oldu!");
static const u8 sText_PkmnPlantedRoots[] = _("{B_ATK_NAME_WITH_PREFIX} köklerini\nsaldı!");
static const u8 sText_PkmnAbsorbedNutrients[] = _("{B_ATK_NAME_WITH_PREFIX}, kökleriyle\nbesinleri çekti!");
static const u8 sText_PkmnAnchoredItself[] = _("{B_DEF_NAME_WITH_PREFIX}, kökleriyle\nkendini sabitledi!");
static const u8 sText_PkmnWasMadeDrowsy[] = _("{B_ATK_NAME_WITH_PREFIX},\n{B_DEF_NAME_WITH_PREFIX}'ı uyuşturdu!");
static const u8 sText_PkmnKnockedOff[] = _("{B_ATK_NAME_WITH_PREFIX}, {B_DEF_NAME_WITH_PREFIX}'ın\n{B_LAST_ITEM} eşyasını attı!");
static const u8 sText_PkmnSwappedAbilities[] = _("{B_ATK_NAME_WITH_PREFIX} yeteneğini\ndüşmanıyla değiştirdi!");
static const u8 sText_PkmnSealedOpponentMove[] = _("{B_ATK_NAME_WITH_PREFIX}, düşmanın\nsaldırısını mühürledi!");
static const u8 sText_PkmnWantsGrudge[] = _("{B_ATK_NAME_WITH_PREFIX}, düşmanının\nKİN beslemesini istiyor!");
static const u8 sText_PkmnLostPPGrudge[] = _("{B_ATK_NAME_WITH_PREFIX}'ın {B_BUFF1}'ı, KİN\nyüzünden tüm PP'sini kaybetti!");
static const u8 sText_PkmnShroudedItself[] = _("{B_ATK_NAME_WITH_PREFIX}, kendini\n{B_CURRENT_MOVE} ile örttü!");
static const u8 sText_PkmnMoveBounced[] = _("{B_ATK_NAME_WITH_PREFIX}'ın {B_CURRENT_MOVE}'ı\nMAGIC COAT ile geri gönderildi!");
static const u8 sText_PkmnWaitsForTarget[] = _("{B_ATK_NAME_WITH_PREFIX} hedefin saldırı\nyapmasını bekliyor!");
static const u8 sText_PkmnSnatchedMove[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın\nsaldırısını çaldı!");
static const u8 sText_ElectricityWeakened[] = _("Elektrik gücü düştü!");
static const u8 sText_FireWeakened[] = _("Ateş gücü düştü!");
static const u8 sText_XFoundOneY[] = _("{B_ATK_NAME_WITH_PREFIX} bir\n{B_LAST_ITEM} buldu!");
static const u8 sText_SoothingAroma[] = _("Rahatlatıcı bir koku\netrafı kapladı!");
static const u8 sText_ItemsCantBeUsedNow[] = _("Eşya şu anda kullanılamıyor.{PAUSE 64}");
static const u8 sText_ForXCommaYZ[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} için,\n{B_LAST_ITEM} {B_BUFF1}");
static const u8 sText_PkmnUsedXToGetPumped[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}, odaklanmak\niçin {B_LAST_ITEM} kullandı!");
static const u8 sText_PkmnLostFocus[] = _("{B_ATK_NAME_WITH_PREFIX} odağını\nkaybetti ve saldıramadı!");
static const u8 sText_PkmnWasDraggedOut[] = _("{B_DEF_NAME_WITH_PREFIX}\ngeri çekildi!\p");
static const u8 sText_TheWallShattered[] = _("Duvar yıkıldı!");
static const u8 sText_ButNoEffect[] = _("Ama bir etkisi olmadı!");
static const u8 sText_PkmnHasNoMovesLeft[] = _("{B_ACTIVE_NAME_WITH_PREFIX}'ın saldırısı\nkalmadı!\p");
static const u8 sText_PkmnMoveIsDisabled[] = _("{B_ACTIVE_NAME_WITH_PREFIX}'ın {B_CURRENT_MOVE}'ı\nengellendi!\p");
static const u8 sText_PkmnCantUseMoveTorment[] = _("{B_ACTIVE_NAME_WITH_PREFIX}, TORMENT yüzünden\naynı saldırıyı üst üste kullanamaz!\p");
static const u8 sText_PkmnCantUseMoveTaunt[] = _("{B_ACTIVE_NAME_WITH_PREFIX}, TAUNT'tan\nsonra {B_CURRENT_MOVE} kullanamıyor!\p");
static const u8 sText_PkmnCantUseMoveSealed[] = _("{B_ACTIVE_NAME_WITH_PREFIX} mühürlü\n{B_CURRENT_MOVE} saldırısını kullanamıyor!\p");
static const u8 sText_PkmnMadeItRain[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\nyağmur yağdırdı!");
static const u8 sText_PkmnRaisedSpeed[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\nHIZ'ını artırdı!");
static const u8 sText_PkmnProtectedBy[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_DEF_ABILITY}\ntarafından korundu!");
static const u8 sText_PkmnPreventsUsage[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı,\n{B_ATK_NAME_WITH_PREFIX}'ın {B_CURRENT_MOVE}\lkullanmasını engelliyor!");
static const u8 sText_PkmnRestoredHPUsing[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_DEF_ABILITY}\nkullanarak canını yeniledi!");
static const u8 sText_PkmnsXMadeYUseless[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\n{B_CURRENT_MOVE}'ı gereksiz kıldı!");
static const u8 sText_PkmnChangedTypeWith[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\nonu {B_BUFF1} türü yaptı!");
static const u8 sText_PkmnPreventsParalysisWith[] = _("{B_EFF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\nfelci önledi!");
static const u8 sText_PkmnPreventsRomanceWith[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\nromantizmi önledi!");
static const u8 sText_PkmnPreventsPoisoningWith[] = _("{B_EFF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\nzehri önledi!");
static const u8 sText_PkmnPreventsConfusionWith[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\nkafa karışıklığını önledi!");
static const u8 sText_PkmnRaisedFirePowerWith[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\nATEŞ gücünü arttırdı!");
static const u8 sText_PkmnAnchorsItselfWith[] = _("{B_DEF_NAME_WITH_PREFIX}, kendini\n{B_DEF_ABILITY} ile sabitledi!");
static const u8 sText_PkmnCutsAttackWith[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\n{B_DEF_NAME_WITH_PREFIX}'ın SALDIRI'sını kesti!");
static const u8 sText_PkmnPreventsStatLossWith[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\ndurum düşmesini engelliyor!");
static const u8 sText_PkmnHurtsWith[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\n{B_ATK_NAME_WITH_PREFIX}'a hasar verdi!");
static const u8 sText_PkmnTraced[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}, {B_BUFF1}'ın\n{B_BUFF2}'ının izini buldu!");
static const u8 sText_PkmnsXPreventsBurns[] = _("{B_EFF_NAME_WITH_PREFIX}'ın {B_EFF_ABILITY}'ı\nyanığı önledi!");
static const u8 sText_PkmnsXBlocksY[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\n{B_CURRENT_MOVE}'ı engelledi!");
static const u8 sText_PkmnsXBlocksY2[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\n{B_CURRENT_MOVE}'ı engelledi!");
static const u8 sText_PkmnsXRestoredHPALittle2[] = _("{B_ATK_NAME_WITH_PREFIX}'ın {B_ATK_ABILITY}'ı\nCAN'ı biraz arttırdı!");
static const u8 sText_PkmnsXWhippedUpSandstorm[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\nkum fırtınası başlattı!");
static const u8 sText_PkmnsXIntensifiedSun[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\nışınları yoğunlaştırdı!");
static const u8 sText_PkmnsXPreventsYLoss[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\n{B_BUFF1} düşüşünü engelliyor!");
static const u8 sText_PkmnsXInfatuatedY[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\n{B_ATK_NAME_WITH_PREFIX}'ı aşık etti!");
static const u8 sText_PkmnsXMadeYIneffective[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı,\n{B_CURRENT_MOVE}'ı etkisiz kıldı!");
static const u8 sText_PkmnsXCuredYProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı,\n{B_BUFF1} sorununu çözdü!");
static const u8 sText_ItSuckedLiquidOoze[] = _("Ama ZEHİRLİ SIVI'sını\nçekti!");
static const u8 sText_PkmnTransformed[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} dönüştü!");
static const u8 sText_PkmnsXTookAttack[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\nsaldırıyı aldı!");
const u8 gText_PkmnsXPreventsSwitching[] = _("{B_BUFF1}'ın {B_LAST_ABILITY}'ı\ndeğişmeyi önlüyor!\p");
static const u8 sText_PreventedFromWorking[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ı\n{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_BUFF1}'ının\lçalışmasını engelledi!");
static const u8 sText_PkmnsXMadeItIneffective[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\nbunu geçersiz kıldı!");
static const u8 sText_PkmnsXPreventsFlinching[] = _("{B_EFF_NAME_WITH_PREFIX}'ın {B_EFF_ABILITY}'ı\nürkmesini engelledi!");
static const u8 sText_PkmnsXPreventsYsZ[] = _("{B_ATK_NAME_WITH_PREFIX}'ın {B_ATK_ABILITY}'ı\n{B_DEF_NAME_WITH_PREFIX}'ın {B_DEF_ABILITY}'ının\lçalışmasını engelliyor!");
static const u8 sText_PkmnsXCuredItsYProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ı\n{B_BUFF1} problemini geçirdi!");
static const u8 sText_PkmnsXHadNoEffectOnY[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_SCR_ACTIVE_ABILITY}'ının\n{B_EFF_NAME_WITH_PREFIX}'a etkisi olmadı!");
static const u8 sText_StatSharply[] = _("oldukça ");
const u8 gText_StatRose[] = _("yükseldi!");
static const u8 sText_StatHarshly[] = _("oldukça ");
static const u8 sText_StatFell[] = _("düştü!");
static const u8 sText_AttackersStatRose[] = _("{B_ATK_NAME_WITH_PREFIX}'ın {B_BUFF1}\ndeğeri {B_BUFF2}");
const u8 gText_DefendersStatRose[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_BUFF1}\ndeğeri {B_BUFF2}");
static const u8 sText_UsingItemTheStatOfPkmnRose[] = _("{B_LAST_ITEM} kullanınca, {B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın\n{B_BUFF1} değeri {B_BUFF2}");
static const u8 sText_AttackersStatFell[] = _("{B_ATK_NAME_WITH_PREFIX}'ın {B_BUFF1}\ndeğeri {B_BUFF2}");
static const u8 sText_DefendersStatFell[] = _("{B_DEF_NAME_WITH_PREFIX}'ın {B_BUFF1}\ndeğeri {B_BUFF2}");
static const u8 sText_StatsWontIncrease2[] = _("{B_ATK_NAME_WITH_PREFIX}'ın durumu\ndaha iyiye gidemiyor!");
static const u8 sText_StatsWontDecrease2[] = _("{B_DEF_NAME_WITH_PREFIX}'ın durumu\ndaha kötü olamaz!");
static const u8 sText_CriticalHit[] = _("Kritik bir vuruş!");
static const u8 sText_OneHitKO[] = _("Bu bir tek vuruşta bitirişti!");
static const u8 sText_123Poof[] = _("{PAUSE 32}1, {PAUSE 15}2, ve{PAUSE 15}… {PAUSE 15}… {PAUSE 15}… {PAUSE 15}{PLAY_SE SE_BALL_BOUNCE_1}Puf!\p");
static const u8 sText_AndEllipsis[] = _("Ve…\p");
static const u8 sText_HMMovesCantBeForgotten[] = _("HM saldırıları\nburada unutulamaz.\p");
static const u8 sText_NotVeryEffective[] = _("Pek etkili değildi…");
static const u8 sText_SuperEffective[] = _("Süper etkiliydi!");
static const u8 sText_GotAwaySafely[] = _("{PLAY_SE SE_FLEE}Sağ salim kaçıldı!\p");
static const u8 sText_PkmnFledUsingIts[] = _("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX}, {B_LAST_ITEM}\nkullanarak kaçtı!\p");
static const u8 sText_PkmnFledUsing[] = _("{PLAY_SE SE_FLEE}{B_ATK_NAME_WITH_PREFIX}, {B_ATK_ABILITY}\nkullanarak kaçtı!\p");
static const u8 sText_WildPkmnFled[] = _("{PLAY_SE SE_FLEE}Vahşi {B_BUFF1} kaçtı!");
static const u8 sText_PlayerDefeatedLinkTrainer[] = _("Oyuncu, {B_LINK_OPPONENT1_NAME}\noyuncusunu yendi!");
static const u8 sText_TwoLinkTrainersDefeated[] = _("Oyuncu, {B_LINK_OPPONENT1_NAME}\nve {B_LINK_OPPONENT2_NAME}'ı yendi!");
static const u8 sText_PlayerLostAgainstLinkTrainer[] = _("Oyuncu, {B_LINK_OPPONENT1_NAME}\noyuncusuna kaybetti!");
static const u8 sText_PlayerLostToTwo[] = _("Oyuncu {B_LINK_OPPONENT1_NAME}\nve {B_LINK_OPPONENT2_NAME}'a kaybetti!");
static const u8 sText_PlayerBattledToDrawLinkTrainer[] = _("Oyuncu {B_LINK_OPPONENT1_NAME} ile\nberabere kaldı!");
static const u8 sText_PlayerBattledToDrawVsTwo[] = _("Oyuncu {B_LINK_OPPONENT1_NAME} ve\n{B_LINK_OPPONENT2_NAME} ile berabere kaldı!");
static const u8 sText_WildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME} kaçtı!");
static const u8 sText_TwoWildFled[] = _("{PLAY_SE SE_FLEE}{B_LINK_OPPONENT1_NAME} ve\n{B_LINK_OPPONENT2_NAME} kaçtı!");
static const u8 sText_NoRunningFromTrainers[] = _("Hayır! Bir EĞİTMEN savaşından\nkaçamazsın!\p");
static const u8 sText_CantEscape[] = _("Kaçamazsın!\p");
static const u8 sText_DontLeaveBirch[] = _("PROF. BIRCH: Beni böyle bırakma!\p");
static const u8 sText_ButNothingHappened[] = _("Ama hiçbir şey olmadı!");
static const u8 sText_ButItFailed[] = _("Ama başarısız oldu!");
static const u8 sText_ItHurtConfusion[] = _("Kafa karışıklığı nedeniyle\nkendine vurdu!");
static const u8 sText_MirrorMoveFailed[] = _("AYNA SALDIRI başarısız oldu!");
static const u8 sText_StartedToRain[] = _("Yağmur başladı!");
static const u8 sText_DownpourStarted[] = _("A downpour started!"); // corresponds to DownpourText in pokegold and pokecrystal and is used by Rain Dance in GSC
static const u8 sText_RainContinues[] = _("Yağmur devam ediyor.");
static const u8 sText_DownpourContinues[] = _("The downpour continues."); // unused
static const u8 sText_RainStopped[] = _("Yağmur durdu.");
static const u8 sText_SandstormBrewed[] = _("Kum fırtınası başladı");
static const u8 sText_SandstormRages[] = _("Kum fırtınası artıyor.");
static const u8 sText_SandstormSubsided[] = _("Kum fırtınası sona erdi.");
static const u8 sText_SunlightGotBright[] = _("Güneş açtı!");
static const u8 sText_SunlightStrong[] = _("Güneş parlıyor.");
static const u8 sText_SunlightFaded[] = _("Güneş ışığı azaldı.");
static const u8 sText_StartedHail[] = _("Dolu yağışı başladı!");
static const u8 sText_HailContinues[] = _("Dolu yağışı devam ediyor.");
static const u8 sText_HailStopped[] = _("Dolu durdu.");
static const u8 sText_FailedToSpitUp[] = _("Ama başarısız oldu!");
static const u8 sText_FailedToSwallow[] = _("Ama başarısız oldu!");
static const u8 sText_WindBecameHeatWave[] = _("Rüzgar ISI DALGASI'na\ndöndü!");
static const u8 sText_StatChangesGone[] = _("Tüm durum değişimleri\niptal oldu!");
static const u8 sText_CoinsScattered[] = _("Etrafa para saçıldı!");
static const u8 sText_TooWeakForSubstitute[] = _("KOPYA için çok güçsüzdü!");
static const u8 sText_SharedPain[] = _("Savaşçılar acılarını paylaştı!");
static const u8 sText_BellChimed[] = _("Çan çaldı!");
static const u8 sText_FaintInThree[] = _("Etkilenen tüm POKéMON'lar üç\ntur içinde bayılacak!");
static const u8 sText_NoPPLeft[] = _("Bu saldırı için yeterli\nPP kalmadı!\p");
static const u8 sText_ButNoPPLeft[] = _("Ama bu saldırı için yeterli\nPP kalmadı!");
static const u8 sText_PkmnIgnoresAsleep[] = _("{B_ATK_NAME_WITH_PREFIX} uyurken\nemirleri reddetti!");
static const u8 sText_PkmnIgnoredOrders[] = _("{B_ATK_NAME_WITH_PREFIX} emirleri\nreddediyor!");
static const u8 sText_PkmnBeganToNap[] = _("{B_ATK_NAME_WITH_PREFIX} uykuya daldı!");
static const u8 sText_PkmnLoafing[] = _("{B_ATK_NAME_WITH_PREFIX} etrafta\ndolanıyor!");
static const u8 sText_PkmnWontObey[] = _("{B_ATK_NAME_WITH_PREFIX} laf dinlemiyor!");
static const u8 sText_PkmnTurnedAway[] = _("{B_ATK_NAME_WITH_PREFIX} arkasını döndü!");
static const u8 sText_PkmnPretendNotNotice[] = _("{B_ATK_NAME_WITH_PREFIX} duymamış\ngibi yaptı!");
static const u8 sText_EnemyAboutToSwitchPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\n{B_BUFF2} kullanmak üzere.\p{B_PLAYER_NAME} POKéMON değiştirecek mi?");
static const u8 sText_PkmnLearnedMove2[] = _("{B_ATK_NAME_WITH_PREFIX}, \n{B_BUFF1} öğrendi!");
static const u8 sText_PlayerDefeatedLinkTrainerTrainer1[] = _("Oyuncu, {B_TRAINER1_CLASS} {B_TRAINER1_NAME}\neğitmenini yendi!\p");
static const u8 sText_CreptCloser[] = _("{B_PLAYER_NAME}, {B_OPPONENT_MON1_NAME}'a\nyaklaştı!");
static const u8 sText_CantGetCloser[] = _("{B_PLAYER_NAME} daha fazla\nyaklaşamıyor!");
static const u8 sText_PkmnWatchingCarefully[] = _("{B_OPPONENT_MON1_NAME} dikkatlice\nizliyor!");
static const u8 sText_PkmnCuriousAboutX[] = _("{B_OPPONENT_MON1_NAME}, {B_BUFF1}'a\nmerak duydu!");
static const u8 sText_PkmnEnthralledByX[] = _("{B_OPPONENT_MON1_NAME}, {B_BUFF1}\nkarşısında büyülendi!");
static const u8 sText_PkmnIgnoredX[] = _("{B_OPPONENT_MON1_NAME}, {B_BUFF1}'ı\numursamadı!");
static const u8 sText_ThrewPokeblockAtPkmn[] = _("{B_PLAYER_NAME}, {B_OPPONENT_MON1_NAME}'a\nbir {POKEBLOCK} attı!");
static const u8 sText_OutOfSafariBalls[] = _("{PLAY_SE SE_DING_DONG}KONUŞMACI: SAFARİ TOPLARIN\nbitti! Oyun bitti!\p");
static const u8 sText_OpponentMon1Appeared[] = _("{B_OPPONENT_MON1_NAME} belirdi!\p");
static const u8 sText_WildPkmnAppeared[] = _("Vahşi {B_OPPONENT_MON1_NAME} belirdi!\p");
static const u8 sText_LegendaryPkmnAppeared[] = _("Vahşi {B_OPPONENT_MON1_NAME} belirdi!\p");
static const u8 sText_WildPkmnAppearedPause[] = _("Vahşi {B_OPPONENT_MON1_NAME} belirdi!{PAUSE 127}");
static const u8 sText_TwoWildPkmnAppeared[] = _("Vahşi {B_OPPONENT_MON1_NAME} ve\n{B_OPPONENT_MON2_NAME} belirdi!\p");
static const u8 sText_Trainer1WantsToBattle[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nsavaşmak istiyor!\p");
static const u8 sText_LinkTrainerWantsToBattle[] = _("{B_LINK_OPPONENT1_NAME}\nsavaşmak istiyor!");
static const u8 sText_TwoLinkTrainersWantToBattle[] = _("{B_LINK_OPPONENT1_NAME} ve {B_LINK_OPPONENT2_NAME}\nsavaşmak istiyor!");
static const u8 sText_Trainer1SentOutPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME},\n{B_OPPONENT_MON1_NAME} gönderdi!");
static const u8 sText_Trainer1SentOutTwoPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME},\n{B_OPPONENT_MON1_NAME} ve {B_OPPONENT_MON2_NAME} gönderdi!");
static const u8 sText_Trainer1SentOutPkmn2[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME},\n{B_BUFF1} gönderdi!");
static const u8 sText_LinkTrainerSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME}\n{B_OPPONENT_MON1_NAME} gönderdi!");
static const u8 sText_LinkTrainerSentOutTwoPkmn[] = _("{B_LINK_OPPONENT1_NAME}, {B_OPPONENT_MON1_NAME}\nve {B_OPPONENT_MON2_NAME} gönderdi!");
static const u8 sText_TwoLinkTrainersSentOutPkmn[] = _("{B_LINK_OPPONENT1_NAME}, {B_LINK_OPPONENT_MON1_NAME} gönderdi!\n{B_LINK_OPPONENT2_NAME}, {B_LINK_OPPONENT_MON2_NAME} gönderdi!");
static const u8 sText_LinkTrainerSentOutPkmn2[] = _("{B_LINK_OPPONENT1_NAME}\n{B_BUFF1} gönderdi!");
static const u8 sText_LinkTrainerMultiSentOutPkmn[] = _("{B_LINK_SCR_TRAINER_NAME}\n{B_BUFF1} gönderdi!");
static const u8 sText_GoPkmn[] = _("Hadi, {B_PLAYER_MON1_NAME}!");
static const u8 sText_GoTwoPkmn[] = _("Gidin! {B_PLAYER_MON1_NAME} ve\n{B_PLAYER_MON2_NAME}!");
static const u8 sText_GoPkmn2[] = _("Hadi, {B_BUFF1}!");
static const u8 sText_DoItPkmn[] = _("Git! {B_BUFF1}!");
static const u8 sText_GoForItPkmn[] = _("Bu iş sende, {B_BUFF1}!");
static const u8 sText_YourFoesWeakGetEmPkmn[] = _("Düşmanın zayıf!\nYaparsın, {B_BUFF1}!");
static const u8 sText_LinkPartnerSentOutPkmnGoPkmn[] = _("{B_LINK_PARTNER_NAME}, {B_LINK_PLAYER_MON2_NAME} gönderdi!\nGit! {B_LINK_PLAYER_MON1_NAME}!");
static const u8 sText_PkmnThatsEnough[] = _("{B_BUFF1}, yeter bu kadar!\nGeri gel!");
static const u8 sText_PkmnComeBack[] = _("{B_BUFF1}, geri gel!");
static const u8 sText_PkmnOkComeBack[] = _("{B_BUFF1}, tamam!\nGeri gel!");
static const u8 sText_PkmnGoodComeBack[] = _("{B_BUFF1}, iyiydin!\nGeri gel!");
static const u8 sText_Trainer1WithdrewPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME},\n{B_BUFF1}'ı çekti!");
static const u8 sText_LinkTrainer1WithdrewPkmn[] = _("{B_LINK_OPPONENT1_NAME},\n{B_BUFF1}'ı çekti!");
static const u8 sText_LinkTrainer2WithdrewPkmn[] = _("{B_LINK_SCR_TRAINER_NAME},\n{B_BUFF1}'ı çekti!");
static const u8 sText_WildPkmnPrefix[] = _("Vahşi ");
static const u8 sText_FoePkmnPrefix[] = _("Düşman ");
static const u8 sText_EmptyString8[] = _("");
static const u8 sText_FoePkmnPrefix2[] = _("Düşman");
static const u8 sText_AllyPkmnPrefix[] = _("Dost");
static const u8 sText_FoePkmnPrefix3[] = _("Düşman");
static const u8 sText_AllyPkmnPrefix2[] = _("Dost");
static const u8 sText_FoePkmnPrefix4[] = _("Düşman");
static const u8 sText_AllyPkmnPrefix3[] = _("Dost");
static const u8 sText_AttackerUsedX[] = _("{B_ATK_NAME_WITH_PREFIX},\n{B_BUFF2} kullandı.");
static const u8 sText_ExclamationMark[] = _("");
static const u8 sText_ExclamationMark2[] = _("");
static const u8 sText_ExclamationMark3[] = _("");
static const u8 sText_ExclamationMark4[] = _("");
static const u8 sText_ExclamationMark5[] = _("");
static const u8 sText_HP2[] = _("CAN");
static const u8 sText_Attack2[] = _("SALDIRI");
static const u8 sText_Defense2[] = _("SAVUNMA");
static const u8 sText_Speed[] = _("HIZ");
static const u8 sText_SpAtk2[] = _("ÖZ. ATK");
static const u8 sText_SpDef2[] = _("ÖZ. DEF");
static const u8 sText_Accuracy[] = _("kesinlik");
static const u8 sText_Evasiveness[] = _("kaçınabilirlik");

const u8 * const gStatNamesTable[NUM_BATTLE_STATS] =
{
    [STAT_HP]      = sText_HP2,
    [STAT_ATK]     = sText_Attack2,
    [STAT_DEF]     = sText_Defense2,
    [STAT_SPEED]   = sText_Speed,
    [STAT_SPATK]   = sText_SpAtk2,
    [STAT_SPDEF]   = sText_SpDef2,
    [STAT_ACC]     = sText_Accuracy,
    [STAT_EVASION] = sText_Evasiveness,
};

static const u8 sText_PokeblockWasTooSpicy[] = _("çok baharatlıydı!");
static const u8 sText_PokeblockWasTooDry[] = _("çok kuruydu!");
static const u8 sText_PokeblockWasTooSweet[] = _("çok tatlıydı!");
static const u8 sText_PokeblockWasTooBitter[] = _("çok acıydı!");
static const u8 sText_PokeblockWasTooSour[] = _("çok ekşiydi!");

const u8 * const gPokeblockWasTooXStringTable[FLAVOR_COUNT] =
{
    [FLAVOR_SPICY]  = sText_PokeblockWasTooSpicy,
    [FLAVOR_DRY]    = sText_PokeblockWasTooDry,
    [FLAVOR_SWEET]  = sText_PokeblockWasTooSweet,
    [FLAVOR_BITTER] = sText_PokeblockWasTooBitter,
    [FLAVOR_SOUR]   = sText_PokeblockWasTooSour
};

static const u8 sText_PlayerUsedItem[] = _("{B_PLAYER_NAME}\n{B_LAST_ITEM} kullandı!");
static const u8 sText_WallyUsedItem[] = _("WALLY, {B_LAST_ITEM}\nkullandı!");
static const u8 sText_Trainer1UsedItem[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME}\n{B_LAST_ITEM} kullandı!");
static const u8 sText_TrainerBlockedBall[] = _("EĞİTMEN, topu engelledi!");
static const u8 sText_DontBeAThief[] = _("Hırsızlık yapma!");
static const u8 sText_ItDodgedBall[] = _("Atılan toptan kaçındı!\nBu POKéMON yakalanamıyor!");
static const u8 sText_YouMissedPkmn[] = _("POKéMON'u ıskaladın!");
static const u8 sText_PkmnBrokeFree[] = _("Ah, hayır!\nPOKéMON geri çıktı!");
static const u8 sText_ItAppearedCaught[] = _("Ahh!\nAz kalsın giriyordu!");
static const u8 sText_AarghAlmostHadIt[] = _("Aarh!\nNeredeyse yakalamıştım!");
static const u8 sText_ShootSoClose[] = _("Tüh!\nAmma yakındı!");
static const u8 sText_GotchaPkmnCaughtPlayer[] = _("Yakaladım!\n{B_OPPONENT_MON1_NAME} yakalandı!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}\p");
static const u8 sText_GotchaPkmnCaughtWally[] = _("Yakaladım!\n{B_OPPONENT_MON1_NAME} yakalandı!{WAIT_SE}{PLAY_BGM MUS_CAUGHT}{PAUSE 127}");
static const u8 sText_GiveNicknameCaptured[] = _("Yakalanan {B_OPPONENT_MON1_NAME}'a bir\nisim vermek ister misin?");
static const u8 sText_PkmnSentToPC[] = _("{B_OPPONENT_MON1_NAME}, {B_PC_CREATOR_NAME}\nPC'sine gönderildi.");
static const u8 sText_Someones[] = _("birisinin");
static const u8 sText_Lanettes[] = _("LANETTE'nin");
static const u8 sText_PkmnDataAddedToDex[] = _("{B_OPPONENT_MON1_NAME}'ın verisi\nPOKéDEX'e eklendi.\p");
static const u8 sText_ItIsRaining[] = _("Yağmur yağıyor.");
static const u8 sText_SandstormIsRaging[] = _("Kum fırtınası devam ediyor.");
static const u8 sText_BoxIsFull[] = _("KUTU dolu!\nDaha yakalayamazsın!\p");
static const u8 sText_EnigmaBerry[] = _("ENIGMA MEYVE");
static const u8 sText_BerrySuffix[] = _(" MEYVE");
static const u8 sText_PkmnsItemCuredParalysis[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nfelci geçirdi!");
static const u8 sText_PkmnsItemCuredPoison[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nzehri geçirdi!");
static const u8 sText_PkmnsItemHealedBurn[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nyanığı geçirdi!");
static const u8 sText_PkmnsItemDefrostedIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nbuzu geçirdi!");
static const u8 sText_PkmnsItemWokeIt[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nuykudan uyandırdı!");
static const u8 sText_PkmnsItemSnappedOut[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nkafa karışıklığını bitirdi!");
static const u8 sText_PkmnsItemCuredProblem[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\n{B_BUFF1} sorununu geçirdi!");
static const u8 sText_PkmnsItemNormalizedStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\ndurumunu normalleştirdi!");
static const u8 sText_PkmnsItemRestoredHealth[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nsağlık kazandı!");
static const u8 sText_PkmnsItemRestoredPP[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\n{B_BUFF1}'ın PP'sini yeniledi!");
static const u8 sText_PkmnsItemRestoredStatus[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\ndurumunu iyileştirdi!");
static const u8 sText_PkmnsItemRestoredHPALittle[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın {B_LAST_ITEM}'ı\nCAN'ını biraz iyileştirdi!");
static const u8 sText_ItemAllowsOnlyYMove[] = _("{B_LAST_ITEM}, sadece\n{B_CURRENT_MOVE}'a izin veriyor!\p");
static const u8 sText_PkmnHungOnWithX[] = _("{B_DEF_NAME_WITH_PREFIX}, {B_LAST_ITEM}\nsayesinde tutundu!");
const u8 gText_EmptyString3[] = _("");
static const u8 sText_YouThrowABallNowRight[] = _("Bir TOP atıyoruz değil mi?\nEe… Hadi bakalım!");

// early declaration of strings
static const u8 sText_PkmnIncapableOfPower[];
static const u8 sText_GlintAppearsInEye[];
static const u8 sText_PkmnGettingIntoPosition[];
static const u8 sText_PkmnBeganGrowlingDeeply[];
static const u8 sText_PkmnEagerForMore[];
static const u8 sText_DefeatedOpponentByReferee[];
static const u8 sText_LostToOpponentByReferee[];
static const u8 sText_TiedOpponentByReferee[];
static const u8 sText_QuestionForfeitMatch[];
static const u8 sText_ForfeitedMatch[];
static const u8 sText_Trainer1WinText[];
static const u8 sText_Trainer2WinText[];
static const u8 sText_TwoInGameTrainersDefeated[];
static const u8 sText_Trainer2LoseText[];

const u8 * const gBattleStringsTable[BATTLESTRINGS_COUNT - BATTLESTRINGS_TABLE_START] =
{
    [STRINGID_TRAINER1LOSETEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer1LoseText,
    [STRINGID_PKMNGAINEDEXP - BATTLESTRINGS_TABLE_START] = sText_PkmnGainedEXP,
    [STRINGID_PKMNGREWTOLV - BATTLESTRINGS_TABLE_START] = sText_PkmnGrewToLv,
    [STRINGID_PKMNLEARNEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnLearnedMove,
    [STRINGID_TRYTOLEARNMOVE1 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove1,
    [STRINGID_TRYTOLEARNMOVE2 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove2,
    [STRINGID_TRYTOLEARNMOVE3 - BATTLESTRINGS_TABLE_START] = sText_TryToLearnMove3,
    [STRINGID_PKMNFORGOTMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnForgotMove,
    [STRINGID_STOPLEARNINGMOVE - BATTLESTRINGS_TABLE_START] = sText_StopLearningMove,
    [STRINGID_DIDNOTLEARNMOVE - BATTLESTRINGS_TABLE_START] = sText_DidNotLearnMove,
    [STRINGID_PKMNLEARNEDMOVE2 - BATTLESTRINGS_TABLE_START] = sText_PkmnLearnedMove2,
    [STRINGID_ATTACKMISSED - BATTLESTRINGS_TABLE_START] = sText_AttackMissed,
    [STRINGID_PKMNPROTECTEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedItself,
    [STRINGID_STATSWONTINCREASE2 - BATTLESTRINGS_TABLE_START] = sText_StatsWontIncrease2,
    [STRINGID_AVOIDEDDAMAGE - BATTLESTRINGS_TABLE_START] = sText_AvoidedDamage,
    [STRINGID_ITDOESNTAFFECT - BATTLESTRINGS_TABLE_START] = sText_ItDoesntAffect,
    [STRINGID_ATTACKERFAINTED - BATTLESTRINGS_TABLE_START] = sText_AttackerFainted,
    [STRINGID_TARGETFAINTED - BATTLESTRINGS_TABLE_START] = sText_TargetFainted,
    [STRINGID_PLAYERGOTMONEY - BATTLESTRINGS_TABLE_START] = sText_PlayerGotMoney,
    [STRINGID_PLAYERWHITEOUT - BATTLESTRINGS_TABLE_START] = sText_PlayerWhiteout,
    [STRINGID_PLAYERWHITEOUT2 - BATTLESTRINGS_TABLE_START] = sText_PlayerWhiteout2,
    [STRINGID_PREVENTSESCAPE - BATTLESTRINGS_TABLE_START] = sText_PreventsEscape,
    [STRINGID_HITXTIMES - BATTLESTRINGS_TABLE_START] = sText_HitXTimes,
    [STRINGID_PKMNFELLASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnFellAsleep,
    [STRINGID_PKMNMADESLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeSleep,
    [STRINGID_PKMNALREADYASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyAsleep,
    [STRINGID_PKMNALREADYASLEEP2 - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyAsleep2,
    [STRINGID_PKMNWASNTAFFECTED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasntAffected,
    [STRINGID_PKMNWASPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasPoisoned,
    [STRINGID_PKMNPOISONEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnPoisonedBy,
    [STRINGID_PKMNHURTBYPOISON - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtByPoison,
    [STRINGID_PKMNALREADYPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyPoisoned,
    [STRINGID_PKMNBADLYPOISONED - BATTLESTRINGS_TABLE_START] = sText_PkmnBadlyPoisoned,
    [STRINGID_PKMNENERGYDRAINED - BATTLESTRINGS_TABLE_START] = sText_PkmnEnergyDrained,
    [STRINGID_PKMNWASBURNED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasBurned,
    [STRINGID_PKMNBURNEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnBurnedBy,
    [STRINGID_PKMNHURTBYBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtByBurn,
    [STRINGID_PKMNWASFROZEN - BATTLESTRINGS_TABLE_START] = sText_PkmnWasFrozen,
    [STRINGID_PKMNFROZENBY - BATTLESTRINGS_TABLE_START] = sText_PkmnFrozenBy,
    [STRINGID_PKMNISFROZEN - BATTLESTRINGS_TABLE_START] = sText_PkmnIsFrozen,
    [STRINGID_PKMNWASDEFROSTED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrosted,
    [STRINGID_PKMNWASDEFROSTED2 - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrosted2,
    [STRINGID_PKMNWASDEFROSTEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDefrostedBy,
    [STRINGID_PKMNWASPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasParalyzed,
    [STRINGID_PKMNWASPARALYZEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasParalyzedBy,
    [STRINGID_PKMNISPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsParalyzed,
    [STRINGID_PKMNISALREADYPARALYZED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsAlreadyParalyzed,
    [STRINGID_PKMNHEALEDPARALYSIS - BATTLESTRINGS_TABLE_START] = sText_PkmnHealedParalysis,
    [STRINGID_PKMNDREAMEATEN - BATTLESTRINGS_TABLE_START] = sText_PkmnDreamEaten,
    [STRINGID_STATSWONTINCREASE - BATTLESTRINGS_TABLE_START] = sText_StatsWontIncrease,
    [STRINGID_STATSWONTDECREASE - BATTLESTRINGS_TABLE_START] = sText_StatsWontDecrease,
    [STRINGID_TEAMSTOPPEDWORKING - BATTLESTRINGS_TABLE_START] = sText_TeamStoppedWorking,
    [STRINGID_FOESTOPPEDWORKING - BATTLESTRINGS_TABLE_START] = sText_FoeStoppedWorking,
    [STRINGID_PKMNISCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnIsConfused,
    [STRINGID_PKMNHEALEDCONFUSION - BATTLESTRINGS_TABLE_START] = sText_PkmnHealedConfusion,
    [STRINGID_PKMNWASCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnWasConfused,
    [STRINGID_PKMNALREADYCONFUSED - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyConfused,
    [STRINGID_PKMNFELLINLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnFellInLove,
    [STRINGID_PKMNINLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnInLove,
    [STRINGID_PKMNIMMOBILIZEDBYLOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnImmobilizedByLove,
    [STRINGID_PKMNBLOWNAWAY - BATTLESTRINGS_TABLE_START] = sText_PkmnBlownAway,
    [STRINGID_PKMNCHANGEDTYPE - BATTLESTRINGS_TABLE_START] = sText_PkmnChangedType,
    [STRINGID_PKMNFLINCHED - BATTLESTRINGS_TABLE_START] = sText_PkmnFlinched,
    [STRINGID_PKMNREGAINEDHEALTH - BATTLESTRINGS_TABLE_START] = sText_PkmnRegainedHealth,
    [STRINGID_PKMNHPFULL - BATTLESTRINGS_TABLE_START] = sText_PkmnHPFull,
    [STRINGID_PKMNRAISEDSPDEF - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpDef,
    [STRINGID_PKMNRAISEDDEF - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedDef,
    [STRINGID_PKMNCOVEREDBYVEIL - BATTLESTRINGS_TABLE_START] = sText_PkmnCoveredByVeil,
    [STRINGID_PKMNUSEDSAFEGUARD - BATTLESTRINGS_TABLE_START] = sText_PkmnUsedSafeguard,
    [STRINGID_PKMNSAFEGUARDEXPIRED - BATTLESTRINGS_TABLE_START] = sText_PkmnSafeguardExpired,
    [STRINGID_PKMNWENTTOSLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnWentToSleep,
    [STRINGID_PKMNSLEPTHEALTHY - BATTLESTRINGS_TABLE_START] = sText_PkmnSleptHealthy,
    [STRINGID_PKMNWHIPPEDWHIRLWIND - BATTLESTRINGS_TABLE_START] = sText_PkmnWhippedWhirlwind,
    [STRINGID_PKMNTOOKSUNLIGHT - BATTLESTRINGS_TABLE_START] = sText_PkmnTookSunlight,
    [STRINGID_PKMNLOWEREDHEAD - BATTLESTRINGS_TABLE_START] = sText_PkmnLoweredHead,
    [STRINGID_PKMNISGLOWING - BATTLESTRINGS_TABLE_START] = sText_PkmnIsGlowing,
    [STRINGID_PKMNFLEWHIGH - BATTLESTRINGS_TABLE_START] = sText_PkmnFlewHigh,
    [STRINGID_PKMNDUGHOLE - BATTLESTRINGS_TABLE_START] = sText_PkmnDugHole,
    [STRINGID_PKMNSQUEEZEDBYBIND - BATTLESTRINGS_TABLE_START] = sText_PkmnSqueezedByBind,
    [STRINGID_PKMNTRAPPEDINVORTEX - BATTLESTRINGS_TABLE_START] = sText_PkmnTrappedInVortex,
    [STRINGID_PKMNWRAPPEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnWrappedBy,
    [STRINGID_PKMNCLAMPED - BATTLESTRINGS_TABLE_START] = sText_PkmnClamped,
    [STRINGID_PKMNHURTBY - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtBy,
    [STRINGID_PKMNFREEDFROM - BATTLESTRINGS_TABLE_START] = sText_PkmnFreedFrom,
    [STRINGID_PKMNCRASHED - BATTLESTRINGS_TABLE_START] = sText_PkmnCrashed,
    [STRINGID_PKMNSHROUDEDINMIST - BATTLESTRINGS_TABLE_START] = gText_PkmnShroudedInMist,
    [STRINGID_PKMNPROTECTEDBYMIST - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedByMist,
    [STRINGID_PKMNGETTINGPUMPED - BATTLESTRINGS_TABLE_START] = gText_PkmnGettingPumped,
    [STRINGID_PKMNHITWITHRECOIL - BATTLESTRINGS_TABLE_START] = sText_PkmnHitWithRecoil,
    [STRINGID_PKMNPROTECTEDITSELF2 - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedItself2,
    [STRINGID_PKMNBUFFETEDBYSANDSTORM - BATTLESTRINGS_TABLE_START] = sText_PkmnBuffetedBySandstorm,
    [STRINGID_PKMNPELTEDBYHAIL - BATTLESTRINGS_TABLE_START] = sText_PkmnPeltedByHail,
    [STRINGID_PKMNSEEDED - BATTLESTRINGS_TABLE_START] = sText_PkmnSeeded,
    [STRINGID_PKMNEVADEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnEvadedAttack,
    [STRINGID_PKMNSAPPEDBYLEECHSEED - BATTLESTRINGS_TABLE_START] = sText_PkmnSappedByLeechSeed,
    [STRINGID_PKMNFASTASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnFastAsleep,
    [STRINGID_PKMNWOKEUP - BATTLESTRINGS_TABLE_START] = sText_PkmnWokeUp,
    [STRINGID_PKMNUPROARKEPTAWAKE - BATTLESTRINGS_TABLE_START] = sText_PkmnUproarKeptAwake,
    [STRINGID_PKMNWOKEUPINUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnWokeUpInUproar,
    [STRINGID_PKMNCAUSEDUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnCausedUproar,
    [STRINGID_PKMNMAKINGUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnMakingUproar,
    [STRINGID_PKMNCALMEDDOWN - BATTLESTRINGS_TABLE_START] = sText_PkmnCalmedDown,
    [STRINGID_PKMNCANTSLEEPINUPROAR - BATTLESTRINGS_TABLE_START] = sText_PkmnCantSleepInUproar,
    [STRINGID_PKMNSTOCKPILED - BATTLESTRINGS_TABLE_START] = sText_PkmnStockpiled,
    [STRINGID_PKMNCANTSTOCKPILE - BATTLESTRINGS_TABLE_START] = sText_PkmnCantStockpile,
    [STRINGID_PKMNCANTSLEEPINUPROAR2 - BATTLESTRINGS_TABLE_START] = sText_PkmnCantSleepInUproar2,
    [STRINGID_UPROARKEPTPKMNAWAKE - BATTLESTRINGS_TABLE_START] = sText_UproarKeptPkmnAwake,
    [STRINGID_PKMNSTAYEDAWAKEUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnStayedAwakeUsing,
    [STRINGID_PKMNSTORINGENERGY - BATTLESTRINGS_TABLE_START] = sText_PkmnStoringEnergy,
    [STRINGID_PKMNUNLEASHEDENERGY - BATTLESTRINGS_TABLE_START] = sText_PkmnUnleashedEnergy,
    [STRINGID_PKMNFATIGUECONFUSION - BATTLESTRINGS_TABLE_START] = sText_PkmnFatigueConfusion,
    [STRINGID_PLAYERPICKEDUPMONEY - BATTLESTRINGS_TABLE_START] = sText_PlayerPickedUpMoney,
    [STRINGID_PKMNUNAFFECTED - BATTLESTRINGS_TABLE_START] = sText_PkmnUnaffected,
    [STRINGID_PKMNTRANSFORMEDINTO - BATTLESTRINGS_TABLE_START] = sText_PkmnTransformedInto,
    [STRINGID_PKMNMADESUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeSubstitute,
    [STRINGID_PKMNHASSUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_PkmnHasSubstitute,
    [STRINGID_SUBSTITUTEDAMAGED - BATTLESTRINGS_TABLE_START] = sText_SubstituteDamaged,
    [STRINGID_PKMNSUBSTITUTEFADED - BATTLESTRINGS_TABLE_START] = sText_PkmnSubstituteFaded,
    [STRINGID_PKMNMUSTRECHARGE - BATTLESTRINGS_TABLE_START] = sText_PkmnMustRecharge,
    [STRINGID_PKMNRAGEBUILDING - BATTLESTRINGS_TABLE_START] = sText_PkmnRageBuilding,
    [STRINGID_PKMNMOVEWASDISABLED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveWasDisabled,
    [STRINGID_PKMNMOVEISDISABLED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveIsDisabled,
    [STRINGID_PKMNMOVEDISABLEDNOMORE - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveDisabledNoMore,
    [STRINGID_PKMNGOTENCORE - BATTLESTRINGS_TABLE_START] = sText_PkmnGotEncore,
    [STRINGID_PKMNENCOREENDED - BATTLESTRINGS_TABLE_START] = sText_PkmnEncoreEnded,
    [STRINGID_PKMNTOOKAIM - BATTLESTRINGS_TABLE_START] = sText_PkmnTookAim,
    [STRINGID_PKMNSKETCHEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSketchedMove,
    [STRINGID_PKMNTRYINGTOTAKEFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnTryingToTakeFoe,
    [STRINGID_PKMNTOOKFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnTookFoe,
    [STRINGID_PKMNREDUCEDPP - BATTLESTRINGS_TABLE_START] = sText_PkmnReducedPP,
    [STRINGID_PKMNSTOLEITEM - BATTLESTRINGS_TABLE_START] = sText_PkmnStoleItem,
    [STRINGID_TARGETCANTESCAPENOW - BATTLESTRINGS_TABLE_START] = sText_TargetCantEscapeNow,
    [STRINGID_PKMNFELLINTONIGHTMARE - BATTLESTRINGS_TABLE_START] = sText_PkmnFellIntoNightmare,
    [STRINGID_PKMNLOCKEDINNIGHTMARE - BATTLESTRINGS_TABLE_START] = sText_PkmnLockedInNightmare,
    [STRINGID_PKMNLAIDCURSE - BATTLESTRINGS_TABLE_START] = sText_PkmnLaidCurse,
    [STRINGID_PKMNAFFLICTEDBYCURSE - BATTLESTRINGS_TABLE_START] = sText_PkmnAfflictedByCurse,
    [STRINGID_SPIKESSCATTERED - BATTLESTRINGS_TABLE_START] = sText_SpikesScattered,
    [STRINGID_PKMNHURTBYSPIKES - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtBySpikes,
    [STRINGID_PKMNIDENTIFIED - BATTLESTRINGS_TABLE_START] = sText_PkmnIdentified,
    [STRINGID_PKMNPERISHCOUNTFELL - BATTLESTRINGS_TABLE_START] = sText_PkmnPerishCountFell,
    [STRINGID_PKMNBRACEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnBracedItself,
    [STRINGID_PKMNENDUREDHIT - BATTLESTRINGS_TABLE_START] = sText_PkmnEnduredHit,
    [STRINGID_MAGNITUDESTRENGTH - BATTLESTRINGS_TABLE_START] = sText_MagnitudeStrength,
    [STRINGID_PKMNCUTHPMAXEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnCutHPMaxedAttack,
    [STRINGID_PKMNCOPIEDSTATCHANGES - BATTLESTRINGS_TABLE_START] = sText_PkmnCopiedStatChanges,
    [STRINGID_PKMNGOTFREE - BATTLESTRINGS_TABLE_START] = sText_PkmnGotFree,
    [STRINGID_PKMNSHEDLEECHSEED - BATTLESTRINGS_TABLE_START] = sText_PkmnShedLeechSeed,
    [STRINGID_PKMNBLEWAWAYSPIKES - BATTLESTRINGS_TABLE_START] = sText_PkmnBlewAwaySpikes,
    [STRINGID_PKMNFLEDFROMBATTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnFledFromBattle,
    [STRINGID_PKMNFORESAWATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnForesawAttack,
    [STRINGID_PKMNTOOKATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnTookAttack,
    [STRINGID_PKMNATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnAttack,
    [STRINGID_PKMNCENTERATTENTION - BATTLESTRINGS_TABLE_START] = sText_PkmnCenterAttention,
    [STRINGID_PKMNCHARGINGPOWER - BATTLESTRINGS_TABLE_START] = sText_PkmnChargingPower,
    [STRINGID_NATUREPOWERTURNEDINTO - BATTLESTRINGS_TABLE_START] = sText_NaturePowerTurnedInto,
    [STRINGID_PKMNSTATUSNORMAL - BATTLESTRINGS_TABLE_START] = sText_PkmnStatusNormal,
    [STRINGID_PKMNHASNOMOVESLEFT - BATTLESTRINGS_TABLE_START] = sText_PkmnHasNoMovesLeft,
    [STRINGID_PKMNSUBJECTEDTOTORMENT - BATTLESTRINGS_TABLE_START] = sText_PkmnSubjectedToTorment,
    [STRINGID_PKMNCANTUSEMOVETORMENT - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveTorment,
    [STRINGID_PKMNTIGHTENINGFOCUS - BATTLESTRINGS_TABLE_START] = sText_PkmnTighteningFocus,
    [STRINGID_PKMNFELLFORTAUNT - BATTLESTRINGS_TABLE_START] = sText_PkmnFellForTaunt,
    [STRINGID_PKMNCANTUSEMOVETAUNT - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveTaunt,
    [STRINGID_PKMNREADYTOHELP - BATTLESTRINGS_TABLE_START] = sText_PkmnReadyToHelp,
    [STRINGID_PKMNSWITCHEDITEMS - BATTLESTRINGS_TABLE_START] = sText_PkmnSwitchedItems,
    [STRINGID_PKMNCOPIEDFOE - BATTLESTRINGS_TABLE_START] = sText_PkmnCopiedFoe,
    [STRINGID_PKMNMADEWISH - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeWish,
    [STRINGID_PKMNWISHCAMETRUE - BATTLESTRINGS_TABLE_START] = sText_PkmnWishCameTrue,
    [STRINGID_PKMNPLANTEDROOTS - BATTLESTRINGS_TABLE_START] = sText_PkmnPlantedRoots,
    [STRINGID_PKMNABSORBEDNUTRIENTS - BATTLESTRINGS_TABLE_START] = sText_PkmnAbsorbedNutrients,
    [STRINGID_PKMNANCHOREDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnAnchoredItself,
    [STRINGID_PKMNWASMADEDROWSY - BATTLESTRINGS_TABLE_START] = sText_PkmnWasMadeDrowsy,
    [STRINGID_PKMNKNOCKEDOFF - BATTLESTRINGS_TABLE_START] = sText_PkmnKnockedOff,
    [STRINGID_PKMNSWAPPEDABILITIES - BATTLESTRINGS_TABLE_START] = sText_PkmnSwappedAbilities,
    [STRINGID_PKMNSEALEDOPPONENTMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSealedOpponentMove,
    [STRINGID_PKMNCANTUSEMOVESEALED - BATTLESTRINGS_TABLE_START] = sText_PkmnCantUseMoveSealed,
    [STRINGID_PKMNWANTSGRUDGE - BATTLESTRINGS_TABLE_START] = sText_PkmnWantsGrudge,
    [STRINGID_PKMNLOSTPPGRUDGE - BATTLESTRINGS_TABLE_START] = sText_PkmnLostPPGrudge,
    [STRINGID_PKMNSHROUDEDITSELF - BATTLESTRINGS_TABLE_START] = sText_PkmnShroudedItself,
    [STRINGID_PKMNMOVEBOUNCED - BATTLESTRINGS_TABLE_START] = sText_PkmnMoveBounced,
    [STRINGID_PKMNWAITSFORTARGET - BATTLESTRINGS_TABLE_START] = sText_PkmnWaitsForTarget,
    [STRINGID_PKMNSNATCHEDMOVE - BATTLESTRINGS_TABLE_START] = sText_PkmnSnatchedMove,
    [STRINGID_PKMNMADEITRAIN - BATTLESTRINGS_TABLE_START] = sText_PkmnMadeItRain,
    [STRINGID_PKMNRAISEDSPEED - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpeed,
    [STRINGID_PKMNPROTECTEDBY - BATTLESTRINGS_TABLE_START] = sText_PkmnProtectedBy,
    [STRINGID_PKMNPREVENTSUSAGE - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsUsage,
    [STRINGID_PKMNRESTOREDHPUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnRestoredHPUsing,
    [STRINGID_PKMNCHANGEDTYPEWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnChangedTypeWith,
    [STRINGID_PKMNPREVENTSPARALYSISWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsParalysisWith,
    [STRINGID_PKMNPREVENTSROMANCEWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsRomanceWith,
    [STRINGID_PKMNPREVENTSPOISONINGWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsPoisoningWith,
    [STRINGID_PKMNPREVENTSCONFUSIONWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsConfusionWith,
    [STRINGID_PKMNRAISEDFIREPOWERWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedFirePowerWith,
    [STRINGID_PKMNANCHORSITSELFWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnAnchorsItselfWith,
    [STRINGID_PKMNCUTSATTACKWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnCutsAttackWith,
    [STRINGID_PKMNPREVENTSSTATLOSSWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnPreventsStatLossWith,
    [STRINGID_PKMNHURTSWITH - BATTLESTRINGS_TABLE_START] = sText_PkmnHurtsWith,
    [STRINGID_PKMNTRACED - BATTLESTRINGS_TABLE_START] = sText_PkmnTraced,
    [STRINGID_STATSHARPLY - BATTLESTRINGS_TABLE_START] = sText_StatSharply,
    [STRINGID_STATROSE - BATTLESTRINGS_TABLE_START] = gText_StatRose,
    [STRINGID_STATHARSHLY - BATTLESTRINGS_TABLE_START] = sText_StatHarshly,
    [STRINGID_STATFELL - BATTLESTRINGS_TABLE_START] = sText_StatFell,
    [STRINGID_ATTACKERSSTATROSE - BATTLESTRINGS_TABLE_START] = sText_AttackersStatRose,
    [STRINGID_DEFENDERSSTATROSE - BATTLESTRINGS_TABLE_START] = gText_DefendersStatRose,
    [STRINGID_ATTACKERSSTATFELL - BATTLESTRINGS_TABLE_START] = sText_AttackersStatFell,
    [STRINGID_DEFENDERSSTATFELL - BATTLESTRINGS_TABLE_START] = sText_DefendersStatFell,
    [STRINGID_CRITICALHIT - BATTLESTRINGS_TABLE_START] = sText_CriticalHit,
    [STRINGID_ONEHITKO - BATTLESTRINGS_TABLE_START] = sText_OneHitKO,
    [STRINGID_123POOF - BATTLESTRINGS_TABLE_START] = sText_123Poof,
    [STRINGID_ANDELLIPSIS - BATTLESTRINGS_TABLE_START] = sText_AndEllipsis,
    [STRINGID_NOTVERYEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_NotVeryEffective,
    [STRINGID_SUPEREFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_SuperEffective,
    [STRINGID_GOTAWAYSAFELY - BATTLESTRINGS_TABLE_START] = sText_GotAwaySafely,
    [STRINGID_WILDPKMNFLED - BATTLESTRINGS_TABLE_START] = sText_WildPkmnFled,
    [STRINGID_NORUNNINGFROMTRAINERS - BATTLESTRINGS_TABLE_START] = sText_NoRunningFromTrainers,
    [STRINGID_CANTESCAPE - BATTLESTRINGS_TABLE_START] = sText_CantEscape,
    [STRINGID_DONTLEAVEBIRCH - BATTLESTRINGS_TABLE_START] = sText_DontLeaveBirch,
    [STRINGID_BUTNOTHINGHAPPENED - BATTLESTRINGS_TABLE_START] = sText_ButNothingHappened,
    [STRINGID_BUTITFAILED - BATTLESTRINGS_TABLE_START] = sText_ButItFailed,
    [STRINGID_ITHURTCONFUSION - BATTLESTRINGS_TABLE_START] = sText_ItHurtConfusion,
    [STRINGID_MIRRORMOVEFAILED - BATTLESTRINGS_TABLE_START] = sText_MirrorMoveFailed,
    [STRINGID_STARTEDTORAIN - BATTLESTRINGS_TABLE_START] = sText_StartedToRain,
    [STRINGID_DOWNPOURSTARTED - BATTLESTRINGS_TABLE_START] = sText_DownpourStarted,
    [STRINGID_RAINCONTINUES - BATTLESTRINGS_TABLE_START] = sText_RainContinues,
    [STRINGID_DOWNPOURCONTINUES - BATTLESTRINGS_TABLE_START] = sText_DownpourContinues,
    [STRINGID_RAINSTOPPED - BATTLESTRINGS_TABLE_START] = sText_RainStopped,
    [STRINGID_SANDSTORMBREWED - BATTLESTRINGS_TABLE_START] = sText_SandstormBrewed,
    [STRINGID_SANDSTORMRAGES - BATTLESTRINGS_TABLE_START] = sText_SandstormRages,
    [STRINGID_SANDSTORMSUBSIDED - BATTLESTRINGS_TABLE_START] = sText_SandstormSubsided,
    [STRINGID_SUNLIGHTGOTBRIGHT - BATTLESTRINGS_TABLE_START] = sText_SunlightGotBright,
    [STRINGID_SUNLIGHTSTRONG - BATTLESTRINGS_TABLE_START] = sText_SunlightStrong,
    [STRINGID_SUNLIGHTFADED - BATTLESTRINGS_TABLE_START] = sText_SunlightFaded,
    [STRINGID_STARTEDHAIL - BATTLESTRINGS_TABLE_START] = sText_StartedHail,
    [STRINGID_HAILCONTINUES - BATTLESTRINGS_TABLE_START] = sText_HailContinues,
    [STRINGID_HAILSTOPPED - BATTLESTRINGS_TABLE_START] = sText_HailStopped,
    [STRINGID_FAILEDTOSPITUP - BATTLESTRINGS_TABLE_START] = sText_FailedToSpitUp,
    [STRINGID_FAILEDTOSWALLOW - BATTLESTRINGS_TABLE_START] = sText_FailedToSwallow,
    [STRINGID_WINDBECAMEHEATWAVE - BATTLESTRINGS_TABLE_START] = sText_WindBecameHeatWave,
    [STRINGID_STATCHANGESGONE - BATTLESTRINGS_TABLE_START] = sText_StatChangesGone,
    [STRINGID_COINSSCATTERED - BATTLESTRINGS_TABLE_START] = sText_CoinsScattered,
    [STRINGID_TOOWEAKFORSUBSTITUTE - BATTLESTRINGS_TABLE_START] = sText_TooWeakForSubstitute,
    [STRINGID_SHAREDPAIN - BATTLESTRINGS_TABLE_START] = sText_SharedPain,
    [STRINGID_BELLCHIMED - BATTLESTRINGS_TABLE_START] = sText_BellChimed,
    [STRINGID_FAINTINTHREE - BATTLESTRINGS_TABLE_START] = sText_FaintInThree,
    [STRINGID_NOPPLEFT - BATTLESTRINGS_TABLE_START] = sText_NoPPLeft,
    [STRINGID_BUTNOPPLEFT - BATTLESTRINGS_TABLE_START] = sText_ButNoPPLeft,
    [STRINGID_PLAYERUSEDITEM - BATTLESTRINGS_TABLE_START] = sText_PlayerUsedItem,
    [STRINGID_WALLYUSEDITEM - BATTLESTRINGS_TABLE_START] = sText_WallyUsedItem,
    [STRINGID_TRAINERBLOCKEDBALL - BATTLESTRINGS_TABLE_START] = sText_TrainerBlockedBall,
    [STRINGID_DONTBEATHIEF - BATTLESTRINGS_TABLE_START] = sText_DontBeAThief,
    [STRINGID_ITDODGEDBALL - BATTLESTRINGS_TABLE_START] = sText_ItDodgedBall,
    [STRINGID_YOUMISSEDPKMN - BATTLESTRINGS_TABLE_START] = sText_YouMissedPkmn,
    [STRINGID_PKMNBROKEFREE - BATTLESTRINGS_TABLE_START] = sText_PkmnBrokeFree,
    [STRINGID_ITAPPEAREDCAUGHT - BATTLESTRINGS_TABLE_START] = sText_ItAppearedCaught,
    [STRINGID_AARGHALMOSTHADIT - BATTLESTRINGS_TABLE_START] = sText_AarghAlmostHadIt,
    [STRINGID_SHOOTSOCLOSE - BATTLESTRINGS_TABLE_START] = sText_ShootSoClose,
    [STRINGID_GOTCHAPKMNCAUGHTPLAYER - BATTLESTRINGS_TABLE_START] = sText_GotchaPkmnCaughtPlayer,
    [STRINGID_GOTCHAPKMNCAUGHTWALLY - BATTLESTRINGS_TABLE_START] = sText_GotchaPkmnCaughtWally,
    [STRINGID_GIVENICKNAMECAPTURED - BATTLESTRINGS_TABLE_START] = sText_GiveNicknameCaptured,
    [STRINGID_PKMNSENTTOPC - BATTLESTRINGS_TABLE_START] = sText_PkmnSentToPC,
    [STRINGID_PKMNDATAADDEDTODEX - BATTLESTRINGS_TABLE_START] = sText_PkmnDataAddedToDex,
    [STRINGID_ITISRAINING - BATTLESTRINGS_TABLE_START] = sText_ItIsRaining,
    [STRINGID_SANDSTORMISRAGING - BATTLESTRINGS_TABLE_START] = sText_SandstormIsRaging,
    [STRINGID_CANTESCAPE2 - BATTLESTRINGS_TABLE_START] = sText_CantEscape2,
    [STRINGID_PKMNIGNORESASLEEP - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoresAsleep,
    [STRINGID_PKMNIGNOREDORDERS - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoredOrders,
    [STRINGID_PKMNBEGANTONAP - BATTLESTRINGS_TABLE_START] = sText_PkmnBeganToNap,
    [STRINGID_PKMNLOAFING - BATTLESTRINGS_TABLE_START] = sText_PkmnLoafing,
    [STRINGID_PKMNWONTOBEY - BATTLESTRINGS_TABLE_START] = sText_PkmnWontObey,
    [STRINGID_PKMNTURNEDAWAY - BATTLESTRINGS_TABLE_START] = sText_PkmnTurnedAway,
    [STRINGID_PKMNPRETENDNOTNOTICE - BATTLESTRINGS_TABLE_START] = sText_PkmnPretendNotNotice,
    [STRINGID_ENEMYABOUTTOSWITCHPKMN - BATTLESTRINGS_TABLE_START] = sText_EnemyAboutToSwitchPkmn,
    [STRINGID_CREPTCLOSER - BATTLESTRINGS_TABLE_START] = sText_CreptCloser,
    [STRINGID_CANTGETCLOSER - BATTLESTRINGS_TABLE_START] = sText_CantGetCloser,
    [STRINGID_PKMNWATCHINGCAREFULLY - BATTLESTRINGS_TABLE_START] = sText_PkmnWatchingCarefully,
    [STRINGID_PKMNCURIOUSABOUTX - BATTLESTRINGS_TABLE_START] = sText_PkmnCuriousAboutX,
    [STRINGID_PKMNENTHRALLEDBYX - BATTLESTRINGS_TABLE_START] = sText_PkmnEnthralledByX,
    [STRINGID_PKMNIGNOREDX - BATTLESTRINGS_TABLE_START] = sText_PkmnIgnoredX,
    [STRINGID_THREWPOKEBLOCKATPKMN - BATTLESTRINGS_TABLE_START] = sText_ThrewPokeblockAtPkmn,
    [STRINGID_OUTOFSAFARIBALLS - BATTLESTRINGS_TABLE_START] = sText_OutOfSafariBalls,
    [STRINGID_PKMNSITEMCUREDPARALYSIS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredParalysis,
    [STRINGID_PKMNSITEMCUREDPOISON - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredPoison,
    [STRINGID_PKMNSITEMHEALEDBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemHealedBurn,
    [STRINGID_PKMNSITEMDEFROSTEDIT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemDefrostedIt,
    [STRINGID_PKMNSITEMWOKEIT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemWokeIt,
    [STRINGID_PKMNSITEMSNAPPEDOUT - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemSnappedOut,
    [STRINGID_PKMNSITEMCUREDPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemCuredProblem,
    [STRINGID_PKMNSITEMRESTOREDHEALTH - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredHealth,
    [STRINGID_PKMNSITEMRESTOREDPP - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredPP,
    [STRINGID_PKMNSITEMRESTOREDSTATUS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredStatus,
    [STRINGID_PKMNSITEMRESTOREDHPALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemRestoredHPALittle,
    [STRINGID_ITEMALLOWSONLYYMOVE - BATTLESTRINGS_TABLE_START] = sText_ItemAllowsOnlyYMove,
    [STRINGID_PKMNHUNGONWITHX - BATTLESTRINGS_TABLE_START] = sText_PkmnHungOnWithX,
    [STRINGID_EMPTYSTRING3 - BATTLESTRINGS_TABLE_START] = gText_EmptyString3,
    [STRINGID_PKMNSXPREVENTSBURNS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsBurns,
    [STRINGID_PKMNSXBLOCKSY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXBlocksY,
    [STRINGID_PKMNSXRESTOREDHPALITTLE2 - BATTLESTRINGS_TABLE_START] = sText_PkmnsXRestoredHPALittle2,
    [STRINGID_PKMNSXWHIPPEDUPSANDSTORM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXWhippedUpSandstorm,
    [STRINGID_PKMNSXPREVENTSYLOSS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsYLoss,
    [STRINGID_PKMNSXINFATUATEDY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXInfatuatedY,
    [STRINGID_PKMNSXMADEYINEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeYIneffective,
    [STRINGID_PKMNSXCUREDYPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXCuredYProblem,
    [STRINGID_ITSUCKEDLIQUIDOOZE - BATTLESTRINGS_TABLE_START] = sText_ItSuckedLiquidOoze,
    [STRINGID_PKMNTRANSFORMED - BATTLESTRINGS_TABLE_START] = sText_PkmnTransformed,
    [STRINGID_ELECTRICITYWEAKENED - BATTLESTRINGS_TABLE_START] = sText_ElectricityWeakened,
    [STRINGID_FIREWEAKENED - BATTLESTRINGS_TABLE_START] = sText_FireWeakened,
    [STRINGID_PKMNHIDUNDERWATER - BATTLESTRINGS_TABLE_START] = sText_PkmnHidUnderwater,
    [STRINGID_PKMNSPRANGUP - BATTLESTRINGS_TABLE_START] = sText_PkmnSprangUp,
    [STRINGID_HMMOVESCANTBEFORGOTTEN - BATTLESTRINGS_TABLE_START] = sText_HMMovesCantBeForgotten,
    [STRINGID_XFOUNDONEY - BATTLESTRINGS_TABLE_START] = sText_XFoundOneY,
    [STRINGID_PLAYERDEFEATEDTRAINER1 - BATTLESTRINGS_TABLE_START] = sText_PlayerDefeatedLinkTrainerTrainer1,
    [STRINGID_SOOTHINGAROMA - BATTLESTRINGS_TABLE_START] = sText_SoothingAroma,
    [STRINGID_ITEMSCANTBEUSEDNOW - BATTLESTRINGS_TABLE_START] = sText_ItemsCantBeUsedNow,
    [STRINGID_FORXCOMMAYZ - BATTLESTRINGS_TABLE_START] = sText_ForXCommaYZ,
    [STRINGID_USINGITEMSTATOFPKMNROSE - BATTLESTRINGS_TABLE_START] = sText_UsingItemTheStatOfPkmnRose,
    [STRINGID_PKMNUSEDXTOGETPUMPED - BATTLESTRINGS_TABLE_START] = sText_PkmnUsedXToGetPumped,
    [STRINGID_PKMNSXMADEYUSELESS - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeYUseless,
    [STRINGID_PKMNTRAPPEDBYSANDTOMB - BATTLESTRINGS_TABLE_START] = sText_PkmnTrappedBySandTomb,
    [STRINGID_EMPTYSTRING4 - BATTLESTRINGS_TABLE_START] = sText_EmptyString4,
    [STRINGID_ABOOSTED - BATTLESTRINGS_TABLE_START] = sText_ABoosted,
    [STRINGID_PKMNSXINTENSIFIEDSUN - BATTLESTRINGS_TABLE_START] = sText_PkmnsXIntensifiedSun,
    [STRINGID_PKMNMAKESGROUNDMISS - BATTLESTRINGS_TABLE_START] = sText_PkmnMakesGroundMiss,
    [STRINGID_YOUTHROWABALLNOWRIGHT - BATTLESTRINGS_TABLE_START] = sText_YouThrowABallNowRight,
    [STRINGID_PKMNSXTOOKATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnsXTookAttack,
    [STRINGID_PKMNCHOSEXASDESTINY - BATTLESTRINGS_TABLE_START] = sText_PkmnChoseXAsDestiny,
    [STRINGID_PKMNLOSTFOCUS - BATTLESTRINGS_TABLE_START] = sText_PkmnLostFocus,
    [STRINGID_USENEXTPKMN - BATTLESTRINGS_TABLE_START] = sText_UseNextPkmn,
    [STRINGID_PKMNFLEDUSINGITS - BATTLESTRINGS_TABLE_START] = sText_PkmnFledUsingIts,
    [STRINGID_PKMNFLEDUSING - BATTLESTRINGS_TABLE_START] = sText_PkmnFledUsing,
    [STRINGID_PKMNWASDRAGGEDOUT - BATTLESTRINGS_TABLE_START] = sText_PkmnWasDraggedOut,
    [STRINGID_PREVENTEDFROMWORKING - BATTLESTRINGS_TABLE_START] = sText_PreventedFromWorking,
    [STRINGID_PKMNSITEMNORMALIZEDSTATUS - BATTLESTRINGS_TABLE_START] = sText_PkmnsItemNormalizedStatus,
    [STRINGID_TRAINER1USEDITEM - BATTLESTRINGS_TABLE_START] = sText_Trainer1UsedItem,
    [STRINGID_BOXISFULL - BATTLESTRINGS_TABLE_START] = sText_BoxIsFull,
    [STRINGID_PKMNAVOIDEDATTACK - BATTLESTRINGS_TABLE_START] = sText_PkmnAvoidedAttack,
    [STRINGID_PKMNSXMADEITINEFFECTIVE - BATTLESTRINGS_TABLE_START] = sText_PkmnsXMadeItIneffective,
    [STRINGID_PKMNSXPREVENTSFLINCHING - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsFlinching,
    [STRINGID_PKMNALREADYHASBURN - BATTLESTRINGS_TABLE_START] = sText_PkmnAlreadyHasBurn,
    [STRINGID_STATSWONTDECREASE2 - BATTLESTRINGS_TABLE_START] = sText_StatsWontDecrease2,
    [STRINGID_PKMNSXBLOCKSY2 - BATTLESTRINGS_TABLE_START] = sText_PkmnsXBlocksY2,
    [STRINGID_PKMNSXWOREOFF - BATTLESTRINGS_TABLE_START] = sText_PkmnsXWoreOff,
    [STRINGID_PKMNRAISEDDEFALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedDefALittle,
    [STRINGID_PKMNRAISEDSPDEFALITTLE - BATTLESTRINGS_TABLE_START] = sText_PkmnRaisedSpDefALittle,
    [STRINGID_THEWALLSHATTERED - BATTLESTRINGS_TABLE_START] = sText_TheWallShattered,
    [STRINGID_PKMNSXPREVENTSYSZ - BATTLESTRINGS_TABLE_START] = sText_PkmnsXPreventsYsZ,
    [STRINGID_PKMNSXCUREDITSYPROBLEM - BATTLESTRINGS_TABLE_START] = sText_PkmnsXCuredItsYProblem,
    [STRINGID_ATTACKERCANTESCAPE - BATTLESTRINGS_TABLE_START] = sText_AttackerCantEscape,
    [STRINGID_PKMNOBTAINEDX - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedX,
    [STRINGID_PKMNOBTAINEDX2 - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedX2,
    [STRINGID_PKMNOBTAINEDXYOBTAINEDZ - BATTLESTRINGS_TABLE_START] = sText_PkmnObtainedXYObtainedZ,
    [STRINGID_BUTNOEFFECT - BATTLESTRINGS_TABLE_START] = sText_ButNoEffect,
    [STRINGID_PKMNSXHADNOEFFECTONY - BATTLESTRINGS_TABLE_START] = sText_PkmnsXHadNoEffectOnY,
    [STRINGID_TWOENEMIESDEFEATED - BATTLESTRINGS_TABLE_START] = sText_TwoInGameTrainersDefeated,
    [STRINGID_TRAINER2LOSETEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer2LoseText,
    [STRINGID_PKMNINCAPABLEOFPOWER - BATTLESTRINGS_TABLE_START] = sText_PkmnIncapableOfPower,
    [STRINGID_GLINTAPPEARSINEYE - BATTLESTRINGS_TABLE_START] = sText_GlintAppearsInEye,
    [STRINGID_PKMNGETTINGINTOPOSITION - BATTLESTRINGS_TABLE_START] = sText_PkmnGettingIntoPosition,
    [STRINGID_PKMNBEGANGROWLINGDEEPLY - BATTLESTRINGS_TABLE_START] = sText_PkmnBeganGrowlingDeeply,
    [STRINGID_PKMNEAGERFORMORE - BATTLESTRINGS_TABLE_START] = sText_PkmnEagerForMore,
    [STRINGID_DEFEATEDOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_DefeatedOpponentByReferee,
    [STRINGID_LOSTTOOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_LostToOpponentByReferee,
    [STRINGID_TIEDOPPONENTBYREFEREE - BATTLESTRINGS_TABLE_START] = sText_TiedOpponentByReferee,
    [STRINGID_QUESTIONFORFEITMATCH - BATTLESTRINGS_TABLE_START] = sText_QuestionForfeitMatch,
    [STRINGID_FORFEITEDMATCH - BATTLESTRINGS_TABLE_START] = sText_ForfeitedMatch,
    [STRINGID_PKMNTRANSFERREDSOMEONESPC - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredSomeonesPC,
    [STRINGID_PKMNTRANSFERREDLANETTESPC - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPC,
    [STRINGID_PKMNBOXSOMEONESPCFULL - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredSomeonesPCBoxFull,
    [STRINGID_PKMNBOXLANETTESPCFULL - BATTLESTRINGS_TABLE_START] = gText_PkmnTransferredLanettesPCBoxFull,
    [STRINGID_TRAINER1WINTEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer1WinText,
    [STRINGID_TRAINER2WINTEXT - BATTLESTRINGS_TABLE_START] = sText_Trainer2WinText,
};

const u16 gMissStringIds[] =
{
    [B_MSG_MISSED]      = STRINGID_ATTACKMISSED,
    [B_MSG_PROTECTED]   = STRINGID_PKMNPROTECTEDITSELF,
    [B_MSG_AVOIDED_ATK] = STRINGID_PKMNAVOIDEDATTACK,
    [B_MSG_AVOIDED_DMG] = STRINGID_AVOIDEDDAMAGE,
    [B_MSG_GROUND_MISS] = STRINGID_PKMNMAKESGROUNDMISS
};

const u16 gNoEscapeStringIds[] =
{
    [B_MSG_CANT_ESCAPE]          = STRINGID_CANTESCAPE,
    [B_MSG_DONT_LEAVE_BIRCH]     = STRINGID_DONTLEAVEBIRCH,
    [B_MSG_PREVENTS_ESCAPE]      = STRINGID_PREVENTSESCAPE,
    [B_MSG_CANT_ESCAPE_2]        = STRINGID_CANTESCAPE2,
    [B_MSG_ATTACKER_CANT_ESCAPE] = STRINGID_ATTACKERCANTESCAPE
};

const u16 gMoveWeatherChangeStringIds[] =
{
    [B_MSG_STARTED_RAIN]      = STRINGID_STARTEDTORAIN,
    [B_MSG_STARTED_DOWNPOUR]  = STRINGID_DOWNPOURSTARTED, // Unused
    [B_MSG_WEATHER_FAILED]    = STRINGID_BUTITFAILED,
    [B_MSG_STARTED_SANDSTORM] = STRINGID_SANDSTORMBREWED,
    [B_MSG_STARTED_SUNLIGHT]  = STRINGID_SUNLIGHTGOTBRIGHT,
    [B_MSG_STARTED_HAIL]      = STRINGID_STARTEDHAIL,
};

const u16 gSandStormHailContinuesStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_SANDSTORMRAGES,
    [B_MSG_HAIL]      = STRINGID_HAILCONTINUES
};

const u16 gSandStormHailDmgStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_PKMNBUFFETEDBYSANDSTORM,
    [B_MSG_HAIL]      = STRINGID_PKMNPELTEDBYHAIL
};

const u16 gSandStormHailEndStringIds[] =
{
    [B_MSG_SANDSTORM] = STRINGID_SANDSTORMSUBSIDED,
    [B_MSG_HAIL]      = STRINGID_HAILSTOPPED
};

const u16 gRainContinuesStringIds[] =
{
    [B_MSG_RAIN_CONTINUES]     = STRINGID_RAINCONTINUES,
    [B_MSG_DOWNPOUR_CONTINUES] = STRINGID_DOWNPOURCONTINUES,
    [B_MSG_RAIN_STOPPED]       = STRINGID_RAINSTOPPED
};

const u16 gProtectLikeUsedStringIds[] =
{
    [B_MSG_PROTECTED_ITSELF] = STRINGID_PKMNPROTECTEDITSELF2,
    [B_MSG_BRACED_ITSELF]    = STRINGID_PKMNBRACEDITSELF,
    [B_MSG_PROTECT_FAILED]   = STRINGID_BUTITFAILED,
};

const u16 gReflectLightScreenSafeguardStringIds[] =
{
    [B_MSG_SIDE_STATUS_FAILED]     = STRINGID_BUTITFAILED,
    [B_MSG_SET_REFLECT_SINGLE]     = STRINGID_PKMNRAISEDDEF,
    [B_MSG_SET_REFLECT_DOUBLE]     = STRINGID_PKMNRAISEDDEFALITTLE,
    [B_MSG_SET_LIGHTSCREEN_SINGLE] = STRINGID_PKMNRAISEDSPDEF,
    [B_MSG_SET_LIGHTSCREEN_DOUBLE] = STRINGID_PKMNRAISEDSPDEFALITTLE,
    [B_MSG_SET_SAFEGUARD]          = STRINGID_PKMNCOVEREDBYVEIL,
};

const u16 gLeechSeedStringIds[] =
{
    [B_MSG_LEECH_SEED_SET]   = STRINGID_PKMNSEEDED,
    [B_MSG_LEECH_SEED_MISS]  = STRINGID_PKMNEVADEDATTACK,
    [B_MSG_LEECH_SEED_FAIL]  = STRINGID_ITDOESNTAFFECT,
    [B_MSG_LEECH_SEED_DRAIN] = STRINGID_PKMNSAPPEDBYLEECHSEED,
    [B_MSG_LEECH_SEED_OOZE]  = STRINGID_ITSUCKEDLIQUIDOOZE,
};

const u16 gRestUsedStringIds[] =
{
    [B_MSG_REST]          = STRINGID_PKMNWENTTOSLEEP,
    [B_MSG_REST_STATUSED] = STRINGID_PKMNSLEPTHEALTHY
};

const u16 gUproarOverTurnStringIds[] =
{
    [B_MSG_UPROAR_CONTINUES] = STRINGID_PKMNMAKINGUPROAR,
    [B_MSG_UPROAR_ENDS]      = STRINGID_PKMNCALMEDDOWN
};

const u16 gStockpileUsedStringIds[] =
{
    [B_MSG_STOCKPILED]     = STRINGID_PKMNSTOCKPILED,
    [B_MSG_CANT_STOCKPILE] = STRINGID_PKMNCANTSTOCKPILE,
};

const u16 gWokeUpStringIds[] =
{
    [B_MSG_WOKE_UP]        = STRINGID_PKMNWOKEUP,
    [B_MSG_WOKE_UP_UPROAR] = STRINGID_PKMNWOKEUPINUPROAR
};

const u16 gSwallowFailStringIds[] =
{
    [B_MSG_SWALLOW_FAILED]  = STRINGID_FAILEDTOSWALLOW,
    [B_MSG_SWALLOW_FULL_HP] = STRINGID_PKMNHPFULL
};

const u16 gUproarAwakeStringIds[] =
{
    [B_MSG_CANT_SLEEP_UPROAR]  = STRINGID_PKMNCANTSLEEPINUPROAR2,
    [B_MSG_UPROAR_KEPT_AWAKE]  = STRINGID_UPROARKEPTPKMNAWAKE,
    [B_MSG_STAYED_AWAKE_USING] = STRINGID_PKMNSTAYEDAWAKEUSING,
};

const u16 gStatUpStringIds[] =
{
    [B_MSG_ATTACKER_STAT_ROSE] = STRINGID_ATTACKERSSTATROSE,
    [B_MSG_DEFENDER_STAT_ROSE] = STRINGID_DEFENDERSSTATROSE,
    [B_MSG_STAT_WONT_INCREASE] = STRINGID_STATSWONTINCREASE,
    [B_MSG_STAT_ROSE_EMPTY]    = STRINGID_EMPTYSTRING3,
    [B_MSG_STAT_ROSE_ITEM]     = STRINGID_USINGITEMSTATOFPKMNROSE,
    [B_MSG_USED_DIRE_HIT]      = STRINGID_PKMNUSEDXTOGETPUMPED,
};

const u16 gStatDownStringIds[] =
{
    [B_MSG_ATTACKER_STAT_FELL] = STRINGID_ATTACKERSSTATFELL,
    [B_MSG_DEFENDER_STAT_FELL] = STRINGID_DEFENDERSSTATFELL,
    [B_MSG_STAT_WONT_DECREASE] = STRINGID_STATSWONTDECREASE,
    [B_MSG_STAT_FELL_EMPTY]    = STRINGID_EMPTYSTRING3,
};

// Index read from sTWOTURN_STRINGID
const u16 gFirstTurnOfTwoStringIds[] =
{
    [B_MSG_TURN1_RAZOR_WIND] = STRINGID_PKMNWHIPPEDWHIRLWIND,
    [B_MSG_TURN1_SOLAR_BEAM] = STRINGID_PKMNTOOKSUNLIGHT,
    [B_MSG_TURN1_SKULL_BASH] = STRINGID_PKMNLOWEREDHEAD,
    [B_MSG_TURN1_SKY_ATTACK] = STRINGID_PKMNISGLOWING,
    [B_MSG_TURN1_FLY]        = STRINGID_PKMNFLEWHIGH,
    [B_MSG_TURN1_DIG]        = STRINGID_PKMNDUGHOLE,
    [B_MSG_TURN1_DIVE]       = STRINGID_PKMNHIDUNDERWATER,
    [B_MSG_TURN1_BOUNCE]     = STRINGID_PKMNSPRANGUP,
};

// Index copied from move's index in gTrappingMoves
const u16 gWrappedStringIds[NUM_TRAPPING_MOVES] =
{
    STRINGID_PKMNSQUEEZEDBYBIND,   // MOVE_BIND
    STRINGID_PKMNWRAPPEDBY,        // MOVE_WRAP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_FIRE_SPIN
    STRINGID_PKMNCLAMPED,          // MOVE_CLAMP
    STRINGID_PKMNTRAPPEDINVORTEX,  // MOVE_WHIRLPOOL
    STRINGID_PKMNTRAPPEDBYSANDTOMB // MOVE_SAND_TOMB
};

const u16 gMistUsedStringIds[] =
{
    [B_MSG_SET_MIST]    = STRINGID_PKMNSHROUDEDINMIST,
    [B_MSG_MIST_FAILED] = STRINGID_BUTITFAILED
};

const u16 gFocusEnergyUsedStringIds[] =
{
    [B_MSG_GETTING_PUMPED]      = STRINGID_PKMNGETTINGPUMPED,
    [B_MSG_FOCUS_ENERGY_FAILED] = STRINGID_BUTITFAILED
};

const u16 gTransformUsedStringIds[] =
{
    [B_MSG_TRANSFORMED]      = STRINGID_PKMNTRANSFORMEDINTO,
    [B_MSG_TRANSFORM_FAILED] = STRINGID_BUTITFAILED
};

const u16 gSubstituteUsedStringIds[] =
{
    [B_MSG_SET_SUBSTITUTE]    = STRINGID_PKMNMADESUBSTITUTE,
    [B_MSG_SUBSTITUTE_FAILED] = STRINGID_TOOWEAKFORSUBSTITUTE
};

const u16 gGotPoisonedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPOISONED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNPOISONEDBY
};

const u16 gGotParalyzedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASPARALYZED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNWASPARALYZEDBY
};

const u16 gFellAsleepStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLASLEEP,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNMADESLEEP,
};

const u16 gGotBurnedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASBURNED,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNBURNEDBY
};

const u16 gGotFrozenStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNWASFROZEN,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNFROZENBY
};

const u16 gGotDefrostedStringIds[] =
{
    [B_MSG_DEFROSTED]         = STRINGID_PKMNWASDEFROSTED2,
    [B_MSG_DEFROSTED_BY_MOVE] = STRINGID_PKMNWASDEFROSTEDBY
};

const u16 gKOFailedStringIds[] =
{
    [B_MSG_KO_MISS]       = STRINGID_ATTACKMISSED,
    [B_MSG_KO_UNAFFECTED] = STRINGID_PKMNUNAFFECTED
};

const u16 gAttractUsedStringIds[] =
{
    [B_MSG_STATUSED]            = STRINGID_PKMNFELLINLOVE,
    [B_MSG_STATUSED_BY_ABILITY] = STRINGID_PKMNSXINFATUATEDY
};

const u16 gAbsorbDrainStringIds[] =
{
    [B_MSG_ABSORB]      = STRINGID_PKMNENERGYDRAINED,
    [B_MSG_ABSORB_OOZE] = STRINGID_ITSUCKEDLIQUIDOOZE
};

const u16 gSportsUsedStringIds[] =
{
    [B_MSG_WEAKEN_ELECTRIC] = STRINGID_ELECTRICITYWEAKENED,
    [B_MSG_WEAKEN_FIRE]     = STRINGID_FIREWEAKENED
};

const u16 gPartyStatusHealStringIds[] =
{
    [B_MSG_BELL]                     = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_ATTACKER] = STRINGID_BELLCHIMED,
    [B_MSG_BELL_SOUNDPROOF_PARTNER]  = STRINGID_BELLCHIMED,
    [B_MSG_BELL_BOTH_SOUNDPROOF]     = STRINGID_BELLCHIMED,
    [B_MSG_SOOTHING_AROMA]           = STRINGID_SOOTHINGAROMA
};

const u16 gFutureMoveUsedStringIds[] =
{
    [B_MSG_FUTURE_SIGHT] = STRINGID_PKMNFORESAWATTACK,
    [B_MSG_DOOM_DESIRE]  = STRINGID_PKMNCHOSEXASDESTINY
};

const u16 gBallEscapeStringIds[] =
{
    [BALL_NO_SHAKES]     = STRINGID_PKMNBROKEFREE,
    [BALL_1_SHAKE]       = STRINGID_ITAPPEAREDCAUGHT,
    [BALL_2_SHAKES]      = STRINGID_AARGHALMOSTHADIT,
    [BALL_3_SHAKES_FAIL] = STRINGID_SHOOTSOCLOSE
};

// Overworld weathers that don't have an associated battle weather default to "It is raining."
const u16 gWeatherStartsStringIds[] =
{
    [WEATHER_NONE]               = STRINGID_ITISRAINING,
    [WEATHER_SUNNY_CLOUDS]       = STRINGID_ITISRAINING,
    [WEATHER_SUNNY]              = STRINGID_ITISRAINING,
    [WEATHER_RAIN]               = STRINGID_ITISRAINING,
    [WEATHER_SNOW]               = STRINGID_ITISRAINING,
    [WEATHER_RAIN_THUNDERSTORM]  = STRINGID_ITISRAINING,
    [WEATHER_FOG_HORIZONTAL]     = STRINGID_ITISRAINING,
    [WEATHER_VOLCANIC_ASH]       = STRINGID_ITISRAINING,
    [WEATHER_SANDSTORM]          = STRINGID_SANDSTORMISRAGING,
    [WEATHER_FOG_DIAGONAL]       = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER]         = STRINGID_ITISRAINING,
    [WEATHER_SHADE]              = STRINGID_ITISRAINING,
    [WEATHER_DROUGHT]            = STRINGID_SUNLIGHTSTRONG,
    [WEATHER_DOWNPOUR]           = STRINGID_ITISRAINING,
    [WEATHER_UNDERWATER_BUBBLES] = STRINGID_ITISRAINING,
    [WEATHER_ABNORMAL]           = STRINGID_ITISRAINING
};

const u16 gInobedientStringIds[] =
{
    [B_MSG_LOAFING]            = STRINGID_PKMNLOAFING,
    [B_MSG_WONT_OBEY]          = STRINGID_PKMNWONTOBEY,
    [B_MSG_TURNED_AWAY]        = STRINGID_PKMNTURNEDAWAY,
    [B_MSG_PRETEND_NOT_NOTICE] = STRINGID_PKMNPRETENDNOTNOTICE,
    [B_MSG_INCAPABLE_OF_POWER] = STRINGID_PKMNINCAPABLEOFPOWER
};

const u16 gSafariGetNearStringIds[] =
{
    [B_MSG_CREPT_CLOSER]    = STRINGID_CREPTCLOSER,
    [B_MSG_CANT_GET_CLOSER] = STRINGID_CANTGETCLOSER
};

const u16 gSafariPokeblockResultStringIds[] =
{
    [B_MSG_MON_CURIOUS]    = STRINGID_PKMNCURIOUSABOUTX,
    [B_MSG_MON_ENTHRALLED] = STRINGID_PKMNENTHRALLEDBYX,
    [B_MSG_MON_IGNORED]    = STRINGID_PKMNIGNOREDX
};

const u16 gTrainerItemCuredStatusStringIds[] =
{
    [AI_HEAL_CONFUSION] = STRINGID_PKMNSITEMSNAPPEDOUT,
    [AI_HEAL_PARALYSIS] = STRINGID_PKMNSITEMCUREDPARALYSIS,
    [AI_HEAL_FREEZE]    = STRINGID_PKMNSITEMDEFROSTEDIT,
    [AI_HEAL_BURN]      = STRINGID_PKMNSITEMHEALEDBURN,
    [AI_HEAL_POISON]    = STRINGID_PKMNSITEMCUREDPOISON,
    [AI_HEAL_SLEEP]     = STRINGID_PKMNSITEMWOKEIT
};

const u16 gBerryEffectStringIds[] =
{
    [B_MSG_CURED_PROBLEM]     = STRINGID_PKMNSITEMCUREDPROBLEM,
    [B_MSG_NORMALIZED_STATUS] = STRINGID_PKMNSITEMNORMALIZEDSTATUS
};

const u16 gBRNPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNSXPREVENTSBURNS,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPRLZPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNPREVENTSPARALYSISWITH,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gPSNPreventionStringIds[] =
{
    [B_MSG_ABILITY_PREVENTS_MOVE_STATUS]    = STRINGID_PKMNPREVENTSPOISONINGWITH,
    [B_MSG_ABILITY_PREVENTS_ABILITY_STATUS] = STRINGID_PKMNSXPREVENTSYSZ,
    [B_MSG_STATUS_HAD_NO_EFFECT]            = STRINGID_PKMNSXHADNOEFFECTONY
};

const u16 gItemSwapStringIds[] =
{
    [B_MSG_ITEM_SWAP_TAKEN] = STRINGID_PKMNOBTAINEDX,
    [B_MSG_ITEM_SWAP_GIVEN] = STRINGID_PKMNOBTAINEDX2,
    [B_MSG_ITEM_SWAP_BOTH]  = STRINGID_PKMNOBTAINEDXYOBTAINEDZ
};

const u16 gFlashFireStringIds[] =
{
    [B_MSG_FLASH_FIRE_BOOST]    = STRINGID_PKMNRAISEDFIREPOWERWITH,
    [B_MSG_FLASH_FIRE_NO_BOOST] = STRINGID_PKMNSXMADEYINEFFECTIVE
};

const u16 gCaughtMonStringIds[] =
{
    [B_MSG_SENT_SOMEONES_PC]  = STRINGID_PKMNTRANSFERREDSOMEONESPC,
    [B_MSG_SENT_LANETTES_PC]  = STRINGID_PKMNTRANSFERREDLANETTESPC,
    [B_MSG_SOMEONES_BOX_FULL] = STRINGID_PKMNBOXSOMEONESPCFULL,
    [B_MSG_LANETTES_BOX_FULL] = STRINGID_PKMNBOXLANETTESPCFULL,
};

const u16 gTrappingMoves[NUM_TRAPPING_MOVES + 1] =
{
    MOVE_BIND,
    MOVE_WRAP,
    MOVE_FIRE_SPIN,
    MOVE_CLAMP,
    MOVE_WHIRLPOOL,
    MOVE_SAND_TOMB,
    0xFFFF // Never read
};

const u8 gText_PkmnIsEvolving[] = _("Ne?\n{STR_VAR_1} evrimleşiyor!");
const u8 gText_CongratsPkmnEvolved[] = _("Tebrikler! {STR_VAR_1}, bir\n{STR_VAR_2} oldu!{WAIT_SE}\p");
const u8 gText_PkmnStoppedEvolving[] = _("Ha? {STR_VAR_1}\nevrimleşmedi!\p");
const u8 gText_EllipsisQuestionMark[] = _("……?\p");
const u8 gText_WhatWillPkmnDo[] = _("{B_ACTIVE_NAME_WITH_PREFIX} ne\nyapacak?");
const u8 gText_WhatWillPkmnDo2[] = _("{B_PLAYER_NAME} ne\nyapacak?");
const u8 gText_WhatWillWallyDo[] = _("WALLY ne\nyapacak?");
const u8 gText_LinkStandby[] = _("{PAUSE 16}Link bekleniyor…");
const u8 gText_BattleMenu[] = _("SALDIR{CLEAR_TO 56}ÇANTA\nPOKéMON{CLEAR_TO 56}KAÇ");
const u8 gText_SafariZoneMenu[] = _("TOP{CLEAR_TO 56}{POKEBLOCK}\nYAKLAŞ{CLEAR_TO 56}KAÇ");
const u8 gText_MoveInterfacePP[] = _("PP ");
const u8 gText_MoveInterfaceType[] = _("TÜR/");
const u8 gText_MoveInterfacePpType[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}PP\nTÜR/");
const u8 gText_MoveInterfaceDynamicColors[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_WhichMoveToForget4[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Hangi saldırı\nunutulsun?");
const u8 gText_BattleYesNoChoice[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Evet\nHayır");
const u8 gText_BattleSwitchWhich[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}Hangisi\ndeğişsin?");
const u8 gText_BattleSwitchWhich2[] = _("{PALETTE 5}{COLOR_HIGHLIGHT_SHADOW DYNAMIC_COLOR4 DYNAMIC_COLOR5 DYNAMIC_COLOR6}");
const u8 gText_BattleSwitchWhich3[] = _("{UP_ARROW}");
const u8 gText_BattleSwitchWhich4[] = _("{ESCAPE 4}");
const u8 gText_BattleSwitchWhich5[] = _("-");

static const u8 sText_HP[] = _("CAN");
static const u8 sText_Attack[] = _("SALDIRI");
static const u8 sText_Defense[] = _("SAVUNMA");
static const u8 sText_SpAtk[] = _("ÖZ. SLD");
static const u8 sText_SpDef[] = _("ÖZ. SVN");

// Unused
static const u8 * const sStatNamesTable2[] =
{
    sText_HP, sText_SpAtk, sText_Attack,
    sText_SpDef, sText_Defense, sText_Speed
};

const u8 gText_SafariBalls[] = _("{HIGHLIGHT DARK_GRAY}SAFARİ TOPU");
const u8 gText_SafariBallLeft[] = _("{HIGHLIGHT DARK_GRAY}Kalan: $" "{HIGHLIGHT DARK_GRAY}");
const u8 gText_Sleep[] = _("uyku");
const u8 gText_Poison[] = _("zehir");
const u8 gText_Burn[] = _("yanık");
const u8 gText_Paralysis[] = _("felç");
const u8 gText_Ice[] = _("buz");
const u8 gText_Confusion[] = _("kafa karışıklığı");
const u8 gText_Love[] = _("sevda");
const u8 gText_SpaceAndSpace[] = _(" ve ");
const u8 gText_CommaSpace[] = _(", ");
const u8 gText_Space2[] = _(" ");
const u8 gText_LineBreak[] = _("\l");
const u8 gText_NewLine[] = _("\n");
const u8 gText_Are[] = _("are");
const u8 gText_Are2[] = _("are");
const u8 gText_BadEgg[] = _("Bad EGG");
const u8 gText_BattleWallyName[] = _("WALLY");
const u8 gText_Win[] = _("{HIGHLIGHT TRANSPARENT}Win");
const u8 gText_Loss[] = _("{HIGHLIGHT TRANSPARENT}Loss");
const u8 gText_Draw[] = _("{HIGHLIGHT TRANSPARENT}Draw");
static const u8 sText_SpaceIs[] = _(" is");
static const u8 sText_ApostropheS[] = _("'s");

// For displaying names of invalid moves
static const u8 sATypeMove_Table[NUMBER_OF_MON_TYPES][17] =
{
    [TYPE_NORMAL]   = _("NORMAL saldırı"),
    [TYPE_FIGHTING] = _("DÖVÜŞ saldırısı"),
    [TYPE_FLYING]   = _("UÇUŞ saldırısı"),
    [TYPE_POISON]   = _("ZEHİR sldırısı"),
    [TYPE_GROUND]   = _("YER saldırısı"),
    [TYPE_ROCK]     = _("KAYA saldırısı"),
    [TYPE_BUG]      = _("BÖCEK sldırısı"),
    [TYPE_GHOST]    = _("HAYALET sldrsı"),
    [TYPE_STEEL]    = _("ÇELİK saldırısı"),
    [TYPE_MYSTERY]  = _("??? saldırısı"),
    [TYPE_FIRE]     = _("ATEŞ saldırısı"),
    [TYPE_WATER]    = _("SU saldırısı"),
    [TYPE_GRASS]    = _("ÇİMEN sldırısı"),
    [TYPE_ELECTRIC] = _("ELKTRK sldrısı"),
    [TYPE_PSYCHIC]  = _("PSİŞİK sldırısı"),
    [TYPE_ICE]      = _("BUZ saldırısı"),
    [TYPE_DRAGON]   = _("EJDER saldırısı"),
    [TYPE_DARK]     = _("KARA sldırısı")
};

const u8 gText_BattleTourney[] = _("TURNUVA");
static const u8 sText_Round1[] = _("Tur 1");
static const u8 sText_Round2[] = _("Tur 2");
static const u8 sText_Semifinal[] = _("Yarı Final");
static const u8 sText_Final[] = _("Final");

const u8 *const gRoundsStringTable[DOME_ROUNDS_COUNT] =
{
    [DOME_ROUND1]    = sText_Round1,
    [DOME_ROUND2]    = sText_Round2,
    [DOME_SEMIFINAL] = sText_Semifinal,
    [DOME_FINAL]     = sText_Final
};

const u8 gText_TheGreatNewHope[] = _("Yeni umut!\p");
const u8 gText_WillChampionshipDreamComeTrue[] = _("Şampiyonluk hayali gerçekleşecek mi?!\p");
const u8 gText_AFormerChampion[] = _("Eski ŞAMPİYON!\p");
const u8 gText_ThePreviousChampion[] = _("Önceki ŞAMPİYON!\p");
const u8 gText_TheUnbeatenChampion[] = _("Yenilmez ŞAMPİYON!\p");
const u8 gText_PlayerMon1Name[] = _("{B_PLAYER_MON1_NAME}");
const u8 gText_Vs[] = _("VS");
const u8 gText_OpponentMon1Name[] = _("{B_OPPONENT_MON1_NAME}");
const u8 gText_Mind[] = _("Akıl");
const u8 gText_Skill[] = _("Yetenek");
const u8 gText_Body[] = _("Beden");
const u8 gText_Judgment[] = _("{B_BUFF1}{CLEAR 13}Yargı{CLEAR 13}{B_BUFF2}");
static const u8 sText_TwoTrainersSentPkmn[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME},\n{B_OPPONENT_MON1_NAME} gönderdi!\p{B_TRAINER2_CLASS} {B_TRAINER2_NAME},\n{B_OPPONENT_MON2_NAME} gönderdi!");
static const u8 sText_Trainer2SentOutPkmn[] = _("{B_TRAINER2_CLASS} {B_TRAINER2_NAME}\n{B_BUFF1} gönderdi!");
static const u8 sText_TwoTrainersWantToBattle[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME} ve\n{B_TRAINER2_CLASS} {B_TRAINER2_NAME}\lsavaşmak istiyor!\p");
static const u8 sText_InGamePartnerSentOutZGoN[] = _("{B_PARTNER_CLASS} {B_PARTNER_NAME}\n{B_PLAYER_MON2_NAME} gönderdi!\lGit, {B_PLAYER_MON1_NAME}!");
static const u8 sText_TwoInGameTrainersDefeated[] = _("{B_TRAINER1_CLASS} {B_TRAINER1_NAME} ve\n{B_TRAINER2_CLASS} {B_TRAINER2_NAME}\lyenildi!\p");
static const u8 sText_Trainer2LoseText[] = _("{B_TRAINER2_LOSE_TEXT}");
static const u8 sText_PkmnIncapableOfPower[] = _("{B_ATK_NAME_WITH_PREFIX} gücünü kullanamıyor\ngibi görünüyor!");
static const u8 sText_GlintAppearsInEye[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX}'ın gözünde bir\nparıltı belirdi!");
static const u8 sText_PkmnGettingIntoPosition[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} konumuna geçiyor!");
static const u8 sText_PkmnBeganGrowlingDeeply[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} derince uluyor!");
static const u8 sText_PkmnEagerForMore[] = _("{B_SCR_ACTIVE_NAME_WITH_PREFIX} dahası için hevesli!");

const u16 gBattlePalaceFlavorTextTable[] =
{
    [B_MSG_GLINT_IN_EYE]   = STRINGID_GLINTAPPEARSINEYE,
    [B_MSG_GETTING_IN_POS] = STRINGID_PKMNGETTINGINTOPOSITION,
    [B_MSG_GROWL_DEEPLY]   = STRINGID_PKMNBEGANGROWLINGDEEPLY,
    [B_MSG_EAGER_FOR_MORE] = STRINGID_PKMNEAGERFORMORE,
};

static const u8 sText_RefIfNothingIsDecided[] = _("REFEREE: If nothing is decided in\n3 turns, we will go to judging!");
static const u8 sText_RefThatsIt[] = _("REFEREE: That's it! We will now go to\njudging to determine the winner!");
static const u8 sText_RefJudgeMind[] = _("REFEREE: Judging category 1, Mind!\nThe POKéMON showing the most guts!\p");
static const u8 sText_RefJudgeSkill[] = _("REFEREE: Judging category 2, Skill!\nThe POKéMON using moves the best!\p");
static const u8 sText_RefJudgeBody[] = _("REFEREE: Judging category 3, Body!\nThe POKéMON with the most vitality!\p");
static const u8 sText_RefPlayerWon[] = _("REFEREE: Judgment: {B_BUFF1} to {B_BUFF2}!\nThe winner is {B_PLAYER_NAME}'s {B_PLAYER_MON1_NAME}!\p");
static const u8 sText_RefOpponentWon[] = _("REFEREE: Judgment: {B_BUFF1} to {B_BUFF2}!\nThe winner is {B_TRAINER1_NAME}'s {B_OPPONENT_MON1_NAME}!\p");
static const u8 sText_RefDraw[] = _("REFEREE: Judgment: 3 to 3!\nWe have a draw!\p");
static const u8 sText_DefeatedOpponentByReferee[] = _("{B_PLAYER_MON1_NAME} defeated the opponent\n{B_OPPONENT_MON1_NAME} in a REFEREE's decision!");
static const u8 sText_LostToOpponentByReferee[] = _("{B_PLAYER_MON1_NAME} lost to the opponent\n{B_OPPONENT_MON1_NAME} in a REFEREE's decision!");
static const u8 sText_TiedOpponentByReferee[] = _("{B_PLAYER_MON1_NAME} tied the opponent\n{B_OPPONENT_MON1_NAME} in a REFEREE's decision!");
static const u8 sText_RefCommenceBattle[] = _("REFEREE: {B_PLAYER_MON1_NAME} VS {B_OPPONENT_MON1_NAME}!\nCommence battling!");

const u8 * const gRefereeStringsTable[] =
{
    [B_MSG_REF_NOTHING_IS_DECIDED] = sText_RefIfNothingIsDecided,
    [B_MSG_REF_THATS_IT]           = sText_RefThatsIt,
    [B_MSG_REF_JUDGE_MIND]         = sText_RefJudgeMind,
    [B_MSG_REF_JUDGE_SKILL]        = sText_RefJudgeSkill,
    [B_MSG_REF_JUDGE_BODY]         = sText_RefJudgeBody,
    [B_MSG_REF_PLAYER_WON]         = sText_RefPlayerWon,
    [B_MSG_REF_OPPONENT_WON]       = sText_RefOpponentWon,
    [B_MSG_REF_DRAW]               = sText_RefDraw,
    [B_MSG_REF_COMMENCE_BATTLE]    = sText_RefCommenceBattle,
};

static const u8 sText_QuestionForfeitMatch[] = _("Maçtan çekilip çıkmak ister\nmisin?");
static const u8 sText_ForfeitedMatch[] = _("{B_PLAYER_NAME} maçtan çekildi!");
static const u8 sText_Trainer1WinText[] = _("{B_TRAINER1_WIN_TEXT}");
static const u8 sText_Trainer2WinText[] = _("{B_TRAINER2_WIN_TEXT}");
static const u8 sText_Trainer1Fled[] = _( "{PLAY_SE SE_FLEE}{B_TRAINER1_CLASS} {B_TRAINER1_NAME} kaçtı!");
static const u8 sText_PlayerLostAgainstTrainer1[] = _("Oyuncu, {B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nkarşısında kaybetti!");
static const u8 sText_PlayerBattledToDrawTrainer1[] = _("Oyuncu, {B_TRAINER1_CLASS} {B_TRAINER1_NAME}\nile berabere kaldı!");
const u8 gText_RecordBattleToPass[] = _("Son savaşını SINIR BİLETİ'ne\nkaydetmek ister misin?");
const u8 gText_BattleRecordedOnPass[] = _("{B_PLAYER_NAME}'ın savaş sonucu\nSINIR BİLETİ'ne yazıldı.");
static const u8 sText_LinkTrainerWantsToBattlePause[] = _("{B_LINK_OPPONENT1_NAME}\nsavaşmak istiyor!{PAUSE 49}");
static const u8 sText_TwoLinkTrainersWantToBattlePause[] = _("{B_LINK_OPPONENT1_NAME} ve {B_LINK_OPPONENT2_NAME}\nsavaşmak istiyor!{PAUSE 49}");

// This is four lists of moves which use a different attack string in Japanese
// to the default. See the documentation for ChooseTypeOfMoveUsedString for more detail.
static const u16 sGrammarMoveUsedTable[] =
{
    MOVE_SWORDS_DANCE, MOVE_STRENGTH, MOVE_GROWTH,
    MOVE_HARDEN, MOVE_MINIMIZE, MOVE_SMOKESCREEN,
    MOVE_WITHDRAW, MOVE_DEFENSE_CURL, MOVE_EGG_BOMB,
    MOVE_SMOG, MOVE_BONE_CLUB, MOVE_FLASH, MOVE_SPLASH,
    MOVE_ACID_ARMOR, MOVE_BONEMERANG, MOVE_REST, MOVE_SHARPEN,
    MOVE_SUBSTITUTE, MOVE_MIND_READER, MOVE_SNORE,
    MOVE_PROTECT, MOVE_SPIKES, MOVE_ENDURE, MOVE_ROLLOUT,
    MOVE_SWAGGER, MOVE_SLEEP_TALK, MOVE_HIDDEN_POWER,
    MOVE_PSYCH_UP, MOVE_EXTREME_SPEED, MOVE_FOLLOW_ME,
    MOVE_TRICK, MOVE_ASSIST, MOVE_INGRAIN, MOVE_KNOCK_OFF,
    MOVE_CAMOUFLAGE, MOVE_ASTONISH, MOVE_ODOR_SLEUTH,
    MOVE_GRASS_WHISTLE, MOVE_SHEER_COLD, MOVE_MUDDY_WATER,
    MOVE_IRON_DEFENSE, MOVE_BOUNCE, 0,

    MOVE_TELEPORT, MOVE_RECOVER, MOVE_BIDE, MOVE_AMNESIA,
    MOVE_FLAIL, MOVE_TAUNT, MOVE_BULK_UP, 0,

    MOVE_MEDITATE, MOVE_AGILITY, MOVE_MIMIC, MOVE_DOUBLE_TEAM,
    MOVE_BARRAGE, MOVE_TRANSFORM, MOVE_STRUGGLE, MOVE_SCARY_FACE,
    MOVE_CHARGE, MOVE_WISH, MOVE_BRICK_BREAK, MOVE_YAWN,
    MOVE_FEATHER_DANCE, MOVE_TEETER_DANCE, MOVE_MUD_SPORT,
    MOVE_FAKE_TEARS, MOVE_WATER_SPORT, MOVE_CALM_MIND, 0,

    MOVE_POUND, MOVE_SCRATCH, MOVE_VICE_GRIP,
    MOVE_WING_ATTACK, MOVE_FLY, MOVE_BIND, MOVE_SLAM,
    MOVE_HORN_ATTACK, MOVE_WRAP, MOVE_THRASH, MOVE_TAIL_WHIP,
    MOVE_LEER, MOVE_BITE, MOVE_GROWL, MOVE_ROAR,
    MOVE_SING, MOVE_PECK, MOVE_ABSORB, MOVE_STRING_SHOT,
    MOVE_EARTHQUAKE, MOVE_FISSURE, MOVE_DIG, MOVE_TOXIC,
    MOVE_SCREECH, MOVE_METRONOME, MOVE_LICK, MOVE_CLAMP,
    MOVE_CONSTRICT, MOVE_POISON_GAS, MOVE_BUBBLE,
    MOVE_SLASH, MOVE_SPIDER_WEB, MOVE_NIGHTMARE, MOVE_CURSE,
    MOVE_FORESIGHT, MOVE_CHARM, MOVE_ATTRACT, MOVE_ROCK_SMASH,
    MOVE_UPROAR, MOVE_SPIT_UP, MOVE_SWALLOW, MOVE_TORMENT,
    MOVE_FLATTER, MOVE_ROLE_PLAY, MOVE_ENDEAVOR, MOVE_TICKLE,
    MOVE_COVET, 0
};

static const u8 sDummyWeirdStatusString[] = {EOS, EOS, EOS, EOS, EOS, EOS, EOS, EOS, 0, 0};

static const struct BattleWindowText sTextOnWindowsInfo_Normal[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [B_WIN_VS_PLAYER] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OPPONENT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_MULTI_PLAYER_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_VS_OUTCOME_DRAW] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_LEFT] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
    [B_WIN_VS_OUTCOME_RIGHT] = {
        .fillValue = PIXEL_FILL(0x0),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 6,
    },
};

static const struct BattleWindowText sTextOnWindowsInfo_Arena[] =
{
    [B_WIN_MSG] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_PROMPT] = {
        .fillValue = PIXEL_FILL(0xF),
        .fontId = FONT_NORMAL,
        .x = 1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 15,
        .shadowColor = 6,
    },
    [B_WIN_ACTION_MENU] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_1] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_2] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_3] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_MOVE_NAME_4] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_DUMMY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_PP_REMAINING] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 2,
        .y = 1,
        .speed = 0,
        .fgColor = 12,
        .bgColor = 14,
        .shadowColor = 11,
    },
    [B_WIN_MOVE_TYPE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_SWITCH_PROMPT] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NARROW,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_YESNO] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BOX] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [B_WIN_LEVEL_UP_BANNER] = {
        .fillValue = PIXEL_FILL(0),
        .fontId = FONT_NORMAL,
        .x = 32,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .shadowColor = 2,
    },
    [ARENA_WIN_PLAYER_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 1,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_VS] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_OPPONENT_NAME] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_MIND] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_SKILL] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_BODY] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TITLE] = {
        .fillValue = PIXEL_FILL(0xE),
        .fontId = FONT_NORMAL,
        .x = -1,
        .y = 1,
        .speed = 0,
        .fgColor = 13,
        .bgColor = 14,
        .shadowColor = 15,
    },
    [ARENA_WIN_JUDGMENT_TEXT] = {
        .fillValue = PIXEL_FILL(0x1),
        .fontId = FONT_NORMAL,
        .x = 0,
        .y = 1,
        .speed = 1,
        .fgColor = 2,
        .bgColor = 1,
        .shadowColor = 3,
    },
};

static const struct BattleWindowText *const sBattleTextOnWindowsInfo[] =
{
    [B_WIN_TYPE_NORMAL] = sTextOnWindowsInfo_Normal,
    [B_WIN_TYPE_ARENA]  = sTextOnWindowsInfo_Arena
};

static const u8 sRecordedBattleTextSpeeds[] = {8, 4, 1, 0};

void BufferStringBattle(u16 stringID)
{
    s32 i;
    const u8 *stringPtr = NULL;

    gBattleMsgDataPtr = (struct BattleMsgData *)(&gBattleBufferA[gActiveBattler][4]);
    gLastUsedItem = gBattleMsgDataPtr->lastItem;
    gLastUsedAbility = gBattleMsgDataPtr->lastAbility;
    gBattleScripting.battler = gBattleMsgDataPtr->scrActive;
    *(&gBattleStruct->scriptPartyIdx) = gBattleMsgDataPtr->bakScriptPartyIdx;
    *(&gBattleStruct->hpScale) = gBattleMsgDataPtr->hpScale;
    gPotentialItemEffectBattler = gBattleMsgDataPtr->itemEffectBattler;
    *(&gBattleStruct->stringMoveType) = gBattleMsgDataPtr->moveType;

    for (i = 0; i < MAX_BATTLERS_COUNT; i++)
    {
        sBattlerAbilities[i] = gBattleMsgDataPtr->abilities[i];
    }
    for (i = 0; i < TEXT_BUFF_ARRAY_COUNT; i++)
    {
        gBattleTextBuff1[i] = gBattleMsgDataPtr->textBuffs[0][i];
        gBattleTextBuff2[i] = gBattleMsgDataPtr->textBuffs[1][i];
        gBattleTextBuff3[i] = gBattleMsgDataPtr->textBuffs[2][i];
    }

    switch (stringID)
    {
    case STRINGID_INTROMSG: // first battle msg
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    stringPtr = sText_TwoTrainersWantToBattle;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_TwoLinkTrainersWantToBattlePause;
                    else
                        stringPtr = sText_TwoLinkTrainersWantToBattle;
                }
                else
                {
                    if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1WantsToBattle;
                    else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                        stringPtr = sText_LinkTrainerWantsToBattlePause;
                    else
                        stringPtr = sText_LinkTrainerWantsToBattle;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersWantToBattle;
                else
                    stringPtr = sText_Trainer1WantsToBattle;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
                stringPtr = sText_LegendaryPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE) // interesting, looks like they had something planned for wild double battles
                stringPtr = sText_TwoWildPkmnAppeared;
            else if (gBattleTypeFlags & BATTLE_TYPE_WALLY_TUTORIAL)
                stringPtr = sText_WildPkmnAppearedPause;
            else
                stringPtr = sText_WildPkmnAppeared;
        }
        break;
    case STRINGID_INTROSENDOUT: // poke first send-out
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
                    stringPtr = sText_InGamePartnerSentOutZGoN;
                else if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_GoTwoPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkPartnerSentOutPkmnGoPkmn;
                else
                    stringPtr = sText_GoTwoPkmn;
            }
            else
            {
                stringPtr = sText_GoPkmn;
            }
        }
        else
        {
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                    stringPtr = sText_TwoTrainersSentPkmn;
                else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_TwoLinkTrainersSentOutPkmn;
                else if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                    stringPtr = sText_LinkTrainerSentOutTwoPkmn;
                else
                    stringPtr = sText_Trainer1SentOutTwoPkmn;
            }
            else
            {
                if (!(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK)))
                    stringPtr = sText_Trainer1SentOutPkmn;
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    stringPtr = sText_Trainer1SentOutPkmn;
                else
                    stringPtr = sText_LinkTrainerSentOutPkmn;
            }
        }
        break;
    case STRINGID_RETURNMON: // sending poke to ball msg
        if (GetBattlerSide(gActiveBattler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0)
                stringPtr = sText_PkmnThatsEnough;
            else if (*(&gBattleStruct->hpScale) == 1 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_PkmnComeBack;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_PkmnOkComeBack;
            else
                stringPtr = sText_PkmnGoodComeBack;
        }
        else
        {
            if (gTrainerBattleOpponent_A == TRAINER_LINK_OPPONENT || gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
            {
                if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                    stringPtr = sText_LinkTrainer2WithdrewPkmn;
                else
                    stringPtr = sText_LinkTrainer1WithdrewPkmn;
            }
            else
            {
                stringPtr = sText_Trainer1WithdrewPkmn;
            }
        }
        break;
    case STRINGID_SWITCHINMON: // switch-in msg
        if (GetBattlerSide(gBattleScripting.battler) == B_SIDE_PLAYER)
        {
            if (*(&gBattleStruct->hpScale) == 0 || gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                stringPtr = sText_GoPkmn2;
            else if (*(&gBattleStruct->hpScale) == 1)
                stringPtr = sText_DoItPkmn;
            else if (*(&gBattleStruct->hpScale) == 2)
                stringPtr = sText_GoForItPkmn;
            else
                stringPtr = sText_YourFoesWeakGetEmPkmn;
        }
        else
        {
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                        stringPtr = sText_LinkTrainerMultiSentOutPkmn;
                    else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_LinkTrainerSentOutPkmn2;
                }
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TWO_OPPONENTS)
                {
                    if (gBattleScripting.battler == 1)
                        stringPtr = sText_Trainer1SentOutPkmn2;
                    else
                        stringPtr = sText_Trainer2SentOutPkmn;
                }
                else
                {
                    stringPtr = sText_Trainer1SentOutPkmn2;
                }
            }
        }
        break;
    case STRINGID_USEDMOVE: // pokemon used a move msg
        ChooseMoveUsedParticle(gBattleTextBuff1); // buff1 doesn't appear in the string, leftover from japanese move names

        if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
            StringCopy(gBattleTextBuff2, sATypeMove_Table[*(&gBattleStruct->stringMoveType)]);
        else
            StringCopy(gBattleTextBuff2, gMoveNames[gBattleMsgDataPtr->currentMove]);

        ChooseTypeOfMoveUsedString(gBattleTextBuff2);
        stringPtr = sText_AttackerUsedX;
        break;
    case STRINGID_BATTLEEND: // battle end
        if (gBattleTextBuff1[0] & B_OUTCOME_LINK_BATTLE_RAN)
        {
            gBattleTextBuff1[0] &= ~(B_OUTCOME_LINK_BATTLE_RAN);
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTextBuff1[0] == B_OUTCOME_LOST || gBattleTextBuff1[0] == B_OUTCOME_DREW)
                stringPtr = sText_GotAwaySafely;
            else if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
                stringPtr = sText_TwoWildFled;
            else
                stringPtr = sText_WildFled;
        }
        else
        {
            if (GetBattlerSide(gActiveBattler) == B_SIDE_OPPONENT && gBattleTextBuff1[0] != B_OUTCOME_DREW)
                gBattleTextBuff1[0] ^= (B_OUTCOME_LOST | B_OUTCOME_WON);

            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    if (gBattleTypeFlags & BATTLE_TYPE_TOWER_LINK_MULTI)
                        stringPtr = sText_TwoInGameTrainersDefeated;
                    else
                        stringPtr = sText_TwoLinkTrainersDefeated;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostToTwo;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawVsTwo;
                    break;
                }
            }
            else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainerTrainer1;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstTrainer1;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawTrainer1;
                    break;
                }
            }
            else
            {
                switch (gBattleTextBuff1[0])
                {
                case B_OUTCOME_WON:
                    stringPtr = sText_PlayerDefeatedLinkTrainer;
                    break;
                case B_OUTCOME_LOST:
                    stringPtr = sText_PlayerLostAgainstLinkTrainer;
                    break;
                case B_OUTCOME_DREW:
                    stringPtr = sText_PlayerBattledToDrawLinkTrainer;
                    break;
                }
            }
        }
        break;
    default: // load a string from the table
        if (stringID >= BATTLESTRINGS_COUNT)
        {
            gDisplayedStringBattle[0] = EOS;
            return;
        }
        else
        {
            stringPtr = gBattleStringsTable[stringID - BATTLESTRINGS_TABLE_START];
        }
        break;
    }

    BattleStringExpandPlaceholdersToDisplayedString(stringPtr);
}

u32 BattleStringExpandPlaceholdersToDisplayedString(const u8 *src)
{
    BattleStringExpandPlaceholders(src, gDisplayedStringBattle);
}

static const u8 *TryGetStatusString(u8 *src)
{
    u32 i;
    u8 status[8];
    u32 chars1, chars2;
    u8 *statusPtr;

    memcpy(status, sDummyWeirdStatusString, 8);

    statusPtr = status;
    for (i = 0; i < 8; i++)
    {
        if (*src == EOS) break; // one line required to match -g
        *statusPtr = *src;
        src++;
        statusPtr++;
    }

    chars1 = *(u32 *)(&status[0]);
    chars2 = *(u32 *)(&status[4]);

    for (i = 0; i < ARRAY_COUNT(gStatusConditionStringsTable); i++)
    {
        if (chars1 == *(u32 *)(&gStatusConditionStringsTable[i][0][0])
            && chars2 == *(u32 *)(&gStatusConditionStringsTable[i][0][4]))
            return gStatusConditionStringsTable[i][1];
    }
    return NULL;
}

#define HANDLE_NICKNAME_STRING_CASE(battlerId, monIndex)                \
    if (GetBattlerSide(battlerId) != B_SIDE_PLAYER)                     \
    {                                                                   \
        if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)                     \
            toCpy = sText_FoePkmnPrefix;                                \
        else                                                            \
            toCpy = sText_WildPkmnPrefix;                               \
        while (*toCpy != EOS)                                           \
        {                                                               \
            dst[dstID] = *toCpy;                                        \
            dstID++;                                                    \
            toCpy++;                                                    \
        }                                                               \
        GetMonData(&gEnemyParty[monIndex], MON_DATA_NICKNAME, text);    \
    }                                                                   \
    else                                                                \
    {                                                                   \
        GetMonData(&gPlayerParty[monIndex], MON_DATA_NICKNAME, text);   \
    }                                                                   \
    StringGet_Nickname(text);                                           \
    toCpy = text;

u32 BattleStringExpandPlaceholders(const u8 *src, u8 *dst)
{
    u32 dstID = 0; // if they used dstID, why not use srcID as well?
    const u8 *toCpy = NULL;
    u8 text[30];
    u8 multiplayerId;
    s32 i;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        multiplayerId = gRecordedBattleMultiplayerId;
    else
        multiplayerId = GetMultiplayerId();

    while (*src != EOS)
    {
        if (*src == PLACEHOLDER_BEGIN)
        {
            src++;
            switch (*src)
            {
            case B_TXT_BUFF1:
                if (gBattleTextBuff1[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff1, gStringVar1);
                    toCpy = gStringVar1;
                }
                else
                {
                    toCpy = TryGetStatusString(gBattleTextBuff1);
                    if (toCpy == NULL)
                        toCpy = gBattleTextBuff1;
                }
                break;
            case B_TXT_BUFF2:
                if (gBattleTextBuff2[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff2, gStringVar2);
                    toCpy = gStringVar2;
                }
                else
                    toCpy = gBattleTextBuff2;
                break;
            case B_TXT_BUFF3:
                if (gBattleTextBuff3[0] == B_BUFF_PLACEHOLDER_BEGIN)
                {
                    ExpandBattleTextBuffPlaceholders(gBattleTextBuff3, gStringVar3);
                    toCpy = gStringVar3;
                }
                else
                    toCpy = gBattleTextBuff3;
                break;
            case B_TXT_COPY_VAR_1:
                toCpy = gStringVar1;
                break;
            case B_TXT_COPY_VAR_2:
                toCpy = gStringVar2;
                break;
            case B_TXT_COPY_VAR_3:
                toCpy = gStringVar3;
                break;
            case B_TXT_PLAYER_MON1_NAME: // first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON1_NAME: // first enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_PLAYER_MON2_NAME: // second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_OPPONENT_MON2_NAME: // second enemy poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT)]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON1_NAME: // link first player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON1_NAME: // link first opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 1]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_PLAYER_MON2_NAME: // link second player poke name
                GetMonData(&gPlayerParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 2]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_LINK_OPPONENT_MON2_NAME: // link second opponent poke name
                GetMonData(&gEnemyParty[gBattlerPartyIndexes[gLinkPlayers[multiplayerId].id ^ 3]],
                           MON_DATA_NICKNAME, text);
                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX_MON1: // attacker name with prefix, only battlerId 0/1
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker,
                                            gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker))])
                break;
            case B_TXT_ATK_PARTNER_NAME: // attacker partner name
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    GetMonData(&gPlayerParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);
                else
                    GetMonData(&gEnemyParty[gBattlerPartyIndexes[GetBattlerAtPosition(GET_BATTLER_SIDE(gBattlerAttacker)) + 2]], MON_DATA_NICKNAME, text);

                StringGet_Nickname(text);
                toCpy = text;
                break;
            case B_TXT_ATK_NAME_WITH_PREFIX: // attacker name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerAttacker, gBattlerPartyIndexes[gBattlerAttacker])
                break;
            case B_TXT_DEF_NAME_WITH_PREFIX: // target name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattlerTarget, gBattlerPartyIndexes[gBattlerTarget])
                break;
            case B_TXT_EFF_NAME_WITH_PREFIX: // effect battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gEffectBattler, gBattlerPartyIndexes[gEffectBattler])
                break;
            case B_TXT_ACTIVE_NAME_WITH_PREFIX: // active battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gActiveBattler, gBattlerPartyIndexes[gActiveBattler])
                break;
            case B_TXT_SCR_ACTIVE_NAME_WITH_PREFIX: // scripting active battlerId name with prefix
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, gBattlerPartyIndexes[gBattleScripting.battler])
                break;
            case B_TXT_CURRENT_MOVE: // current move name
                if (gBattleMsgDataPtr->currentMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->currentMove];
                break;
            case B_TXT_LAST_MOVE: // originally used move name
                if (gBattleMsgDataPtr->originallyUsedMove >= MOVES_COUNT)
                    toCpy = sATypeMove_Table[gBattleStruct->stringMoveType];
                else
                    toCpy = gMoveNames[gBattleMsgDataPtr->originallyUsedMove];
                break;
            case B_TXT_LAST_ITEM: // last used item
                if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
                {
                    if (gLastUsedItem == ITEM_ENIGMA_BERRY)
                    {
                        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
                        {
                            if ((gBattleScripting.multiplayerId != 0 && (gPotentialItemEffectBattler & BIT_SIDE))
                                || (gBattleScripting.multiplayerId == 0 && !(gPotentialItemEffectBattler & BIT_SIDE)))
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                            {
                                toCpy = sText_EnigmaBerry;
                            }
                        }
                        else
                        {
                            if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                            {
                                StringCopy(text, gEnigmaBerries[gPotentialItemEffectBattler].name);
                                StringAppend(text, sText_BerrySuffix);
                                toCpy = text;
                            }
                            else
                                toCpy = sText_EnigmaBerry;
                        }
                    }
                    else
                    {
                        CopyItemName(gLastUsedItem, text);
                        toCpy = text;
                    }
                }
                else
                {
                    CopyItemName(gLastUsedItem, text);
                    toCpy = text;
                }
                break;
            case B_TXT_LAST_ABILITY: // last used ability
                toCpy = gAbilityNames[gLastUsedAbility];
                break;
            case B_TXT_ATK_ABILITY: // attacker ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerAttacker]];
                break;
            case B_TXT_DEF_ABILITY: // target ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattlerTarget]];
                break;
            case B_TXT_SCR_ACTIVE_ABILITY: // scripting active ability
                toCpy = gAbilityNames[sBattlerAbilities[gBattleScripting.battler]];
                break;
            case B_TXT_EFF_ABILITY: // effect battlerId ability
                toCpy = gAbilityNames[sBattlerAbilities[gEffectBattler]];
                break;
            case B_TXT_TRAINER1_CLASS: // trainer class name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                    toCpy = gTrainerClassNames[GetSecretBaseTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                    toCpy = gTrainerClassNames[GetUnionRoomTrainerClass()];
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                    toCpy = gTrainerClassNames[GetFrontierBrainTrainerClass()];
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_A)];
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                    toCpy = gTrainerClassNames[GetEreaderTrainerClassId()];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_A].trainerClass];
                break;
            case B_TXT_TRAINER1_NAME: // trainer1 name
                if (gBattleTypeFlags & BATTLE_TYPE_SECRET_BASE)
                {
                    for (i = 0; i < (s32) ARRAY_COUNT(gBattleResources->secretBase->trainerName); i++)
                        text[i] = gBattleResources->secretBase->trainerName[i];
                    text[i] = EOS;
                    ConvertInternationalString(text, gBattleResources->secretBase->language);
                    toCpy = text;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_UNION_ROOM)
                {
                    toCpy = gLinkPlayers[multiplayerId ^ BIT_SIDE].name;
                }
                else if (gTrainerBattleOpponent_A == TRAINER_FRONTIER_BRAIN)
                {
                    CopyFrontierBrainTrainerName(text);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_A);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_EREADER_TRAINER)
                {
                    GetEreaderTrainerName(text);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_A].trainerName;
                }
                break;
            case B_TXT_LINK_PLAYER_NAME: // link player name
                toCpy = gLinkPlayers[multiplayerId].name;
                break;
            case B_TXT_LINK_PARTNER_NAME: // link partner name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT1_NAME: // link opponent 1 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id))].name;
                break;
            case B_TXT_LINK_OPPONENT2_NAME: // link opponent 2 name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(BATTLE_PARTNER(BATTLE_OPPOSITE(gLinkPlayers[multiplayerId].id)))].name;
                break;
            case B_TXT_LINK_SCR_TRAINER_NAME: // link scripting active name
                toCpy = gLinkPlayers[GetBattlerMultiplayerId(gBattleScripting.battler)].name;
                break;
            case B_TXT_PLAYER_NAME: // player name
                if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
                    toCpy = gLinkPlayers[0].name;
                else
                    toCpy = gSaveBlock2Ptr->playerName;
                break;
            case B_TXT_TRAINER1_LOSE_TEXT: // trainerA lose text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerALoseText();
                }
                break;
            case B_TXT_TRAINER1_WIN_TEXT: // trainerA win text
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_A);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_26: // ?
                HANDLE_NICKNAME_STRING_CASE(gBattleScripting.battler, *(&gBattleStruct->scriptPartyIdx))
                break;
            case B_TXT_PC_CREATOR_NAME: // lanette pc
                if (FlagGet(FLAG_SYS_PC_LANETTE))
                    toCpy = sText_Lanettes;
                else
                    toCpy = sText_Someones;
                break;
            case B_TXT_ATK_PREFIX2:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_DEF_PREFIX2:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix2;
                else
                    toCpy = sText_FoePkmnPrefix3;
                break;
            case B_TXT_ATK_PREFIX1:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_DEF_PREFIX1:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix;
                else
                    toCpy = sText_FoePkmnPrefix2;
                break;
            case B_TXT_ATK_PREFIX3:
                if (GetBattlerSide(gBattlerAttacker) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_DEF_PREFIX3:
                if (GetBattlerSide(gBattlerTarget) == B_SIDE_PLAYER)
                    toCpy = sText_AllyPkmnPrefix3;
                else
                    toCpy = sText_FoePkmnPrefix4;
                break;
            case B_TXT_TRAINER2_CLASS:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                    toCpy = gTrainerClassNames[GetFrontierOpponentClass(gTrainerBattleOpponent_B)];
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                    toCpy = gTrainerClassNames[GetTrainerHillOpponentClass(gTrainerBattleOpponent_B)];
                else
                    toCpy = gTrainerClassNames[gTrainers[gTrainerBattleOpponent_B].trainerClass];
                break;
            case B_TXT_TRAINER2_NAME:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    GetFrontierTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    GetTrainerHillTrainerName(text, gTrainerBattleOpponent_B);
                    toCpy = text;
                }
                else
                {
                    toCpy = gTrainers[gTrainerBattleOpponent_B].trainerName;
                }
                break;
            case B_TXT_TRAINER2_LOSE_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_WON_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_WON, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else
                {
                    toCpy = GetTrainerBLoseText();
                }
                break;
            case B_TXT_TRAINER2_WIN_TEXT:
                if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                {
                    CopyFrontierTrainerText(FRONTIER_PLAYER_LOST_TEXT, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
                {
                    CopyTrainerHillTrainerText(TRAINER_HILL_TEXT_PLAYER_LOST, gTrainerBattleOpponent_B);
                    toCpy = gStringVar4;
                }
                break;
            case B_TXT_PARTNER_CLASS:
                toCpy = gTrainerClassNames[GetFrontierOpponentClass(gPartnerTrainerId)];
                break;
            case B_TXT_PARTNER_NAME:
                GetFrontierTrainerName(text, gPartnerTrainerId);
                toCpy = text;
                break;
            }

            // missing if (toCpy != NULL) check
            while (*toCpy != EOS)
            {
                dst[dstID] = *toCpy;
                dstID++;
                toCpy++;
            }
            if (*src == B_TXT_TRAINER1_LOSE_TEXT || *src == B_TXT_TRAINER2_LOSE_TEXT
                || *src == B_TXT_TRAINER1_WIN_TEXT || *src == B_TXT_TRAINER2_WIN_TEXT)
            {
                dst[dstID] = EXT_CTRL_CODE_BEGIN;
                dstID++;
                dst[dstID] = EXT_CTRL_CODE_PAUSE_UNTIL_PRESS;
                dstID++;
            }
        }
        else
        {
            dst[dstID] = *src;
            dstID++;
        }
        src++;
    }

    dst[dstID] = *src;
    dstID++;

    return dstID;
}

static void ExpandBattleTextBuffPlaceholders(const u8 *src, u8 *dst)
{
    u32 srcID = 1;
    u32 value = 0;
    u8 text[12];
    u16 hword;

    *dst = EOS;
    while (src[srcID] != B_BUFF_EOS)
    {
        switch (src[srcID])
        {
        case B_BUFF_STRING: // battle string
            hword = T1_READ_16(&src[srcID + 1]);
            StringAppend(dst, gBattleStringsTable[hword - BATTLESTRINGS_TABLE_START]);
            srcID += 3;
            break;
        case B_BUFF_NUMBER: // int to string
            switch (src[srcID + 1])
            {
            case 1:
                value = src[srcID + 3];
                break;
            case 2:
                value = T1_READ_16(&src[srcID + 3]);
                break;
            case 4:
                value = T1_READ_32(&src[srcID + 3]);
                break;
            }
            ConvertIntToDecimalStringN(dst, value, STR_CONV_MODE_LEFT_ALIGN, src[srcID + 2]);
            srcID += src[srcID + 1] + 3;
            break;
        case B_BUFF_MOVE: // move name
            StringAppend(dst, gMoveNames[T1_READ_16(&src[srcID + 1])]);
            srcID += 3;
            break;
        case B_BUFF_TYPE: // type name
            StringAppend(dst, gTypeNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_MON_NICK_WITH_PREFIX: // poke nick with prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
            {
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, text);
            }
            else
            {
                if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
                    StringAppend(dst, sText_FoePkmnPrefix);
                else
                    StringAppend(dst, sText_WildPkmnPrefix);

                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, text);
            }
            StringGet_Nickname(text);
            StringAppend(dst, text);
            srcID += 3;
            break;
        case B_BUFF_STAT: // stats
            StringAppend(dst, gStatNamesTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_SPECIES: // species name
            GetSpeciesName(dst, T1_READ_16(&src[srcID + 1]));
            srcID += 3;
            break;
        case B_BUFF_MON_NICK: // poke nick without prefix
            if (GetBattlerSide(src[srcID + 1]) == B_SIDE_PLAYER)
                GetMonData(&gPlayerParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            else
                GetMonData(&gEnemyParty[src[srcID + 2]], MON_DATA_NICKNAME, dst);
            StringGet_Nickname(dst);
            srcID += 3;
            break;
        case B_BUFF_NEGATIVE_FLAVOR: // flavor table
            StringAppend(dst, gPokeblockWasTooXStringTable[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ABILITY: // ability names
            StringAppend(dst, gAbilityNames[src[srcID + 1]]);
            srcID += 2;
            break;
        case B_BUFF_ITEM: // item name
            hword = T1_READ_16(&src[srcID + 1]);
            if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            {
                if (hword == ITEM_ENIGMA_BERRY)
                {
                    if (gLinkPlayers[gBattleScripting.multiplayerId].id == gPotentialItemEffectBattler)
                    {
                        StringCopy(dst, gEnigmaBerries[gPotentialItemEffectBattler].name);
                        StringAppend(dst, sText_BerrySuffix);
                    }
                    else
                    {
                        StringAppend(dst, sText_EnigmaBerry);
                    }
                }
                else
                {
                    CopyItemName(hword, dst);
                }
            }
            else
            {
                CopyItemName(hword, dst);
            }
            srcID += 3;
            break;
        }
    }
}

// Loads one of two text strings into the provided buffer. This is functionally
// unused, since the value loaded into the buffer is not read; it loaded one of
// two particles (either "は" or "の") which works in tandem with ChooseTypeOfMoveUsedString
// below to effect changes in the meaning of the line.
static void ChooseMoveUsedParticle(u8 *textBuff)
{
    s32 counter = 0;
    u32 i = 0;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == 0)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    if (counter >= 0)
    {
        if (counter <= 2)
            StringCopy(textBuff, sText_SpaceIs); // is
        else if (counter <= MAX_MON_MOVES)
            StringCopy(textBuff, sText_ApostropheS); // 's
    }
}

// Appends "!" to the text buffer `dst`. In the original Japanese this looked
// into the table of moves at sGrammarMoveUsedTable and varied the line accordingly.
//
// sText_ExclamationMark was a plain "!", used for any attack not on the list.
// It resulted in the translation "<NAME>'s <ATTACK>!".
//
// sText_ExclamationMark2 was "を つかった！". This resulted in the translation
// "<NAME> used <ATTACK>!", which was used for all attacks in English.
//
// sText_ExclamationMark3 was "した！". This was used for those moves whose
// names were verbs, such as Recover, and resulted in translations like "<NAME>
// recovered itself!".
//
// sText_ExclamationMark4 was "を した！" This resulted in a translation of
// "<NAME> did an <ATTACK>!".
//
// sText_ExclamationMark5 was " こうげき！" This resulted in a translation of
// "<NAME>'s <ATTACK> attack!".
static void ChooseTypeOfMoveUsedString(u8 *dst)
{
    s32 counter = 0;
    s32 i = 0;

    while (*dst != EOS)
        dst++;

    while (counter != MAX_MON_MOVES)
    {
        if (sGrammarMoveUsedTable[i] == MOVE_NONE)
            counter++;
        if (sGrammarMoveUsedTable[i++] == gBattleMsgDataPtr->currentMove)
            break;
    }

    switch (counter)
    {
    case 0:
        StringCopy(dst, sText_ExclamationMark);
        break;
    case 1:
        StringCopy(dst, sText_ExclamationMark2);
        break;
    case 2:
        StringCopy(dst, sText_ExclamationMark3);
        break;
    case 3:
        StringCopy(dst, sText_ExclamationMark4);
        break;
    case 4:
        StringCopy(dst, sText_ExclamationMark5);
        break;
    }
}

void BattlePutTextOnWindow(const u8 *text, u8 windowId)
{
    const struct BattleWindowText *textInfo = sBattleTextOnWindowsInfo[gBattleScripting.windowsType];
    bool32 copyToVram;
    struct TextPrinterTemplate printerTemplate;
    u8 speed;

    if (windowId & B_WIN_COPYTOVRAM)
    {
        windowId &= ~B_WIN_COPYTOVRAM;
        copyToVram = FALSE;
    }
    else
    {
        FillWindowPixelBuffer(windowId, textInfo[windowId].fillValue);
        copyToVram = TRUE;
    }

    printerTemplate.currentChar = text;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = textInfo[windowId].fontId;
    printerTemplate.x = textInfo[windowId].x;
    printerTemplate.y = textInfo[windowId].y;
    printerTemplate.currentX = printerTemplate.x;
    printerTemplate.currentY = printerTemplate.y;
    printerTemplate.letterSpacing = textInfo[windowId].letterSpacing;
    printerTemplate.lineSpacing = textInfo[windowId].lineSpacing;
    printerTemplate.unk = 0;
    printerTemplate.fgColor = textInfo[windowId].fgColor;
    printerTemplate.bgColor = textInfo[windowId].bgColor;
    printerTemplate.shadowColor = textInfo[windowId].shadowColor;

    if (printerTemplate.x == 0xFF)
    {
        u32 width = GetBattleWindowTemplatePixelWidth(gBattleScripting.windowsType, windowId);
        s32 alignX = GetStringCenterAlignXOffsetWithLetterSpacing(printerTemplate.fontId, printerTemplate.currentChar, width, printerTemplate.letterSpacing);
        printerTemplate.x = printerTemplate.currentX = alignX;
    }

    if (windowId == ARENA_WIN_JUDGMENT_TEXT)
        gTextFlags.useAlternateDownArrow = FALSE;
    else
        gTextFlags.useAlternateDownArrow = TRUE;

    if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED))
        gTextFlags.autoScroll = TRUE;
    else
        gTextFlags.autoScroll = FALSE;

    if (windowId == B_WIN_MSG || windowId == ARENA_WIN_JUDGMENT_TEXT)
    {
        if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
            speed = 1;
        else if (gBattleTypeFlags & BATTLE_TYPE_RECORDED)
            speed = sRecordedBattleTextSpeeds[GetTextSpeedInRecordedBattle()];
        else
            speed = GetPlayerTextSpeedDelay();

        gTextFlags.canABSpeedUpPrint = 1;
    }
    else
    {
        speed = textInfo[windowId].speed;
        gTextFlags.canABSpeedUpPrint = 0;
    }

    AddTextPrinter(&printerTemplate, speed, NULL);

    if (copyToVram)
    {
        PutWindowTilemap(windowId);
        CopyWindowToVram(windowId, COPYWIN_FULL);
    }
}

void SetPpNumbersPaletteInMoveSelection(void)
{
    struct ChooseMoveStruct *chooseMoveStruct = (struct ChooseMoveStruct *)(&gBattleBufferA[gActiveBattler][4]);
    const u16 *palPtr = gPPTextPalette;
    u8 var = GetCurrentPpToMaxPpState(chooseMoveStruct->currentPp[gMoveSelectionCursor[gActiveBattler]],
                         chooseMoveStruct->maxPp[gMoveSelectionCursor[gActiveBattler]]);

    gPlttBufferUnfaded[92] = palPtr[(var * 2) + 0];
    gPlttBufferUnfaded[91] = palPtr[(var * 2) + 1];

    CpuCopy16(&gPlttBufferUnfaded[92], &gPlttBufferFaded[92], sizeof(u16));
    CpuCopy16(&gPlttBufferUnfaded[91], &gPlttBufferFaded[91], sizeof(u16));
}

u8 GetCurrentPpToMaxPpState(u8 currentPp, u8 maxPp)
{
    if (maxPp == currentPp)
    {
        return 3;
    }
    else if (maxPp <= 2)
    {
        if (currentPp > 1)
            return 3;
        else
            return 2 - currentPp;
    }
    else if (maxPp <= 7)
    {
        if (currentPp > 2)
            return 3;
        else
            return 2 - currentPp;
    }
    else
    {
        if (currentPp == 0)
            return 2;
        if (currentPp <= maxPp / 4)
            return 1;
        if (currentPp > maxPp / 2)
            return 3;
    }

    return 0;
}
