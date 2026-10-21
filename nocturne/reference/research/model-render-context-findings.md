# Original render buffer and lighting setup

Five complete bodies are now compiled and compared against original Nocturne
instructions: 636 recognized bytes, or 644 bytes across their complete contiguous
spans. The rolling [validation](model-render-context-validation.json) contains
1,536 passing cases and reaches all 149 measured main instruction addresses.
All declared RAM, 128 VU words, ACC/overflow/Q, Status and the FCSR condition
agree. There are 825 overlaps, 4,288 independent scalar/vector oracles, 32
original retail headers and 64 calls through the real context pointer setter.
Another [9,984 affected comparisons](model-render-context-regressions.json) pass
on the rebuilt host. The five saved interfaces were independently reopened and
their current exports merged into the 9,059-function inventory.

| Entry | Recovered role | Recognized bytes | DDS counterpart |
| --- | --- | ---: | --- |
| 002B67E0 | Configure work/scratch buffer split | 196 | 002DDE88 |
| 002B68B0 | Read mesh header into work context | 88 | 002DDF58 |
| 002B6908 | Compose and cache normal basis | 92 | 002DDFB0 |
| 002B6968 | Build colour/light parameters | 200 | 002DE010 |
| 002B6A30 | Add material biases and forward lighting inputs | 60 | 002DE0D8 |

## Counts and flags follow the original loads

The renderer passes mesh command +0x10 to 002B68B0. Its first two unsigned
halfwords become context +0x40/+0x42; the community parsers call them triangle
and vertex counts. The second load overwrites A1 before the tail jump to
002B67E0, so **the vertex count at source +2 is forwarded**. The first count
does not control that buffer split. The source preserves scalar load/store
order, including output writes that overlap the next input halfword.

Context +0x48 contains the raw high halfword of the mesh flags. Context +0x44
contains masked low flags, and GP global 005520D4 receives its bits 0x78.
The renderer's S7 bits 0x800/0x80 therefore correspond to full mesh bits
08000000/00800000 (Weights/Normal), not bits in the masked low flags.

002B67E0 compares a signed 64-bit count with 128, then tests exact 64-bit
equality with 128. Its offset arithmetic uses the low word times 96. The
three branches preserve the original scratch base 70001000, GP work pointer
005520D0, capacities 128/2000, store order and context +0x7C list anchor.
Dirty upper count words and negative counts remain distinct inputs.

## Normal and colour preparation

The light-context pointer at 005520D8 is set by the already recovered
002B9B38. The original, still pending light builder at 002BA250 corroborates
its normal rows +0x10/+0x20/+0x30, first light colour +0x40 and ambient +0x80.
002B6908 composes incoming basis rows +0x40/+0x50/+0x60 into VF24/VF25/VF26.
It then caches the raw incoming rows at 0058F070/80/90, rather than those
transformed results. Partial XYZ operations retain the other VU lanes.

002B6968 unpacks RGBA bytes, converts them to floats, divides two colour
vectors by 128, blends light and ambient using F12, applies the base colour,
uses the original raw VU MINI comparison with 255, and subtracts the blended
result. F13 is clamped to at least 1 by the original COP1 comparison; F14
times that value is stored separately. The wrapper reads material +0x1C,
+0x28/+0x2C and colour words +8/+4 in their original order before forwarding.
The saved interfaces retain five integer plus three float arguments for the
core, and three integer plus two float arguments for its wrapper.

The original QMTC2 instructions transport all 128 bits. Incoming T3/T4/A1
upper halves are explicit fixture inputs and remain observable in VF5/6/7.
The C and Java MINI primitives had already passed 65,878 independently checked
reference pairs each; that primitive evidence adds no function credit.

## Community, Unity and transfer evidence

The [context leads](model-render-context-leads.json) pin the inspected
[DDS3 Model Studio](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771/Source/DDS3ModelLibrary/Models)
and [DDS decompilation](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c)
sources, original instruction words, file offsets, record hashes and Unity
light-packet leads. Unity's HDLightParallelPacket supplies useful normal,
colour and matrix vocabulary; its managed construction is not accepted as
an exact implementation of these PS2 routines.

All five complete DDS spans were checked. The 200-byte lighting core is
identical. Other differences are explicitly decoded GP locations, normal
cache address materialization and corresponding tail jumps. The DDS work
globals are 003BDA20/24/28 and its basis cache starts at 003F98A0. Mutable
contents are not assumed equal across games.

The bounded original PB/AB survey contains 627 MD00 records and 38,140
community-corroborated kind 4/5/7/8 headers. Their retained original record
hashes are rechecked by this verifier. None has Weights enabled with Normal
disabled. Kind 7/8 paths bypass the unusual CPU helper; kind 4/5 headers
matter to that branch. Two actual weighted kind 5 examples occur in
model/event/e614/reiko.PB. This does not prove global dead code: embedded
field LB data, other carriers and generated/runtime commands are outside
this survey. The original 002B6BC0 branch and store remain pending unchanged.

Next recover the remaining clip/light/transfer helpers and both complete
placement branches. These tests establish backed instruction value behavior;
they do not establish DMA execution, pipeline timing, physical PS2 behavior,
the complete renderer or a matching executable. Work remains in place with
one rolling capture and no checkpoints.
