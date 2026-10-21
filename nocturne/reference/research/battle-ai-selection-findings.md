# Native single, group and automatic targeting; AI_TAR_AI

Four complete routines in `src/battle_ai_selection.c` and `.h` compile and
pass **2,048 original-instruction comparisons**, executing **4,345,773
steps**. They add **1,212 recognized body bytes**. All **229 main instruction
addresses** execute, with no unexercised selected main address. Full declared
RAM, raw64 returns, Status, FCSR condition, CPU primitives, ordered libc/VM
traces and native callee saves agree. Actual target-list sorting includes
**8,736 C.LT.S comparisons**. There are **128 connected COMM52/END programs**
and **384 actual VM indirect calls**. One rolling capture is retained.

| PS2 entry | Role | Recognized bytes | Cases |
|---|---|---:|---:|
| `00287508` | `nbSetSingleTarget2` | 580 | 512 |
| `00287778` | `nbSetGroupTarget2` | 228 | 384 |
| `002879F0` | `nbSetAiTarget` | 324 | 768 |
| `00287EE0` | `nbCommand_AI_TAR_AI` | 80 | 256 |
| `0010B520` | Existing interpreter, connected programs | Already integrated | 128 |

The actual filters, scorer, estimator/effects, work/scheduler, target
type/rule/area, eligibility/list sorting, item queries, summon setup, default
RNG, libc and interpreter execute. No game-result hook supplies a target.
The host's existing private-stack bridge provides storage for the three
target outputs; the real getter writes their values. The 28 declared RAM
spans include the original selector and opcode/command tables. All 174 COP1
sites are pinned to original body/opcode bytes. Ten affected existing reports
pass another **23,053 comparisons** against their retained captures; these
rechecks are not added again to aggregate counts.

## Original dispatch and selection

Single selection bounds the selector with **unsigned full64 <11**, then
dispatches through the original table at RAM00545800 / file00446800:
1=life minimum,2=status,3=ID,4=light,5=dark,6=player,7=condition mask,
8=random eligible,9=non-petrified level minimum,10=level minimum.
Only status/ID use the additional parameter. Out-of-range selectors fall back
to0. If no slot has flag8 after filtering, both selector and parameter reset
to0. Selector0 invokes the actual AI scorer with group0.

It then enumerates every flag8 slot, including existing marks without flag4.
Any nonempty list consumes the real RNG, **even a one-candidate list**. All
other flag8 marks clear; the chosen slot's remaining flags are preserved.
It returns the scorer's raw64 result when invoked, otherwise0. Empty lists
consume no final-selection RNG. The scorer itself can consume RNG through
effect estimates, as documented in the previous batch.

Group selection uses selectors1..10 to mark **all flag4 slots**, without
calling their single-target filters. Negative, dirty-high/out-of-range and
zero selectors fall back to the AI scorer with group1. No flag8 marks also
reset the parameter. Existing marks remain. It has no separate final random
selection, although an invoked estimator can draw RNG.

Automatic selection accepts signed action0/1/5 only. Skill actionsDE,
E2..E6 andFC invoke actual enemy summon setup with main and signed LW
context+1A0, then force selector8. The target getter and actual eligibility
marker execute next. Type0 calls single selection; types1/2 call group
selection. A nonzero raw result stores action3 and skill0 after reloading
the actor pointer, then returns that result. Other actions return0.

Sixteen final automatic cases exercise empty summon slots through the entire
caller path. DE/E2/E6/FC, devil IDs1/2/0/-1, availability, ten empty slots,
original model multiplication, eligibility sorting, forced selector8 and
actual RNG selection are checked together. Independent oracles assert
scale2.0 for positive devil IDs, unchanged scale for0/-1, exact selected
flag bits and exact RNG state. Earlier controlled cases separately assert
single/group success and scorer-1 failure behavior.

## Community command52 and interpreter behavior

The pinned [Atlus Script Tools SMT3 library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/SMT3/Modules/Common/Functions.json),
revision `1c557a092dd7610829b7215be0f0f5101acf1d72`, names command52
AI_TAR_AI and lists no parameters. Original descriptor RAM0052E4F0 /
file0042F4F0 contains target00287EE0 and pop count0. The Unity named body
independently corroborates the role. The native command obtains actual
script user data, invokes automatic targeting with0/0, and writes the actual
16-slot selection bitset to context+3C **only when targeting returns0**.
It always returns1. A scorer-1 failure leaves the prior bitset intact while
the automatic caller sets action3/skill0.

The 128 constructed programs execute original COMM52 dispatch and END,
checking command/opcode target order, work arguments, CP/count/timer changes,
target flags, bitset updates and retained failure masks. They are connected
interpreter tests, not complete execution of the original141 AI procedures.

The pinned [randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
retain build/AI/encounter context. All384 original scorer modes are0;
modes1/2 in failure and scoring tests use constructed headers. URLs,
revisions, content hashes, original selector targets and descriptor bytes
are in [the community audit](battle-ai-selection-community.json). Its prior
context snapshot contains historical membership fields; the current script
frontier below independently derives source-current status.

## Integration, transfer and the next original-script frontier

Four reviewed Unity roles are recorded in
[the match audit](battle-ai-selection-matches.json). PS2 branches, offsets,
raw64 guards and original tables govern source; protected/managed HD tails
do not supply native behavior. All four interfaces are saved in the single
working Ghidra project, independently reopened and checked. Four current
exports decompile and merge into the8,979-entry inventory.

Strict complete-span search resolves no selected DDS body. The pinned
[DDS command library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/DigitalDevilSaga/Modules/Common/Functions.json)
has no AI_TAR_AI name. Nocturne command52 is not assumed portable. The
shared native selection fingerprint is recorded with those limits.

Current recovery is **1,453 unique routines /8,979 (16.182%)**, **215,120
recognized body bytes** and **689,217 aggregate comparisons**, including
226,533 focused cases. The selected startup/automatic-target/command52
[direct frontier](battle-ai-frontier.json) has **zero remaining bodies** at
source-current compared boundaries. This closes that chain, not the full
battle engine or original script decision execution.

A new [original embedded-script census](battle-script-frontier.json), produced
by `tooling/audit_battle_script_frontier.py`, rechecks original BF bytes,
descriptor pairs and every registered canonical-source hash. Of63 used
command IDs,18 have compared bodies and45 remain unrecovered. Compared
commands account for5,018 of7,178 static occurrences. The unresolved direct
command graph has **89 bodies /8,656 bytes**, excluding dynamic callbacks.
RND and Hojo/HP checks have the largest remaining static use. The recovered
selector chain also enables the remaining AI_TAR wrappers. Recover those
commands and connected original-procedure paths next.

Arithmetic FCSR flags, dynamic scheduling, physical PS2 gameplay and a matching
executable remain unproved. No new full-suite run, checkpoint or project copy
was created. Static script frequency is a recovery priority, not runtime
coverage or proof that an original procedure executes end to end.
