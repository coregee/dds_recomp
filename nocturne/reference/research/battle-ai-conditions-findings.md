# Native battle AI predicates and community query commands

Fifty-eight complete native C bodies in `src/battle_ai_conditions.c` and `.h`
compile with warnings treated as errors and pass **10,048 original-instruction
comparisons**, executing **2,618,604 steps**. All **1,361 selected main
instruction addresses** execute. The batch adds **6,844 recognized
body bytes**: 27 unique callbacks, two support-condition helpers, the packed
condition dispatcher, its script bridge, three cost/party-level dependencies,
and 24 command wrappers.

Full declared RAM, defined raw64 returns, Status, FCSR condition, CPU primitives,
ordered VM/predicate/libc traces and returning native callee saves agree. The
**192 connected interpreter programs** check **1,826 VM calls**,
**4,439 predicate callbacks** and **3,315 C.LT.S comparisons**. There are
**56 original BREAK7 observations**. Another **36,301 affected existing cases**
pass using the retained captures; those rechecks add no aggregate case credit.

## Original tables and restored code

The original callback table is RAM `004F0788`, ELF file `003F1788`, immediately
before the embedded AI BF at RAM `004F0800` / file `003F1800`. Its inspected
120-byte domain contains 30 slots: 0/29 are null, 28 are nonzero, and 4/21
share the incrementing check-counter callback. Those 28 slots resolve to all
27 native callbacks in this batch.

The two original Hojo switches at `00285C48` and `00285D30` previously had
incomplete Ghidra ownership. Their original 18-entry tables at RAM `00545740`
and `00545790` / file `00446740` and `00446790` now have complete disassembly,
references, ownership and decompilation. Owned body sizes expand from 56/64 to
224/400 bytes; each contiguous span includes one unowned padding NOP. Original
body/table hashes and case domains are checked. The function inventory stays
8,979. This repair is saved in the working project without a project copy.

## Native behavior

- `nbAiChkJoken` extracts type with word SRL and the argument with low16 ANDI.
  Type0 returns1 without clearing the mask. Other types load the actual original
  callback, clear context+190 in the actual call delay, and execute it. A zero
  result returns0; a nonzero result intersects with the prior nonzero mask and
  returns1 even when that intersection is empty. There is no index guard.
- Self HP is an unsigned-halfword percentage at or below a full64 signed
  threshold. Self MP is an absolute halfword amount. A zero maximum HP traps
  before division; friend iteration can leave earlier target marks in memory.
- Friend queries scan slots4..13 and enemy queries0..3. They require party
  flag1 and exclude flags38. These are native ranges, not a universal claim
  about affiliation for every actor. Status queries compare `(status & FFF)`
  exactly with the argument. Enemy-ID and alignment queries additionally
  exclude unit flag4; friend-ID skips context+30 and has no unit-flag4 test.
- The check counter is read, incremented below127, and stored before the
  threshold comparison, including failing checks. Hojo codes0..17 map signed
  counters to positive/negative tests or inclusive min/max tests. Code10 is
  the original default. Out-of-range full64 codes return0.
- Player/party level and turn predicates do not create target marks. Hama
  eligibility uses the actual affinity getter for attribute6. SKILLNOMP tests
  the actual cost failure code, which can mean HP, MP or sealing; it is not
  exclusively an MP check.
- HP cost retains the signed low-word MULT/DIV1 calculation, flat addition,
  minimum1 and original free-cost flags. MP cost retains its separate race
  flag. `nbCheckSkillCost` distinguishes0/1/2/3 and the actual seal test.
  `nbGetLvAvg` scans fourteen actual party records with the native side/flag
  tests and returns0 for an empty count.
- The script bridge clears the mask, calls the dispatcher and stores the real
  VM boolean. Parameterized wrappers OR their fixed type into the full raw
  parameter without clamping it. Connected programs use real PUSHIS, COMM,
  PUSHREG, POPIX, AI_TAR_JOKEN, AI_ACT_WAIT and END. POPIX stores the boolean
  before END; END otherwise consumes a stacked value as a return address.

The fixtures distinguish shipped data from constructed flags, costs, counters,
tags and explicitly backed callback targets. The original null slot29 is
replaced only in declared constructed inputs to test the dispatcher without
inventing a native bounds guard. Invalid original dereferences remain unproved.

## Community and Unity evidence

The pinned [Atlus Script Tools SMT3 library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/SMT3/Modules/Common/Functions.json)
provides all 24 query names and parameter counts. Each name/pop count is
corroborated against the original descriptor, target body and fixed type.
Names supply context; the native table and instructions decide behavior.
All 58 named Unity roles are reviewed as semantic references. Managed fields,
guards, array shapes and HD changes are not imported as native behavior.

The same revision's [DDS library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/DigitalDevilSaga/Modules/Common/Functions.json)
has sixteen same-name command descriptors. Their actual DDS targets/pop counts
are checked and attributed. No selected complete span resolves under the strict
DDS comparison. Keep those descriptors as leads; Nocturne's command numbers,
callback numbers, target ranges and layouts require separate DDS evidence.

Sources/revisions/hashes are in [the context audit](battle-ai-conditions-community.json),
[Unity review](battle-ai-conditions-matches.json) and [transfer report](battle-ai-conditions-transfer.json).
The broader [community inventory](community-research.md) also records original
randomizer/modding research and the newly inspected DDS/P4 source-transfer report.

## Current evidence and next work

[Validation](battle-ai-conditions-validation.json),
[affected rechecks](battle-ai-conditions-regression.json),
[saved-interface check](battle-ai-conditions-abi.json) and the current selected
export record support integration. One rolling fixture/vector pair is retained;
failed captures were overwritten. No checkpoint, project copy or duplicate
capture archive was created.

These are bounded original-instruction comparisons and constructed connected
programs. Unchanged original AI procedure decisions, dynamic scheduling,
physical gameplay, invalid pointers, arithmetic FCSR flags, timing and a
matching executable remain unproved. Continue remaining battle getters and
ordinary AI execution using the current [source-checked command census](battle-script-frontier.json),
then execute original AI procedures with their real dependencies.
