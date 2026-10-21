# Basic allocation, scene ownership and camera/mover creation

Recovered `src/basic_creation.c/h` adds 13 complete native bodies, covering
1,528 summed original body bytes. All 3,328 original-instruction/C comparisons
pass and reach all 306 main instruction addresses. They execute 1,002,209 original
steps, 681 actual setup calls and 2,508 vector instructions. The comparison checks
455,936 vector-register/ACC-overflow/Q values, alongside declared RAM writes,
defined raw 64-bit results, processor status/primitives, callee saves and VM trace.
The affected C compiles with warnings treated as errors. All 13 working Ghidra
interfaces were saved, checked after reopening and exported successfully.

## Allocation and ownership

Offsets are hexadecimal. A basic allocation requests 68 bytes. It initializes
type at `0F` via the word at `0C`, color `34=80808080`, callback record `10`,
and fields through `30`; trailing storage remains untouched. The original
18-entry callback table at `002FA5C8` selects world type0, mover type3 and camera
type4 constructors. Types12..15 and17 have null records; type16 has a real record
whose six words are zero. An initializer result other than exactly one invokes
the actual destructor and releases the basic. Tests exercise this failure through
the original world constructor with a zero-returning pool state, not a returning
callback substitute or an altered dispatch table.

DeleteBasic runs the selected destructor, reloads previous/next pointers at
`24/20`, repairs their links and releases the basic. Host callback adapters execute
the recovered world/mover/camera constructors and world/mover destructors; they
abort for other targets. The generic source retains callback dispatch rather than
replacing unknown types with successful returns. Other callback bodies remain work.

Scene data+`8` points to 18 twelve-byte count/head/tail records. AddSceneBasicData
accepts types2..17, allocates through AddBasic, records the owning scene at basic
`30`, appends to that type's list and increments its 32-bit count. DeleteSceneBasicData
uses the basic's type and owning scene, adjusts endpoints, runs DeleteBasic and
decrements the count after release. Endpoint comparisons retain full-width native
pointer equality, so dirty upper argument lanes can differ from a low-word-only
comparison. Backed lists cover empty/head/interior/tail cases and count wrap.

The world constructor initializes a 40-byte block: scene head/tail `0/4`, active
scene/control scene `8/C`, memory handle `10`, slots `14`, free indices/count
`1A/1C/1E`, and array-handle head/tail `20/24`. World destruction deletes actual
linked scene basics, releases actual array handles, frees the memory handle and
then releases world data. Tests connect real memory-handle allocation, splitting
and release. DeleteScene also clears matching active/control-scene references.
These native routines leave the former owner's data pointer unchanged.

## Camera and mover connection

Camera construction attempts pose initialization, allocates 144 bytes of camera
data, creates the 172-byte object-control block at data+`80`, enables flags `62`
and clears data+`88`. It returns one even when pose allocation did not succeed;
unchecked subsequent allocation accesses are preserved. Existing/null pose and
absent-world or zero nested-handle branches are compared.

AddMoverBasic creates a scene-listed type3 basic, obtains the wrapping 16-bit
serial ID, writes the owning object to mover data+`0` and assigns its name pointer
from `002FA670 + index*16`. Global `0054E9C8` becomes signed `(index+1)%10`, with
native 32-bit wrap before division. Tests include negative and overflowed indices.
CreateMover keeps an existing slot1 mover or creates and attaches a new one. Its
native return retains the existing/replaced pointer; the Unity method is void.
Mover destruction releases the actual owned path/spline chain, clears the owning
object's slot1 and releases mover data. Connected cases execute these dependencies.

AddCameraObjectBasicDef creates type4, records the supplied serial and ensures a
mover. AddPathBasic creates type17 and stores name, resource data and serial in
the native order. The named HD path counterpart uses type16. Actual constructor
and scene-list delete sequences are compared; camera destruction remains unfinished.

## Unity and DDS evidence

Eleven named Unity roles are reviewed in `basic-creation-matches.json`; the two
world lifecycle bodies have descriptive PS2 aliases. Several HD callees are
inlined. Managed guards, layout, garbage collection and ownership differ; camera
constructor constants in the HD export are not used as native value proof.

All 13 complete DDS instruction spans resolve. The generic matcher supplies eleven;
two more have explicit complete-span checks anchored by incoming calls from already
matched scene allocation and CreateMover bodies. There are 20 generic and six
additional agreeing call links. Indexed callback-table address construction,
paired GP-relative loads/stores and code addresses are the only changed words in
those spans; all remaining words, operation order and branch geometry agree.
Selected original callback records and all 160 bytes of `MOVER00`..`MOVER09` names
are independently checked. Other type callback implementations are not claimed equal.

The serial dependency at Nocturne `0010E248` now resolves to DDS `0010FA80` with
its complete 20-byte span. Both ELF GP bases are verified; serial global
`0054E9C0` relocates to `003BA9B8`, and mover index `0054E9C8` to `003BA9C0`.
See `basic-creation-transfer.json` for the exact word pairs and hashes. This is
static DDS evidence, not DDS execution.

## Current progress

At this batch integration, recovery covered 1,246 / 8,975 recognized functions (13.883%), with 643,450
aggregated comparisons and 186,728 summed original body bytes. The last full run
remains 413 functions / 462,684 cases; 833 additional routines supply 180,766
focused cases. No new full-suite run, physical PS2 validation or matching executable
is claimed. The separate vector-value prerequisite still passes 50,000 operand
cases / 300,000 software-reference values with the current host build.

The subsequent [camera view and CAM_CREATE recovery](camera-view-findings.md)
closes those five direct bodies and also recovers the look-at camera constructor.
The current graph has no remaining direct bodies at compared boundaries; 10
selected lifecycle cleanup bodies /1,440 bytes remain. Continue camera/control
destruction and its model/event/material dependencies.
Other object types, scheduling and complete gameplay remain open.

Evidence: `basic-creation-validation.json`, `basic-creation-abi.json`,
`basic-creation-matches.json`, `basic-creation-transfer.json`, the current
`basic-creation/` capture and `camera-creation-frontier.json`. The working project
was saved in place; captures and logs were overwritten without backup copies.

The subsequent [model ownership/cleanup recovery](model-cleanup-findings.md)
adds 15 complete prerequisites; the current selected lifecycle graph has 10
bodies /1,440 bytes remaining.
