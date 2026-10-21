# Recursive process shutdown and moon texture cleanup

Seven integrated C routines cover 812 original body bytes and pass 2,816 focused
original-instruction comparisons. The shared host DLL builds with warnings as
errors. All seven interfaces are saved in the working project, independently
reopened and successfully exported. The instruction comparison executes the real
list, pool and deferred-queue callees, recursive children and selected callbacks.

| PS2 entry | Recovered routine | Cases | HD identity |
| --- | --- | ---: | --- |
|00100d70|dds3KillProcessNow|512|1824e1330 KillProcess|
|00100e08|dds3EndProcess|512|1824e10b0 EndProcess|
|00100e80|dds3EndingProcesses|256|1824e2780 dds3EndingProcess|
|00101738|dds3KillProcess|512|1824e2ee0 dds3KillProcess|
|00101b80|dds3UnlinkProcess|256|1824e3c90 dds3UnlinkProcess|
|001eaf08|ps2MoonShutdown|512|Descriptive PS2 alias|
|002ab8f0|ps2TextureDeferredRelease|256|Descriptive PS2 alias|

The public kill wrapper rejects full 64-bit zero and -1 arguments. States1/2
store the truncated shutdown halfword and move through actual removal/insertion
to ending state3. State3 updates the delay directly. A zero delay finalizes the
process immediately; other states return zero. The ending walker decrements only
positive signed16 delays and saves the next list pointer before finalization.
Negative delays remain pending.

Immediate finalization saves each child's sibling before the actual recursive
kill call. After children, it removes the parent from its process list, makes the
diagnostic call, loads and executes the shutdown callback, clears the low flag
nibble, detaches parent/sibling membership, and releases the process pool slot.
The unlink routine replaces the parent's first child or searches the sibling
chain, then clears sibling before parent. Its equality compares sign-extended
raw32 link words against the full target argument, and valid membership is
assumed. The recovered C does not add a missing-sibling escape.

Moon shutdown reads the process data pointer, reloads each of six consecutive
texture handles after the preceding append, skips zero handles, and calls the
actual deferred-queue wrapper. It then executes pool release on the data record
and clears the singleton at54f76c. The wrapper uses queue5520a0; it does not
destroy textures immediately. The real queue allocates a16-byte node when needed
and256-byte blocks containing63 handle slots, with actual semaphore wrappers.

Five retained Unity process-manager bodies provide reviewed logical counterparts.
HD replaces raw links44/48/4c and callback34 with managed references68/70/78 and
delegate40, widens the signed shutdown delay from16 to32 bits, and removes
explicit pool release through managed storage. HD kill checks a func_ans field
for -1 where PS2 checks the raw process argument. HD unlink can stop at a missing
sibling and clears parent before sibling; PS2 order and assumptions are retained.
The ending flag masks are equivalent after OR3, not a behavioral difference.

The HD moon shutdown at1821a7f80 retains a data cast and singleton clear but no
six-texture/pool cleanup core. `sdfTex$$sdfTexFreeDelayed` at18230d470 initializes
classes and returns without a retained handle/queue operation. Metadata and caller
roles alone are insufficient to promote either exact PS2/HD identity.

The comparisons cover child/grandchild recursion, first/middle/last sibling
detachment, all low flag nibbles, positive/zero/negative delays, full64 sentinels
and delay lanes, all64 texture presence masks and empty/partially filled deferred
queues. They compare all58,768 declared RAM bytes, Status, primitive counts,
2,341 diagnostic boundaries,828 actual selected callbacks and12,276 kernel trace
words. Selected callbacks execute the real empty callback002b58b8 and recovered
moon shutdown001eaf08. Synthetic pool metadata supplies backed pages and slots;
this is not validation of actual game allocator initialization or scheduling.
Some ending-list fixtures deliberately permit a saved-next node to have been
removed by recursive shutdown; the original traversal is preserved without an
added liveness check.

The only intercepted game function is diagnostic printf002d4748. Its original
format52dd18 and full process operand are checked; formatter/FILE side effects
are not executed. CPU primitives use the existing synchronous value model, and
semaphore results use the existing32-bit value boundary. Arbitrary list/global
aliases, malformed cycles/membership, all callbacks, physical interrupt timing,
PS2 runtime, HD equivalence and matching binaries remain unproved.

DDS uniquely matches end00100ef0, ending tick00100f68, kill wrapper001016f8 and
unlink00101b08, as well as the existing list/pool/deferred anchors. Their three
callers point to finalizer00100e68, which has136 bytes instead of Nocturne's152.
Removing exactly Nocturne words17..20—the diagnostic address construction, printf
call and argument delay slot—leaves34 words that agree, except direct call targets.
All four remaining calls independently agree with the kill/list/unlink/pool body
matches. The exact full-span search remains zero; this is a separately reviewed
diagnostic omission, not a relaxed instruction mask.

DDS has two wrapper candidates002d00b8/002d1c08, both calling matched deferred
append002d3c30. Their queue identities remain ambiguous. The moon shutdown has
no exact-structure candidate under the narrow masks. No DDS runtime/source
equivalence or uniform code relocation is claimed.

Process dispatcher00100a48 and merged traversal00100c48 are now recovered in
[process-dispatch findings](process-dispatch-findings.md). Continue real game
callbacks, especially moon texture initializer001eadd8 and update001e9a80. Diagnostic
formatting remains a connected source gap. Full executable recovery is unfinished.

Evidence: [source](../src/process_shutdown.c),
[validation](process-shutdown-validation.json),
[reopened interfaces](process-shutdown-abi.json),
[HD review](process-shutdown-matches.json),
[DDS cohort and explicit diagnostic omission](process-shutdown-transfer.json).
