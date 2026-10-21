#ifndef NOCTURNE_RECOVERED_H
#define NOCTURNE_RECOVERED_H

#include <stddef.h>
#include <stdint.h>

/* Confirmed SLUS_209.11 fields; gaps preserve bytes whose meaning is unknown. */
typedef struct datUnitWork_PS2 {
    uint32_t flag;
    uint16_t id, hp, maxhp, mp, maxmp, badstat;
    int32_t exp;
    uint16_t level;
    int8_t param[6], skillparam[6];
    uint16_t uniqueid;
    uint8_t unknown_24[0x14];
    uint16_t skillcnt, skill[24];
    uint8_t unknown_6a[0x10];
    int8_t mitamaparam[6];
    int8_t levelupparam[6];
    uint16_t keisyoskill[24];
    uint8_t keiattr[24];
    uint16_t hensinmae;
    uint8_t unknown_d0[8];
    int32_t hensinmaeexp;
    uint8_t unknown_dc[0x10];
} datUnitWork_PS2;

/* Inline PS2 record, not the HD managed object's layout. SetElem proves every
 * copied range; reserved field names come from the HD reference. */
typedef struct fclEncycElem_PS2 {
    uint16_t id, reserved0, maxhp, maxmp;
    int32_t exp;
    uint16_t level;
    int8_t param[6], skillparam[6];
    uint16_t skillcnt, skill[24];
    int8_t mitamaparam[6], levelupparam[6];
    uint16_t keisyoskill[24];
    uint8_t keiattr[24];
    uint16_t hensinmae, reserved1;
    uint32_t flag, reserved2;
    int32_t hensinmaeexp;
} fclEncycElem_PS2;

typedef struct datGlobalWork_PS2 {
    uint8_t unknown_0000[0x840];
    uint32_t event_bits[128];
    uint8_t moon_flags, moon_phase;
    uint8_t unknown_0a42[2];
    uint32_t moon_move_bits;
    int32_t maka;
    uint8_t unknown_0a4c[4];
    int32_t stock_capacity;
    datUnitWork_PS2 units[16];
    uint8_t stock_list[16];
    int32_t stock_count;
    uint8_t item_counts[0xa0];
    int16_t boss_records[40][2];
    uint8_t unknown_1a68[0x292];
    uint8_t hearts_equipped;
    uint8_t hearts_owned[64], hearts_skill_state[64], hearts_owned_count;
    uint8_t unknown_1d7c[0xfd44];
    uint16_t hearts_learned_skills[26][12];
    uint8_t unknown_11d30[0x90];
    uint8_t hearts_param_upgrades[26][6];
    uint8_t unknown_11e5c[0x24];
    int32_t encyc_count;
    uint8_t unknown_11e84[0xc];
    fclEncycElem_PS2 encyc_records[184];
    /* More fields follow; this is a partial global-work view. */
} datGlobalWork_PS2;

typedef struct datBossRashEntry_PS2 {
    int32_t available_bit, record_bit, enemy_id, initial_press;
} datBossRashEntry_PS2;

/* Only the skill range and stride are established here. This partial view
 * must not be mistaken for a complete recovered demon descriptor. */
typedef struct datDevilSkillRecord_PS2 {
    uint8_t unknown_00[4];
    uint8_t race;
    uint8_t unknown_05[0x11];
    uint16_t skill[8];
    uint8_t unknown_26[0x16];
} datDevilSkillRecord_PS2;

typedef struct nbMainProcessData_PS2_prefix {
    uint8_t unknown_00[0x60];
    uint32_t flag;
    /* More fields follow; total battle process-data size is unproved. */
} nbMainProcessData_PS2_prefix;

/* Reviewed compiler-support parts layout; names are chosen semantic aliases.
 * The ABI exchanges binary64 bits through integer EE registers, not F0. */
typedef struct ps2SoftDoubleParts {
    uint32_t fpclass, sign;
    int32_t exponent;
    uint8_t unknown_0c[4];
    uint64_t fraction;
} ps2SoftDoubleParts;

