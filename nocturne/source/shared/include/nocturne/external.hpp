// Game functions the rewritten modules call but which have not been rewritten
// yet. Each is implemented by a bridge to the legacy recovered C (or, in the
// tests, by deterministic fakes). As modules are rewritten, their functions
// move out of this header into a proper module header.
//
// Signatures use the original names and argument meanings from the HD
// remaster, with typed pointers in place of raw addresses.
#pragma once

#include <cstdint>

#include "nocturne/battle/process.hpp"
#include "nocturne/data/records.hpp"
#include "nocturne/data/types.hpp"
#include "nocturne/ee/float.hpp"
#include "nocturne/effect/boss.hpp"

namespace nocturne {

namespace eff {
void BTLDelete(uint32_t handle);                             // effBTLDelete: frees a battle effect
void BTLCutDelete(uint32_t cut);                             // effBTLCutDelete
void BTLCutDraw(uint32_t cut);                               // effBTLCutDraw (0x16B0F0): a frame of the cut
uint32_t BTLCutCreate(uint32_t effect, uint16_t cutNo, nb::Formation* form, uint32_t stat);   // effBTLCutCreate: a cut of the effect plays (eff::BattleCut)
void BTLSkillSetFormationInfo(int32_t formindex, uint32_t targets);   // effBTLSkillSetFormationInfo
void BTLSkillStart(int32_t skill, int32_t arg);              // (0x16B7A8) "effBTL:Skill Start" (tentative name)
void BTLSkillEnd();                                          // (0x16B850) "effBTL:Skill End" (tentative name)
uint32_t BTLBedName(int32_t skill);                          // (0x1748A0) the skill's .BED file name (a static string)
uint32_t BTLLoad(uint32_t data);                             // (0x16A9C0) a loaded .BED: the effect's handle
void BTLSystemCutDelete(uint32_t cut);                       // (0x1740B8) a cut, and its effect once unused
void BTLPartDelete(uint32_t part);                           // (0x173D78) effBTLPartDelete (tentative)
void OngyokiEffectDelete(uint32_t handle);                   // (0x198298)
void OngyokiEffect2Delete(uint32_t handle);                  // (0x198900)
void OngyokiCloneEffectDelete(uint32_t handle);              // (0x1990F0)
void OngyokiCloneEffect2Delete(uint32_t handle);             // (0x199BC8)
// Ongyo-Ki's effects (effPCPBoss*Create): the effect's handle.
uint32_t OngyokiEffectCreate(const OngyokiEffectParam& param);   // (0x198200)
uint32_t OngyokiEffect2Create(const OngyokiEffect2Param& param); // (0x198868)
uint32_t OngyokiCloneEffectCreate(const OngyokiCloneEffectParam& param); // (0x199000)
uint32_t OngyokiCloneEffect2Create(const OngyokiCloneEffect2Param& param); // (0x199B10)
// ... and their frames' drawing (effPCPBoss*Draw).
void OngyokiEffectDraw(uint32_t handle);                     // (0x1982C8)
void OngyokiEffect2Draw(uint32_t handle);                    // (0x198930)
void OngyokiCloneEffectDraw(uint32_t handle);                // (0x199600)
void OngyokiCloneEffect2Draw(uint32_t handle);               // (0x199C08)
// A hit or ailment effect on a formation (effBTLPart*; tentative names): its
// kind's create, end and draw functions, from the table at 0x31BF00.
uint32_t BTLPartCreate(nb::Formation* form, int32_t kind);  // (0x173CB0) effBTLPartCreate
void BTLPartEnd(uint32_t part);                              // (0x173D28)
void BTLPartDraw(uint32_t part);                             // (0x173DC8)
} // namespace eff

namespace cmp {
int32_t RemoveDevilEx(uint16_t devil);                     // cmpRemoveDevilEx: a demon leaves the stock
} // namespace cmp

namespace nb {
MainProcessData* GetMainProcessData();
UnitWork* GetUnitWorkFromFormindex(int32_t formindex);   // null for an empty slot
Party* GetPartyFromFormindex(int32_t formindex);
UnitWork* GetUnitWorkPointer(MainProcessData& data, Party& party);
// (0x264010) healing's numbers and effects, through the effect library
void MakeHealPackets(int32_t startframe, int32_t uniqueid, Formation* form, int32_t type, int32_t hp, int32_t mp,
                       uint32_t badstat);
// (0x263C00) damage's numbers and effects, through the effect library
void MakeDamagePackets(int32_t startframe, int32_t uniqueid, Formation* form, int32_t type, int32_t hp, int32_t mp,
                      int32_t badstat, int32_t hiteff, int32_t dead, int32_t deadtype, int32_t moji, int32_t animeoff);
// (0x280518) the battle panel shows the analysed unit
void PanelAnalyzeStart();
// (0x280528) the battle panel stops showing the analysed unit
void PanelAnalyzeEnd();
// (0x26CCF0) nbInitNegoProcess: the talks' process between the two slots
void StartTalkProcess(ActionProcessData& a, int32_t pformindex, int32_t eformindex, int32_t negotype, int32_t skill);
// A unit's motions (nbUnitProcess; names by the HD remaster's order, tentative).
int32_t GetMotionActframe(ee::Float speed, Formation& form, int32_t motion);   // (0x24D3A0) frames to the hit
ee::Float GetMotionSpeed(ee::Float speed, Formation& form, int32_t motion);    // (0x24D428)
int32_t GetMotionNo(Formation& form, int32_t motion);                           // (0x24D490)
// The motions' sounds (nbSound; tentative names).
// Packets READY builds (nbMakePacket; tentative names).
void MakeSkillEffectPacket(int32_t startframe, int32_t timer, ActionProcessData& a, Formation& form, int32_t hiteff,
                           int32_t motiontype, int32_t skill);                          // (0x2617A8)
void AddHitEffPacket(int32_t startframe, ActionProcessData& a, Formation& form, int32_t kind);   // (0x262480)
void AddHitEffPacket(int32_t startframe, int32_t uniqueid, Formation& form, int32_t kind);       // ... by the packets' owner
void MakeTargetPacket(ee::Float speed, int32_t start, ActionProcessData& a, Formation& form, uint32_t targets,
                      int32_t kind);                                                    // (0x2648C0)
void SetWaitMotion(Formation& form, int32_t motion, ee::Float speed);               // (0x24D238)
void SetUnitMotion(Formation& form, int32_t motion, int32_t loop, ee::Float speed); // (0x24CFF8)
// The battle panel (nbPanelProcess); names by the HD remaster's order, tentative.
void PanelAllShow();            // (0x279C30) the panel, its press gauge and auto marker
void PanelPressGaugeShow();     // (0x27C2C0)
void PanelStockSelectInit();    // (0x27FA98) the stock list for choosing a demon
void PanelStockEnd();           // (0x27FA78)
// (0x2584C8) the turn order after an action
void UpdateOrder();
// (0x27FD18) the stock panel's selection (sw 0: keep it as it is)
uint32_t PanelStockSelect(MainProcessData& data, int32_t sw);
} // namespace nb

// Streamed voice (ADPCM) for movies and events.
namespace movie {
bool CheckAdpcmFlag();   // (0x2C2178) a stream is playing
void StopAdpcm();        // (0x2C2180)
} // namespace movie

namespace nb {
// (0x247ED8) queues an action to run next (counters, talks, death scripts)
void PushAction(int32_t type, int32_t from, int32_t to, int32_t data);
// (0x263918) a death's visuals, through the effect library
void MakeDeathVisualPackets(int32_t startframe, int32_t uniqueid, Formation* form, int32_t deadtype, int32_t deadpcm);
// (0x282200) the battle panel's input on or off
void PanelSetEnabled(bool enabled);
// The panel's drawing (nbPanelProcess; tentative names): where in the
// display list, the primitive's settings, alpha blending, and a textured
// rectangle (screen x, y, w, h from texture u, v, tw, th; RGBA).
void PanelSetOrderingOffset(int32_t offset);   // (0x2797B0)
void PanelSetPrimitive(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f, int32_t g, int32_t h);   // (0x279868)
void PanelSetAlpha(int32_t mode);              // (0x279980)
void PanelDrawTexturedRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t u, int32_t v, int32_t tw, int32_t th,
                           uint32_t color, uint32_t texture);   // (0x279A88)
// (0x280538) the panel's Analyze page shows this unit
void PanelSetAnalyzeUnit(UnitWork* unit);
void SetFormRot(Formation& form, const Vec4& rot);   // nbSetFormRot
void PanelAutoHide();                  // nbPanelAutoHide (0x279C58)
void PanelHide();                      // (0x281E28) tentative name
void CameraScriptSet1Shot(Formation* form);    // nbCameraScriptSet1Shot
// The talks' debug menu (NegoDebugDraw, NegoDebugSelectDraw, NegoDebug), shown
// while battle stat 0x400000 is set; NegoDebug is nonzero when it closes.
void TalkDebugDraw(uint32_t talk);
void TalkDebugSelectDraw(uint32_t talk);
int32_t TalkDebug(uint32_t talk);
void CameraScriptSetBougai(Formation* form);   // nbCameraScriptSetBougai
// nbReturnUnit (0x24D980): a unit leaves the field for the stock (dead: it died)
void ReturnUnit(int32_t partyno, int32_t lost, int32_t dead);
// nbSetUnitMove (0x24DD10): a party member walks toward `pos`; nbSetUnitHomeMove (0x24DE40) back home
void MoveToTarget(ee::Float speed, int32_t partyno, const Vec4* pos);
void MoveHome(ee::Float speed, int32_t partyno);
// (0x28D1B8) the unit's voice sound (tentative name)
// (0x1E3700, 0x1E37E8) a unit model's colour / alpha moves to `value` over
// `frames` (0: at once); tentative names
void UnitSetColor(uint32_t unit, int32_t frames, uint32_t color);
void UnitSetAlpha(uint32_t unit, int32_t frames, uint32_t alpha);
// (0x1E3B78) a unit model's two motion words at +0xBA, +0xBC (meaning unknown)
void UnitSetMotionWords(uint32_t unit, int16_t a, int16_t b);
void SetPartyFormation(MainProcessData& data, uint32_t group);   // nbSetPartyFormation (0x28A340)
void SetEnemyFormation(MainProcessData& data);                   // nbSetEnemyFormation (0x28A758)
// The damage motions: nbSetDamage (0x24DF78; week: the hit was on a
// weakness), nbSetDamage2 (0x24E020, a light one), nbSetBadstatMotion
// (0x24E040, an ailment's), nbSetBadstatMotion2 (0x24E0E8).
void SetDamage(Formation& form, ee::Float range, int32_t week);
void SetDamage2(Formation& form, ee::Float range);
void SetBadstatMotion(Formation& form, int32_t type, ee::Float range);
void SetBadstatMotion2(Formation& form);
// nbSummonUnit (0x24D8C0): a summoned devil appears: side 0 the player's, from stock `stockno`
void SummonUnit(int32_t side, int32_t stockno, int32_t formindex);
void AddToOrder(int32_t formindex);   // (0x258048) the turn order takes in a new unit
} // namespace nb

