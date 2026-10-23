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
/* nbTarSelProcessData: target selection (partial). */
typedef struct nbTarSelProcessData {
    PTR32(nbMainProcessData) data;
    PTR32(nbActionProcessData) act;
    u8 stat;
    s8 ctype;
    u8 crule, carea, nowcarea;
    s8 nowno, nowform;
    u8 unknown_0f;
    s16 partyindex;
    s8 friendcnt, enemycnt;
    s8 friendno[12], enemyno[12];
} nbTarSelProcessData;

/* datDevilAI_t: enemy AI per devil ID (0x3989E0). */
typedef struct datDevilAIChk { u32 check[2]; u32 table; } datDevilAIChk;
typedef struct datDevilAITbl { u16 ritu, skill; u32 target; } datDevilAITbl;
typedef struct datDevilAI {
    u16 scriptid, ailevel;
    datDevilAIChk aichk[3];
    datDevilAITbl aitable[3][5];
    u16 deadscriptid, deadeventno;
} datDevilAI;

/* scrCommandTable_t: FlowScript command table entry (0x52E350). */
typedef struct scrCommandTable {
    PTR32(void) comm;
    s32 paranum;
} scrCommandTable;

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

/* fclencyceelem_t: a compendium entry. */
typedef struct fclencyceelem {
    u16 id, reserved0, maxhp, maxmp;
    s32 exp;
    u16 level;
    s8 param[6], skillparam[6];
    u16 skillcnt, skill[24];
    s8 mitamaparam[6], levelupparam[6];
    u16 keisyoskill[24];
    u8 keiattr[24];
    u16 hensinmae, reserved1;
    u32 flag, reserved2;
    u32 hensinmaeexp;
} fclencyceelem;

/* rstSkillInfo_t: skills still to be learned. */
typedef struct rstSkillInfo {
    s8 skillcnt;
    u8 targetlevel[24];
    u8 unknown_19;
    u16 skill[24];
} rstSkillInfo;

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
    u8 unknown_1d7c[0xfd44];
    u16 hearts_learned_skills[26][12];
    u8 unknown_11d30[0x90];
    u8 hearts_param_upgrades[26][6];
    u8 unknown_11e5c[0x24];
    s32 encyc_count;
    u8 unknown_11e84[0xc];
    fclencyceelem encyc_records[184];
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
    u8 unknown_94[0xa4 - 0x94];
    s16 unknown_a4;
    u8 unknown_a6[0xf0 - 0xa6];
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
    u32 unknown_04;
    PTR32(datUnitWork) enemyunit;
    u32 unknown_0c;
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
    u16 phasetime;
    u32 battletime;
    float press3;
    s16 press4_p, press4_ten, press4_hansya, press4_miss;
    s16 StageMajor, StageMinor;
    s32 summonallowed;
    s32 aiextra;
    s32 eventrid;
    s16 negopformindex, negoeformindex;
    s32 negoresult;
    u8 item[4], itemcnt[4];
    u32 maka, exp;
    u32 baselight, niidalight, gamecamera, niidacamera, eventcamera;
    u32 MainProcessID, MaeProcessID, AtoProcessID, ResultProcessID, StageProcessID, UnitProcessID;
    u32 ActionProcessID[4];
    s32 NowActionProcess;
    u32 CommSelProcessID, TarSelProcessID, EffectProcessID;
    u32 KoukaProcessID;
    u32 NegoProcessID, CameraProcessID, DebugProcessID, AiScriptProcessID;
    u32 PanelProcessID, HelpProcessID, AutoCommProcessID, EncProcessID, EventProcessID;
    u32 HatudoEff, hPnlTex1, hPnlTex2, hPnlTex3, hPnlTex4;
    s32 jyokyomsgid;
    u8 unknown_134[0x14c - 0x134];
    s32 piercedResistance;
} nbMainProcessData;

/* nbTimeList_t */
typedef struct nbTimeList { u16 lockframe, endframe, hp, pad; } nbTimeList;

