# Packed VM arithmetic and conditional control

Fifteen complete original routines are integrated in `src/script_ops.c`, adding **2,216 recognized body bytes**. They comprise the binary operator, twelve operator wrappers, Not and If. All **441 non-delay root addresses** are reached. The focused report passes **2,560 instruction/C comparisons**: 2,432 for the new routines and 128 connected programs through the previously recovered trace loop. The build passes with warnings treated as errors; sixteen interfaces were saved in the working Ghidra project, reopened and exported in place.

All **35 original opcode handlers** now have compiled recovered source and execute through the actual original dispatch table in the connected tests. This completes the opcode bodies, not the broader scripting system: construction, scheduling and most command callbacks remain unfinished. The aggregate executable recovery is **878 / 8,956 functions (9.80%)**, **579,927 comparisons**, and 136,676 summed original body bytes. No new full-suite or physical PS2 run is claimed.

## Original behavior

The binary helper saves both signed-byte tags into GP globals and selects integer operations only when both tags are 0 or 2. It pops the top value first, stores it at 0x551C58 or 0x551C64, then pops the lower value into 0x551C5C or 0x551C68. Subtraction, division and ordered comparisons preserve that operand order. Tags 4, 5 and unknown tags enter the float-pop path; that pop helper returns zero for those tags.

Operations 0..11 are add, subtract, multiply, divide, boolean OR, boolean AND, equal, unequal, less, greater, less-or-equal and greater-or-equal. Integer arithmetic wraps in 32 bits; division uses signed word operands, including minimum-integer divided by -1. Integer zero divisors execute the original BREAK7. Operation selection checks the full 64-bit input; invalid values still pop both operands and push the previous integer or float result global. Tests include high-word values whose low word resembles a valid operation.

Float arithmetic uses the checked raw EE instruction-value primitives. Boolean OR/AND execute the actual recovered software-float widening and software-double comparison helpers, with their original short-circuit order. Hardware comparisons and those software helpers remain distinct operations. Boolean and comparison results push integer tag 0; arithmetic pushes float tag 1.

Not handles integer tags 0/2 and float tags 1/3, replacing the value with integer zero/one; tag 4 and unknown tags leave the stack unchanged and advance CP. If consumes tags 0..3 and advances CP on true. False, tag 4 and unknown tags branch to a label record at work+0xB8, stride 32, target +0x18; unsupported tags are not popped. All wrappers reload CP after the complete operator call and then advance it.

## Comparisons and connected evidence

The new comparison boundary flushes exponent-zero magnitudes, equates signed zeros and preserves signed-magnitude ordering of exponent-255 payloads. It matches all 160 locally pinned [published ps2autotests comparisons](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/ee_fpu/compare.expected), including 120 EQ/LT/LE cases and 40 false-predicate cases. Earlier fixture evidence explicitly records four disagreements for an exponent-255 clamping policy. No clamping policy is substituted here.

The original eight comparison instruction sites are decoded from executable bytes and execute a scoped instruction primitive in the probe, updating FCSR condition bit 23. The C provider and original-instruction path agree on that bit. Other FCSR arithmetic/conversion flags and traps remain outside the value-model scope; the processor language installed on the system is unchanged.

The cases execute **827,371 original instruction steps**, **10,864 actual indirect calls**, **1,200 comparison instructions**, and **20 integer divide-by-zero exceptions**, including four complete-program exception paths. Returning calls check full declared VM RAM, defined raw64 results, Status, integer/floating callee saves, condition bit 23 and indirect target/order/raw arguments. Exception cases compare observable RAM and the original BREAK7 boundary, without inventing a return or callee-save guarantee. No game function returns are substituted.

Fifteen HD semantic counterparts are reviewed, including `CodeFunc_2Operation` and `CodeFunc_IF`. Managed checks, aborts, IEEE encodings, static-object layout and obfuscated constants differ; the PS2 instructions determine recovered behavior.

## DDS transfer and remaining work

All fifteen new complete spans and the existing trace loop resolve in DDS. The binary helper at Nocturne 0x10AB48 corresponds to DDS 0x10C9A8, constrained by twelve independently matching wrapper calls. There are forty agreeing direct-call links and 105 decoded GP loads/stores in the enhanced report. Eight operator temporary globals consistently relocate to DDS 0x3BD76C..0x3BD788.

Previously recovered Comm and Minus also gain complete constrained matches. Their opcode-table positions, GP addresses, the minus switch table and three common command descriptors agree. Across this and prior groups, all 35 opcode targets now have checked complete DDS spans. Seven switch tables preserve all 49 relative arm targets; the 35-entry opcode table relocates from Nocturne 0x2FA528 to DDS 0x329930. SYNC/WAIT/SEL_JMP descriptor IDs and argument counts agree; other game-specific command-table contents are not claimed equivalent. Static transfer is not DDS execution proof.

Current evidence is in `script-ops-validation.json`, `script-ops-matches.json`, `script-ops-transfer.json` and `script-ops-abi.json`. `script-ops/` holds one rolling fixture/vector set and input manifest. Continue with the callers of `ps2ScriptTrace`, script-work allocation/initialization and process scheduling, then recover command families through those connected paths. Arbitrary malformed scripts, physical execution and a matching rebuilt executable remain unproved.