// The script VM (flowscript), as seen by script commands.
// Textures.
namespace tex {
uint32_t Load(uint32_t name);              // (0x1CB0D8) load a .TMX file into a texture
void DeferredRelease(uint32_t texture);    // ps2TextureDeferredRelease

// A rectangle of pixels to send to video memory (ps2TextureQueueUpload).
struct UploadRecord {
    uint32_t pixels;
    uint32_t unknown_04;        // not set by the font engine
    uint8_t flags;              // 2: free the pixels once sent
    uint8_t psm;                // pixel format (20: 4 bits per pixel)
    uint16_t width;             // of the destination, in pixels
    uint32_t base;              // the destination, in words
    uint16_t x, y, w, h;
};
static_assert(sizeof(UploadRecord) == 24);
void QueueUpload(const UploadRecord& record);
} // namespace tex

namespace snd {
void Play(int32_t sound, int32_t volume, int32_t pan);   // ps2SoundPlay
bool BankReady(uint32_t bank);                            // ps2SoundBankStatus: the bank is in sound memory
int32_t BankStatus(uint32_t bank);                        // ... 0 not, 1 in sound memory, 2 on its way
void SelectOutput(int32_t piece);                         // (0x2C20F0, legacy name) a sound command's output for a piece
void SelectChannel(int32_t value);                        // (0x2C1E70, legacy name)
void VolumeHalfDown();   // (0x2C20A0) the music at half volume
void VolumeHalfUp();     // (0x2C20C8) ... back up
void StopEffectMidi(uint32_t sound);                      // (0x2C1730) a playing effect's music stops
void SetBankSource(uint32_t data, int32_t size);          // (0x2C1DB0) send a bank to sound memory
void PlayMidi(int32_t midi);                              // (0x2C1670) a piece of music
void FadeOutMidi(int32_t midi);                           // (0x2C2070) ... fading out
void EnsureBank(uint32_t bank);                           // ps2SoundEnsureBank: a bank on its way to sound memory
} // namespace snd

