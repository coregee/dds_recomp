# Billboard copying and native animation records

Eight complete original bodies are integrated in `src/billboard_copy.c`, adding
1,240 recognized body bytes. [The comparison](billboard-copy-validation.json)
passes 1,536 cases and reaches all 270 selected main instruction addresses.
Actual allocation, texture construction/upload, animation binding and diagnostic
calls execute; no original callback table or game return is replaced.

| PS2 entry | Recovered role | Cases |
|---|---|---:|
| `0015B1B0` | Texture-backed billboard resource owner | 128 |
| `0015C1E8` | Common draw-state initialization | 128 |
| `0015C230` | Normal billboard allocation | 128 |
| `0015C350` | Animated billboard copy | 128 |
| `0015C908` | Bind one animation frame record | 128 |
| `0015C940` | Select empty, single, dual or plural animation | 384 |
| `0015CEA0` | Billboard copy and shared-resource retain | 256 |
| `001DF5C8` | Model effect resource's billboard-copy callback | 256 |

## Community and HD evidence

The DDS project's [billboard reconstruction](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/billManager.c)
and [API definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/bill_object_api.h)
provide independent record and ownership context. The source-unit notes and
`eff_bill.h` were also inspected at that revision. Their links and content
hashes are retained in [the review](billboard-copy-matches.json).

The original consumers corroborate 20-byte animation descriptors, 24-byte
frame/plural records and 20-byte resolved outputs. Signed halfword frame delays
and plural start delays are retained. Native flag `10000000` selects plural
records; mode bits `C0` select two entries; bit `100` prints a polygon diagnostic.
These definitions guided the cases independently of a Unity match.

One reviewed community initialization differs: `billAllocChild` clears its
child pointer before testing the texture argument. Nocturne `0015C230` leaves
word `30` dirty when its full-width argument is zero. The recovered C preserves
the original instructions, including subsequent initialization overwriting only
the fields actually written by `0015C1E8`.

Six Unity roles were reviewed, including the animated-copy/selection bodies and
the model resource callback `mdlEffectDup_P2A`. Managed null/bounds checks,
reference arrays, allocation differences and changed field layouts supply role
context only. `001DF5C8` is the billboard callback; `001DF600` calls the separate
generic effect copier and remains pending.

## Original behavior and connected verification

Static copies increment the child resource's word `8`. Animated copies increment
word `14`, allocate `count*20+6C` bytes and rebuild frame outputs from the shared
descriptor data. Original loads and reloads remain in their native order.
The model callback then increments its own resource word `4`; these are distinct
ownership counters, including native low-word wrapping.

The texture-backed resource allocates `44C` bytes through the actual memory
handle routines and places its owner after a `400`-byte drawing area. Actual TMX
construction, VRAM allocation, image copy and DMA queue submission execute.
The native width/height conversion uses signed twelve-bit values and separately
shifted half sizes; cases around widths 2047, 2048, 4095 and 4096 check that
arithmetic rather than assuming an ordinary unsigned dimension conversion.

The comparison checks 2,029,678 original steps, full declared RAM, defined raw
returns, Status/CPU primitives, callee saves, COP1 state and all 210,432 compared
VU/ACC/Q words. There are 288 actual image uploads, 96 constructor preludes and
256 consecutive animation selections. Diagnostic output goes through the real
recovered variadic formatter. These selections do not constitute frame updates.

The capture records incidental V0 after void calls. The verifier now checks
consecutive results only where an ABI return is declared, while retaining every
call, call-count, RAM, operand and processor comparison. The 320 excluded values
are void-call V0 scratch, not defined game returns.

[Saved interfaces](billboard-copy-abi.json) pass after independently reopening
the working project. All eight corrected decompilations were exported and
merged into the current inventory. [Affected regressions](billboard-copy-regressions.json)
pass another 17,808 existing motion/track/retail cases on the same rebuilt host.

The host memory map extends the existing diagnostic string range contiguously.
No separate overlapping texture-global span is needed: that range was already
backed. Failed rolling captures were overwritten; no checkpoint, project copy,
frozen source tree or duplicate vector capture was created.

## Transfer and remaining work

[Complete-span static DDS comparisons](billboard-copy-transfer.json) resolve six
counterparts: `00151178`, `001512E8`, `001518A0`, `001518D8`, `00151E60` and
`00219E30`, with thirteen checked call links and the selection diagnostics'
relocated addresses. Texture-resource construction and normal allocation have
no full-span candidate. This is static correspondence, not DDS execution.

The new [motion-effect frontier](model-motion-effect-frontier.json) decodes the
original five-case PIB dispatcher and both actual T0 copy callbacks. It also
includes the five established generic effect-copy kinds and 22 actual nested
copy/constructor pointers, exposing 79 pending recognized descendants /13,552
bytes. The inspected prefixes cover thirteen common-polygon copies, four
special-polygon copies and five line constructors; full table extents and
asset selection remain unproved. This graph overlaps the existing action, hit-effect and part/PCP graphs;
their counts must not be added.

Continue generic copying and its real indirect constructors, then effect-record
creation, unlink/free and the motion-change composite at `001DD440`. The native
hit-effect graph still has thirteen pending direct bodies /2,036 bytes. Its
part/PCP copy-scale graph now has 293 pending recognized bodies /48,348 bytes
and seven missing exports.

Connected texture cases use one nonpaletted mip with image sizes above 1,024
bytes, so the original image-transfer path assigns its queue handle metadata.
The adapter's initially unused scratch word is overwritten by the actual
allocator; it does not supply a game result. Other texture modes retain their
separate earlier evidence and are not claimed as connected billboard coverage.
Malformed ownership, exhaustion, asset loading/selection, physical PS2/GS
runtime, full processor timing/flags and a matching executable remain unproved.
Whole-program recovery remains incomplete.
