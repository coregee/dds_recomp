# Generic effect dispatch and recursive PCP cleanup

`src/effect_recursive_release.c/h` adds eighteen complete original routines:
three table dispatchers and fifteen recursive cleanup bodies. All **1,216
original-instruction/C comparisons pass**, covering **1,876 summed body bytes**
and every one of the **384 main instruction addresses**. The affected C builds
with warnings treated as errors. All eighteen interfaces were saved and checked
after reopening the working Ghidra project, then exported in place.

The comparisons execute 1,370,892 original steps, 16,188 entries into the new
routines and **15,198 original destructor callbacks**. Full declared RAM,
Status, primitives, callee saves, ordered callback targets and raw 64-bit child
arguments agree. Eighteen semaphore calls and six diagnostic cases /149
independently checked bytes also agree. The rolling evidence is
`effect-recursive-validation.json`; no full-suite run is claimed.

## Original table dispatch

Offsets are hexadecimal. Each dispatcher invokes its original callback before
releasing its wrapper pool slot. No bounds or null guards are added.

| PS2 entry | Role | Kind | Original table | Record stride | Callback | Child |
|---|---|---|---|---|---|---|
| 0015AB58 | dds3EffectDelete | signed LW +00 | 00316EF8 | 30 | +00 | +08 |
| 00175A08 | dds3EffectPartDeleteO | LHU +00 | 0031DE40 | 28 | +08 | +04 |
| 00175FB8 | dds3EffectPCPDelete | signed LW +00 | 0031DF90 | 28 | +08 | +08 |

The child loads occur in original JALR delay slots. The observer records their
operands without bypassing either the load or the actual callee. Separate entry
traces check recursion order and argument transport. All five inspected generic
kinds and all 65 inspected PCP kinds execute through real recovered dependencies.
Effect-part kinds 0, 1, 2, 4, 5 and 6 execute; kind3 remains the unrecovered model
callback. The callback adapter aborts on unsupported targets. Source dispatch
preserves the original target through its callback interface.

## Recursive ownership

Fixed cleanup families retain their original 24, 16, 13, 12 and 21 child calls.
0018A5D8 visits each +5C entry before the corresponding +20 and +1C pair;
001902C8 visits the +90, +74 and +58 bands in that order. These are not reordered
into ascending address traversal. Large descriptor 0018B708 releases +134C,
then +1348, then memory-handle+1350.

Scatter routines 00183CF8 and 00184950 gate their child arrays on a nonzero
owned handle. They capture the original count, reload the array pointer for each
child, release the array handle, clean up their Scatter resource and then free
their descriptor handle. Their count/array/handle triples are +88/+8C/+90 and
+78/+7C/+80 respectively.

00190BF0 skips child cleanup when +108 is nonzero but still releases its pool
slot. Otherwise it visits fixed children and three optional arrays. Array lengths
come from the low 32-bit product of +B4 and +7C/+80/+84, sign-extended as in the
original MULT result. Each live array pointer is reloaded; null child entries
are skipped. The original signed LW lanes and unsigned comparisons are retained.

001948E0 first visits +58 track children at 24-byte stride through +164. It then
visits four effect-part entries per track through optional +174, skips null
entries and releases handles +178 and +17C in the original order.

Fixtures use finite backed trees, independent pool slots and valid memory-handle
neighbors. Dynamic cases cover zero and nonzero counts, absent and present
arrays/handles, null array entries and both +108 paths. The particle fixtures
retain independently checked diagnostic output from the earlier ownership work.
Arbitrary cycles, malformed ownership and unbacked lengths remain unproved.

## Unity and DDS correspondence

Three retained Unity roles are reviewed: `effManager$$dds3EffectDelete` at
1823E4680, `effPart$$dds3EffectPartDeleteO` at 18277C540 and
`effPart$$dds3EffectPCPDelete` at 18277B010. Their managed guards, layouts,
delegate machinery and inlining differ from the native implementation. Most
individual PCP variant names remain descriptive native aliases.

All **eighteen selected complete DDS spans** resolve. Original incoming calls
first constrain the general and part dispatchers; reviewed table relocation
then constrains PCP dispatch and disambiguates the two identical cleanup bodies.
Only the explicit dispatcher LUI/LW table immediates and native call targets
are masked. **77 callback positions and 55 callee links agree**.

| Inspected records | Nocturne table | DDS table | Bytes |
|---|---|---|---|
| 5 generic kinds | 00316EF8 | 0034DE20 | 240 |
| 7 effect-part kinds | 0031DE40 | 00353710 | 280 |
| 65 PCP kinds | 0031DF90 | 00353880 | 2,600 |

These are inspected records, not proof of complete table extent or runtime
selection. Part kind3 separately constrains the uncompiled model tail at
00175DF8 to DDS 00162DE0. Its 20-byte shape agrees with relocated tail targets
001DD220 and 002177D0. This is a lead for the remaining model cleanup chain;
neither model-callee equivalence nor DDS execution is claimed.

## Current progress

Integrated recovery is **1,378 /8,978 recognized functions (15.349%)**,
**660,538 aggregate comparisons** and **195,488 summed original body bytes**.
The last full run remains 413 functions /462,684 cases; 965 additional routines
contribute 197,854 focused cases. All 101 registered focused reports refer to
current source. There are 622 reviewed HD counterparts, 46 library identities,
753 descriptive PS2 aliases and 274 shared transfer signatures.

The effect-table audit now has **one unrecovered unique target**, the model
destructor, and no unexported targets in the inspected records. The selected
camera/model lifecycle graph has **nine direct bodies /1,368 bytes remaining**.
Model ownership and its indirect resource/movie cleanup are next. Physical
rendering, scheduling, console runtime execution, DDS execution and a matching
binary remain outstanding. Recognized functions do not prove complete code
discovery. Changes and rolling evidence are saved in place without checkpoints
or routine backup copies.
