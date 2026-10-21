# Original model track construction

Eight complete original PS2 bodies /1,656 recognized bytes are integrated in [model_track_creation.c](../src/model_track_creation.c). Recovery is **1,798/8,982 recognized functions (20.018%)**, with 263,296 recognized body bytes, 302,419 focused comparisons across 133 reports and 765,103 aggregate comparisons. These totals include repeated dependency comparisons; they do not prove whole-program reconstruction.

## References and recovered behavior

The pinned community [DDS track-polygon source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/effModelTrackPoly.c), revision `bec33411543cdc487bad9debdf758f0090a2242c`, supplies independent history/gradient terminology and owned-field context. The same revision's [model motion API definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/mdl_motion_api.h) provide adjacent controller context. Native instructions decide Nocturne's offsets, arithmetic, allocation and defaults. Upstream source is inspected as reference, without being copied or linked into the recovery.

The [reference review](model-track-creation-matches.json) pins these sources and five inspected Unity counterparts: Hermitian track creation, gradient setting, color blend, sword-track creation and model-track creation. Managed fields, arrays and initialization guards are separate from PS2 layouts. In particular, Unity's color helper returns the first color for nonpositive rates, whereas the PS2 helper extrapolates negative rates. The native special-model cut9 branch uses length5 and rate0.025; the inspected HD cut9 branch uses face10 and rate0.05. Neither HD change is imported.

| Original entry | Recovered body |
|---|---|
| `001A3868` | Allocate track history, color table, owned footer and draw material |
| `001A39A0` | Store the raw draw-kind word |
| `001A39A8` | Fill alternating color gradients using original pair-wise frame arithmetic |
| `001ABBD0` | Packed VU color interpolation, including negative extrapolation |
| `001A4280` | Construct the special track bundle and constant gradient |
| `001A2F38` | Construct ordinary or special-model track work from its parameter record |
| `001DCD60` | Clear old blur and initialize a packed-color transition |
| `001DF820` | Read the native effect record and forward color-transition operands |

History has `(length*steps)*2+4` slots, each with16 vertex bytes and4 color bytes. A40-byte footer owns the memory handle and material. Allocation resets the shared44-byte draw state at `0056AF00`, sets flags4000 and the original index-table pointer `0031FFE0`. Actual pool, memory-handle and material consumers execute in the comparison.

Gradient uses the arithmetic-shifted count, converts it to unsigned float through the original negative-word path, divides1 by that count, and increments its amount once per endpoint pair. Negative counts imply enormous unsigned loops; the source preserves them. The packed helper returns the full incoming second color operand when amount is at least1; otherwise it executes the original vector unpack, scaling, interpolation, truncation and packing.

The native special-model predicate is major1 with minor192 or339..341. Cut9/10/17/18 choose the original lengths, kinds and colors; other cuts use the original default. The common rate comes from original GP-relative address `0054C9F0`, containing raw bits `3CCCCCCC` (approximately0.025). Ordinary construction retains its original length and six-way interpolation steps.

Color transition first calls actual `mdlFreeBlur`. Its signed64 count guard precedes low32 multiplication. Positive counts publish a zeroed48-byte record with original halfword fields, normalized start RGBA and a VU delta divided by the product. The effect-record wrapper retains its unsigned halfword reads and original fifth argument in T0. These fixtures start with no existing blur; nonempty transition replacement remains a subsequent connected integration target.

## Validation and explicit boundaries

- [Fresh native capture](model-track-creation/vectors.jsonl.capture.json): 1,536 cases /4,109,998 original instruction steps, declared RAM writes checked, no uninitialized-read warnings and a clean final capture log.
- [Passing C comparison](model-track-creation-validation.json): all seven other bodies reach every selected main address; the gradient reaches42/48. Total coverage is361/367. Its six negative-count conversion instructions remain explicitly unvisited, without an unreachable/dead-code claim. The verifier accepts only those individually declared gaps and leaves them visible in the report. Returning fixtures use finite backed allocations and bounded gradients.
- Actual arithmetic executes1,795,632 vector instructions and74,814 COP1 comparisons. The comparison checks208,320 defined VU/ACC/Q words, full declared RAM, raw defined returns, Status, callee saves and processor primitives. Only VF2.ZW are excluded when the new scalar-QMTC2 path executes: those two lanes retain implicit CPU upper-half scratch outside the canonical64-bit argument ABI and are unused by the selected scalar-X operations. All remaining135 words stay checked; rows without that path retain all137 checks. No game result or RAM is supplied to make the comparison pass.
- In147 special-model cases, the native constructor copies an untouched word from its private parameter frame. The host transport independently regenerates that word from the native harness's initial Java Random seed and stack position, before any original instruction. It does not read a native output or expected object field. Other native stack parameters use adapter-owned backed scratch restored after calling the actual recovered consumers. Arbitrary runtime stack padding, aliases, ownership and OOM paths remain unproved.
- [Reopened interfaces](model-track-creation-abi.json) pass for all eight routines, including A0/A1/F12 color blending and the five-register color transition. Working-project edits are saved in place. Corrected unsigned-DIVU export decompiles all eight functions with zero failed exports and merges the recognized inventory. The language-switch log's temporary `rom0` cache diagnostic does not replace the successful final export summary; the ABI and capture logs are clean.
- [Affected evidence](model-track-creation-regressions.json) checks1,536 new cases and16,272 existing motion/retail cases on the same rebuilt host. Existing rolling captures are reused, with current source/verifier/input/vector/DLL pins. No new full-suite run, checkpoint, project copy or duplicate capture is claimed.

## Transfer and next dependencies

The [complete-span DDS comparison](model-track-creation-transfer.json) resolves gradient `001A39A8→00188878`, packed color `001ABBD0→0018DD40`, color transition `001DCD60→00217310` and its record wrapper `001DF820→0021A088`, with six checked direct/tail-call constraints including dependencies. History, ordinary model work and special-bundle creators have no complete candidate under the current rules. The tiny draw-kind setter retains nine ambiguous candidates. Static correspondence does not prove DDS execution.

The refreshed [hit-effect frontier](battle-check1-effect-frontier.json) has13 pending direct descendants /2,036 bytes, down from21. The inspected part/PCP prefixes have300 pending recognized descendants /49,536 bytes and seven missing exports. The broader action graph has369 pending bodies /89,068 bytes, while the inspected motion graph stays closed. These graphs overlap and must not be summed.

Next recover the effect record creators, dispatch, unlink/free and motion-change composite: `001DF670`, `001DF770`, `001DF848`, `001DF968`, `001DFA00`, `001DFA78`, `001DFB00` and `001DD440`, including actual indirect copy wrappers `001DF5C8`/`001DF600`. Then recover the looping/nonlooping wrappers and remaining outer hit constructors. Do not replace those dependencies with fake callback returns. Retail effect/model associations, physical runtime, full scheduling and a matching executable remain outstanding.
