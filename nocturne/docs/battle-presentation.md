# How battle actions are shown: the kouka queue

An action's effects are computed first (battle-mechanics.md) and then
shown by a queue of "kouka" (effect) packets. Each packet starts at a frame
of the action's timeline and lasts a number of frames: a motion, a move or
turn, a colour or fade on a unit, a damage number, a word ("Weak", "Miss"),
a sound, the press turn icons, a death. The kouka process plays the queue
every frame (below); the builders here only queue packets.

Function and field names here are the original (HD remaster) ones, for
looking them up in Ghidra. The rewrite uses English names (the queue is
`nb::EffectQueue` in `battle/kouka.cpp`, `SetAllPacket` is `queueHitResult`);
`reference/function-map.tsv` maps each original to its rewrite.

Source: `source/shared/src/battle/kouka.cpp` (original units `nbKoukaProcess` and
`nbMakePacket`). Tested against the original instructions
(`kouka_tests.cpp`).

## Packets

A packet (`nbKoukaPacket_t`, 0x40 bytes from the pool): `startframe`,
`framelength`, `type`, `flag`, `time`, `uniqueid` (the action it belongs
to), the list links, the unit's formation slot or party, `partyno`, an
effect handle, two parameter words and a vector. The queue
(`nbKoukaProcessData_t`) is the kouka process's data; the main process
data names that process (`KoukaProcessID`).

The builders are named after the packet they queue (`nbAddDmgMotKoukaPacket`:
a hit reaction). Some details:

- A new damage number or word on the same unit and action cuts the earlier
  one short where the new one starts.
- A sound isn't queued again if the same sound starts within 5 frames
  before (three sound channels, types 0x19, 0x1C, 0x1D).
- A dodge (`Sake`) steps 0.9 of the unit's radius, at most 100, and plays
  sound 0x10010.
- A death that starts an event (`nbAddDeadEventKoukaPacket`) also ends the
  battle (endtype 7); the event number it hands the main process is the
  packet's still-empty parameter, 0 — the event number itself goes into
  the packet.
