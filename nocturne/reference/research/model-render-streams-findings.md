# Original packed render streams and normalization

Seven complete bodies, totaling 524 original bytes, are now compiled and
compared with the original instructions. The rolling
[validation](model-render-streams-validation.json) passes 3,584 cases and
reaches all 117 measured main instruction addresses. It compares all declared
ordinary RAM, 128 VU words, ACC/overflow/Q, Status and the FCSR condition.
There are 2,080 overlaps and 20,160 independent oracles, plus 384 actual copy
prefixes and 256 normalization suffixes. The rebuilt source also passes
[11,520 affected regression cases](model-render-streams-regressions.json).
The saved mixed integer/float interfaces were reopened and seven current
exports merged into the original 9,059-function inventory.

| Entry | Recovered role | Bytes | DDS counterpart |
| --- | --- | ---: | --- |
| 002B6BC0 | Weighted points with original A0-controlled odd loop | 88 | 002DE268 |
| 002B6C18 | Accumulate weighted points into live output | 96 | 002DE2C0 |
| 002B6C78 | Copy packed vectors | 44 | 002DE320 |
| 002B6CA8 | Copy packed position/normal pairs | 68 | 002DE350 |
| 002B6CF0 | Blend packed position/normal deltas | 108 | 002DE398 |
| 002B6D60 | Blend packed position deltas | 68 | 002DE408 |
| 002B6DA8 | Normalize output normals | 52 | 002DE450 |

## Preserve the unusual loop

002B6BC0 loads four matrix rows once, transforms an incoming 16-byte position
with an implicit translation term, then multiplies all four output lanes by
the input W weight. A3 advances by 16 and A1 decrements, but the branch tests
**A0 after adding 96**. Its delay-slot store uses **advanced A3 minus 96**,
which is 80 bytes before the position just read. It does not store through A0.
The adjacent accumulation routine instead branches on decremented A1 and
stores through the output cursor. These remain two distinct implementations.

Choosing initial A0 = -96*k gives an actual finite original path: the kth
addition reaches zero. The 512 constructed cases use k=1..8 and execute
2,304 measured odd-loop iterations, with independently varied A1 values
including zero. Source and matrix buffers have fully backed prefixes; matrix
overlaps check that the four rows are loaded before any loop store. This
validates the preserved body without claiming that retail callers supply
negative A0 or that the path is safe for arbitrary runtime inputs.

The earlier bounded asset census found no Weights-without-Normal header
among 38,140 community-corroborated kind4/5/7/8 headers. Other carriers and
runtime/generated commands remain unexamined for that constraint. Compiling
and testing this body does not establish its retail reachability or justify
changing its branch, count or destination.

## Packed words, ordering and live register state

Packed vector inputs have 12-byte stride. The first eight bytes carry X/Y;
the LW of Z supplies a signed 64-bit word. Consequently output W is the raw
sign-extension word of Z, including FFFFFFFF for negative zero, rather than
a homogeneous 1 or an old destination W. Weighted positions have 16-byte
stride, and output records have 96-byte stride at offsets 0/+0x10.

The paired copy writes the position before reading the normal. The paired
blend reads both sources and both old output vectors before its stores. The
single blend reads the old output before its packed source. Selected aliases
exercise these differences. Blend operations affect XYZ; the incoming packed
Z sign word remains in W. MFC1 weight transport retains the incoming upper
64 bits of T0 or A3; those fixture inputs and all resulting VF6 lanes compare.

The normalizer first squares XYZ into VF3, then forms ACC.x = x²+y² and
VF4.x = ACC.x + incoming VF1.x*z². Original opcode 4A6403BE selects
VRSQRT Q,VF0.w,VF4.x. It multiplies only XYZ by Q and retains normal W.
The renderer initializes VF1 to (1,1,1,0), but standalone raw-state cases vary
it rather than replacing that dependency with a fixed Euclidean formula.
Power-of-two axis normals provide independent exact oracles.

All count-controlled loops retain their unconditional first body and original
decrement/branch; no empty-input guard is added. Tests cover backed counts
1..8, raw float encodings and selected sequences. Full zero/negative-count
execution, exception behavior, pipeline timing, other VU flags, DMA and
physical hardware behavior are outside this comparison scope.

## Community, Unity and shared engine evidence

The [owned lead report](model-render-stream-leads.json) pins source revisions,
hashes, original words, callers and register dependencies. Inspected
[DDS3 Model Studio mesh readers](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771/Source/DDS3ModelLibrary/Models/MeshTypes)
corroborate 12-byte Vector3 position/normal arrays for ordinary and blend
streams, and 16-byte Vector4 weighted positions with 12-byte normals for
weighted node batches. They inform the separate fixture layouts; native
instructions determine the sign word, output stride and alias ordering.
The [DDS source and symbols](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c)
supply context, while all seven complete original spans independently match
DDS byte for byte. Pinned PCSX2 sources corroborate VU selector/value rules.

The current Unity symbol/corpus search supplies morph and motion leads, but
its shared return-only model exports and managed motion-state blends do not
establish exact counterparts for these native streams. This negative search
is bounded to the inspected corpus and names. No additional HD identity is
credited from it.

The harness now recognizes an original opcode-pinned transport instruction
in a branch delay slot, where Ghidra reports the branch address. The initial
failed capture was replaced by the complete passing rolling capture. No
return values or game routines were substituted to make the loops terminate.

Next recover the four remaining lighting/clip helpers, then the complete
renderer and both placement branches. The full executable remains unfinished.
Work stays in place with one rolling capture and no checkpoints.
