# Native targeting rules, eligibility and candidate ordering

Ten complete original PS2 bodies are recovered in `src/battle_targeting.c`
and integrated into the current host build. The current focused report passes
**5,120 cases**, executing **2,610,555 original instruction steps**, **207 real
item RNG advances** and **1,589 original C.LT.S comparisons**. All **533
reachable main instruction addresses** execute. The one remaining main address,
`00258EB0`, is separately proved impossible: its LBU descriptor mode must be
less than two, unequal to one and unequal to zero. Delay-slot instructions are
executed by the original instruction model but excluded from this main-address
coverage metric.

The working Ghidra project was saved in place, then reopened independently to
check all ten names and raw EE interfaces. All ten refreshed exports decompile
and merge into the current recognized-function inventory. No project copies,
checkpoint archives or repeated full-suite capture were created.

## Recovered bodies

| PS2 entry | Role | Recognized bytes | Compared cases |
|---|---|---:|---:|
| `00242B68` | `datGetNormalAtkPow` | 96 | 256 |
| `00242D18` | `datGetDefPow` | 52 | 256 |
| `00243FE8` | `datGetAisyo` | 144 | 512 |
| `00244E68` | `datGet3Zokusei` | 76 | 256 |
| `00245C90` | `datGetItemSkillNo` | 132 | 384 |
| `00259C48` | `nbGetItemSkillNo` | 72 | 256 |
| `00258DE8` | `nbGetTargetTypeRuleArea` | 540 | 512 |
| `0025D690` | `GetTarSelProcessData` | 36 | 128 |
| `0025DA78` | `CheckFormCursor` | 384 | 2,048 |
| `0025DC00` | `nbSetSelectOkMark` | 572 | 512 |

The total is **2,104 recognized body bytes**. The action-rule body's contiguous
span includes padding outside its recognized instruction ranges; body hashes
and Ghidra body ownership are checked separately.

## Original PS2 contracts

Attack and defense execute the actual recovered parameter reader, using lanes
zero and three respectively, add the unsigned halfword level at unit `+14`,
and double with original word arithmetic. Attack halves this result when the
low twelve status bits equal `40`. Affinity treats full-width `-1` as its early
sentinel, uses the signed halfword demon affinity row at
`3497CE + demon_id * 3C`, reads a signed word from `3A7FE0`, and substitutes
the row at `3ABD60` when status is `400`. Flag4 units use row zero. Alignment
bypasses flag4 units and gives demon flag40 precedence over flag80.

The item getter loads all six native literal words at `543170` before its
item1 branch. Item1 runs the actual recovered default RNG at `529BD8`; other
items use the halfword at `3DC4A2 + low_item_id * 8`. The battle wrapper still
consumes item1's RNG result before replacing the returned skill with context
`+64`. A cached skill must not eliminate that state transition.

The action reader uses signed LH unit `+6A`, guarded by an unsigned comparison
against seven. Action0 sets normal/reversed area and rule and invokes the real
passive ownership check for skill130. Actions1 and5 read the skill directly or
through the item wrapper, then use descriptor `3D7998 + skill * 3C`: byte8
sets type, byte9 supplies side bits, and byteA supplies the low four rule bits.
Action4 uses area2. Action6 reads the root flags and signed formation index;
actions2/3 and out-of-range actions retain zero defaults. Output pointer tests
retain their full 64 bits, and stores occur in type/rule/area order after all
dependencies and descriptor reads. Compared aliases include shared outputs and
an output overlapping descriptor bytes.

`GetTarSelProcessData` runs actual named-process lookup for the original
`nb_tarsel` literal at `5442B8`, followed by the actual process-data getter.
The original getter has no additional null guard.

Eligibility preserves full-width self/target equality and signed target
comparisons, while address arithmetic and target-minus-four wrap as words.
Type2 bypasses side selection; area3 allows both sides; area1/2 exchange sides
under root flag8. Rule1 requires self, rule2 excludes self. An inactive slot is
rejected unless rule4 and slot flag800 permit it; rule8 excludes active slots.
Slot flag40 selects a signed party index at `+90`, whose party halfword flags38
reject the slot.

Candidate construction clears slot flagsC and evaluates all sixteen physical
slots. Eligible slots gain flag4, but only slots0..13 enter the lists. Normal
side assignment puts0..3 into the own list and4..13 into the enemy list; root
flag8 reverses this. Native count bytes12/13 and list bases14/20 retain their
signed loads and live reloads.

