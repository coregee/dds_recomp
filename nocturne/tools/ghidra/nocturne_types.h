/* Record types for the Ghidra project, in plain C, under their original
 * names (HD remaster). Imported by ImportTypes.java (tools/ghidra/import-types.ps1).
 *
 * This mirrors source/include/nocturne/data/records.hpp and battle/process.hpp;
 * source/tests/tables compiles it and checks sizes and offsets match.
 * PTR32(T) is a 32-bit PS2 pointer: a real pointer in Ghidra, uint32_t on a PC. */
#ifndef NOCTURNE_GHIDRA_TYPES_H
#define NOCTURNE_GHIDRA_TYPES_H

#ifndef PTR32
#define PTR32(T) T *
#endif

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

/* Bad status (datUnitWork.badstat, low 12 bits): one ailment at a time. */
typedef enum nbBadStat {
    BAD_NONE = 0x000, BAD_SHOCK = 0x001, BAD_FREEZE = 0x002, BAD_SLEEP = 0x004,
    BAD_PANIC = 0x008, BAD_BIND = 0x010, BAD_MUTE = 0x020, BAD_POISON = 0x040,
    BAD_CHARM = 0x080, BAD_STUN = 0x100, BAD_FLY = 0x200, BAD_STONE = 0x400,
    BAD_DEAD = 0x800, BAD_CURSE = 0x8000
} nbBadStat;

/* Skill element ("attr"). */
typedef enum nbAttr {
    ATTR_NONE = -1, ATTR_PHYS = 0, ATTR_FIRE = 1, ATTR_ICE = 2, ATTR_ELEC = 3,
    ATTR_FORCE = 4, ATTR_ALMIGHTY = 5, ATTR_EXPEL = 6, ATTR_DEATH = 7,
    ATTR_CURSE = 8, ATTR_NERVE = 9, ATTR_MIND = 10
} nbAttr;

/* Stat index ("paratype"). */
typedef enum datParam {
    PARAM_STR = 0, PARAM_UNUSED1 = 1, PARAM_MAG = 2, PARAM_VIT = 3, PARAM_AGI = 4, PARAM_LUK = 5
} datParam;

typedef struct datUnitWork {
    u32 flag;               /* 1 valid, 2 in party, 4 Demi-fiend, 0x20 enemy */
    u16 id;
    u16 hp, maxhp, mp, maxmp;
    u16 badstat;
    s32 exp;
    u16 level;
    s8 param[6];
    s8 skillparam[6];
    u16 uniqueid;
    u16 reserve1, reserve2;
    u8 namecode[16];
    u16 skillcnt;
    u16 skill[24];
    s16 nowcommand;
    u16 nowindex;
    s16 nowtarea, nowtform;
    s16 prevcommand;
    u16 previndex;
    s16 prevtarea, prevtform;
    s8 mitamaparam[6];
    s8 levelupparam[6];
    u16 keisyoskill[24];
    u8 keiattr[24];
    u16 hensinmae;
    u16 getdevilhearts[4];
    u32 hensinmaeexp;
    u8 fullnamecode[16];
} datUnitWork;

typedef struct datNormalSkill {
    u8 flag, use, koukatype, costtype;
    u16 cost, costbase;
    u8 targettype, targetarea, targetrule, targetrandom;
    u16 untargetbadstat, targetprog;
    u8 hittype, hitlevel;
    u16 hitprog;
    u8 targetcntmin, targetcntmax;
    u16 hptype;
    s16 hpn;
    u16 mptype;
    s16 mpn;
    s16 hpbase, mpbase;
    u16 minus;
    u8 badtype, badlevel;
    u16 badstatus;
    u32 hojotype;
    s8 hojopoint;
    u8 deadtype;
    u8 unknown_2e[2];
    u32 program;
    s16 criticalpoint, failpoint, magicbase, magiclimit;
} datNormalSkill;

typedef struct datSpecialSkill {
    s16 n, m, a, b;
} datSpecialSkill;

