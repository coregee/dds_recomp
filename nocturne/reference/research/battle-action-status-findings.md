# CHECK1 timeline, death, passive and action-stack recovery

Twenty-one complete native routines in `src/battle_action_status.c` cover
1,656 recognized body bytes. Their 5,888 original-instruction comparisons reach
all 328 selected main instruction addresses. The host build passes with
warnings treated as errors. Full declared RAM, raw returns, Status, primitives,
FCSR and defined vector state agree; actual process lookup, unit/party routing
and skill search execute. All 21 Ghidra interfaces are saved in the working
project, checked after reopening, and included in the current corrected exports.

Existing packet and completion captures also pass against the rebuilt library:
4,864 and 2,176 cases respectively. The current reports and source/input hashes
are checked by `battle-action-status-regressions.json`. No full-suite capture,
checkpoint, project copy or duplicate validation capture was created.

## Community research and original record inputs

The pinned [Nocturne randomizer implementation](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/nocturne.py)
places basic AI records at ELF file offset `0x002999E0` with stride `0xA4`.
Its [original notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
identify the USA build and file/RAM address relationship. The implementation
uses the four-byte-earlier base than its commented `0x002999E4` lead.
Native consumers corroborate RAM base `0x003989E0`, stride 164 bytes, and the
death-script/event fields at offsets `0xA0` and `0xA2`.

Each of the three death queries exercises IDs 0 through 383 in 384 cases,
for 1,152 original-ID cases. The complete original AI table is checked unchanged
before and after each case. Native ID0 exits before accessing a death field;
the three ID0 cases preserve that behavior. Additional synthetic endings cover
zero/nonzero and unsigned values 32768 and 65535. This extends the community
record lead into validation of its original instruction consumers.

The [DDS battle-table documentation](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/battle-tables.md)
provides related-engine context for `AICALC.TBL`, `UNIT.TBL` and `SKILL.TBL`.
Those DDS containers and layouts are not imported into Nocturne. Reference
revisions, fetched content hashes, the native AI table hash and all original
ending halfwords are retained in `battle-action-status-matches.json`.

## Native behavior retained

| Area | Checked PS2 behavior |
|---|---|
| Timeline | 32 inline rows at context `+0x88`, stride8; unlock/end/HP halfwords at `+0/+2/+4`. HP and timer loads are unsigned. Addition uses a signed low32 sum: negative clamps to zero and returns1; positive values wrap on the halfword store. Main flag `0x20000` disables the change. |
| Group death | Signed full64 form comparison selects enemy forms4..13 or friendly forms0..3. Each active form needs zero timeline HP and absence of descriptor flag `0x100`. Context/main/form pointers reload during iteration. |
| Descriptor flags | Actual work lookup; null and flag4 return0. Otherwise a signed word is loaded from `0x3497C0 + id*60`. |
| Passive consumption | Skills `0x159` and `0x168` use the real skill search. Party flag `0x400` rejects reuse; success sets `0x200`. The stop helper sets `0x400` when `0x200` is present. Original guards and unchecked accesses are retained. |
| Death queries | Form index is signed LH at `+0x92`. Work flag4 chooses ID0; condition masked to `0xFFF` equalling `0x200` overrides it with ID255. Death script/event values use unsigned LHU with the original A4 stride. |
| Order | Twelve signed bytes at main `+0x48`; negative entries are skipped. Entries whose referenced party lacks flag1 or has flag `0x20` become `0xFF`. Native code has no positive-index upper-bound guard; backed cases include127. |
| Talk and stock | Talk rejects exactly seven single condition values; combinations follow the default. Stock examines16 physical 236-byte records, requires flag1 without flag4, and compares the full incoming raw64 ID. First match wins; absence returns all64 one bits. |
| Memory and panel | Communication halfwords `+0x72/+0x78/+0x74/+0x76` are cleared to `0/FFFF/0/FFFF` in that order. Panel analysis end writes `0x551224=0`, then `0x551220=4`. |
| Action stack | Main `+0x3C` supplies a cached base; count at `+0x40` reloads before every field store and the final increment. Selected backed aliases redirect later fields when an earlier store changes the count. A changed base field does not replace the cached base. |

The Unity reference supplies 21 reviewed semantic roles. Managed object layouts,
array checks, obfuscated HD constants and source argument widths are not copied.
The native death halfwords also correct signed/stride interpretations in the
older untyped PS2 pseudocode.

## Remaining work and transfer limits

Current integrated recovery is 1,691 of 8,980 recognized routines, or 18.831%,
with 251,084 recognized body bytes. The original action graph retains 411
unresolved bodies /95,292 bytes. CHECK1's direct closure falls from46 to25
pending bodies /8,528 bytes. Continue the remaining packet composites, model
queries, communication completion and the entry/update callbacks at
`00257488` and `002577D8`, followed by actor selection and real message progression.
Indirect or unrecognized dependencies can expand this closure.

Strict full-span DDS comparison finds no selected complete counterpart in this
batch. The signature ledger records native offsets and predicates as comparison
leads; it does not establish shared DDS layouts or execution. These comparisons
use bounded backed RAM and finite queues. Physical battle execution, a matching
executable and full-program recovery remain outstanding.