typedef struct nbActionProcessData {
    PTR32(nbMainProcessData) data;
    u32 stat;
    s8 seq, nextseq;
    u16 seqtime;
    s32 seqcnt, skilltime;
    float press;
    s32 newpresstype;
    s16 newpress_p, newpress_ten;
    s32 newaddpresstype;
    PTR32(nbParty) party;
    PTR32(nbFormation) form;
    PTR32(datUnitWork) work;
    s32 partyindex, type, target;
    u32 select, timer;
    s32 runerr, jyokyomes, jyo_varid, jyo_varind, adata;
    s32 autoskill;
    s32 allhpdamage, allmpdamage, massuruid;
    s32 negotype;
    u8 unknown_6c[0x74 - 0x6c];
    u32 hEffBTL, hBed, hSkillSe, hSkillMem, skillmidi;
    nbTimeList timelist[32];
    u32 packettime;
    s32 hitstopframe;
    u32 aiselect;
    s32 aijokentbl;
    s8 aichktbl[5];
    u8 unknown_19d[3];
    u32 aisummonid;
} nbActionProcessData;

/* nbTarSelProcessData: target selection (partial). */
typedef struct nbTarSelProcessData {
    PTR32(nbMainProcessData) data;
    PTR32(nbActionProcessData) act;
    u8 stat;
    s8 ctype;
    u8 crule, carea, nowcarea;
    s8 nowno, nowform;
    u8 unknown_0f;
    s16 partyindex;
    s8 friendcnt, enemycnt;
    s8 friendno[12], enemyno[12];
} nbTarSelProcessData;

/* datDevilAI_t: enemy AI per devil ID (0x3989E0). */
typedef struct datDevilAIChk { u32 check[2]; u32 table; } datDevilAIChk;
typedef struct datDevilAITbl { u16 ritu, skill; u32 target; } datDevilAITbl;
typedef struct datDevilAI {
    u16 scriptid, ailevel;
    datDevilAIChk aichk[3];
    datDevilAITbl aitable[3][5];
    u16 deadscriptid, deadeventno;
} datDevilAI;

/* scrCommandTable_t: FlowScript command table entry (0x52E350). */
typedef struct scrCommandTable {
    PTR32(void) comm;
    s32 paranum;
} scrCommandTable;

/* ---- the message manager (itfMesManager, source/include/nocturne/interface/message.hpp) ---- */

typedef struct frText frText;
typedef struct frRequest frRequest;
typedef struct itfmisclinkheader itfmisclinkheader;
typedef struct frTextureCell frTextureCell;

/* A glyph in the font texture cache. */
typedef struct frGlyph {
    u16 index, pad02, refs, pad06;
    PTR32(frTextureCell) cell;
} frGlyph;

/* A 24x24 cell of the font texture (a ring at 0x56B668). */
struct frTextureCell {
    s32 index, x, y, x2;
    u32 unknown_10;
    PTR32(frGlyph) glyph;
    PTR32(frTextureCell) prev;
    PTR32(frTextureCell) next;
};
typedef struct frTextureCells {
    u32 handle, pixel_handle;
    s32 width, height, bytes, count, free;
    PTR32(frTextureCell) ring;
} frTextureCells;

/* _TEXT: one character of a font request. */
struct frText {
    u16 code, draw_count;
    s32 lx, ly, lw;
    u32 color;
    u8 col_no, style, tp, mode;
    u8 width, height;
    u8 pad1a[2];
    PTR32(frGlyph) glyph;
    u32 data;
    PTR32(frText) prev;
    PTR32(frText) next;
};

/* _FRQ: a font request; a chain is handled by its last request. */
struct frRequest {
    u8 draw_spd;
    s8 space;
    u8 pad02[2];
    s32 x, y;
    s32 w_pxls;
    s16 x_size, y_size;
    u32 priority;
    s32 strlen;
    PTR32(frText) str;
    PTR32(frText) str_end;
    PTR32(frRequest) prev;
    PTR32(frRequest) next;
    PTR32(frRequest) head;
};

