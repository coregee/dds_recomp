# Script ownership and engine-process bridge

Nine complete PS2 routines are recovered in `src/script_process.c`, adding 780 recognized body bytes. The focused report passes 1,344 original-instruction/C comparisons, including 53 connected process creation, delayed startup, WAIT/yield and script completion sequences. Those sequences execute 162 actual VM callback advances. The affected C builds with warnings treated as errors. Names and raw-register interfaces are saved and reopened in the working Ghidra project; selected exports are updated in place.

The routines cover linking and unlinking script work, creating its engine process, clearing global script variables, script/procedure name searches, process-relative user-data access, and the VM process callback. Actual recovered pool allocators, engine lists, process-data access, strcmp and VM handlers execute. No game function is replaced with a supplied return value. The existing 2,560-case operator/program comparison also still passes through the changed host bindings and reaches all 35 opcode handlers.

The new cases execute 297,597 original instruction steps and 686 VM indirect calls. They reach 150 of 152 non-delay root addresses. The two remaining addresses, 0x10A298 and 0x10A2A0, handle Trace results outside 1/2; the complete original Trace body returns only 1 for yield and 2 for termination. These branches are retained in the recovered source's return mapping, rather than reached by substituting a fake Trace result. Full backed RAM, defined raw64 returns, ordered VM target/argument traces, Status and CPU primitive counts agree. Returning original calls preserve the checked integer/floating callee saves. CPU value callbacks support the actual pool and aligned strcmp instructions; string functions themselves execute.

## Shared layouts

| Field or role | Nocturne | DDS |
|---|---|---|
| Script count | 0x54E994 | 0x3BA990 |
| Script head / tail | 0x54E998 / 0x54E99C | 0x3BA994 / 0x3BA998 |
| Global context pointer | 0x54EA20 | 0x3BAA00 |
| Work previous / next | +0xE8 / +0xEC | Same offsets |
| Work owning process / user data | +0xE4 / +0xF0 | Same offsets |
| Process's script-work pointer | +0x38 | Same offset |

The bridge selects the name from the procedure table at work+0xB4, record index work+0xC8, stride 32. It creates an ordinary 80-byte engine process with startup/shutdown delays 1/1, VM callback 0x10A268, shutdown callback 0x10A210 and script work as process data. The returned process is stored at work+0xE4, including an actual allocator-produced null result. The process callback obtains that work through the real getter and invokes the real VM. Yield returns zero, retaining the callback; termination returns raw64 -1 for the scheduler. Connected cases transition the created process from starting to running before advancing WAIT to completion.

The script list preserves store ordering, live reloads, unchecked links and wrapped counts. Global initialization loads the context pointer once and interleaves 256 integer stores at +0x40 with 256 float-word stores at +0x440. User-data writes truncate to a word; reads sign-extend that word into V0.

Procedure lookup searches the first kind-zero section in 16-byte descriptors starting at data+0x20. Header+0x10 is the signed descriptor count; descriptor+8 is the signed record count and +0xC the offset. Names occupy 32-byte records. This lookup does not validate FLW0. Tests include first/later/missing sections, duplicate kind-zero sections, negative/zero counts, raw high-word arguments, high-bit name bytes, empty names, missing names and backed query/name aliases.

Eight Unity semantic counterparts are reviewed. The reference uses managed objects, strings, delegates and checks, and the procedure reader can collect multiple procedure sections. The PS2's first-section lookup, layouts and completion return remain authoritative. The retained HD corpus has no identified counterpart for the process-relative user-data getter.

All nine complete spans resolve in DDS, with seven agreeing direct-call targets and fourteen decoded GP accesses. The registered VM callback literal agrees with its independently matched body; the shutdown literal leads to DDS 0x10C070 but its body remains unrecovered here. Constants, field offsets, registers and relative branches are retained. Static transfer is distinct from DDS execution.

Current evidence: `script-process-validation.json`, `script-process-matches.json`, `script-process-transfer.json`, `script-process-abi.json`, and the single rolling fixture/vector set in `script-process/`. Script work is supplied in these tests. Allocation/FLW0 parsing, messages, file loading, shutdown and actual scheduler dispatch of scripts are the [next connected frontier](script-process-next-frontier.md). Physical PS2 execution and a matching rebuilt executable remain unproved.
