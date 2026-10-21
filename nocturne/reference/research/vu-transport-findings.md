# VU prerequisite for material color recovery

The original color interpolation helper at 002b42b0 (124 bytes) and blended callback at 002b51d0 (172 bytes) use quadword transfers, packed-integer unpacking, vector arithmetic, an accumulator, float conversions and repacking. Forty actual VU/MMI sites are captured in the draft reports. They remain outside the 274 recovered C functions.

The canonical processor model supplies only four bytes to QMTC2/QMFC2, although these instructions transfer 16 bytes. Its physical VF and ACC lane aliases also disagree with little-endian x/y/z/w ordering. Writes to VF0 or the zero GPR are not discarded in the affected transfer definitions. Direct execution exposes these issues, so using the current color pseudocode would not establish equivalent behavior.

A separate processor draft corrects transfer widths, ignored destination writes and physical lane aliases. Only `cop2.sinc` and its compiled `r5900.sla` differ from the canonical 16-file language. Transfer userops copy the actual P-code input; they do not replace game functions. The original ELF and both languages are attested before and after execution.

The [active executable inventory](vu-transport-impact.json) contains transfers in 670 recognized function bodies: 595 QMTC2, 171 QMFC2, 2,546 LQC2 and 1,712 SQC2 instructions. These are body counts and may include overlapping functions. None of the current 274 recovered functions contains one of these transfers. The inventory follows the active export index; one stale assembly file from an earlier boundary is excluded without deleting it. This establishes the breadth of the prerequisite, without claiming all transfer sites are affected in the same way.

| Evidence category | Current canonical model failures | Separate corrected draft failures |
| --- | --- | --- |
| 11 published transfer anchors | 10 | 0 |
| 1 extra synthetic ignored-GPR-write probe | 1 | 0 |
| 16,384 generated model-agreement probes | 10,924 | 0 |

The published anchors come from [ps2autotests transfer results at revision 97469ff](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/cpu/vu0_macro/transfer.expected), with its source preserved alongside the expected file. The generated cases compare randomized 128-bit transfers, memory loads/stores and ignored writes; their expectations are model-derived and are labelled separately. They are not additional hardware captures. [PCSX2's pinned VU interpreter](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/VUops.cpp) supplies an independent implementation reference. Local copies retain their third-party notices and serve as reference material.

Eight published multiply/add result words from the [TriAce test](https://github.com/unknownbrackets/ps2autotests/blob/97469ffbed8631277b94e28d01dabd702aa97ef3/tests/vu/games/triace.cpp) also match the existing raw-word EE provider. This is a narrow arithmetic anchor; it does not validate all VU operations, accumulator precision, exceptional values or flags.

The remaining arithmetic P-code lacks explicit destination masks, broadcast selection and previous destination/ACC inputs. Examples include masked VSUB and accumulator-dependent VMADD/VMADDA. A transfer fix cannot recover those lost dependencies. Next steps are explicit operand-preserving semantics, independent mask/broadcast/ACC tests, packed-integer and conversion tests, then fresh execution of the two original color routines. Promoting any language change requires a complete fresh canonical capture; historical expected rows must remain pinned to their original language.

[Transport validation certificate](vu-transport-validation.json) pins 46 audit inputs, both language inventories, original-site reports, published sources, generated results and eight arithmetic anchors. The draft lives under `drafts/vu_color_prerequisite/ee-vu-transport-draft/`. It is not installed or used to certify the 274-function checkpoint. Hardware execution, timing, pipeline hazards, flags, microprogram execution and matching binaries remain unverified.

The [next prerequisite checkpoint](vu-color-prerequisite-findings.md) now verifies explicit operands for seven arithmetic families, all masks and broadcasts, four packed-integer families and MAC result priority. Original color recovery and complete fresh canonical capture remain the next integration steps.