Enemy ordering uses strict pairwise swaps based on the raw float word at slot
offset zero. This is **not stable sorting**: later swaps can reorder equal
values. The original instruction at `0025DDB0` is independently opcode-checked
as C.LT.S. Comparison uses the existing EE value boundary, including exponent0
flush-to-zero and exponent255 finite payload ordering, and checks FCSR condition
bit23. Other floating-point exception flags and physical hardware are not proved
by this boundary.

## Community context and Unity review

The [Nocturne Randomizer source](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/nocturne.py)
is pinned to `f74e85c0f632b751eaf278046884961c618c8541`. Its first indexed demon
record starts at ELF offset `24A7F0`, stride3C, with flags at record `+0C`.
The native flag/skill field view is twelve bytes later than that community
record window. For demon IDs1..383, the checked address relation is:

`24A7F0 + (id - 1) * 3C + 0C = 3497C0 + id * 3C - FF000`.

This reconciles the two bases without assuming a complete descriptor layout.
The community writer modifies a halfword; the native alignment reader loads a
word. Reader width and precedence come from original instructions.

[DDS battle-table documentation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
is pinned to `bec33411543cdc487bad9debdf758f0090a2242c`. Its targeting vocabulary
provides related-engine context. The Nocturne descriptor offsets, numeric
domains and rule masks here come from Nocturne's own reader; DDS layouts are
not imported by name. Source URLs, revisions and retrieved hashes are recorded
in [battle-targeting-community.json](battle-targeting-community.json).

Ten Unity methods are reviewed in
[battle-targeting-matches.json](battle-targeting-matches.json). Their managed
arrays, bounds/null/type checks and sort-key representation differ. In
particular, HD accesses a Vector3 component where the original reads slot
float word0. The raw64 tested interfaces are comparison signatures, not proof
of original source typedefs.

## Transfer result

The strict full-span search finds one 36-byte accessor pattern at DDS1
`001028A0`. Its original pointed-to name is **Admini**, whereas Nocturne's is
**nb_tarsel**. It therefore establishes a shared named-process accessor
structure, not a DDS target-manager identity. The report separates this
structural peer from selected semantic counterparts; the latter is empty for
this batch. The two accessor calls link to the scheduler/name and process-data
routines already independently checked in the community engine audit.

No other selected complete battle body matches in this constrained search.
That is not evidence against shared behavior implemented with different code
or table layouts. See [battle-targeting-transfer.json](battle-targeting-transfer.json).

## Progress and next recovery

The current source/hash audit records **1,414 unique integrated routines out
of8,979 recognized (15.748%)**, **200,560 unique recognized body bytes**, and
**673,089 aggregate comparisons**. The last full run remains413/462,684;
105 focused reports contribute210,405 cases. The current ledgers contain650
PS2/HD mappings,756 PS2 aliases and278 shared signatures. Aggregate case counts
include dependency reruns; they are not unique input or gameplay coverage.

The original AI frontier now contains **39 unresolved direct bodies /14,520
bytes**, with no missing exports. Its newly checked original single-target
dispatch table at `545800` gives ten leaf calls: LIFEMIN, BAD, ID, LIGHT, DARK,
PLAYER, JOKEN, RND, BAARLV and LVMIN. Unity names are next-step leads; these
filters are not yet counted as compiled recovery. Selector0 and fallback use
the unrecovered scorer `00286B68`. Continue these filters and the scoring
prerequisites before automatic target selection `002879F0` and command52
`00287EE0`. The original decision scheduler, full gameplay, a matching PS2
binary and physical PS2 execution remain outstanding.

## Current evidence

- [Focused validation](battle-targeting-validation.json): per-entry counts,
  complete coverage accounting, source/verifier hashes and capture hash.
- [Interfaces](battle-targeting-interfaces.json) and
  [independent Ghidra check](battle-targeting-abi.json).
- Current capture: `analysis/battle-targeting/vectors.jsonl`, overwritten in
  place when this subsystem needs another capture.
- Driver: `tooling/recover_battle_targeting.py`; stages `prepare`, `pin`,
  `compare`, `transfer`, `publish`.
- [Current recovery audit](recovery-progress.json) and
  [current original AI frontier](battle-ai-frontier.json).
