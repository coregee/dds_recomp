Current verified checkpoint: **413 functions /462684 fresh original-instruction cases**. [Findings](texture-environment-findings.md) · [Next frontier](texture-environment-next-frontier.md). Earlier checkpoint narratives below are retained as historical records.

Historical checkpoint document: its batch counts and unresolved states describe the earlier checkpoint. Current evidence is linked above.

Current verified checkpoint:364 recovered functions /449,372 fresh original-instruction cases. See [heap and queue findings](heap-queue-findings.md), [current certificate](heap-queue-validation.json) and [next frontier](heap-queue-next-frontier.md). This document retains historical345 results.

# Memory handles, generic arrays and material lists

Current verified checkpoint: **345 / 8,954 recognized functions (3.85%)**, **443,420 completely fresh original-instruction cases**, 38,160 summed original body bytes, 254 reviewed HD counterparts, 46 identified library routines, 88 descriptive PS2 aliases and 92 transfer patterns. Saved project: `ghidra/checkpoints/345-functions/Nocturne.gpr`. Full or near-full recovery remains unfinished.

This batch adds **13 reconstructed routines**, **1,804 original function bytes** and **22,016 focused original/C cases**. Contiguous spans total 1,828 bytes; six unreachable 4-byte NOPs are excluded. The recognized inventory and reviewed HD pair count are unchanged.

Recovered source: `src/memory_handle_allocation.c/.h`, `src/memory_handle_unlink.c/.h` and `src/array_lists.c/.h`. [Batch certificate](memory-array-lists-validation.json), [complete regression](behavior-validation.json) and [checkpoint integrity](checkpoint-345-integrity.json) pin the evidence.

| PS2 entry | Recovered function | Function bytes | Focused cases |
|---|---|---:|---:|
| `002a9038` | `ps2MemoryHandleAllocate` | 284 | 2,048 |
| `002a9390` | `ps2MemoryHandleReallocate` | 428 | 2,048 |
| `002a9540` | `ps2MemoryHandleUnlinkNext` | 20 | 4,096 |
| `002a9558` | `ps2MemoryHandleFree` | 160 | 2,048 |
| `002bfe58` | `ps2ArrayCreate` | 140 | 1,024 |
| `002bfee8` | `ps2ArrayFree` | 44 | 1,024 |
| `002bff18` | `ps2ArrayGrow` | 124 | 2,048 |
| `002bff98` | `ps2ArrayResize` | 192 | 2,048 |
| `002b2d28` | `ps2MatListCreate` | 28 | 1,024 |
| `002b2d48` | `ps2MatListFreeMaterials` | 100 | 1,024 |
| `002b2df8` | `ps2MatListGrow` | 20 | 1,024 |
| `002b2e10` | `ps2MatListAppend` | 104 | 2,048 |
| `002b38a0` | `ps2MatListMake` | 160 | 512 |

## Recovered behavior

Allocation wraps requested size+127 and masks to128-byte granularity. It disables interrupts, scans linked16-byte descriptors, compares gaps as signed32 values and splits through the actual pool allocator. A state-2 descriptor conditionally restores interrupts before reading/calling the pressure callback, then resumes its scan. The callback fixture executes the actual already recovered empty002b58b8 body. Unlink captures both links before writing next.prev and handle.next. Free captures the next descriptor first, merges a free next through real unlink/pool release, rereads the live previous descriptor, then either coalesces it or clears state/held count. Interrupt restoration depends on entry state.

Reallocation preserves the caller-visible descriptor address. Equal rounded extent returns immediately. Expansion into a free next either unlinks/frees it exactly or moves its data boundary. Other expansion allocates a real temporary handle, copies through the actual recovered memcpy, exchanges descriptor links/data, repairs four live neighboring links and frees the temporary handle. Shrink moves the free-next boundary or creates a real free descriptor before a used next. Held-pointer counts retain original descriptor ownership. Selected unaligned source/destination copies run through the real copy body.

Generic arrays use16-byte headers: raw32 handle0/dataC and count4/capacity6/stride8/growthA halfwords. Create multiplies full32 numeric inputs while storing wrapping halfword fields. Existing growth releases its pointer, sums unsigned halfwords then truncates to signed16, uses the signed stride product, reallocates and reacquires. Resize distinguishes absent and existing handles, signed nonpositive requests, real free/reallocation, live count reads and conditional count trimming. These policies differ from managed HD arrays.

