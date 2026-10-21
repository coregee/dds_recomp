# Original battle action process, 2026-10-12

Subsequent [action completion recovery](battle-action-finish-findings.md) adds
actual state19/state21 updates and their effect/packet/timeline dependencies.
The dispatcher comparison below records the earlier callback boundary; the
current action graph retains459 unresolved bodies /100,032 bytes.

Twelve complete native bodies (868 recognized bytes) now compile and pass
2,176 comparisons against original PS2 instruction execution. All 164 selected
main instruction addresses execute. This adds the action process at `00257CD0`,
WAIT and END callbacks, three distinct empty entries, named kouka process lookup,
context-owned packet counting, CHECK3 progression and native ADPCM flag/stop helpers.
Five named Unity semantic roles are recorded; the changed HD unique-ID counter
remains a descriptive native alias. Shared empty/constant HD bodies do not
establish unique function identities.

## Dispatcher interface and progression

The old Ghidra listing omitted the process argument. Native `00257CE0` calls
`dds3GetProcessData` with the incoming A0; its full raw64 process interface is
now saved and independently checked after reopening the working project.
All twelve corrected interfaces and current exports are saved in place.

Context flags are word+4, current/next states signed bytes+8/+9, and the frame
counter an unsigned halfword+A. Flag400 invokes the actual recovered stock
renderer first. The original jump table at `00544100` treats effective state7
specially: the previous action must compare unsigned raw64 >=19 to advance.
A missing previous process yields -1 and therefore qualifies. Native ADPCM
checking, diagnostic output and real command100 submission happen even when
this previous-state gate prevents advancement; flag40 is checked afterward.

Flag2 defers the entry transition. Current state22 returns raw64 -1; other
states enter the signed-byte-indexed original table at `003FA7C0`, then clear
flag2. Ordinary update dispatch uses the second pointer of each pair. A nonzero
callback return sets flag2. The frame counter increments through FFFE and
saturates at FFFF. Native code supplies no index clamp or null-target guard.

The comparison executes actual updates2/3/15/20/22 and entries0/2/3/15/20/21/22.
The host adapter aborts on other unrecovered targets. These boundaries cover the
complete caller body, without establishing the other callback bodies or whole
battle scheduling. All 384 unchanged original A4 actor records pass scripted
entry through the dispatcher; another128 ordinary-entry samples execute actual AI.
The qualifying default chooser's state2/3 selection remains separate work.

## Native kouka and ADPCM behavior

The `nb_kouka` getter calls the original three-queue name search and then
unconditionally obtains process data. Its packet list starts at data+8; each
node's owner word+8 is sign extended and compared with the complete raw64
context argument, then node+C advances the list. HD instead counts a unique ID
and adds stock-hide behavior at CHECK3. The PS2 version only requests state21
when no packets belong to the context. WAIT requests state18. END reloads
flags before each of six actual diagnostic printf calls.

The ADPCM flag is the signed word at `005519C8`. Stop submits original command100
through the actual movie-command queue, including token increment with zero
skipped, packet/header writes, tail wrap and WakeupThread. Kernel return values
are explicit external inputs; kernel/CPU operands and results are compared in
order. This does not execute IOP audio or prove live scheduling.

## Community research and SMT transfer

The pinned [Nocturne randomizer notes](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/notes/nocturne_random.txt)
and [implementation](https://github.com/nmarkro/Nocturne-Randomizer/blob/f74e85c0f632b751eaf278046884961c618c8541/nocturne.py)
guide build/offset and A4/BF interpretation. Their upstream content hashes are
checked when pinning the new source. The broader
[BF format reference](https://github.com/tge-was-taken/Atlus-Script-Tools/blob/1c557a092dd7610829b7215be0f0f5101acf1d72/Documents/Reference/FlowScriptBFFormatReference.txt)
and community scheduler/source-unit audits remain context for the already
recovered actual constructors and process dependencies. No mod patch is applied.

Strict complete-span matching finds one unique 36-byte DDS wrapper at001028A0
for native0025E8E0, with the same name-search/get-data shape. Inspecting the
relocated literal rejects a kouka identity: DDS searches `Admini` at003BA848,
while Nocturne searches `nb_kouka` at00544350. The
[transfer report](battle-action-process-transfer.json) retains this shared
engine pattern but promotes zero selected same-role counterparts. This is why
code shape, symbols and community context need independent native checks.

## Evidence and remaining work

The [current comparison report](battle-action-process-validation.json) records
7,092,589 original steps, 694 actual entry callbacks,180 update callbacks,
54,000 VU instructions,298,112 defined vector/ACC/Q comparisons,16,200 observed
upper-GPR color words,150 quad allocations,4,425 ordering callbacks and1,218
kernel/CPU trace words. Both original dispatch tables, UI tables and sine
coefficients remain unchanged before and after every case. Complete declared
RAM, defined raw returns, Status, primitives and FCSR conditions also agree.

Another8,301 affected existing comparisons pass against the rebuilt host:
4,224 panel support,832 stock/party rendering,1,997 action entry and1,248 movie
queue cases. Their actual rolling vectors and all pinned input/source/verifier
hashes are checked in [the regression report](battle-action-process-regressions.json).
No copies, checkpoints or additional full-suite capture were created.

The current [action frontier](battle-action-dispatch-frontier.json) retains472
unresolved bodies /101,564 bytes across the inspected callbacks and direct
dependencies. Continue state21 effect deletion, state19 death completion,
state18 readiness and the default/communication chooser, then connect real
message-frame progression and outer scheduling. Arbitrary malformed states,
all remaining callbacks, physical gameplay and a matching executable remain
unproved.
