# Native typed kouka packets, 2026-10-12

Twenty-seven complete routines (3,084 recognized body bytes) now compile and
pass 4,864 comparisons against original PS2 instructions. All 669 selected main
instruction addresses execute. The selected bodies are dependencies of state18's
CHECK1 completion path; this closes packet prerequisites without claiming the
outer callbacks or packet execution. All27 working Ghidra interfaces are saved,
independently reopened and checked, with current exports merged in place.

## Packet constructors and composites

The source in `src/battle_kouka_packets.c` uses the actual recovered name-search,
process-data lookup,64-byte allocator and linked append. It adds23 constructors
for native kinds6/8/9/10/17/19/20/24/25/27/33/36/38/45/46/47/48/49/52/53/56/57/58,
plus two composites and two list helpers. Native kind numbers are distinct from
BF command IDs. The [reference review](battle-kouka-packets-matches.json) checks
the named Unity role and kind literal for every one of the23 constructors.
Managed pointers, unique IDs and extra guards are recorded as differences.

Construction retains the native word/halfword stores and their order. For
example, PadShock fills halfwords+28/+2A/+2C. Native death-event construction
clears main+40, stores its form, reads the packet's initialized+28, writes main+44
and+88, then replaces packet+28. Backed aliases make that order observable;
the C implementation does not substitute a guessed value for the live read.
All constructors preserve the base allocator's uninitialized final16 bytes.

Fade-in executes three actual constructors: color kind5 at the initial frame
with time0, home-alpha kind8, then home-color kind6 at the sign-extended32-bit
sum of initial frame and delay. The fly composite executes its actual kind45
constructor before returning1. The copied native body alone is insufficient
to identify that tiny composite in DDS:27 generic wrapper spans fit its shape.

## Register interfaces and sound-list behavior

Damage-motion, easy-damage and bad-damage constructors receive their float parameter through
F12, followed by integer arguments in A0 onward. The original pseudocode had
misclassified this first argument. Their saved interfaces now specify float32
in F12 and raw64 integer registers. The canonical C functions accept float;
host-only adapters copy test words without converting them through Python
floating-point values. Signed zero, infinity, NaN, subnormal, large finite and
random input words are compared as exact stored bits. These routines copy their
float inputs; no motion-ratio arithmetic or physical animation is claimed.

`nbOnOffKoukaPacketFlag` gets the original main process's kouka handle. A null
handle skips lookup. Each packet's signed kind byte compares to the complete
raw64 argument; enabled also tests the complete argument, while mask stores
only the resulting low byte. The successor is captured before writing flags.

`nbCheckSePacket` uses signed LH frame values and the sign-extended32-bit
SUBU result of frame-window. Both comparisons use signed64 values. Only kinds
25/28/29 qualify; their sign-extended sound word compares to the complete raw64
sound argument. Consequently, matching low32 bits with different upper lanes
need not suppress a duplicate. The native upper frame bound is inclusive and
the lower bound exclusive. `nbAddSePacket` runs that real query before allocating.
The comparison includes128 connected first-sound/second-sound cases, covering
suppression and the exact lower-window boundary.

Dead PCM construction uses actual unit-work lookup from the visual form's signed
halfword+92, not a managed visual object or a substituted party pointer. Missing
work suppresses allocation; native work+E masked byFFF equal to200 selectsFF,
otherwise work+4 supplies the unsigned halfword. Negative form indices and the
separate>=16 unit-work route remain native behaviors in the source and inputs.

## Community and cross-game evidence

The pinned [randomizer build notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
provide USA-build/file-offset context. The DDS community's
[source-unit research](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/docs/tu-names.md)
reports substantial battle-code rewrites, so packet layouts and subtype handling
are checked through native consumers rather than inferred from engine ancestry.
Inspected revisions and content hashes are retained in the reference review.

The [complete-span transfer report](battle-kouka-packets-transfer.json) resolves
no selected complete DDS counterpart. It retains the27 ambiguous fly-wrapper
shapes and rejects the generic `Admini` getter as a kouka identity. The prior
two-bank destructor transfer remains separate evidence; it does not justify
transferring this whole packet subsystem. Shared fingerprints are recorded as
leads for other SMT PS2 executables, with these limits retained.

## Validation and next work

[Native comparisons](battle-kouka-packets-validation.json) execute1,109,961 steps
and check full declared RAM, raw64 returns, Status, CPU primitives, defined
floating/vector state and inherited callback traces. Actual allocation reaches
the last slot of a pool page. Cases cover empty/nonempty lists, byte-kind
branches, signed frame boundaries, word overflow, dirty upper arguments, missing
work, partial initialization and selected backed aliases. Finite lists and
bounded allocations are tested; arbitrary corrupt ownership is not.

[Affected comparison evidence](battle-kouka-packets-regressions.json) checks
another2,176 existing completion/cleanup cases against the rebuilt host. Current
source, verifier, DLL, input and vector hashes are checked without copying old
captures. No new full-suite run or physical gameplay is claimed. Next recover
the remaining CHECK1 dependencies and both outer callbacks, then actual message
progression and actor selection. The goal remains full or near-full executable
recovery, with current files and rolling outputs rather than checkpoints.

The current action graph has432 unresolved bodies /96,948 bytes. State18 CHECK1's
direct closure has46 pending bodies /10,184 bytes after these prerequisites;
additional indirect dependencies may expand it.
