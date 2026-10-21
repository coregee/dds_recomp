# Complete render DMA vertex consumer

`002B9048` is recovered as `ps2RenderConsumeDmaVertices`. The complete 304-byte
body is integrated into the main recovered library. All 70 main instruction
addresses execute in 258 fresh original-instruction comparisons. Ghidra's
five raw64 arguments (`A0,A1,A2,A3,T0`) and raw64 `V0` result were applied,
checked after reopening, and exported in place.

The original 177-pair VU0 program executes actual VIF input packets in a pinned
PCSX2 interpreter reference. Golden game records are used only for comparison
after execution. Both actual captures reproduce every record word: type7 has
40 vertices in two batches, and type8 has eight vertices in one batch.

## What the recovered function does

The consumer processes at most 24 vertices per batch. It computes QWC from
the wrapping word product `stride * batch`, overhead and alignment; writes
QWC, masked source address and DMA start in original order; advances the
source cursor; and polls CHCR and VIF status before the interlocked VU read.
Nonpositive signed raw64 counts preserve the original raw64 source result.

Four VU quads become each 96-byte output record: position at `00`, normal at
`10`, colour at `20`, and UV at `30`. The metadata load reads the low halfword
of UV.W through VI10. Its upper16 state, signed CFC2 result and full128 PEXTLB
transport are retained before the word store at `50`. Bytes `40..4F` and
`54..5F` remain untouched. Reads precede stores in each record, preserving
backed source/output overlaps.

The comparison covers 5,526 producer vertices, 369 DMA batches, 2,762 ordered
MMIO events, 26 source/output overlaps and 16 nonpositive-count cases. It
compares all declared RAM, all 4KB of VU data, the complete version-bound
1,680-byte VU register state, 8,256 CPU upper words, raw64 returns, Status,
FCSR and callee saves. Twelve affected families contribute another 27,392
passing cases on the rebuilt main library. The last whole-suite capture is
unchanged; no new full-suite claim is made.

## Independent references and SMT transfer

[DDS3 Model Studio's type7 batches](https://github.com/tge-was-taken/DDS3-Model-Studio/blob/92f350749ab24dcfd7c35b8fac105a5c1883d771/Source/DDS3ModelLibrary/Models/MeshTypes/MeshType7Batch.cs)
and [type8 batches](https://github.com/tge-was-taken/DDS3-Model-Studio/blob/92f350749ab24dcfd7c35b8fac105a5c1883d771/Source/DDS3ModelLibrary/Models/MeshTypes/MeshType8Batch.cs)
provide independently checked packet layouts and entry20/22 activation leads.
Three extracted retail streams and both runtime captures corroborate the
selected layouts. Type7 uses overhead `12*N+20` and stride `28*N+8`; type8 uses
28 and 32. The parser's sign property does not replace primary VIF USN semantics.

[Megami-Decomps' sdf model source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfModel.c)
supplies context. The complete DDS peer at `002E06F0` is byte-identical to
Nocturne's consumer; live DDS producer behavior remains untested. The shared
SMT ledger now records this checked span and its device/record boundaries.
Unity's inspected VU wrappers are return-only, so they supply vocabulary rather
than a replacement for the PS2 DMA/VIF algorithm.

The [primary reference build](vu0-reference-build.json) uses pinned PCSX2
revision `b4d6e2aa7b9069162fa0e7cbc45ae95fc2566f39`, preserving its pair runner,
register-use analysis, pipelines, operation bodies and stop/continuation
semantics. [Macro checks](model-render-dma-macro-audit.json) preserve the actual
CTC2, VLQI, VILWR and CFC2 state effects, including VI backup history.

## Limits and next recovery

The selected unmasked VIF decoder assumes cycle1/1 and mode0. DMA/VIF readiness
is finite external test input, and micro stages complete at E before stopped-VU
macro reads. Concurrent EE/VU wall timing, cache coherence, VIF/GIF/VU1 hardware
behavior and installed microVU equivalence remain unproved.

Unknown initial VU bytes and UV-transform upper halves are zero-filled for
the actual capture replay. Record agreement therefore establishes those
outputs, not full captured pipeline/local-memory equivalence. Synthetic cases
explicitly initialize the complete local memory for full reference-state checks.
Direct DebugServer VU memory reads remain invalid; the host scan did not verify
the resident microprogram image.

Next recover the complete `002B9178` renderer, including its 2,372-byte contiguous
span, positive type7/type8 paths, real matrix/light/material setup, optional
secondary UV stream, packet construction and finalizer. Its direct helpers now
all have compiled comparisons. The outer placement/update paths and whole
executable remain unfinished. Work was saved in place without checkpoints.

Evidence: [consumer validation](model-render-dma-validation.json),
[actual record replay](model-render-dma-replay.json),
[regressions](model-render-dma-regressions.json),
[reopened interface](model-render-dma-abi-check.json),
[static/source leads](model-render-dma-leads.json), and
[current progress](recovery-progress.json).
