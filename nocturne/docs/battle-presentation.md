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
library (skill and passive effects, hit effects, Ongyo-Ki's clones), the
damage, healing and death-visual compositions built on them, removing
packets (which frees those effects) and the kouka process itself.

## The action process and its time list

Each action runs as a process (`nbActionProcess`, `source/src/battle/action.cpp`)
through a state machine: a table at 0x3FA7C0 of `SetAction_*` (entering a
state) and `CheckAction_*` (each frame; true when done, after choosing the
next state) pairs. Fixed transitions: AI → READY (7), WAIT → CHECK1 (18),
CHECK3 → ATO (21, once the action's packets are all played), ATO → END
(22, freeing the skill's effect).

- **AI** (2) clears the unit's command and runs the table AI
  (enemy-ai.md); **AISCR** (3) runs the devil's AI script instead
  (`DevilAI::scriptid`). The script runs as a child process of the battle
  (`nbInitAiScript`, one priority step ahead of it, `AiScriptProcessID`);
  once it ends, the action goes to READY, or to the talks' result (10,
  NEGORESULT) when the script started talks (`negoresult`). That this
  matches state 10 supports the tentative numbering.
- **DEADSCRIPT** (19) runs a dying unit's script (the procedure in
  `adata`); when it ends, the unit fades out and leaves the field (a return
  packet at frame 25, the unit busy for 30 frames) and the action goes to
  CHECK1.
- **END** (22) prints debug messages for what the action did: stat bits
  0x10000 .. 0x200000 are a physical attack, a magic attack, healing, magic,
  an item and a summon. The numbers of the states between BAD
and INVISIBLE are placed by the order of their code (tentative). Four
action processes form a ring in the main process data (`ActionProcessID`,
`NowActionProcess`).

The time list schedules the units an action touches, one entry per
formation slot: `lockframe` (busy until), `endframe` (done at) and `hp` as
the action's packets will leave it. `SetTimeList` starts no earlier than
the unit is free, `OverwriteTimeList` doesn't; neither moves a time earlier,
and a unit is never done before it is free. A unit counts as dead at 0 HP
unless its devil can't die (format flag 0x100).

The PS2 action data has no `uniqueid` field (the HD remaster's): the
action's own address identifies its kouka packets.
