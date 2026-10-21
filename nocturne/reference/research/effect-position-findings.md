# Connected original effect position

Verified against original `SLUS_209.11` instructions on 2026-10-14. Ten complete
new C bodies cover 268 original bytes; two previously recovered dispatchers are
also compared. The [proof](effect-position-validation.json) passes 1,156 cases,
all 80 measured main instruction addresses, full declared RAM, ordered raw
callback operands, Status/FCSR condition and all VU/ACC-overflow/Q state.

| PS2 entry | Recovered role | Original bytes |
| --- | --- | ---: |
| `0015ac80` | Major-effect position dispatch | 56 |
| `0015d020` | Billboard raw vector store | 16 |
| `0015d7b0` | Material billboard child-position tail call | 24 |
| `00164f00` | Polygon position store | 16 |
| `00165580` | Alternate polygon position store | 16 |
| `00169e80` | Special polygon position store | 16 |
| `001a8ce0` | Magatuhi track-position dispatch | 64 |
| `001a7708` | Type2 track origin store | 20 |
| `001a7f58` | Type3 track origin store | 20 |
| `001a88b0` | Type4 track origin store | 20 |

The unchanged tables route through five major rows, seven part rows, five track
rows and 44 PCP rows. Major uses LW kind, stride48, position column20 and an
unconditional callback with child at8. Part uses LHU kind, stride40, column16
and a nullable callback with child at4. Track uses LW kind, stride24, column12
and nullable child4. PCP uses LW kind, stride40, column16 and nullable child8.
Each child LW sign-extends to64 bits; the source argument retains its incoming
64 bits. No target, game result or callback output is substituted.

Actual nested callbacks total 190 major/track, 332 part and 254 PCP calls, with
2,045 observed original entries. The 867 source-alias cases include self-copy,
child-source and wrapper-header sources. Raw stores load all four words before
writing any destination word. Material billboard loads child at80 then leaves
its16-byte frame before tail-calling the raw setter. Track leaves store at40.
Model position retains its real VF10 load and existing setter's forced VF0.W.
PCP paths execute their canonical shared-pointer and VU origin-delta bodies.

[Transfer review](effect-position-transfer.json) checks all ten complete DDS
counterpart spans and 61 position slots. All nonrelocated instruction words
match. Table-address words are independently decoded, and the material
billboard's tail target is constrained by the counterpart part table. Community
DDS names are attributed to revision
`bec33411543cdc487bad9debdf758f0090a2242c` of
[Megami-Decomps/dds-decomp](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/config/dds1/symbol_addrs.txt).
This is static transfer evidence; DDS execution is not claimed.

[Unity lead review](effect-position-matches.json) inspects named billboard,
major-effect, part and PCP setters. Their vector/dispatch roles agree, but HD
object wrappers, runtime guards and field offsets are not imported into PS2
source or claimed as binary identities. Descriptive Nocturne names are not
claims about original source spelling.

All 12 ABI records pass after saving and reopening the working Ghidra project.
The ten new current exports merge into its 9,059-entry inventory. Another
[15,896 affected retained cases](effect-position-regressions.json) pass on the
current DLL: spawn-once 800, wrapper controls 2,112, controls 2,744 and fields 10,240.
Original vectors are retained in place; no checkpoints or backup copies are made.

Current source recovery is 2,184/9,059 (24.109%), 308,348 integrated body bytes,
353,271 focused /815,955 aggregate comparisons. This closes the earlier
model-only host position boundary across the inspected tables. Backed aligned
synthetic position sources do not establish retail lifecycle scheduling or
physical hardware behavior. Spawn-once update still depends on model processing,
placement/draw packets, linked effects, children and the original update table.
Its refreshed direct graph has 85 pending bodies /27,648 bytes. Recover these
paths without skipping rendering or replacing missing model functions.
