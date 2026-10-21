# Battle presentation, camera and formation recovery

41 complete native bodies are integrated in `src/battle_presentation.c/.h`.
The working Ghidra project was saved in place, all 41 interfaces independently
reopened, and all 41 current exports decompiled successfully. No checkpoint or
project copy was created.

The source-checked embedded battle BF census now covers **63/63 used command
IDs and 7,178/7,178 static command occurrences**. This closes the command-body
frontier at the compared boundaries; it does not prove execution of the 141
unchanged original procedures or their battle scheduling.

## Original-instruction evidence

The [rolling comparison](battle-presentation-validation.json) passes **6,400
cases**, **4,899,873 original steps** and all **728 selected main instruction
addresses**. It checks 3,632 recognized body bytes, all declared RAM, defined
raw returns, Status, FCSR condition, ordered VM calls and 32 VU registers plus
ACC, ACC overflow and Q. The 384 connected interpreter programs account for
1,432 actual VM indirect calls; 264,936 vector instructions and 4,712 C.LT.S
comparisons execute. These programs are constructed command tests, not unchanged
original battle procedures.

Actual main/work, pose setters, quaternion conversion/product, type-dispatched
object-control flags, printf and VM dependencies execute. The fixture objects
carry valid unit type5, control routing and pose pointers. Independent store
oracles include nonzero panel flags, randomized AI flags, nonzero event word
upper halves, actor indices, signed visibility indices and integer/float event
argument conversion. Existing AI, pose and camera comparisons add **14,944
passing affected rechecks**, without duplicate aggregate credit; see
[the regression report](battle-presentation-regressions.json).

## Native details retained

- Model operations traverse 32 physical slots of stride0xF0. Formation display
  uses sixteen slots, with group ranges0..3,4..13,14..15. Full64 group selectors
  differ from lowword formation indices.
- Formation visibility requires both flag masks0x1/0x2 and a basic pointer. It changes
  render bit0 and actual base-control flag0x1000 through the type dispatcher.
  Pose updates retain the second source load after the actual setter, including
  backed overlap with the pose flag word.
- The selection helper compacts pointers at5698E4, writes count569964 and mask
  569968, and leaves the unused pointer tail intact. Its bit31 shift signextends
  before the full64 mask AND. Target-party lookup uses the first target pointer.
- Both eight-byte panel helpers have byte stores in their return delay slots:
  00281E28 clears55123C and00282268 clears55123D. Auto-hide also clears5511A5.
- PRESS/NAKAMA store a full word at main+94, actor index halfword at main+92,
  and clear context+68. AI_CHANGE uses main+60 bit0x40000.
- Camera states are1A/1B/1C; the setter writes the low16 selector as a full word.
  Bougai retains count0/1/many selection, grouped doubled radius accumulation,
  max width/height, minimum400, original odd atan polynomial, PS2 vector length
  and normalization. It does not substitute Unity floating-point grouping.

The original Bougai vectors assign only XYZ. Its two untouched W stack words
are retained as explicit read-time machine operands, as is V0's untouched
upper64 in the sphere-center MFC1/QMTC2 transfer. The comparison observes 1,404
frame operand words and7,640 upper-register operand words. These transports
preserve original inputs rather than replacing game-function results. The
existing independently checked VU arithmetic model supplies SQRT/RSQRT values;
new instruction handling is opcode/body-scoped. Full machine flags and timing
remain outside this value model.

## Unity, community and SMT transfer

[39 reviewed Unity roles](battle-presentation-matches.json) identify the native
mechanisms. Managed layouts, bounds guards, UI visibility calls, initialization
and math grouping differ. The two tiny panel helpers retain descriptive aliases
without distinct Unity identities.

The [community audit](battle-presentation-community.json) records the
pre-recovery frontier and checks all eleven original command descriptors,
their parameter readers and static procedure intervals against pinned Atlus
Script Tools and randomizer references. Its original Nocturne label/section
qualifications remain applicable; it is research evidence, not a current
unrecovered-body count.

The [DDS transfer audit](battle-presentation-transfer.json) checks eight
same-name original DDS descriptors. No selected complete span resolves uniquely;
short target-bit and forwarding-command candidates remain ambiguous. Names
and numeric commands alone do not transfer native layouts or recovered bodies.

Current integrated recovery is **1,582 unique functions /8,979 (17.619%)**,
229,464 recognized body bytes and714,625 aggregate comparisons. Complete
unchanged original BF decisions, dynamic scheduling, physical gameplay and a
matching executable remain outstanding. The next step is to execute the original
embedded procedure paths with these now-recovered dependencies.