typedef struct ps2SoftFloatParts {
    uint32_t fpclass, sign;
    int32_t exponent;
    uint32_t fraction;
} ps2SoftFloatParts;

/* A view starting at the first skill's level byte inside each Hearts record.
 * Eight four-byte entries repeat at stride66; this is not a complete record. */
typedef struct cmbHeartsSkillEntry_PS2 {
    int8_t level;
    uint8_t unknown_01;
    uint16_t skill;
} cmbHeartsSkillEntry_PS2;
typedef struct cmbHeartsSkillRow_PS2 {
    cmbHeartsSkillEntry_PS2 skills[8];
    uint8_t unknown_20[34];
} cmbHeartsSkillRow_PS2;

/* Descriptor fields proved by the connected Hearts accessors. The signed16
 * at+4 and the remaining bytes have not been assigned semantic meanings. */
typedef struct cmbHeartsRecord_PS2 {
    uint8_t flag, unknown_01;
    int16_t aisyo;
    uint8_t unknown_04[2];
    int8_t param[6], master_param[6];
    uint8_t unknown_12[8];
    cmbHeartsSkillEntry_PS2 skills[8];
    uint8_t unknown_3a[8];
} cmbHeartsRecord_PS2;

typedef struct cmpHeartsPosition_PS2 {
    int8_t id, icon_type;
    uint8_t unknown_02[2];
    uint32_t icon_color;
} cmpHeartsPosition_PS2;