// Movable memory blocks (sdfMemHandle).
namespace mem {
uint32_t PoolAllocate(int32_t size);      // ps2PoolAllocate: a small block
void PoolRelease(uint32_t block);         // ps2PoolRelease
uint32_t HandleAllocate(int32_t size);
uint32_t HandleAcquirePointer(uint32_t handle);
void HandleFree(uint32_t handle);
} // namespace mem

namespace file {
uint32_t Load(uint32_t path);   // sdfDevLoadFile: a whole file in a new memory handle
uint32_t Load(uint32_t path, uint32_t* data);   // ... and where it is
uint32_t Request(uint32_t path);        // (0x296A68) start loading a file: its request
bool CheckEnd(uint32_t request);        // fileCheckEnd: loaded
uint32_t GetMemHandle(uint32_t request);   // fileGetMemHandle
int32_t GetLoadSize(uint32_t request);     // fileGetLoadSize
void RequestRelease(uint32_t request);     // ps2ResourceRequestRelease
void PacRequestFree(uint32_t request);     // ps2ResourcePacRequestFree
void WaitIdle();                           // (0x296B88) the loader pumped until no request is pending
} // namespace file

namespace pac {
// Turn the offsets listed in a relocation table into addresses (base + offset).
void RelocatePointers(uint32_t destination, uint32_t base, uint32_t table, uint32_t bytes);
} // namespace pac

