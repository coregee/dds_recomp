# Motion key search and interpolation recovery

The complete original routine at `002b4120` is recovered in `src/motion_key_search.c/.h` and promoted into the saved262-function checkpoint. Its separately preserved draft remains under `analysis/drafts/motion_key_search/`. **All 8,192 original-instruction comparisons pass.** Every one of its **66 owned instruction words /264 bytes** is independently encoded and compared with the immutable ELF. The full address span is272 bytes; two unreachable padding NOPs at `002b41cc` and `002b4204` are excluded from owned body bytes. Both returns, their delay slots, the binary search, branch-likely annulment, signed multiply result and raw interpolation store are included.

## Original behavior and layout evidence

The original ABI is node in A0, raw frame word in F12 and a direct12-byte output in A1. The host draft uses an explicit RAM/base/offset binding; this wrapper is not the original calling convention. Output slots contain raw32-bit previous and next record addresses followed by the raw interpolation result word. Generated pseudocode incorrectly casts that final SWC1 value to an integer.

The node supplies a controller address at+4 and cut address at+8. The cut supplies ushort count at+4, ushort byte stride at+6 and ushort key times at+8. Key data starts after `2*((count+1)&~1)` bytes of times, including even-count padding. The controller loop flag is the byte at+32 and duration is the ushort at+2E. These are accessed field extents, not complete structure/allocation proofs.

CVT.W.S converts the frame to the signed integer used in the binary search. An integer midpoint selects a previous key; before the first timestamp it can select−1, and count0 still performs backed reads around the header. The draft preserves these behaviors instead of adding a clamp, empty-list return, sort or chosen selection. Later it converts the start/delta with CVT.S.W and executes ordered raw SUB.S/DIV.S. Equal timestamps force next=previous and interpolation=raw0. A nonlooping last key uses the same previous/next address; a looping last key uses the data start and controller duration. Arbitrary unsorted timestamp fixtures exercise the same original search, without claiming that unsorted game tracks are valid.

The first output address is stored before the controller pointer is loaded. For a normal next key, the second output address is stored before its timestamp is loaded. For a looping last key, the second store precedes the duration load in a branch delay slot. These orders matter when the output overlaps input fields and are preserved in C. The raw source frame survives unchanged in F12.

## Verification

The inputs cover11 counts (0,1,2,3,4,8,16,31,64,257,512), raw frame edges and random words, zero through256-byte strides, monotone/repeated/equal/random times and14 output locations. Output aliases include the node header/controller/cut slots, controller duration/flag fields and cut header/times. Redirected controller loads remain backed and aligned. Every actual data load is range/alignment checked, including the duration LHU executed inside its branch step.

The 8,192 cases execute5,481 division paths and2,711 zero-delta paths;3,376 last-key paths include2,185 looping and1,191 nonlooping cases. There are4,816 normal next-key paths and745 backed zero-count cases. All66 owned words are covered by pre-step tracing with conditional delay-slot accounting; this is not exhaustive path or input proof. The C comparison checks all8,192 original RAM bytes plus64 canary bytes. Storage restores after both successful calls and an injected failure, and nine malformed rows reject before execution.

The separate EE division prerequisite passes36 pinned published result words,40,000 Java/C model probes and40,036 checks of the actual original DIV.S F0,F0,F1 word at `002b4224`. Its overlapping input/output register and raw operand width/order are verified. Java/C agreement derives from the retained licensed algorithm and is reported separately from published expectations. The model covers values; FCSR exception state, timing and hardware/runtime execution remain outside this validation.

A prepublication capture was discarded and replaced after detecting that Ghidra could retain a full-page fixture array as live backing. The final harness clones the input array before execution, and the verifier independently checks the frozen header/count/stride fields. The original checkpoint was never modified by that capture.

## HD lead and transfer

Native `sdfMotion.sdfMotGetKey` at `1825eccc0` retains the recognizable search/last-key/interpolation algorithm. Managed object headers, arrays, output references, NULL/bounds checks and stride units differ: the HD method multiplies its ushort stride by2, while this original routine uses a byte stride. The identity is now promoted in `function-matches.tsv` after canonical source verification, complete fresh regression and saved ABI reopen.

Transfer candidates for other SMT PS2 games are the even-padded ushort timestamp table, upper-midpoint signed-frame search, direct raw-address key pair plus ratio, and controller loop/duration fields. Re-establish the target ABI, header offsets and units from its instructions before assigning names or transferring the layout.

The preserved key checkpoint contains **262 functions /211,996 passing comparisons (~2.93% of 8,944 recognized functions)**. Every instruction case was freshly captured under the six-operation EE value model; no old rows were reused. The capture checks 141 input hashes before and after execution, and the comparison report pins 65 source and 59 verifier files. The FPU provider passes 208 published result words and 180,000 separately labelled Java/C probes. Comparison correction, FCSR flags, timing and hardware/runtime execution remain outside this validation.

The original 261 checkpoint and its 117 certified source/verifier inputs, language and immutable vectors remain preserved. The new project is `ghidra/checkpoints/262-functions/Nocturne.gpr`, with snapshot `backups/SLUS_209.11-2026-10-05-190030.gzf`, SHA256 `ed116ca9c83e7dfc6beebf49159c3b773a2cce606bd20bb0609e40ab33276e88`. The identity ledger has 249 reviewed HD pairs and the transfer ledger has 70 fingerprints. Next is the real scalar/material callback chain in [motion-material-frontier.md](motion-material-frontier.md).

`motion-key-search-validation.json` pins the C source/DLL, fixture engine, immutable ELF, independently encoded body, native lead, separate division evidence and canonical integrity report. No installed Ghidra processor, live GUI or game execution was changed.

The reopened saved ABI is node A0:4,frame F12:4,output A1:4,void return. The Ghidra output structure types the ratio as float, while C and fixtures preserve its raw encoding. Partial controller33 and cut-header8 views join the direct key-pair12 view. All8,944 recognized functions export/decompile with zero failures. Prior callback, model, PIB and library ABI checks also pass.

The key checkpoint above is preserved historically under `checkpoints/262-functions/`. The current269-function/236,572-case checkpoint adds the real scalar/material caller chain, with8192 original stack key-pair witnesses; see [scalar/material recovery](material-motion-findings.md).
