# VU color prerequisites: explicit operands, packing and MAC values

The 274-function canonical checkpoint remains unchanged. This work advances the two connected original color routines at `002b42b0` and `002b51d0`, and prepares a processor model usable for the broader VU recovery frontier. It does not count either routine as recovered C yet.

## Explicit instruction operands

The separate `drafts/vu_color_prerequisite/ee-vu-operands-draft/` changes seven families: VSUB, broadcast VSUB, broadcast ADDA, broadcast MADDA, broadcast MADD, ITOF0 and FTOI0. Their P-code exposes the old destination, Fs, Ft, old ACC, destination mask, broadcast selection, operation and numeric destination identifier. Writes to VF0 preserve the old architectural constant.

All **17,920 exact-value probes pass**: seven families, 16 masks, four selector encodings, five destination/source/VF0 cases and eight independent samples each. The test callbacks use Float operations only on exactly representable values. Expected encodings come from independent integer arithmetic. Unselected lanes include arbitrary raw-word sentinels. The tests also check source retention and the accumulator when it is not the destination.

The **18 actual arithmetic sites in the two original color bodies** are inspected under the draft. A separate Python decoder checks their masks, selectors, register identities, argument widths and destinations against the original instruction words. [Operand certificate](vu-operand-contract-validation.json) pins 58 audit inputs and the actual instruction-execution results. This establishes operand handling; the exact-value test callback must not be used as the general game arithmetic provider.

The first synthetic audit reused one address for changing words and exposed the emulator's decoded-instruction cache. That failed run remains in `drafts/vu_color_prerequisite/operand-audit-failed-cache.log`. The successful audit gives every instruction its own address and explicitly writes emulator memory before execution. Only its fresh report and log are certified.

## Packed channel values

PEXT(LB/LH) interleave the low source elements; PPAC(H/B) select alternating source elements. The test compares a bit-field callback with independently indexed byte arrays. The lane maps are also extracted and checked against the [pinned PCSX2 MMI source](https://github.com/PCSX2/pcsx2/blob/81526d4dc7cc70e4ae75abb35a789417456c6d43/pcsx2/MMI.cpp).

All **32,768 generated packing probes pass** across four families, eight register arrangements and 1,024 structured/random patterns each. The prior draft fails 4,092 cases, all writes to the zero GPR. Four specialized ignored-write constructors fix those cases in `ee-vu-packing-draft/`; ordinary-destination P-code remains identical. No flags are consumed or changed by these packing operations. [Packing certificate](vu-color-packing-validation.json) pins 58 inputs, both reports and the primary-source lane maps. These generated expectations are separate from published hardware captures.

## Arithmetic research model

The existing vendored `ps2float` revision is also used by the [libretro VU interpreter at that same revision](https://github.com/libretro/ps2/blob/6eabf2242d451ee2e6d52b1e3f10efb77143ed05/pcsx2/VUops.cpp). Its vector multiply-accumulate calls `ps2f_madd(acc,s,t,0)`. This supplies a concrete basis for adapting the already validated arithmetic core to VU values.

MAC output is not always the composition of two raw result words: intermediate multiplication overflow has result priority. For example, accumulator `ffffffff`, multiplicand `7fffffff` and multiplier `40000000` yield `7fffffff` through the reference MAC, whereas raw MUL followed by ADD yields zero. Twelve compiled-reference counterexamples establish that distinction in [the priority report](vu-madd-reference-priority.json). These hexadecimal words use the research model's extended finite encoding; IEEE NaN behavior is inapplicable.

The separate integer-only `VUArithmeticValueModel.java` retains the core's LGPL notice and ordered Booth/carry-save multiplication. It adds MAC overflow priority with `acc_of=0`, without changing the canonical EE provider. **121,952 Java/C reference comparisons pass**: 21,952 complete edge triples and 100,000 random raw-word triples. [MAC model certificate](vu-madd-model-validation.json) pins the adapter, generated probes, compiled C reference and Java class. This is consistency with the shared research algorithm, not 121,952 hardware measurements.

## Next integration

Register the integer provider against the explicit VU P-code and the audited packing callbacks, then execute the original color helper and callback against candidate C. Preserve raw32 address bindings, packed byte order, `0.5` bias, operand order, masks and MAC exception priority. The callback must execute its original key lookup, color helper and setter dependencies. Verify the consumed conversion domains and independently pin the original function bodies before naming or source promotion.

Once the new original-instruction comparisons pass, language/provider promotion requires a complete fresh canonical capture. Historical vectors and language pins remain immutable. Timing, flags, microprogram execution and whole-game hardware behavior remain outside the current value model; matching binary reconstruction is still unverified. Related SMT games require separate original-instruction checks before adopting these findings.
