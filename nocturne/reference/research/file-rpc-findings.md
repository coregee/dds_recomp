# PS2 RPC transport and file descriptors

Seventeen complete routines are now compiled C, adding 2,204 summed original
body bytes. All 2,880 original-instruction/C comparisons pass. The working
project is saved in place and current exports/reports replace rolling outputs.

| Entry | Recovered routine | Bytes |
|---|---|---:|
|002de458|ps2SifSyncDataCache|172|
|002de6d0|ps2SifRpcPacketTake|168|
|002de778|ps2SifRpcPacketRelease|28|
|002de178|ps2SifSendCommand|308|
|002de2b0|ps2SifSendCommandDefault|60|
|002ded48|ps2SifRpcCall|492|
|002deb78|ps2SifRpcBind|320|
|002dc260|ps2KernelSifSetDma|16|
|002dc270|ps2KernelSifSetDmaInterrupt|16|
|002dbeb0|ps2KernelDeleteSema|16|
|002df468|ps2FileRpcDescriptorInitialize|92|
|002df4c8|ps2FileRpcDescriptorTake|136|
|002df550|ps2FileRpcDescriptorLookup|108|
|002df980|ps2FileRpcLockInitialize|76|
|002df9d0|ps2FileRpcLock|44|
|002dfa00|ps2FileRpcUnlock|12|
|002dfca8|ps2FileRpcVersionMismatch|140|

The recovered call and bind routines execute their actual packet allocator,
command builder, cache-range traversal, native semaphore veneers, DMA veneers
and packet release. No high-level RPC return is supplied. The external boundary
records syscall packets/results and ordered `DHWBIN`/`SYNC 0` instructions.
This recovers the shared transport used by file open/close/seek/read/write;
those file operations and IOP completion callbacks are not counted here.

The allocator walks 64-byte packets using a busy bit and writes the packet index
in the flags' upper half. It retains the original serial special case: starting
at zero stores two in the queue but gives serial one to the packet. Interrupts
are disabled and then enabled unconditionally, including exhaustion. Release
clears the serial and busy bit without freeing the packet storage.

Commands retain the original packet-size guard, low-byte size and payload-size
encoding, destination and command stores. They submit one or two 16-byte DMA
records, with command record flag `0x44`. Cached ranges round to 64-byte lines;
the exact order of cache and sync operations, including the unrolled eight-line
loop, is compared. Physical cache behavior and DMA transfer are unproved.

RPC call modes preserve asynchronous submission and optional initial cache work,
the full-width same-buffer comparison, callback presence, semaphore creation,
wait/delete and failure release. The ninth argument is a 32-bit load from the
caller's stack at offset zero; its saved Ghidra interface now reflects that
storage. Bind resets the client server fields and shares the same real transport.

RPC call/bind write only the semaphore count words before the native create
veneer. Its observed option word remains unwritten in the original frame.
The harness seeds that word as an explicit initial-stack operand and supplies
the same value at the C syscall boundary. It is not silently zeroed or claimed
to be a recovered packet store. Other unobserved packet words remain outside
the service contract. Descriptor/lock initialization explicitly writes option
zero, initializes only when the stored semaphore ID is minus one, and retains
unchecked kernel errors.

The descriptor table has 32 records of 16 bytes; allocation scans flags at
offset four and reserves with `0x10000000`. Lookup tests the full unsigned
64-bit ID against 32. The version check compares three four-byte tokens with
the real recovered `memcmp`, preserving its conditional order.

Reviewed results include 66 allocated packets, 190 exhausted/disabled queues,
128 releases, 512 RPC calls and 256 binds. Of the call/bind cases, 135 accept
submission, 555 exhaust the queue, 47 fail DMA and 31 fail semaphore creation.
Descriptor cases reserve 103 slots and exhaust 25; 128 lookup and 128 version
cases also pass. The group compares 12,896 declared RAM bytes, defined results,
Status and primitive counts, 11,392 syscall trace words and 24,416 cache trace
words over 171,221 original instruction steps. Cached and uncached packet-pool
addresses are separately backed test storage, not a cache-coherency model.

DDS has complete matching spans for all 17 routines and 47 agreeing call links.
Only listed absolute address operands and J/JAL targets relocate. Register roles,
constants, syscall selectors and branch words remain exact. The duplicate packet
take/release candidates are selected by actual RPC call/bind links. The short
unlock is constrained by the known signal callee and lock-semaphore address;
the duplicate version check is selected by its client/descriptor-table relation.
Queue, descriptor table and contiguous semaphore/version-pointer relationships
agree. These are shared static SMT patterns; DDS execution is not claimed.

Unity supplies the retained file-job roles, but no managed method identity is
promoted for this PS2 transport group. Next are SIF/RPC initialization and real
completion handlers, file command packets/uncached reply access, then workers
and the LB scheduler/pump. IOP completion, kernel scheduling, actual asynchronous
file I/O, arbitrary aliases, unbounded malformed queues, PS2 runtime and a
matching executable remain unproved.

The current read-only inspection in `file-rpc/frontier.txt` confirms that
`002decb8` has existing instructions but no owning function. It loads the server
record from packet+34, appends that record through its queue at record+40, copies
the request fields, and tail-calls thread-wakeup support `002dcd50` only for a nonnegative
queue thread ID with a zero queue flag. It has no stack frame; its last return
delay slot is at `002ded40`, before the next recognized entry `002ded48`.
This is original instruction evidence for the next discovery/recovery step,
not a new canonical function or a runtime observation. That wakeup support is
itself original SDK code with current-thread, deferred queue and semaphore
effects; it must be recovered rather than supplied as a kernel result.

Source: `src/file_rpc.c` and `.h`. Current evidence: `file-rpc-validation.json`,
`file-rpc-matches.json`, `file-rpc-transfer.json`, `file-rpc-abi.json`, and rolling
`file-rpc/` outputs.

The next completion batch now recognizes and recovers002decb8 in place, using
the already canonical draw-wakeup source. Its response, file-completion and
notification peers are also canonical. The earlier missing-function description
above records the pre-discovery inspection. See [current completion findings](file-completion-findings.md).
