# Shared emitter initialization and drawing ownership

Fifteen complete original bodies /1,984 bytes are integrated in
[emitter_initialization.c](../src/emitter_initialization.c). All2,816 fresh
original-instruction comparisons pass. The fifteen saved interfaces were
independently reopened, and all fifteen decompilations merge into the working
inventory. The full executable remains the goal; actual copy constructors,
outer motion effects and physical runtime remain outstanding.

## Research incorporated

Six community files at Megami-Decomps revision
`bec33411543cdc487bad9debdf758f0090a2242c` are linked and hashed in
[the reference review](emitter-initialization-matches.json).
[The particle manager](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/parManager.c)
and [drawing-kind API](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/par_kind_api.h)
guide interpretation of the shared `0x150` header and four resource kinds.
Native Nocturne fields and consumers establish the actual ownership and reset
behavior. No upstream implementation replaces a recovered game dependency.

[Billboard research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/billManager.c)
and [its API](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/bill_object_api.h)
inform P2A prefix/descriptor/texture ownership and frame selection. Native
source retains unchecked null-resource reads, signed modes and dirty allocation
fields. Twelve inspected cache descriptors remain their original kind0 values;
kind1 creation is exercised independently through the unchanged factory table.
Do not infer support for cached P2A resources from the generic helper's name.

[Track source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effModelTrackPoly.c)
and [list definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/eff_track_poly_list.h)
supply model-list and ordinary/special track terminology. Actual Nocturne
model predicates, cut selection, allocations, colour history and resets execute.
The original special reset leaves additional dirty fields that HD assigns.

All fifteen Unity roles are reviewed. The proposed `dds3SpPolyReset` identity
for `001656F0` is rejected: it dispatches a whole special polygon. The reviewed
`parManager.dds3Particle_EffectReset` instead has the four drawing-kind routes.
The separately recognized point-history reset has the HD
`dds3Particle_BlurReset` role. Managed bounds/null checks and allocation layouts
remain reference context rather than native behavior.

## Bodies and boundary repair

| Native entry | Recovered role |
|---|---|
| `0015CAF0` | P2A animation resource import, texture owners and descriptors |
| `0015C2C8` | Animated billboard allocation and initial frame binding |
| `0015CDB0` | Actual two-kind billboard factory and basic initialization |
| `0015CF98` | Cached billboard clone and native resource retain |
| `0015D038` | Raw float scale stores |
| `0015D088` | Billboard mode and per-frame flag selection |
| `0015D3E8` | Animated colour-advance flag |
| `0015DF58` | Shared emitter state, billboard and drawing-kind initialization |
| `001656F0` | Four-kind history/vertex/model-list reset dispatch |
| `00164748` | Selected sixteen-byte point-history slot reset |
| `001A3510` | Owned model-track pointer list and actual child creation |
| `001A3640` | Selected list child reset |
| `001A3170` | Model predicate selecting ordinary/special reset |
| `001A3980` | Hermitian history reset |
| `001A51C0` | Special bundle reset with actual child history reset |

[Boundary discovery](emitter-history-reset-discovery.json) proves the kind1
tail jump at `00165744` reaches `00164748`. Ghidra had absorbed the complete
twenty-byte helper into the unrelated, uncompiled function at `001614F0`.
Only that remote tail is separated; the caller retains596 original owned
bytes. Five original words and the return delay slot establish the helper.
The inventory becomes8,986 functions; discovery alone adds no source credit.

## Original private-frame behavior

Kind4 initialization writes a fifty-two-byte parameter record but leaves its
first twenty bytes unassigned. Tests declare those bytes before native
execution and pass them through real model-track creation. They are independent
input state, not values read from a native result or substituted game returns.
Retail selection and the caller's real frame contents remain research work.

A second copied word requires more than the initial random stack seed. The
list's preceding allocation at `002A9038` executes `SD s0,0(sp)` at `002A9040`.
The high half lies at list-SP minus`0x2C`, exactly the later model constructor's
private `+24` word. The list does not assign S0 until that allocator returns.
For common initialization, S0 is the raw work argument; for a standalone list,
it is independently declared incoming caller S0. Original instruction words,
frame offsets and the surviving write are recorded in the reference review.
The C replay derives the copied word from those inputs, without reading native
output. All256 child-padding transports agree in complete owned RAM.

## Comparison and SMT transfer

[The focused proof](emitter-initialization-validation.json) executes10,597,784
original steps and3,060,015 vector instructions. It checks420 actual TMX uploads,
793 ordered factory callbacks,99 connected creation/reset sequences,341 C.EQ.S
and126,556 other COP1 comparisons. All401 reachable selected main addresses
execute. The remaining one of402 is a separately proved impossible extra return
in the unsigned-halfword kind dispatch at `0015D088`.

Declared RAM, defined raw returns, Status, callee saves, COP1 condition and
defined VU/ACC/Q agree. VF2.ZW unused implicit CPU upper scratch is excluded
only when scalar QMTC2 executes. The actual factory and property pointers remain
unchanged, and both billboard constructors execute their recovered dependencies.
The zero-address P2A resource reads use explicitly backed test input, without a
fabricated null fallback. Full hardware flags/timing, arbitrary aliases,
exhausted/overflow allocations and physical rendering remain unproved.

[Static transfer](emitter-initialization-transfer.json) resolves eleven complete
DDS spans. A124-byte factory span additionally checks the separated LUI/ADDIU
table address and BasicInit JAL, constrained by the original two-kind table and
an independently matched kind1 constructor. Other differing instructions are
not masked merely to manufacture a correspondence.

[The layout audit](emitter-initialization-layout-variants.json) independently
decodes two useful differences: Nocturne's P2A allocation adds76 bytes per
texture where the DDS semantic candidate adds80; the cache descriptor index
uses an8-byte stride where DDS uses12. These bodies remain semantic variants,
not full-span matches or proof of DDS execution. Carry native widths and record
geometry into later SMT transfer work instead of assuming DDS types fit.

[Affected regressions](emitter-initialization-regressions.json) pass28,880 prior
prerequisite, Magatuhi, billboard, motion, retail and ownership cases against the
same rebuilt host. Prior ownership/release paths are checked in those regression
groups; the new connected sequences exercise creation followed by reset.
The earlier enormous negative-count gradient remains explicitly unvisited.
No new whole-suite or physical gameplay run is claimed.

## Next work

[Current progress](recovery-progress.json) is1,852/8,986 recognized functions
(20.610%), with313,683 focused and776,367 aggregate comparisons across137
reports. The expanded [motion-effect graph](model-motion-effect-frontier.json)
includes both billboard factory targets and the original reset tail jump:
45 pending recognized descendants /6,620 bytes, with no missing exports at its
inspected boundaries. Other frontiers overlap and must not be summed.

Continue the thirteen common emitter copy constructors and four special polygon
constructors, including their real initialization/RNG/reset dependencies and
caller-frame contents. Then recover generic copy kinds0..2 and the outer group
motion-effect change at `001DD440`. Associate original assets with these paths
before claiming retail kind4 behavior, complete scheduling or a matching binary.
Source and reports are saved in place; no checkpoint or backup copies were made.
