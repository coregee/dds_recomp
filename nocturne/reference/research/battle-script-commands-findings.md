# Retail BF random, wait and target commands

Twelve complete bodies in `src/battle_script_commands.c` and `.h` compile
and pass **3,328 original-instruction comparisons**, executing **8,639,240
steps**. They add **1,156 recognized body bytes**. All **211 selected main
instruction addresses** execute. Full declared RAM, defined raw64 returns,
Status, FCSR condition, CPU primitives, ordered libc/VM traces and returning
native callee saves agree. Actual sorting executes **24,504 C.LT.S
comparisons**. There are **256 connected interpreter programs**, **2,058
ordered VM indirect calls** and **183 original BREAK7 observations**.

| PS2 entry | Community command ID/name | Selector | Cases |
|---|---|---:|---:|
| `0010B908` | 10 / RND | Parameterized RNG | 384 |
| `00287DD8` | 50 / AI_ACT_WAIT | Action3 | 128 |
| `00287F30` | 53 / AI_TAR_LIFEMIN | 1 | 256 |
| `00287F98` | 345 / AI_TAR_BAARLV | 9 | 256 |
| `00288000` | 347 / AI_TAR_LVMIN | 10 | 256 |
| `00288068` | 54 / AI_TAR_BAD | 2; parameter0 | 256 |
| `002880D8` | 55 / AI_TAR_ID | 3; parameter0 | 256 |
| `00288148` | 57 / AI_TAR_LIGHT | 4 | 256 |
| `002881B0` | 58 / AI_TAR_DARK | 5 | 256 |
| `00288218` | 59 / AI_TAR_PLAYER | 6 | 256 |
| `00288280` | 60 / AI_TAR_RND | 8 | 256 |
| `002882E8` | 384 / AI_TAR_JOKEN | 7 | 256 |
| `0010B520` | Existing interpreter, connected programs | Already integrated | 256 |

## Native behavior

RND gets parameter0 through the actual packed VM getter, passes its unsigned
low word to the default RNG, adds1 with word arithmetic and writes the
actual integer-return tag/value. It returns1. Integer/return tags0/4,
float1, global integer2, global float3 and invalid/signed-negative tags
execute. Negative integer parameters are nonzero unsigned RNG bounds.
Float conversion retains the native truncation and saturation rules.

On a zero bound, the real RNG advances before the original BREAK7. The
return tag and value remain unchanged; no successful result or exception
unwinding contract is assigned. Independent oracles check every RND case's
four-word RNG state and return storage, including175 standalone traps.
The remaining8 traps occur inside connected programs before targeting/wait.
The CPU model only supplies DIVU's zero-divisor HI/LO values at the
opcode-checked original `002C0C74`; the actual following BEQL/BREAK7
executes. The host observer catches that exception without supplying a
game result. Other division sites and unobserved host traps remain unchanged.

AI_ACT_WAIT gets the context through the actual getter, loads the actor at
context+2C, stores halfword action3 at actor+6A and skill0 at actor+6C,
and returns1. Independent oracles also check the context target bitset
remains unchanged.

All ten target wrappers retain their context, call the actual automatic
selector with the listed selector, retry with selector0/parameter0 on a
nonzero result, and write the actual selection bitset to context+3C when
the final result is0. Only BAD and ID get an extra script parameter, after
the context getter. Every wrapper returns1.

The first failing automatic call stores action3/skill0. Its retry therefore
returns0 early; the wrapper then writes the actual empty target bits.
**320 independently checked failure cases** preserve this behavior. The
previous AI_TAR_AI command52 lacks this retry and retains the prior target
bitset on the initial failure. Group/single asymmetry and existing marks
come from the recovered actual selectors; the wrappers do not replace them.

The connected programs execute PUSHIS, COMM/RND, the selected target
command, COMM/AI_ACT_WAIT and END. BAD/ID programs additionally execute
PUSHREG so their parameter comes from RND's real VM return. There are248
returning programs and8 trapping programs. These constructed programs
test integration; they are not executions of the original AI procedures.

## Research and shared SMT evidence

The [SMT3 command library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/SMT3/Modules/Common/Functions.json)
supplies names and parameter counts at revision
`1c557a092dd7610829b7215be0f0f5101acf1d72`. Every selected original
target/pop-count pair is checked against the descriptor table at RAM0052E350
/ ELF file0042F350, and selector values are checked against the actual
caller instructions. Per-command RAM/file locations and source hashes
are recorded in `battle-script-commands-community.json`. Twelve named
Unity roles are reviewed separately; HD managed guards, layouts and RNG
behavior do not supply PS2 semantics.

The CPU zero-divisor rule is checked against [PCSX2 DIVU](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/R5900OpcodeImpl.cpp#L382)
at revision `81526d4dc7cc70e4ae75abb35a789417456c6d43`.

The complete RND span uniquely matches DDS `SLUS_209.74` at **0010D768**
after masking explicit call destinations. Its RNG helper's complete span
matches **002E83F8**, with an agreeing original caller edge. The independent
[DDS command library](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Source/AtlusScriptLibrary/Libraries/DigitalDevilSaga/Modules/Common/Functions.json)
and original DDS descriptor also identify command10/RND at0010D768.
Seven other same-name DDS descriptors remain leads, with no selected
complete-span match. Nocturne AI_TAR_RND is command60 whereas the DDS
same-name descriptor is command52. LIGHT/DARK/PLAYER/JOKEN names are absent
from that pinned DDS library. Per-game command numbers and context layouts
require their own verification; this is static transfer evidence, not DDS
execution.

## Current integration

The twelve interfaces are saved in the working project, independently
reopened and checked, and all12 updated exports decompile without failure
and merge into the8,979-entry inventory. The one rolling fixture/capture
pair declares29 RAM spans and176 body/opcode-checked COP1 sites. All
**29,517 affected existing cases** pass against retained captures: targeting,
selection, estimates, filters/actions, VM parameters/core/stack/operators
and compiler arithmetic. Those rechecks are not added again to totals.

Current source hashes agree across113 focused reports: **1,465 unique
integrated routines**, **216,276 recognized body bytes**, **229,861 focused
cases** and **692,545 aggregate cases**, including the earlier462,684-case
full run. There is no new full-suite run or checkpoint.

The original embedded BF census now has **26/63 compared command IDs**,
accounting for **5,545/7,178 static occurrences**. All used target wrappers
are covered. **37 command IDs /81 direct bodies /7,860 bytes** remain at
compared boundaries. Next are the Hojo/status/HP and battle-query commands,
then connected original-procedure execution. Static command coverage is
not full AI behavior coverage. Dynamic callbacks, scheduling, physical
gameplay, arithmetic FCSR flags, timing and a matching executable remain
unproved; full program recovery is still active.
