# Native sound-bank loading, wait and play

Two complete bodies in `src/sound_bank_flow.c` pass **384 original-instruction comparisons**, covering **312 recognized body bytes** and all **55 reachable main instruction addresses**. The bank-status helper returns only0/1/2, making two retained compiler dispatch branches at **002C1CD8** and **002C1CE8** unreachable. Both interfaces are saved in the working Ghidra project, independently reopened and checked; current exports are merged in place.

| PS2 entry | Recovered routine | Complete DDS counterpart |
| --- | --- | --- |
| 002C1CA0 | ps2SoundEnsureBank | No complete span under the current mask |
| 002C18D8 | ps2SoundPlay | 002E8F78 |

Bank checking extracts a signed bank number from the low32 sound ID shifted right16. A resident bank is found among seven IOP records; a matching pending-bank word produces status2. Status0 formats `MIDI%04X.SMG` into the original sixteen-byte private filename area, prefixes `/sound/`, and submits command **A0** with the terminating NUL. The pending-bank word is written after submission. Known native callers discard V0, so the selected EnsureBank interface is void and makes no claim about the leftover return register.

Only status2 enters the wait loop. Each iteration runs the real delay helper with argument2: GetThreadId, CancelWakeupThread, SetAlarm with the original alarm callback, then SleepThread. A nonzero callback word at **5519D8** runs the installed loader pump **002976C0**. The original cache scan and bank lookup then execute again until status1 is observed. The source retains this unbounded wait.

Play always calls EnsureBank first, then queues command **90** with twelve parameter bytes: the sound ID at+0, volume narrowed to a halfword at+8, and the low pan byte stored as a halfword at+A. Its full64 return is the actual sign-extended queue token, including rollover behavior.

The original does **not** write packet bytes+4..+7. Native source retains this unwritten private word. The host comparison replays **192 observed original stack words** at that position; their values are context inputs, not recovered logic. Written ID/volume/pan, filename bytes, queue producer index, token and pending/resident bank state have independent oracles. This is not matching compiled stack-layout evidence.

The comparison executes actual cache, formatter, path, string, enqueue/submit, delay and loader-pump bodies. Full declared RAM, defined Play returns, Status, CPU primitives, saved registers and ordered cache/kernel/wait observations agree. It consumes **81,664 supplied TagLo operands**, includes **128 explicit external IOP bank arrivals**, and executes **126 actual loader pumps**. Arrival writes occur at selected SleepThread syscall boundaries; no game function or callback return is supplied. Kernel scheduling, real IOP execution, hardware cache behavior and physical audio remain unproved.

Missing-bank fixtures use nonnegative signed16 banks. Negative resident/pending banks retain signed extraction. Missing negative-bank filenames may overlap the original adjacent filename/path buffers and remain outside this finite returning fixture domain. Queue mode is asynchronous with space available; separate queue comparisons cover synchronous submission and full-queue behavior. The callback domain is the installed pump or a null callback.

The complete DDS Play caller identifies bank-ensure **002E9340** and command-enqueue **002E87A8** as role leads, although those bodies differ under the current mask. They are not promoted to complete matches. The native packet shape, bank records, pending word and alarm/pump protocol are recorded in the shared SMT signature ledger. No exact HD identity is accepted for these platform bodies.

The remaining Message update graph has **six unresolved bodies / 1,608 bytes / no unresolved indirect sites**: CalcMesFlow, CalcMessage, CalcSelect, SelectItem, SelectItemMove and CalcManagerProc. Static traversal stops at compared routines and does not establish every production callback or scheduling path. Overall integrated recovery is **1,118 / 8,975 functions (12.457%)**, with **616,218 aggregated comparisons**. The last full run remains **413 functions / 462,684 cases**.

Current evidence: `sound-bank-flow-validation.json`, `sound-bank-flow-interfaces.json`, `sound-bank-flow-abi.json`, `sound-bank-flow-transfer.json`, the rolling `sound-bank-flow/` capture and current function exports. Work saves in place; no checkpoint, project copy, frozen source tree or duplicate capture was created.
