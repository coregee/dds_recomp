# CD initialization, callbacks, worker and shutdown

Twelve complete bodies are reconstructed in `src/cd_lifecycle.c` and its
header, adding 2,048 original body bytes. They extend the single rolling CD
capture and source comparison to 35 functions and 2,250 passing cases.
All 1,315 non-delay instruction addresses are reached; 64,916,016 original
steps, 731 actual native RPC response handlers, all 72,856 declared RAM bytes
and 212,163 ordered trace words agree. Current measured totals are in
`cd-stream-validation.json`.
The affected C builds with warnings treated as errors.

Two original spans had no Ghidra function: `002cb578..002cb64b` (212 bytes)
and `002cb650..002cb6ef` (160 bytes). Their executable bytes were checked,
bounded instructions disassembled, and exact function bodies created in the
working project in place. `cd-lifecycle-discovery.json` records the increase
from 8,958 to 8,960 recognized functions. No checkpoint or project copy was
created.

| Nocturne | Recovered function | DDS complete-span match |
| --- | --- | --- |
| 002cb3b8 | ps2CdSetReadCallback | 002f2f60 |
| 002cb418 | ps2CdReplyNotify | 002f2fc0 |
| 002cb4b8 | ps2CdCallbackThreadMain | 002f3060 |
| 002cb578 | ps2CdEnsureCallbackThread | 002f3120 |
| 002cb650 | ps2CdReadCopyReply | 002f31f8 |
| 002cb788 | ps2CdExit | 002f3330 |
| 002cb820 | ps2CdSetCommandCallback | 002f33c8 |
| 002cb898 | ps2CdCommandCallback | 002f3440 |
| 002cb8d8 | ps2CdRegisterCommandCallback | 002f3480 |
| 002cc110 | ps2CdInitialize | 002f3cb8 |
| 002de150 | ps2SifRemoveCommandHandler | 0030ccd0 |
| 002dbce0 | ps2KernelExitThreadRaw | 0030a860 |

These aliases describe the observed bodies. Retained SDK spellings and Unity
counterparts are not claimed for the platform functions.

## Initialization

Initialization first rejects active S RPC work, executes real RPC initialization
and GetThreadId, then enables the callback inhibit, resets five request binding
flags, increments the invocation serial and clears the additional state word.
Service `80000592` binds through client `598e68`; signed failures and absent
servers each execute the original 1,048,577-iteration decrement/NOP retry loop.

RPC command zero sends the four-byte low mode word and receives sixteen bytes
at `52b200`. The uncached marker at offset twelve is loaded before version
words at offsets four and eight. Marker `FF` bypasses version checks; `FE`
also sets the debug word to one. Otherwise signed word arithmetic rounds the
version words toward zero when dividing by 256. A result below two in either
word changes the return from one to two.

Only the full 64-bit input equal to five selects shutdown, followed by setting
all three semaphore words to minus one. Other modes initialize the semaphores
and register the command callback. A failed RPC submission clears the inhibit
and returns zero without these later calls. Version boundaries, negative
words, special markers, submission failures, retries and raw mode aliases are
included in the current fixtures.

## Read replies and worker

Read callback replacement checks actual N activity before swapping the pointer
under DI and conditional EI. Notification copies the mailbox word into the
mirrored command. Command eleven clears activity without signaling; other
commands signal the N semaphore and, when a worker and read callback are
present, the callback semaphore. The mailbox is then cleared.

Read-copy replies use an uncached packet with signed counts at offsets zero
and four, destinations at eight and twelve, and payloads at sixteen and
eighty. Both byte loops reload their count after each store, retaining header,
data and output alias behavior. Tail notification uses the global command
mailbox, rather than the incoming reply pointer.

The callback worker is the original infinite loop. Finite external wait events
deliver actual notification bodies; its callbacks execute recovered serial,
newline or buffered-output functions. An exit mailbox of `FFFFFFFF` clears
activity, mailbox, worker handle and worker state before calling raw kernel
ExitThread. Selected cases let that service return once, executing the
original continuation before a later successful termination. The C comparison
wrapper catches only the external kernel termination; it does not manufacture
a return from the worker. The function remains nonreturning in canonical C.

First worker creation retains the live attribute word in its 24-byte thread
record, writes the original worker entry, stack, size, GP and priority, stores
the created handle, and starts it even when creation reports failure. Later
calls only change priority and return zero. GetThreadId uses the previously
established signed 32-bit kernel ABI; creation/start/priority operands retain
their raw widths.

## Command callbacks and shutdown

Command `80000012` registers the actual command callback with parameter zero.
The inhibit is set before DI and registration, then cleared after conditional
EI. Callback replacement writes its parameter before its pointer. Invocation
loads the pointer before checking the inhibit and passes the signed parameter
word. Removal selects the command table by the full input sign, wraps the low
word shifted by three, and clears only the handler word, retaining its parameter.

Shutdown signals the exit mailbox only when the worker is active. It always
attempts deletion of N, S and callback semaphores, regardless of preceding
failures, then removes the command handler under DI and conditional EI.

## Transfer and remaining work

All 35 current CD spans have unique static DDS matches with 139 agreeing
call/callback links. The two relocated callback literal pairs are independently
constrained to the matched worker and command callback. Scalar constants,
service IDs, branches, field offsets and retry geometry remain fixed. These
are transfer leads, not DDS execution proof.

The comparison checks complete declared RAM, ordered kernel/cache/interrupt/
debug/callback traces and Status. Kernel results, finite IOP arrivals and thread
termination are external boundaries. Arbitrary callbacks, asynchronous
reentrancy, physical PS2/IOP scheduling and a matching executable remain
unverified.

Movie archive readiness `002bd5d8`, seek `002bd6a0`, sector read `002bd750`
and lookup `002bd9c8` now have the recovered CD dependencies. Their separate
libc printf chain is still unfinished: `002d4748 -> 002d6600 -> 002d6678`,
with stream initialization `002d9908 -> 002d96f8`. The main formatter is a
5,652-byte body with fourteen direct callees. The fatal entry `002a82b0`
merely saves argument registers to its private stack and enters an infinite
NOP/branch loop; it calls no formatter and must not be replaced by a returning
error stub.
