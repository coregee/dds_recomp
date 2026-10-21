# Native battle AI actions and embedded procedure construction

Eleven complete PS2 routines are recovered in `src/battle_ai_actions.c` and
compiled into the current host. **1,037 original-instruction/C comparisons
pass**, covering **760 recognized body bytes** and all **154 main instruction
addresses**. The working Ghidra interfaces were saved in place, independently
reopened and checked, and all eleven current assembly/pseudocode exports merged.
Command376 exposed a previously unrecognized twelve-byte body at `00288C90`,
bringing the recognized inventory to **8,979**.

| PS2 entry | Reviewed role | Direct cases |
|---|---|---:|
| 00287D78 | AI_ACT_ATTACK | 64 |
| 00287DA8 | AI_ACT_ESCAPE | 64 |
| 00287E08 | AI_ACT_SKILL | 64 |
| 00287EB0 | AI_SET_CRITICAL | 64 |
| 00259018 | nbSetNormalSkill0 | 128 |
| 00246B68 | nbGetSelectBit | 64 |
| 00288C90 | BTL_AI_ROT_CLR | 64 |
| 00288CA0 | BTL_AI_ROT_NEXT | 64 |
| 00288CE8 | BTL_AI_ROT_GET | 64 |
| 00288AD8 | BTL_PNL_ON | 64 |
| 00288A50 | BTL_CAM_ORG | 64 |

The remaining comparisons are **128 connected interpreter programs** and
**141 constructions of unchanged embedded BF procedure records**, through the
actual recovered script/message constructor. Original execution takes 1,077,600
steps and makes 2,432 compared indirect VM calls. Full declared RAM, defined
raw64 results, Status, CPU primitives, returning callee-save registers and
ordered VM targets/arguments agree. Eight direct rotation cases observe the
original divide-by-zero exception rather than assigning a returning result.

## Community and Unity evidence

[The original Hardtype discussion](https://gamefaqs.gamespot.com/boards/582958-shin-megami-tensei-nocturne/74938870?page=16),
particularly Krisan-Thyme and Zombero's posts164/166/167/169, supplied the embedded
AI BF location and distinguished it from weighted enemy AI records. The
[current community audit](community-research-audit.json) checks our original
ELF: file offset `0x3F1800` maps to RAM `0x004F0800`. Its 141 procedures use
63 command IDs; 29 were absent from the 191-file DDS3 archive script audit.
The native header declares `0x35B01` bytes, while the backed section extent is
`0x35BF1`, including 240 trailing string bytes. Construction fixtures preserve
both the unchanged header and the full backed extent.

[Atlus Script Tools' SMT3 command library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/SMT3/Modules/Common/Functions.json)
at revision `1c557a092dd7610829b7215be0f0f5101acf1d72` supplies the command
names; all 438 nonzero native descriptors in its 544-entry library have agreeing
parameter counts. These descriptors, original bodies and eleven named Unity
roles corroborate the current identities. The two native return-one commands
share a generic HD body: their names rest on command slots and metadata, rather
than a distinctive body fingerprint. HD managed guards, class globals and field
offsets do not replace native PS2 behavior.

The [Nocturne randomizer](https://github.com/nmarkro/Nocturne-Randomizer/tree/f74e85c0f632b751eaf278046884961c618c8541)
and its credited researchers provide adjacent battle-table, skill and script-ID
leads. Their weighted-AI table boundary discrepancy remains open; this batch
does not establish those record layouts.

## Recovered behavior

The battle context points to the actor at `+0x2C`. Attack stores action0 and
executes the actual normal-skill helper; escape stores action7 and clears the
skill. Skill fetches its VM parameter before reloading the actor pointer, stores
the truncated halfword at `+0x6C`, then action1 at `+0x6A`. Critical ORs `0x0100`
into the halfword addressed by context `+0x24`.

Normal-skill setup handles action0 and action1 skills164..167. Actual passive
skill0130 lookup supplies the attack flag. Native demon data supplies element
and animation unless unit flag4 selects constants0/1. The helper rewrites the
original element, animation and visual descriptors in native order and runs
the real formatter on the unchanged EUC-JP diagnostic. Other actions and skills
leave these descriptors unchanged. The selection helper scans sixteen physical
records at stride `0xF0`, extracting flagbit8 into a selection mask.

Rotation uses the native word at `0x005514E8`. NEXT fetches its parameter,
increments with 32-bit wrapping and stores that increment **before** signed
remainder or the original BREAK7 exception. CLR resets the word; GET publishes
the signed integer through the actual VM return helper. BTL_PNL_ON and
BTL_CAM_ORG are unconditional completion commands in this PS2 build.

## Transfer and remaining work

[The DDS transfer report](battle-ai-actions-transfer.json) checks the other
original executable and the community DDS command library at the same pinned
revision. Seven same-name descriptors provide leads. No selected complete body
resolves uniquely under the current relocation masks; each eight-byte no-op has
75 indistinguishable candidates. A missing full-span candidate does not prove
different semantics. DDS command IDs377/378 have different names/parameter
descriptors, so Nocturne's rotation IDs cannot simply be carried across.
The shared signature records native patterns and their limits without claiming
new DDS recovery.

Startup `00288D80` and its message/process-link dependencies are now recovered
in the subsequent [startup batch](battle-ai-startup-findings.md). Continue
automatic targeting `002879F0`, then relate actual AI procedure selection to
weighted records. Startup executes `scrStartScript2(priority, 0x004F0800, procedure)`
and battle-context user data through the real construction graph. This batch proves
construction of all original procedure records and synthetic command execution;
original AI decision paths, scheduling and physical battle runtime remain
unproved. No new full-suite run or checkpoint was created.

Current evidence: `battle-ai-actions-validation.json`,
`battle-ai-actions-interfaces.json`, `battle-ai-actions-abi.json`,
`battle-ai-actions-matches.json` and the rolling `battle-ai-actions/` capture.
