# PCP effect cleanup and shared resources

`src/effect_leaf_release.c/h` adds 50 complete original routines: 37 selected
PCP destructor targets and 13 resource helpers. All 3,200 original-instruction/C
comparisons pass, covering 2,508 summed original body bytes and every one of
the 511 main instruction addresses. The affected C builds with warnings treated
as errors. The 50 interfaces were saved in the working Ghidra project, checked
after reopening and exported into the current inventory in place.

The comparisons execute 1,753,382 original steps, 7,424 fixed child releases
and 13,996 semaphore calls. Ordered entry traces contain 20,491 calls, including
the tested roots. Full declared RAM, Status, primitives, callee saves and raw
64-bit arguments agree. Independent diagnostic checks cover 108 cases and
4,476 output bytes. There are no uninitialized reads or uncovered main addresses
in this batch. The current rolling evidence is
`effect-leaves-validation.json`; there is no new full-suite run.

## Native behavior

Offsets below are hexadecimal. Fixed arrays read child pointers in ascending
order at +1C, executing actual track-poly cleanup at 001785E8 before releasing
the parent pool slot. Original counts are 8, 12 or 30, with unchecked child
reads and pointer reloads retained. Material, texture, memory-handle, queue and
pool dependencies execute their original behavior rather than callback stubs.

At 00186080, Scatter texture-resource deletion decrements and stores the
reference count at +04. Zero releases texture+00 through the native deferred
queue and then frees the resource pool slot. A starting count of zero wraps;
the native routine has no underflow guard. At 00188DA0, Scatter list deletion
conditionally releases texture+7C, then material+74, handle+78 and its own slot.

Needle cleanup at 0018A070 tests handle+68, prints the retained diagnostic at
00533C90 when nonzero, reloads the handle and frees it. Its caller at 00189B68
releases material+6C first, invokes that cleanup, then frees handle+70.

Shared Needle deletion at 0018E000 releases its own slot first, decrements
0054F1E8 and stores it. At zero it reads the owner at 00551DD0, releases
owner+38 through 001A2098, rereads the owner and releases its pool slot. The
global owner pointer is not cleared. Distinct original helpers with identical
bodies remain distinct recovered functions.

## Discovery and Unity evidence

Original table targets 0018EAF8 and 0018ED10 are real 20-byte pool tails;
00192A90 is a real 8-byte empty routine. They were recognized without overlaps
and exported in place, increasing the recognized inventory from 8,975 to 8,978.
Their original instructions are included in the passing comparisons.

Three named Unity roles are reviewed:

| PS2 | Unity address | Retained role |
|---|---|---|
| 00186080 | 1825484C0 | dds3ScatterPolyListTexResourceDelete |
| 00188DA0 | 182547770 | dds3ScatterPolyListDelete |
| 0018A070 | 182545280 | dds3NeedleModelVNCListDelete |

The Needle diagnostic independently agrees with the HD StringLiteral cell
182E91C90 in `pc/il2cpp/script.json`. Managed layouts, guards and Unity mesh
destruction differ from the PS2 ownership implementation. Individual effect
variants retain descriptive native aliases. The `effPart` initializer at
18276DAF0 still times out after a 180-second decompiler attempt; its failed
metadata and log are current, and no complete delegate-name mapping is claimed.

## Transfer to DDS

Forty-nine selected complete spans resolve, constrained by the unique original
DDS table at 00353880 corresponding to Nocturne's 0031DF90. The inspected
prefix has 65 records of 40 bytes, with delete at +08. Fifty selected table
constraints and 98 callee links agree. Neither full table extent nor runtime
selection is established.

Shared Needle's complete span differs only at four reviewed GP-relative
immediates and relocated call targets. The ELF GP bases agree with the decoded
addresses: counter 0054F1E8 maps to 003BB048, and owner 00551DD0 to 003BD7FC.
Repeated loads and stores refer to the same respective globals.

Two behavioral variants are recorded separately in `effect-leaves-transfer.json`:

- Needle cleanup 0018A070 maps through its complete incoming caller to DDS
  00177048. DDS's 44-byte body omits the diagnostic from Nocturne's 80-byte
  instruction span; it null-tests handle+68 and frees it. This is excluded from
  the 49 complete matches.
- The existing texture dependency 002AB8F0 maps through the Scatter call to
  DDS 002D2D00. Nocturne's 28-byte wrapper unconditionally appends to its queue.
  DDS's 68-byte body null-guards the texture, decrements its associated count,
  clears texture+20 only at zero and appends to queue 003BD9F0. It is not a
  complete-span equivalent dependency. Static caller correspondence does not
  imply equivalent ownership across the games.

## Integrated progress and remaining work

At this batch, recovery reached **1,360 / 8,978 recognized functions (15.148%)**,
**659,322 aggregate comparisons** and **193,612 summed original body bytes**.
The last full run remains 413 functions /462,684 cases; 947 additional routines
contribute 196,638 focused cases. All 100 registered focused reports refer to
current source. There are 619 reviewed HD counterparts, 46 library identities,
738 descriptive PS2 aliases and 273 shared transfer signatures.

At this batch the effect-table audit had 19 unrecovered unique targets and no
unexported targets in its inspected records, down from 56. The selected
camera/model lifecycle graph still has ten direct bodies /1,440 bytes remaining.
Subsequent [recursive effect recovery](effect-recursive-findings.md) closes
eighteen of those targets; model/camera lifetime and indirect ownership are next.
Physical rendering, scheduling, PS2 runtime execution,
DDS execution and matching-binary validation remain outstanding. Recognized
function coverage is not proof of complete executable discovery.