namespace fr {
struct Request;
uint32_t DrawFontEx2(Request& font, int32_t mode, int32_t ot);   // frDrawFontEx2 (0x1C7E38): a request drawn
} // namespace fr

namespace guest {
void callFunction(uint32_t entry);   // call original code through a function pointer
// An action state not rewritten yet: its SetAction_* / CheckAction_* by address.
void callActionSet(uint32_t entry, uint32_t action);
int32_t callActionCheck(uint32_t entry, uint32_t action);
// A presentation packet's player not rewritten yet (nbKoukaProcess), by address.
void callEffectPlayer(uint32_t entry, uint32_t queue, uint32_t packet);
// A talk step's flow function not rewritten yet, by address: its result.
int32_t callTalkStep(uint32_t entry, uint32_t talk);
// Original code not rewritten yet, by address, with up to four arguments:
// its result.
uint32_t callOriginal(uint32_t entry, uint32_t a0 = 0, uint32_t a1 = 0, uint32_t a2 = 0, uint32_t a3 = 0);
// A packet maker not rewritten yet (it moves a unit with VU0 vector math),
// by address: (startframe, uniqueid, the formation, the one it faces).
int32_t callMovePackets(uint32_t entry, int32_t startframe, int32_t uniqueid, uint32_t form, uint32_t target);
int32_t callCommand(uint32_t entry); // a script command not rewritten yet
} // namespace guest

