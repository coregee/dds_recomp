# Native battle support scaling and packed affinity

Four complete routines in `src/battle_affinity.c` and `.h` compile and pass
**2,560 original-instruction comparisons**, executing **627,533 steps** and
every **394 main instruction address**. They contribute **2,160 recognized
body bytes**. Actual process/party/unit getters, support counters and bounds,
skill attributes, base affinity, passive scans and folded moon execute. No
fixture supplies a callee's game result.

| Original entry | Recovered role | Recognized bytes | Cases |
|---|---|---:|---:|
| `00267F58` | `nbSetHojoAddCounter` | 212 | 512 |
| `002684B0` | `nbGetHojoRitu` | 360 | 512 |
| `00267890` | `nbGetAisyo` | 1,416 | 1,024 |
| `00268EB8` | `nbGetVirtualAisyo` | 172 | 512 |

## Verified original behavior

`nbSetHojoAddCounter` resolves the actual party, reads a signed halfword at
party `+8 + low_type*2`, adds the low delta as a wrapping word and clamps
only when the **full signed64 type is 0..19**. The original calls each bound
again when that bound clamps the result; the recovered source keeps that
sequence. A zero **full64 preview argument** commits the low halfword. Its
return is the sign-extended wrapping word difference from the old value,
including preview mode. A null party returns0. Compared cases include
negative backed offsets, invalid types, dirty high lanes, null parties,
signed16 extremes, word-addition wrap and preview with only bit32 set.

`nbGetHojoRitu` resolves the unit before reading its support counter. For
unit ID `125` it adds `(folded_moon - 4)/2`, using signed truncation toward
zero. Types6/7 transform negative counters to `-2*counter` and positive
counters to `-counter`; other types double positive counters and retain
negative counters. Zero retains1.0. The nonzero path executes native
`CVT.S.W`, adds8.0, then multiplies0.125. Full64 type4 additionally multiplies
2.5 when counter15 is positive. The recovered function returns float in
**F0**; the host test adapter preserves its raw bits. Nine original COP1
sites, including branch-delay arithmetic, are body/opcode pinned against
the existing EE value provider. Arithmetic FCSR flags and timing are outside
that value comparison.

`nbGetAisyo(skill,target,attribute)` first resolves the actual unit. A target
whose full signed64 index is at least16 tail-calls `datGetAisyo`; that path
does not perform the party/passive/support adjustments below. For other
targets it resolves the party, recognizes only the full64 `-1` attribute
sentinel as0 and returns100 for attributes12..15. The remaining path:

- Reads a signed word at party `+30 + low_attribute*4`.
- Uses a positive counter19 as an alternate affinity row, with **16 words
  per row** at `003A7FE0`.
- Replaces the base for exact low12 status200 or400 using tables
  `003ABDA0` and `003ABD60`, respectively.
- Adds bit10000 for positive temporary counters10/9/12/11 when the full64
  attribute is1/2/6/7, respectively.
- For nonnegative full64 skill IDs, excluding attributes5/11, reads the
  original action kind byte at `003D799A + low_skill*3C`. Kinds0/1 use
  positive counters14/13 to add bit20000.
- For unsigned full64 attributes0..10, excluding5, scans actual possessed
  passive skills. Attributes0..4 check `143+a`, `14D+a`, `152+a`, `139+a`;
  attributes6..10 check `142+a`, `138+a`. The first three applicable groups
  contribute10000/40000/20000. The last group scales the low16 rate using
  a **signed LH** factor at `003DC268 + coefficient_index*8`, a word product
  and signed division by100. The coefficient index is `a` for0..4 and `a-1`
  for6..10.

The final result is **`(packed & FFFFFFFFFFFF0000) | signed_word_quotient`**.
The quotient is not masked back to16 bits. Negative or large coefficients
can therefore affect higher result bits; replacing this with a conventional
unsigned packed-rate update would change original behavior. Compared cases
include all switch arms, inline and demon-descriptor passive lists, mixed
flags, signed coefficients, status overrides, alternate rows, negative
attribute prefixes, dirty raw arguments and the direct target>=16 path.

`nbGetVirtualAisyo` ignores source formation, calls the actual signed-byte
skill attribute reader, excludes `-1` and attributes12..14, then invokes
the full affinity path. Its result priority is **20000, then40000, then10000**,
otherwise0. Attribute15 remains allowed through this wrapper and is handled
by the underlying affinity routine.

## Unity and community evidence

Reviewed Unity roles are `nbCalc$$nbSetHojoAddCounter` at `18264A560`,
`nbCalc$$nbGetHojoRitu` at `182645F00`, `nbCalc$$nbGetAisyo` at `182643610`
and `nbCalc$$nbGetVirtualAisyo` at `18264A060`. Their metadata is decompiled,
with no lock calls or opaque lock stubs. The add-counter HD pseudocode has
a damaged switch with bad instruction output; its recognizable calls and
preview store establish a role, while **original PS2 instructions establish
the complete implementation**. Managed arrays, guards and layouts do not
establish PS2 byte identity or original C typedefs.

The [randomizer Pierce patch](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/asm/src/pierce.asm)
at revision `f74e85c0f632b751eaf278046884961c618c8541` supplies another
consumer lead for `003D6998 + skill*8`. Its `.org` patch/injection sites
are RAM addresses `00265B80` / `002FE2D0`; the audit records original bytes
at the first site. Its injected reader uses **LBU**, whereas original
`nbGetNormalSkillAttr` uses **LB**. The patch changes Pierce behavior;
its labels are not original symbols. No patch was applied.

The [DDS battle-table documentation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
at revision `bec33411543cdc487bad9debdf758f0090a2242c` describes packed
low-rate/high-flag affinity values and temporary affinity effects. This is
useful related-engine context. Its **19-entry rows** differ from the
**16-word stride** proved by these Nocturne instructions. Numeric selectors,
flags and layouts are not transferred from the documentation.

The original target is USA `SLUS_209.11`, SHA256
`a26e86e59cab447d9b1839ec11ab82b1557230bcc99746b78e3b5d4359dcc6ff`.
For its checked ELF segment, RAM `003A7FE0` maps to **ELF file offset
`002A8FE0`**. Community URLs/revisions/content hashes and native field
windows are recorded in `battle-affinity-community.json`. Strict complete-span
DDS search resolves no selected counterpart. Shared signatures preserve
structural leads and explicit limits.

## Integration and limits

All four Ghidra interfaces are saved in the existing working project,
independently reopened and checked, with float F0 storage for the ratio.
Four selected current exports decompile and merge into the8,979-entry
inventory. The affinity export removes a constant-condition dispatch block;
original execution comparison still reaches all247 main addresses in that
body. Canonical source is the behavior-checked reconstruction.

The support-access, targeting, filter and work-access batches were compared
again against their existing rolling captures after test memory routing
changed. All **11,136 affected comparisons** pass; they are already counted
in their respective reports and are not added again to the aggregate. No
new full-suite capture or checkpoint was created. The earlier minimum-bound
raw Ghidra switch rendering remains separately documented; its canonical C
is complete and compared.

Current source hashes agree across **108 focused reports**: **1,435 unique
integrated routines**, **217,317 focused cases** and **680,001 aggregate
cases**, including the historical462,684-case full run. The direct AI frontier
is now **18 unresolved bodies /10,484 bytes**, with no missing exports.
Continue estimates/support evaluators and scorer `00286B68`, then single/group
and automatic target dispatch. Finite backed data/indices and acyclic queues
were compared; arbitrary malformed pointers/counts, private stack aliases,
physical PS2 execution, full gameplay and a matching executable remain
unproved.
