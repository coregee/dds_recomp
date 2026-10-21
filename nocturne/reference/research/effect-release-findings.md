# Native model-track and special-polygon cleanup

Recovered `src/effect_release.c/h` adds nine complete original functions and
448 summed body bytes. All 1,152 original-instruction/C comparisons pass,
reaching every one of the 90 main instruction addresses. Actual material queue
append, memory-handle coalescing and pool release execute, with 128 original
special-polygon destructor callbacks, 1,680 semaphore boundary calls and 202,668
original steps. The affected C builds with warnings treated as errors. All nine
interfaces were saved in `ghidra/working/Nocturne.gpr`, independently checked
after reopening and exported into the current whole-program inventory.

| PS2 entry | Recovered function | Complete DDS counterpart |
|---|---|---|
| 001A3118 | Eff_ModelTrackPolyDelete | Unresolved |
| 001A3950 | ps2HermitianTrackPolyRelease | Two provisional candidates |
| 001A4368 | ps2SpecialTrackBundleRelease | Two provisional candidates |
| 001660D0 | dds3TrackPolyDelete | 0015B8B8 |
| 001681F8 | ps2SpPolyKind0Delete | 0015D9E0 |
| 001688E8 | ps2SpPolyKind1Delete | 0015E0D0 |
| 001690A0 | ps2SpPolyKind2Delete | 0015E888 |
| 001696D8 | ps2SpPolyKind3Delete | 0015EEC0 |
| 00169D80 | dds3SpPolyDelete | 0015F578 |

Offsets below are hexadecimal. Model-track cleanup checks its owner at +00
through the already recovered major/minor predicate. The special path releases
the bundle at +38, then clears +38 before reloading it; the ordinary path releases
the nonzero record there. Both paths release the effect itself. The special
bundle contains its record at +30. Record cleanup defers material+20 to queue
005520C8 and frees memory-handle+24; it does not free the record separately.
Track-poly cleanup similarly defers material+20, then frees memory-handle+10.

The special-polygon dispatcher reads unsigned LH +B0 and uses the original
00317678 table, with twelve bytes per record. All four original destructor
entries execute. Kind 0 releases track+DC and the object pool slot. Kinds 1/2/3
release track+F0/E0/F4, then memory-handle+F8/E8/FC respectively. Their individual
Ring/RingOld/SphereRing/RollRing names remain provisional; the source records
the proved kind and offsets. The host adapter preserves the full-width callback
argument and aborts unreviewed targets.

The Unity bodies confirm `Eff_ModelTrackPolyDelete`, `dds3TrackPolyDelete` and
`dds3SpPolyDelete`. The existing predicate 001A4208 now has the reviewed HD
identity `Eff_ModelTrackPoly_DANTE_Check`: major 1 and minor C0 or 153..155.
This upgrades its identity without adding another compiled function or case.
The managed release implementations use Unity objects and different guards,
layouts and ownership. They are semantic references for native reconstruction.

Six selected DDS counterparts resolve. For the dispatcher, only the original
LUI/LW address immediates at body offsets 24/32 relocate; the rest of the complete
56-byte span is fixed. Four independently matched destructor spans constrain
the DDS table at 0034E658 and reject the adjacent update dispatcher at 0015F5B0.
The two small helper bodies still have multiple provisional candidates. Static
transfer does not establish DDS execution or equivalent runtime queue state.

Checks compare all declared RAM, Status, processor primitive calls, integer/FPU
callee saves, actual semaphore arguments/results and ordered JALR targets.
Fixtures exercise material null/high-bit values, dirty upper pointer lanes,
both neighbor-coalescing states and selected record/owner aliases. Original
unchecked dereferences and release order remain. Arbitrary tables, malformed
ownership, physical scheduling/rendering, complete camera/model lifetime and
a matching executable are still unproved. Export retains the previously known
`rom0` language-fixup diagnostic; all nine requested functions subsequently
decompiled, and the unsigned-DIVU and 8,975-function inventory checks passed.

At this batch publication, integrated recovery was 1,276 /8,975 functions (14.217%), with 651,770
aggregated comparisons and 189,284 summed original body bytes. The last full
run remains 413 functions /462,684 comparisons; 863 additional functions add
189,086 focused comparisons. All 97 registered focused reports remain current
for their source hashes. There are 603 reviewed HD counterparts, 670 descriptive
PS2 aliases, 46 library identities and 270 shared SMT signatures.

The current camera creation graph has no remaining direct construction bodies
at compared boundaries. Its selected lifecycle graph now has eleven direct
bodies /1,496 bytes remaining. Unresolved indirect material/effect callbacks can
expand that graph. Continue material and generic effect destruction, model
resource/handle cleanup, then object-control and camera destruction.

Evidence: `effect-release-validation.json`, `effect-release-abi.json`,
`effect-release-matches.json`, `effect-release-transfer.json` and the current
`effect-release/` capture. The working project and rolling outputs were updated
in place, with no checkpoint or backup copies.

The subsequent [billboard/particle recovery](particle-release-findings.md)
adds 24 complete bodies, including every entry in the thirteen-destructor
particle table. The current selected lifecycle graph has ten direct bodies
/1,440 bytes remaining; unresolved indirect paths can expand it.