_Static_assert(sizeof(datUnitWork_PS2) == 0xec, "unit stride");
_Static_assert(offsetof(datUnitWork_PS2, hp) == 6, "HP offset");
_Static_assert(offsetof(datUnitWork_PS2, badstat) == 0xe, "status offset");
_Static_assert(offsetof(datUnitWork_PS2, param) == 0x16, "parameter offset");
_Static_assert(offsetof(datUnitWork_PS2, uniqueid) == 0x22, "unique ID offset");
_Static_assert(offsetof(datUnitWork_PS2, skillcnt) == 0x38, "skill count offset");
_Static_assert(offsetof(datUnitWork_PS2, mitamaparam) == 0x7a, "mitama offset");
_Static_assert(offsetof(datUnitWork_PS2, skill) == 0x3a, "skills offset");
_Static_assert(offsetof(datUnitWork_PS2, levelupparam) == 0x80, "level-up parameter offset");
_Static_assert(offsetof(datUnitWork_PS2, keisyoskill) == 0x86, "inherited skills offset");
_Static_assert(offsetof(datUnitWork_PS2, keiattr) == 0xb6, "inheritance attributes offset");
_Static_assert(offsetof(datUnitWork_PS2, hensinmae) == 0xce, "pre-transformation ID offset");
_Static_assert(offsetof(datUnitWork_PS2, hensinmaeexp) == 0xd8, "pre-transformation experience offset");
_Static_assert(sizeof(fclEncycElem_PS2) == 0xb0, "compendium record stride");
_Static_assert(offsetof(fclEncycElem_PS2, skill) == 0x1c, "record skills offset");
_Static_assert(offsetof(fclEncycElem_PS2, keisyoskill) == 0x58, "record inherited skills offset");
_Static_assert(offsetof(fclEncycElem_PS2, keiattr) == 0x88, "record inheritance attributes offset");
_Static_assert(offsetof(fclEncycElem_PS2, flag) == 0xa4, "record flags offset");
_Static_assert(offsetof(fclEncycElem_PS2, hensinmaeexp) == 0xac, "record pre-transformation experience offset");
_Static_assert(offsetof(datGlobalWork_PS2, event_bits) == 0x840, "event bits offset");
_Static_assert(offsetof(datGlobalWork_PS2, moon_phase) == 0xa41, "moon phase offset");
_Static_assert(offsetof(datGlobalWork_PS2, moon_move_bits) == 0xa44, "moon move offset");
_Static_assert(offsetof(datGlobalWork_PS2, maka) == 0xa48, "currency offset");
_Static_assert(offsetof(datGlobalWork_PS2, units) == 0xa54, "unit stock offset");
_Static_assert(offsetof(datGlobalWork_PS2, stock_list) == 0x1914, "stock list offset");
_Static_assert(offsetof(datGlobalWork_PS2, stock_count) == 0x1924, "stock count offset");
_Static_assert(offsetof(datGlobalWork_PS2, item_counts) == 0x1928, "item counts offset");
_Static_assert(offsetof(datGlobalWork_PS2, boss_records) == 0x19c8, "boss records offset");
_Static_assert(offsetof(datGlobalWork_PS2, encyc_count) == 0x11e80, "compendium count offset");
_Static_assert(offsetof(datGlobalWork_PS2, encyc_records) == 0x11e90, "compendium records offset");
_Static_assert(sizeof(datGlobalWork_PS2) == 0x19d10, "partial global-work extent");
_Static_assert(sizeof(datBossRashEntry_PS2) == 16, "boss table stride");
_Static_assert(sizeof(datDevilSkillRecord_PS2) == 0x3c, "demon descriptor stride");
_Static_assert(offsetof(datDevilSkillRecord_PS2, skill) == 0x16, "descriptor skills offset");
_Static_assert(offsetof(nbMainProcessData_PS2_prefix, flag) == 0x60, "battle process flags offset");
_Static_assert(sizeof(ps2SoftDoubleParts) == 24, "software-double parts size");
_Static_assert(offsetof(ps2SoftDoubleParts, fraction) == 16, "software-double fraction offset");
_Static_assert(sizeof(ps2SoftFloatParts) == 16, "software-float parts size");
_Static_assert(offsetof(ps2SoftFloatParts, fraction) == 12, "software-float fraction offset");
_Static_assert(sizeof(float) == 4, "32-bit float interface");
_Static_assert(offsetof(datGlobalWork_PS2, hearts_owned) == 0x1cfb, "Hearts ownership offset");
_Static_assert(offsetof(datGlobalWork_PS2, hearts_equipped) == 0x1cfa, "equipped Hearts offset");
_Static_assert(offsetof(datGlobalWork_PS2, hearts_skill_state) == 0x1d3b, "Hearts skill state offset");
_Static_assert(offsetof(datGlobalWork_PS2, hearts_owned_count) == 0x1d7b, "Hearts ownership count offset");
_Static_assert(offsetof(datGlobalWork_PS2, hearts_learned_skills) == 0x11ac0, "Hearts learned skills offset");
_Static_assert(sizeof(cmbHeartsSkillRow_PS2) == 66, "Hearts skill row stride");
_Static_assert(sizeof(cmbHeartsSkillEntry_PS2) == 4, "Hearts skill entry stride");
_Static_assert(offsetof(cmbHeartsSkillEntry_PS2, skill) == 2, "Hearts skill ID offset");
_Static_assert(offsetof(datGlobalWork_PS2, hearts_param_upgrades) == 0x11dc0, "Hearts parameter upgrades offset");
_Static_assert(sizeof(cmbHeartsRecord_PS2) == 66, "Hearts descriptor stride");
_Static_assert(offsetof(cmbHeartsRecord_PS2, param) == 6, "Hearts normal parameters offset");
_Static_assert(offsetof(cmbHeartsRecord_PS2, master_param) == 12, "Hearts master parameters offset");
_Static_assert(offsetof(cmbHeartsRecord_PS2, skills) == 26, "Hearts descriptor skills offset");
_Static_assert(sizeof(cmpHeartsPosition_PS2) == 8, "Hearts position table stride");
_Static_assert(offsetof(cmpHeartsPosition_PS2, icon_color) == 4, "Hearts icon color offset");

/* Host binding names, not recovered original symbol names. PS2 bindings:
 * global-work pointer: 0x0054ea20; default RNG words: 0x00529bd8;
 * immutable boss table: 0x003fa430. */
extern datGlobalWork_PS2 *g_datGlobalWork;
extern uint32_t *g_sdfDefaultState;
extern const datBossRashEntry_PS2 *g_datBossRashTable;
/* More host bindings: descriptor table at3497c0, draw alpha at54f75c,
 * debug-enable word at54e824. Names are adaptations, not original symbols. */
