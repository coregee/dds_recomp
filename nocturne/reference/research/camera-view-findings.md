# Camera view construction and CAM_CREATE

Recovered `src/camera_view.c/h` adds six complete native functions, covering
960 summed original body bytes. All 3,168 original-instruction/C comparisons
pass: 512 per new function and 96 connected programs through the existing script
interpreter. Every one of the 215 main instruction addresses executes. The affected
C compiles with warnings treated as errors. All six Ghidra interfaces were saved
in the working project, checked after reopening, and exported successfully.

| PS2 entry | Recovered function | Complete DDS counterpart |
|---|---|---|
| 002B5E78 | ps2RigidInverseMatrix | 002DD520 |
| 002B6748 | sdfVu0LookAtMatrix | 002DDDF0 |
| 00112500 | dds3CameraObjectBasicMakeCamera | 00112AE8 |
| 00112620 | dds3AddCameraObjectBasicTypeFree | 00112C08 |
| 00112718 | dds3AddCameraObjectBasicTypeLookAt | 00112D00 |
| 001E7900 | evtCommand_CAM_CREATE | 00226FC0 |

## Native behavior

Offsets below are hexadecimal. MakeCamera obtains pose at basic+1C and camera
data at basic+18. It converts the quaternion at pose+50 into vector rows28..31,
transforms local up at data+50 into data+70, and forces its W lane to one.
Only mode data+84 equal to one transforms local target data+40 and adds position
pose+40 into target data+60. Other modes retain the existing target. LookAt then
stores the view matrix into data+00..3F.

LookAt normalizes target minus position over XYZ, normalizes cross(up,direction)
as the right vector, and obtains the remaining axis from cross(direction,right).
The rigid inverse transposes the three XYZ rows, sets their W lanes to zero, and
computes ordered negative translation products with translation W equal to one.
Native vector scratch, masked lanes, ACC overflow and Q remain observable. The
source retains native operation grouping for nonunit quaternions, nonorthonormal
matrices and degenerate directions.

Free-camera creation copies the two default vectors before allocation, sets mode
one and FOV from 0054C1BC, applies rotation then position, backs up the pose, and
builds the view. Look-at creation sets mode zero and FOV from 0054C1C0, applies
position, backs up the pose, copies up then target, and builds the view. Input
aliases into actually allocated camera/pose storage retain their original order.

CAM_CREATE is original command117, verified at descriptor 0052E350+117*8.
It uses actual memset, serial-ID generation, camera/mover/pose/control creation,
radius-one assignment and script integer-result publication. The private command
vectors use the existing host stack-address adapter; this is an adaptation rather
than an original function identity. The 96 interpreter programs invoke the command
through the unchanged original dispatch table.

## Comparison and transfer evidence

The comparison executes 2,554,848 original steps, 239,632 vector instructions,
64 actual constructor setup calls and 384 VM indirect calls. It checks 434,016
vector-register/ACC-overflow/Q values, complete declared RAM, defined raw 64-bit
results, processor status/primitives, callee saves and ordered VM traces. Fixtures
cover signed zero, subnormals, exponent255 encodings, random raw bits, nonunit
rotations, degenerate views, mode differences and backed input/output aliases.

Packed-word primitive support is restricted to opcode-pinned original sites.
Its PEXTLW/PEXTUW/PCPYLD/PCPYUD permutations were independently checked against
[PCSX2's EE MMI implementation](https://raw.githubusercontent.com/PCSX2/pcsx2/master/pcsx2/MMI.cpp).
Recovered C transposes directly, independently of those primitive permutations.
The separate 50,000-case vector prerequisite still agrees on 300,000
software-reference values with the current host build.

Five named Unity roles corroborate the native view/creation/command functions.
The rigid inverse is recorded as a descriptive PS2 identity; no separate named
HD function is invented. All six complete DDS spans resolve uniquely with 16
agreeing callee constraints. The constructor matches additionally verify both
ELF GP bases, equal FOV words and two equal 16-byte default vectors, retaining
all register/opcode/field-offset/branch bits outside reviewed relocations. The
free constructor also has an incoming CAM_CREATE link; both constructor spans
are adjacent. This is static transfer evidence, not DDS execution.

## Current integration

At this batch integration, recovery covered 1,252 / 8,975 recognized functions (13.950%), with 646,522
aggregated comparisons and 187,688 summed original body bytes. The last full run
remains 413 functions / 462,684 cases; 839 additional routines contribute 183,838
focused cases. The 96 existing interpreter cases are checked here but excluded
from the aggregate's new-function count. All 95 registered focused reports then had
current source hashes. There are 590 reviewed HD roles, 659 descriptive PS2 aliases,
46 library identities and 268 shared SMT signature patterns.

The current camera creation graph has no remaining direct bodies at the compared
boundaries. The subsequent [model ownership/cleanup recovery](model-cleanup-findings.md)
reduces selected lifecycle cleanup to 10 bodies /1,440 bytes.
Continue camera/control destruction and its model/event/material dependencies.
Physical camera scheduling/rendering, full VU flags/timing, complete gameplay and
a matching executable remain unproved. Other callback types remain outside this
selected graph.

Evidence: `camera-view-validation.json`, `camera-view-interfaces.json`,
`camera-view-abi.json`, `camera-view-matches.json`, `camera-view-transfer.json`,
the current `camera-view/` capture and `camera-creation-frontier.json`.
Changes were saved in place and rolling outputs overwritten without checkpoints
or backup copies.

The read-only export's language replacement logs the existing processor `rom0`
block-creation diagnostic, also present in earlier exports. Its subsequent DIVU
and function-inventory assertions pass, and all six requested bodies decompile
and merge successfully. The diagnostic does not constitute PS2 ROM validation.
