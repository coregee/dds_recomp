# Original triangle emission and render passes

Seven complete original bodies are recovered: 2,224 recognized bytes and
2,236 bytes across their full contiguous instruction spans.

| PS2 entry | Role | Recognized bytes |
| --- | --- | ---: |
| 002B85D8 | Emit textured triangles | 580 |
| 002B8820 | Emit triangles with secondary render state | 648 |
| 002B8AA8 | Emit colour-only triangles | 348 |
| 002B8C08 | Select the base triangle emitter | 40 |
| 002B8C30 | Update UV/colour data and emit the material pass | 228 |
| 002B8D18 | Update auxiliary attributes and emit the auxiliary pass | 288 |
| 002B8E38 | Dispatch base, material and auxiliary passes | 92 |

The 3,584 fresh original-instruction cases reach all 508 measured addresses.
Full declared RAM, all vector words, ACC/overflow/Q, clip history,
Status/FCSR in the retained value model, and the explicit upper halves of
V0/V1/A3/T3/T4/A1 compare with compiled C. This checks 491,008 vector-state
words and 43,008 CPU upper words. There are 245,544 independent packet-format
and vertex-value checks, 1,344 active overlaps and 448 connected emission
sequences. Another 21,760 affected retained cases pass on the current DLL.
Saved raw64 interfaces, including the six-register emitter, pass a separate
reopen check; all seven exports merge into the existing 9,059-entry inventory.

## Batching and packet bytes

The emitters read the signed triangle count at context +50, the cursor at
+8C, and pointer triples at the original mutable global `00581030`. Textured
emitters batch at most 16 triangles; colour-only emission batches at most 24.
The source retains the original count-zero path and adds no guards for invalid
negative counts. Each batch zero-pads the cursor to 4 modulo 16, writes its
VIF commands and GIF payload, then writes `0x14000004` and advances the cursor.

The raw commands `0x6501C000` and `0x6CxxC001` decode as UNPACK V2-16 with
NUM 1 and UNPACK V4-32 with a variable NUM. The last word is MSCAL with
immediate 4. Textured vertices carry position, UV and colour quads; colour-only
vertices carry position and colour. Each source quad is loaded immediately
before its store. Overlapping input/output buffers therefore retain the
original ordered effects rather than copying a whole triangle in advance.

The first textured batch includes three A+D state writes for TEX1_1, TEX0_1
and CLAMP_1. The secondary emitter's first batch includes five writes for
TEX1_2, TEX0_2, CLAMP_2, TEST_2 and ALPHA_2. Later batches omit those state
writes. Packed GIF register lists are `0x412` for STQ/RGBA/XYZF2 and `0x41`
for RGBA/XYZF2. The secondary emitter retains all six raw64 register arguments,
including T0/T1, and applies its disable mask to the live primitive flags.

## Real pass dependencies and live reloads

The material pass calls the actual recovered UV transform and linked UV
interpolation bodies. It then reads the material's mode and colours. Modes
0..2 conditionally call the real lighting constructor and record-colour
rebuild; mode 3 calls the real packed-colour fill; higher unsigned modes skip
that work. State fields are loaded after these dependencies, including the
zero-extended material +20 word and the three following 64-bit state values.

Thirty-two targeted cases make the UV store overlap material +20/+24, changing
the mode before its later read. Another 32 overlap context +40/+44. In those
cases mode 4 skips colour work, and the parent's reloaded flags omit the
auxiliary pass, preserving the original finite path after the count field has
also changed. Both compare without supplied game outputs or added guards.
The initial capture also caught an insufficient fixture allocation for a
multi-pass overlap; enlarging its backed object span preserved the full input
and output counts. The rolling capture was replaced, without a backup copy.

The auxiliary pass reads lighting context +D0 and either the cached basis at
`0058F070` or the alternate basis selected by context +48 bit 800. Its packed
colour products, dot calculation and alpha contribution are retained. VF5.ZW
come from the incoming upper half of A3's constant QMTC2 transport; the UV
store writes the entire vector. The original reads the next normal even on
the final iteration. Real linked UV/colour interpolation follows, then the
secondary emitter receives the original tail-call arguments and fog mask.

## Community and SMT transfer

[The independent lead report](model-render-emission-leads.json) pins thirteen
complete Nocturne/DDS spans: seven roots and six real dependencies. Every
changed root word is a decoded GP reference, global-address materialization
or checked direct/tail call. The patterns enter the shared SMT ledger with
the byte-span and game-specific qualifications retained.

The report attributes [Megami-Decomps DDS research](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c),
[DDS3 Model Studio layouts](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771),
and primary PCSX2 VIF/GIF definitions. One parser disagreement is retained:
Model Studio calls bit 14 `Sign` and uses signed Int16 reads when it is set;
PCSX2 identifies it as USN and selects unsigned unpacking. The recovered source
emits the original raw bytes and adopts no signed hardware decoder from that
property. Unity supplies lighting/material vocabulary, not this PS2 packet
algorithm.

Packet bytes do not establish VIF/GIF execution or a VU1 program upload.
MSCAL 4 is distinct from the previously recovered VU0 VCALLMS 0/9 program.
Upstream clipping builders `002B7498`, `002B7A80` and `002B8068`, dispatcher
`002B8E98`, DMA/VU consumer `002B9048`, and the full renderer remain pending.
Malformed loops, full processor flags, hardware timing, cache aliasing and
rendered appearance are unproved. No checkpoints or savestates were created.