extern const datDevilSkillRecord_PS2 *g_datDevilSkillTable;
extern float g_evtMoonDrawAlpha;
extern int32_t g_nbDebugEnabled;
_Noreturn void nocturne_break(uint32_t code);
/* External diagnostic binding at 0x002d4748. The call at 0x001097e8 only
 * spills varargs to its own stack frame; this build has no debug output body. */
int32_t nocturne_diagnostic_printf(const char *message);

uint32_t sdfGetRand(uint32_t *state);
float sdfGetRandFloat(uint32_t *state);
uint32_t sdfGetRandInt(uint32_t *state, uint32_t limit);
void evtBitAllOff(void);
void evtBitOn(int32_t no);
void evtBitOff(int32_t no);
uint32_t evtBitCheck(int32_t no);
void datOverwriteBadStat(datUnitWork_PS2 *work, uint32_t badstat);
void datSetBadStat(datUnitWork_PS2 *work, uint32_t badstat);
void datResetBadStat(datUnitWork_PS2 *work, uint32_t badstat);
uint32_t datAddHp(datUnitWork_PS2 *work, int32_t hp);
uint32_t datAddMp(datUnitWork_PS2 *work, int32_t mp);
int32_t datGetLevelForDraw(datUnitWork_PS2 *work);
void datAddMaka(int32_t addmaka);
int32_t datCheckMaka(int32_t maka);
int32_t datGetBaseParam(datUnitWork_PS2 *work, int32_t paratype);
int32_t datGetParam(datUnitWork_PS2 *work, int32_t paratype);
int32_t datGetBadStatusAttr(int32_t bad);
int32_t datCheckDying(datUnitWork_PS2 *work);
int32_t datCheckItem(int32_t id, int32_t num);
int32_t datCheckItemFull(int32_t id);
int32_t datGetPlayerLevel(void);
int32_t datCheckStockFull(void);
int32_t datGetUniqueDevilId(int32_t uid);
int32_t datCheckSyojiSkill(datUnitWork_PS2 *work, uint32_t skill);
int32_t datCheckSkillInParty(int32_t skillid);
int32_t datGetBaseMaxHp(datUnitWork_PS2 *work);
int32_t datGetBaseMaxMp(datUnitWork_PS2 *work);
uint32_t datGetMaxHp(datUnitWork_PS2 *work);
uint32_t datGetMaxMp(datUnitWork_PS2 *work);
int32_t datGetRace(datUnitWork_PS2 *work);
int32_t datBossRashGetRec(int32_t eid, int32_t type);
void datBossRashUpdRec(int32_t eid, int32_t press);
int32_t datBossRashChk(int32_t eid);
void cmpAddStockListGBWK(int8_t index);
void cmpDeleteStockListGBWK(int8_t index);
void cmpReplaceStockGBWK(void);
int32_t cmpRemoveDevilEx(uint16_t id);
int32_t datDelDevil(int32_t id);
void fclEncyc_SetElem(fclEncycElem_PS2 *elem, datUnitWork_PS2 *unit);
int32_t fclEncycSearch(int32_t id);
int32_t fclEncycGetNum(void);
int32_t fclEncycGetRatio2(void);
int32_t fclEncycRegist(datUnitWork_PS2 *unit, int32_t overwrite);
uint32_t evtGetAgeOfMoon(void);
uint32_t evtGetAgeOfMoon16(void);
void evtSetAgeOfMoon(int32_t age);
void evtEnableMoonCalc(void);
void ps2MoonDisableCalc(void);
void evtEnableMoonDraw(void);
void evtDisableMoonDraw(void);
void evtEnableMoonDraw2(void);
void evtDisableMoonDraw2(void);
void nbMainProcess_ClearLocalBit(void);
void nbMainProcess_SetDebugFlag(nbMainProcessData_PS2_prefix *data);
int32_t nbHatudoCheckSkill(datUnitWork_PS2 *work, int32_t skill);
int32_t nbGetNegoKureHpA(void *n, datUnitWork_PS2 *a, datUnitWork_PS2 *b);
uint64_t ps2SoftDoublePack(const ps2SoftDoubleParts *parts);
void ps2SoftDoubleUnpack(const uint64_t *bits, ps2SoftDoubleParts *parts);
uint64_t ps2SoftDoubleFromInt(int32_t value);
int32_t ps2SoftDoubleToInt(uint64_t bits);
uint64_t ps2SoftDoubleMul(uint64_t left, uint64_t right);
uint64_t ps2Mul64(uint64_t left, uint64_t right);
const ps2SoftDoubleParts *ps2SoftDoubleAddParts(const ps2SoftDoubleParts *left,
    const ps2SoftDoubleParts *right, ps2SoftDoubleParts *output);
