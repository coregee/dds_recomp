# Shared process lists and startup transitions

Six integrated C routines cover 1,088 original body bytes and pass 2,560 focused
original-instruction comparisons. They compile in the shared host DLL with
warnings treated as errors. All six raw EE interfaces were saved in the working
project, independently reopened, and successfully exported. No checkpoint was
created. These are process-manager prerequisites reached from moon initialization;
process construction and callback dispatch remain outstanding.

| PS2 entry | Recovered routine | Cases | Reviewed retained Unity body |
| --- | --- | ---: | --- |
|001005e8|dds3DeleteProcessList|512|1824e0da0 DeleteProcessList|
|00100760|dds3AddProcessList|512|1824e0540 AddProcessList|
|001009a0|dds3StartReadyProcess|512|1824e2420 StartProcess|
|001009e8|dds3StartingProcesses|512|1824e24b0 StartingProcess|
|00101aa8|dds3SetProcessData|256|1824e3900 dds3SetProcessData|
|00101ab0|dds3GetProcessData|256|1824e2a50 dds3GetProcessData|

The low flag nibble selects three head/tail/count records: state 1 at 54e850,
state 2 at 54e868, state 3 at 54e85c. Insertion orders unsigned 32-bit priorities
and places a new node after every existing tie. Removal updates neighboring links
and head/tail, clears previous then next, and decrements the selected count.
Invalid state nibbles leave the node and lists alone. Synthetic count values
exercise increment/decrement wrap independently of actual list lengths.

Startup moves a node through the real removal/insertion routines, retains the
high flag bits, changes the low nibble to 2 and clears starttime/runtime words.
The waiting-list walker decrements only positive signed 16-bit delays, saves the
next node before transitioning the current one, and starts nodes whose delay
becomes zero. Negative delays remain waiting. Process-data setters truncate to
32 bits; getters sign-extend the raw stored word into the full 64-bit V0 lane.

The managed HD process record retains flags 1c, priority 20 and clocks 24/28, but
widens startup/shutdown delays from PS2 halfwords 2c/2e to managed ints 30/34.
PS2 callback/data/link slots 30/34/38/3c/40 become managed delegate/object/link
fields 38/40/50/58/60. HD takes managed ref IDs and adds null/class checks. Its
unlink and insertion store order also differs. The HD ready mask fffffff2|2 is
equivalent to the PS2 mask fffffff0|2; this is not a behavior difference.
Recovered names describe reviewed logical counterparts, not proven original
PS2 source spelling or typedefs.

The comparisons execute all transition callees without interception and compare
all 4,132 declared RAM bytes, raw argument high lanes and full getter results.
Fixtures cover all flag nibbles, empty/single/multiple lists, head/middle/tail
removal, unsigned priority boundaries/ties, count wrap and positive/zero/negative
delays while moving multiple waiting nodes. Ordinary disjoint backed lists are
the tested domain. Arbitrary aliases, malformed cycles, callback scheduling,
Unity runtime equivalence, physical PS2 runtime and matching binaries are unproved.
Recorded emulator PCs omit branch delay-slot PCs because a step executes those
within its branch; they are not a separate complete-instruction coverage metric.

DDS static body matches are 001006e0 removal, 00100858 insertion, 00100a98 ready,
and 00100ae0 waiting traversal. All three connected calls agree. The nine masked
GP displacements consistently map Nocturne a6e0..a700 to DDS 9b10..9b30 in
four-byte steps, preserving the three adjacent head/tail/count records. This is
a symbolic layout constraint; no absolute DDS GP base or uniform code relocation
is inferred. The data getter has one body candidate 00101a70. The setter has two,
00101a68 and 0016a220, so its DDS identity is unresolved. DDS source/runtime
equivalence remains untested.

Constructor 001015b0 and moon initialization 001eafb8 are now integrated with
1,536 passing cases; see [creation findings](process-creation-findings.md).
Continue through the remaining moon callbacks and process dispatch. Moon process
initializer 001eadd8 loads six PS2 texture handles, whereas the retained Unity
initializer only creates managed data; retain that port difference. Dispatcher
00100a48 requires actual callback/state evidence before full process-manager
recovery can be claimed.

Evidence: [source](../src/process_lists.c),
[validation](process-lists-validation.json),
[reopened interfaces](process-lists-abi.json),
[HD review and layout](process-lists-matches.json),
[DDS matches and constraints](process-lists-transfer.json).
