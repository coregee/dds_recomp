# Packed script VM and dispatch

Eighteen additional routines compile and pass 1,152 original-instruction/C
comparisons, covering all 289 non-delay root instruction addresses and 1,412
recognized body bytes. The capture executes 21,484 original steps and observes
212 actual indirect calls. The existing six VM/movie-script routines also pass
their affected 768-case comparison after the host address binding change.
Annotations are saved in place and the current whole-program exports are merged.

Recovered source is in src/script_core.c, src/script_core.h and src/script_fpu.h.
The current interfaces, validation, reference review and transfer evidence are
script-core-interfaces.json, script-core-validation.json,
script-core-matches.json and script-core-transfer.json.

| Entry | Recovered routine |
| --- | --- |
| 0010b690 | scrGetFloatParaBits |
| 0010b748 | scrGetStrPara |
| 0010b7d8 | scrGetLabelCodeAddress |
| 0010b800 | scrSetCodePointer |
| 0010b820 | scrGetCommandTimer |
| 0010b830 | scrGetMessageHandle |
| 0010b840 | scrGetScriptHandle |
| 0010b848 | scrGetData |
| 0010b858 | ps2ScriptSkipRequested |
| 0010b940 | scrCommand_SYNC |
| 0010b960 | scrCommand_WAIT |
| 0010bb78 | scrCommand_SEL_JMP |
| 0010a380 | scrPopInt |
| 0010b110 | scrCodeFunc_Minus |
| 0010a998 | scrCodeFunc_Comm |
| 0010aa38 | scrCodeFunc_End |
| 0010ab18 | scrCodeFunc_Goto |
| 0010b520 | ps2ScriptTrace |

The current work pointer is 00551c78. Its packed fields are CP+18, stack count+1c,
type bytes+20, values+3c, labels+b8, code+bc, message handle+cc, total timer+d0,
command timer+d4 and user data+f0. Labels occupy 32-byte records with the target
CP at +18. Code records contain signed 16-bit opcode and argument fields.
Integer/pointer loads return sign-extended raw64 values; all word addressing and
increments preserve original 32-bit wrap.

The float getter returns raw F0 bits: tags 0/4 convert a signed integer, tag 1
passes the raw word, and tags 2/3 select the global integer/float tables. Invalid
tags return positive zero. String arguments accept only tag 5 and return the
raw sign-extended slot word. PopInt decrements the count before inspecting the
original top type and reloads the new count for value addressing; zero-count
underflow cases preserve this behavior. Unary minus negates integer words or
invokes the original EE float-negation primitive. Tag 4 and unknown tags leave
the operand unchanged while still advancing CP.

The dispatcher reads the original opcode table at 002fa528. A zero opcode result
clears the command timer and returns two. Result two increments both timers and
returns one. Result one clears the command timer and continues interpreting;
other nonzero results continue without that reset. The recovered loop retains
indirect invocation and does not substitute callback results.

The command opcode publishes its work pointer and reads the original eight-byte
function/argument-count descriptors at 0052e350. A zero command result yields
two without popping arguments. A nonzero result reloads and subtracts the
descriptor's argument count, then advances CP only if the callback left it
unchanged. SYNC tests a nonzero command timer. WAIT completes immediately for
a nonpositive delay, otherwise compares the signed timer with a freshly reloaded
argument. SEL_JMP reads the selected label and can change CP; its original
descriptor consumes eight arguments. End pops a return address and adds one,
or returns zero when the stack is empty. Goto loads the label target directly.

Finite test programs execute real negation, goto, end, command, SYNC, WAIT,
selected-label jump and movie draw-check bodies. Original table data remain
unchanged. Full declared RAM, defined return values, Status, integer/FP callee
saves and ordered indirect targets/arguments agree. Independent checks cover
conversion results, fields, label addresses, pointer returns, counters and stores.
Unimplemented opcode/command targets are explicitly rejected by the host test
binding; the recovered EE-side dispatcher retains the original indirect calls.
This does not claim recovery or execution of every opcode in the table.

Generic Ghidra FLOAT_NEG canonicalized exponent-255 payload bits in an early
comparison. The original EE NEG.S raw value flips bit 31, as supported by the
[pinned PCSX2 interpreter](https://raw.githubusercontent.com/PCSX2/pcsx2/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/FPU.cpp).
The probe checks the two exact NEG.S f0,f0 opcodes before applying that processor
value primitive. Eighteen such instructions execute in the passing capture.
The canonical source uses a dedicated EE instruction boundary, with the host
provider modeling only the result. CVT and NEG floating-point status flags,
exceptions, physical scheduling, PS2 runtime and matching binaries remain unproved.

Sixteen named HD semantic counterparts are reviewed. Managed bounds/null checks,
abort paths, arrays/delegates and layouts differ. The string port constructs and
decodes a managed string rather than returning the PS2 raw slot word. The minus
reference contains obfuscated return constants and abort paths; its reviewed
type/arithmetic/advance role does not establish complete native byte equivalence.
Skip and the main dispatch loop retain descriptive PS2 aliases.

Ten new routines have complete DDS counterparts. Complete WAIT, skip, selected
jump and end callers anchor otherwise ambiguous helpers. Original ELF REGINFO
GP values then permit narrow address masking: Nocturne current work00551c78 maps
to DDS003bd78c, and global context0054ea20 maps to DDS003baa00. All other words
agree across the full contiguous spans. Five-entry PopInt and integer-argument
jump tables have identical relative arm targets. This additionally resolves the
already recovered integer getter0010b5c8 to DDS0010d428. SYNC's eight initial
generic candidates reduce to one through the agreed timer callee. The report
contains ten callee constraints, eight decoded global loads and two checked
jump tables. Missing float/string/handle/dispatch matches remain explicit;
static DDS transfer does not establish DDS execution equivalence.

Next recover the push/return-stack helpers, remaining load/store opcodes and
binary operator dispatcher0010ab48, then connect the VM to its script-process
construction and scheduling callers. The whole executable remains unfinished.
