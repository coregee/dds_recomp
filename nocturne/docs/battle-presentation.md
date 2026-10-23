# How battle actions are shown: the kouka queue

An action's effects are computed first (battle-mechanics.md) and then
shown by a queue of "kouka" (effect) packets. Each packet starts at a frame
of the action's timeline and lasts a number of frames: a motion, a move or
turn, a colour or fade on a unit, a damage number, a word ("Weak", "Miss"),
a sound, the press turn icons, a death. The kouka process plays the queue
every frame (not rewritten yet); the builders here only queue packets.

Source: `source/src/battle/kouka.cpp` (original units `nbKoukaProcess` and
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

Each action runs as a process (`nbActionProcess`, `source/src/battle/action.cpp`)
through a state machine: a table at 0x3FA7C0 of `SetAction_*` (entering a
state) and `CheckAction_*` (each frame; true when done, after choosing the
next state) pairs. Fixed transitions: AI → READY (7), INVISIBLE → CHECK1 (18),
CHECK3 → ATO (21, once the action's packets are all played), ATO → END
(22, freeing the skill's effect).

- **AI** (2) clears the unit's command and runs the table AI
  (enemy-ai.md); **AISCR** (3) runs the devil's AI script instead
  (`DevilAI::scriptid`). The script runs as a child process of the battle
  (`nbInitAiScript`, one priority step ahead of it, `AiScriptProcessID`);
  once it ends, the action goes to READY, or to the talks' result (10,
  NEGORESULT) when the script started talks (`negoresult`). That this
  matches state 10 supports the tentative numbering.
- **BAD** (4) checks the unit's ailment at the start of its turn. Shock,
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
- **NEGO** (9) waits for the talks' process; a dead Demi-fiend's talks end
  with result 8.

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
packets (`source/src/battle/action.cpp`; their code runs from 0x24F420 to
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

Not rewritten yet: `SetAllPacket`, which builds a skill's whole result.

## Side events: counters, talks, death scripts

After an action, its process checks for events that push another action
onto the battle's queue (`nbPushAction`; `source/src/battle/action_events.cpp`):

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