// Engine process table.
namespace dds3 {
// dds3ProcessID_t, as far as the rewrite reads it.
struct ProcessID {
    uint8_t unknown_00[0x20];
    int32_t priority;
};
uint32_t SearchProcessName(uint32_t name);   // name: address of a C string
uint32_t GetProcessData(uint32_t process);   // the process's data, as an address
// Starts a process: `processfunc` runs every frame, `shutdownfunc` at its
// end (both original code addresses).
uint32_t StartProcess(uint32_t name, int32_t priority, int32_t startdelay, int32_t shutdowndelay,
                      uint32_t processfunc, uint32_t shutdownfunc, uint32_t data);
int32_t GetFrameIndex();   // which of the two display buffers is being built (0x100418)
void SetProcessData(uint32_t process, uint32_t data);
void KillProcess(uint32_t process, int32_t delay);
bool ExistProcess(uint32_t process);
void LinkProcess(uint32_t parent, uint32_t process);   // makes `process` the last child of `parent`
int32_t GetRunTime(uint32_t process);
void FadeIn(int32_t r, int32_t g, int32_t b, int32_t frames);    // from the color
void FadeOut(int32_t r, int32_t g, int32_t b, int32_t frames);   // to the color
void FadeIn2(int32_t frames);    // dds3FadeIn2: back from the last fade's color
void ObjectBaseOnFlag(uint32_t basic, uint32_t flag);    // dds3ObjectBaseOnFlag: an object's control flags set
void ObjectBaseOffFlag(uint32_t basic, uint32_t flag);   // dds3ObjectBaseOffFlag: ... cleared
void SetPosPoseSet(uint32_t basic, uint32_t pos);        // dds3SetPosPoseSet: an object placed
void PadAct(uint32_t mode, uint8_t pow, uint32_t frame);         // dds3PadAct: the pad's vibration
} // namespace dds3

namespace evt {
bool BitCheck(int32_t bit);
void BitOn(int32_t bit);
void BitOff(int32_t bit);
uint32_t GetAgeOfMoon();      // 0..15, 0 = new, 8 = full Kagutsuchi
int32_t GetAgeOfMoon16();     // the phase in sixteenths (tentative)
void SetAgeOfMoon(int32_t age);
} // namespace evt

namespace sdf {
int32_t GetRandInt(int32_t limit);   // uniform in [0, limit) from the default RNG
uint32_t GetRand();                  // the raw 32-bit value
ee::Float GetRandFloat();            // uniform in [0, 1)
} // namespace sdf

