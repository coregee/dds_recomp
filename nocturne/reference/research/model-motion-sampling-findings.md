# Original basic-model motion sampling and blending

Twelve complete bodies in `src/model_motion_sampling.c` add 1,816 recognized bytes. All 3,584 original-instruction comparisons pass, reaching all 412 selected main addresses and executing 743,176 original steps. The comparisons cover full declared RAM, defined results, Status, the FCSR condition bit, processor primitives, callee saves, original table preservation, ordered callbacks and defined VU/ACC-overflow/Q values. The host build passes with warnings treated as errors.

The cases execute 71,068 vector instructions, 24,402 COP1 comparisons, 320 ordered original factory callbacks and 480 connected prelude calls. The latter represent 160 actual controller-construction, track-binding and captured-value sequences before sampling. These execute the recovered allocator and original minor factory targets, rather than injected constructor returns.

Another 3,584 existing controller/factory cases pass on the rebuilt host. [The current regression report](model-motion-sampling-regressions.json) checks source, verifier, input, vector, primitive-review and DLL hashes. All twelve working Ghidra interfaces were saved, checked after reopening and merged into corrected exports. Sample callbacks use A0/raw64 and F12/float32; blend adds F13/float32. Euler takes F12/F13/F14, while cosine returns its raw float32 result in F0. Host transport wrappers and private helpers receive no additional function credit.

## Reference context

Six reviewed Unity bodies provide semantic identities for position/scale sampling, visibility sampling/blending, Euler conversion and cosine. The six other callback metadata names alias the four-line empty `ChildHD.UpdateOption` body at `1810D6760`. They supply no usable algorithm identity and are explicitly rejected as counterpart bodies. Those recovered native callbacks use descriptive PS2 aliases.

The inspected [community motion bindings](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/include/sdf_motion_bindings.h) and [motion research source](https://github.com/Megami-Decomps/dds-decomp/blob/bec33411543cdc487bad9debdf758f0090a2242c/src/dds1/sdf/sdfMotion.c) at revision `bec33411543cdc487bad9debdf758f0090a2242c` inform key-track headers, interval pointers, capture fields and callback roles. [The reference review](model-motion-sampling-matches.json) retains direct links, fetched hashes, corroborated fields and the rejected Unity aliases. Native Nocturne instructions independently establish record widths, layouts, operation order and flag behavior. Community source is reference material; it is not copied, linked or executed.

## Native behavior recovered

- Position and scale sample unaligned three-word keys, multiply the second key by its weight into ACC, then multiply-add the first by the inverse weight. They set output W to one. Blend first interpolates keys, then blends with the node's captured vector using the original order and unclamped rate.
- Euler rotation samples three channels, converts their negative half-angles through the actual native cosine/sine polynomial, writes the quaternion and derives three matrix rows. Its blend path also performs the original shortest-sign normalized interpolation with the captured quaternion.
- Packed quaternion keys contain four signed halfwords with twelve fractional bits. The original PEXTLH/PSRAW16/VITOF12 sequence expands them before normalized interpolation. Optional capture blending runs a second actual normalized interpolation. Quaternion and matrix outputs retain the original grouping and value primitives.
- Visibility reads the first selected key byte, sets model flag bit4 for zero or clears it for nonzero. Its blend callback ignores the blend weight, as the original does.
- Cosine adds the original GP-relative quarter-turn constant and executes the real sine body. Euler conversion retains the original six trig calls and final multiply/add/subtract grouping.

The existing implicit-VU quaternion helper models vector results while excluding COP1 condition effects. The complete new consumers explicitly evaluate the original dot-sign comparison so the observable FCSR condition also agrees. VF3.XYZ is excluded for the three quaternion-consuming callback bodies because it carries scratch CPU-upper-lane transport outside that helper's defined contract. VF3.W, every other vector register, ACC values/overflow and Q remain compared. No existing verification is relaxed.

Native fixtures include varying key counts, before-first/last-key positions, loop/no-loop and zero-duration intervals, finite and raw floating patterns, signed packed keys, dirty upper argument bits, unclamped rates and connected factory/bind/capture paths. They are constructed backed records; they do not establish retail motion-asset decoding or runtime selection.

## Packed instruction validation

The first native capture stopped at an unregistered PEXTLH site. The verifier now registers that original site and implements opcode-pinned PSRAW and VITOF12 value operations. [PCSX2 MMI](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/MMI.cpp) and [VU operations](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/VUops.cpp) independently establish signed-word shifts and the binary-power conversion. Their inspected revision and fetched hashes are retained in [the primitive review](model-motion-packed-values-validation.json).

That review checks every one of the 65,536 signed-halfword keys against independently computed exact binary-power values in both Java and the compiled C value provider: 131,072 passing provider values. These checks add no game function or original-instruction comparison credit. The completed rolling native capture has no ERROR or uninitialized read. The corrected exporter retains its known temporary-language `rom0` block error, while its fresh summary confirms twelve complete exports, unsigned DIVU and unchanged function inventory. Interface application and reopen logs are clean.

## Transfer and remaining work

[Static DDS checks](model-motion-sampling-transfer.json) resolve all twelve complete selected counterparts. Ten independently checked original sample/blend vtable positions distinguish the otherwise duplicate visibility bodies. Full cosine and sine spans also agree after checked GP-relative constant/call relocations; both ELF reginfo GP values and eight byte-identical original constants are verified. This is static correspondence, not DDS execution or proof of unrelated data.

The five basic-model callback vtables are now recovered at these compared boundaries. Expanding the [indirect frontier](model-motion-creation-frontier.json) through ten original material constructors and one morph constructor exposes their actual vtable addresses and further callbacks: seventeen recognized pending bodies /1,652 bytes, with no missing exports in this inspected graph. Pending work includes the material/morph factory dispatch, selected constructors, text callbacks and morph sampling/blending. Whole-motion scheduling, full table extents, original retail asset associations, remaining hit/model constructors, physical PS2 runtime and a matching executable remain outstanding. Overlapping action/effect/motion graphs must not be summed.

Current recovery is 1,770/8,982 recognized functions (19.706%), with 259,420 recognized recovered bytes. The 129 focused reports contribute 291,779 cases; with the older 462,684-case full run, the aggregate is 754,463. Source hashes are checked now; historical verifier versions and DLL pins remain historical. No checkpoint, project/source copies or repeated full-suite capture were created.
