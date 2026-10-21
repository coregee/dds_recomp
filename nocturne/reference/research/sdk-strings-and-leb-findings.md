# PS2 string and integer-decoding helpers

Eight more library routines are recovered in `src/ps2_sdk_helpers.c/.h`. All 15,436 new original-instruction fixtures pass. This batch establishes a checkpoint of 166 compiled functions and 109,549 cases (1.858% of 8,935 recognized functions). Their chosen aliases identify observed behavior; the original library version and symbol spelling remain unconfirmed. They have no reviewed HD counterparts.

| Original entry | Source alias | Listed words | Summed body bytes |
|---|---|---:|---:|
| `002d57f8` | `ps2Strcat` | 75 | 300 |
| `002d5924` | `ps2Strchr` | 100 | 400 |
| `002d5e48` | `ps2Strncmp` | 109 | 436 |
| `002d6000` | `ps2Strncpy` | 111 | 444 |
| `002d61c0` | `ps2Strrchr` | 20 | 80 |
| `002d6210` | `ps2Strstr` | 33 | 132 |
| `002d1e08` | `ps2ReadUleb128` | 17 | 68 |
| `002d1e50` | `ps2ReadSleb128` | 22 | 88 |

The original-byte audit independently re-encodes all 487 listed instructions against `game/SLUS_209.11`, totaling 1,948 bytes. Enclosing spans total 1,952 bytes because `strncmp` omits one unreachable NOP at `002d5fc4`; padding at `002d61bc` lies outside `strncpy`. Seven routines are leaves. Concatenation calls the existing original `strcpy` at `002d5bf8`, adding 69 connected instruction words. None reads game tables, global work or RNG state.

`drafts/next_sdk_batch/manifest.md` records complete original span hashes, source hashes, real callers, source review and the separate actual-word audit. The canonical library ledger contains these aliases alongside the previously recovered 25 routines. All 33 library interfaces pass the saved EE register audit: these eight use four-byte `a0` through `a2` arguments and `v0` pointer/integer results, with argument count appropriate to each signature.

## String behavior and access stages

`strcat` scans the destination using its initial byte alignment. An aligned 16-byte path performs an initial eight-byte load before its first 16-byte load. The terminating block is scanned bytewise, then the real recovered `strcpy` appends the source and NUL. The result remains the initial destination. `strchr` narrows the target to its low byte, probes aligned eight- or 16-byte blocks for zero/target, then searches bytes; target zero returns the NUL address. A final reread determines pointer versus NULL.

`strncmp` returns the exact unsigned byte difference, rather than a normalized sign. Count zero accesses no memory, including NULL arguments. Its equal full-block loop rereads the left block for NUL. Crucially, the 16-byte continuation loads the next **left** block before checking whether 16 comparison bytes remain. Counts 17 through 31 can therefore probe the complete second left block while reading the right tail only bytewise. This speculative block must be backed even when the counted comparison span is shorter. The eight-byte continuation checks the remaining count before its next load.

`strncpy` writes exactly the supplied count, with zero padding after a source NUL and no invented final terminator on truncation. Count zero accesses no memory. Its first aligned 16-byte detector complements the input **before** byte subtraction, then ANDs with the complemented input. In addition to NUL, bytes `0x01` through `0x7e` conservatively stop that fast path. Preserving this detector matters for overlapping buffers and store staging. A possible first 16-byte store is followed by another 16-byte probe that can branch into eight-byte stores. Counts 8 through 15 at initial 16-byte alignment remain scalar. The reconstructed C retains repeated loads and block snapshots before writes.

`strrchr` performs scalar low-byte comparisons and returns the last matching character; target zero returns the terminating NUL. `strstr` retains the original bytewise retry order, reads the initial needle byte even when the haystack is empty, and checks the next needle byte before the corresponding haystack byte. An empty needle returns the haystack pointer. Terminated read-only aliases are valid for the search routines.

The source uses explicit byte accesses and block snapshots to preserve observed ordinary-RAM ordering. Counts narrow to low 32 bits; targets narrow to low eight bits. Whole blocks actually probed must be readable, and evolving overlapping source strings must terminate within backed storage. PS2 address wrap, MMIO, concurrent mutation and atomic EE bus transactions are outside portable C validation.

## Bytewise integer decoders

The decoders consume seven-bit payload chunks until a byte has its continuation bit clear, then write exactly one four-byte result and return the next source pointer. Output is complete, aligned four-byte storage. Source and output may overlap because all input reads precede the final store.

The original `SLLV` masks shifts with 31. Overlong input retains these wrapped shifts; the implementation adds no overflow, maximum-length, canonical-encoding or bounds repair. For example, bytes `80 80 80 80 80 01` store `0x00000008` and return source plus six. Signed decoding extends the sign only when total shift after the final byte is below 32 and that byte's bit 6 is set. Longer encodings retain their low-word payload result.

Caller `002d2b60` chains unsigned decoding at `002d2c0c` into signed decoding at `002d2c18`, storing into aligned fields `s1+8` and `s1+0xc` and passing the returned next pointer. This original caller grounds the pointer/output ABI independently of inferred pseudocode signatures.

## Validation evidence

`SdkHelperVectors.java` and `compare_sdk_helpers.py` add 15,436 canonical cases: concatenation 532, first-character search 1,280, bounded comparison 1,314, bounded copy 5,762, last-character search 1,280, substring search 656 and 2,306 per decoder. These include all 16 source alignments, 30 explicit speculative left-block tails, every first-detector false-positive value, varied overlap data, all 32 wrapped decoder shift residues and legitimate one-past decoder pointers. Every arena byte and both guards are compared. The original recovered copy dependency executes normally.

The preserved independent actual-word interpreter compares compiled reviewed source with every byte of a 1,024-byte arena and normalized returns across 21,388 cases, with zero mismatches. It executes real original `strcpy` for concatenation and includes delay slots, branch-likely annulment and scalar/MMI operations. Thirty-three-byte walking-bit encodings cover all 32 masked decoder shift residues, with independent arithmetic assertions for those values and the six-byte anchor. This is separate instruction-model evidence, not PS2 hardware capture and not an additional canonical case count.

Source review independently checked the initial concatenation LD/LQ sequence, the bounded comparison's speculative left-block reads, bounded copy's 16/16/8 stages and the decoders' final-store ordering. The saved report pins the actual isolated DLL tested, whose source body is unchanged by canonical promotion. The canonical header changes only its include guard.

The saved PS2 snapshot is `backups/SLUS_209.11-2026-10-03-212854.gzf`, SHA-256 `e5667d08e94a12730ff60366f635767b307636fb92e29c1d353f75bf5f721cc5`. It contains 174 reviewed HD counterparts, 33 library aliases, two PS2 game aliases and the established partial types. All 33 ABI checks pass. The live PC analysis transaction remains preserved.

Exact block detectors, stage order, byte counts and decoder wrap rules are useful cross-game fingerprints. Establish the other executable's original instructions and ABI before transferring source; a standard C function name alone does not prove an equivalent implementation.
