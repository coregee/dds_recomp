# Compendium restore and comparison

The complete source covers five new native functions: registration checking
`00216BF0`, stock comparison `00219318`, restore by ID `0021A0B8`, restore core
`0021A118` and unit/record comparison `0021A308`. They contain 335 instructions
and 1,340 recognized bytes. The same source unit includes the existing
22-instruction search `00216B20` with its original full-width argument;
that registered variant adds no new identity. All six bodies total 357
instructions, 1,428 recognized bytes and 1,436 span bytes.

Both strict compile profiles and independent reviews pass. All 1,024
original/probe/main cases pass over 3,087,190 original steps. The
68 connected sequences add 180 calls: 160 defined raw returns and 20 genuine
void completions. Each actual C replay compares 142,630,912 ordinary RAM
bytes. All six native interfaces are saved, freshly reopened and exported.
All 542 earlier objects and sources are unchanged, and 1,632 retained cases
pass. The [publication](compendium-restore-publication.json) adds five
identities, taking recovery to 2,698/9,062 functions and 459,408 recognized
bytes. The complete raw64 search variant contributes no extra identity.

## Unity and community context

The [HD/community study](compendium-restore-HD-community-study.json) identifies
all five roles in retained Unity decompilations: `fclEncycCheckRegistable`,
`GetValidUnitIndex`, `SetRecordToUnit`, `SetRecordToUnitCore` and
`CompareUnitToRecord`. Managed arrays, initialization, guards and DLC remapping
are separate HD behavior. In particular, HD registers missing IDs in the
stock comparison path. The PS2 search returns `-1`, and its caller forms
`Game + 0x11DE0` without a missing-record guard. That original behavior is
preserved with backed input objects.

The [randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
provide independent descriptor, skill-row and parameter context. Their five
named parameter positions and intervening slot agree with this comparison's table
`[0,2,3,4,5]`. They do not establish the complete compendium record layout.
The actual executable supplies the 236-byte unit and 176-byte record offsets,
and distinguishes file coordinates from guest RAM.

## Native field and control behavior

The comparison returns the first mismatch code in this order. Offsets are
relative to the unit or serialized record, and are hexadecimal.

| Code | Compared fields |
|---|---|
| 1 | Unit flags masked by `240`, record word `A4` |
| 2 | Unit maximum HP `08`, record halfword `04` |
| 3 | Unit maximum MP `0C`, record halfword `06` |
| 4 | Unit EXP `10`, record word `08` |
| 5 | Unit level `14`, record halfword `0C` |
| 6 | Five parameter bytes at unit `16+i`, record `0E+i` |
| 7 | Five bytes at unit `1C+i`, record `14+i` |
| 8 | Five bytes at unit `7A+i`, record `4C+i` |
| 9 | Five bytes at unit `80+i`, record `52+i` |
| 10 | Unit skill count `38`, record halfword `1A` |
| 11 | Record skill membership in the unit skill array |
| 12 | Unit halfword `CE`, record halfword `A0` |
| 13 | Unit word `D8`, record word `AC` |

For codes 6–9, `i` follows the original parameter-order table. Skill membership
is unordered and allows repeated record skills to match the same unit entry;
it is not a multiset comparison. The native counts are not capped at 24.
Species/unique IDs, current HP/MP and unrelated padding are not compared by
this function. Returning zero means equality under these specific checks.

Stock comparison scans physical slots 4–15. It requires flag 1, excludes flag
`10` and status bit `800`, and uses the original search and comparison on each
eligible unit. A null output stops after the first difference. A backed output
collects physical slot numbers and counts every difference.

Restore clears all 236 destination bytes before reading the source ID and
calling the real default-unit constructor. It then copies the original fields
in instruction order, including individual unaligned word and doubleword
merges. Overlap can therefore change later source reads. The source preserves
that order, along with exact guest frame addresses and full-width public
arguments. Returning cohorts require four-byte-aligned unit and record bases;
individual field accesses still exercise the native partial operations.

The older `fclEncycSearch(int32_t)` interface narrows the argument. Restore by
ID forwards a full 64-bit register, and the native search compares it against
an unsigned record halfword. The complete local search variant preserves this
distinction without supplying a synthetic miss result or changing the older
registered implementation.

## Validation boundary

The authored cohort covers all six bodies, connected restore/comparison
calls, actual constructor dependencies, full declared RAM, immutable tables,
every defined raw return and genuine void completion, Status/FCSR condition,
stack balance and binding restoration. No expected output initializes C.
Complete volatile registers, private saved-frame bytes, arithmetic FCSR flags,
exhaustive inputs and physical gameplay remain outside this semantic profile.

The original capture observes equality and all thirteen mismatch codes. It
also observes a search match at index 184 and full-width `-1` results for
missing IDs. All 315 non-delay instruction addresses across the six bodies
are reached. Forty-two delay instructions are folded into their branches;
the address coverage does not establish every control edge or possible alias.