/* The header of a .fnt file. */
typedef struct frFontHeader {
    u32 header_size, data_size;
    u8 unknown_08[2];
    u8 palettes;
    u8 unknown_0b[3];
    u16 glyphs, width, height, glyph_bytes;
    u8 metrics, unknown_17;
    u32 names;
} frFontHeader;

/* A loaded font (nine styles at 0x56BA30). */
typedef struct frStyle {
    u32 handle;
    PTR32(frFontHeader) data;
    s32 metric_size[2];
    u32 metric[2];
    u32 cache, glyphs, names;
} frStyle;

/* A pool node; the payload follows. */
typedef struct frPoolNode frPoolNode;
struct frPoolNode {
    s32 index;
    PTR32(frPoolNode) next;
};

/* frMsgInfo_t: laying out a message page. */
typedef struct frMsgInfo {
    s32 x, y;
    u32 z;
    s8 style, colno, tp;
    u8 speed;
    u32 text;
    PTR32(frRequest) font;
    s32 pos;
    u8 newline, position, pad1e[2];
} frMsgInfo;

/* Font engine settings (0x54F404). */
typedef struct frSettings {
    u32 result;
    s8 space;
    u8 pad05[3];
    s32 step, base_width, space_width;
    u32 unknown_14;
    u8 mode, pad19[7];
    u8 style;
} frSettings;

/* itfpanel_t */
typedef struct itfpanel {
    u32 handle, workhandle, pwork, z;
    s32 pos[4];
    s32 color[4];
    u8 type;
} itfpanel;

/* A panel's vertices and colours (itfPanelTypeWork_t, by type). */
typedef struct itfPanelVertex { s32 x, y; } itfPanelVertex;
typedef struct itfPanelColor { s32 r, g, b, a; } itfPanelColor;
typedef struct itfColorRatio { s32 r, g, b, unused; } itfColorRatio;
typedef struct itfPanelNormalWork { itfPanelVertex vertex[8]; itfPanelColor edge, body; } itfPanelNormalWork;
typedef struct itfPanelMesWinWork {
    itfPanelVertex grid[16], top[12], bottom[12];
    itfPanelColor edge, body, shade[6];
} itfPanelMesWinWork;
typedef struct itfPanelSelWinWork {
    itfPanelVertex grid[16], top[8], bottom[8];
    itfPanelColor edge, body, shade[4];
} itfPanelSelWinWork;
typedef struct itfPanelPlainWork { itfPanelVertex vertex[4]; itfPanelColor body, shade[3]; } itfPanelPlainWork;
typedef struct itfPanelPera1Work { itfPanelVertex vertex[4]; itfPanelColor body; } itfPanelPera1Work;
typedef struct itfPanelLeftFadeWork { itfPanelVertex vertex[6]; itfPanelColor edge, body; } itfPanelLeftFadeWork;
typedef struct itfPanelFacilityWork { u32 texture; itfPanelVertex vertex[8]; itfPanelColor edge, body; } itfPanelFacilityWork;

/* itfMesBinFileHeader_t and the dialog headers of a loaded MSG1 table. */
typedef struct itfMesBinFileHeader {
    u8 filetype, format;
    s16 user_id;
    u32 filesize, mgc, extsize, ofs_addrinfo, size_addrinfo, numtypeheader;
    u8 resolveaddress, reserved0;
    u16 version;
} itfMesBinFileHeader;
typedef struct itfMesBinTypeHeader { u32 type, ptr; } itfMesBinTypeHeader;
typedef struct itfMesBinTypeHeader2 { PTR32(u32) ppspkhead; s32 spknum; u32 pextdata, reserved; } itfMesBinTypeHeader2;
typedef struct itfMesBinMesHeader { char label[24]; s16 page; u16 speaker; u32 addr[1]; } itfMesBinMesHeader;
typedef struct itfMesBinSelHeader { char label[24]; s16 ext, item, pattern; u16 reserved; u32 ptr[1]; } itfMesBinSelHeader;

