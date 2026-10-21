# Native model ownership and camera cleanup prerequisites

Recovered `src/model_cleanup.c/h` adds 15 complete native functions and 1,148
summed original body bytes. All 4,608 original-instruction/C comparisons pass:
4,096 cover the new functions and 512 recheck the existing motion base initializer
and cut setter through address adapters. Every one of the 217 main instruction
addresses in the new functions executes. The affected C compiles with warnings
treated as errors. All 15 interfaces were saved in the working Ghidra project,
checked after reopening and exported successfully.

| PS2 entry | Recovered function | Complete DDS span |
|---|---|---|
| 0010F970 | dds3AreaBasicTypeToItemType | 00111160 |
| 0010FA68 | dds3AreaBasicReleaseItem | 00111258 |
| 0010FAB8 | dds3AreaBasicGetItemArray | 001112A8 |
| 001DCE88 | mdlFreeBlur | 00217438 |
| 001DDB68 | mdlGetMajorNum | 002183D0 |
| 001DDB78 | mdlGetMinorNum | 002183E0 |
| 001A4208 | ps2ModelNeedsSpecialRelease | Unresolved |
| 001E3AF0 | evtDeleteUnitHandle | Unresolved |
| 002A9650 | ps2MemoryHandleDeferredRelease | Unresolved |
| 002B0648 | ps2ModelRootRelease | 002D7AC8 |
| 002B2A80 | ps2ModelTextureListRelease | 002D9FC8 |
| 002B3520 | ps2MaterialDeferredRelease | Unresolved |
| 002B3B50 | sdfMotionNodeFree | 002DB1F8 |
| 002B3C60 | sdfMotionCtrlrFree | 002DB308 |
| 002B4100 | ps2MotionNodePoolDestroy | Ambiguous: 147 candidates |

## Native ownership and ordering

Offsets below are hexadecimal. Area item class is one only when the original
full-width type equals eight. Basic+18 points to indexed-array handles selected
by type*4. ReleaseItem reads the item's type byte at 0F and searches/recycles its
actual world-array slot. Dirty upper item argument bits preserve native full-width
equality rather than matching a stored low-word pointer automatically.

Model-root release optionally defers the material list at root+0C, releases the
array at +10, and then either queues the root at 005520B8 or immediately releases
the array at +00 and the root. Texture-list release snapshots signed LH count+4,
reloads data+0C for each element, optionally queues textures at 005520A0, and
releases the actual array/backing handle. Handle and material release use separate
queues at 00552078 and 005520C8. Full-width flags, including nonzero upper bits
with a zero low word, retain the original branch behavior.

Motion controllers use next+00, parent+04, parent list+14 and array+10. Free unlinks
the controller by full-width comparison, snapshots the signed array count, calls
each node's actual vtable destructor, then releases the array and controller.
The original body reloads array+10 only after a positive-length loop. Five unchanged
original vtables select destructor 002B4100, which really releases the node through
the pool; it is not an empty substitute. The host callback adapter executes that
body and aborts for other targets. The existing initializer writes parent+4 before
vtable+0; the existing cut setter writes +8. Their adapters are private host helpers,
not additional recovered original functions.

Blur cleanup follows handle+30 to a header and nodes with next+0/root+4. It defers
each model root, releases nodes and header, then clears handle+30. Major/minor
queries read handle+0C to unsigned halfwords at +8/+A. The native special-release
predicate requires major one and minor C0 or 153..155. Event-unit cleanup clears
basic+8C to data+18 field+80, releases and clears owned +68 pool data and +9C path
control, releases the unit, and returns one; null unit also returns one.

## Evidence and limits

The final capture executes 405,252 original steps, 672 actual setup calls,
460 actual motion-destructor calls and 1,984 semaphore boundary calls. It checks
complete declared RAM, defined raw 64-bit results, processor status/primitives,
callee saves, kernel arguments/results and the ordered motion callback trace.
Actual pool, memory-handle coalescing, deferred queue append, world-array search
and path/spline release execute. Fixtures include empty/head/interior/missing
ownership, signed negative counts, queue rollover, backing-handle allocation,
raw argument lanes and selected aliases. The current capture has no uninitialized
reads and all writes stay within declared RAM or private stack.

Nine named Unity roles corroborate area, blur, major/minor, event-unit and motion
ownership. Empty shared HD model-root/texture-list bodies and the opaque material
delayed-free export are excluded as exact identities. Six new routines retain
descriptive PS2 aliases. Ten complete DDS spans resolve with nine agreeing callee
constraints. The unique model-root match additionally verifies both ELF GP bases
and its sole GP ADDIU relocation: queue 005520B8 maps to 003BDA08. Runtime queue
contents are not compared. Other missing or ambiguous DDS spans remain explicit.

At this batch publication, integrated recovery was 1,267 /8,975 recognized functions (14.117%), with
650,618 aggregated comparisons and 188,836 summed original body bytes. The last
full run remains 413 functions /462,684 cases; 854 additional routines contribute
187,934 focused cases. Existing motion-helper cases are checked here but do not
increase the aggregate. All 96 registered focused reports have current source
hashes. There are 599 reviewed HD counterparts, 665 descriptive PS2 aliases,
46 library identities and 269 shared SMT signature patterns.

The current camera creation graph still has no remaining direct bodies at compared
boundaries. Its selected lifecycle dependencies have reduced from 28 bodies /2,796
bytes to 14 bodies /1,668 bytes. Continue model resource/effect/material release,
then control-work and camera destruction. Other callback targets, cyclic/malformed
graphs, full camera scheduling/rendering, physical PS2 behavior, DDS execution and
a matching executable remain unproved.

Evidence: `model-cleanup-validation.json`, `model-cleanup-interfaces.json`,
`model-cleanup-abi.json`, `model-cleanup-matches.json`, `model-cleanup-transfer.json`,
the current `model-cleanup/` capture and `camera-creation-frontier.json`. The
working project was saved in place; current captures/logs were overwritten without
checkpoints or backup copies. The read-only export retains the existing processor
`rom0` diagnostic during language replacement; its subsequent DIVU/inventory
assertions pass and all 15 requested bodies export and merge successfully.

The subsequent [effect release recovery](effect-release-findings.md) adds nine
complete bodies and upgrades the special-model predicate to its reviewed Unity
identity. The current selected lifecycle graph has eleven direct bodies /1,496
bytes remaining; unresolved indirect callbacks can expand it.

The subsequent [billboard/particle recovery](particle-release-findings.md)
adds 24 complete bodies, including every entry in the thirteen-destructor
particle table. The current selected lifecycle graph has ten direct bodies
/1,440 bytes remaining; unresolved indirect paths can expand it.