// Original debug printf. Messages are identified by the address of their
// format string so a host build can print the original Japanese text.
namespace diag {
enum class Message : uint32_t {
    Critical         = 0x005449c0, // "critical p:%d, z = %d, a = %d"
    PhysicalHitRate  = 0x005449e0, // 物理ヒット率 = %d   (physical hit rate)
    MagicHitRate     = 0x005449f8, // 魔法ヒット率 = %d   (magic hit rate)
    StoneShatterRate = 0x00544bf8, // 石化一撃確率 = %d   (stone one-hit chance)
    AilmentRecovery  = 0x00544c10, // バットステータス回復確率 = %d
    FirstStrike      = 0x00544d70, // 先制率 Plv, Elv, Tbl, z, rnd
    BackAttack       = 0x00544da8, // バックアタック確率 X, Y, B, rand
    EscapeRate       = 0x00544de0, // 逃走率 = %d
    ConsecutiveRate  = 0x00544df0, // "renzoku ritu = %d, index = %d"
    Miss             = 0x00551140, // "MISS!!"
    AttackRatio      = 0x00544d00, // "atkritu = %f"
    DefenseRatio     = 0x00544d10, // "defritu = %f"
    MagicHeal        = 0x00544d30, // 回復 waza = %d, atkritu = %f 回復値=%d (heal: power, ratio, amount)
    StingerVsBoss    = 0x00544b48, // "DANTE SUTING BOSS NG..."
    CurseKillBlocked = 0x00544b68, // "SIBAE JYUSATU TAISEI ARI NG..." (target resists Death)
    PestilenceNoPoison = 0x00544b88, // "PESTO POISON NASI NG..."
    AilmentChance    = 0x00544ba8, // バッドステータス反映確率 waza:%d aisyo:%d ritu:%d rnd:%d
    AilmentCureRate  = 0x00544be8, // "bad ritu:%f"
    ResetLevel       = 0x00543188, // "YAMI-B Lv:%d"
    ResetExp         = 0x00543198, // "YAMI-B Exp:%d"
    FusionAccident   = 0x0053caf8, // "Combione accident!!!..." (passed the accident type)
    CompendiumFull   = 0x0053d7e8, // "****** FATAL!! The encyclopedia record is bound to burst!!!"
    AiActionTable    = 0x00545830, // "Koukatbl = %d" (the action chosen)
    DidPhysical      = 0x00544070, // 物理攻撃を行った (made a physical attack): an action's stat bits 0x10000..
    DidMagicAttack   = 0x00544088, // 魔法攻撃を行った (made a magic attack)
    DidHeal          = 0x005440a0, // 回復を行った (healed)
    DidMagic         = 0x005440b0, // 魔法を使用した (used magic)
    DidItem          = 0x005440c0, // アイテムを使用した (used an item)
    DidSummon        = 0x005440d8, // 召喚を行った (summoned)
    AilmentWeight          = 0x00545d40, // BAD行動確率 type:%d ritu:%d (an ailment action's weight)
    AdpcmPlaying     = 0x005440e8, // AD-PCM再生中! (a streamed voice is playing)
    SkillSkill       = 0x00546138, // すきるすきる＝%d ("skill skill = %d", a menu skill checked)
    DeadFormindex    = 0x00544030, // "dead formindex = %d!!"
    AllFrame         = 0x00544048, // "allframe %d" (an action's length)
    PrevCommind      = 0x00544058, // "prev commind = %d"
    Returning        = 0x00544020, // 帰還します (a devil returns to the stock)
    AhrimanCounter   = 0x00543880, // アーリマンカウンター発生!!! (Ahriman counters)
    Counter          = 0x005438c0, // カウンター発生!!! (a counter)
    BegForLifeSide       = 0x005438d8, // "inoti party = %d (%X)" (an enemy begs for its life)
    AskToJoinSide       = 0x005438f0, // "binjo party = %d" (an enemy asks to join)
    EscapeErrParty   = 0x00543908, // "escape err party" (a free hit after a failed escape)
    TalkResult       = 0x00543fb8, // "nego result = %d"
    HitHp            = 0x00543780, // "HP damage = %d, kaifuku = %d" (a hit's damage and healing)
    HitMp            = 0x005437a0, // "MP damage = %d, kaifuku = %d"
    HitMiss          = 0x005437c0, // "MISS!!!" (a hit that did nothing)
    HitCount         = 0x005437f8, // 攻撃回数=%d, select = 0x%08X (hits; EUC-JP)
    BedName          = 0x00543b30, // "name [%d]:%s" (a skill's effect file)
    MidiName         = 0x00543b58, // "MIDI :%s" (its sound file)
    ActTime          = 0x00543b68, // "acttime = %d" (frames to the hit)
    SelectBits       = 0x00543b78, // "select %d -> %08X"
    MotionSoundWait        = 0x00543ce0, // "mot se wait(1).."
    SeSize           = 0x00543cf8, // "se size = %d"
    LoadSeOrBed      = 0x00543d18, // "load se or bed"
    SeOk             = 0x00543d40, // "se ok!! [%08X]"
    SeWait2          = 0x00543d50, // "se wait(2).."
    BedOk            = 0x00543d70, // "bed ok!!"
    LoadBed          = 0x00543d80, // "load bed"
    TalkSides        = 0x00543fa8, // "NEGO p:%d e:%d" (the talks' two slots)
    ItemNo           = 0x005439f8, // "item no = %d" (an item chosen in the menu)
    SkillNo          = 0x00543a08, // "skill no = %d" (the skill it uses)
    AiTable          = 0x00545840, // "AItbl = %d"
    AiNoSkill        = 0x005457d8, // "no skill"
    AiNoTarget       = 0x005457e8, // "taisyo nashi!!!" (no target)
    SkillRewritten   = 0x00544170, // スキル書き換え!! (normal attack data rewritten)
    NoMessagePage    = 0x00535a80, // "itfMesMngRequestMessage() escape 1" (a message with no pages)
    NotASelection    = 0x00535aa8, // "itfMesMngRequestSelect() - Invalid Type : %d"
    NameTranslate    = 0x00535998, // "NAME[%d] : Translate." (an entered name's glyphs loaded)
    NameRestore      = 0x005359b0, // "NAME[%d] : Restore." (and freed)
    ProcedureStart   = 0x0052e270, // "procedure start <%s>"
    ProcedureEnd     = 0x0052e2b8, // "procedure end <%s>"
    ScriptsBefore    = 0x0052e2e0, // "before = %d" (scripts running)
    ScriptRelease    = 0x0052e2f0, // "scrAllReleaseScript <%s>"
    ScriptKillProcess = 0x0052e310, // "dds3KillProcess"
    ScriptReleaseWork = 0x0052e328, // "scrReleaseScript"
    ScriptsAfter     = 0x0052e340, // "after = %d"
    ScriptRunWithoutProcess = 0x0052f5e8, // SCR_RUN from a script without a process (EUC-JP)
    ScriptPut        = 0x0052f588, // "put -> %d"
    ScriptPuts       = 0x0052f5a8, // "puts -> %s"
    CutCreate        = 0x00544518, // "cutcreate 3" (a skill effect packet's cut starts)
    NoInvoker        = 0x00532f90, // "effBTL:InvokeForm == NULL ****** !!"
    SkillState       = 0x00532f20, // "effBTL:Set Stat[%X]" (what a skill did, for its effect)
    SkillMotionCut   = 0x00543e10, // "mot %d, cut %d" (the first cut's hit and end frames)
    SkillEffectResult = 0x00543e20, // スキル効果タイプ = %d (how the skill lands on a target)
    SkillCut3Frames  = 0x00543e38, // "cut3 mottime:%d  endtime:%d" (the second cut's)
    SkillTotalDamage = 0x00543e58, // トータルダメージ HP=%d, MP=%d
    SkillEndFrame    = 0x00543e78, // "skill kouka end time = %d"
    SkillFreeFrame   = 0x00543e98, // "skill kouka unlock time = %d"
    NoBuffEffect     = 0x00543eb8, // "Kereijyou Koukaga nai ---" (a buff with nothing left to do)
    SpeakUpLevels    = 0x00545218, // "plv = %d, elv = %d" (the same, for a demon speaking up)
    TalkDrain        = 0x005451f8, // "drain = %d" (what a demon drains)
    TalkDrainedHp    = 0x00545208, // "pwork hp = %d" (the talker's HP after)
    BattleEvent      = 0x00545db0, // イベント起動 -> %d (an event starts)
    TalkRequest      = 0x00544ff0, // "request = %d" (what a demon asks for)
    TalkSelect       = 0x00545018, // "select = %d" (the answer to its demand)
    TalkHelper       = 0x00545068, // 味方スキル発動! p[%d] id[%04X] (a helper's talk skill)
    TalkLevels       = 0x005450e0, // "plv = %d, elv = %d" (the Demi-fiend's and the demon's levels)
    TalkMessageEnd   = 0x00544f10, // "msg end" (a talk step's message read)
    InfoChosen       = 0x00544e48, // "select info usemestype = %d mesno =%d" (nbGetInfoMsg)
    InfoCounts       = 0x00544e70, // "normal_mesno = %d jouken_mesno = %d"
    SkillPress       = 0x00543ee8, // "press %f" (the press turns the action used)
    MotionMidi       = 0x00545bd0, // "MIDI=0x%08X" (a motion's sound bank)
    BgmStop          = 0x00545ce0, // "nbBgmStop(%d,%d)"
    EncounterRate    = 0x00545ba0, // エンカウント率 %d/%d (the encounter threshold rolled, and its base)
    UnitLoadTime     = 0x00545cf8, // ">>> UNIT LOAD TIME = %d frame <<<"
};
// Integer arguments are passed sign-extended; %f arguments are ee::Double bits.
void print(Message message, int64_t a = 0, int64_t b = 0, int64_t c = 0, int64_t d = 0, int64_t e = 0);
} // namespace diag

// The original code divides with a trap on zero (MIPS BREAK 7).
[[noreturn]] void divideByZeroTrap();

} // namespace nocturne
