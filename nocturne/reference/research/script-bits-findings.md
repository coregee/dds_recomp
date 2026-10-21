# Native bit commands and an original negotiation procedure

The three common bit commands now have complete compiled PS2 source: `scrCommand_BIT_CHK` at `0010B888`, `scrCommand_BIT_ON` at `0010B8B8`, and `scrCommand_BIT_OFF` at `0010B8E0`. Their original command-table slots are 7, 8 and 9, each with one argument to pop. They read integer parameter zero, invoke the existing event-bit checker/setter/clearer, and return one. Only BIT_CHK publishes an integer result through the VM's return register.

The named Unity methods confirm these roles and their callees. HD BIT_CHK adds a configuration-bit-9 override for one protected index; that branch does not exist in the PS2 wrapper. HD event-bit setting also adds achievement handling. Neither feature is imported into PS2 source.

The rolling original-instruction capture has **512 passing comparisons**: 128 direct calls per wrapper and 128 interpreter programs that set/check/publish, then clear/check/publish a bit. The actual parameter getter, event-bit routines, integer-return setter, stack, command and opcode bodies execute. Full declared RAM, raw 64-bit results, ordered indirect calls, Status and callee saves agree; all **22 non-delay wrapper instruction addresses** are reached. Direct cases cover literal/global integer and float parameters, return-address tags, unknown tags, bit-word boundaries and backed negative indexes -1..-31. Other invalid indexes, conversion flags/traps and PS2 runtime behavior remain unproved. All three working-project interfaces were saved, independently reopened and re-exported in place.

DDS full-span matching initially leaves 11 BIT_CHK and 29 ON/OFF candidates. Complete checked callees constrain these to **0010D6E8, 0010D718 and 0010D740**, respectively. Every original instruction word agrees apart from explicitly relocated calls and GP displacements; decoded ELF GP bases and the previously anchored current-work/global-work pointers agree. Seven wrapper-to-callee links and five complete callee bodies support the identities. This establishes static shared-engine evidence, not DDS execution.

The same recovered interpreter also executes the unchanged shipped `game/dds3/nego/script/NegoMain.bf` procedure 3, **plan_compati**. Its control flow stays within code PCs 679..1060 and uses nine opcode types with no commands or procedure calls. All 144 combinations of local integers 18 and 19 pass against the original EE interpreter, collectively reaching **all 382 script instructions**. The capture executes 266,960 native steps and 4,592 actual opcode calls. Entire BF bytes remain unchanged. Work/section pointers are prepared in backed RAM; this selected-procedure experiment does not claim a complete loader-to-negotiation gameplay run.

For local 18 in 0..3 and local 19 in 4..13, the procedure stores zero to global integer 12 and either zero or 100 to local integer 20:

| Local 18 | Local 19 values producing zero | Other values in 4..13 |
|---|---|---|
| 0 | 10 | 100 |
| 1 | 4 | 100 |
| 2 | 8 | 100 |
| 3 | 7, 8, 13 | 100 |

Inputs outside those ranges preserve both prior result words. The test varies their initial contents and checks this independently of the interpreter comparison. The meanings of the two inputs and result fields are not promoted from the procedure name alone.

Evidence: `script-bits-validation.json`, `script-bits-matches.json`, `script-bits-transfer.json`, `script-bits-abi.json`, and `script-procedure-validation.json`. Production source is `src/script_common_bits.c`; the reproducible runners are `tooling/recover_script_bits.py` and `tooling/run_shipped_script_procedure.py`. These runs update rolling outputs and create no checkpoint or backup.
