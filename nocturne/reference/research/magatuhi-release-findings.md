# Magatsuhi ownership and P2A polygon release

`src/magatuhi_release.c/h` adds ten complete original bodies and 452 summed
function bytes. All 1,408 focused original-instruction/C comparisons pass:
1,280 cases cover the new routines and 128 recheck existing billboard/particle
dependencies under the new address routing. Every one of the 92 new main
instruction addresses executes. The runs contain 268,231 original steps,
128 actual Magatsuhi callbacks, 246 semaphore calls and 49 independent
diagnostic cases /1,050 bytes. The affected C builds with warnings treated as
errors. All ten interfaces were saved in the working Ghidra project, checked
after reopening and exported into the current 8,975-function inventory.

## Native release order

Offsets below are hexadecimal. The Bezier descriptor releases memory-handle+08;
the Magatsuhi billboard descriptor releases memory-handle+34. The Magatsuhi
object releases its billboard through pointer+1C, then releases its pool slot.
Both descriptor routines dereference their argument without a null guard;
the owned memory handle itself may be zero.

| Original kind | Role | Nocturne entry | Native cleanup fields, in order |
|---|---|---|---|
| 0 | SmokeConv | 001A5F68 | Bezier+180, Magatsuhi+18C, memory-handle+190 |
| 1 | Point4 | 001A6908 | Bezier+184, Magatsuhi+188, memory-handle+18C |
| 2 | Cylinder | 001A72D8 | Magatsuhi+120, memory-handle+128 |
| 3 | Spiral | 001A7B08 | Magatsuhi+124, memory-handle+12C |
| 4 | Smoke | 001A83B0 | Magatsuhi+124, memory-handle+128 |

`dds3MagatuhiParDelete` at 001A8C78 uses the wrapper's signed LW kind+00 to
index 24-byte records at 00320040. Its destructor is word+08. The original
JALR delay slot loads child+04; the wrapper pool slot is released after that
callback. The five child objects release their owned handles rather than
calling pool release on the child directly. Native pointer reloads and order
are retained.

`dds3P2APolygonDelete` at 0015D778 first defers material+84, then deletes the
billboard at +80 through its original dispatch/refcount/formatter dependencies,
then releases its own pool slot. Adjacent 0015D918 is a render routine and is
not substituted for this destructor.

## Unity identification

Eight named roles are reviewed: the five variants, Magatsuhi object deletion,
Magatsuhi particle-wrapper deletion and P2A polygon deletion. The five variant
positions are independently constrained by the Unity static initializer
at 1823D6EE0. Each record installs its Delete delegate at +20; resolving the
referenced MethodInfo cells through `pc/il2cpp/script.json` identifies:

| Kind | MethodInfo cell | Unity destructor |
|---|---|---|
| 0 | 182E8E180 | 1823DE9A0, effMagaSmokeConvDelete |
| 1 | 182E8E1F8 | 1823DCD50, effMagaPoint4Delete |
| 2 | 182E8E2F0 | 1823DAEE0, effMagaCylinderDelete |
| 3 | 182E8E038 | 1823E1C40, effMagaSpiralDelete |
| 4 | 182E8E148 | 1823E0210, effMagaSmokeDelete |

The original create/draw/delete records and retained managed ownership fields
agree with these positions. Identification does not rely on function address
order or on the similar inlined Unity cleanup fragments. Unity's mesh
destruction, null/type guards and managed layouts differ from native ownership.
Its shared empty Bezier/billboard frees are excluded from exact HD identities;
the two native descriptor routines retain descriptive PS2 aliases.

## Transfer to DDS

All ten selected complete spans resolve, with the five destructor positions
also agreeing in the unique DDS table at 00355730.

| Nocturne | DDS | Role |
|---|---|---|
| 001ABE20 | 0018DF90 | Bezier owned handle |
| 001A54C8 | 001893C0 | Magatsuhi billboard owned handle |
| 001A5280 | 00189178 | Magatsuhi object |
| 001A5F68 | 00189E60 | SmokeConv |
| 001A6908 | 0018A800 | Point4 |
| 001A72D8 | 0018B1D0 | Cylinder |
| 001A7B08 | 0018BA00 | Spiral |
| 001A83B0 | 0018C2A8 | Smoke |
| 001A8C78 | 0018CB70 | Magatsuhi particle wrapper |
| 0015D778 | 00152720 | P2A polygon |

The complete 72-byte wrapper only relocates its LUI/LW table address and pool
J target; every other instruction bit is fixed. P2A's billboard and pool
callees agree with previously reviewed complete spans. Its material release
dependency additionally resolves to DDS 002DAA68 across all 52 bytes, allowing
only the GP queue immediate and append J target to relocate. Both ELF GP bases
are verified: 00554170 and 003C0CF0. The queue addresses become 005520C8 and
003BDA18; the append callee is the previously reviewed DDS 002D3C30.
This already compiled dependency is excluded from the ten-new-function count.
Static transfer does not prove DDS execution.

## Remaining work and current evidence

At this batch, integrated recovery reached 1,310 /8,975 functions (14.596%), with 656,122
aggregated comparisons and 191,104 summed original body bytes. The last full
run remains 413 functions /462,684 cases; 897 additional functions contribute
193,438 focused cases. Rechecks of existing functions are not counted twice.
All 99 registered focused reports remain current for their source hashes.
There are 616 reviewed HD counterparts, 691 descriptive PS2 aliases, 46 library
identities and 272 shared SMT signatures.

The [camera lifecycle graph](camera-creation-frontier.json) still contains ten
direct unrecovered bodies /1,440 bytes. The separately recorded
[effect-part frontier](effect-part-release-frontier.json) inspects the original
generic, effect-part and a bounded prefix of the nested PCP callback tables.
At this batch it exposed 56 unique unrecovered table targets, including three without an
exported function body. Subsequent [PCP cleanup recovery](effect-leaves-findings.md)
recognizes those three bodies and reduces the current unresolved count to 19.
This is not a complete table-size or runtime
reachability claim. The three targets required body-boundary discovery before recovery;
the larger callback family is additional work beyond the direct lifecycle count.
The effect-part model destructor tails into `mdlFreeSub`, while PCP cleanup can
recurse through child effect parts. Continue the model handle/resource release
chain and those actual callback dependencies before claiming generic cleanup.

Checks compare full declared RAM, Status, processor primitives, callee saves,
semaphore values, callback target/argument order and independent diagnostic
bytes. Fixtures cover all five Magatsuhi kinds, owned/null handle combinations,
both neighbor coalescing states, actual pool ownership, dirty argument upper
lanes and P2A material/billboard variants. No game/library body is replaced by
a return hook. Arbitrary malformed ownership, physical deferred scheduling,
full console gameplay and a matching executable remain unproved. Export retains
the known `rom0` language-fixup diagnostic; every requested export completes,
the inventory merges and unsigned DIVU verification passes.

Evidence: `magatuhi-release-validation.json`, `magatuhi-release-abi.json`,
`magatuhi-release-matches.json`, `magatuhi-release-transfer.json` and the rolling
`magatuhi-release/` capture. Changes were saved in place without checkpoints or
backup copies.