- Death: a unit whose death runs a script or starts an event (the devil
  AI table's `deadscriptid` / `deadeventno`) stays on the field, as does
  the Demi-fiend, unless the caller insists.

Packets leave the queue through `DelKoukaPacket`, which also frees what
they started: a skill's cut (types 0x00, 0x15, 0x2B; 0x2B also its battle
effect, 0x1A through the effect system's reference count), a hit effect's
part (type 0x0F, kinds 0..10 but 3) and Ongyo-Ki's clones (0x27..0x2A).
`nbDelAllKoukaPacketType`, `nbDelAllMojiNumEffectKoukaPacket` (numbers and
words over one slot) and 0x25EC58 (an action's packets) remove several.

## Playing the queue (`nbKoukaProcess`)

The kouka process (`nb_kouka`, priority 0x2B08, a child of the battle's
process) runs `nbKoukaProcess1` every frame. Each packet first counts its
`startframe` down to 0; then its player runs once a frame and its
`framelength` counts down (flag 1 holds the length, flag 2 pauses the
packet), and once the length is below 0 the packet is deleted, so a packet
of length 0 plays once. Packets on a unit (skill effects, colours, motions,
damage motions, summons, dodges, flights, buffs, model shows) wait while the
unit's formation is busy (its `flag` bits 0..2). Each type has its player
(`Run*Kouka`, in the HD remaster's order at 0x25EFD0..0x260F20); the
simple ones:

- the HP or MP change (`nbAddHpMp`, not while stat 0x20000 holds the
  units' state), the ailment set or cleared, the buffs applied, the status
  line and the skill's name on the help line, the Analyze page;
- a hit stop: the game stops 12 frames (`dds3Stop`), then runs at a third
  of its speed for 24 (`dds3SlowOn(3, 24)`);
- a dodge: the formation steps back (movement type 2) by `r` x 0.9 at 0.3;
- an ailment's effect on the unit replaced or ended (`effBTLPart`, the
  formation's anime bit 0x100), a hit effect's frame;
- a unit returning to the stock (`0x24D980`; in encounter 0x10F this marks
  the battle, stat 0x2000), a move or turn toward a target or home;
- a death's event: the queued actions are dropped and the event noted for
  the battle (`eventno`);
- Flare's charge: Kagutsuchi moves two sixteenths on;
- a passive that fired cuts its action's first cut short: 12 more frames;
- the pad's vibration, the skill's field colour, the stock panel's fade;
- a unit's colour or alpha moving to a value over some frames, or back to
  its own (`Formation` +0x9c);
- the press gauge (kept within 0..1) and the press turn icons (never below
  0; on the player's turn the blinking icons lost are counted for an
  event boss, `d31_press_total`), not while stat 0x10000 holds;
- an ailment's motion ending: the unit stands again at its saved speed;
- the screen fading out to black or white, or back in;
- a skill effect's cut: created on the packet's first frame
  (`effBTLCutCreate`), then drawn each frame (`effBTLCutDraw`; type 0x1A's
  is a system cut);
- a damage motion: a stagger (`nbSetDamage`, weak hits harder), a light
  one (`nbSetDamage2`), or an ailment's motion (`nbSetBadstatMotion`;
  ailments 4, 8, 0x20..0x200 stagger and hold, 0x100 at half speed; -1
  stands the unit up again);
- a motion (motion 0x17 loops back and forth) or a skill's motion with its
  ending (once, hold, or hold and clear the model's motion words);
- a summon: the devil appears (`nbSummonUnit`), its side is laid out again
  (`nbSetPlayerFormation` / `nbSetEnemyFormation`) and on its side's turn
  it joins the turn order;
- a sound effect: played, played once its bank is in (0x1C), or waited for
  a frame at a time (0x1D); sounds 0x10008/0x10009 stop the event boss's
  music for a repelled skill 0x107 or 0x113.

`nbDelUnEventKoukaPacket` empties the queue between scenes but for sounds,
voices and fades: units on their way back arrive, and a skill's colour
ends. Not rewritten yet (run as original code): turns, damage numbers
and words (they need the VU0's vector math), a devil's voice, and flight
(it reloads the unit's model).

## Press turns

`nbMakeNewPressPacket` queues how a result changes the press turn icons
(full ones `press4_p`, blinking ones `press4_ten`):

| Result type | Change |
|---|---|
| 0, 8..12 | one blinking icon; a full one too unless there are fewer full than blinking |
| 1 | a blinking icon if fewer full than blinking, else a full one |
| 2, 3 | a full icon, or a blinking one if no full ones are left |
| 4, 5 | two blinking icons, and full ones to match |
| 6, 7, 13, 14 | all (10 of each) |
| 15, 16, 17 | 2, 4 or 3 blinking icons gained |

Neither count goes above 8.

## Names

Packet types and builders without an HD name: type 4 (played with the
turn, `nbAddHomeRotKoukaPacket`), 0x20 (with the motion stop,
`nbAddMotionStopPacket`), 0x36 (with the skill colour,
`nbAddSkillColorPacket`) and a third sound channel (`nbAddSePacket3`).

Not rewritten yet: the builders that create effects through the effect
library (skill and passive effects, hit effects), the
damage, healing and death-visual compositions built on them, removing
packets (which frees those effects) and the kouka process itself.

## The action process and its time list

Each action runs as a process (`nbActionProcess`, `source/shared/src/battle/action.cpp`)
through a state machine: a table at 0x3FA7C0 of `SetAction_*` (entering a
state) and `CheckAction_*` (each frame; true when done, after choosing the
next state) pairs. Fixed transitions: AI → READY (7), INVISIBLE → CHECK1 (18),
CHECK3 → ATO (21, once the action's packets are all played), ATO → END
(22, freeing the skill's effect).

- **COMM** (1) opens the command menu (`nbCommSelProcess`, below) with
  the battle panel and press gauge, and in a manual battle first removes
  the queued FORMONOFF packets; in an auto battle (BattleStat 0x40) the
  unit chooses by itself. Its check waits for the menu: attack and talk go
  to TARSEL (5); a skill or item too, or to **STKSEL** (6) when it aims at
  the stock (target area bit 1 without 4 or 8, the party not flagged 2 or
  4); summoning skills and the summon command first prepare the summon
  slots (`nbSetPlayerSummonFormation`, `nbSetEnemySummonFormation`).
  Escape, pass, return and command 8 go straight to READY and close the
  menu. A skill that can't do anything (`nbCheckBattleSkillError1`) shows
  why and keeps the menu open. With the debug pad shortcuts (0x54E824),
  two button pairs win the battle (`DokodemoPoa`) or force a press
  (`KyouseiPress`) at once.
- **TARSEL** (5) waits for the target cursor. A target chosen for a skill
  or item that would do nothing there (`nbCheckBattleSkillError2`) shows
  why and keeps the cursor; otherwise the targets go in `select` and the
  action to READY. Cancelling returns to COMM by setting the state
  directly (not through `nbActionSetSeq`), so the menu stays as it was.
  **STKSEL** (6) does the same with the battle panel's stock list: the
  chosen demon is target bit 16 + its stock index (static 0x551120 holds
  the answer: -1 none yet, -2 cancelled).
- **READY** (7) sets up the chosen command. Once per turn a panicked unit
  may act by its ailment instead, and a cursed one, one time in four, goes
  to BAD. A skill that can't be used (`nbCheckSkillUse`: muted, not enough
  HP or MP) or a command with no target sets `runerr` and a status line;
  an item used up leaves the stock. Skills, items and summons start loading
  their effect file (`.BED`, if the skill's hit-effect byte 3 is set) and
  sound bank (`/sound/MIDIxxxx.SMG`, bank ID `(skill + 0x200) << 16`). The
  unit's motion starts (attack: motion type 3; skill: the skill's
  hit-effect byte 0; item 0x19; summon 0x18), at triple speed for an auto
  battle's attacks (option 2 off), a motion that ends by fading the unit
  out queuing the fade. `timer` is the motion's frames to the hit (talks:
  35). HP and MP costs are paid by packets at frame 1, except a skill with
  flag 8, which takes all HP 60 frames after the hit (83 for skills 0x73
  and 0x74); then the
  effect, target and hit-effect packets, the other side's guard (buff
  0x10) ending, the battle panel, and the help line's name for the action
  (four bosses' skill 0xE2 has its own name; skill 0xF7 shows none).
  Its check waits for the loads in turn (`seqcnt` 0..3: the motion's sound
  bank, the skill's sound file and bank, the effect file) and for the hit's
  frame, then goes on by command: SKILL (8), ESCAPE (13), WAIT (12), NEGO
  (9) or RETURN (14), showing a pending status line.
- **SKILL** (8) builds the action's result packets, hit by hit, in the order
  `GetKoukaList` gives: a formation index and a hit count per target, the
  targets already down or leaving left out. A random-target skill
  (`targetrandom` 1) spreads its `targetcntmin..max` hits at random, never
  on the same target twice in a row and at most one or two more than there
  are targets on any one; skills 0x9E and 0x9F hit once the target with the
  lowest share of its HP; the others hit each target the full count, in
  slot order, in reverse or shuffled by their hit-effect kind (byte 1:
  0..7, 8..11, 12..15; skill 0xCC hits in reverse on the enemies' turn).
  `SetAllPacket` builds one target's result from the skill's resolution
  (`nbGetKoukaType`): a hit (0) deals its HP and MP effect `cnt` times,
  each hit's ratio shrinking by the skill's reduction rate; a repel (1)
  turns the hit on the user, who may null its ailment; a drain (2) heals the
  target by what it would have lost; a null (3) shows "Null". Ailments
  0x1000, 0x2000 and 0x4000 (skill 0x110 only) instead leave the target
  a half, a quarter or a tenth of its HP. Never Yield, then Endure, leave a killed unit 1 HP
  (once each per battle, `nbSetKuisibariStop`); a stoned unit shatters. A hit
  that does nothing shows "Miss" and ends the hits. After the hits: healing
  and cures as one packet, the buff shown, HP and MP drained back to the
  user, a counter for a physical hit landed, and the press cost: a normal
  hit one icon, a critical or weak hit half (types 3 and 2); an enemy's
  repel or drain all four, a null two (types 6, 7, 5).

  The state itself (`SetAction_SKILL`): the skill's effect plays its first
  cut on the user (`effBTLCutCreate`, cut 1), who is busy until the cut
  ends (10 frames with no effect, a third of that when fast); a motion that
  ends by fading (end type 2) keeps the user busy to the fade. Then per
  target, from the later of its own free frame and the running start:
  `nbGetKoukaType`'s result (an action of type 4 can't be repelled or
  drained, only nulled), the effect's second cut on the target (the result
  waits for the cut's hit, `effBTLGetMotionChangeFrame`; first 16 targets
  only, and not for repels or drains), the result packets by kind (0..3
  `SetAllPacket`, 4 dodge, 5 miss, 6 summon, 7 Analyze, 8 Trafuri, 9 thrown
  Macca, 10 an enemy escapes, 11 Ongyo-Ki found, 12 Aurora, 13 an extra
  press icon, 14 Flare's charge), and the next target's start a little
  later by the skill's hit spacing (hit-effect byte 1: +5, +8, +10 or +1
  frames). A physical skill ends the user's guard counter 0xF; a null
  spends the target's Ice, Fire, Expel or Death guard (counters 9, 10, 12,
  11). After the targets: Drain Attack (0x12E) heals an attack's user a
  quarter of the HP and MP it took (`datSpecialSkill` 6: n, m); skills
  0x11E and 0x109 heal the user a share of its maximum HP or MP; the effect
  learns what happened (`effBTLSkillSetState`: repelled 4, drained 8,
  nulled 0x10, dodged 0x20, missed 0x40); the user's own time ends at 0.8
  of the action's; a user the skill killed dies; Ahriman may counter; the
  passive that fired (299..302) is named and the skill's status line
  queued (twenty skills have their own; Pierce's is 100; a buff with
  nothing left to change, 0x44; on the other side's turn, the paired
  message). The first cut is drawn until the end, with its sound, unless
  every result hid it (then the camera takes the cut's state); then the
  press turns, and a hit stop when the turn's last icon goes (event bit
  0xC09).
- **AI** (2) clears the unit's command and runs the table AI
  (enemy-ai.md); **AISCR** (3) runs the devil's AI script instead
  (`DevilAI::scriptid`). The script runs as a child process of the battle
  (`nbInitAiScript`, one priority step ahead of it, `AiScriptProcessID`);
  once it ends, the action goes to READY, or to the talks' result (10,
  NEGORESULT) when the script started talks (`negoresult`). That this
  matches state 10 supports the tentative numbering.
- **BAD** (4) shows the battle panel and press gauge, then checks the
  unit's ailment at the start of its turn. Shock,
  freeze, sleep, bind and stone cost the turn (the press turn icons change
  as for a pass); shock and freeze then wear off, and sleep restores an
  eighth of HP and MP. The unit is busy for 30 frames and the action goes
  to CHECK1. A charmed or panicked unit, or a cursed one with no other
  ailment, acts by the ailment AI (enemy-ai.md) and goes to **BADWAIT**
  (11), which shows the status line at frame 5 and then waits (until frame
  31 for a lost turn or the curse's damage; else until the line is gone or
  frame 41) before READY. Any other unit goes to NON (0), as entering a
  state clears the next one (`nbActionSetSeq`), and chooses its command as
  usual.
- The camera: BADWAIT asks for camera state COMMAND_BAD, or ENEMY_BAD when
  the battle's stat bit 8 is set, which by this and the status line's
  second message forms marks the enemies' turn. The camera states are named
  by debug strings in their table (0x320C50; `battle/camera.hpp`).
- **DEADSCRIPT** (19) runs a dying unit's script (the procedure in
  `adata`); when it ends, the unit fades out and leaves the field (a return
  packet at frame 25, the unit busy for 30 frames) and the action goes to
  CHECK1.
- **END** (22) prints debug messages for what the action did: stat bits
  0x10000 .. 0x200000 are a physical attack, a magic attack, healing, magic,
  an item and a summon.
- **WAIT** (12): a pass costs half a press turn icon; a turn lost to an
  ailment a whole one; a cursed unit takes 15% of its maximum HP
  (`SetDamagePacket`, which Endure can survive). **ESCAPE** (13) counts the
  attempt and uses all the press turns; a success ends the battle (endtype
  3) and fades the screen to white at frame 30, a failure may give an awake
  enemy a free action. **RETURN** (14) sends a devil back to the stock for
  half an icon. **INVISIBLE** (15) does nothing. Each then goes to CHECK1.
- **CHECK1** (18) is the action's aftermath. Entering it: a poisoned unit
  still standing loses an eighth of its maximum HP (not after using item 1,
  nor once its enemies are all down or the battle has ended); every unit the
  action killed dies once the last unit is free; a hidden unit reappears
  when the action is over; the passive skills' effects end at 70% of the
  action, and the stock panel fades out at its end. Its check waits for an
  Analyze to be dismissed and for the action's packets to be within 15
  frames of their end, moves the turn order on, runs the talk checks and
  death scripts, and remembers the unit's command for next turn (an attack,
  a skill or a pass; skills 0x31 and 0x32 and other commands forget it), then
  goes to CHECK3.
- **NEGO** (9) starts the talks (`nbInitNegoProcess`) between two slots:
  the first marked target slot flagged as the talks' player side
  (formation stat 0x100) or enemy side (0x200), with the actor's own slot
  taking its side; the battle panel stops taking input. Its check waits
  for the talks' process; a dead Demi-fiend's talks end with result 8.
- **NEGORESULT** (10) carries out the talks' result (`negoresult`):

  | Result | Effect | Press |
  |---|---|---|
  | 1 | the enemy's motions reset | -1, new press 0xC |
  | 2 | the enemy leaves | -1, 0xC |
  | 3 | it joins (`nbGetNakama`) and leaves the field | -1, 0xB |
  | 4 | motions reset | -10, 0xD |
  | 5 | it and every enemy of its kind leave | -1, 0xC |
  | 6, 9 | every enemy leaves (9: it joins first) | none |
  | 7 | motions reset | none |
  | 8 | nothing, and no camera | none |

  Enemies that leave walk off at a random frame within 20. The press
  packets come for talks the Demi-fiend started; for talks an ailment
  started (`negotype` 1, 2) only with results 2..4, for types 3 and 4 only
  with 4. The camera turns to the pair (`nbCameraSetTaizi`, state
  NEGO_TAIZI) after the Demi-fiend's own talks when his slot has flag
  0x10. With no enemy left the battle ends (endtype 9).

The pairs' code is in the HD remaster's order of the states, and what each
pair does confirms its number (WAIT, ESCAPE, RETURN and INVISIBLE were first
numbered one off). Four action processes form a ring in the main process
data (`ActionProcessID`, `NowActionProcess`).

Each frame, `nbActionProcess1` runs the state's check until it reports done
(action stat bit 2); the next frame enters the state the check chose
(`nbActionSetSeq`, which clears the state's counters and next state), and a
done END ends the process. An action about to be READY waits until the one
before it in the ring has reached state 19 or later (or there is none), and
stops a streamed voice that is still playing. Action stat bit 0x40 holds the
action where it is. States not rewritten yet are called through the table
by address.

The time list schedules the units an action touches, one entry per
formation slot: `lockframe` (busy until), `endframe` (done at) and `hp` as
the action's packets will leave it. `SetTimeList` starts no earlier than
the unit is free, `OverwriteTimeList` doesn't; neither moves a time earlier,
and a unit is never done before it is free. A unit counts as dead at 0 HP
unless its devil can't die (format flag 0x100).

The PS2 action data has no `uniqueid` field (the HD remaster's): the
action's own address identifies its kouka packets.

## An action's results (`Set*Packet`)

Helpers of the action process record what an action did and queue its
packets (`source/shared/src/battle/action.cpp`; their code runs from 0x24F420 to
`SetTarget` at 0x251428, in the HD remaster's order):

- **Press turns:** `SetPress` keeps the worst cost. Below -1 (more than a
  whole icon) the larger loss wins; above -1 a larger value wins unless more
  than an icon is already lost; -1 or less only fills an empty (0) cost.
  `SetNewPress` keeps the highest result type (the table above).
  `SetAddPressPacket` turns a skill that grants icons (program 13; 2, 3 or 4
  icons) into result types 15, 17 or 16.
- **Dodges and misses** (`SetSakePacket`, `SetMissPacket`) cost two icons
  (result type 4); a dodged single-target skill says so on the status line.
  `SetHitStopFrame` keeps the earliest hit plus 7 frames.
- **Deaths** (`SetDeadPacket`) happen when the unit's last packet ends; an
  enemy leaves its rewards. `SetDamagePacket` hurts the acting unit itself
  (the curse): Endure, or Never Yield, leaves it at 1 HP once.
- **Others:** an enemy running away (`SetEnemyEscapePacket`), Macca thrown
  (`SetMakaPacket`: the player's side can't lose more than it has), a
  Trafuri-like escape that ends the battle (`SetTorafuPacket`), Analyze,
  Flare's charge, a hidden unit fading back in (`UnitKyoseiDisp`), and
  `SetAuroraPacket`, which turns a unit's affinities through rows 0xF8..0xFB
  of the affinity table.

- **Summons** (`SetPlayerSummonPacket`): an enemy's call for help puts a
  devil of its choice into the first free of the 10 enemy units
  (`nbAppendEnemyDevilWork`, HP and MP from its format) and uses up one of
  the battle's allowed calls; the player's side summons a stock devil, or for
  skill 0xDF a random one that is in the stock, not out, alive and not at
  0 HP (`nbGetRandamStock`; none: "no one answered", message 0x3E).
- A devil talked into joining enters the stock at unit 4 or the first free
  one after it, and the compendium (`nbGetNakama`).

- **Ongyo-Ki's clones** (formation stat bit 2): an attack that finds the
  real one among them (`SetOngShadowPacket`) shows word 4, he leaves (the
  `ONGY` effect, 22 frames) and dies, and the clones stagger (motion 14); it
  costs two icons (result type 14). `SetOngShadowPacket2` makes the other
  clones vanish (`ONGY2`, 27 frames) and marks the battle (stat 0x4000). His
  splitting into clones is the `BUNSIN` effects (24 frames, 48 for three);
  the PS2 also has a one-clone packet (`nbAddOngBunshinPacket`) the HD
  remaster dropped.


## Side events: counters, talks, death scripts

After an action, its process checks for events that push another action
onto the battle's queue (`nbPushAction`; `source/shared/src/battle/action_events.cpp`):

| Check | Push | When |
|---|---|---|
| `CheckCounter` | 4 | the unit hit has Avenge, Retaliate or Counter (passives 0x133..0x131, tried in that order, each at 100 / its rate percent) and isn't shocked, frozen, asleep, bound, stunned, charmed or stoned |
| `CheckArrCounter` | 4 (skill 0xF3) | Ahriman (first form) counters a kind of party action once the story unlocks it (event bits 0x851..0x856: physical attack, magic attack, healing, magic, item, summon) |
| `CheckInotiNego` | 1 | the last enemy, hit by the party and at 24% HP or less, begs for its life (6%), if it isn't above the Demi-fiend's level |
| `CheckBinjoNego` | 2 | an enemy the party's action didn't target asks to join (2%), once each |
| `CheckKoketaNego` | 3 | after a failed escape, a random enemy that can act gets a free action |
| `CheckDeadScript` | 5 | an enemy the action killed has a death script |

`CheckSenseiNego` lets an enemy that ambushed the party open with talk
(21 / enemies percent); `CheckMukanNego` lets the last silent enemy speak up
(5%, from the third turn). Talks need the devil's talk record to allow them
(`datDevilNegoFormat`: `senseitype`, `inotitype`, `binjotype`,
`mukantype`), no full Kagutsuchi, and the speakers able to talk. No devil in
the PS2 data has a `mukantype`, so that talk never happens. A battle stat bit
(0x2000000, tentative: a debug switch) makes every talk certain.

`SetNowActionStat` records what a party action does as the action's stat
bits, which Ahriman's counter and `SetAction_END`'s debug messages read.
`KyouseiPress` ends the press turns at once; `DokodemoPoa` kills every enemy.

## Choosing a target (`nbTarSelProcess`)

The target cursor is its own process ("nb_tarsel",
`source/shared/src/battle/target_select.cpp`). `SetTarget` (the TARSEL state)
marks the slots the command can reach (`nbSetSelectOkMark`) and starts it
(`nbSetTargetProcess`). The cursor starts on the actor's side if it has
targets, else the other, and on the unit's last target when the
cursor-memory option is on (`dds3CheckConfigBit(1)`, config bit 4) or in an
auto battle.

Each frame (`nbTarSelProcess1`) the pad moves it (`CursorSelect`):
previous / next step through the side's targets, a fresh press wrapping
around and a held one stopping at the ends; side previous / next switch
sides, and step through the one side when only it has targets. Confirm
stores the target in the unit (`MemoryCommand`); cancel backs out (sound
10); a move plays sound 3. Single targets get the cursor; group commands
mark the whole side; all-target commands everyone (`UpdateSelect`). The
cursor's two rings pulse on a 30-frame loop (`AnimeTargetCursor`), and the
target's name shows on the help line (`DispTargetHelp`). Event battles
(stat 0x200000) don't take the pad; auto battles take the cursor's target at
once.

## Choosing a command (`nbCommSelProcess`)

The battle menu is the process "nb_commsel"
(`source/shared/src/battle/comm_select.cpp`) and its record
`nbCommSelProcessData` (0x14D0 bytes, HD field names). `SetCommList` fills
six lists of up to 0x120 entries; each entry is a skill, item or stock
index or one of the fixed commands 0x8000 Attack, 0x8001 Escape, 0x8002
Pass, 0x8003 command 7 (a demon's; "Dismiss" in the battle strings,
tentative) and 0x8004 Talk:

| Tab | Holds |
|---|---|
| 0 | Attack, the unit's active skills usable in battle (`use` bit 2), Pass |
| 1 | the Demi-fiend's Talk and talk skills (0x180.., kinds 0..6) |
| 2 | the Demi-fiend's items usable in battle |
| 3 | the stock demons not in the party (the Demi-fiend's) |
| 4 | a demon's command 7 |
| 5 | Escape |

Each entry also gets a reason it can't be chosen (`commdisable`), the
last found winning: 1 for skill or item flag 1 in a boss battle
(BattleStat 1) and for Escape (skill 0x48, item 0x38, the Escape entry)
when `nbGetEscapeSwitch` says no; 2 for skill flag 2 / item flag 8 with
BattleStat 4; 3 when `nbCheckSkillCost` refuses; 4 for a dead stock demon;
5 for magic while Mute and Talk while Fly; 6 for skill 0xDF with four in
the party or no one to summon. The game's own debug bit 0x4000000 lists
every skill.

The pad (`SelectCommandList`, bytes at 0x2F5830): up / down move the
cursor and scroll (four rows; the summon list shows two and grows to three
when the cursor reaches its edge), left / right change tabs, confirm takes
an entry that can be chosen (`MemoryCommand` sets `nowcommand`: 0 attack,
1 skill, 2 escape, 3 pass, 4 talk, 5 item, 6 summon, 7 command 7), cancel
returns to the first entry, button 0 picks Pass at once and button 13
toggles the help panel (event bit 0xC0E). The cursor starts on the unit's
previous command when the options say so (`SetCommCursor2`: option 1, or
option 2 in an auto battle). Drawing the menu (`nbCommSelProcess1` and the
`Disp*` functions) is still the original's.

## The help line (`nbHelpProcess`)

The line of text at the top of the screen is the process "nb_help"
(`source/shared/src/battle/help.cpp`) and its record `nbHelpProcessData` (0x38
bytes; field names from the HD remaster). `nbDispText` replaces what it
shows: two strings 10 pixels apart (type 0), a message (type 1: the table
and number `nbDispMsgHelp` stored in reqmsgid / reqmsgno), or a string and
the name the player entered (type 2, the Demi-fiend: his race by Magatama
from `cmbGetPlayerRaceID`, then his name). Each string is laid out one
character per font request in style 1, 3 units apart (0x1CA0D0 / 0x1CA258,
`fr::LinkLetters`); only the width is kept, and the text is laid out again
each frame to draw. Replacing the text releases a message shown before
(`nbHelpOff`).

| Function | Shows | Frames | Color |
|---|---|---|---|
| `nbDispSkillName`, `nbDispItemName` | the name | 30 | 0x89FEFF80 |
| `nbDispMiscActionNameComm` | "Attack" (command 0), "Retreated" (2), "Pass" (3), "Summon" (6), "Dismiss" (7); nothing for others | 30 | 0x89FEFF80 |
| `nbDispDevilName` | race and name (a target) | 2, so each frame of the cursor shows it again | 0xA09DC380 |
| `nbDispMsgHelp` type 0, 1 / 2 / 3 | a message | 45 / 20 / 30 | white / name color / white |
| `nbDispJyokyoHelp` | a status message (type 1); a devil's name with index 0 becomes the Demi-fiend's entered name (`{var}` type 10) | 45 | white |

Two more wrappers are never called and aren't in the HD remaster: 0x289078
(a table of two leftover Japanese strings at 0x5263F8, with the type as an
argument) and 0x2891A8 (the battle strings at 0x3E8BF0 by index); their
names in the rewrite are descriptive. The frame driver (`nbHelpProcess1`)
and the panel behind the text (`DrawPanel`) are still the original's: the
panel is three pieces of the battle panel texture, as wide as the text.

## Battle events (`nbEventProcess`)

A death's or a script's event (`MainProcessData::eventno`) runs as a process
named "nb_event", a child of the battle. The event table at 0x527260 is read
by `eventno % 100`, but only its first 16 rows are real (row 0 is empty).
Each row gives:

- the event's pack;
- its process function;
- the encounter it belongs to;
- its music, as a sound bank plus a piece;
- four fade frame counts that a death event's fade uses.

When an encounter starts, `nbLoadBattleEventPackInit` starts loading the
packs and banks of every row for that encounter, and `nbLoadBattleEventPack`
reports when they are all in memory.

The process's first step (`nbEventProcess1`) records the pack. The second
(`nbEventProcess3`) does the setup:

- cures any ailments of the enemies present;
- puts every unit present into its wait motion;
- clears formation stat bit 8;
- hands over to the event's own function and starts its music. With no
  function, the event ends there.

On shutdown the music fades out, the battle's event and stat bit 0x1000 are
cleared, and the units restart their wait motions. The event's memory
handle, file and pack requests are released, then its own shutdown function
is called and its user block is freed.

## The Macca window (`nbMakaProcess`)

The window showing the party's Macca fades in by 0x20 a frame. It stays open
while `keep` is set; otherwise it closes 20 frames after `nbMakaDispOff`.
`DispMaka` draws a three-piece panel from the battle panel texture, then
seven digits, most significant first, with leading zeros left blank (a
zero amount shows "0").

## Sounds (`nbSound`)

Sound banks are named by a file number in the upper half of a word:
`/sound/MIDI%04X.SMG`. The lower half picks a piece in the bank.

**Unit banks.** Each motion of a unit's model can have its own bank, and a
demon's talks have one more:

- a motion's bank is 0x1000 + model x 16 + the motion's piece, where the
  model comes from the table at 0x3E7028. That table maps almost every unit
  to itself; 173 to 175 and 204 to 206 share another unit's sounds. The
  piece comes from the model record's motion entry, and -1 means no sound;
- a talk bank is 0x500 + the unit.

The battle keeps a table of ten units' banks (`MainProcessData::sound`, 0xE0
bytes each):

- a unit joining requests its files, or adds one more user to its entry;
- `nbUpdateSoundTable` collects the files as they finish loading;
- a motion or a talk sends its bank to sound memory when needed, unless the
  bank is already there or on its way;
- the last user leaving frees the entry.

**Music.** The battle's music type is the encounter's own (`btlsound`), else
its area pack's, else 1. Each type has a main bank, a bank of pieces, and
the pieces played:

- types 1 to 3 are the normal battles. Their pieces' bank is one of seven or
  eight, picked by a counter that `nbBgmNext` advances;
- types 1 and 2 also have a second piece. `nbBgmTrans` switches to it at
  the first action's start (the action process's READY state).

`nbBgmLoadChk` loads the two banks one step per call. `nbBgmStop` fades the
pieces out, plus piece 0x2B0000.

The names `nbBgmTrans` and `nbBgmFadeOut` are tentative: they follow the HD
remaster's order. Ghidra's old name for the switch, `nbStopMotionSe`, was
wrong.

## The encounter's opening (`nbEncProcess`)

The "nb_enc" process runs while a battle starts:

1. It starts the encounter effect and requests the enemies' models (unit
   group 1).
2. When those are in, it requests the party's models (group 0).
3. The enemies appear one at a time, one every eighth frame of the process,
   each with hit effect 4. When the battle opens from a fade (`stat`
   0x800), they are all simply shown.
4. Under a full Kagutsuchi with `stat` 0x400, every enemy present gets
   object flag 0x400 and a 200.0 in its control block (a glow, tentative).
   A fade-in battle shows the enemies and fades in. A back attack shows
   status message 6 (7 with the sides swapped).
5. When the party's models are in, each member appears without an effect
   (anime bit 0x200). The load time is printed: ">>> UNIT LOAD TIME = %d
   frame <<<".
6. The process ends when every unit present is ready and the opening camera
   is done. "Ready" means stat bit 2 is set and the unit's handle no longer
   has bit 0x10000. This check reads 32 slots, past the fourteen
   formations, into the parties' memory.

## The battle's opening (`nb_mae`)

The battle's "before" process ("nb_mae", BeforeProcessID) runs one step a
frame, each naming the next:

1. The stage is requested (main +0x7C, +0x7E; record at 0x575350), and
   the encounter's effect starts (`effBTLEncountStart`, skill effect 0x200).
2. The encounter's event packs are requested. For encounter 0x14D, the
   flight model's file is requested too (flyh). The stage process is held
   back (process flag 0x20).
3. Once the packs are in, the flight model's memory is kept (flymem) and
   the stage is shown.
4. The music loads.
5. The process waits for the music to load.
6. The music plays, and the process ends.

The first release loads the flight model as a plain file; the later ones
load it as a PAC.

## The result screen (`nbResultProcess`)

When the battle is won, `nbInitResultProcess` starts the result process
("nb_result") as the battle's child and keeps its ID in `ResultProcessID`.
Its first frame (`nbResultProcess1`) prepares the screen and hands over to
`nbResultProcess2`, which runs it:

1. The battle's helper processes stop (`ShutdownProcess`, tentative: the
   HD name in order): the auto command, camera, effect, unit, help and
   panel processes, each killed with a one-frame delay and its ID cleared.
2. The experience earned (`nbGetKakutokuExp`) is kept for the screen.
3. The screen loads (`nbResultLoad`). It gets three textures and gives a
   row to each party member, at most four in stock order. Each row shows
   the member's experience and level and the experience it gains
   (`GetAddExp`), counting up a 45th of the gain a frame (rounded up, at
   least 1).
4. Its counters start at zero.

`nbResultProcess2` runs each frame, timed by the process's run time:

| Frame | What happens |
|---|---|
| 3 | The screen fades in. |
| 16 on | Once a scene is active, the stage is let go (`ClearStage`). |
| 20 | The next field's pack starts loading, polled until done ("pac1 done"). |
| 21 on | Either of two buttons (pad bytes 1 and 3) skips the counting. |
| every frame | The screen is drawn (0x24B010, not yet rewritten). |

A skip (`nbResultSkip`, tentative) puts every row at its total. A row
whose level rose (`rstCalcLevelFromExp`) is marked and gets a level-up
animation, and one sound (0x11) plays for them all.

`nbResultFinWaitChk` holds the end while any row is still counting, then
counts frames up to 60. Once it reaches 15, a button press ends the screen.
Sixteen frames later, with the pack in, the spoils are granted
(`nbResultAddExp`), the music fades and the process ends. After a battle
of 871 frames or more, the next battle's piece is also chosen
(`nbBgmNext`); the first release chooses it after every battle.

A level-up animation (`nbResultLvupAnmAdd`) takes the first free one of
64 slots for 20 frames; with all 64 in use it is dropped.

`ClearStage` (tentative) lets the battle's units go. For each of 32
formation slots it frees a present unit's PAC request (formation +0xB4)
and clears its state, which reaches past the fourteen formations. It marks
fourteen parties gone (flag 0x28) and releases the stage. The first
release frees the request as a plain file (`ps2ResourceRequestRelease`).

On shutdown (`nbResultShutdown`) the ID is cleared, the three textures go
back to the texture cache (`nbResultTexDel`), and what follows the battle
begins.
