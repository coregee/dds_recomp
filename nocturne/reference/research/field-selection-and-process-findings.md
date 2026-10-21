# Field selection and process checks

Eleven connected routines are recovered in `src/field_neighbors.c/.h`, with
reviewed native HD counterparts in `function-matches.tsv`. All 5,376 new
original-instruction cases pass. The complete checkpoint is 202 compiled C
functions and 131,262 cases, with 203 reviewed HD counterparts, 39 separately
identified PS2 library routines and three chosen PS2 game aliases.

Complete original/native artifacts, caller sets and hashes are retained in
`drafts/next_field_batch/body-evidence.json`. The independent encoder checked
all 219 listed instructions; complete spans contain 221 words / 884 bytes.
Two omitted ELF NOPs at `00123984` and `0012426c` remain in the span hashes.
Source and fixture peer reviews found no discrepancy under the stated contracts.

| PS2 entry | Recovered routine | Native HD entry |
|---|---|---|
| `001233f0` | `fldLightMaIdxCalc` | `1820512b0` |
| `001236a0` / `00123760` / `00123828` | Rifuto / Ribera / Esuto `ClearMsg` | `182056420` / `1820560d0` / `18204fb70` |
| `001238f0` / `00123970` / `00123a10` | Anahori `SelectInit` / `SelectGet` / `SelectNext` | `18204f5d0` / `18204f250` / `18204f8e0` |
| `0022cf08` | `cmpChkCampProcess` | `1822e53f0` |
| `00124240` | `fldProcCampChk` | `1821fff90` |
| `00149288` | `fldAutoMapChkMode` | `18200bee0` |
| `00124508` | `fldProcAmChk` | `1821ffeb0` |

## Original storage and behavior

The primary ELF GP word confirms `GP=00554170`. New partial views are eight
bytes at `0054eb48` (signed selection index and eligible count) and eight bytes
at `0054eb68` (signed camp and automap waits). The consuming camp byte is
`0054fdd4`; the signed automap mode word is `0054ee60`. Bindings are host
adaptations, and these extents are not complete object sizes. Work, RNG, flags,
runtime and LightMa retain their existing backing. Runtime words +4/+8 are
read through character representation, leaving the existing unknown fields explicit.

LightMa index calculation reads full signed field/area words and returns
100/101/102. Field `15` selects 100 for area2, 101 for area17, otherwise102.
Field `1a` selects101 for areas12/13/15, otherwise102. Field `1d` selects100
for area1, 101 for areas9/a, otherwise102. Other fields return100, including
the redundant field25/areaF branch. Numeric meanings remain unassigned.

Each ClearMsg gates on global-work+A4C bit4/2/1, executes the real recovered
Clear, then reloads runtime flags and sets bit2/4/8. An absent global bit skips
runtime entirely. Original global-store-before-runtime operations remain in
the source; expected results do not use a collapsed update formula. Native
Rifuto protected bookkeeping and Ribera's extra byte AND46 are port differences.

Anahori scans exactly sixteen inline 236-byte units at work+A54. Eligibility
requires flag1, excludes flags4/10/800, and requires nonzero unsigned HP at+6.
ID0, duplicates, capacity, stock-list count and list bytes do not gate eligibility.
Init clears index then count, computes locally and finally stores count0..16.
Get uses stored count only as a zero/nonzero gate, then selects the requested
eligible ordinal through the fixed scan; IDs return as unsigned ushort values,
and missing ordinals return0. Negative/stale counts do not change the scan bound.
Next wraps the 32-bit increment before its signed comparison, with one final
index write. Native Init/Next use different intermediate store patterns.

The camp leaf returns1 for byte1, resets byte2 to0 and otherwise returns0
without a write. CampChk prioritizes positive wait=>2, camp result1=>1,
process flag20 present=>0, absent=>3. Byte2 is consumed before checking flags.
AmChk returns2 for a positive wait; otherwise it Booleanizes the real mode
getter. The getter itself returns the entire signed word, including negatives.

## Validation and next dependencies

The field generator captures expected values only by executing original ELF
instructions. It contributes512 cases per routine except the camp leaf's256
byte patterns. Coverage includes full-word selector values, every physical
unit slot, rejecting flags/HP edges, zero/duplicate/high IDs, stale signed
index/count values, wrap boundaries and eight real Init/Get/Next/re-Init
sequences. There are 849 allowed NULL-proxy rows on branches that skip a binding.

Every call compares all nine complete storage spaces, seven guard pairs,
the global-work slot and nine host bindings. Guards overlapping other guard
intervals are recaptured after all initialization writes. The adapter retains
the actual shared kernel owner/data addresses and restores all bytes/bindings
in finally blocks. Separate infrastructure and bounded word-model checks are
development evidence; they add no canonical cases.

`field-selection-and-process-validation.json` records this subset and the
complete checkpoint hashes. The saved snapshot passes 39 library ABI checks;
the fresh raw export decompiles all 8,935 recognized functions. Ordinary stable
distinct RAM is the declared scope; MMIO, concurrent writes, bus access traces,
PS2 execution and matching binaries remain unverified.

`drafts/next_field_batch/frontier-notes.md` keeps the protected LightMa ClearMsg,
large process state machine and VU encounter check outside this batch. Selection
deletion and its script wrapper are being recovered separately through real
event-bit and stock-removal dependencies, with their distinct return behavior.

Complete fixture SHA256: `f2dae8c5c8c1ffc32376edfd7b2bf98ce54999b451408b229648c765be534d39`.
Saved snapshot: `backups/SLUS_209.11-2026-10-04-085044.gzf`, SHA256 `0e9d60810475fe03e3641cbd5a504abed201affb6dd824990335f12eff2dd1f8`.