typedef struct datDevilFormat {
    u32 flag;
    u8 race, level;
    u16 hp, maxhp, mp, maxmp;
    s16 aisyoid;
    s8 param[6];
    u16 skill[8];
    s16 keisyotype;
    u16 keisyoform;
    u16 dropmakka, dropexp;
    u8 dropitem[2], droppoint[2];
    u16 specialbit;
    u8 specialitem, specialpoint, hougyokupoint, masekipoint;
    s8 attackattr;
    u8 attackcnt, attackinterval, reserve1;
} datDevilFormat;

typedef struct datEncount {
    s8 backattack, esc;
    u8 item, itemcnt, formationtype, unknown_05;
    u16 devil[11];
    u16 stageid, areaid, flag;
    u8 maxparty, maxcall;
    u16 btlsound;
} datEncount;

typedef struct datEncountRitu {
    u16 encountid, ritu;
    u8 sensei, renzokuritu;
    u16 renzokuindex;
} datEncountRitu;

typedef struct datEncountTbl {
    s32 normalritu;
    datEncountRitu ritu[12];
} datEncountTbl;

typedef struct datEncountPack {
    u16 stageid, areaid, btlsound, moonchk, table2, eventbit1, eventbit2;
    u8 table1[6];
    datEncountTbl enctable[4];
} datEncountPack;

typedef struct datAisyoRow {
    u32 attr[16];           /* rate % | 0x10000 null | 0x20000 repel | 0x40000 drain | 0x80000000 weak */
} datAisyoRow;

typedef struct datGlobalWork {
    u8 unknown_0000[0x840];
    u32 event_bits[128];
    u8 moon_flags, moon_phase;
    u8 unknown_0a42[2];
    u32 moon_move_bits;
    s32 maka;
    u32 unknown_0a4c;
    s32 stock_capacity;
    datUnitWork units[16];   /* [0] the Demi-fiend, [4..] demons */
    u8 stock_list[16];
    s32 stock_count;
    u8 item_counts[0xa0];
    s16 boss_records[40][2];
    u8 unknown_1a68[0x284];
    u8 reason_points[4];     /* [1..3]: Reason (Kotowari) points */
    u8 unknown_1cf0[0xa];
    u8 hearts_equipped;      /* Magatama ID */
    u8 hearts_owned[64];
    u8 hearts_skill_state[64];
    u8 hearts_owned_count;
} datGlobalWork;

/* datSkill: per-skill info. Table at 0x3D6998, 512 entries. */
typedef struct datSkill {
    s8 skillattr;            /* element, -1 none */
    s8 type;                 /* 0 active, 1 passive, -1 unused */
    s16 index;
    u16 keisyoform;          /* which demons can inherit it */
    s8 capacity;
    u8 flag;
} datSkill;

/* fclSkill: how a devil grows. Table at 0x333CF8, per devil ID. */
typedef struct fclSkillEvent {
    s8 targetlevel;
    u8 type;                 /* 1 learn skill, 5 evolve into devil, 7 evolution notice */
    u16 param;
} fclSkillEvent;
typedef struct fclSkill {
    s8 growparam[6];         /* level-up stat weights */
    fclSkillEvent event[24];
} fclSkill;

typedef struct datItem {
    u8 use, flag;
    u16 skillid;
    u32 price;
} datItem;

/* fclHearts: Magatama. Table at 0x339E00. */
typedef struct fclHeartsSkill {
    u8 targetlevel, unknown_01;
    u16 id;
} fclHeartsSkill;
typedef struct fclHearts {
    u8 flag, unknown_01;
    s16 aisyoid, masteraisyoid;
    s8 growparam[6];
    s8 mastergrowparam[6];
    s8 autoasignparam[6];    /* Demi-fiend level-up stat weights */
    u8 splitlevel, splitid;
    fclHeartsSkill skill[8];
    u8 event[8];
} fclHearts;