uint64_t ps2SoftDoubleAdd(uint64_t left, uint64_t right);
uint64_t ps2SoftDoubleSub(uint64_t left, uint64_t right);
uint32_t ps2SoftDoubleToUint(uint64_t bits);
int32_t ps2SoftDoubleCompareParts(const ps2SoftDoubleParts *left, const ps2SoftDoubleParts *right);
int32_t ps2SoftDoubleCompare(uint64_t left, uint64_t right);
void ps2SoftFloatUnpack(const uint32_t *bits, ps2SoftFloatParts *parts);
float ps2SoftFloatPack(const ps2SoftFloatParts *parts);
uint64_t ps2SoftDoublePackFields(uint32_t fpclass, uint32_t sign, int32_t exponent, uint64_t fraction);
float ps2SoftFloatPackFields(uint32_t fpclass, uint32_t sign, int32_t exponent, uint32_t fraction);
uint64_t ps2SoftDoubleFromFloat(float value);
float ps2SoftDoubleToFloat(uint64_t bits);
extern const int8_t *g_fclItemHeartsTable;
extern const cmbHeartsSkillRow_PS2 *g_cmbHeartsSkillRows;
int8_t fclChkItemHearts(uint16_t itemid);
int32_t fclAddItem(uint16_t itemid, int32_t num);
void datAddItem(int32_t id, int32_t num);
int32_t datAddHearts(int32_t id);
int8_t cmpChkHaveHearts(int8_t id);
int32_t cmpChkHaveNormalHeartsAll(void);
int8_t cmbGetHeartsAfterSkillNums(uint8_t id);
void cmbAddHeartsSkill(int8_t id, uint16_t skill);
int8_t cmbCreateDefaultHeartsSkill(uint8_t id, datUnitWork_PS2 *unit);
extern const cmbHeartsRecord_PS2 *g_cmbHeartsRecords;
extern const cmpHeartsPosition_PS2 *g_cmpHeartsPositions;
int8_t cmbChkGetHearts(int8_t id);
int16_t cmbGetHeartsSkillNums(uint8_t id);
int8_t cmbChkHeartsMaster(uint8_t id);
int8_t cmbGetMasterHeartsNums(void);
void cmbSetHeartsMaster(int8_t id);
uint16_t ps2HeartsSkillAt(uint8_t id, int8_t index);
int16_t cmbGetHeartsAisyo(uint8_t id);
int8_t cmbGetHeartsDefaultParam(int8_t id, int8_t index, int8_t type);
int8_t cmbGetHeartsParamEx(int8_t id, int8_t index, int8_t mode);
int8_t cmbGetHeartsParam(int8_t id, int8_t index);
void ps2HeartsAddParam(uint8_t id, datUnitWork_PS2 *unit);
void cmbSubHeartsParam(uint8_t id, datUnitWork_PS2 *unit);
int8_t cmbChkSkillOwner(uint16_t skill, datUnitWork_PS2 *unit);
uint16_t cmbChkGetHeartsSkill(uint8_t id, datUnitWork_PS2 *unit);
int8_t cmpGetHeartsFromPos(int8_t index);
int8_t cmpGetHeartsIconTypeFromPos(int8_t index);
uint32_t cmpGetHeartsIconColorFromPos(int8_t index);

#endif
