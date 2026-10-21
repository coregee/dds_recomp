# Material definitions, lifetime and handle pointers

This document records the historical 332-function checkpoint. [Current recovery](memory-array-lists-findings.md) is345 functions and443,420 fresh comparisons. Its original publication is preserved in the 332 archive.

Historical verified checkpoint: **332 / 8,954 recognized functions (3.71%)**, **421,404 completely fresh original-instruction cases**, 36,356 summed original body bytes, 254 reviewed HD counterparts, 46 identified library routines, 75 descriptive PS2 aliases and 88 transfer patterns. Saved project: `ghidra/checkpoints/332-functions/Nocturne.gpr`. Full or near-full recovery remains unfinished.

This batch adds **six reconstructed routines**, **688 original function bytes** and **16,896 focused original/C comparisons**. Their contiguous reviewed spans total 692 bytes; material release contains one excluded unreachable 4-byte NOP. No function boundary or HD identity is added.

Recovered source: `src/material_lists.c/.h`. [Batch certificate](checkpoints/332-functions/inputs/analysis/material-lists-validation.json), [complete regression](checkpoints/332-functions/behavior-validation.json) and [checkpoint integrity](checkpoints/332-functions/inputs/analysis/checkpoint-332-integrity.json) pin the evidence. The saved project is `ghidra/checkpoints/332-functions/Nocturne.gpr`.

| PS2 entry | Recovered C function | Function bytes | Focused cases |
|---|---|---:|---:|
| `002b32e8` | `ps2MatReadDefinition` | 460 | 4,096 |
| `002b34b8` | `ps2MatRelease` | 100 | 512 |
| `002b3558` | `ps2MatWritePacketHeader` | 60 | 4,096 |
| `002b37b8` | `ps2MatCopyScalars40And44` | 20 | 4,096 |
| `002a9688` | `ps2MemoryHandleAcquirePointer` | 20 | 2,048 |
| `002a96a0` | `ps2MemoryHandleReleasePointer` | 28 | 2,048 |

## Recovered behavior

The definition reader copies word 0 and halfword 4 into the material before loading flags at definition+6. It processes eleven optional fields in ascending bit order: ambient, diffuse, texture, five-word record 38, word 18, texture plus word 34, five-word record 3C, specular, word 28, a constant raw float word and the scalar pair 40/44. Payload lengths are 4/4/4/20/4/4/20/4/4/4/8 bytes, at most 80 bytes. Texture indexes use the low 16 bits of the packed word; the second texture field takes word 34 from its high 16 bits. Higher flag bits are ignored. The returned cursor reflects consumed fields.

The reader retains real setters and lazy getters. Each five-word float input is loaded before the setter call; subsequent texture-array reads occur after prior writes. Focused cases cover all 2,048 low-flag combinations, existing/lazy scalar records, high flags and selected material/definition/record aliases. There is no initial snapshot of the whole definition.

Immediate material release accepts NULL, loads the counter and first packet pointer before decrementing the wrapping counter, frees packet 8, then rereads packet C and optional records 38/3C after earlier releases, and finally frees the material itself. Capture executes the real recovered pool-free logic over active/available/full/empty page fixtures, duplicate slots, counter edges and both initial interrupt states.

The packet-header writer stores byte 3 = 0x30 before reading commands+(index<<2)+8, writes tag halfword 0 = 10, masks the command with 0x0fffffff, zeroes words 8/C and returns output+16. Aliases expose the first-store-before-load ordering. The scalar transport performs raw word 40 → output 28, then word 44 → output 2C, preserving sequential overlap behavior and float bit patterns.

Handle acquisition loads unsigned count E and pointer 8, increments the wrapping 16-bit count and returns the previously loaded pointer. Release returns the old unsigned count, decrements only when nonzero and performs no store at zero. Focused count cases include 0, 1, 0x7fff, 0x8000, 0xfffe and 0xffff.

## Unity leads and transfer

The native HD list new/add/make methods provide structural leads for callers. List make retains capacity threshold 32, material construction, definition reading, append and cursor advance. PS2 receives the count through the first packed word, while HD receives a separate argument and uses managed arrays. The native HD sdfMatSet output does not retain the eleven-field parser; no direct HD counterpart is promoted for these six routines.

Four new transfer patterns cover the packed definition reader, material owner release sequence, packet/scalar transport and handle reference words. The ledger now has 88 reviewed patterns. Six relocation-masked draft search signatures retain constants while masking branch/JAL relocation fields; they remain search aids, with no established DDS or other SMT-game matches.

## Verification and preservation

The six-body standalone run compares return values, five RAM spans totaling 20,864 bytes, 320 canary bytes, Status and primitive-call counts. Original saved registers, GP/SP/RA and zero are checked. Owner buffers, host bindings, Status and counters restore after success, rejection and injected mismatch checks. Eleven malformed standalone rows and four malformed canonical rows are rejected. The accepted focused capture has no uninitialized-memory warnings.

All 332 canonical C functions compile and pass 421,404 completely fresh original-instruction rows. Capture pins 181 inputs before and after execution; source validation pins 79 source and 85 verifier files. All 16 audited language files remain pinned. The prior shared-counter regression is resolved to the exact archived 326 exporter, preserving its original decoded-instruction callback evidence.

Saved Ghidra checks verify the six original bodies, custom A0..A2/V0 raw32 storage and five new partial accessed views. Ten prior ABI groups also reopen successfully. All 8,954 recognized functions export and decompile with zero failures. The exact 326 checkpoint remains preserved: 400 artifacts, 160 certified source/verifier inputs, 177 capture inputs and 404,508 original rows. Earlier 305/285 archives and the invalid initial available-page fixture remain intact.

[The next frontier](material-lists-next-frontier.md) continues through descriptor unlink/free, handle allocation/reallocation, generic arrays and the named Unity material-list callers. Full/near-full source, remaining code discovery, data reconstruction, original kernel behavior, runtime, IRQ timing, privileged exceptions, allocation failure, private callee stack and matching binaries remain unproved.