Material-list creation fixes stride4/growth8. Append compares signed count/capacity, grows if necessary, rereads unsigned count and data, converts the index to signed16, stores the incremented count before writing the material slot. Aliases into the array header expose this ordering. Make reads an unsigned count from the first packed definition word, uses capacity max(count,32), then executes real material create → definition reader → append while advancing the returned cursor. Immediate free rereads list data/count after each real material release, then frees the array. Deferred queue release remains separate.

## Unity reference and SMT transfer

The named HD new/add/make methods provided the capacity32 and construction/reader/append loop that led into these original callers. PS2 obtains count from a packed word; HD receives a separate argument and uses managed storage. These structural references remain distinct from reviewed exact symbol identities. The native HD definition reader does not retain all eleven PS2 fields.

Four new fingerprints record extent allocation/coalescing, stable-address relocation, signed generic-array policy and material-list construction/lifetime. The transfer ledger contains 92 patterns. Applying them to DDS or another SMT PS2 game requires independently checking descriptor/header offsets, constants, call ordering and platform dependencies; no cross-game match is asserted.

The [expanded native reference review](drafts/memory_handles/closure-unity-review.json) records nine named HD leads. Material-list grow maps to an empty return body at 1810d6760 shared by 701 methods; it cannot supply original PS2 growth behavior. HD pointer accessor1825e6330 omits the wrapping held count. Model-node grow/set-capacity constructs managed elements rather than preserving raw data through original handle relocation.

A [read-only DDS scan and caller review](drafts/memory_handles/closure-transfer-review.json) corroborates static candidates for all thirteen routines. Ten complete relocation-masked bodies have a unique loaded-segment hit. Exact original maker/free/append instruction sites select the three ambiguous bodies; all relative branch words and absolute callee correspondences remain consistent. This is concrete shared-code evidence. DDS global ownership, function boundaries and behavior still require independent validation; its project and source remain unchanged.

## Verification and preservation

All 345 compiled canonical functions pass443,420 completely fresh original-instruction cases. No previous expected rows are reused. Capture freezes189 inputs before and after execution; the source report pins85 C/header and87 verifier files. The focused13-body suite compares eight RAM spans totaling 63,876 bytes,512 canary bytes, raw returns, Status, four primitive counters and actual pressure-callback counts. Original saved registers, GP/SP/RA and zero are checked. Owners, bindings, Status and counters restore after success, malformed rejection and an injected mismatch. Ten malformed rows are rejected in both standalone and actual canonical-export adapters.

Every selected path exercises both initial interrupt states. The earlier complete run agreed on all original/C rows but correlated allocation path8 with one IRQ choice; it is preserved as diagnostic evidence. The first IRQ-correlated passing run and the too-small large-growth fixture are also retained. All 22,016 final focused rows were recaptured after correcting fixture coverage; none were reused.

The isolated345 Ghidra project preserves the 332 project. Thirteen byte-gated custom low32 A0..A2/V0 interfaces and eleven earlier ABI groups pass independent read-only reopen. Signed32 numeric parameter types and existing partial accessed views are retained. All 8,954 recognized functions export/decompile with zero failures. Exact332 history retains 899 artifacts,164 certified source/verifier inputs,181 capture inputs and421,404 original rows. The326/305/285 archives remain preserved.

[The next frontier](memory-array-lists-next-frontier.md) covers initialization, deferred lifetime and allocator callers. Full/near-full source, complete code/data discovery, arbitrary callbacks, allocation failure, hardware/kernel timing and exceptions, runtime, private callee stack and a matching executable remain unfinished.

## Corroborated DDS static candidates

| Nocturne entry | DDS candidate | Recovered Nocturne role |
|---|---|---|
| `002a9038` | `002d03f8` | `ps2MemoryHandleAllocate` |
| `002a9390` | `002d0750` | `ps2MemoryHandleReallocate` |
| `002a9540` | `002d0900` | `ps2MemoryHandleUnlinkNext` |
| `002a9558` | `002d0918` | `ps2MemoryHandleFree` |
| `002bfe58` | `002e75f0` | `ps2ArrayCreate` |
| `002bfee8` | `002e7680` | `ps2ArrayFree` |
| `002bff18` | `002e76b0` | `ps2ArrayGrow` |
| `002bff98` | `002e7730` | `ps2ArrayResize` |
| `002b2d28` | `002da270` | `ps2MatListCreate` |
| `002b2d48` | `002da290` | `ps2MatListFreeMaterials` |
| `002b2df8` | `002da340` | `ps2MatListGrow` |
| `002b2e10` | `002da358` | `ps2MatListAppend` |
| `002b38a0` | `002daee8` | `ps2MatListMake` |
