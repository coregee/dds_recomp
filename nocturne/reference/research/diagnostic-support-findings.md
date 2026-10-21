# Native diagnostic packet and formatting support

Three complete routines in `src/diagnostic_support.c` pass **768 original-instruction comparisons**, covering **280 recognized body bytes** and all **58 main instruction addresses**. The actual interrupt wrappers and stream formatter execute. Full declared RAM, defined raw64 returns, Status, primitive counts and callee saves agree, with independent pool-state and selected formatted-output oracles. The affected C builds with warnings treated as errors. All three interfaces are saved in the working Ghidra project, independently reopened and exported in place.

| PS2 entry | Recovered routine | DDS evidence |
| --- | --- | --- |
| 002CCF68 | ps2DiagnosticRpcPacketTake | 002F4B10, constrained by the later RPC caller |
| 002CD010 | ps2DiagnosticRpcPacketRelease | 002F4BB8, constrained by the later RPC caller |
| 002D7F88 | ps2LibcVsprintf | Unique complete span at 00305B08 |

The diagnostic transport uses an independent packet queue at **599700**. The queue has serial **+0**, packet base **+4** and signed count **+8**. Each packet occupies 64 bytes, with busy/flags **+10**, self pointer **+14** and serial **+18**. Offsets are hexadecimal. Allocation scans for the first clear busy bit and writes `(index << 16) | 5`. When the incremented serial is one, the queue advances to two while the packet retains one. Release clears the serial and only the busy bit. The source retains these native details.

Allocation uses the actual interrupt-disable wrapper, then **unconditionally enables interrupts** on every return. It does not restore an initially disabled state. Fixtures check empty, negative and exhausted counts, early and late free packets, serial wrap, cached/uncached packet addresses and dirty argument high lanes. The common comparison driver now permits an explicit expected final Status for a routine that changes it; existing fixtures retain the default requirement that Status is preserved.

`vsprintf` constructs the original string-buffer FILE with flags **208**, capacity **7FFFFFFF**, reentrancy context from **52BE28** and the supplied output pointer, then calls the recovered formatter at **002D6600** with an explicit guest argument cursor. It writes the final terminator at the advanced output pointer and preserves the formatter's return. Cases include twelve argument slots, raw high lanes, width and precision, strings, characters and `%n`. The original formatter's distinction between `%lX` and `%llX` is preserved. Host transport relocates the private FILE; this is behavioral source recovery, without a matching native stack-layout claim.

The DDS `vsprintf` span resolves uniquely, with its actual formatter callee at **003033F0** and reentrancy word at **0039BFD0**. Standalone comparison finds two identical copies of each pool body. The subsequent complete diagnostic RPC caller at 002CD418 disambiguates them to 002F4B10 and 002F4BB8; the rolling transfer report records its original call-destination constraints. No exact Unity identity is asserted for these native library helpers.

The subsequent [diagnostic RPC and transport recovery](diagnostic-rpc-findings.md) closes **002CD418**, **002BD4A8** and **002BD550**. The [current Message update graph](message-update-frontier.json) has **thirteen unresolved bodies / 4,240 bytes / two indirect sites**. Remaining loader work includes phase processor **00297460**, pump **002976C0** and all three production file-event callbacks. Actual kernel scheduling, IOP completion, PS2 runtime and a matching executable remain unproved.

Current evidence: `diagnostic-support-validation.json`, `diagnostic-support-interfaces.json`, `diagnostic-support-abi.json`, `diagnostic-support-transfer.json`, the rolling `diagnostic-support/` capture and current function exports. No checkpoint, project copy or archived source/capture was created.
