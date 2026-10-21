# SDK case comparison, float signs and range records

Six PS2 library/runtime leaves are recovered in `src/ps2_sdk_neighbors.c/.h`.
All 7,853 new original-instruction cases pass. Names are behavioral aliases;
no HD counterpart, historical compiler name or library version is asserted.
All 120 complete original words / 480 bytes independently match the ELF.
Primary body/caller/artifact hashes are in `drafts/next_sdk_neighbors/body-evidence.json`.

| PS2 entry | Recovered interface | Canonical cases |
|---|---|---:|
| `002d5720` | `ps2Strcasecmp` | 3,072 |
| `002d11c0` | `ps2AbsFloat`, F12=>F0 | 683 |
| `002d1388` | `ps2CopySignFloat`, F12/F13=>F0 | 1,249 |
| `002d2728` | `ps2CountRuntimeRangeRecords` | 451 |
| `002d27f8` | `ps2FindRuntimeRangeRecord` | 2,319 |
| `002e6e30` | `ps2GetRuntimeState` | 79 |

## Exact original interfaces

Case comparison uses signed LB bytes in its equality loop and unsigned LBU
bytes in its final difference. Class bit0 adds32 without truncating the folded
value to a byte. The loop can index-128..127, while the final path indexes0..255.
The fixed class base `0054b551` therefore needs the entire 384-byte backing
at `0054b4d1..0054b650`, not zero padding for negative indexes. Preceding
bytes include original adjacent pointer data. The canonical capture is
`ps2/sdk-character-class-bytes.bin`, SHA256
`4dcaf9dc35bafa1513667b60ab1f06e1f979567dbd9a15da96580919b1772806`;
the host class binding points128 bytes into it. No host locale folding is used.
Original callers compare filename suffixes after the recovered Strrchr leaf.

Abs clears only sign bit31; CopySign combines F12 magnitude with F13 sign.
Both return raw F0 encodings and use private sixteen-byte PS2 stack frames.
No floating arithmetic or FCSR access occurs. C uses memcpy bit transport;
two uint32 test adapters call the actual recovered float functions, preventing
Python float conversion from quieting or canonicalizing payloads. Signed zeros,
subnormals and exponent255 encodings retain every other bit.

Range chains begin with a four-byte-aligned length word. Length0 terminates.
Nonzero length reads discriminator+4; nonzero discriminator reads start+8;
Find reads size+12 only for nonzero start. Count increments for those nonzero
starts and never reads+12. Each next record advances by low32(length+4),
represented as a signed displacement within one backed object. Finite backward
chains are supported. Find returns the first record satisfying
`low32(query-start) < unsigned_size`, or NULL. Consistent LW/SUBU sign extension
on both SLTU operands preserves that unsigned32 ordering, including ranges
crossing zero. No format/compiler/unwind identity is inferred from these fields.

The getter loads the original32-bit pointer slot `0052be28` once, in its JR
delay slot, and never dereferences the target. The stored original pointer is
`0052bb38`; its tested64-byte backing is a synthetic context, not a recovered
runtime-object size. NULL, aliases and one-past results remain valid getter
values because no target access occurs.

## Validation and limits

The generator captures original results and all bytes/guards for the 4096-byte
arena, exact 384-byte classifier and 64-byte synthetic runtime prefix. The host
adapter compares those three complete spaces, all three guard pairs, class
binding integrity and the normalized runtime slot/returned pointers. It saves
and restores the backings and slot after every call. Float inputs/outputs travel
as raw words in F12/F13/F0 through the original instruction path.

Cases cover every byte against varied partners, folded equal pairs and shared
strings, all string alignments, filename suffixes, nonterminated right backing
on the short left-NUL path, raw float edges/walks, first-match/conditional record
paths, signed/unsigned range boundaries, finite backward chains, and NULL/alias/
one-past getter results. Full-sized arena/guard capture exposes unintended writes.
Private float stack accesses are reviewed and checked by the separate word
model; they are not public host stack snapshots or hardware validation.

The separate 104,675 original-word probes and 7,853 fixture-adapter smoke rows
are development model checks, outside the canonical count. The whole checkpoint
is 202 compiled C functions /131,262 original-instruction comparisons. Its saved
PS2 snapshot passes all 39 library register ABI checks, including F13 for CopySign.
`sdk-case-float-and-ranges-validation.json` retains source/verifier/vector hashes.

Ordinary stable backed little-endian RAM, finite aligned record chains and
enough backing for every byte actually read are required. Strings may alias
and have arbitrary byte alignment. There is no fabricated NULL/malformed-chain
fallback. Address-space wrapping outside the backed representation, MMIO,
concurrency, bus atomicity, FCSR effects, PS2 runtime and matching binaries
remain outside this host comparison.

Complete fixture SHA256: `f2dae8c5c8c1ffc32376edfd7b2bf98ce54999b451408b229648c765be534d39`.
Saved snapshot: `backups/SLUS_209.11-2026-10-04-085044.gzf`, SHA256 `0e9d60810475fe03e3641cbd5a504abed201affb6dd824990335f12eff2dd1f8`.
