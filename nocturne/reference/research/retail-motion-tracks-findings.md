# Original retail motion track integration

The existing recovered key search and motion controller pass **2,448 original-instruction comparisons** using unchanged retail Nocturne motion data. This adds integration evidence, with no new function credit or recovered game-code changes. Current recovery remains 1,790/8,982 recognized functions (19.929%); the progress audit records 300,883 focused and 763,567 aggregate comparisons across 132 focused reports.

## Inputs and community context

The [retail census](retail-motion-assets.json) reads the original DDS3 image in place: 742 uncompressed MT00 books across 688 model PB/AB files, 6,818 nonempty cuts and 978,745 distinct track offsets within books. Original PAC relocation and motion consumers establish the geometry. The inspected DDS community [motion binding definitions](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_motion_bindings.h), revision `bec33411543cdc487bad9debdf758f0090a2242c`, supply independently corroborated track terminology; original Nocturne instructions decide time interpretation and behavior.

The [selection](retail-motion-tracks-selection.json) contains all 74 tracks with nonmonotonic unsigned time words, plus two normal tracks for each of the eleven observed command kinds: 96 isolated tracks. Their original track bytes, command/index metadata, key payloads, frame counts and surrounding record context are preserved. Each track has twelve direct key-search cases and twelve frame-sampling cases: 2,304 comparisons. Targets and controller state for these isolated cases are constructed; they do not establish retail model-index association.

Twelve distinct small complete AB records contribute another 144 cases. They cover battle stone, reflection/absorption, player, event door/magatama, field WPC and miscellaneous records. Each case executes original pointer relocation, controller construction and cut change before sampling. Complete records range from 49 to 786 bytes, including zero-command books. Selection of these small records does not prove the full PB/AB loader.

## Compared execution

The [passing comparison report](retail-motion-tracks-validation.json) covers key search `002B4120` (1,152 cases) and controller sampling `002B3E90` (1,296 cases). All 119 selected main instruction addresses are reached. Actual dependencies execute 512,990 original steps, 41,213 vector instructions, 2,736 prelude calls, 780 creation/bind/capture callbacks and 2,088 sample/blend callbacks. The comparison checks 335,124 defined vector/ACC/Q values, 4,008 COP1 comparisons, selected RAM and unchanged isolated-track hashes.

There are 1,296 consecutive native frame updates. Defined returns agree in all cases: 216 return 1 (completed), 108 return 2 (looped), and 972 return 0. The initial sampler is void; its captured V0 remains diagnostic scratch in the original capture and is excluded from return comparison. Every subsequent defined update return is checked.

The [observation report](retail-motion-tracks-observations.json) independently reads original native outputs. All 1,152 key-pointer/weight outputs are recorded. For all 144 complete-book cases, reversing only the original relocation targets reproduces the entire original record byte for byte. There are no other book mutations.

## Unsigned time anomalies

All 74 unusual tracks are executed, giving 1,776 exceptional-track comparisons across key search and sampling. Their time sequences become ordered when viewed as signed halfwords, but the original key reader uses unsigned `LHU`. No signed reinterpretation, sorting or repairs are applied.

There are 78 zero-frame key queries among the twelve variants because some original endpoint variants also equal zero. Seventy-two select key index 1; six select index 0. The six are three morph tracks in each of `model/event/e619/hijiri.PB` and `model/event/e800/hijiri.PB`, at record offset 690,240 and book-relative track offsets 301,696, 301,844 and 301,992. Their times begin `[65315,65327,65332,...]` and later wrap to zero. At frame zero the native reader selects pair 0/1 and returns weight bits `C5AA1755` (approximately -5442.9165). The recovered C agrees with the native result.

The negative-frame queries select pair 0/1 and produce weights `3F800180`, `3F800182` or `C5AA1955`, according to the original track. These observations demonstrate actual search behavior on those bytes, without resolving author intent or proving which anomalous frames the game reaches during gameplay. Sampling retains the original controller's frame-clamping behavior.

## Current evidence and remaining work

The comparison pins the current original executable, selected assets, recovered sources, verifier and existing host DLL. No source, host adapter or DLL changed in this integration batch. The same rolling native capture was reused after correcting the verifier's treatment of a void sampler return; no duplicate capture or checkpoint was created. Existing source pins remain current, and no new full-suite run is claimed.

The inspected motion graph has no pending recognized bodies or missing exports. Next establish target/model associations and continue the remaining hit/model constructors and scheduling. In particular, group-motion change `001DD440` calls the pending effect unlink/creation paths `001DFB00` and `001DFA00`; its complete behavior needs those actual dependencies. Whole-executable reconstruction, physical gameplay validation and a matching binary remain outstanding. The tested DDS transfer spans are documented separately in [motion controller findings](model-motion-control-findings.md); these retail Nocturne assets add no new DDS body match.
