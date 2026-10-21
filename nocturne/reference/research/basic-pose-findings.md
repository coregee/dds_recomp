# Native pose lifetime, quaternion product and transform cache

Twenty-one complete PS2 routines are integrated as `src/basic_pose.c` and
`src/basic_pose.h`. All pass 6,144 original-instruction/C comparisons, covering
1,080 summed body bytes and all 236 main instruction addresses. The working
Ghidra project was saved in place, reopened to check all 21 interfaces, and the
21 current assembly/pseudocode exports merged into the existing inventory.

The capture executes 50,688 vector instructions and compares all 32 vector
registers, four ACC words, four ACC overflow bits and Q: 841,728 values in total.
It also compares declared RAM, defined integer results, Status, processor
primitives, callee saves and the unchanged VM call trace. There are 320 actual
prelude calls, including initialization followed by release and initialization,
position/rotation mutation, transform creation, optional invalidation and a
second query. Actual recovered pool and quaternion-normalization dependencies
execute; game routines are not replaced with return hooks.

## Native layout and behavior

`basic+1C` points to a 208-byte pose. The tested layout is:

| Offset | Native field |
|---|---|
| 00..3F | Four cached transform rows |
| 40 / 50 / 60 | Position / quaternion / scale, four words each |
| 80 / 90 / A0 | Previous position / quaternion / scale |
| B0 | Identity vector |
| C0 | Pose flags |
| C4 / C8 | Radius / zeroed initialization word |

Initialization succeeds only when the basic is non-null, its pose pointer is
zero, and allocation returns a nonzero pointer. Existing poses return zero.
Initialization writes flags1, position/quaternion `[0,0,0,1]`, scale `[1,1,1,0]`,
the B0 identity vector, and zero C4/C8; it retains uninitialized matrices and
backups. The compared allocation-failure branch uses backed pool metadata whose
bump result is zero, rather than an allocator return hook. This is not a
production out-of-memory experiment. Release clears the pointer after the
actual pool release.

Position/rotation/scale mutations first write `(flags|1)&~2`, then reload their
vector source. Cases where the source overlaps C0 verify that this order is
observable. Position addition and scale multiplication operate on all four
lanes. Quaternion addition is native quaternion multiplication, with no
normalization; the separate rotation getter normalizes all four components.
The position macro getter explicitly sets W to one.

Transform bit2 selects the cache. A clear bit constructs quaternion rows,
broadcasts scale X/Y/Z into the three respective rows, forces translation W to
one, writes the four rows and retains the flag. A set bit reloads existing rows,
including deliberately stale/raw matrices. The quaternion-to-matrix routine
accepts nonunit and zero quaternions and retains native grouping, intermediate
registers and ACC overflow. Inputs include raw exponent255, denormal and signed
zero words, dirty high pointer/mask lanes, source aliases and self-allocation
aliases. `dds3CheckPoseSetFlag` ANDs the sign-extended native word with its full
64-bit mask, rather than silently truncating that mask.

`dds3SerializeID` increments the word at54E9C0 and masks it to16 bits. Its named
Unity body independently shows the increment and clearing of the upper half.

## Unity identities and DDS transfer

Twenty HD roles have reviewed, non-opaque named bodies and pinned semantic
anchors in `basic-pose-matches.json`. `sdfQuat.Mult` calls Unity quaternion
multiplication and `sdfQuat.ToMatrix` calls Unity matrix rotation. Those roles
identify the corresponding PS2 algorithms; they do not establish identical
float grouping, scratch state, layouts or managed null/lifetime behavior.
The separate PS2 scale/rotation/position transform helper at0010E048 has a
descriptive alias: HD `dds3GetTMPoseSet` contains that sequence inline, so no
separate named HD function is invented.

Twenty complete DDS instruction spans resolve, with six agreeing call links.
The serial-ID body has no full-span match under the existing relocation mask;
the subsequent [basic creation recovery](basic-creation-findings.md) resolves its
complete20-byte DDS span with explicit verified GP relocation. See `basic-pose-transfer.json` and the
shared `BasicPoseQuaternionAndTransformCache` signature. Static DDS agreement
does not establish DDS execution.

## Remaining camera construction

`camera-creation-frontier.json` now includes the actual lifecycle records for
type3 mover and type4 camera, rather than only the generic allocator's direct
calls. Type17 path has no lifecycle record in the original table. There are
no remaining direct bodies at compared boundaries after the subsequent
[basic creation](basic-creation-findings.md) and [camera view/command117
recovery](camera-view-findings.md). Selected initialization/release callbacks
still expose 10 bodies /1,440 bytes. All18 original type records are inventoried;
other types and unresolved indirect calls are not claimed recovered.

Continue camera/control destruction and its model/event/material cleanup.
Radius-collision routines, broader object update callbacks and physical camera
movement remain outstanding. The original direct-only rotation frontier is marked superseded.

These are bounded software instruction comparisons. Full VU flags, pipeline
timing, physical PS2 behavior, complete gameplay and a matching executable remain
unproved. No new full-suite run or checkpoint is claimed.

The subsequent [model ownership/cleanup recovery](model-cleanup-findings.md)
adds 15 complete prerequisites; the current selected lifecycle graph has 10
bodies /1,440 bytes remaining.
