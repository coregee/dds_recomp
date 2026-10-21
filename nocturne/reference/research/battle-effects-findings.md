# Native affinity, HP/MP, status and support effects

Six complete routines in `src/battle_effects.c` and `.h` compile and pass
**4,096 original-instruction comparisons**, executing **6,266,140 steps**.
They add **5,488 recognized body bytes**. All **1,068 reachable main
instruction addresses** execute; five further MP addresses have an explicit
original dispatch-table proof of unreachability. Full declared RAM, raw64
word returns, F12/F0 values, Status, FCSR condition, CPU primitives, ordered
libc traces and native callee saves agree. The capture includes **120
original C.LT.S comparisons** and **8,092 libc kernel/CPU trace words**.

| PS2 entry | Recovered role | Recognized bytes | Cases |
|---|---|---:|---:|
| `00266130` | `nbGetAisyoRitu` | 528 | 512 |
| `00266350` | `nbGetKoukaHp` | 1,276 | 768 |
| `00266878` | `nbGetKoukaMp` | 1,012 | 768 |
| `00266D60` | `nbGetKoukaBadDamage` | 1,032 | 1,024 |
| `00267180` | `nbGetKoukaBadKaifuku` | 488 | 512 |
| `00268030` | `nbSetHojoKouka` | 1,152 | 512 |

Actual scheduler/work getters, packed affinity/passive/support paths,
physical/magic/healing/HP power, parameters, event bits, default RNG,
software-double conversion and original printf/formatter/dtoa/bigint/heap
dependencies execute. No game-result hook or skipped diagnostic supplies a
result. Seventeen existing power spans are extended/merged into eighteen
declared effect spans; there is one rolling fixture/capture pair.

## Original semantics

`nbGetAisyoRitu` obtains main, source and target work before reading the
signed action attribute. Attribute -1 and 12..14 bypass packed-rate scaling.
Otherwise the low16 rate becomes100 when it is zero and flags60000 are set.
A frozen target with status2 and a physical action also floors the rate
at100. Actual passive165 floors physical resistance and writes main+14C=1
when it changes the rate. Passive169 then supplies an independent1.5 boost;
without it, attributes1..4 use actual activated passives135..138. The rate
uses the original raw coefficient at RAM0054E530, not a rounded decimal.

HP and MP read the action record at RAM003D7998 / ELF file002D8998,
stride0x3C. Type fields are unsigned halfwords, powers and offsets signed
halfwords. HP type/power/offset are+16/+18/+1E; MP uses+1A/+1C/+20. The
original four dispatch tables at RAM00544A50/4A90/4AD0/4B10 are pinned in
the interface/context audits. Type0 and out-of-range types retain the
native -1 sentinel. Damage versus healing is selected by the **low word**
of the incoming selector, while the count guard uses signed **full64**
before division uses its low signed word.

Both dispatchers retain all fixed, percentage, physical/magic, HP-based,
healing, current-value and random-limit cases. Signed products wrap at32
bits before original signed division by100. Physical HP damage alone has
status40/200 reductions by2/10. Jitter draws the actual default random float,
subtracts0.5, doubles, multiplies the coefficient, multiplies the original
value, adds it, and truncates in the native COP1 order. Scaling then applies
the input F12 ratio and, when AF2 is set and the source is not player side,
the original enemy coefficient. HP changes zero damage to1 and caps types12
and13 by target maxHP; MP caps damage by currentMP and has no zero-to-one
rule. Healing mode returns the independent healing accumulator. The shared
C implementation preserves the distinct entry contracts and asymmetries.

The MP retail type6 table entry routes directly to00266B10. Thus the type6
conversion in its default block at00266ACC..00266ADC cannot execute: the
default block only admits types1/12/14, and none of its calls writes that
action type. These five instructions are distinguished from tested code;
their condition remains visible in canonical source. Ordinary constant100
and10 division traps cannot fire; dirty high lanes with a zero low count
divisor still retain BREAK7, but that trap path is not captured in this cohort.

