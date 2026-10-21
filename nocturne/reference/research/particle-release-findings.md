# Billboard ownership and the complete particle destructor family

Recovered `src/particle_release.c/h` adds 24 complete original functions and
1,368 summed body bytes. All 3,072 original-instruction/C comparisons pass,
reaching all 269 main instruction addresses. The runs execute 2,432 actual
particle/billboard destructor callbacks and 1,338 semaphore boundary calls over
1,187,399 original steps. Independent output checks cover 533 diagnostic cases
and 11,760 bytes. The affected C builds with warnings treated as errors. All 24
interfaces were saved in `ghidra/working/Nocturne.gpr`, checked after reopening
and exported successfully into the current whole-program inventory.

## Native ownership

Offsets below are hexadecimal. Billboard texture cleanup decrements and stores
refcount+08 before testing for zero. At zero it executes actual printf with
`BillManager Free Tex`, defers texture+00 and frees memory-handle+40. Animated
P2A cleanup decrements refcount+14 similarly, prints `BillManager P2A Free`, then
releases texture records through signed count+10 and data+18 before freeing its
own memory-handle+00. The count and data pointer reload after each child call.
Counter zero underflows naturally; the native code adds no guards.

Billboard deletion uses unsigned LH+2C and the original twelve-byte records at
00317080. Both destructors release resource+30 and the object pool slot. Empty
normal deletion and opaque P2A cleanup in Unity are excluded as native source
identities; the dispatcher itself has a reviewed named counterpart.

Particle basic cleanup uses unsigned LH+30. Kind 1 releases physics+38 through
its memory-handle+0C; kinds 2/3 release track-poly+40/+44; kind 4 releases the
model-track effect list at +44. It always deletes billboard+F4 and releases the
backing descriptor at +F8 through that descriptor's memory-handle+00. The
model-track list snapshots count+04, reloads data+00 per item, executes actual
effect cleanup and finally frees memory-handle+08. Its original signed LW count
and unsigned loop comparison are retained.

The normal and Exp particle dispatchers use unsigned LH+140 and the original
thirteen-entry destructor table at 00317278. All thirteen callbacks execute.
The first eleven call basic cleanup and release the particle pool slot. Kind 11
first frees memory-handle+17C; kind 12 conditionally frees +174. Their individual
Spiral/Smoke/etc. names remain provisional; source records the original kind.

The Unity reference confirms five roles: billboard deletion, model-track list
deletion, particle basic deletion and both particle dispatchers. The two otherwise
identical native dispatchers are distinguished by copy entries in their original
generic effect records. Type 1's copy path tests for -1 and copies/reconfigures
its billboard, matching `dds3ParticleExpCopy`; type 0 preserves the simpler
`dds3ParticleCopy` path. Those copy routines provide identity context and are
not compiled or counted in this batch.

## Transfer to DDS

Twenty-one selected complete spans resolve. Two unique extra-resource
destructors locate the DDS table at 0034E258. Every table entry agrees with a
complete candidate body and its shared basic-cleanup callee, distinguishing
the eleven individually identical short wrappers.

| Kind | Nocturne destructor | DDS destructor |
|---|---|---|
| 0 | 0015E328 | 00153B10 |
| 1 | 0015E978 | 00154160 |
| 2 | 0015EFC8 | 001547B0 |
| 3 | 0015FB70 | 00155358 |
| 4 | 00160150 | 00155938 |
| 5 | 00160860 | 00156048 |
| 6 | 00160F20 | 00156708 |
| 7 | 001614C8 | 00156CB0 |
| 8 | 00161A70 | 00157258 |
| 9 | 00162248 | 00157A30 |
| 10 | 00162518 | 00157D00 |
| 11 | 00163060 | 00158848 |
| 12 | 00163780 | 00158F68 |

The two complete particle dispatchers resolve to 0015A3C0/0015A968, with only
their reviewed LUI/LW table-address immediates relocated. A unique complete
incoming generic effect dispatcher at DDS 0014FAB8 preserves type positions
0/1/2 and corroborates their ordering. That incoming routine remains a static
lead, outside this batch's compiled count. The complete basic cleanup span
also corroborates DDS billboard dispatch at 00151F00 and animated deletion at
00151368. Physics, backing, model-track list and basic cleanup resolve to
00159CD8, 00153728, 00188480 and 00153920 respectively.

The DDS billboard table identifies normal deletion at 00151210, but its
56-byte body null-tests resource+30 before release. Nocturne's 44-byte body
calls unconditionally. This guarded variant is excluded from the complete-span
count, and the table rejects two unrelated masked 44-byte candidates. The two
diagnostic/refcount bodies remain unmatched. Static transfer does not establish
DDS execution or equivalent runtime ownership.

## Verification and remaining work

Checks compare full declared RAM, Status, processor primitive calls, integer/FPU
callee saves, semaphore arguments/results, ordered JALR targets and independent
diagnostic bytes. Fixtures cover all thirteen particle and both billboard
callbacks, all basic-cleanup kinds, finite shared-resource lists, refcount
underflow/high bits, signed animation counts, upper pointer lanes and memory
coalescing. Printf executes the actual recovered formatter into bounded guest
stdout. No original game/library function is replaced by a return hook.
Unreviewed callback targets abort in the host adapter. Malformed ownership,
physical console/deferred scheduling/rendering, complete gameplay and a matching
executable remain unproved. Export retains the known `rom0` language-fixup
diagnostic; every requested function subsequently decompiled and the unsigned
DIVU and 8,975-function inventory checks passed.

At that batch, integrated recovery was 1,300 /8,975 functions (14.485%), with 654,842
aggregated comparisons and 190,652 summed original body bytes. The last full
run remains 413 functions /462,684 cases; 887 additional functions add 192,158
focused cases. All 98 registered focused reports remain current for their
source hashes. There are 608 reviewed HD counterparts, 689 descriptive PS2
aliases, 46 library identities and 271 shared SMT signatures.

Camera construction has no remaining direct bodies at compared boundaries.
Its selected lifecycle graph has ten direct bodies /1,440 bytes remaining;
unresolved indirect paths can expand it. Continue the remaining generic effect
categories, model resource/handle release and camera/control destruction.

The subsequent [Magatsuhi and P2A release batch](magatuhi-release-findings.md)
continues generic category3 cleanup and records the wider nested effect-part
callback frontier. Current totals are in `recovery-progress.json`.

Evidence: `particle-release-validation.json`, `particle-release-abi.json`,
`particle-release-matches.json`, `particle-release-transfer.json` and the current
`particle-release/` capture. Work and rolling outputs were saved in place,
without checkpoint or backup copies.
