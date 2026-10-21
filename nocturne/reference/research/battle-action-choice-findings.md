# Action selection, CHECK1 and action-context lifecycle

All thirteen selected original PS2 bodies are reconstructed in
`src/battle_action_choice.c`: 1,453 recognized instructions, 5,812 recognized
bytes and 5,880 span bytes. All 2,560 original/probe/main cases pass; native
interfaces were saved, freshly reopened and exported. The
[publication](battle-action-choice-publication.json) takes recovery to
2,715/9,062 functions and 465,952 recognized bytes. The current module has
548 source units; all 546 earlier objects and sources remain unchanged.
All 12,100 affected retained cases and the broad 413-function/462,684-case
suite pass on this module.

| PS2 entry | Retained Unity role | Native result / raw arguments |
| --- | --- | --- |
| 00251EF0 | SetTargetPlayer | void / context |
| 00251FD8 | SetTargetParty | void / context, target |
| 00252400 | CheckMukanNego | raw64 / context |
| 002525F0 | CheckSenseiNego | raw64 / context |
| 00252720 | CheckInotiNego | raw64 / context |
| 002529D0 | CheckBinjoNego | raw64 / context |
| 002532A8 | SetDamagePacket | void / context, damage |
| 00253490 | CheckAction_NON | raw64 / context |
| 00257488 | SetAction_CHECK1 | void / context |
| 002577D8 | CheckAction_CHECK1 | raw64 / context |
| 00257E30 | nbActionShutdown | void / process ID |
| 00257EB0 | InitActionProcessData | raw64 guest pointer / five arguments |
| 00257FA8 | nbInitActionProcess | void / five arguments |

The last two interfaces consume A0, A1, A2, A3 and T0, retaining all 64 bits
until original operations narrow them. They must not be squeezed into the
older compendium observer's three-argument limit. The existing canonical Core
observer already supports the required raw5, raw64/void and trap ownership.

The [source study](battle-action-choice-HD-community-study.json),
[admission](battle-action-choice-admission.json) and
[independent source review](battle-action-choice-independent-source-review.json)
bind original words, all 118 call sites, the 106 external sites across 47
identities, return ownership and volatile liveness. The thirteen Unity bodies
corroborate roles; managed object layouts, null checks and exceptions do not
replace PS2 behavior. Existing AI/BF interpreters, process services, packets,
RNG, pool and formatter execute as real dependencies.

## Native contexts and control

An action context is 1A4 bytes. It links Main at +0, formation at +24, actor at
+28 and UnitWork at +2C. The separate strides remain 240-byte actors,
128-byte formations and 236-byte unit records. The constructor really
allocates and clears its context, stores the five arguments, writes raw
BF800000 at context+14 and clears its timeline. That raw COP1 store does not
constitute selected floating arithmetic.

The default chooser's computed JR at 0025351C is an internal five-target table
at 005439E0. Its unsigned guard and every local target are retained. This is
not permission to invoke arbitrary callbacks. The selected lifecycle creates
the original 03F8 process and publishes its real ID in a Main+D4 slot selected
through the original signed cursor arithmetic at Main+E4. Shutdown receives
that process ID, obtains its actual userdata and releases the real context.

Connected tests can pass a genuine constructor return to later calls. For a
void initializer, they instead load its published process ID from actual
prior-call memory. These are caller argument bindings, with no inter-call RAM
patches or assumed allocation/process answers. Every call records the actual
arguments, declared width, completion, trap and any defined result.

## Arithmetic traps and immutable data

Three BREAK7 instructions remain in the reconstructed source. Two are
input-reachable: 002526C8 divides 21 by signed Main+1A before a zero-divisor
BREAK at 002526D0; 002528F0 traps on zero maximum HP before its later division
at 00252908. A trap retains partial RAM and the guest stack position; it does
not return or unwind the native frame. Later planned calls must not execute.
The third BREAK at 00257754 is annulled because the divisor is the preceding
literal 100. No fabricated input is used to claim that path was executed.

The original-runner projection supplies only the reviewed R5900 DIV-zero
HI/LO CPU values at 002526C8 before allowing the real branch/BREAK to execute.
Its opcode and trap instruction words are checked. It supplies no game helper
return, RNG outcome or expected memory. Generated Java and real helper sources
compile against the installed Ghidra libraries without opening the project or
executing the target.

Original Mukan permission halfwords at 003DCB4A + 48*ID are zero for all IDs
0..383. That qualifies normal-descriptor coverage. Native indexing has no
383 cap: 28 actual original halfwords are nonzero at backed raw IDs 384..511.
Those addresses can exercise an explicitly separate raw-ID stress domain
without patching the table or claiming a valid retail demon. The original
003DCB38/6000-byte span hashes to
`7b0cb876b9904e984260ce3cf27292e92bb6476148d821e17bb109d5d5b6d8f2`.

## Shared runtime and transfer limits

Three registered packet wrappers use the actual EffectHost CPU29 stack, while
scalar dependencies use the actual Core/sorter stack. The new provider joins
those existing stack owners before calls, returns and traps, preserving the
active upper lanes. Activation clears the CPU bank, so active-lane checks use
the post-activation baseline; the full caller CPU29 value is separately saved
and restored. No old provider, observer or CPU mirror is added.

The [transport admission](battle-action-choice-transport-admission.json)
identifies nine existing routing flags and three actual pointer cells. Pure
provider tests pass in Od/O2. Actual original/probe/main execution also passes
for all 2,560 cases. All 546 earlier source/object files are unchanged in the
additive 548-unit module.

Pinned community randomizer data and related SMT engine research inform the
input worlds and discovery priorities. Native AI header rows and embedded BF
scripts remain distinct. Context links, process priorities, callback pairs,
stack ownership and packet boundaries are transferable search leads. No DDS
counterpart, gameplay execution, exhaustive input coverage, full volatile or
private-frame identity, or physical PS2 behavior is established by this stage.

The actual cohort attempted 2,850 call positions, completed 2,802 and left 96 planned positions unexecuted after traps. The 48 trapped cases retain real partial RAM and interrupted guest SP. The [bounded floating-register review](battle-action-choice-ambient-FPR-review.json) distinguishes locally supplied packet F12 values from printf private spills; no arbitrary floating format or full private-frame identity is claimed.

## Measured instruction-path limits

The stored-results review lists 32 non-delay instruction positions not reached by this finite cohort. Source review covers every selected original instruction; passing these cases does not establish every branch edge. Both target-flag leaves also have independently derived whole ordinary-RAM postconditions.

Ghidra preservation checks cover all unselected function and symbol rows listed in the report, plus all initialized bytes. They normalize only the rendered name of the existing dynamic DEFAULT pointer label at 003FA7C4, after checking its exact properties and unchanged pointer to selected chooser 00253490. Renaming that chooser changes the label display automatically; no alias is created and its symbol identity and raw data remain unchanged. The [native report](battle-action-choice-native-ghidra.json) records this qualification.

The real sound-packet query follows Main+F4 to the existing Kouka process, then process+38 to its userdata and userdata+8 to the packet list. The cohort initializes that genuine object graph; the native query has no null-process fallback.
