# Original model draw prerequisites

Verified against `SLUS_209.11` instructions on 2026-10-14. Eight complete C bodies
cover 508 original bytes. The [proof](model-draw-prerequisites-validation.json)
passes 3,328 cases, all 118 measured main addresses, complete declared RAM,
defined returns, Status/FCSR condition, all 128 VU words, ACC/overflow/Q and
intermediate/final clip state. Full drawing and spawn-once update remain pending.

| PS2 entry | Recovered role | Bytes | DDS counterpart |
| --- | --- | ---: | --- |
| `002b1838` | Eight-corner bounds clip mask | 276 | `002d8cb8` |
| `002b66b8` | Load VF24..27 and tail-compose | 36 | `002ddd60` |
| `002b0970` | Node/frame matrix DMA reference | 68 | `002d7df0` |
| `002b9b38` | Raw draw word store | 8 | `002e11e0` |
| `002b9b40` | Compare cache key and copy vector | 40 | `002e11e8` |
| `002b9b68` | Raw f12 float store | 8 | `002e1210` |
| `002b1808` | Four surface pointers and tail initialization | 44 | `002d8c88` |
| `002c8188` | Install pool/ordering callbacks | 28 | `002efd30` |

Bounds loads six words through unaligned LDR/LDL and signed LW, with native
PCPYLD packing into VF2/3. Their W lanes are signed Z extensions, not inserted
homogeneous coordinates. Eight corner transforms preserve VU MULAx/MADDAy/z,
VF0.W translation, VF4/5 interleaving and final ACC/overflow state. Two control18
reads collect the first/final four six-bit clip groups. Their intersection
returns the six plane bits. The 2,048 bounds cases include 512 independent identity
masks, unaligned records and raw sign/subnormal/extreme/random encodings.

The cohort compares 19,712 intermediate/final clip values and 455,936 VU/ACC/Q
words. Its 394 aliases cover packet/source overlaps, cache/global self-copies and
callback stores overwriting surface-array words. The packet uses node+30 plus
frame shifted by 7, wraps in 32 bits, masks 28 address bits and writes native tag/VIF
words in order; its packet+10 return sign-extends ADDIU. Vector caching compares
a sign-extended stored key against the full incoming 64-bit argument, then stores
the key before reading object+10. Raw f12 settings use no arithmetic.

Both actual clip helpers pass 69,811 cases against a separately compiled,
unmodified `_vuCLIP` body from
[PCSX2 VUops.cpp](https://github.com/PCSX2/pcsx2/blob/b4d6e2aa7b9069162fa0e7cbc45ae95fc2566f39/pcsx2/VUops.cpp).
[C results](vu-clip-values-validation.json), [Java results](vu-clip-java-validation.json)
and the [source record](vu-clip-reference-source.json) pin the file, extracted body,
wrapper, reference DLL and values. The actual Java model is used by the Ghidra
instruction helper. Macro `VCLIPw` synchronizes flags, and
[VU0 CFC2](https://github.com/PCSX2/pcsx2/blob/b4d6e2aa7b9069162fa0e7cbc45ae95fc2566f39/pcsx2/VU0.cpp)
sign-extends control words into low64 GPR values. Only the two original bounds
control18 sites are added, preserving the earlier Q-read path. VNOP preserves
value state. These processor checks add no source credit and do not prove full
pipeline timing, other VU flags, microprogram interlocks or hardware behavior.

Surface setup stores slots 3,0,2,1 before leaving its 16-byte frame and tail-calling
the second object's initializer. That writes original callbacks `002c7f88` and
`002c8128` at 16/20; it does not execute or replace their outputs. Original surface
arrays are zero in the ELF and initialized by frame code. Full frame/ordering
consumption remains recovery work.

[DDS review](model-draw-prerequisites-transfer.json) checks eight complete spans,
decoded GP globals, matrix-tail targets and callback literals. The short word
setter is additionally constrained by neighboring cache/float globals and actual
placement calls. Installed callback bodies have matching noncall words; their
new callee targets remain candidates requiring independent checks. Names are
attributed to the pinned
[DDS symbol file](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/config/dds1/symbol_addrs.txt).
Descriptive Nocturne aliases do not claim original spelling or DDS execution.
The [HD review](model-draw-prerequisites-matches.json) rejects shared return-only
`sdfModelLinkOt` as an equivalent draw implementation.

All eight Ghidra interfaces pass after saving/reopening; current exports merge.
Another [5,664 affected cases](model-draw-prerequisites-regressions.json) pass on
the final DLL: pose 544, effect matrix 2,048 and quaternion rotation 3,072. The matrix
vectors were captured afresh to check the shared instruction helper on a nonclip
path. No checkpoints, backups or savestates were made.

Recovery is 2,192/9,059 (24.197%), 308,856 integrated bytes, 356,599 focused /819,283
aggregate comparisons across 162 focused reports. Next recover installed ordering
callbacks, node/material packet lists, both placement branches, anchors/children
and full spawn-once update. The [type7 graph](pcp-type7-lifecycle-frontier.json)
has 79 pending direct bodies /27,212 bytes, with dynamic callbacks expanding it.
