# Original lighting, clipping and UV helpers

Four complete bodies totaling 840 bytes are now compiled and compared with
original instructions. The [rolling validation](model-render-clip-validation.json)
passes 2,048 cases and reaches all 202 measured main instruction addresses.
It compares all declared ordinary RAM, 128 VU words, ACC/overflow/Q, clip
history, explicit CPU upper halves, Status and the FCSR condition.
There are 1,280 overlaps and 512 connected packed-to-in-place sequences.
Another [15,104 affected regression cases](model-render-clip-regressions.json)
pass on the rebuilt source. All four saved interfaces were reopened and the
current exports merged into the 9,059-function inventory.

| Entry | Recovered role | Bytes | DDS counterpart |
| --- | --- | ---: | --- |
| 002B6DE0 | Light and clip packed position/normal arrays | 208 | 002DE488 |
| 002B6EB0 | Light and clip live output records | 168 | 002DE558 |
| 002B6F58 | Packed arrays with UV transformation | 252 | 002DE600 |
| 002B7058 | Live output records with UV transformation | 212 | 002DE700 |

## Preserve history and partial lanes

All four load three parameter vectors from 0058F030/40/50 into VF19/20/21.
The setup changes only VF24/VF25/VF26.W: each becomes VF19.W times that
row's incoming X. The normal dot term uses these W lanes and VF19.Y.
Normal W becomes twice that dot term minus 1; its XYZ lanes remain normal
data. The dot term is clamped using raw VU MAX/MINI, and output colour is
VF20 + VF21 times that clamped term. Projection uses VF28..31 with an
implicit translation factor of VF0.W.

The first CLIP uses the projected point against its own W. Its control18
read is stored as the full low byte at output +0x51, retaining two bits of
earlier clip history. The second CLIP uses VF9, whose X receives normal W;
its incoming Y/Z remain live and affect the full history. This read's low
two bits go to output +0x50. The tests compare all 11,448 actual CFC2 reads
through their native stores, every intermediate CLIP state and final history,
with 2,560 independently computed clip states and 20,480 scalar oracles.

Original VCLIP mask15 still compares XYZ with threshold W. The harness adds
only its checked decoding and eight original-body/opcode-pinned control18
read sites. The underlying C and Java CLIP helpers previously passed 69,811
independent pinned-emulator reference cases each. Raw MIN/MAX helpers had
also been independently checked; those processor primitives add no source
function credit.

## UV transport and final prefetch

002B6F58 takes UV data in T0 and a 24-byte UV transform in T1 in addition to
A0..A3. The original caller passes a draw-entry transform at +0x68. The
in-place UV variant instead takes UV data in A2 and its transform in A3.
Three LD/QMTC2 pairs supply UV columns. LD changes only CPU low64, so
VF16/VF18.ZW retain V0.upper64 and VF17.ZW retains V1.upper64.

In the packed variant, the per-position PCPYLD replaces V0.upper64 with
the position Z/sign word before the UV LD; VF4.ZW therefore follows that
packed position. The in-place variant retains incoming V0.upper64. UV math
writes only VF5.XY, but the store writes all 16 bytes at output +0x30:
incoming VF5.ZW must survive. The host processor boundary tracks these
actual packed/LD transitions across connected calls; all 8,192 explicit CPU
upper words and full VU state agree with original execution.

002B6EB0 reads next-record normal and position after advancing the output
cursor but before current colour and clip-byte stores. It does so even when
the decremented count is zero. Final VF6/VF2 retain the backed sentinel
record, rather than the last computed normal/position. This prefetch is
preserved in all 512 root cases. The UV in-place variant has its own ordinary
per-iteration loads and does not gain that same final prefetch.

All loops retain the original unconditional first body and count decrement.
Inputs cover aligned, backed counts 1..4, raw float encodings, global/source/
UV/output aliases and connected calls. No zero/negative-count empty guard is
added. Exception behavior, pipeline/interlock timing, other VU flags, DMA,
physical rendering and the complete renderer remain outside this proof.

## Research and transfer

The [lead report](model-render-clip-leads.json) records primary source URLs,
revisions, hashes, exact words, callers and state dependencies.
[DDS3 Model Studio](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771/Source/DDS3ModelLibrary/Models)
corroborates 12-byte Vector3 position/normal arrays, 8-byte Vector2 texture
coordinates and material parameter storage. The
[DDS draw/model/material definitions](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c)
and the previously recovered original UV builder corroborate 24-byte
transforms at draw-entry +0x68/+0x80. Native instructions determine the
register-half transport, output layout and read/store ordering.

Unity material offset/tile/angle/texTm and HDLightParallelPacket supply
vocabulary and role leads. The inspected corpus does not establish named
exact counterparts for these four native loops; that search is bounded.
All four complete DDS spans agree after exactly two decoded global address
materialization words each: 0058F030 becomes 003F9860. Mutable data contents
are not assumed equal between games.

These four helpers are now recovered. Next continue packet/DMA consumers
and the full 002B9178 renderer, then both placement branches and outer update.
The complete executable remains unfinished. Work stays in place without
checkpoints, with one rolling capture for this cohort.
