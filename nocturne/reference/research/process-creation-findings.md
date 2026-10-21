# Process construction and moon initialization

`dds3StartProcess` at001015b0 (316 bytes) and `evtInitMoonProcess` at001eafb8
(120 bytes) are integrated into the shared C build. The two routines pass 1,536
focused original-instruction comparisons: 1,024 constructor and 512 moon cases.
The working project saves their interfaces in place; independent reopening
checks all seven constructor argument registers A0..A3/T0..T2 and full V0,
and both selected assembly/pseudocode exports succeed.

The constructor executes the real 80-byte pool allocation. A null result returns
before touching the name or lists. Otherwise it clears the hash at record+18,
copies the first name byte and accumulates signed bytes while copying the next
byte, stopping at zero or after copying byte24. Byte24 occupies the low byte of
the hash. Thus names with at least24 nonzero bytes replace the low hash byte with
input byte24, including a zero terminator. The later forced zero at name byte23
does not reverse its contribution to the hash. Unwritten allocation bytes remain
untouched. Recovered C preserves this sequence rather than substituting a string
copy/hash helper.

The constructor stores priority20, flags1, truncated startup/shutdown halfwords
2c/2e, callback words30/34 and data38, then clears clocks and link words. Actual
sorted insertion executes. If the truncated startup delay is zero, actual
unlink/reinsert moves the node to the ready list. Callback addresses are stored;
construction does not execute them.

The retained named HD `dds3KernelCore$$dds3StartProcess` at1824e39a0 is a reviewed
logical counterpart. Unity builds a managed ID with a separate zeroed24-byte
name array, encodes the supplied string as ASCII and sums unsigned encoded bytes.
It has no PS2 inline-name/hash overlap, widens delays to32 bits, uses managed
delegates/object references, generates an ID through a virtual method, and adds
null/class/array checks and extra ID arguments. Those differences are explicit;
the recovered PS2 source is not replaced with managed behavior.

The moon initializer first checks raw process slot54f76c. An existing nonzero
value bypasses allocation and all moon changes. Otherwise it starts name `moon`
at54f780 with priority2b0b, delays1/1, callbacks1eadd8/1eaf08 and data0. It stores
the returned raw ID before executing the real calculation-enable, draw-disable
and phase-zero routines, then clears the cycle byte and event counter11a7c.
This reset still occurs for a null constructor result. Retained HD
`evtMoon$$evtInitMoonProcess` at1821a5960 shares the guarded creation/reset tree,
with managed IDs/delegates and widened fields.

The comparisons execute actual pool bump/freed-slot/new-page paths, page-list
advancement and the linked list/moon bodies. CPU DI/EI/SYNC/PLZCW values use the
existing synchronous model; no game-function call is intercepted. All 114,464
declared RAM bytes, Status, primitive counts and full constructor return lanes
are compared. Names include signed bytes, lengths around23/24/25, and backed
overlap with the allocated record. Delays include full raw high argument lanes
and values whose low16 bits truncate to zero or negative. There are168 null
constructor cases, produced through a real bump path with a synthetic payload
base0; this exercises the branch, not an allocator out-of-memory model. Physical
interrupt timing/scheduling, arbitrary list/global aliases, callback execution,
Unity runtime equivalence and matching binaries remain unproved.

DDS has one static constructor body at00101570. Its pool callee002cfeb8,
insertion00100858 and ready transition00100a98 all agree with individual body
matches. The existing removal link also agrees. The pool class-table address
constructor is explicitly masked; local offsets, signed-byte operations,
constants, registers and relative branches remain exact. The three moon setters
have unique static bodies at00228710/00228778/002286f8. The moon initializer has
no exact-structure DDS candidate under the narrow masks. This is not evidence
that DDS lacks corresponding logical behavior, and no DDS runtime equivalence is
claimed.

Shutdown1eaf08, its deferred wrapper and shared recursive lifecycle are now
integrated; see [shutdown findings](process-shutdown-findings.md). Next gaps are
process dispatch00100a48 and its general callbacks, plus moon
initializer1eadd8 and update1e9a80. The PS2 initializer loads six
texture handles; its retained managed counterpart only creates process data.
Complete moon-process and process-manager recovery remain unfinished.

Evidence: [source](../src/process_creation.c),
[validation](process-creation-validation.json),
[reopened interfaces](process-creation-abi.json),
[HD review](process-creation-matches.json),
[DDS cohort](process-creation-transfer.json).
