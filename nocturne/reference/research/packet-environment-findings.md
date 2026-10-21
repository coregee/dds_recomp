Current verified checkpoint: **413 functions /462684 fresh original-instruction cases**. [Findings](texture-environment-findings.md) · [Next frontier](texture-environment-next-frontier.md). Earlier checkpoint narratives below are retained as historical records.

# Packet builders and environment records

Current checkpoint: **410 reconstructed functions**, **461,916 completely fresh original-instruction comparisons**, **46,736 validated original body bytes**. Compiled source covers approximately **4.58%** of8,955 recognized functions. Full or near-full recovery remains unfinished.

Sixteen complete original bodies add1,764 active bytes across1,776 contiguous bytes, with twelve excluded unreachable NOP bytes. No boundaries change. The [saved Ghidra project](../ghidra/checkpoints/410-functions/Nocturne.gpr), [batch certificate](packet-environment-validation.json) and [integrity report](checkpoint-410-integrity.json) retain the proof.

| Entry | Recovered alias | Active bytes |
|---|---|---:|
| `002ad130` | `ps2DrawInitializeInlineRegisterPacket` | 64 |
| `002ad170` | `ps2DrawInitializeReferencedRegisterPacket` | 132 |
| `002ad1f8` | `ps2DrawBuildRegisterGroupPacket` | 180 |
| `002ad2b0` | `ps2DrawBuildOffsetRangePacket` | 136 |
| `002ad338` | `ps2DrawBuildFixedStatePacket` | 68 |
| `002ad380` | `ps2DrawBuildSingleRegisterGroup` | 164 |
| `002ad428` | `ps2DrawBuildConfiguredEnvironment` | 316 |
| `002ad720` | `ps2DrawInitializeEnvironmentRecord` | 160 |
| `002ad7c0` | `ps2DrawLinkEnvironmentRecord` | 64 |
| `002ad800` | `ps2DrawBuildContextReference180` | 68 |
| `002ad848` | `ps2DrawBuildContextReference70` | 68 |
| `002ad890` | `ps2DrawAppendStateReference1a0` | 92 |
| `002ad8f0` | `ps2DrawAppendStateReference1e0` | 92 |
| `002ad9f0` | `ps2DrawInitializeAuxiliaryRecord` | 120 |
| `002adb68` | `ps2DrawStoreNonnegativeModeByte` | 20 |
| `002adb80` | `ps2DrawResetGlobalState` | 20 |

## Recovered behavior

Inline and referenced packet constructors preserve full64-bit GIF values, separate16-bit QWC and28-bit source address masks, original store order and wrapping word count arithmetic. The nine-argument register-group builder usesA0..A3/T0..T3 and a raw32 ninth argument at originalSP+0. Its word shifts sign-extend before64-bit ORs; the offset mode tests the full64-bit argument. A32-bit decompiler interface would lose meaningful bits.

The configured environment builder executes two real register-group calls. It rereads the mode byte after the first call and configuration dimensions after both calls, then builds the offset, pair-tail and fixed-state packets. Selected configuration/output/global aliases expose those live reads. Environment initialization records its original callback and configuration pointer, then executes the recovered offset/fixed-state builders.

Context-reference helpers test full64-bit zero and select source180/190 or70/B0. State references use source1A0/1E0, mask to28 address bits, clear the output quadword and call the actual REF appender. Record linking executes real node append followed by real chain append, preserving aliases between the two calls.

The auxiliary record uses the actual inline constructor before its ordered field stores. The mode setter clamps a signed64-bit negative argument before taking its low byte. Global reset writes byte55188B, word5293F8 and word551890 in that order. The separate four-byte BSS word5293F8 has an explicit host address binding and participates in complete RAM comparisons.

## Unity and shared SMT evidence

The [frozen Unity packet review](drafts/packet_builders/reference-review.json) covers eight named native methods: packet constructors and GIF packing helpers, alongside managed frame/zbuf/xyoffset/scissor/default/clear fields. It narrows packet roles and parameter meanings. Managed initialization, field representation and native-port behavior still require comparison; no new exact HD identity is promoted. The ledgers contain254 reviewed HD pairs,46 independent library identities,153 descriptive PS2 aliases and114 transferable patterns.

The [expanded disk-only DDS cohort](drafts/draw_environment/transfer-review.json) has32 unique whole-body candidates and30 consistent direct call/jump targets sharing offset00027480. The scan masks reviewed relocated jumps, GP references and completed ELF addresses while retaining relative branches, field offsets, literals and tag masks. DDS boundaries, globals, indirect targets and original/C behavior remain unverified; zero DDS identities are promoted.

## Verification and preservation

The sixteen canonical routines pass4,096 focused original/C cases across ten complete RAM spans totaling1,124,852 bytes and5,120 canary bytes. Comparisons retain raw argument widths, the original ninth stack slot, Status, callee-save preservation and independent primitive/kernel/deferred/order traces. Every selected path mode includes both initial IRQ states. Seventeen malformed rows are rejected, and bindings/RAM restore after success, rejection and an injected BSS mismatch. The actual focused host DLL is frozen separately.

All410 compiled routines pass461,916 entirely fresh original-instruction comparisons, with zero reused rows. The report pins97 source/header and108 verifier/input files; full capture pins222 inputs before and after execution. Seventeen ABI groups pass after independently reopening the saved project. All8,955 recognized functions export/decompile with zero failures.

The exact preceding394 checkpoint preserves1,915 artifacts,197 certified source/verifier inputs,214 capture inputs and457,820 original rows, plus its project and snapshot. Earlier archives remain intact. The original runtime-state getter is retained, and the same2,004 historical STOP-capture warning lines remain in order; the new focused capture has none.

A separate Java preflight caught a scope error in the unused full-capture adapter after the first focused proof passed. The [diagnostic archive](diagnostics/packet-environment-producer-scope/archive.json) retains that adapter, compiler errors and complete first proof. The corrected producer compiled, then a wholly new4,096-case focused capture and the complete fresh regression established the final inputs. No source mismatch was observed.

Selected coherent configurations and RAM aliases do not prove arbitrary inputs, physical GS/DMA, concurrent callbacks, private-stack equivalence or a matching executable. The [next frontier](packet-environment-next-frontier.md) starts with the texture packet helper and installed environment callback. Full or near-full source and remaining code/data discovery remain active.

The [frozen next-three proof](packet-environment-private-review.json) retains952 active bytes across768 focused cases: a twelve-argument texture helper, its actual environment caller, and an unrecognized160-byte callback reached through a stored function pointer. These remain outside410 source functions; the missing callback still needs boundary creation and saved ABI proof. The expanded static DDS review has35 unique bodies and34 checked direct targets. The texture helper uses offset27438, while34 other bodies use27480; its callers resolve to that individual candidate.

The full original execution completed before a disk-full error in the final row-copy step. [Recovery evidence](drafts/packet_environment/capture-recovery.json) retains the222-file final input check, complete original rows preserved on G:, and an exact hash-verified header/prefix recipe for the truncated duplicate. The reconstructed461,916-row fresh capture passed the entire C comparison and separate arithmetic checks; no historical rows were substituted.

A separate [storage prototype](drafts/packet_environment/compressed-storage-prototype.json) round trips596 original sample rows as standard gzip JSONL. It streams one compressed body and fills a reserved metadata member afterwards; the8,387,081-byte logical sample occupies2,577,658 physical bytes. Canonical producer/consumer integration and a full pinned capture remain future work. This prototype does not change the current capture or function count.
