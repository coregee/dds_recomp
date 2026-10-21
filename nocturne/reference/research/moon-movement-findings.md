# Moon movement and field light clearing

Two integrated C routines cover 500 original body bytes and pass 768 focused
original-instruction comparisons: `evtMoonAddMove` at001eac20 (432 bytes,
512 cases) and `ps2FieldLightClearMessage` at001234b0 (68 bytes,256 cases).
The host DLL builds with warnings treated as errors. Both interfaces were saved
in the working project, independently reopened, and exported successfully.
Movement takes a float in F12 and returns void. No checkpoint was created.

The movement routine stores its accumulated ADD.S result even when it does not
advance the phase. Exact threshold equality does not advance. Crossing the
threshold resets movement, advances the raw phase modulo16, sets the countdown
to30, and executes four real field-clear wrappers at folded new moon. Its byte
cycle counter wraps before the actual default-state RNG call; reset occurs above
12 or13 according to that result. Event bits502/503/504 control the signed
counter at global-work+11a7c; it increments below240, including negative values,
and sets505 at48 and506 at112 or160. The light wrapper gates on effect bit8,
executes the existing clear routine, then reloads the runtime word and sets bit1.

The retained Unity method `evtMoon$$evtMoonAddMove` at1821a5bd0 is a reviewed
logical counterpart. It shares the movement, phase, countdown, effect and event
tree, but uses a fixed12 cycle limit and managed32-bit phase/cycle fields rather
than PS2 bytes. PS2 randomness and storage widths are preserved in recovered C.
Original PS2 symbol spelling and identical cross-runtime behavior are unproved.
The Unity light-clear-message metadata at182051090 points to protected native
control flow; that exact identity remains tentative and the PS2 routine retains
a descriptive alias.

The focused comparisons execute the linked moon, event, RNG and field callees,
compare105,832 declared RAM bytes, and cover both random limits, byte wrap,
negative and capped counters, threshold equality and all effect masks. The81
diagnostic calls check the original format address and full sign-extended counter
at the external printf boundary. Formatter/FILE side effects are not executed.
Float evidence covers finite normal values and signed zeros, using the existing
EE ADD value model and comparing the C.LT condition bit. Exceptional encodings,
full FCSR exception/timing behavior, arbitrary RAM aliases, physical PS2 runtime
and matching-binary validation remain unproved.

Narrow DDS structure searches found no candidates for either body. Only explicit
address/GP displacements and jump targets were masked; local offsets, constants,
registers and relative branches remained exact. This does not establish absence
of the logical subsystem in DDS. Two shared SMT patterns record the useful
behavioral leads without asserting DDS equivalence.

Current evidence: [validation](moon-movement-validation.json),
[reopened interfaces](moon-movement-abi.json),
[HD counterpart review](moon-movement-matches.json),
[DDS comparison](moon-movement-transfer.json), and
[source](../src/moon_movement.c).
