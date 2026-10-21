# Native effect scoring, AI candidate ranking and summon slots

Three complete native bodies in `src/battle_ai_estimates.c` and `.h` compile
and pass **1,536 original-instruction comparisons**, executing **18,147,477
steps**. They add **1,612 recognized body bytes**. All **335 reachable main
instruction addresses** execute; two further scorer addresses have explicit
native proofs of unreachability. Full declared RAM, raw64 returns, Status,
FCSR condition, CPU primitives, ordered libc traces and native callee saves
agree. The capture includes **282 C.LT.S comparisons** and **6,358 libc
kernel/CPU trace words**. One rolling fixture/capture pair is retained.

| PS2 entry | Recovered role | Recognized bytes | Cases |
|---|---|---:|---:|
| `00268F68` | `nbGetVirtualKoukaPoint` | 516 | 512 |
| `00286B68` | `nbAiSelAi` / Unity `nbAi.Sel_AI` | 840 | 512 |
| `0028B528` | `nbSetEnemySummonFormation` | 256 | 512 |

## Actual dependencies and original estimator behavior

The scheduler/work getters, affinity and temporary/passive support paths,
six native effect evaluators, physical/magic/healing/HP power, parameter and
event-bit readers, default RNG, software-double routines and real
printf/formatter/dtoa/bigint/heap paths execute. No game-result hook supplies
an estimate or skips a diagnostic. The 21 declared RAM spans also include
the actual AI, encounter and model tables. All 173 COP1 sites are pinned to
original opcode/body bytes. The existing effects, power, affinity, support,
targeting and work reports pass another **16,768 comparisons** against their
retained captures after the host address routes change. These repeated cases
are not added again to aggregate coverage.

The estimator obtains source work, then target work, then the real affinity
ratio. It evaluates status damage and cure, HP damage and healing, MP damage
and healing, and finally support effects in that exact order. Each effect
uses preview=1 and count=1 where applicable. Preview still consumes actual
RNG in applicable effect/power routines and can clear support counters through
flags400/40000. It is not a pure query.

Positive healing is capped by the signed word difference between stored
maximum and current HP/MP. Maximum below current can produce a negative
cap. Status damage and cure each contribute one point if nonzero. HP/MP
changes contribute their low word only when their signed64 value is at
least two; support contributes its word unconditionally. The final word
sum wraps and returns sign-extended to64 bits. Support flags use a signed
LW from action record+28; the support amount uses a signed LB at+2C.

## Original scorer and the compact-ordinal quirk

The scorer reads a unit's unsigned ID, then the unsigned mode halfword at
`003989E2 + id*0xA4`. Action is signed LH+6A: action0 uses skill0; action1
uses LHU+6C. Other actions emit the native diagnostic and return0. Its
second input is unused. The group input is stored as a word, so a nonzero
high lane alone does not enable grouping.

- Mode0 ORs flag8 into every flag4 formation slot and returns0.
- Mode1 evaluates all flag4 candidates, retaining even zero scores.
- Mode2 rejects exact virtual-affinity results10000/20000/40000, then
  rejects zero effect scores. Retained scores form a compact list.
- Modes3..65535 return0. Empty lists in mode1/2 print and return signed-1.

With a nonzero group word and a nonempty list, all flag4 slots receive
flag8, including candidates rejected in mode2. Otherwise a strict signed
word comparison chooses the largest score, starting with score0 and
ordinal0. Negative/zero scores and ties preserve the earlier ordinal.
The winning compact ordinal is then mapped across **all flag4 slots**,
including the rejected candidates. Existing flag8 marks remain intact.

Explicit cases508/509 have independently asserted selection marks. Case508
rejects slot0 and assigns distinct positive maximum-HP scores to slots1/2.
Slot2 wins compact ordinal1, which maps back to **slot1**. Case509 rejects
slot0 and ties the remaining positive scores: compact ordinal0 maps back
onto the rejected **slot0**. Cases510/511 separately return-1 for an
all-rejected list and an all-zero list. The source preserves this behavior.

Two main instructions cannot execute. At286C10, the mode would need to be
neither0 nor1 after LHU mode<2. At286D50, actual `nbGetVirtualAisyo` would
need to return a value>20000 other than40000; its complete native body
returns only0,10000,20000,40000. These are separate from executed coverage.

## Summon slots and community context

Summon setup first clears flag800 on slots4..13, even if availability at
main+84 is zero or encounter count is zero. It reads a **byte** at
`003AF002 + encounter*0x26`, the encounter record's+22 field. If available,
it examines that many slots starting at4, without clamping the byte count
to ten or sixteen. Occupied flag1 slots are skipped. Other slots gain800.
Only a positive signed **full64** devil argument writes model scale; the
model address uses its low word. The two model floats at
`0034F1E0 + devil*0x310 +10/+18` multiply in the original COP1 order and
store into slot+50. Constructed counts include255 and dirty argument lanes.
The redundant count+4>4 test cannot fail after a nonzero unsigned byte.

The [randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt),
revision `f74e85c0f632b751eaf278046884961c618c8541`, identify USA
SLUS_209.11, the RAM/file displacementFF000, AI strideA4 and encounter
stride26. Their AI file address002999E4 is **full header+4**; the native
procedure halfword is at RAM003989E0 / file002999E0, and the scorer mode
is at+2. All **384 original mode halfwords are0**. Modes1/2 are tested
with constructed headers, not asserted as stock gameplay behavior.

The same notes call encounter+22 reinforcements and suggest two bytes.
This native consumer's LBU proves a one-byte count at RAM003AF002 /
file002B0002. It does not assign a meaning to the following byte. The
pinned [DDS battle-table documentation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
supplies related-engine AI vocabulary; it does not establish equal layouts.
Direct URLs, revisions, content hashes, native readers and original mode
values are in [the context audit](battle-ai-estimates-community.json).

## Integration and limits

The three reviewed Unity roles are recorded in the
[role audit](battle-ai-estimates-matches.json). Original offsets, raw64
guards and compact-ordinal behavior govern the canonical C. Strict
complete-span search resolves **no selected DDS counterpart**; a known
printf dependency remains separate. The shared SMT fingerprint records the
checked native structure without claiming an identical other-game body.

Interfaces are saved in the single working Ghidra project, independently
reopened and checked; all three current exports merge into the8,979-entry
inventory. After integration the current audit reports **1,449 unique
routines**, **213,908 recognized body bytes** and **687,169 aggregate
cases**. Four direct AI bodies /1,212 bytes remain: single selection287508,
group selection287778, automatic targeting2879F0 and command52/AI_TAR_AI
287EE0. The latter has1,155 static occurrences in the community-discovered
embedded BF AI resource. Recover those callers and connected interpreter
paths next.

Full declared RAM and native register/call behavior are compared for bounded,
valid, nonaliasing contexts/queues/units and backed stdout/heap. Arithmetic
FCSR flags, timing, physical gameplay and a matching executable remain
unproved. No new full-suite run, checkpoint or project copy was created.
