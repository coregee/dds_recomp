# Original material and morph motion recovery

Seventeen complete PS2 routines /1,652 recognized body bytes are now integrated.
Recovery reaches **1,787 /8,982 functions (19.895%)**, with 261,072 recognized
body bytes. The 130 focused reports contribute 296,387 cases; including the
earlier 462,684-case full run, the aggregate is 759,071. Existing captures were
reused for affected checks; this is not a new full-suite run.

## References and original behavior

Two named HD factory bodies are inspected in the current Unity corpus:
`sdfMotion$$sdfMotGenMatNode` at `1825EC220` returns null after initialization,
and `sdfMotion$$sdfMotGenMorphNode` aliases the zero-return body at `1811B9D90`.
Neither provides an algorithm counterpart, so all seventeen native routines
retain descriptive PS2 identities.

The community DDS [motion binding definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_motion_bindings.h)
and [motion implementation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfMotion.c)
at revision `bec33411543cdc487bad9debdf758f0090a2242c` clarify indexed material
bindings, direct text-parameter keys and captured slot pairs. These are reference
leads; original Nocturne instructions establish the implementation. Community
source is not copied, linked or executed. The [reference review](model-material-morph-matches.json)
retains source URLs, revision and content hashes.

| Original entries | Recovered behavior |
|---|---|
| `002B4C88`, `002B5998` | Minor factory dispatch using the low command halfword; raw operands forwarded to actual constructor targets |
| `002B4D10`, `002B4E70`, `002B4FD0`, `002B5130`, `002B5290` | Allocate 20-byte material bindings and select the original vtables |
| `002B57E8`, `002B58C0` | Allocate 36-byte direct primary/secondary text-parameter bindings |
| `002B5848`, `002B5880`, `002B5920`, `002B5958` | Find the actual key interval, then copy the first 20-byte key through existing material setters; blend weight is ignored |
| `002B59C8`, `002B5A20` | Select a contiguous 16-byte morph record and construct its 32-byte binding |
| `002B5A80`, `002B5B10` | Sample or blend two ID/weight influences, combining duplicate IDs and merging captured influences |

The actual ten material constructor slots and one morph slot execute recovered
bodies through the existing factory adapter. Material indices follow the
owner/resource pointer array; morph indices use a contiguous record stride.
Captured morph pairs occupy node offsets `10` and `18` hexadecimal.

Morph blending first scales the current key contributions by the incoming
blend weight. Each captured weight is scaled by its inverse and ignored at or
below the original threshold word `358637BD` at RAM `0054E748`. Matching IDs
accumulate weights; new IDs fill the second slot or replace the smaller influence
when their weight is greater. A remaining single influence clears the second
slot. Rates are unclamped, and target/captured fields reload in native order,
including the tested overlapping capture/target cases.

## Verification

- [Fresh original capture](model-material-morph/vectors.jsonl.capture.json):
  4,608 cases /550,074 original steps, with declared RAM writes checked and a
  clean capture log. The completed capture replaces the earlier test setup
  that omitted floating-register annotations on a cut-change prelude.
- [Canonical C comparison](model-material-morph-validation.json): all 349
  selected main instruction addresses reached; full declared RAM, defined
  returns, Status, callee saves, processor primitives and COP1 conditions agree.
- The cases execute 1,280 ordered factory/capture/bind callbacks and 192
  connected construction/cut-change pairs (384 actual prelude calls). Original
  factory and vtable bytes remain unchanged in all 4,608 cases.
- [Affected regressions](model-material-morph-regressions.json): another 3,584
  construction and 3,584 basic sampling cases pass on the same rebuilt host,
  with current input/source/verifier/DLL/vector hashes checked.
- [Saved ABI check](model-material-morph-abi.json): all seventeen interfaces
  pass after reopening the working project. The corrected export decompiles all
  seventeen and merges them into the 8,982-entry inventory with unsigned DIVU.
  Its temporary language fixup emits the known `rom0` block warning; the fresh
  export summary is complete with zero failed functions.

## SMT transfer and next dependencies

The [complete-span transfer report](model-material-morph-transfer.json) resolves
all seventeen DDS counterparts. Original major/minor slots and constructor-selected
vtables constrain duplicate shapes. The full morph blend differs only in its
independently matched key-search call and one GP-relative threshold load. Both
ELF REGINFO GP values and the byte-identical threshold at DDS `003BA610` are
checked. This establishes static correspondence, not DDS execution.

The [expanded motion frontier](model-motion-creation-frontier.json) has no pending
factory/callback roots among the inspected prefixes. Including the immediate
cut-change wrapper `002B3E70`, sample/blend dispatcher `002B3E90` and frame-update
body `002B3FB8` leaves three pending routines /568 recognized bytes and no missing
exports. The seven internal update-state targets are checked as labels owned by
the update body, without separate function credit.

Continue those actual control paths and retail motion-asset associations, then
remaining hit/model construction. Complete table extents, full executable
recovery, physical runtime and a matching executable remain outstanding. Source,
Ghidra interfaces and rolling outputs are updated in place without checkpoints.