typedef struct mesIVector2 { s32 x, y; } mesIVector2;
typedef struct Speaker_tag { mesIVector2 pos; PTR32(frRequest) pfont; u16 num, pad; } Speaker_tag;
typedef struct message_tag {
    mesIVector2 pos;
    PTR32(itfMesBinMesHeader) pbinheader;
    PTR32(frRequest) pfont;
    s8 phase;
    u8 wait, last_style, last_col, last_tp, last_spd;
    s16 lines, page, maxpage;
} message_tag;
typedef struct defkey_tag { s16 key, index; } defkey_tag;
typedef struct select_tag {
    mesIVector2 pos;
    PTR32(frRequest) pfont;
    u32 mask;
    s16 phase, select, select_imm, lines, alpha, numdef;
    defkey_tag defkey[16];
} select_tag;
typedef struct window_tag { PTR32(itfpanel) spk; PTR32(itfpanel) mes; s32 mes_offset[4]; s32 mes_color[4]; } window_tag;
typedef struct variable_tag { u32 pptr[32]; u32 pmh[32]; } variable_tag;
typedef struct curctr_tag { u8 isdraw, pad; s16 phase, ctr0, ctr1; u32 ctr_key; } curctr_tag;

/* instanceMes_tag: a message window. */
typedef struct instanceMes_tag {
    u32 stat;
    PTR32(itfMesBinFileHeader) pdata;
    u32 pext, z;
    s16 otindex, type;
    Speaker_tag speaker;
    message_tag message;
    select_tag select;
    window_tag window;
    variable_tag variable;
    curctr_tag curctr;
    u32 func_kuti;
} instanceMes_tag;

struct itfmisclinkheader {
    PTR32(itfmisclinkheader) pprev;
    PTR32(itfmisclinkheader) pnext;
    s32 id;
    PTR32(instanceMes_tag) instance;
    u32 handle;
};
typedef struct itfMiscLinkStack {
    PTR32(itfmisclinkheader) head, tail, freehead, freetail;
} itfMiscLinkStack;

/* The message manager's globals (0x56BE60). */
typedef struct itfMesManager {
    s32 count;
    u32 texture;
    s32 frame;
    u16 config, pad;
    itfMiscLinkStack list;
    itfmisclinkheader nodes[128];
} itfMesManager;


/* ---- the FlowScript VM (source/include/nocturne/script/vm.hpp) ---- */

typedef struct scrProcessWork scrProcessWork;

/* scrHeader_t: a .bf file's header. */
typedef struct scrHeader {
    u8 FileType, FileFormat;
    u16 UserID;
    s32 FileSize;
    char MagicCode[4];
    s32 ExpandSize, TypeTableCount;
    s16 LocalIntCount, LocalFloatCount;
    s32 Reserve2, Reserve3;
} scrHeader;

/* scrTypeTable_t: a section descriptor. */
typedef struct scrTypeTable { s32 Type, ItemSize, ItemCount; u32 ItemAddress; } scrTypeTable;

/* scrProcTable_t: a procedure or label. */
typedef struct scrProcTable { char Name[24]; s32 CodeAddress, Reserve1; } scrProcTable;

/* scrCode_t: a code word {opcode, operand}. */
typedef struct scrCode { s16 s0, s1; } scrCode;

/* scrProcessWork_s: a running script (0xF4 bytes). */
struct scrProcessWork {
    char Name[24];
    s32 CP, SP;
    u8 StackType[28];
    u32 StackData[28];
    PTR32(scrHeader) header;
    PTR32(scrTypeTable) typeTable;
    PTR32(scrProcTable) procTable;
    PTR32(scrProcTable) labelTable;
    PTR32(scrCode) code;
    u32 MessageData, StringData;
    s32 StartProc, MesHandle, ScriptTimer, CommandTimer;
    u32 MemHandle;
    PTR32(s32) LocalInt;
    PTR32(u32) LocalFloat;
    u32 ProcessID;
    PTR32(scrProcessWork) prev;
    PTR32(scrProcessWork) next;
    u32 data;
};

/* The running scripts (0x54E994). */
typedef struct scrScriptList {
    s32 scrHandleCount;
    PTR32(scrProcessWork) scrHandleFirst;
    PTR32(scrProcessWork) scrHandleLast;
} scrScriptList;

