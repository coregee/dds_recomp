# Native quaternion path rotation

Recovered **three complete native routines / 284 recognized body bytes** in `src/path_rotation.c` and `.h`. All **3,072 original-instruction comparisons pass**, reaching all **62 main instruction addresses**. The original engine executes **138,800 steps / 40,899 vector instructions**, with **104,448 defined vector, ACC-overflow and Q values compared**. Saved working interfaces reopen independently and allthree current exports merge without failure. The affected C builds with warnings treated as errors.

Compiled recovery is **1,189 / 8,975 functions (13.248%)**, **627,322 aggregate comparisons / 181,820 summed original body bytes**. The last full run remains413 functions /462,684 cases; 776 additional routines contribute164,638 focused cases. All91 focused reports refer to unchanged current source. The full executable objective remains active.

## Original rotation behavior

Path flag2 selects channel18hex. Actual GetElement selects segment/weight and the native code loads two16-byte quaternion records intoVF10/VF11. A count-one resource reads the backed previous prefix; the managed HD bounds/special handling is not imported. The absent-channel path copiesVF0 identity toVF10 and leaves other state untouched.

The blend computes the dot product in `((X+Y)+Z)+W` order using VU MUL/ACC/MADD. Negative dot chooses a negated B inVF12; otherwise it copies B. It computes `A*(1-rate)+selectedB*rate`, without clamping the rate, then tail-normalizes. Native arithmetic grouping and ordered operands remain explicit. This is normalized linear blending, not spherical interpolation.

Normalization squares allfour lanes and sums `((W²+X²)+Y²)+Z²`. The native VRSQRT divides1 by the square root intoQ, then VMULQ scales allfour lanes. Zero/nonunit quaternions, opposite signs, extrapolation, raw exponent255/denormal words, dirty pointer high lanes and actual progress-to-rotation sequences are included. ACC overflow is retained because it changes subsequent MAC result priority.

## Math prerequisite and reference correction

`VURotationValueModel.java` uses an integer square-root digit loop and the already validated divider. ADD/MUL/MADD/MSUB track result words plus the ACC-overflow bit. The separate pinned C provider uses `tooling/reference/ps2float/ps2float.c`, SHA25690F6A70BA391E1ED5D604613C1A2B27200D1BC80DCB6D33E49CFD015AA2F2001. All **50,000 operand cases / 300,000 result values agree**, including both initial ACC-overflow states. This is agreement with a software reference, not a physical VU measurement; those prerequisite cases are not added to compiled game-function counts.

The previously suggested generic HD helpers are **rejected as exact identities**: NORMALIZE182658520 usesVector3.Normalize and retainsW; INTERPOLATE182657AD0 usesVector4.Lerp without the native sign choice and normalization. The HD camera-path GetRot18222F600 contains the appropriate inline quaternion dot/sign/blend/normalization pattern and is reviewed as the path-role counterpart. The two math routines remain descriptive native aliases.

## Compared state and transfer

The capture executes original opcodes with body-hashed instruction sites and actual GetElement/progression dependencies; it has no native function-return hooks. Full declared RAM, Status,CPU primitive counts,integer/FP callee saves and defined VU0/VU1/VU2/VU10/VU11/VU12,VU3.W,ACC four result/overflow lanes andQ agree. VU3.XYZ and incidental GPR upper lanes are scratch and excluded. Full status/MAC flags,FCSR exception flags,pipeline timing,physical PS2 behavior and live camera movement remain unproved. The affected existing path-evaluation comparison passes its1,728 cases with current source and its rolling original capture.

All **three selected complete DDS spans resolve**, with three agreeing callee constraints across the key/blend/normalize chain. DDS execution and a matching rebuilt PS2 executable remain outstanding.

## Current outputs and remaining work

`analysis/path-rotation-validation.json`, `-interfaces.json`, `-abi.json`, `-matches.json` and `-transfer.json` hold current evidence. `analysis/vu-rotation-values-validation.json` records the software-reference agreement. `tooling/recover_path_rotation.py` maintains rolling captures. No checkpoints, project copies, frozen sources or duplicate captures were created.

`analysis/path-rotation-next-frontier.json` records the full unresolved direct graph from path construction00116AD0 and camera creation001E7900, plus any indirect sites. Camera creation must be distinguished from selecting the follow camera:0010E248 increments the16-bit serial counter. Transform code also needs the quaternion-to-matrix/view-matrix chain. Full executable recovery and gameplay/matching-binary validation remain unfinished.

| PS2 entry | Function | Body bytes | DDS entry |
|---|---|---:|---|
| 00116528 | dds3PathBasicControlGetRot | 128 | 00117050 |
| 002C0AE0 | ps2QuaternionBlendNormalized | 120 | 002E8278 |
| 002C04E8 | ps2QuaternionNormalize | 36 | 002E7C80 |
