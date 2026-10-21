# Basic AI decisions, queries and summon commands

Eighteen further PS2 bodies are integrated in `src/battle_ai_execution.c` and
`.h`. They compile with warnings treated as errors and pass **5,632 comparisons
against original instructions**, executing **11,818,129 original steps**.
The batch adds **2,712 recognized body bytes**. All **536 reachable selected
main instruction addresses** execute; the other three have explicit proofs in
[the fallback audit](battle-ai-execution-weighted-proof.json). The source retains
the original fallbacks.

Full declared RAM, defined raw64 returns, Status, FCSR condition, CPU primitives,
ordered VM/predicate/libc calls and returning native callee saves agree. There
are **256 connected interpreter programs**, **1,920 VM calls**, **1,484 actual
predicate callbacks** and **43,371 C.LT.S comparisons**. An additional **16,653
affected existing cases** pass using retained captures; rechecks add no aggregate
case credit. All 18 interfaces were saved and independently reopened in the
working Ghidra project, and all 18 complete decompilations were exported into
the current 8,979-function index.

## Community layout checked against original records

The pinned [randomizer implementation](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/nocturne.py)
uses file `002999E0` and stride `A4`; its
[notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
give decision data at `002999E4`. These refer to the header and header+4 of the
same native block, RAM `003989E0`. The
[record and descriptor audit](battle-ai-execution-community.json) checks every
one of the **384 original records** against the executable and pins the sources.

| Record offset | Native field |
|---|---|
| `00` | Procedure index, unsigned16; startup bridge verified separately |
| `02` | Cost/availability mode, unsigned16; all 384 originals contain0 |
| `04`, `10`, `1C` | Three 12-byte condition records: first packed condition, second packed condition, table number |
| `28`, `50`, `78` | Three 40-byte action tables, each with five entries |
| Entry `+0`, `+2`, `+4` | Unsigned16 weight, unsigned16 action, packed target word |
| `A0` | Uninterpreted trailing word; 22 originals are nonzero; these routines do not read it |

The recovered header provides these native record types with compile-time
offset and size checks. The table labels in community notes remain context;
the original condition records decide which table executes. The randomizer's
patched record contents are distinct from the shipped records.

The comparisons include **2,304 executions with unchanged original records**:
all three condition triples for every record; one direct table per record;
and the ordinary runner and its AI command for every record. Battle state is
constructed. Separate cases cover special action codes, zero weights, exclusion
bytes, rejected actions and modes1/2. This is not a claim that every original
action or all 141 embedded BF procedures ran end to end.

## Native behavior retained

`nbAiAiChk` clears the condition mask and stores the condition index before
calling the two real predicates with short-circuit evaluation. Passing a pair
containing type4 resets support counter index+1. Type21 aliases the increment
callback but does not trigger this reset.

`nbAiGetKoudou` excludes a slot only when its signed byte at context+198..19C
is positive. Negative bytes remain eligible. It adds unsigned16 weights, calls
the actual bounded RNG, and returns the original action index. Empty or zero
weight sets return raw64 -1. Stable weights and the real RNG make the final
selection fallback unreachable; two additional dead branches follow from the
eight possible high nibbles of an unsigned16 action.

`nbAiSetKoudou` preserves native stores for normal attack8000, escape8001,
wait8002 and action9/8003. Ordinary values below8000 set action1 and that skill.
Nibbles9000/A000/B000/C000/D000/F000 choose skillsE2/E3/E5/E6/FC/DE and retain
the low12 parameter. E000 stores action9 and battle-work+88. Other high-bit
values retain the native default stores. Normal attack invokes the actual
descriptor rewrite and diagnostic formatter.

`nbRunAi` tries the three condition pairs in order, uses the first passing
table, and defaults to table0 when none passes. `nbRunAiSub` clears exclusions,
samples an action, prints its index, runs real cost/availability and targeting
checks, marks rejected entries and retries. Exhaustion stores action3, skill0
and target mask0. Success obtains the actual selection bitset. Original mode0
and constructed modes1/2 have separate evidence.

Queries retain the native turn byte, signed press-action counter, level,
affinity/support/status override ordering and escape rules. GET_FUREA calls
the raw `evtGetAgeOfMoon16` getter and divides its byte by2. It does not use the
other moon getter's folded phase. SUMMON fetches parameter0 before storing the
actor action/skill, then parameter1, the context parameter and the actual
formation helper. Tagged integer, float, variable and unsupported parameters
exercise the real VM getters; summon slots use the original model data and
COP1 multiplication.

## Identities and transfer

All **18 named Unity roles** are reviewed in
[the identity audit](battle-ai-execution-matches.json). The pinned
[SMT3 command library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/SMT3/Modules/Common/Functions.json)
agrees with all eight selected native descriptor targets and pop counts:
AI, AI_GET_TURN, AI_GET_PRESSKOUDO, AI_GET_MYLV, AI_GET_MYAISYO, AI_GET_FUREA,
AI_CHK_ESCAPE and AI_ACT_SUMMON. Native instructions govern behavior and layout.

[DDS transfer](battle-ai-execution-transfer.json) independently checks seven
same-name community descriptors. No selected complete body resolves uniquely;
the tiny AI wrapper has21 unconstrained static candidates. Names and common
engine structure remain leads, without transferring Nocturne record layouts
or claiming DDS execution.

## Current coverage and next work

The current audit counts **1,541 integrated functions /8,979 (17.162%)**,
**225,832 recognized integrated body bytes** and **708,225 aggregated cases**.
The [original embedded-script census](battle-script-frontier.json) now covers
**52/63 used IDs** and **6,735/7,178 static uses**. The remaining **11 IDs** expose
**41 direct bodies /3,632 bytes** at compared boundaries: battle camera, panel,
formation, event, press/nakama and AI-change commands. AI-change toggles are
small flag operations; presentation/event wrappers lead into additional bodies.

Continue these commands and unchanged original BF procedure paths, then broader
battle execution. Finite instruction comparisons do not establish dynamic
scheduling, physical gameplay, arithmetic FCSR flags, timing, invalid-pointer
behavior or a matching executable. Work remains saved in place with one rolling
capture for this subsystem and no checkpoints.