/* The screen quake (0x54E970, dds3KernelDraw). */
typedef struct dds3Quake { u16 dds3QuakeFlag; s16 dds3QuakeFrame; u16 dds3QuakeXRange, dds3QuakeYRange; } dds3Quake;


/* ---- the screen effects (source/include/nocturne/effect/event.hpp, kernel/draw.hpp) ---- */

typedef struct sdfIVector2 { s32 x, y; } sdfIVector2;
typedef struct dds3Vector4 { float x, y, z, w; } dds3Vector4;

/* dds3Effect_Blur_t */
typedef struct dds3Effect_Blur {
    u32 abgr;
    s32 blend;
    float rotate, scale;
    sdfIVector2 center;
    sdfIVector2 xy[2];
} dds3Effect_Blur;
typedef struct dds3Effect_PartialMultiBlurParam { s32 area; dds3Effect_Blur Blur; } dds3Effect_PartialMultiBlurParam;
typedef struct dds3Effect_DistortionBlurParam {
    u32 number, interval;
    float speed;
    u32 abgr;
    s32 blend;
    float rotate, distortion;
    sdfIVector2 center;
    s32 area, width;
} dds3Effect_DistortionBlurParam;
typedef struct dds3Effect_RippleBlurParam {
    u32 number;
    float speed, interval;
    u32 abgr;
    s32 blend;
    float rotate, power, frequency;
    sdfIVector2 center;
    s32 area;
} dds3Effect_RippleBlurParam;
typedef struct dds3Effect_Filter { u32 abgr; s32 blend; sdfIVector2 xy[2]; } dds3Effect_Filter;
typedef struct dds3Effect_PartialMultiFilterParam {
    s32 area;
    sdfIVector2 center;
    dds3Effect_Filter Filter;
} dds3Effect_PartialMultiFilterParam;

/* sdf3DFogParam_t */
typedef struct sdf3DFogParam { float fogMax, fogMin, fogNear, fogFar; u32 color; } sdf3DFogParam;

/* An event effect's fades (0x551C10: mulblur, distblur, ripblur, blur2, filter2, mfilter). */
typedef struct dds3EffectFade { u16 now, max, abase, atarget, swapnow, swapmax; } dds3EffectFade;
typedef struct dds3EffectFades { dds3EffectFade mulblur, distblur, ripblur, blur2, filter2, mfilter; } dds3EffectFades;

/* The lights', ambient's, fog's and soften / bias fades (0x551BC0). */
typedef struct dds3SceneFades {
    u16 lightrgbnow[4], lightrgbmax[4];
    u16 lightdirnow[4], lightdirmax[3];
    u16 ambientnow, ambientmax, pad;
    u32 ambientbase, ambienttarget;
    u16 fogrgbnow, fogrgbmax, fogparanow, fogparamax;
    u32 fogrgbbase, fogrgbtarget;
    u16 sbnow, sbmax;
    float softenbase, softentarget, biasbase, biastarget;
} dds3SceneFades;


/* datBossPress_t: a boss refight (0x3FA430, 40 entries). */
typedef struct datBossPress { s32 flag, flag2, encid, dbest; } datBossPress;


/* ---- the battle's presentation queue (source/include/nocturne/battle/kouka.hpp) ---- */

typedef struct nbKoukaPacket nbKoukaPacket;
struct nbKoukaPacket {
    s16 startframe, framelength;
    s8 type;
    u8 flag;
    u16 time;
    s32 uniqueid;
    PTR32(nbKoukaPacket) next;
    PTR32(nbKoukaPacket) prev;
    PTR32(nbFormation) form;
    PTR32(datUnitWork) unit;
    PTR32(nbParty) party;
    s32 partyno;
    u32 cuteff;
    u32 data1, data2;
    dds3Vector4 v;
};
typedef struct nbKoukaProcessData {
    PTR32(nbMainProcessData) data;
    s32 packetcnt;
    PTR32(nbKoukaPacket) first;
    PTR32(nbKoukaPacket) last;
} nbKoukaProcessData;

#endif
