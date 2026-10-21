# RNG initialization and field flags

Eighteen reviewed PS2 routines now have compilable C in `src/kernel_event_neighbors.c/.h` and native HD identities in `function-matches.tsv`. All 7,828 new original-instruction cases pass. The complete checkpoint is 185 compiled C functions and 118,033 comparisons (2.071% of 8,935 recognized functions), with 192 reviewed HD counterparts. Source/verifier/vector hashes pass the progress builder checks.

| PS2 entry | Interface | Native HD entry |
|---|---|---|
| `002c0c98` | `sdfRandomize` | `18230c8d0` |
| `00125990` / `001259a8` / `001259c0` | `fldSeqOnFlag` / `fldSeqOffFlag` / `fldSeqCheckFlag` | `182201970` / `182201900` / `182201890` |
| `001259d0` / `001259e0` / `001259f8` | `fldProcOnFlag` / `fldProcOffFlag` / `fldProcCheckFlag` | `182200450` / `1822003f0` / `1822000c0` |
| `001234f8` / `001235b0` | `fldLightMaClear` / `fldLightMaChk` | `182051200` / `182050fe0` |
| `001236e8` / `00123718` / `00123748` | `fldRifutoMaClear` / `fldRifutoMaStart` / `fldRifutoMaChk` | `182056590` / `182056640` / `1820563b0` |
| `001237a8` / `001237d8` / `00123810` | `fldRiberaMaClear` / `fldRiberaMaStart` / `fldRiberaMaChk` | `182056240` / `1820562f0` / `182056060` |
| `00123870` / `001238a0` / `001238d8` | `fldEsutoMaClear` / `fldEsutoMaStart` / `fldEsutoMaChk` | `18204fce0` / `18204fd90` / `18204fb00` |

All 166 contiguous original words (664 bytes) were independently re-encoded against the ELF. Two source reviews checked complete PS2 and native bodies, field widths, store order and metadata. The original/native artifact hashes are retained in `drafts/kernel_event_neighbors/body-evidence.json`; `independent-review.md` records the separate review and fixture assessment.

## Original data and interfaces

The ELF's primary GP word is `70 41 55 00` at file offset `0x1f6624`, giving `GP=00554170`. Both PT_MIPS_REGINFO and the `.reginfo` section reference this one stored record. It confirms the sequence word at `0054eb80`, process word at `0054eb88`, LightMa condition word at `0054eafc`, and established global-work pointer slot at `0054ea20`.

The twelve-byte `fldFlagState_PS2` view contains sequence flags at zero, an unknown four-byte gap, and process flags at eight. The twenty-four-byte `fldRuntimeFlags_PS2_prefix` at `002fbf80` exposes only the flags word at offset `0x14`. These are partial views, not complete object sizes. Ghidra preserves the unknown gaps; both saved field-layout readbacks have the expected extents and word offsets.

Seq/Proc On ORs the supplied mask; Off ANDs its complement; Check returns exact zero or one when any requested bit matches. Original Check uses a sign-extending LW, full 64-bit AND and SLTU. A raw uint32 argument therefore requires zero extension or consistent sign extension; arbitrary inconsistent upper register bits are outside the recovered C interface.

The existing four unknown bytes at global work offset `0xa4c` are the shared effect word for these leaves. C reads/writes their character representation with four-byte memcpy, avoiding an incompatible structure cast. Each effect mutator stores this word before reading and storing the separate runtime flags word. Physical field bindings remain distinct and stable.

| Effect family | Global-work bit | Cleared runtime bit | Start behavior |
|---|---:|---:|---|
| LightMa | `8` | `1` | No start routine in this batch |
| RifutoMa | `4` | `2` | Set global bit `4` |
| RiberaMa | `2` | `4` | Set global bit `2`, clear global bit `1` |
| EsutoMa | `1` | `8` | Set global bit `1`, clear global bit `2` |

