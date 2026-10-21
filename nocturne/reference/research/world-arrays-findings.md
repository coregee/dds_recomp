# World indexed arrays and object control

Recovered `src/world_arrays.c/h` contains 23 complete native routines, covering
2,300 original body bytes. All 6,656 original-instruction/C comparisons pass,
reaching all 465 main instruction addresses. The cases execute 477,971 original
steps and 320 connected setup calls. The affected C compiles with warnings treated
as errors. All 23 interfaces were saved in the working Ghidra project, checked
after reopening, and exported successfully into the current inventory.

## Native structures and behavior

The current-world pointer at `0054E9C4` leads through basic+`18` to world data.
Offsets below are hexadecimal. World data stores the slot-array pointer at `14`,
free first/last/count halfwords at `1A/1C/1E`, and handle-list head/tail pointers
at `20/24`. Each 16-byte handle contains first/last/cursor/count halfwords at
`0/2/4/6` and next/previous pointers at `8/C`. Each eight-byte slot contains a
basic pointer at `0` and next/previous indices at `4/6`. The sentinel is `FFFF`;
indices are loaded signed, counts unsigned, and halfword updates wrap.

Twelve routines recover handle allocation/release, slot allocation/recycling,
single/all deletion, cursor traversal, counting, get/set and search. A zero
request to AddBasicArray returns one before accessing pointers. Other requests
retain the full-width signed count checks. GetBasicArrayHandle ignores the
subsequent AddBasicArray result, so selected negative requests return a linked
empty handle. Search stops at a null slot value even when a later slot matches.
SearchDelete resets the cursor; mode zero deletes the first match, while nonzero
mode continues until the search terminates. Native sign extension, unchecked
access and halfword overflow are retained.

The object-control initializer allocates and clears 172 bytes, writes mode three
at `8`, creates its array handle at `4`, records the owning basic at `10`, and
initializes 24 sentinel words from `A8` down to `4C`. The remaining bodies recover
flag on/off/check, basic-type to item-type mapping, control replacement, the Svs
control setter/getter, mover construction and owned path release. CheckFlag
combines a sign-extended native flag word with the full 64-bit argument. The type
mapper truncates and sign-extends through the original ADDIU before testing its
range. Mover construction allocates a 16-byte data block. MoverFreePath releases
the actual path/spline/handle ownership chain before clearing its pointer.

The fixtures include shuffled slot indices up to 32767, empty/head/interior/tail
positions, duplicate and null values, whole-list recycling, counter wrap, dirty
upper argument lanes and selected backed alias/malformed-index cases. Connected
cases use actual pool, memset, array, path and spline dependencies. Comparisons
check declared RAM writes, defined raw 64-bit results, processor status and
primitives, callee saves and interpreter trace. Arbitrary cyclic or malformed
chains are outside these bounded cases.

## Unity and DDS evidence

Twenty-two named Unity roles are reviewed in `world-arrays-matches.json`. The
separate PS2 Svs getter has a descriptive alias; HD exposes the read inside other
bodies. Managed layouts, garbage collection and null/bounds behavior differ.
HD flag setters also manipulate visibility and animation locks, which the PS2
bodies do not implement. These are semantic references, not interchangeable code.

Twenty-two complete DDS instruction spans resolve with 23 agreeing call links
and seven repeated global constraints. The transfer helper now accepts explicitly
verified GP-relative load relocations. For this batch, both ELF REGINFO GP values
are checked: Nocturne `00554170` plus signed `A854` addresses `0054E9C4`; DDS
`003C0CF0` plus signed `9CCC` addresses `003BA9BC`. An independently matched
SearchDelete body anchors the DeleteBasicArray callee, whose 256-byte DDS span
differs only at that GP-load immediate. Opcode/register bits and all other
instructions remain fixed. This does not relax arbitrary field offsets.

The neighboring DDS control initializer at `001117A8` is a related variant lead,
recorded separately in `world-arrays-dds-initializer-lead.json`. Its verified
116-byte prefix agrees apart from three independently mapped calls and the
allocation/clear sizes: DDS uses 180 bytes, compared with Nocturne's 172. DDS also
adds a sentinel store at `B0`; its purpose remains unproved. The shifted epilogue
and neighboring type mapper corroborate the role. It is excluded from the
22 complete-span identities.

## Current integration and next work

At this batch integration, recovery covered 1,233 of 8,975 recognized functions (13.738%),
with 640,122 aggregated comparisons and 185,200 summed original body bytes.
The last full run remains 413 functions / 462,684 cases; 820 additional routines
contribute 177,438 focused cases. This batch is a focused comparison, not a new
full-suite run, physical PS2 validation or matching-executable proof.

The subsequent [basic creation recovery](basic-creation-findings.md) closes
basic/object list creation and mover/camera initialization. The current camera
creation graph now includes the subsequent [camera view/create command
recovery](camera-view-findings.md): no direct bodies remain at compared boundaries;
14 selected lifecycle cleanup bodies /1,668 bytes remain. Continue camera/control
destruction and its model/event/material dependencies.
Other type callbacks, physical scheduling and complete gameplay remain open.

Evidence: `world-arrays-validation.json`, `world-arrays-abi.json`,
`world-arrays-matches.json`, `world-arrays-transfer.json`, and the current
`world-arrays/` capture. Changes were saved in place; rolling outputs were
overwritten without checkpoints or backup copies.

The subsequent [model ownership/cleanup recovery](model-cleanup-findings.md)
adds 15 complete prerequisites; the current selected lifecycle graph has 10
bodies /1,440 bytes remaining.
