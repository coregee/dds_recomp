# PS2 stock compaction

`src/stock_compaction.c/.h` reconstructs `001ff0c8` as `ps2CompactStockUnits`. All 656 new original-instruction comparisons pass. The complete checkpoint is 167 compiled C functions and 110,205 comparisons. This is a chosen descriptive PS2 alias: no supported native HD counterpart was found.

The original body has 43 contiguous words (172 bytes), SHA-256 `4b95ed0293c6d75c3b092e5d24fde777ce79927029e5d559f83a16fee81feee1`. Independent reviews re-encoded every word and checked both dependencies, the 75-word custom-copy routine and seven-word clear routine. `drafts/stock_compaction/body-evidence.json` preserves the original bytes, instruction addresses and file hashes. The ELF SHA-256 remains `a26e86e59cab447d9b1839ec11ab82b1557230bcc99746b78e3b5d4359dcc6ff`.

## Recovered behavior

The routine scans an unsigned byte count of 236-byte records and selects records whose unsigned 16-bit ID at offset four is nonzero. It ignores the flag word when selecting a record. Selected records before the first hole remain completely untouched. A later selected record calls the original custom-copy helper to an earlier element, then clears its original source through the original full-unit clear helper. Moves preserve order; custom copy also recomputes resource limits, clamps HP/MP and sets flag one.

Pre-existing ID-zero tail records keep their unrelated bytes unless a move overwrites them. The routine does not blanket-clear the tail or repair the global ownership list/count. This differs from the already identified HD `cmpMisc$$cmpReplaceStockGBWK`, whose PS2 counterpart is `00240808` and whose flag predicate, copy operation and list handling are different.

Count zero permits NULL and reads no array. Other counts require that many complete, four-byte-aligned records with valid resource/skill backing for moved units. Tests with separately backed arrays through 255 elements establish the byte count and signedness, not a larger global stock capacity. Copies use distinct elements; arbitrary partial record overlap is outside the recovered interface. The return type is void because the original zero-count path does not define a meaningful result.

No direct caller appears in the current function index, executable J/JAL scan or literal pointer-word scan. This does not exclude indirect references or establish that the routine was unused. The HD search checked 10,924 native game bodies, including every indexed custom-copy caller and unit-array method, without a supported counterpart.

## Validation checkpoint

`StockCompactionVectors.java` covers all counts 0 through 255 at both supported alignment residues, plus eight hole/ID patterns at nine focus counts. There are 10 NULL zero-count cases, 270 cases without a move, 386 with moves, and two cases making 254 real copy-and-clear calls. Tests deliberately disagree flags and IDs. Every case compares the complete 64 KiB arena, guards, global work, RNG state, table hashes and actual shared bindings. No high-level copy or clear replacement supplies expected behavior.

The longest original execution took 609,611 instruction steps; its bounded harness allowance is 1,000,000. The canonical report `behavior-validation.json` records 656 passing compactor cases, source/verifier hashes and the complete vector SHA-256 `5ed2bfde337795971202202ead8825bf93c613e8732bd2001ebc1b7bfdd99253` at this checkpoint. The separate 4,096-case original-word draft probe and 656-case Java/C fixture development checks are outside the canonical total. These are isolated instruction-model comparisons; matching PS2 binaries and hardware execution remain unverified.

Canonical source hashes at this checkpoint: C `ac4afef4a3f71761b573d52b199d3e375e4fbee5b7404c15a087699017cfc743`, header `4d50b250644274840dae533a5c1dbe811659c38955928c3e6cbac6c9ff0e8e74`. Fixture SHA-256 is `c67626e80a8bed136e0a0b83a426bff461b6504aa536883c0fd76a0959480800`; adapter SHA-256 is `9701da741175562b9d742e8a21537c5562d611029991d86fde7c27c7cc35545f`.

The saved snapshot `backups/SLUS_209.11-2026-10-03-215024.gzf`, SHA-256 `c4465e118cd7bec9cac54c038a3237c94c8e62cc49918cb08c610c88d57070c0`, contains 174 reviewed HD mappings, 33 independent SDK/library identities and three chosen PS2 game aliases. All 33 saved library register ABI checks pass. Fresh whole-program export decompiles all 8,935 recognized functions without a failed body.
