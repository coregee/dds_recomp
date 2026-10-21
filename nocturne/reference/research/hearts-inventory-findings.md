# Items, Magatama ownership and learned skills

Seven additional PS2/Unity counterparts connect nine recovered C routines in `src/hearts_inventory.c`. The two existing `datCalc` matches are now implemented as well. Names come from the reviewed HD methods, with PS2 layouts and behavior checked separately against instructions.

| PS2 entry | HD method | Original-instruction cases |
|---|---|---:|
| `0x002138C0` | `fclMisc.fclChkItemHearts` | 1,000 |
| `0x00213938` | `fclMisc.fclAddItem` | 200 |
| `0x002442E0` | `datCalc.datAddItem` | 600 |
| `0x002452C8` | `datCalc.datAddHearts` | 200 |
| `0x002328C8` | `cmpInitDH.cmpChkHaveHearts` | 256 |
| `0x00232880` | `cmpInitDH.cmpChkHaveNormalHeartsAll` | 100 |
| `0x002221D0` | `rstCalcCore.cmbGetHeartsAfterSkillNums` | 256 |
| `0x002224D8` | `rstCalcCore.cmbAddHeartsSkill` | 192 |
| `0x00222550` | `rstCalcCore.cmbCreateDefaultHeartsSkill` | 768 |

## Mapping and acquisition

`0x002138C0` masks the incoming ID to 16 bits, checks whether unsigned16 `ID - 0x40` is below 25, and reads a signed byte from a table copied from `0x0053D6E8`. The original bytes are 1 through 25: item IDs `0x40..0x58` map to Magatama IDs 1 through 25. The apparent uninitialized-array access in old pseudocode was misleading: the actual `LB` address is `SP + ID - 0x40`, inside the 25-byte copied table for the accepted range.

`0x00213938` dispatches mapped IDs to `datAddHearts`, otherwise calls `datAddItem(ID, quantity)`, and returns 1 unconditionally. This matches the HD `fclAddItem` call sequence and arguments. Duplicate Magatama acquisition and quantity zero still return 1 from this wrapper.

`datAddItem` dispatches Magatama IDs before normal item handling. Other IDs below `0x70` update the inventory byte at global `+0x1928 + ID`, using a wrapping signed32 sum clamped to 0..99. Quest IDs set event bit `ID + 0x360` regardless of quantity. ID `0x8D` additionally updates its quantity byte; negative depletion clears event bit `0x3ED`. Quantity zero sets ownership while preserving quantity. Positive signed overflow in this special-item branch follows the original signed comparison and low-byte store, rather than a mathematical saturating add.

## Confirmed global fields

The global pointer is read through `GP - 0x5750`, corresponding to RAM slot `0x0054EA20` with the established GP value.

| Global offset | Storage / observed use |
|---|---|
| `+0x1CFB` | Ownership byte list |
| `+0x1D3B` | Per-ID skill state byte; count accessor masks low nibble |
| `+0x1D7B` | Unsigned ownership count byte |
| `+0x11AC0 + ID*24` | Learned ushort skills, 12-slot stride per ID |

The 64-byte spans between ownership, state and count fields describe physical storage; they do not establish a logical capacity of 64 Magatama. The source view exposes 26 learned-skill rows for tested IDs 0..25, retaining the remaining bytes as unknown. These are additions to the partial global view, whose overall extent remains `0x19D10`.

`datAddHearts` compares existing ownership bytes with the full signed32 ID. A new acquisition appends the low byte, increments the byte count, and clears the entire skill-state byte for that ID. It then checks ownership of every normal ID 1..24 and sets event `0x860` when all are owned; ID 25 is excluded from that check. Finally it creates default skills for the first party unit at global `+0xA54`. Duplicate acquisition returns 0 without those updates.

## Learned and default skills

`cmbAddHeartsSkill` reads the state's low nibble, stores the ushort skill at `+0x11AC0 + 2*(ID*12 + count)`, and increments the entire state byte. Later connected accessors prove bit7 is mastery; bits4..6 remain unclassified. The source preserves the original whole-byte increment. No new capacity checks are introduced.

`cmbCreateDefaultHeartsSkill` examines eight four-byte entries at `0x00339E1A + ID*66`. Each entry has a level byte at `+0` and skill ushort at `+2`. Only nonzero skills with level zero are appended to the unit's inline skill list, followed by the same per-Magatama append helper. It returns the signed low byte of the unit's ushort skill count. ID zero returns zero without modifying the unit.

The 66-byte row in `nocturne.h` is a view beginning at a record's first level byte, not a claim that the complete descriptor has been recovered. Its unknown tail keeps the original stride. HD uses managed arrays and a wider unit count; its default-skill method additionally contains protected DLC-event gates absent from the PS2 instructions.

The shipped 26-row backing span contains no level-zero nonzero skills. Validation therefore includes 512 synthetic row variants inside the isolated emulator, exercising all 256 level-selection masks and all 256 zero-skill masks. They compare execution of the original instructions with the same C input table, including high-bit skill IDs, unit writes, per-ID writes and untouched bytes. The other 256 default-skill cases use shipped data. The executable, ISO and Steam files remain unchanged.

The acquisition comparisons also include synthetic default skills through all three grant paths, with the party unit inside global work, completion event initially clear and duplicate cases. This closes the connected-path gap identified by the earlier 56,632-case source audit. The row view and descriptor now share a single host backing buffer; see `hearts-parameters-findings.md` for the partial descriptor and mastered parameters.

All nine routines pass 3,572 comparisons. Ownership queries cover every signed8 input; count queries cover all 256 state-byte values; append cases cover all upper-nibble states with valid free slots. Full global-work buffers, the separate unit buffer, RNG state and auxiliary globals are compared. IDs, capacities and unit skill counts follow valid caller contracts; these tests do not establish behavior for malformed indexes or exhausted arrays. They are instruction-model comparisons, not console execution or binary matching.

## Review queue correction and transfer

The matcher had ranked `0x00213938` as `cmpTest.cmpDbgItem` at score 0.9422 because both reach `datAddItem`. The HD debug function has cursor state, rendering, input and formatted strings; the PS2 function is a 23-instruction grant wrapper. Direct call and return review established `fclAddItem` instead. `rejected-matches.tsv` retains this rejection and a second gift-updater/debug-menu mismatch; the queue excludes them without applying other candidate names.

These layouts and small algorithms are transfer candidates for related SMT PS2 games. Recheck the table mapping, ID range, list/state offsets, descriptor stride, skill limits, completion event and any DLC/version differences in each executable.
