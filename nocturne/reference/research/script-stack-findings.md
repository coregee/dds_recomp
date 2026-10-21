# Packed VM stack, variables and procedure control

Twenty-two complete original routines are integrated in `src/script_stack.c`, adding 1,644 summed recognized body bytes. The focused report passes **1,472 comparisons**: 1,408 for the new bodies and 64 complete programs through the existing trace loop. All **369 non-delay root instruction addresses** in the new routines are reached. The build passes with warnings treated as errors. The 23 interfaces were saved directly into the working Ghidra project, reopened for verification and exported into the current inventory.

Twenty Unity semantic counterparts are reviewed. `CodeFunc_PushI` and `CodeFunc_Jump` are named leads whose exported native bodies are protected lock stubs; their recovered PS2 identities rely on actual instructions and dispatch-table positions. Exact original source spelling remains unproved.

## Original behaviors retained

Push stores a tag, reloads the count for the value store, then reloads it again for the increment. Tags are integer 0, float 1, return address 4 and string 5. An overlapping test with count -8 makes the value store overwrite the count itself; the final count is the stored value plus one. Count 27 tests overlap with the return tag/value fields.

Float pop decrements the count before reading the original top tag, and reloads the count when locating the value. Tags 0/2 convert integers, 1/3 preserve raw float words, and 4 or unknown tags return zero. This differs from the float argument getter, which converts return-address tag 4 as an integer. Zero-count underflow is included. Mixed A0/F12 push and raw F0 returns use explicit register storage; host C represents the float payload as bits.

Global integer/float arrays are context+0x40/+0x440; local array pointers are work+0xDC/+0xE0. Operand indices are signed halfwords at code-record+2. PushI and PushF consume two records; PushIS consumes one. Float stores advance CP before the store, while integer stores reload and advance CP after it. Tests where the destination aliases CP distinguish these behaviors.

PS2 PushSTR adds the raw work+0xC4 string-table base to the signed operand. The HD port pushes the offset into its managed string representation. PushReg copies return type work+0x3B and value work+0xA8. Procedure records are at work+0xB4 with a 32-byte stride and CP target at +0x18. Call pushes the current CP as tag 4, reloads the operand and enters the procedure; the previously recovered End pops it and resumes at CP+1. Proc and Run only advance CP. HD Run additionally calls its abort helper.

## Connected execution and transfer

Sixty-four finite programs execute all seventeen new opcode handlers through the original 35-entry table at 0x2FA528. Actual call/end/jump/goto paths, immediate/global/local load-store pairs, return-register and string pushes execute. The comparison observes 1,984 real indirect calls and 111,114 original instruction steps across the whole focused group. Declared VM RAM, defined results, Status, callee saves and target/order/raw arguments agree. Original executable tables are retained and actual recovered callees execute without substituted game returns.

DDS has a corresponding 35-entry table at 0x329930. Existing end/goto and complete new opcode-body matches constrain it. All twenty-two new spans and the previously recovered trace loop resolve, with thirteen agreeing direct calls, eight decoded GP loads and equal relative arm targets in both pop switch tables. The prior integer-pop dependency is also constrained. Proc and Run have identical bodies; their distinct table positions identify their roles. Remaining arithmetic/conditional table targets are leads, not recovered source or validated DDS execution.

## Evidence and limits

- `analysis/script-stack-validation.json`: focused comparison and instruction coverage.
- `analysis/script-stack-matches.json`: reviewed HD roles and the two explicitly unreviewed protected bodies.
- `analysis/script-stack-transfer.json`: complete spans, original opcode/switch tables, GP and callee constraints.
- `analysis/script-stack-abi.json`: reopened working-project register interfaces.
- `analysis/script-stack/`: one rolling fixture/vector set and input manifest, overwritten on subsequent runs.

Float conversion checks use the previously validated EE value-only RTZ primitive; FCSR flag/trap behavior is outside this comparison. Tests cover backed ordinary and selected overlapping layouts and finite programs. Arbitrary malformed scripts, remaining arithmetic/conditional opcodes and the broader command set, script process construction/scheduling, physical PS2 execution and a matching rebuilt executable remain unfinished. The latest aggregate is **863 / 8,956 functions (9.64%)**, **577,495 comparisons**, with no new full-suite run claimed.

Continue with binary operator 0x10AB48, its twelve wrappers, Not and If; then connect script construction and scheduling.
