# Memory bundles, model defaults and colour callbacks

Thirty-one complete native bodies /1,328 bytes are integrated. The current
[validation](model-memory-parts-validation.json) passes 496 comparisons with
all 266 selected main instruction addresses reached. The saved Ghidra
interfaces were independently reopened and checked; all 31 corrected exports
were merged into the working inventory. [Recovered source](../src/model_memory_parts.c)
and [interfaces](model-memory-parts-interfaces.json) retain descriptive native
aliases and the original argument widths.

## Retail loading and construction

The loader at `001DE2E0` initializes the actual PAC parser, selects borrowed
payloads when flags bit 1 is set, decodes, registers PIB/model/motion records
and releases parser nodes. The part constructor at `00175D78` uses group 7,
the word serial at `0054F1E4`, flags `101`, a caller wrapper's word size and
payload at `+10`, then creates and initializes an actual model context.

Inputs include unchanged `model/event/e659/hikari.PB` (704 bytes) and
`model/event/e635/field_a.PB` (960 bytes), read directly from DDS3. Every record
kind was enumerated; both contain only PIB, model, motion and the terminal
record. No texture-free assumption was taken from the filtered asset census.
Their bytes and hashes remain in the current fixtures, without standalone asset
copies. The synthetic sixteen-byte size wrapper is distinguished from those
original PB bytes.

There are 34 retail bundle cases: sixteen direct memory loads, sixteen part
constructions and two constructions through the original part table followed
by actual colour dispatch. Both owned and borrowed payload paths execute,
including pointer relocation, model/motion construction, default motion and
selected context cleanup. The last standalone constructor starts with serial
`65535` and leaves the original word counter at `65536`.

The parser's original stack address persists in freed record nodes. Host
address adaptation therefore maps its local buffer to that guest stack address,
including the enclosing part-constructor frame. It does not substitute a
captured pointer or game-function result. Every declared RAM span remains
compared. Older synthetic `70000000` local mappings retain their previous
behaviour for other callers.

## Defaults and indirect colour routes

Default initialization uses the original vectors at `0031DF60`/`70`/`80`, forces
position W to one, preserves rotation and scale lanes, executes the recovered
quaternion-to-matrix routine and writes colour `80808080`. A present motion
controller receives the original default-motion call and speed one; context
flag bit zero is cleared.

Colour dispatch uses unchanged major, part, track and seven-slot PCP tables.
Synthetic backed caller shapes exercise absent lists, mixed billboard/effect
nodes, skipped node kinds and nested wrappers. New part-table bindings execute
the actual retail model and material-billboard constructors. The material
billboard keeps its plain allocation's dirty prefix, creates the actual
animated billboard and material, and builds the packed VF0 identity matrix.

The root colour stores the low word. Its attached colour is
`(raw64 & FFFFFFFFFF000000) | 00808080`: the sign-extended native mask preserves
the caller's high word. Truncating before that mask was caught by callback
comparison and corrected. Leaf colour stores still write only their original
words. The bounded PAC trace is reset between independent cases; no native
callback or return is replaced to make comparisons pass.

The current capture checks 442 actual PAC callbacks, 129 colour callbacks,
four part-constructor callbacks, 34 billboard factories, 72 motion-creation
callbacks, 232 original caller preludes and 392 independently supplied command
frame operands. All selected main addresses, defined returns, declared RAM,
Status and defined COP1/VU/ACC/Q values agree.

## Reference research and SMT transfer

Six inspected Unity bodies provide model-loading, transform, colour and part
dispatch roles. [The reference review](model-memory-parts-matches.json) keeps
their local corpus hashes and separates Unity guards, managed layouts and
object updates from native behaviour.

Pinned DDS research at revision `bec33411543cdc487bad9debdf758f0090a2242c`
provides [model-manager transforms and broadcast code](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/model/mdlManager.c),
[PAC state](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_pac_state.h),
[file-request ownership](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/file_pac.h)
and [billboard work](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/effect/billManager.c).
Independent [DDS3 Model Studio metadata](https://github.com/tge-was-taken/DDS3-Model-Studio/blob/92f350749ab24dcfd7c35b8fac105a5c1883d771/Source/DDS3ModelLibrary/Models/ModelPackInfo.cs)
informs record layout and retail selection. Its signed model-count
interpretation remains distinct from native full-word version testing and
unsigned effect/motion readers, as recorded in the [community audit](community-model-studio-audit.json).

[Thirty complete DDS counterparts](model-memory-parts-transfer.json) resolve
through nineteen call constraints and twenty-two checked colour-table slots.
Tiny leaves require original incoming slots as well as their complete bytes.
Four wrappers use interleaved LUI/ADDU/LW address construction that the generic
matcher misses; explicit comparisons preserve every word except their two
checked data relocations. Default initialization similarly preserves its
complete span, checked callees and byte-identical default vectors.

The part-bundle constructor is deliberately excluded from exact transfer:
Nocturne uses LW/SW for its word serial; DDS uses LHU/SH for a halfword serial.
The remaining PCP dispatch constructor supplies a checked 176-byte static
table-context comparison but receives no compiled recovery credit.

## Current boundary

Another 6,182 cases across eight affected suites pass on the same DLL using
retained original captures. [The regression report](model-memory-parts-regressions.json)
includes every report whose source hash changed and the libc local-mapping
suite. This is focused validation, with no new full capture or physical-runtime
claim.

Recovery is now 2,019/8,992 functions (22.453%): 330,019 focused /792,703 aggregate
cases across 151 reports. The expanded bootstrap graph includes track colour,
PCP constructors and colour callbacks: 34 pending bodies /9,628 bytes, no missing
exports. Earlier seventeen-body estimates omitted these indirect roots. Graphs
overlap other subsystems and are not summed.

Continue the remaining seven actual PCP constructors and their wrapper, then
larger retail bundles with textures and effects and native external-worker
arrivals. Complete corpus/lifecycle execution, physical IO/DMA/rendering, a
matching executable and the full program remain outstanding. Work stays in
the current source/project and rolling reports without checkpoints.
