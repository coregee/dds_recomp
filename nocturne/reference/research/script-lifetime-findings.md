# Script shutdown and message ownership release

Thirteen complete PS2 routines are recovered in `src/script_lifetime.c`, adding 1,532 recognized body bytes. They connect script destruction to real font recycling, panel/variable ownership, message-manager cleanup, memory-handle coalescing, pool release and process shutdown. The affected C builds as C11 with MSVC warnings treated as errors. Names and raw register interfaces are saved in the working Ghidra project, independently reopened and checked; all thirteen selected exports merge into the current 8,956-function inventory.

| Original entry | Recovered role | Reviewed Unity reference |
|---|---|---|
| 0x100418 | ps2KernelGetFontContextIndex | Descriptive alias for the observed font-list consumer |
| 0x1C8120 | frCombineFontRequestEx | frFont, 0x18264F5E0 |
| 0x1C6FF8 | frDestroyFontRequestAfter | frFont, 0x18264F990 |
| 0x1CC150 | itfPnlRelease | itfPanel, 0x182665D60 |
| 0x1CDD78 | itfMesMngRequestMessageRelease | itfMesManager, 0x182452210 |
| 0x1CDF80 | itfMesMngRequestSelectRelease | itfMesManager, 0x182452FF0 |
| 0x1CFD88 | itfMesReleaseAllWindow | ReleaseAllWindow, 0x18244D3A0 |
| 0x1CFDF8 | itfMesReleaseAllVariable | ReleaseAllVariable, 0x18244D340 |
| 0x1CF058 | ps2MessageManagerReleaseInner | Descriptive alias; included in HD manager release |
| 0x1CDB38 | itfMesMngRelease | itfMesManager, 0x182452150 |
| 0x109E50 | scrReleaseScript | ScrScriptProcess, 0x1826C8400 |
| 0x109F08 | scrAllReleaseScript | ScrScriptProcess, 0x1826C8130 |
| 0x10A210 | scrScriptShutdown | ScrScriptProcess, 0x1826C8770 |

The focused comparison passes **1,856 cases**, executes **5,806,041 original instruction steps**, and reaches **all 307 non-delay root instruction addresses**. Full declared RAM, defined raw64 results, CPU primitive counts, Status and returning-call callee saves agree. The capture has no uninitialized reads or undeclared RAM writes. Another 10,032 independent RAM observations check cleared fields, masks, preserved handles, list links and process data.

Every one of the **191 shipped BF files** traverses actual construction followed by direct script release, all-script release and script shutdown: 573 resource cases. These paths execute 858 real constructors. Mixed one-to-four-work lists contain both process-owned and unowned scripts; all-release invokes the original process-kill/shutdown path, including 223 actual shutdown callbacks. Ordered callback targets and arguments agree with compiled execution. Another 256 repeated shutdown calls observe cleared process data and skip the freed work. Populated supplied ownership fixtures cover fonts, panels, 32 variable slots, file handles and local arrays. Allocator results and cleanup results are never supplied as game-function hooks.

The existing construction comparison also passes its 1,344 cases and the existing process-shutdown comparison its 2,816 cases through the changed host bindings. Those affected checks use current compiled source and their previous original captures; this batch is not a new full-suite run. Diagnostic formatting executes the actual recovered printf/formatter against a bounded string-buffer FILE; physical console output is outside this evidence.

## Original behavior

The context getter returns the sign-extended word at 0x551B80. Font recycling uses only its low eight bits to select a head word at 0x56BBC4 + index*4, then executes the real splice with Mode zero and stores its result. **Recycling does not release the font allocation.** The getter's alias describes this verified use; an exact retained HD kernel method is not claimed.

Splicing returns the second raw64 argument for a null first argument, or the first for a null second. Otherwise it writes first+0x28 from second+0x2C, reloads second+0x2C and writes that node's +0x24, then reloads first+0x2C into second+0x2C. Full raw64 Mode equality selects positioning. Mode 1 with a tag pointer whose unsigned halfword is 13 copies X and advances Y by the first request's signed height at +0x12; other Mode-1 requests advance X by width at +0xC shifted left four and copy Y. Tested backed aliases preserve these live reloads. The HD counterpart omits the PS2 tag-13 positioning branch and changes managed list fields.

A nonnull panel releases its optional handle at +4 when the ownership marker at +8 is nonzero, then reloads and releases the primary handle at +0. Window cleanup releases its two panel pointers at instance+0x9C/+0xA0 and clears phase bits with mask 0xFFFFF0FF. It leaves geometry, alpha and color fields untouched. All releases run the actual memory-descriptor and pool bodies, including neighboring-free-block coalescing.

Message release checks a signed64 negative ID before indexing the 20-byte slot table. It recycles message+0xC, calls the recovered message initializer with position reset disabled, and masks phase with 0xFFFDFFF8. A full-width nonzero speaker argument additionally recycles speaker+8 and initializes the speaker without resetting position. Selection release has **no negative-ID guard**; it recycles selection+8, clears +0xC and halfwords +0x10/+0x16, sets +0x12 to 0xFFFF and masks phase with 0xFFFBFFC7.

Variable cleanup walks 32 pointer words in ascending order. Each nonzero pointer owns a handle in the parallel array at +0x80; cleanup releases that handle and clears the pointer. **The handle words remain stale.** The manager's inner routine caches the instance pointer, releases message, selection, windows and variables, clears phase, releases the live slot allocation handle, clears slot+0xC, appends the slot to the free list and decrements the live manager count. The wrapper guards negative IDs and inactive slots, with no upper-bound check. The HD manager combines the wrapper and inner cleanup and substitutes managed references for native handles.

Script release formats the procedure name through the real printf, invokes the disabled diagnostic, releases locals at +0xDC/+0xE0, releases a nonnegative message ID at +0xCC, releases a nonzero file handle at +0xD8, unlinks the work and returns it to the pool. It does not remove an owning process itself. All-release caches work+0xEC before cleanup; owned work is destroyed through zero-delay process kill and its real shutdown callback, while unowned work calls direct release. The original tail printf defines the raw64 return of all-release; HD returns void. Shutdown obtains process data, releases nonnull work and clears process+0x38. Repeating shutdown therefore sees no work.

Seven complete selected DDS spans match uniquely: font recycle 0x194920, panel release 0x199900, message release 0x19BC98, selection release 0x19BFD8, variables 0x19DF70, guarded manager release 0x19B9A0 and script shutdown 0x10C070. Eight callee constraints and two repeated global constraints agree. Complete spans for the context getter, font splice, windows, inner manager, script release and all-release do not match under the current mask. Incoming callee addresses remain leads, rather than forced full-body identities. The existing allocator/list/printf dependencies also supply checked transfer anchors. This is static transfer evidence, not DDS execution.

Evidence: `script-lifetime-validation.json`, `script-lifetime-matches.json`, `script-lifetime-transfer.json`, `script-lifetime-abi.json`, and one rolling fixture/vector set under `script-lifetime/`. Full shipped-program execution, arbitrary invalid/cyclic ownership, exhaustive aliases/OOM, physical PS2 scheduling and a matching rebuilt executable remain unproved. The blocking file loader and file-backed construction now have their own [comparison](script-file-findings.md). Next connect those loaded allocations to actual shutdown and release.
