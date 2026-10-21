# Compendium recovery

Five reviewed native counterparts establish a PS2 compendium module: `fclEncycRegist` at `0x00216A18`, Search at `0x00216B20`, GetNum at `0x00216B78`, GetRatio2 at `0x00216B90`, and SetElem at `0x00219DF0`. The canonical ledger includes their HD addresses and differences. The C name `fclEncyc_SetElem` qualifies HD's generic `SetElem` name; exact PS2 source spelling is inferred.

## Record layout

SetElem clears `0xB0` bytes then copies these ranges from the `0xEC`-byte unit. Bulk loads/stores prove the fixed copy lengths independently of HD array declarations. HD native SetElem supplies the corresponding field names, managed-array element copies, scalar transfers and flag mask.

| Field | Unit offset | Record offset | Copied bytes |
|---|---:|---:|---:|
| ID | `0x04` | `0x00` | 2 |
| Maximum HP / MP | `0x08` / `0x0C` | `0x04` / `0x06` | 2 each |
| Experience / level | `0x10` / `0x14` | `0x08` / `0x0C` | 4 / 2 |
| Base / skill parameters | `0x16` / `0x1C` | `0x0E` / `0x14` | 6 each |
| Skill count / skill IDs | `0x38` / `0x3A` | `0x1A` / `0x1C` | 2 / 48 |
| Mitama / level-up parameters | `0x7A` / `0x80` | `0x4C` / `0x52` | 6 each |
| Inherited skills | `0x86` | `0x58` | 48 |
| Inheritance attributes | `0xB6` | `0x88` | 24 |
| Pre-transformation ID | `0xCE` | `0xA0` | 2 |
| Flags masked with `0x240` | `0x00` | `0xA4` | 4 |
| Pre-transformation experience | `0xD8` | `0xAC` | 4 |

Reserved bytes at `0x02..03`, `0xA2..A3` and `0xA8..AB` remain zero. Current HP/MP, unique ID and unrelated unit state are not transferred. HD unit skill elements are wider and narrowed during SetElem; copying a managed object representation would be incorrect.

## Registry behavior

Global work stores its signed count at `0x11E80` and 184 records at `0x11E90`. Search compares each zero-extended 16-bit record ID against the supplied integer and returns the first matching index or -1. It does not truncate a wider supplied ID. GetNum directly loads the count.

PS2 GetRatio2 computes signed `(count * 100) / 184` with 32-bit wrapping multiplication. Positive count with a result below one returns one. HD replaces this calculation with descriptor filtering, dictionary deduplication and a cached count; a reviewed counterpart does not imply identical code.

Registration searches `unit->id`, appends a new record and increments count, or replaces an existing record only when `overwrite != 0`. Its return is 0 for a new record, 1 for an overwrite, and -1 for a rejected duplicate or full registry. After a successful SetElem, it sets completion event `0x913` when the PS2 ratio reaches 100 and clears it otherwise. The original instructions establish SetElem's second argument at `0x00216A5C`; correcting the prototype restores that omitted parameter in decompiled callers.

HD adds an `update` parameter, DLC ID remapping, dynamic capacity, managed storage and cache invalidation. These features are absent from the PS2 routine.

## Validation

Each of the five routines has 100 comparisons against isolated execution of the original PS2 instructions. Cases cover random source fields, zeroed reserved bytes, all 24 copied elements, first-match and wider-ID searches, count boundaries, signed/wrapping ratio cases, new registration, overwrite rejection, completion transitions and full-record failure. Unit bytes, a separate destination record and the complete `0x19D10` global-work view are compared before and after; unknown gaps remain covered.

On full-registry failure, external printf at `0x002D4748` is bound to a message-capture callback and compared with the C binding. The actual platform formatter is not executed. The second diagnostic callee at `0x001097E8` executes its original vararg-spill prologue and returns without an output body. Console output, hardware execution and matching compilation remain unvalidated.

The remaining compendium operations, save/load representation, registration callers and menu behavior still require recovery. The record-copy pattern is a candidate for other SMT PS2 games; no shared offset or capacity is assumed.
