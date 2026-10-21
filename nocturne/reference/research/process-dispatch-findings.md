# Process dispatch and merged traversal

Two integrated C routines cover 800 original body bytes and pass 1,536 focused
original-instruction comparisons. The shared host DLL builds with warnings as
errors. Their interfaces are saved in the existing working Ghidra project,
independently reopened and exported; all evidence files are rolling outputs.

| PS2 entry | Recovered routine | Cases | Retained HD counterpart |
| --- | --- | ---: | --- |
|00100a48|dds3RunProcess|1,024|1824e19b0 RunProcess|
|00100c48|dds3RunningProcess|512|1824e1ed0 RunningProcess|

RunProcess returns1 immediately when flag20 is set, preserving the existing
current-process word, input outputs and clock. Otherwise it stores the low32
process address at54e874 before preparing input. Flag10 clears64 pad bytes at
2f5810 and12 control bytes at54e908/54e910. Without that flag it copies the two
32-byte pad banks from2f57d0 and the control groups from54e8f8/54e900. The PS2
copy/clear loops are inline, with paired loads before stores and original
interleaved control write order retained.

The callback word at30 is loaded with sign extension. Zero and -1 skip invocation.
An invoked callback receives the original full64 process argument. Every nonzero
full64 return replaces the callback word with its low32 bits. Only an exact full64
-1 return with low state2 invokes the real EndProcess, clears currentprocess and
returns0. Other cases increment clock28 with32-bit wrap, clear currentprocess and
return1. A callback slot already containing -1 skips without ending the process.
A delayed end returns0 even when the process is moved to state3 and remains alive.

The merged walker compares unsigned priorities20 from active54e868 and ending
54e85c; active wins ties. It saves the selected node's previous40 before dispatch.
Return1 loads that node's next3c after the call. Return0 reads the saved previous
node's live next, or reloads the respective root when previous was zero. When one
side is exhausted, the original drains the other side without reconsidering new
nodes on the exhausted side. A newly ending process therefore is not guaranteed
to be visited in this same pass. This is preserved rather than replaced with a
fresh merge after each callback. Its original body is288 bytes in a292-byte span
with one alignment hole; the static search retains that hole.

Unity retains both logical bodies. HD uses a managed delegate at38 and separate
signed32 func_ans at48 to signal termination; PS2 uses the raw callback return.
HD clears func_ans and includes class/null/bounds checks and ASCII-name calls.
HD PadEi/managed arrays replace the raw PS2 input globals. HD next/prev58/60 map
to PS23c/40, and managed process references replace raw addresses. Managed
shutdown delay and GC differ from PS2 halfwords and explicit pool release.
Names are reviewed logical counterparts; exact source spelling and port
behavioral equivalence are not claimed.

The fixtures execute the actual returning GetProcessData body00101ab0, with
zero, positive, sign-extended negative and -1 data returns. They execute actual
Run/End/list/pool bodies, recursive child/grandchild shutdown in direct dispatch,
and the selected empty shutdown callback002b58b8. No callback return value is
supplied by the harness. Across the two groups672 returning callbacks are
observed. Each22-word callback trace compares raw callback/process arguments,
currentprocess and all76 prepared input bytes before entry. The comparisons
check all58,948 declared RAM bytes, raw dispatch results, Status/primitive counts,
21 diagnostic calls and12 real shutdown callbacks. Occupancy covers both lists,
active only, ending only and neither; equal and high-bit unsigned priorities,
clock wrap, skipped/masked/copied input, root reload and saved-previous paths
are included.

Only diagnostic printf002d4748 is intercepted: format/process operands are
checked, but original formatter/FILE effects are excluded. CPU primitives use
synchronous value models, not physical scheduling. The selected read-only
returning callback does not exercise arbitrary callback changes to state/links,
including the ending-side return0 fallback, or arbitrary64 return values beyond
sign-extended32 data. Those source branches are reconstructed from instructions
and HD control flow, but are not claimed as callback-integration test coverage.
Malformed cycles/membership, arbitrary aliases, all callback targets, PS2 runtime,
HD runtime equivalence and matching binaries remain unproved.

DDS uniquely matches Run00100b40 and Running00100d40. The dispatcher calls the
independently matched End00100ef0; all four merged-walker calls target the unique
Run body. All five edges agree. Every full-span instruction word is exact except
explicit calls, GP loads and listed controller/global address immediates; loop
bounds, bank offsets, flags, node fields and branches are not masked. Paired pad
input003244d0/output00324510 are64 bytes apart, and control input/output pairs
are16 bytes apart. Repeated constructors/displacements agree, including all
three currentprocess stores. DDS GP is not assumed, and no DDS source/runtime
comparison or annotations are made.

Next are real game callback recovery, especially moon texture initialization
001eadd8 and update001e9a80, with their actual loading/rendering dependencies.
General scheduler and formatter boundaries remain outstanding. Full or near-full
executable recovery is unfinished.

Evidence: [source](../src/process_dispatch.c),
[validation](process-dispatch-validation.json),
[reopened interfaces](process-dispatch-abi.json),
[HD counterparts](process-dispatch-matches.json),
[DDS structures and address constraints](process-dispatch-transfer.json).

[Moon callback, original asset and connected LB loader frontier](moon-callback-frontier.md).