Status kind1/3 selects the damage evaluator. Skill110's actual RNG100 draw
chooses1000/2000/4000/20/100/40 at thresholds40/60/70/80/90. Kind3 enumerates
mask bits0..13 and draws an actual random index; ordinary masks retain15
bits. Actual status-to-attribute lookup and packed affinity follow; flags
170000 reject an effect. Special guards for skills10A,103/104 and4F retain
their diagnostics and original full64/lowword conditions. Except status800,
the probability ratio comes from affinity low16/100. Chance255 or a nonzero
full64 preview skips the roll. Otherwise the original AF2/target-flag
coefficients, integer RNG100 draw, strict signed threshold comparison and
four-argument diagnostic execute. Successful effects use the original
**numeric status precedence**, not a rewritten bitset containment test.

Status kind2 is the recovery evaluator. It reads the low12 mask and, unless
chance255 or preview is nonzero, calculates chance from actual source and
target parameters2/5, integer parameter5/4, F12 and native COP1 operations.
Its original software-double diagnostic occurs before actual RNG100. **Both
preview and execution require an existing status overlap** to return the
mask. A preliminary interpretation suggesting opposite branches was
rejected after checking raw opcodes at00267314 and00267330; the capture
confirms the canonical behavior.

Support flags execute in native bit order, through actual AddCounter and
bound getters. Word negation, absolute differences and accumulation wrap.
Positive/negative clear flags400/40000 operate on counters4..8 and call the
actual setter **even in preview**. Earlier modifications can affect later
operations, so a collection of independent mock results cannot replace
the original sequence.

## Community and Unity evidence

The inspected [randomizer Pierce assembly](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/asm/src/pierce.asm)
contains a `PIERCE_NOP` at RAM00266250 / ELF file00167250. Native instructions
show this is the nonphysical-action rejection before passive165's resistance
floor. The community patch removes that physical-only condition; it has
**not** been applied to our original ELF or canonical behavior. Its separate
00265B80 injection is attributed as modded behavior. The pinned
[research notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
identify USA SLUS_209.11 and the file/RAM offset convention. This is useful
context for interpreting addresses, not proof of routine semantics.

The pinned [DDS battle-table documentation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
provides related action/affinity vocabulary. DDS action rows are0x38 versus
Nocturne0x3C, and affinity rows are19 versus16 words. Native consumers govern
field width, offsets, numeric guards and coefficients. Direct URLs,
revisions, content hashes, tables and original branch bytes are recorded in
`battle-effects-community.json`.

Six reviewed nonopaque Unity bodies establish the named roles. Managed
layout, difficulty configuration and altered Pierce handling remain separate
from original PS2 behavior. The strict full-span DDS search resolves **no
selected counterpart** for these six routines. RNG and libc dependency
candidates remain separate from selected identities; the tiny physical
healing tail still has147 unconstrained shape candidates and is not promoted.

## Integration and limits

All six custom interfaces are saved in the working project and independently
reopened. The current selected export completes6/6 with no decompilation
failure and merges into the8,979-function inventory. **15,232 affected existing
power/affinity/support/targeting/filter/work comparisons** pass again against
their existing captures; those repeats are not added to aggregate coverage.

The source audit now reports **1,446 unique integrated functions /16.104%**,
**212,296 recognized body bytes**,110 focused reports and **685,633 aggregate
cases**. The current AI frontier has **seven unresolved bodies /2,824 bytes**:
estimator00268F68, scorer00286B68, single/group selectors00287508/27778,
automatic target dispatcher002879F0, command5200287EE0 and helper0028B528.
No unexported direct target remains. The separate minimum-support raw Ghidra
switch-rendering limitation remains recorded.

Validation uses backed finite indices/queues, returning library paths,
bounded string stdout and nonempty random masks. Arbitrary invalid pointers,
zero random limits, private stack aliases, arithmetic FCSR flags, timing,
physical PS2 gameplay, a matching executable and a new full regression remain
unproved. No checkpoint, backup, project copy or duplicated capture is created.
