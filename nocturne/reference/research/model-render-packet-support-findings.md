# Renderer packet support

Eight complete original bodies, totaling 1,072 recognized bytes, are recovered:

| PS2 entry | Role | Bytes |
| --- | --- | ---: |
| 002B7130 | Relight transformed records and update the axis clip byte | 140 |
| 002B71C0 | Transform record UV coordinates | 96 |
| 002B7220 | Interpolate UV coordinates through generated-edge links | 76 |
| 002B7270 | Interpolate UV and colour through generated-edge links | 100 |
| 002B72D8 | Rebuild record colours from stored light values | 152 |
| 002B7370 | Fill record colours from packed colour products | 168 |
| 002B7418 | Construct an interpolated edge record using VU Q | 128 |
| 002B8F70 | Pad and finalize the DMA packet through the real cursor setter | 212 |

The 4,096 fresh original-instruction cases reach all 238 measured addresses.
Full declared RAM, all 128 vector words, ACC/overflow/Q, clip history,
Status/FCSR and the explicit upper halves of V0/V1/A3 compare with compiled C.
There are 561,152 vector-state words, 24,576 CPU upper words, 5,344 clip-state
observations and 12,560 independent scalar checks. The cases include 1,116
active overlaps, 32 cursor/header aliases and 128 connected edge-to-colour
interpolation sequences. Another 17,664 affected retained cases pass on the
current host. Saved interfaces pass a separate reopen check, and the eight
current exports merge into the 9,059-entry inventory.

## Original behavior retained

Generated 96-byte records use +40 for the next link, +44/+48 for the source
records and +4C for the raw interpolation ratio. `002B7418` stores source
pointers before its source loads, so destination/source overlap matters. Its
first source's axis-clip bit selects boundary 1 or incoming VF1.W minus 1.
VDIV reads the W components; CFC2 reads architectural control 22, Q. The
stored ratio feeds position interpolation and later linked UV/colour updates.
The original loads all relevant source vectors before the generated record's
stores, and reloads its next link after those stores.

`002B71C0` loads and transforms one extra UV pair even on the final iteration.
The final VF3 therefore contains the sentinel transform, while SD writes the
previous pair's XY. LD preserves the CPU register's upper half, and QMFC2
changes the upper half used by subsequent loads. `002B72D8` likewise prefetches
the next normal and computes its light value before storing the current
colour. Both source loops retain their original unconditional count behavior.
`002B7370` accepts count zero for its record-fill loop but still performs the
linked-source colour copies. The source adds no convenience guards for invalid
counts or cyclic lists.

The finalizer handles null allocation and empty payload branches, pads words
to 16 bytes, computes the payload QW count, then pads quads to 64 bytes. The
count excludes the extra 64-byte padding. It calls the real `002ACB78`
align-up16 cursor setter, then reloads the packet pointer and writes +8 before
+0. The 32 GP/context aliases make that reload observable: changing the cursor
also changes the header-pointer field. The emitted header words are
`0x1100000000000000` and `0x20000000 | (QW_count & 0xFFFF)`.

The original capture now admits one pinned VDIV W/W instruction, two pinned
MADDq sites, and the two reviewed CFC2 reads. It reuses the separately checked
division, MAC, clip and raw MIN/MAX value models. Full VU flags, pipeline
scheduling, DMA completion and hardware timing are separate obligations.

## Community context and transfer

[The independent lead report](model-render-packet-support-leads.json) pins
[Megami-Decomps DDS research](https://github.com/Megami-Decomps/dds-decomp/tree/bec33411543cdc487bad9debdf758f0090a2242c),
[DDS3 Model Studio layouts](https://github.com/tge-was-taken/DDS3-Model-Studio/tree/92f350749ab24dcfd7c35b8fac105a5c1883d771),
and primary PCSX2 register, transport and division definitions. It checks all
eight complete DDS counterparts plus the real 20-byte cursor setter. Six
roots are byte-identical; the relight root differs only in its two global
address words, the finalizer in two checked calls, and the setter in its GP
store. These constrained patterns enter the shared SMT ledger.

The DDS community's generated-node names and packed mesh/material layouts
provide roles and fixture context. They do not establish that scene or patch
link structures share these generated-record offsets. Unity's lighting and
UV types supply vocabulary; its return-only model-ordering export is rejected
as an algorithm reference for this path.

The full renderer now has two pending direct helpers: packet construction
`002B8E98`, whose emission and clipping dependencies remain to be recovered,
and DMA/VU consumption `002B9048`. Complete `002B9178`, placement `002B1DB8`
and the outer context/update path remain pending. Constructed high-address
backing does not prove physical cache aliasing or rendered DMA behavior.
No checkpoints, backup copies or savestates were created.
