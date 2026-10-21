# Console source recovery

Six additional routines are integrated in `src/dev_console.c` and compile as
C11 with `/W4 /WX /O2`. The actual recovered DLL passes **1,536 focused original
instruction comparisons**,256 per routine. Ghidra annotations are saved in the
working project; independent reopening checks all six interfaces, including the
fifth argument in t0. All six selected exports decompile with zero failures.
The recognized inventory remains8,956.

| Original entry | Recovered routine | Body bytes | Identity |
| --- | --- | ---: | --- |
| 002bd300 | sdfDevSetPrintAttr | 24 | Reviewed sdfDevCons HD counterpart |
| 002bd318 | sdfDevSetPrintCB | 40 | Reviewed sdfDevCons HD counterpart |
| 002bcad0 | ps2DevFinalizeGlyphPacket | 112 | Descriptive PS2 alias |
| 002bc680 | ps2DevUnlinkConsole | 40 | Descriptive PS2 alias |
| 002bc6e0 | ps2DevClearConsole | 52 | Descriptive PS2 alias |
| 002bc7e0 | ps2DevAdvanceConsoleLine | 140 | Descriptive PS2 alias |

Current integrated recovery is **436 functions /49,208 summed original body
bytes (4.87% of recognized functions)**. The last full run remains413 functions
and462,684 cases. Three focused groups add23 routines and5,888 cases, bringing
the aggregate to **468,572 cases**. This is not a new full-suite run. The ledgers
now contain256 reviewed HD counterparts,46 library identities,177 descriptive
PS2 aliases and125 transfer patterns. Full or near-full executable recovery
remains unfinished.

The two print setters retain Unity's x/y/z/attr fields, shifted by the managed
object header: PS2 offsets0/4/8/0c correspond to HD10/14/18/1c. PS2 writes x,z,y
then tail-calls the actual attribute setter; HD writes x,y,z and adds managed
null/bounds guards. PS2 color indexing uses low-word SLL/ADDU wrapping, so the
recovered source does not substitute the HD array-bound behavior. The raw EE
verification interfaces do not claim original source typedefs or symbol spelling.

The packet finalizer preserves signed word subtraction/shift, odd-count alignment,
signed division by5 and the sign-extended quotient OR. Tests include negative raw
count bits and aliases between handle and packet. Console unlink reads both links
before writing neighbors or the head. Clear and scroll retain signed halfword
dimensions, ordered cursor changes and actual recovered memmove/memset calls.
The original probe executes those memory routines, supplying only instruction
values for opaque PCPYH/PCPYLD operations; it does not replace the game/library
functions with host memory operations.

Each comparison checks **12,320 declared memory bytes**, including separate
backed high-address storage.124 clear cases confirm the original sign-extended
64-bit pointer return. Fixtures cover zero and nonzero clears, signed dimensions
and cursor values,87 scroll paths,169 increment paths, color/control aliases,
packet/handle aliases, list self/global aliases and high argument lanes. Synthetic
backed color storage extends beyond Unity's15-entry array; those cases test PS2
address arithmetic and do not claim an HD index domain. Arbitrary invalid
dimensions, unbacked addresses, physical address aliasing, whole text rendering,
PS2 hardware and matching executables remain outside these comparisons.

Read-only DDS inspection provides a concrete transfer lead. Nocturne002bd300
matches the unique DDS002e49e8 body except two table relocations; Nocturne002bd318
matches DDS002e4a00 except its tail jump. The DDS tail target is002e49e8, and all
15 original color words match the DDS table at003987e0. `dev-console-transfer.json`
records checked executable hashes and these independent constraints. DDS source
comparison, annotations, runtime behavior and original symbols are unproved.

Current results are `dev-console-validation.json`, `dev-console-interfaces.json`,
`dev-console-abi.json` and one rolling original capture under `dev-console/`.
No checkpoint, project copy, source freeze or duplicated capture was created.
The full HD/PS2 ranking queue was refreshed with the two new reviewed anchors.

Continue the actual console renderer002bcfd0 through its glyph/background packet
builders, double-buffer initialization and DMA/sync dependencies. The real draw
consumer002adb98 and cleanup002aadc8 remain larger connected targets.
