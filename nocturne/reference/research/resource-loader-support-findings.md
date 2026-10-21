# Native resource-loader lists, file handles and submissions

**Twelve complete PS2 routines** in `src/resource_loader_support.c` pass **2,432 original-instruction comparisons**, covering **1,008 recognized body bytes** and all **205 main instruction addresses**. Actual file read/write commands, semaphore wrappers and selected recovered completion callbacks execute. Full declared RAM, defined raw64 returns, Status, primitive counts, callee saves and ordered syscall/callback observations agree. The source builds with warnings treated as errors. Twelve new interfaces and two existing semaphore interfaces are saved and independently reopened; fourteen current exports are merged in place.

| PS2 entry | Recovered routine | Complete DDS span |
| --- | --- | --- |
| 002967E8 | Remove active request and matching ring slots | 002888C8 |
| 002968A8 | Push reusable request | 00288988 |
| 002968B8 | Remove reusable request | 00288998 |
| 00296AA8 | fileGetMemHandle | 00288B88 |
| 00296AB0 | fileGetLoadPtr | 00288B90 |
| 00296AB8 | fileGetLoadSize | 00288B98 |
| 00296AC8 | fileCheckEnd | 00288BA8 |
| 00296B08 | PAC completion predicate | 00288BE8 |
| 00296C88 | Reserve PAC ring slot and submit read | 00288D68 |
| 00296F50 | Submit raw read | 00289030 |
| 00297218 | Submit raw write | 002892F8 |
| 00297658 | Drain completed user callbacks | 00289738 |

The native manager at **575618** uses semaphore **+0**, read/write ring bytes **+4/+5**, pending/free bytes **+6/+7**, active head/tail **+8/+C**, completed callback head **+10**, reusable head **+18** and ring-buffer base **+1C**. Four slot records begin at **+20**, stride eight, with request pointers at **+24**. Offset notation is hexadecimal.

Requests retain type/phase bytes **+0/+1**, active/reusable next **+4**, file job **+C**, remaining byte count **+10**, original size **+14**, user callback/argument **+18/+1C**, memory handle/top pointer/current pointer **+20/+24/+28**, and completed-list next **+2C**. PAC requests add decoding completion and ring slot at **+68/+6A**. The Unity `fileManager_H.fileCb_t` fields corroborate these roles, and four named file getters retain usable bodies at **182005EE0**, **182005EA0**, **182005EC0** and **182005E80**. Managed object offsets differ. HD `fileCheckEnd` only checks phase six; the PS2 PAC path also requires its decoding-complete halfword. The PS2 source retains that extra gate and sign-extends native getter words.

Active unlink compares each loaded pointer with the supplied **full64** request value. Dirty high lanes can therefore leave the list and slots untouched. It clears all matching ring slots, removes the first matching active node and repairs the tail when required. The reusable removal loop preserves the original unchecked membership assumption; fixtures supply a present member. No new missing-member behavior is invented.

PAC reads reserve a free slot, wrap the write index from three to zero, decrement the byte-sized free count and set phase **3 -> 4** before invoking the actual file command. The signed low-word remaining count is capped at **65,536 bytes**. Raw reads and writes use a **32,768-byte** cap, preserving negative counts and wrapped pointer arithmetic. If the file job is not ready, its original command returns minus one while the already written resource phase remains four. Independent oracles check these fields, submitted byte counts and buffer addresses, including every ring index, empty/free-counter cases, boundaries, invalid job phases and dirty argument high lanes.

The completion drain pops **+2C** under the semaphore, unlocks, invokes the actual callback with request and argument, then reacquires and rereads the global head. **762 actual callbacks** run in a finite test domain: the three recovered getters and active unlink. Unlink callbacks modify the real active list and slots while the completion queue drains. Their results are not supplied by a returning stub. Ordered target/request/argument observations agree independently, alongside **4,496 original syscall observations** and **73,266 original instruction steps**. Production user callback coverage, reentrant callback appends, kernel concurrency and IOP file execution are not established.

The existing semaphore source already uses SignalSema selector **42** and WaitSema selector **44** (hexadecimal). Their current saved interfaces and exports were refreshed alongside this batch to align saved names with that source and the original syscall instructions. These two existing routines are not counted as new recovery.

All twelve complete DDS counterparts resolve, supported by **twenty agreeing callee links** and **five repeated global constraints**. Manager **575618 -> 3DC658** and worker semaphore table **529B04 -> 398864** relocate consistently. Three tiny getter candidates are disambiguated by the original **96-byte getter/padding/end-check neighborhood**, which is byte-for-byte equal in DDS. A second PAC predicate candidate lies inside the independently anchored fileCheckEnd span and is rejected; the separate closed leaf at **288BE8** remains. This is static source transfer evidence, with no DDS runtime claim.

The phase processor at **00297460** constructs three actual file-event callbacks: **00296D90**, **00296FD8** and **002972A0**. The write callback at **002972A0** was missing from the function inventory. Its original address construction, closed 48-byte frame, restored RA/SP and return establish **436 recognized bytes in a 444-byte span**; two unreachable four-byte NOPs remain outside the function body. It is now created, saved and exported without overlap, increasing the inventory to **8,975 recognized functions**. Its pseudocode is available; it has no recovered-C comparison yet.

The [current update graph](message-update-frontier.json) includes the resource pump and all three installed file callbacks as explicit roots. It contains **nineteen unresolved bodies / 5,420 bytes / two indirect sites**. The increase in visible callback dependencies is not regression in source coverage. Complete pump/phase/event processing, allocation retries and their diagnostic transport, sound bank loading and submission, and six Message update/input routines remain next. Original scheduling, IOP completion, physical audio/rendering, PS2 runtime and a matching executable remain outstanding.

Rolling evidence: `resource-loader-support-validation.json`, `resource-loader-support-interfaces.json`, `resource-loader-support-saved-interfaces.json`, `resource-loader-support-abi.json`, `resource-loader-support-matches.json`, `resource-loader-support-transfer.json`, `resource-write-callback-discovery.json`, current function exports and `message-update-frontier.json`. `transfer_resource_loader_support.py` regenerates and constrains the DDS result. Work saves in place; no checkpoint or project copy was created.