Clear removes the indicated global bit; both Clear and Start remove the corresponding runtime bit. Other bits survive. RifutoMa does not clear the two competing bits. RiberaMa and EsutoMa Start combine their OR/AND into one original global store. The native port performs two managed stores for these starts.

LightMa Check returns `1` immediately when global bit eight is set, skipping the condition load. Otherwise every nonzero signed condition word returns `0`, including negative values; zero returns `-1`. The host condition proxy may be NULL only on the skipped-load branch. The other three checks return zero or one and change no captured state.

## RNG port difference

`sdfRandomize` takes a direct, four-byte-aligned sixteen-byte destination. NULL selects the existing four-word state at `00529bd8`. It reads no previous state and writes four words in order:

1. Seed XOR `0x0aed1a0c`.
2. Rotate the preceding value right eight bits.
3. XOR `0xaa5a02fe`, then rotate right eight bits.
4. XOR `0x11be81c7`, then rotate right eight bits.

The original shifts and stores discard seed bits above bit 31. The HD managed reference/writeback interface differs, its third stage omits the second XOR, and its final expression includes an unresolved protected global. The retained spelling and first-stage structure support the identity; equal PS2/HD random sequences are not claimed.

## Comparison coverage and limits

The frozen fixture generator has SHA-256 `45004827aa2e17ef4cf60fc49db2c86363485a428752d9b9599aa42c322e882e`; the host adapter has SHA-256 `aa472f9348a0b12ede95373e10dfa836036ec8c116c0d62f1c35b8ec10a99cac`. It supplies 7,828 cases: 592 seeding, 518 for each of six generic flag helpers, 1,568 LightMa checks and 256 for each remaining effect routine.

Seeding covers 74 edge/walking-bit/complement inputs and eight destination placements, including NULL, explicit default state, four aligned arena residues, work+A4C and runtime+8. Masks cover every bit and its complement against seven old-word patterns with both qualified extensions. Effect cases enumerate all sixteen low-bit combinations in both words, varied high bits, six enabled values, and 32 NULL-enabled short-circuit cases.

Every fixture compares all six complete storage spaces and four dedicated guard pairs, retaining the actual shared work/RNG allocations and checking all five bindings. Inputs are restored independently; expected bytes and results come from captured original calls. The generator restores every original space, guard and global slot in a finally block.

An independent actual-word interpreter plus the compiled C adapter passes the same 7,828 generated rows. Its separate access checks confirm ordered seed stores without old-state reads, the skipped LightMa condition load, and global-store-before-runtime-read ordering. `drafts/kernel_event_neighbors/fixture-adapter-check.json` records this development evidence; it is not additional canonical coverage or hardware validation. Disjoint ordinary-RAM value comparisons do not establish MMIO or physical access-trace behavior. Matching PS2 binaries and console execution remain unverified.

The ranked `dds3KernelCore$$dds3GetRandA` candidate at `001c0ad8` was rejected after reading its entire 221-instruction event-dispatch body and the native managed wrapper. The rejection is recorded in `rejected-matches.tsv`; sharing an RNG callee does not establish a wrapper identity.

The canonical subset report is `kernel-and-field-flags-validation.json`. At this checkpoint the complete vector SHA-256 is `5cc696cbd5d5e4685abb6452b64a5ec6a0e9ab75de564cbdf1632ecafcc6b11a`. The canonical C/header SHA-256 values are `a48ff3444d49d7a9204be1c870d00b151027500f1b69090b8885dbc808c1ab11` and `e89f19b290b9de25e1b7f22435f8fa82dc2488083b00e747c423180efea3526f`. The saved snapshot `backups/SLUS_209.11-2026-10-04-081407.gzf` has SHA-256 `47ec7cd661c275ba35141c38de0105f08051b83c48412fb78c657200e93d94f9`, including both partial field types. Its 33 library ABI checks pass, and fresh whole-program export decompiles all 8,935 recognized functions without a failed body.
