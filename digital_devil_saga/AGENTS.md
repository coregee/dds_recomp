# Disassembly workflow

This repository is for reverse engineering the Digital Devil Saga executable (`game/SLUS_209.74`). The primary goal is to identify as many executable functions, function signatures, parameters, return values, local variables, globals, and useful data structures as the evidence supports.

## Breakpoint loop

The user drives PCSX2 and supplies the action that triggered a breakpoint. Treat the paused emulator state and that action as the starting point for each investigation.

1. Use the PCSX2 MCP connection/status tools to confirm the current session is paused at the expected breakpoint. Check the game/image when identity is uncertain.
2. Read the EE registers (including PC, SP, RA, argument and return registers), the relevant stack words, and memory pointed to by plausible arguments or state pointers. Use PCSX2 MCP `read_registers`, `read_memory`, `evaluate`, `disassemble`, and `get_backtrace` as appropriate.
3. Inspect instructions around the PC and callers/callees as needed. Compare the live values with the user's description of the action. Use Ghidra MCP to inspect static disassembly, decompilation, cross references, and existing names when it helps interpret the runtime state.
4. Report the address and the specific observations that support each proposed function purpose, signature, variable, or structure field. Separate directly observed values from inferred meanings, and mark uncertain names or types as hypotheses.
5. Ask a focused follow-up question or request another user-driven breakpoint when one snapshot cannot distinguish plausible interpretations. Suggest the exact action or breakpoint that would resolve the uncertainty.

Keep each pass quick and scoped to the supplied breakpoint. The user controls gameplay, breakpoint setup, and when execution resumes. Do not step, continue, load a state, alter guest memory/registers, or change breakpoints unless the user asks for it in that investigation. Do not claim a function's role from a single hit when the evidence only identifies a candidate.

## Recording findings

Use stable executable addresses when discussing symbols. Check existing Ghidra names before proposing replacements. When a finding is strong enough to record, update the Ghidra program with the supported name, prototype, variable, or comment; preserve uncertainty in comments rather than encoding a guess as fact. Save the program after edits. `analysis/ghidra-annotations.tsv` is the Git-friendly export of user annotations; `tooling/ghidra/snapshot.ps1` creates that export and a restorable GZF backup after the Ghidra program is saved. See `README.md` for the snapshot command.
