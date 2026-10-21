# Native cvt wrapper recovery

The complete444-byte body at002d7ce8 is recovered as ps2LibcCvt. All512
comparisons pass through the actual dtoa,software-double,bigint,heap and memory
dependencies:5,868,097 original instruction positions and22,848 ordered trace
words. Declared RAM,raw64 return,Status and kernel traces agree. The interface is
saved in the working Ghidra project,independently reopened and exported successfully.

The native f/e/E/g/G tests compare full64-bit argument values. A high word attached
to the same low character therefore takes the unknown-character path. e/E increment
precision with signed-extension of the wrapping low word; f requests dtoa mode3,
other characters mode2. Negative double bits call actual soft-subtraction fromzero
and store byte45 in the caller's sign byte. Private dtoa sign/end words remain
separate from that byte. g/G without alternate flag skip padding; other formats
pad to precision,with f adding the decimal point. The original zero comparison
sets the end directly to the target. Length is stored last and no new terminator
is added after appended zeros. Selected sign/decimal/count-word aliases are tested.

Actual nested calls retain separate temporary guest words in the host adapter.
This replaces its previous single scratch slot and permits cvt->dtoa->d2b calls
without a fabricated callee result. The affected dtoa4,096 and stream1,408 checks
also passed after that change. Private compiled PS2 stack layout remains unproved.

Coverage reaches91/93 non-delay addresses. The two unvisited stores at002d7dfc/
002d7e00 require the returned digits to start with ASCII0 while the same actual
software comparator reports a nonzero value. Normal successful dtoa output uses
nonzero leading digits or an empty rounded-tozero string; subnormal/zero input
compares equal tozero. The retained branch is not claimed exercised by these cases.
Nonfinite direct f calls would use decimal-point9999 and overwrite static data;
the formatter's Inf/NaN path is separate,and those calls are outside this batch.

DDS00304ad8 uniquely matches the complete wrapper. The connected cohort has109
agreeing call links,six repeated globals,and the previously verified dtoa tables.
This is static transfer evidence,not DDS runtime or matching-executable proof.
Recovery is724/8,960 functions with553,510 aggregated comparisons. The complete
main formatter and its stream/unbuffered wrappers are the current source targets.