/* Evolution and inheritance (fclCombineCalcCore). */
typedef struct cmbEvoFlag { u16 devil, eventbit; } cmbEvoFlag;
typedef struct fclKeisyoSkillLevel { u16 skill; u8 level, unknown_03; } fclKeisyoSkillLevel;
typedef struct fclKeisyoScoreRow { s16 keisyotype; u16 score[16]; } fclKeisyoScoreRow;
typedef struct fclKeisyoScore {
    s16 unknown_00;
    s16 attribute[16];
    fclKeisyoScoreRow row[12];
} fclKeisyoScore;
typedef struct cmbPowerUpSkill { u16 skill, target; } cmbPowerUpSkill;

/* fclKeisyoList_t: skills a fused devil inherited (results screen). */
typedef struct fclKeisyoList {
    u16 skill[8];
    u8 count;
} fclKeisyoList;

/* Entry of the devil list sorted by race, then level (highest first). */
typedef struct cmbDevilSort {
    u16 devil, unused;
    PTR32(datDevilFormat) format;
} cmbDevilSort;

/* Fusion tables (fclCombineTable). */
typedef struct fclCombCom { u16 devil1, devil2, birth; } fclCombCom;
typedef struct fclRankBase { u8 race, flag; } fclRankBase;   /* flag 1 rank up, 2 down */
typedef struct fclRankTbl { u16 devil; fclRankBase base[32]; } fclRankTbl;
typedef struct fclCombSpirit { u16 devil; u16 paramtype[2]; u8 uprate, unknown_07; } fclCombSpirit;
typedef struct fclIkenieExtPattern { u8 race1, race2, race3, birthrace; } fclIkenieExtPattern;
typedef struct fclIkenieExtPatternDev { u16 devil1, devil2, devil3, birth; } fclIkenieExtPatternDev;
typedef struct fclIkenieExtPatternDev2 { u16 devil1, devil2, birth; } fclIkenieExtPatternDev2;
typedef struct fclIkenieExtPatternDevRace { u16 devil; u8 race1, race2; u16 birth; } fclIkenieExtPatternDevRace;
typedef struct fclEventDevil { u16 devil, unknown_02; u32 eventflag; } fclEventDevil;
typedef struct fclMoonRange { u8 min, max; } fclMoonRange;

typedef struct nbVec4 { float x, y, z, w; } nbVec4;

typedef struct nbFormation {
    nbVec4 orgpos, orgrot, pos, rot, center;
    float r, h, cr, scl, oneshotr, allshotr, movey, movez;
    s32 type;
    u32 time, stat, flag, anime, basic;
    s32 serial;
    u32 hunit;
    s16 partyindex, formindex;
    u8 unknown_94[0xf0 - 0x94];
} nbFormation;

typedef struct nbParty {
    s16 flag, formindex, statindex;
    u16 partyindex;
    s16 count[20];
    u32 aisyo[16];
    u16 hojoskill[8];
} nbParty;

typedef struct nbMainProcessData {
    PTR32(nbFormation) form;
    PTR32(datUnitWork) enemyunit;
    u8 unknown_08[8];
    PTR32(nbParty) party;
    u32 unknown_14;
    s16 playerpcnt, enemypcnt, activeunit;
    u16 unknown_1e;
    u32 sound, sound_mem;
    s32 encpackno, packno, packindex, encno, formationtype;
    u32 actionstack;
    s32 actionstackp;
    u32 endtype;
    s8 order[12];
    s8 orderindex;
    u8 unknown_55;
    s16 previndex;
    u16 prevcommand, prevcommind, prevflag, debug;
    u32 stat, flag;
    u8 turn;
    s8 phase, nextphase;
    u8 esccnt;
    u8 unknown_6c[0x98 - 0x6c];
    u8 item[4], itemcnt[4];
    u32 maka, exp;
    u8 unknown_a8[0x14c - 0xa8];
    s32 piercedResistance;
} nbMainProcessData;

typedef struct nbActionProcessData {
    PTR32(nbMainProcessData) data;
    u8 unknown_04[0x58 - 0x04];
    s32 autoskill;
} nbActionProcessData;

#endif
