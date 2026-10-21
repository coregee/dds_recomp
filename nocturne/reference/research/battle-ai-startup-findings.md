# Native AI startup and message variable conversion

Nine complete routines are recovered in `src/battle_ai_startup.c`. The compiled
host passes **1,600 original-instruction/C comparisons**, covering **1,560
recognized body bytes** and all **320 main instruction addresses**. The saved
working interfaces are independently checked and the selected exports updated
in place. There is no new full-suite run or checkpoint.

| PS2 entry | Recovered role | Direct cases |
|---|---|---:|
| 00288D80 | nbInitAiScript | 192 |
| 00101AF8 | dds3LinkProcess | 128 |
| 001CE5E8 | itfMesMngSetVar | 256 |
| 001CE7D8 | Immediate variable string setter | 128 |
| 001CE808 | Immediate variable byte-length setter | 128 |
| 001CF320 | Allocating variable setter | 256 |
| 001CFE48 | Native decimal writer | 128 |
| 001CE538 | Native character-name builder | 128 |
| 001CD710 | SET_MSG_VAR command113 | 128 |

Another **128 connected interpreter programs** execute the real SET_MSG_VAR
command. Its native descriptor has three parameters, agreeing with
[Atlus Script Tools' SMT3 command library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/SMT3/Modules/Common/Functions.json)
at revision `1c557a092dd7610829b7215be0f0f5101acf1d72`. Seven named Unity
counterparts corroborate roles. The decimal and native character-name helpers
retain descriptive PS2 names without an exact HD identity claim.

Original execution takes 1,551,663 instruction steps and makes 768 compared
indirect VM calls. Full declared RAM, defined raw64 results, Status, CPU
primitives, returning callee-save registers and ordered VM targets/arguments
agree. An empty-stack END completes with the code pointer still at that
instruction; its original position is independently checked in interpreter cases.

## Original startup

All **141 unchanged embedded BF procedure records** are started through the
actual script/message/process constructors, rather than supplying their return
values. An additional 51 cases vary original procedure selection and use a
synthetic empty-message descriptor in 26 cases to cover the negative message
handle path. Original actor IDs and their native name-table pointers drive
message variable0 through the real allocator and copier.

Startup reads the parent's priority at `mainProcess->process + 0x20`, subtracts
one with native word wrapping, and always starts BF `0x004F0800`. It assigns
battle-context user data to VM work `+0xF0`, sets actor-name variable0 when the
message handle at `+0xCC` is nonnegative, links the process to its parent, then
publishes the new process at main work `+0x104`.

The native linker detaches an already-parented target before walking the
destination sibling chain. It appends through offsets `+0x48` and `+0x4C`, then
stores the parent at `+0x44`. An unparented target's existing sibling pointer is
retained. Empty, one-child and longer lists, both detach positions and this
retained-pointer case are compared.

Unity's named `nbInitAiScript` adds eventbit `0x0E80` and encounter104/105 checks
to select between two script resources. Those HD conditions are absent from
this complete PS2 body and are excluded from recovered native startup.

## Complete message setter

Ghidra originally owned only 88 bytes of `001CE5E8`; the eleven branch-table
targets were omitted. Original table `0x00535AE0` now establishes all cases.
The restored body owns **476 instruction bytes** across its **496-byte span**;
twenty padding bytes remain outside the function. An explicit jump-table
annotation also restores its full switch pseudocode. Original executable bytes
are unchanged.

| Type | Native conversion |
|---:|---|
| 0 | Actual sprintf using original `%d` format at `0x0054F4C0` |
| 1 | Demon name pointer table `0x003E7328` |
| 2 | No conversion or allocation |
| 3 | Item name pointer table `0x003E8170` |
| 4 | `R` at signed raw64 values >=1001; otherwise decimal with `B` for negative and `F` suffix |
| 5 | Skill name pointer table `0x003E83F0` |
| 6 / 7 | Fixed 32-byte field name records at `0x00311450` / `0x00311850` |
| 8 | Race name pointer table `0x003E7930` |
| 9 | Magatama name pointer table `0x003E8C30` |
| 10 | Native two-byte character-name records, converted to buffer `0x0056C880` |

Type values outside0..10 leave variables unchanged. The script wrapper first
checks the real message handle; negative handles skip all parameter reads.
Otherwise it fetches index, number and type in order through the actual VM
helpers and completes with1. The interpreter cases exercise native name/no-op
types; number/floor conversions are compared through the full direct setter.

Variable text pointers start at instance `+0xC4`, and memory handles at
`+0x144`, both with four-byte index stride. Replacing an owned string runs the
real memory-handle free operation before clearing its pointer. A nonpositive
raw64 explicit length uses strlen and copies `(length+4)&~3` bytes, including
native padding after the NUL. A positive length allocates `(length+5)&~3`, clears
that entire extent, reloads the destination pointer and copies the requested
bytes. Allocation, acquire, free, formatter, string and copy routines all execute.

Private number/floor buffers can expose previously untouched bytes through
the rounded copy. The comparison supplies the same eighty bytes of ordinary
private-frame input before original execution and to the host's frame adapter.
It does not replace a call or supply formatted output. Thus trailing bytes are
compared rather than silently zeroed or ignored. The decimal helper also
retains native low-byte remainders on negative standalone inputs; the character
builder reloads its live character count after each output character.

## Shared SMT evidence and remaining work

[The DDS comparison](battle-ai-startup-transfer.json) resolves four complete
selected spans: parent linking, the two immediate variable wrappers and
SET_MSG_VAR. Both immediate wrappers identify the same DDS allocating setter,
`0019D460`, corresponding to Nocturne `001CF320`. All **71 words** of that span
agree except relocated original calls and one field-base instruction: Nocturne
uses instance `+0xC4`, DDS uses `+0xD0`. The twelve-byte layout shift is recorded
as a separate variant, rather than an exact offset/source match. This is
static binary evidence, with no DDS execution claim.

The [current AI dependency graph](battle-ai-frontier.json) keeps automatic
targeting `002879F0` and command52 at `00287EE0` open. Recover target-work
access, eligibility and score/filter dependencies before its decision wrapper,
then connect actual unchanged AI decision procedures. The community randomizer's
weighted-AI record boundary discrepancy also remains open. Original scheduling,
physical battle runtime, arbitrary allocation failure/invalid pointers/cycles
and matching executable behavior remain unproved.

Current evidence: `battle-ai-startup-validation.json`,
`battle-ai-startup-interfaces.json`, `battle-ai-startup-abi.json`,
`battle-ai-startup-matches.json`, `battle-ai-startup-transfer.json`,
`battle-ai-message-setter-discovery.json` and the rolling `battle-ai-startup/`
capture. The source build treats warnings as errors.
