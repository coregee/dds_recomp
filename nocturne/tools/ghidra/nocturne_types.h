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
    datUnitWork units[16];
} datGlobalWork;

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
